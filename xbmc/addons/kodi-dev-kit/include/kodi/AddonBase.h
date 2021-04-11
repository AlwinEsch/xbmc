/*
 *  Copyright (C) 2005-2021 Team Kodi
 *  This file is part of Kodi - https://kodi.tv
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include "c-api/addon_base.h"
#include "c-api/dl/kodi_api_1.h"

#ifdef __cplusplus

#include <assert.h>
#include <dlfcn.h>
#include <memory>
#include <string>
#include <string.h>
#include <unistd.h>

namespace kodi
{

namespace gui
{
struct IRenderHelper;
} /* namespace gui */

//==============================================================================
/// @ingroup cpp_kodi_Defs
/// @defgroup cpp_kodi_Defs_HardwareContext using HardwareContext
/// @brief **Hardware specific device context**\n
/// This defines an independent value which is used for hardware and OS specific
/// values.
///
/// This is basically a simple pointer which has to be changed to the desired
/// format at the corresponding places using <b>`static_cast<...>(...)`</b>.
///
///
///-------------------------------------------------------------------------
///
/// **Example:**
/// ~~~~~~~~~~~~~{.cpp}
/// #include <d3d11_1.h>
/// ..
/// // Note: Device() there is used inside addon child class about
/// // kodi::addon::CInstanceVisualization
/// ID3D11DeviceContext1* context = static_cast<ID3D11DeviceContext1*>(kodi::addon::CInstanceVisualization::Device());
/// ..
/// ~~~~~~~~~~~~~
///
///@{
using HardwareContext = ADDON_HARDWARE_CONTEXT2;
///@}
//------------------------------------------------------------------------------

class ATTR_DLL_LOCAL dl
{
public:
  static inline std::string get_kodi_lib_path(int argc, char* argv[])
  {
    std::string main_shared;

    for (int i = 1; i < argc; ++i)
    {
      if (argv[i] == nullptr)
        break;

      std::string arg = argv[i];
      if (arg.rfind("--dl=", 0) == 0)
      {
        main_shared = arg.substr(strlen("--dl="));
        break;
      }
      else if ((arg == "-l") || (arg == "--dl"))
      {
        if (i + 1 < argc) // Make sure we aren't at the end of argv!
        {
          main_shared = argv[++i]; // Increment 'i' so we don't get the argument as the next argv[i].
          break;
        }
      }
    }

    return main_shared;
  }

  static inline bool LoadDll(int argc, char** argv)
  {
    const std::string libPath = get_kodi_lib_path(argc, argv);
    dll = dlopen(libPath.c_str(), RTLD_LAZY | RTLD_GLOBAL);
    if (dll == nullptr)
      return false;

    bool (*load_kodi_api_1)(struct kodi_api_1*) = reinterpret_cast<decltype(load_kodi_api_1)>(dlsym(dll, "load_kodi_api_1"));
    if (!load_kodi_api_1 || !load_kodi_api_1(&api))
    {
      fprintf(stderr, "FATAL: Failed to load required kodi dev kit lib '%s'!\n", libPath.c_str());
      dlclose(dll);
      return false;
    }

    return true;
  }

  static inline void UnloadDll()
  {
    dlclose(dll);
  }

  static kodi_api_1 api;
  static KODI_IFC_HDL hdl;
  static KODI_DLL_HDL dll;
};

class CSettingValue
{
public:
  explicit CSettingValue(const std::string& settingValue) : str(settingValue) {}
  bool empty() const { return str.empty(); }

  std::string GetString() const { return str; }
  int GetInt() const { return atoi(str.c_str()); }
  unsigned int GetUInt() const { return atoi(str.c_str()); }
  bool GetBoolean() const { return atoi(str.c_str()) > 0; }
  float GetFloat() const { return static_cast<float>(atof(str.c_str())); }
  template<typename enumType>
  enumType GetEnum() const
  {
    return static_cast<enumType>(GetInt());
  }

private:
  const std::string str;
};

namespace addon
{

template<class CPP_CLASS, typename C_STRUCT>
class CStructHdl
{
public:
  CStructHdl() : m_cStructure(new C_STRUCT()), m_owner(true) {}

  CStructHdl(const CPP_CLASS& cppClass)
    : m_cStructure(new C_STRUCT(*cppClass.m_cStructure)), m_owner(true)
  {
  }

  CStructHdl(const C_STRUCT* cStructure) : m_cStructure(new C_STRUCT(*cStructure)), m_owner(true) {}

  CStructHdl(C_STRUCT* cStructure) : m_cStructure(cStructure) { assert(cStructure); }

  const CStructHdl& operator=(const CStructHdl& right)
  {
    assert(&right.m_cStructure);
    if (m_cStructure && !m_owner)
    {
      memcpy(m_cStructure, right.m_cStructure, sizeof(C_STRUCT));
    }
    else
    {
      if (m_owner)
        delete m_cStructure;
      m_owner = true;
      m_cStructure = new C_STRUCT(*right.m_cStructure);
    }
    return *this;
  }

  const CStructHdl& operator=(const C_STRUCT& right)
  {
    assert(&right);
    if (m_cStructure && !m_owner)
    {
      memcpy(m_cStructure, &right, sizeof(C_STRUCT));
    }
    else
    {
      if (m_owner)
        delete m_cStructure;
      m_owner = true;
      m_cStructure = new C_STRUCT(*right);
    }
    return *this;
  }

  virtual ~CStructHdl()
  {
    if (m_owner)
      delete m_cStructure;
  }

  operator C_STRUCT*() { return m_cStructure; }
  operator const C_STRUCT*() const { return m_cStructure; }

  const C_STRUCT* GetCStructure() const { return m_cStructure; }

protected:
  C_STRUCT* m_cStructure = nullptr;

private:
  bool m_owner = false;
};

class IAddonInstance
{
public:
  explicit IAddonInstance(ADDON_INSTANCE type)
    : m_type(type)
  {
  }
  virtual ~IAddonInstance() = default;

  virtual ADDON_STATUS CreateInstance(ADDON_INSTANCE instanceType,
                                       const std::string& instanceID,
                                       KODI_HANDLE instance,
                                       KODI_HANDLE& addonInstance)
  {
    return ADDON_STATUS_NOT_IMPLEMENTED;
  }

  virtual void SetAddonStruct(KODI_HANDLE instance) = 0;

  const ADDON_INSTANCE m_type;
  std::string m_id;
};

class CAddonBase
{
public:
  CAddonBase() = default;
  virtual ~CAddonBase() = default;

  virtual ADDON_STATUS Create() { return ADDON_STATUS_OK; }

  virtual ADDON_STATUS SetSetting(const std::string& settingName,
                                  const CSettingValue& settingValue)
  {
    return ADDON_STATUS_UNKNOWN;
  }

  virtual ADDON_STATUS CreateInstance(ADDON_INSTANCE instanceType,
                                       const std::string& instanceID,
                                       KODI_HANDLE instance,
                                       KODI_HANDLE& addonInstance)
  {
    return ADDON_STATUS_NOT_IMPLEMENTED;
  }

  virtual void DestroyInstance(ADDON_INSTANCE instanceType,
                               const std::string& instanceID,
                               KODI_HANDLE addonInstance)
  {
  }

  /* Background helper for GUI render systems, e.g. Screensaver or Visualization */
  std::shared_ptr<kodi::gui::IRenderHelper> m_renderHelper;

  static struct CIfc
  {
    CAddonBase* m_addonBase{nullptr};
    KODI_OWN_HDL m_firstInstance{nullptr};
    KODI_ADDON_HDL m_globalSingleInstance{nullptr};
  } ifc;

// private:

  static inline void ADDONBASE_Destroy(KODI_ADDON_HDL hdl)
  {
    delete static_cast<CAddonBase*>(hdl);
  }

  static inline ADDON_STATUS ADDONBASE_SetSettingString(const KODI_ADDON_HDL hdl, const char* name, const char* value)
  {
    return static_cast<CAddonBase*>(hdl)->SetSetting(name, CSettingValue(value));
  }

  static inline ADDON_STATUS ADDONBASE_SetSettingBoolean(const KODI_ADDON_HDL hdl, const char* name, bool value)
  {
    return static_cast<CAddonBase*>(hdl)->SetSetting(name, CSettingValue(value ? "1" : "0"));
  }

  static inline ADDON_STATUS ADDONBASE_SetSettingInteger(const KODI_ADDON_HDL hdl, const char* name, int value)
  {
    return static_cast<CAddonBase*>(hdl)->SetSetting(name, CSettingValue(std::to_string(value)));
  }

  static inline ADDON_STATUS ADDONBASE_SetSettingFloat(const KODI_ADDON_HDL hdl, const char* name, float value)
  {
    return static_cast<CAddonBase*>(hdl)->SetSetting(name, CSettingValue(std::to_string(value)));
  }

  static inline ADDON_STATUS ADDONBASE_CreateInstance(const KODI_ADDON_HDL hdl,
                                                      ADDON_INSTANCE instanceType,
                                                      const char* instanceID,
                                                      KODI_INSTANCE_HDL* addonInstance,
                                                      KODI_IFC_HDL parent)
  {
    CAddonBase* base = static_cast<CAddonBase*>(hdl);

    ADDON_STATUS status = ADDON_STATUS_NOT_IMPLEMENTED;

    if (addonInstance == nullptr)
    {
      kodi::dl::api.kodi_log(ADDON_LOG_FATAL, "kodi::addon::CAddonBase CreateInstance called with empty instance memory");
      return ADDON_STATUS_PERMANENT_FAILURE;
    }

    /* Check about single instance usage:
     * 1. The kodi side instance pointer must be equal to first one
     * 2. The addon side instance pointer must be set
     * 3. And the requested type must be equal with used add-on class
     */
    if (ifc.m_globalSingleInstance &&
        static_cast<IAddonInstance*>(ifc.m_globalSingleInstance)->m_type == instanceType)
    {
      /* The handling here is intended for the case of the add-on only one
       * instance and this is integrated in the add-on base class.
       */
      static_cast<IAddonInstance*>(ifc.m_globalSingleInstance)->SetAddonStruct(addonInstance);
      status = ADDON_STATUS_OK;
    }
    else
    {
      /* Here it should use the CreateInstance instance function to allow
       * creation of several on one addon.
       */

      /* Check first a parent is defined about (e.g. Codec within inputstream) */
      if (parent != nullptr)
      {
        status = static_cast<IAddonInstance*>(parent)->CreateInstance(
            instanceType, instanceID, addonInstance, addonInstance->instance);
      }

      /* if no parent call the main instance creation function to get it */
      if (status == ADDON_STATUS_NOT_IMPLEMENTED)
      {
        status = base->CreateInstance(instanceType, instanceID, addonInstance, addonInstance->instance);
      }
    }

    if (addonInstance->instance == nullptr)
    {
      if (status == ADDON_STATUS_OK)
      {
        kodi::dl::api.kodi_log(ADDON_LOG_FATAL,
                                           "kodi::addon::CAddonBase CreateInstance returned an "
                                           "empty instance pointer, but reported OK!");
        return ADDON_STATUS_PERMANENT_FAILURE;
      }
      else
      {
        return status;
      }
    }

    if (static_cast<IAddonInstance*>(addonInstance->instance)->m_type != instanceType)
    {
      kodi::dl::api.kodi_log(ADDON_LOG_FATAL,
          "kodi::addon::CAddonBase CreateInstance difference between given and returned");
      delete static_cast<IAddonInstance*>(addonInstance->instance);
      addonInstance->instance = nullptr;
      return ADDON_STATUS_PERMANENT_FAILURE;
    }

    // Store the used ID inside instance, to have on destroy calls by addon to identify
    static_cast<IAddonInstance*>(addonInstance->instance)->m_id = instanceID;

    return status;
  }

  static inline void ADDONBASE_DestroyInstance(KODI_ADDON_HDL hdl,
                                               ADDON_INSTANCE instanceType,
                                               KODI_INSTANCE_HDL* instance)
  {
    CAddonBase* base = static_cast<CAddonBase*>(hdl);

    if (ifc.m_globalSingleInstance == nullptr && instance->instance != base)
    {
      base->DestroyInstance(instanceType, static_cast<IAddonInstance*>(instance->instance)->m_id, instance->instance);
      delete static_cast<IAddonInstance*>(instance->instance);
    }
  }
};

inline std::string ATTR_DLL_LOCAL GetLibPath(const std::string& append = "")
{
  char* str = kodi::dl::api.kodi_addon_get_lib_path();
  std::string ret = str;
  free(str);
  if (!append.empty())
  {
    if (append.at(0) != '\\' && append.at(0) != '/')
#ifdef TARGET_WINDOWS
      ret.append("\\");
#else
      ret.append("/");
#endif
    ret.append(append);
  }
  return ret;
}

inline std::string ATTR_DLL_LOCAL GetSharePath(const std::string& append = "")
{
  char* str = kodi::dl::api.kodi_addon_get_share_path();
  std::string ret = str;
  free(str);
  if (!append.empty())
  {
    if (append.at(0) != '\\' && append.at(0) != '/')
#ifdef TARGET_WINDOWS
      ret.append("\\");
#else
      ret.append("/");
#endif
    ret.append(append);
  }
  return ret;
}

inline std::string ATTR_DLL_LOCAL GetUserPath(const std::string& append = "")
{
  char* str = kodi::dl::api.kodi_addon_get_user_path();
  std::string ret = str;
  free(str);
  if (!append.empty())
  {
    if (append.at(0) != '\\' && append.at(0) != '/')
#ifdef TARGET_WINDOWS
      ret.append("\\");
#else
      ret.append("/");
#endif
    ret.append(append);
  }
  return ret;
}

inline std::string ATTR_DLL_LOCAL GetTempPath(const std::string& append = "")
{
  char* str = kodi::dl::api.kodi_addon_get_temp_path();
  std::string ret = str;
  free(str);
  if (!append.empty())
  {
    if (append.at(0) != '\\' && append.at(0) != '/')
#ifdef TARGET_WINDOWS
      ret.append("\\");
#else
      ret.append("/");
#endif
    ret.append(append);
  }
  return ret;
}

inline bool ATTR_DLL_LOCAL CheckSettingString(const std::string& settingName,
                                                std::string& settingValue)
{
  char* buffer = nullptr;
  bool ret = kodi::dl::api.kodi_addon_get_setting_string(settingName.c_str(), &buffer);
  if (buffer)
  {
    if (ret)
      settingValue = buffer;
    free(buffer);
  }
  return ret;
}

inline std::string ATTR_DLL_LOCAL GetSettingString(const std::string& settingName,
                                                     const std::string& defaultValue = "")
{
  std::string settingValue = defaultValue;
  CheckSettingString(settingName, settingValue);
  return settingValue;
}

inline void ATTR_DLL_LOCAL SetSettingString(const std::string& settingName,
                                              const std::string& settingValue)
{
  kodi::dl::api.kodi_addon_set_setting_string(settingName.c_str(), settingValue.c_str());
}

inline bool ATTR_DLL_LOCAL CheckSettingInt(const std::string& settingName, int& settingValue)
{
  return kodi::dl::api.kodi_addon_get_setting_int(settingName.c_str(), &settingValue);
}

inline int ATTR_DLL_LOCAL GetSettingInt(const std::string& settingName, int defaultValue = 0)
{
  int settingValue = defaultValue;
  CheckSettingInt(settingName, settingValue);
  return settingValue;
}

inline void ATTR_DLL_LOCAL SetSettingInt(const std::string& settingName, int settingValue)
{
  kodi::dl::api.kodi_addon_set_setting_int(settingName.c_str(), settingValue);
}

inline bool ATTR_DLL_LOCAL CheckSettingBoolean(const std::string& settingName, bool& settingValue)
{
  return kodi::dl::api.kodi_addon_get_setting_bool(settingName.c_str(), &settingValue);
}

inline bool ATTR_DLL_LOCAL GetSettingBoolean(const std::string& settingName,
                                               bool defaultValue = false)
{
  bool settingValue = defaultValue;
  CheckSettingBoolean(settingName, settingValue);
  return settingValue;
}

inline void ATTR_DLL_LOCAL SetSettingBoolean(const std::string& settingName, bool settingValue)
{
    kodi::dl::api.kodi_addon_set_setting_bool(settingName.c_str(), settingValue);
}

inline bool ATTR_DLL_LOCAL CheckSettingFloat(const std::string& settingName, float& settingValue)
{
  return kodi::dl::api.kodi_addon_get_setting_float(settingName.c_str(), &settingValue);
}

inline float ATTR_DLL_LOCAL GetSettingFloat(const std::string& settingName,
                                              float defaultValue = 0.0f)
{
  float settingValue = defaultValue;
  CheckSettingFloat(settingName, settingValue);
  return settingValue;
}

inline void ATTR_DLL_LOCAL SetSettingFloat(const std::string& settingName, float settingValue)
{
  kodi::dl::api.kodi_addon_set_setting_float(settingName.c_str(), settingValue);
}

template<typename enumType>
inline bool ATTR_DLL_LOCAL CheckSettingEnum(const std::string& settingName,
                                              enumType& settingValue)
{
  int settingValueInt = static_cast<int>(settingValue);
  bool ret = kodi::dl::api.kodi_addon_get_setting_int(settingName.c_str(), &settingValueInt);
  if (ret)
    settingValue = static_cast<enumType>(settingValueInt);
  return ret;
}

template<typename enumType>
inline enumType ATTR_DLL_LOCAL GetSettingEnum(const std::string& settingName,
                                                enumType defaultValue = static_cast<enumType>(0))
{
  enumType settingValue = defaultValue;
  CheckSettingEnum(settingName, settingValue);
  return settingValue;
}

template<typename enumType>
inline void ATTR_DLL_LOCAL SetSettingEnum(const std::string& settingName, enumType settingValue)
{
  kodi::dl::api.kodi_addon_set_setting_int(settingName.c_str(), static_cast<int>(settingValue));
}

} /* namespace addon */

inline bool Init(unsigned int api,
                 int argc, char* argv[],
                 struct KODI_ADDON_FUNC* func, bool via_main, bool no_receive)
{
  if (!kodi::dl::LoadDll(argc, argv))
    return false;

  KODI_IFC_HDL hdl = kodi::dl::api.kodi_init(api, argc, argv, func, via_main, no_receive);
  if (!hdl)
    return false;

  kodi::dl::hdl = hdl;

  return true;
}

inline void Deinit()
{
  kodi::dl::api.kodi_deinit(kodi::dl::hdl);
  kodi::dl::UnloadDll();
}

template<typename... Args>
void Log(const ADDON_LOG loglevel, const std::string& fmt, Args&&... args)
{
  kodi::dl::api.kodi_log(loglevel, fmt.c_str(), args...);
}

} /* namespace kodi */

#define KODI_STARTER \
  kodi_api_1 kodi::dl::api{0}; \
  KODI_IFC_HDL kodi::dl::hdl{nullptr}; \
  KODI_DLL_HDL kodi::dl::dll{nullptr};

#ifdef LIBRARY_ADDON
#define ADDONCREATOR(AddonClass) \
  KODI_STARTER \
  kodi::addon::CAddonBase::CIfc kodi::addon::CAddonBase::ifc; \
  ADDON_STATUS ADDON_Create(KODI_OWN_HDL first_instance, KODI_ADDON_HDL* hdl) \
  { \
    using namespace ::kodi::addon; \
    CAddonBase::ifc.m_firstInstance = first_instance; \
    CAddonBase::ifc.m_addonBase = new AddonClass; \
    *hdl = CAddonBase::ifc.m_addonBase; \
    return static_cast<CAddonBase*>(*hdl)->Create(); \
  } \
  extern "C" ATTR_DLL_EXPORT int non_blocking_main_start(int argc, char** argv) \
  { \
    static KODI_ADDON_FUNC func = {ADDON_Create, \
                              kodi::addon::CAddonBase::ADDONBASE_Destroy, \
                              kodi::addon::CAddonBase::ADDONBASE_CreateInstance, \
                              kodi::addon::CAddonBase::ADDONBASE_DestroyInstance, \
                              kodi::addon::CAddonBase::ADDONBASE_SetSettingString, \
                              kodi::addon::CAddonBase::ADDONBASE_SetSettingBoolean, \
                              kodi::addon::CAddonBase::ADDONBASE_SetSettingInteger, \
                              kodi::addon::CAddonBase::ADDONBASE_SetSettingFloat}; \
    return kodi::Init(__KODI_API__, argc, argv, &func, true, false) ? 0 : -1; \
  } \
  extern "C" ATTR_DLL_EXPORT void non_blocking_main_stop() \
  { \
    kodi::Deinit(); \
  }
#else
#define ADDONCREATOR(AddonClass) \
  KODI_STARTER \
  kodi::addon::CAddonBase::CIfc kodi::addon::CAddonBase::ifc; \
  ADDON_STATUS ADDON_Create(KODI_OWN_HDL first_instance, KODI_ADDON_HDL* hdl) \
  { \
    using namespace ::kodi::addon; \
    CAddonBase::ifc.m_firstInstance = first_instance; \
    CAddonBase::ifc.m_addonBase = new AddonClass; \
    *hdl = CAddonBase::ifc.m_addonBase; \
    return static_cast<CAddonBase*>(*hdl)->Create(); \
  } \
  extern "C" ATTR_DLL_EXPORT int main(int argc, char** argv) \
  { \
    static KODI_ADDON_FUNC func = {ADDON_Create, \
                              kodi::addon::CAddonBase::ADDONBASE_Destroy, \
                              kodi::addon::CAddonBase::ADDONBASE_CreateInstance, \
                              kodi::addon::CAddonBase::ADDONBASE_DestroyInstance, \
                              kodi::addon::CAddonBase::ADDONBASE_SetSettingString, \
                              kodi::addon::CAddonBase::ADDONBASE_SetSettingBoolean, \
                              kodi::addon::CAddonBase::ADDONBASE_SetSettingInteger, \
                              kodi::addon::CAddonBase::ADDONBASE_SetSettingFloat}; \
    if (!kodi::Init(__KODI_API__, argc, argv, &func, true, false)) \
      return -1; \
    while (1) \
    { \
      if (!kodi::dl::api.kodi_process(kodi::dl::hdl)) \
        break; \
    } \
    kodi::Deinit(); \
    return 0; \
  }
#endif

#endif /* __cplusplus */
