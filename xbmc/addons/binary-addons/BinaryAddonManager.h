#pragma once
/*
 *      Copyright (C) 2005-2017 Team Kodi
 *      http://kodi.tv
 *
 *  This Program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2, or (at your option)
 *  any later version.
 *
 *  This Program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with Kodi; see the file COPYING.  If not, see
 *  <http://www.gnu.org/licenses/>.
 *
 */

#include "addons/AddonManager.h"
#include "addons/kodi-addon-dev-kit/include/kodi/AddonBase.h"
#include "threads/CriticalSection.h"
#include "threads/Thread.h"
#include "utils/ActorProtocol.h"

#include <map>

namespace ADDON
{

  class IAddonInstanceHandler;

  class CAddonDll;
  typedef std::shared_ptr<CAddonDll> AddonDllPtr;

  class CBinaryAddonBase;
  typedef std::shared_ptr<CBinaryAddonBase> BinaryAddonBasePtr;
  typedef std::vector<BinaryAddonBasePtr> BinaryAddonBaseList;

  class IBinaryAddonManagerCallback
  {
  public:
    virtual ~IBinaryAddonManagerCallback() {};
    virtual void EnableEvent(BinaryAddonBasePtr addon) {}
    virtual void DisableEvent(BinaryAddonBasePtr addon) {}
    virtual void UpdateEvent(BinaryAddonBasePtr addon) {}
    virtual void InstallEvent(BinaryAddonBasePtr addon, bool update, bool modal) {}
    virtual void PreUnInstallEvent(BinaryAddonBasePtr addon) {}
    virtual void PostUnInstallEvent(BinaryAddonBasePtr addon) {}
    virtual bool RequestRestart(BinaryAddonBasePtr addon, bool datachanged) { return false; }
  };

  class CBinaryAddonDataProtocol : public Actor::Protocol
  {
  public:
    CBinaryAddonDataProtocol(std::string name, CEvent* inEvent, CEvent *outEvent) : Protocol(name, inEvent, outEvent) {};
    enum OutSignal
    {
      ENABLE_EVENT,
      DISABLE_EVENT,
      PRE_INSTALL_EVENT,
      POST_INSTALL_EVENT,
      PRE_UNINSTALL_EVENT,
      POST_UNINSTALL_EVENT,
      TIMEOUT,
    };
    enum InSignal
    {
      ACC,
      ERR,
    };
  };

  struct MsgAddonPostInstall
  {
    std::string addonID;
    bool update;
    bool modal;
  };

  class CBinaryAddonManager : private CThread
  {
  public:
    CBinaryAddonManager();
    ~CBinaryAddonManager();

    bool Init();
    void DeInit();

    /*!
     * @brief Checks system about given type to know related add-on's are
     * installed.
     *
     * @param[in] type Add-on type to check installed
     * @return true if given type is installed
     */
    bool HasInstalledAddons(const TYPE &type) const;

    /*!
     * @brief Checks system about given type to know related add-on's are
     * installed and also minimum one enabled.
     *
     * @param[in] type Add-on type to check enabled
     * @return true if given type is enabled
     */
    bool HasEnabledAddons(const TYPE &type) const;

    /*!
     * @brief Checks whether an addon is installed.
     *
     * @param[in] addonId id of the addon
     * @param[in] type Add-on type to check installed
     * @return true if installed
     */
    bool IsAddonInstalled(const std::string& addonId, const TYPE &type = ADDON_UNKNOWN);

    /*!
     * @brief Check whether an addon has been enabled.
     *
     * @param[in] addonId id of the addon
     * @param[in] type Add-on type to check installed and enabled
     * @return true if enabled
     */
    bool IsAddonEnabled(const std::string& addonId, const TYPE &type = ADDON_UNKNOWN);

    /*!
     * @brief Get a list of add-on's with info's for the on system available
     * ones.
     *
     * @param[out] addonInfos list where finded addon information becomes stored
     * @param[in] enabledOnly If true are only enabled ones given back,
     *                        if false all on system available. Default is true.
     * @param[in] type        The requested type, with "ADDON_UNKNOWN"
     *                        are all add-on types given back who match the case
     *                        with value before.
     *                        If a type id becomes added are only add-ons
     *                        returned who match them. Default is for all types.
     */
    void GetAddonInfos(BinaryAddonBaseList& addonInfos, bool enabledOnly, const TYPE &type) const;

    /*!
     * @brief Get a list of disabled add-on's with info's for the on system
     * available ones.
     *
     * @param[out] addonInfos list where finded addon information becomes stored
     * @param[in] type        The requested type, with "ADDON_UNKNOWN"
     *                        are all add-on types given back who match the case
     *                        with value before.
     *                        If a type id becomes added are only add-ons
     *                        returned who match them. Default is for all types.
     */
    void GetDisabledAddonInfos(BinaryAddonBaseList& addonInfos, const TYPE& type);

    /*!
     * @brief To get information from a installed add-on
     *
     * @param[in] addonId the add-on id to get the info for
     * @param[in] type if used becomes used type confirmed and is supported, if
     *                 not a nullptr is returned
     * @return add-on information pointer of installed add-on
     */
    const BinaryAddonBasePtr GetInstalledAddonInfo(const std::string& addonId, const TYPE &type = ADDON_UNKNOWN) const;

    /*!
     * @brief Used from other addon manager to get active addon over a from him
     * created CAddonDll.
     *
     * @param[in] addonId related addon id string
     * @return if present the pointer to active one or nullptr if not present
     *
     */
    AddonPtr GetRunningAddon(const std::string& addonId) const;

    /*!
     * @brief To get the path where temporary addon parts can be becomes stored
     *
     * @return the base path used for temporary addon paths
     *
     * @warning the folder and his contents becomes deleted during stop and
     * close of Kodi
     */
    const std::string& GetTempAddonBasePath() { return m_tempAddonBasePath; }

    /*!
     * @brief Used to register callback functions on manager
     *
     * The callbacks are done in case of addon changes to do needed work on
     * related addon systems, e.g. stop Live TV playback and unload related
     * dll, then the addon can be easily changed.
     *
     * @param[in] type the add-on type who need to observed by the callback
     * @param[in] cb The class who include IBinaryAddonManagerCallback as
     *               parent and have his functions as child
     * @return true if register is successfull done
     */
    bool RegisterCallback(const TYPE type, IBinaryAddonManagerCallback *cb);

    /*!
     * @brief Unregister addon change observer
     *
     * This unregister the with RegisterCallback() created parts.
     *
     * @param[in] type the addon type callback to unregister.
     */
    void UnregisterCallback(const TYPE type);

    /*!
     * Event functions called from CAddonDll in case of changes
     */
    //@{
    void OnEnabledEvent(const std::string& addonId);
    void OnDisabledEvent(const std::string& addonId);
    void OnPreInstallEvent(const std::string& addonId);
    void OnPostInstallEvent(const std::string& addonId, bool update, bool modal);
    void OnPreUnInstallEvent(const std::string& addonId);
    void OnPostUnInstallEvent(const std::string& addonId);
    //@}

  private:
    /*!
     * Thread and message handling
     */
    //@{
    virtual void Process() override;

    void StateMachine(int signal, Actor::Message *msg);

    int m_extTimeout;
    CEvent m_inMsgEvent;
    CEvent m_outMsgEvent;
    CBinaryAddonDataProtocol m_control;
    //@}

    bool AddAddonBaseEntry(BINARY_ADDON_LIST_ENTRY& entry);

    CCriticalSection m_critSection;

    typedef std::map<std::string, BinaryAddonBasePtr> BinaryAddonMgrBaseList;
    BinaryAddonMgrBaseList m_installedAddons;
    BinaryAddonMgrBaseList m_enabledAddons;

    const std::string m_tempAddonBasePath;
    std::map<TYPE, IBinaryAddonManagerCallback*> m_managers;
  };

} /* namespace ADDON */
