/*
 *  Copyright (C) 2005-2021 Team Kodi
 *  This file is part of Kodi - https://kodi.tv
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

/* File autogenerated, see xbmc/addons/kodi-dev-kit/tools/code-generator/code_generator.py */

#include "peripheral.h"

// Shared API
#include "addons/kodi-dev-kit/src/shared/api/addon-instance/peripheral.h"

// Kodi
#include "addons/interface/RunningProcess.h"
#include "peripherals/addons/PeripheralAddon.h"
#include "utils/log.h"

/* Code below becomes on auto generation reused, hand edited parts should included here */
/*---AUTO_GEN_PARSE<HAND_EDITED_FIELD_1>---*/
/*---AUTO_GEN_PARSE<HAND_EDITED_FIELD_1_END>---*/

namespace KODI
{
namespace ADDONS
{
namespace INTERFACE
{

/* Code below becomes on auto generation reused, hand edited parts should included here */
/*---AUTO_GEN_PARSE<HAND_EDITED_FIELD_2>---*/
/*---AUTO_GEN_PARSE<HAND_EDITED_FIELD_2_END>---*/

void CHdl_kodi_addoninstance_peripheral_h::InitDirect(
    directFuncToKodi_addoninstance_peripheral_h* ifcToKodi,
    directFuncToAddon_addoninstance_peripheral_h* ifcToAddon)
{
  ifcToKodi->thisClassHdl = this;
  m_ifcToAddon = ifcToAddon;
  ifcToKodi->kodi_addon_peripheral_trigger_scan_v1 = kodi_addon_peripheral_trigger_scan_v1;
  ifcToKodi->kodi_addon_peripheral_refresh_button_maps_v1 =
      kodi_addon_peripheral_refresh_button_maps_v1;
  ifcToKodi->kodi_addon_peripheral_feature_count_v1 = kodi_addon_peripheral_feature_count_v1;
  ifcToKodi->kodi_addon_peripheral_feature_type_v1 = kodi_addon_peripheral_feature_type_v1;
}

bool CHdl_kodi_addoninstance_peripheral_h::HandleMessage(int funcGroup,
                                                         int func,
                                                         const msgpack::unpacked& in,
                                                         msgpack::sbuffer& out)
{
  if (funcGroup != funcGroup_addoninstance_peripheral_h)
    return false;

  switch (func)
  {
    /* NOTE: Ignored as direct api only is set! */
    default:
      CLog::Log(LOGERROR,
                "CHdl_kodi_addoninstance_peripheral_h::{}: addon called with unknown function id "
                "'{}' on group 'addoninstance_peripheral_h'",
                __func__, func);
  }

  return false;
}

// Function calls from Kodi to addon

KODI_ADDON_PERIPHERAL_HDL CHdl_kodi_addoninstance_peripheral_h::kodi_addon_peripheral_create_v1(
    KODI_OWN_HDL kodi_hdl)
{
  // Original API call: typedef KODI_ADDON_PERIPHERAL_HDL(ATTR_APIENTRYP PFN_KODI_ADDON_PERIPHERAL_CREATE_V1)( KODI_OWN_HDL kodi_hdl);

  return m_ifcToAddon->kodi_addon_peripheral_create_v1(m_ifcToAddon->thisClassHdl, kodi_hdl);
}

void CHdl_kodi_addoninstance_peripheral_h::kodi_addon_peripheral_destroy_v1(
    KODI_ADDON_PERIPHERAL_HDL hdl)
{
  // Original API call: typedef void(ATTR_APIENTRYP PFN_KODI_ADDON_PERIPHERAL_DESTROY_V1)(KODI_ADDON_PERIPHERAL_HDL hdl);

  m_ifcToAddon->kodi_addon_peripheral_destroy_v1(m_ifcToAddon->thisClassHdl, hdl);
}

void CHdl_kodi_addoninstance_peripheral_h::kodi_addon_peripheral_get_capabilities_v1(
    KODI_ADDON_PERIPHERAL_HDL hdl, struct PERIPHERAL_CAPABILITIES* capabilities)
{
  // Original API call: typedef void(ATTR_APIENTRYP PFN_KODI_ADDON_PERIPHERAL_GET_CAPABILITIES_V1)( KODI_ADDON_PERIPHERAL_HDL hdl, struct PERIPHERAL_CAPABILITIES* capabilities);

  m_ifcToAddon->kodi_addon_peripheral_get_capabilities_v1(m_ifcToAddon->thisClassHdl, hdl,
                                                          capabilities);
}

enum PERIPHERAL_ERROR CHdl_kodi_addoninstance_peripheral_h::
    kodi_addon_peripheral_perform_device_scan_v1(KODI_ADDON_PERIPHERAL_HDL hdl,
                                                 struct PERIPHERAL_INFO** scan_results,
                                                 size_t* peripheral_count)
{
  // Original API call: typedef enum PERIPHERAL_ERROR(ATTR_APIENTRYP PFN_KODI_ADDON_PERIPHERAL_PERFORM_DEVICE_SCAN_V1)( KODI_ADDON_PERIPHERAL_HDL hdl, struct PERIPHERAL_INFO** scan_results, size_t* peripheral_count);

  return m_ifcToAddon->kodi_addon_peripheral_perform_device_scan_v1(m_ifcToAddon->thisClassHdl, hdl,
                                                                    scan_results, peripheral_count);
}

void CHdl_kodi_addoninstance_peripheral_h::kodi_addon_peripheral_free_scan_results_v1(
    KODI_ADDON_PERIPHERAL_HDL hdl, struct PERIPHERAL_INFO* scan_results, size_t peripheral_count)
{
  // Original API call: typedef void(ATTR_APIENTRYP PFN_KODI_ADDON_PERIPHERAL_FREE_SCAN_RESULTS_V1)( KODI_ADDON_PERIPHERAL_HDL hdl, struct PERIPHERAL_INFO* scan_results, size_t peripheral_count);

  m_ifcToAddon->kodi_addon_peripheral_free_scan_results_v1(m_ifcToAddon->thisClassHdl, hdl,
                                                           scan_results, peripheral_count);
}

enum PERIPHERAL_ERROR CHdl_kodi_addoninstance_peripheral_h::kodi_addon_peripheral_get_events_v1(
    KODI_ADDON_PERIPHERAL_HDL hdl, struct PERIPHERAL_EVENT** events, size_t* event_count)
{
  // Original API call: typedef enum PERIPHERAL_ERROR(ATTR_APIENTRYP PFN_KODI_ADDON_PERIPHERAL_GET_EVENTS_V1)( KODI_ADDON_PERIPHERAL_HDL hdl, struct PERIPHERAL_EVENT** events, size_t* event_count);

  return m_ifcToAddon->kodi_addon_peripheral_get_events_v1(m_ifcToAddon->thisClassHdl, hdl, events,
                                                           event_count);
}

void CHdl_kodi_addoninstance_peripheral_h::kodi_addon_peripheral_free_events_v1(
    KODI_ADDON_PERIPHERAL_HDL hdl, struct PERIPHERAL_EVENT* events, size_t event_count)
{
  // Original API call: typedef void(ATTR_APIENTRYP PFN_KODI_ADDON_PERIPHERAL_FREE_EVENTS_V1)(KODI_ADDON_PERIPHERAL_HDL hdl, struct PERIPHERAL_EVENT* events, size_t event_count);

  m_ifcToAddon->kodi_addon_peripheral_free_events_v1(m_ifcToAddon->thisClassHdl, hdl, events,
                                                     event_count);
}

bool CHdl_kodi_addoninstance_peripheral_h::kodi_addon_peripheral_send_event_v1(
    KODI_ADDON_PERIPHERAL_HDL hdl, const struct PERIPHERAL_EVENT* event)
{
  // Original API call: typedef bool(ATTR_APIENTRYP PFN_KODI_ADDON_PERIPHERAL_SEND_EVENT_V1)(KODI_ADDON_PERIPHERAL_HDL hdl, const struct PERIPHERAL_EVENT* event);

  return m_ifcToAddon->kodi_addon_peripheral_send_event_v1(m_ifcToAddon->thisClassHdl, hdl, event);
}

enum PERIPHERAL_ERROR CHdl_kodi_addoninstance_peripheral_h::
    kodi_addon_peripheral_get_joystick_info_v1(KODI_ADDON_PERIPHERAL_HDL hdl,
                                               unsigned int index,
                                               struct JOYSTICK_INFO* info)
{
  // Original API call: typedef enum PERIPHERAL_ERROR(ATTR_APIENTRYP PFN_KODI_ADDON_PERIPHERAL_GET_JOYSTICK_INFO_V1)( KODI_ADDON_PERIPHERAL_HDL hdl, unsigned int index, struct JOYSTICK_INFO* info);

  return m_ifcToAddon->kodi_addon_peripheral_get_joystick_info_v1(m_ifcToAddon->thisClassHdl, hdl,
                                                                  index, info);
}

void CHdl_kodi_addoninstance_peripheral_h::kodi_addon_peripheral_free_joystick_info_v1(
    KODI_ADDON_PERIPHERAL_HDL hdl, struct JOYSTICK_INFO* info)
{
  // Original API call: typedef void(ATTR_APIENTRYP PFN_KODI_ADDON_PERIPHERAL_FREE_JOYSTICK_INFO_V1)(KODI_ADDON_PERIPHERAL_HDL hdl, struct JOYSTICK_INFO* info);

  m_ifcToAddon->kodi_addon_peripheral_free_joystick_info_v1(m_ifcToAddon->thisClassHdl, hdl, info);
}

enum PERIPHERAL_ERROR CHdl_kodi_addoninstance_peripheral_h::kodi_addon_peripheral_get_features_v1(
    KODI_ADDON_PERIPHERAL_HDL hdl,
    const struct JOYSTICK_INFO* joystick,
    const char* controller_id,
    struct JOYSTICK_FEATURE** features,
    size_t* feature_count)
{
  // Original API call: typedef enum PERIPHERAL_ERROR(ATTR_APIENTRYP PFN_KODI_ADDON_PERIPHERAL_GET_FEATURES_V1)( KODI_ADDON_PERIPHERAL_HDL hdl, const struct JOYSTICK_INFO* joystick, const char* controller_id, struct JOYSTICK_FEATURE** features, size_t* feature_count);

  return m_ifcToAddon->kodi_addon_peripheral_get_features_v1(
      m_ifcToAddon->thisClassHdl, hdl, joystick, controller_id, features, feature_count);
}

void CHdl_kodi_addoninstance_peripheral_h::kodi_addon_peripheral_free_features_v1(
    KODI_ADDON_PERIPHERAL_HDL hdl, struct JOYSTICK_FEATURE* features, size_t feature_count)
{
  // Original API call: typedef void(ATTR_APIENTRYP PFN_KODI_ADDON_PERIPHERAL_FREE_FEATURES_V1)(KODI_ADDON_PERIPHERAL_HDL hdl, struct JOYSTICK_FEATURE* features, size_t feature_count);

  m_ifcToAddon->kodi_addon_peripheral_free_features_v1(m_ifcToAddon->thisClassHdl, hdl, features,
                                                       feature_count);
}

enum PERIPHERAL_ERROR CHdl_kodi_addoninstance_peripheral_h::kodi_addon_peripheral_map_features_v1(
    KODI_ADDON_PERIPHERAL_HDL hdl,
    const struct JOYSTICK_INFO* joystick,
    const char* controller_id,
    const struct JOYSTICK_FEATURE* features,
    size_t feature_count)
{
  // Original API call: typedef enum PERIPHERAL_ERROR(ATTR_APIENTRYP PFN_KODI_ADDON_PERIPHERAL_MAP_FEATURES_V1)( KODI_ADDON_PERIPHERAL_HDL hdl, const struct JOYSTICK_INFO* joystick, const char* controller_id, const struct JOYSTICK_FEATURE* features, size_t feature_count);

  return m_ifcToAddon->kodi_addon_peripheral_map_features_v1(
      m_ifcToAddon->thisClassHdl, hdl, joystick, controller_id, features, feature_count);
}

enum PERIPHERAL_ERROR CHdl_kodi_addoninstance_peripheral_h::
    kodi_addon_peripheral_get_ignored_primitives_v1(KODI_ADDON_PERIPHERAL_HDL hdl,
                                                    const struct JOYSTICK_INFO* joystick,
                                                    struct JOYSTICK_DRIVER_PRIMITIVE** primitives,
                                                    size_t* primitive_count)
{
  // Original API call: typedef enum PERIPHERAL_ERROR(ATTR_APIENTRYP PFN_KODI_ADDON_PERIPHERAL_GET_IGNORED_PRIMITIVES_V1)( KODI_ADDON_PERIPHERAL_HDL hdl, const struct JOYSTICK_INFO* joystick, struct JOYSTICK_DRIVER_PRIMITIVE** primitives, size_t* primitive_count);

  return m_ifcToAddon->kodi_addon_peripheral_get_ignored_primitives_v1(
      m_ifcToAddon->thisClassHdl, hdl, joystick, primitives, primitive_count);
}

void CHdl_kodi_addoninstance_peripheral_h::kodi_addon_peripheral_free_primitives_v1(
    KODI_ADDON_PERIPHERAL_HDL hdl,
    struct JOYSTICK_DRIVER_PRIMITIVE* primitives,
    size_t primitive_count)
{
  // Original API call: typedef void(ATTR_APIENTRYP PFN_KODI_ADDON_PERIPHERAL_FREE_PRIMITIVES_V1)(KODI_ADDON_PERIPHERAL_HDL hdl, struct JOYSTICK_DRIVER_PRIMITIVE* primitives, size_t primitive_count);

  m_ifcToAddon->kodi_addon_peripheral_free_primitives_v1(m_ifcToAddon->thisClassHdl, hdl,
                                                         primitives, primitive_count);
}

enum PERIPHERAL_ERROR CHdl_kodi_addoninstance_peripheral_h::
    kodi_addon_peripheral_set_ignored_primitives_v1(
        KODI_ADDON_PERIPHERAL_HDL hdl,
        const struct JOYSTICK_INFO* joystick,
        const struct JOYSTICK_DRIVER_PRIMITIVE* primitives,
        size_t primitive_count)
{
  // Original API call: typedef enum PERIPHERAL_ERROR(ATTR_APIENTRYP PFN_KODI_ADDON_PERIPHERAL_SET_IGNORED_PRIMITIVES_V1)( KODI_ADDON_PERIPHERAL_HDL hdl, const struct JOYSTICK_INFO* joystick, const struct JOYSTICK_DRIVER_PRIMITIVE* primitives, size_t primitive_count);

  return m_ifcToAddon->kodi_addon_peripheral_set_ignored_primitives_v1(
      m_ifcToAddon->thisClassHdl, hdl, joystick, primitives, primitive_count);
}

void CHdl_kodi_addoninstance_peripheral_h::kodi_addon_peripheral_save_button_map_v1(
    KODI_ADDON_PERIPHERAL_HDL hdl, const struct JOYSTICK_INFO* joystick)
{
  // Original API call: typedef void(ATTR_APIENTRYP PFN_KODI_ADDON_PERIPHERAL_SAVE_BUTTON_MAP_V1)( KODI_ADDON_PERIPHERAL_HDL hdl, const struct JOYSTICK_INFO* joystick);

  m_ifcToAddon->kodi_addon_peripheral_save_button_map_v1(m_ifcToAddon->thisClassHdl, hdl, joystick);
}

void CHdl_kodi_addoninstance_peripheral_h::kodi_addon_peripheral_revert_button_map_v1(
    KODI_ADDON_PERIPHERAL_HDL hdl, const struct JOYSTICK_INFO* joystick)
{
  // Original API call: typedef void(ATTR_APIENTRYP PFN_KODI_ADDON_PERIPHERAL_REVERT_BUTTON_MAP_V1)( KODI_ADDON_PERIPHERAL_HDL hdl, const struct JOYSTICK_INFO* joystick);

  m_ifcToAddon->kodi_addon_peripheral_revert_button_map_v1(m_ifcToAddon->thisClassHdl, hdl,
                                                           joystick);
}

void CHdl_kodi_addoninstance_peripheral_h::kodi_addon_peripheral_reset_button_map_v1(
    KODI_ADDON_PERIPHERAL_HDL hdl, const struct JOYSTICK_INFO* joystick, const char* controller_id)
{
  // Original API call: typedef void(ATTR_APIENTRYP PFN_KODI_ADDON_PERIPHERAL_RESET_BUTTON_MAP_V1)( KODI_ADDON_PERIPHERAL_HDL hdl, const struct JOYSTICK_INFO* joystick, const char* controller_id);

  m_ifcToAddon->kodi_addon_peripheral_reset_button_map_v1(m_ifcToAddon->thisClassHdl, hdl, joystick,
                                                          controller_id);
}

void CHdl_kodi_addoninstance_peripheral_h::kodi_addon_peripheral_power_off_joystick_v1(
    KODI_ADDON_PERIPHERAL_HDL hdl, unsigned int index)
{
  // Original API call: typedef void(ATTR_APIENTRYP PFN_KODI_ADDON_PERIPHERAL_POWER_OFF_JOYSTICK_V1)(KODI_ADDON_PERIPHERAL_HDL hdl, unsigned int index);

  m_ifcToAddon->kodi_addon_peripheral_power_off_joystick_v1(m_ifcToAddon->thisClassHdl, hdl, index);
}

// Callbacks from addon to Kodi

void CHdl_kodi_addoninstance_peripheral_h::kodi_addon_peripheral_trigger_scan_v1(void* thisClassHdl,
                                                                                 KODI_OWN_HDL hdl)
{
  auto thisClass = reinterpret_cast<CHdl_kodi_addoninstance_peripheral_h*>(thisClassHdl);
  if (thisClass == nullptr)
    return;

  /*---AUTO_GEN_PARSE<HAND_EDITED_FIELD_KODI_ADDON_PERIPHERAL_TRIGGER_SCAN>---*/
  // AUTOGENERATED - Used by class "PERIPHERALS::CPeripheralAddon" with "void TriggerDeviceScan()" on "peripherals/addons/PeripheralAddon.h".

  PERIPHERALS::CPeripheralAddon* cb = static_cast<PERIPHERALS::CPeripheralAddon*>(hdl);
  cb->TriggerDeviceScan();
  /*---AUTO_GEN_PARSE<HAND_EDITED_FIELD_KODI_ADDON_PERIPHERAL_TRIGGER_SCAN_END>---*/
}

void CHdl_kodi_addoninstance_peripheral_h::kodi_addon_peripheral_refresh_button_maps_v1(
    void* thisClassHdl, KODI_OWN_HDL hdl, const char* device_name, const char* controller_id)
{
  auto thisClass = reinterpret_cast<CHdl_kodi_addoninstance_peripheral_h*>(thisClassHdl);
  if (thisClass == nullptr)
    return;

  /*---AUTO_GEN_PARSE<HAND_EDITED_FIELD_KODI_ADDON_PERIPHERAL_REFRESH_BUTTON_MAPS>---*/
  // AUTOGENERATED - Used by class "PERIPHERALS::CPeripheralAddon" with "void RefreshButtonMaps(const std::string& strDeviceName, const std::string& controllerId = "")" on "peripherals/addons/PeripheralAddon.h".

  PERIPHERALS::CPeripheralAddon* cb = static_cast<PERIPHERALS::CPeripheralAddon*>(hdl);
  cb->RefreshButtonMaps(device_name, controller_id);
  /*---AUTO_GEN_PARSE<HAND_EDITED_FIELD_KODI_ADDON_PERIPHERAL_REFRESH_BUTTON_MAPS_END>---*/
}

unsigned int CHdl_kodi_addoninstance_peripheral_h::kodi_addon_peripheral_feature_count_v1(
    void* thisClassHdl,
    KODI_OWN_HDL hdl,
    const char* controller_id,
    enum JOYSTICK_FEATURE_TYPE type)
{
  auto thisClass = reinterpret_cast<CHdl_kodi_addoninstance_peripheral_h*>(thisClassHdl);
  if (thisClass == nullptr)
    return 0;

  /*---AUTO_GEN_PARSE<HAND_EDITED_FIELD_KODI_ADDON_PERIPHERAL_FEATURE_COUNT>---*/
  // AUTOGENERATED - Used by class "PERIPHERALS::CPeripheralAddon" with "unsigned int FeatureCount(const std::string& controllerId, JOYSTICK_FEATURE_TYPE type) const" on "peripherals/addons/PeripheralAddon.h".

  PERIPHERALS::CPeripheralAddon* cb = static_cast<PERIPHERALS::CPeripheralAddon*>(hdl);
  return cb->FeatureCount(controller_id, type);
  /*---AUTO_GEN_PARSE<HAND_EDITED_FIELD_KODI_ADDON_PERIPHERAL_FEATURE_COUNT_END>---*/
}

enum JOYSTICK_FEATURE_TYPE CHdl_kodi_addoninstance_peripheral_h::
    kodi_addon_peripheral_feature_type_v1(void* thisClassHdl,
                                          KODI_OWN_HDL hdl,
                                          const char* controller_id,
                                          const char* feature_name)
{
  auto thisClass = reinterpret_cast<CHdl_kodi_addoninstance_peripheral_h*>(thisClassHdl);
  if (thisClass == nullptr)
    return JOYSTICK_FEATURE_TYPE_UNKNOWN;

  /*---AUTO_GEN_PARSE<HAND_EDITED_FIELD_KODI_ADDON_PERIPHERAL_FEATURE_TYPE>---*/
  // AUTOGENERATED - Used by class "PERIPHERALS::CPeripheralAddon" with "JOYSTICK_FEATURE_TYPE FeatureType(const std::string& controllerId,const std::string& featureName) const" on "peripherals/addons/PeripheralAddon.h".

  PERIPHERALS::CPeripheralAddon* cb = static_cast<PERIPHERALS::CPeripheralAddon*>(hdl);
  return cb->FeatureType(controller_id, feature_name);
  /*---AUTO_GEN_PARSE<HAND_EDITED_FIELD_KODI_ADDON_PERIPHERAL_FEATURE_TYPE_END>---*/
}

/* Code below becomes on auto generation reused, hand edited parts should included here */
/*---AUTO_GEN_PARSE<HAND_EDITED_FIELD_3>---*/
/*---AUTO_GEN_PARSE<HAND_EDITED_FIELD_3_END>---*/

} /* namespace INTERFACE */
} /* namespace ADDONS */
} /* namespace KODI */
