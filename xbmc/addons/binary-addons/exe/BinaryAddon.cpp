/*
 *      Copyright (C) 2015 Team KODI
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
 *  along with KODI; see the file COPYING.  If not, see
 *  <http://www.gnu.org/licenses/>.
 *
 */

#include "BinaryAddon.h"
#include "tools.h"

#include "Application.h"
#include "CompileInfo.h"
#include "addons/IAddon.h"
#include "addons/binary-addons/AddonDll.h"
#include "utils/log.h"
#include "utils/StringUtils.h"

#include <netinet/in.h>

namespace ADDON
{

CBinaryAddon::CBinaryAddon(bool isLocal, int fd, unsigned int id, bool isFather, int rand)
  : CThread("Addon handler"),
    m_isLocal(isLocal),
    m_active(false),
    m_fd(fd),
    m_Id(id),
    m_loggedIn(false),
    m_isIndependent(false),
    m_isFather(isFather),
    m_randomConnectionNumber(rand),
    m_addon(nullptr),
//     m_addonCB(nullptr),
//     m_pHelpers(nullptr),
    m_sharedMem(nullptr)
{
  if (m_isFather)
  {
    m_socket.SetHandle(fd);
    StartNetStreamThread();
  }
}

CBinaryAddon::CBinaryAddon(const CBinaryAddon *right, int rand)
  : CThread("Addon handler (child)"),
    m_isLocal(right->m_isLocal),
    m_active(false),
    m_fd(right->m_fd),
    m_Id(right->m_Id),
    m_loggedIn(false),
    m_isIndependent(false),
    m_isFather(false),
    m_randomConnectionNumber(rand),
    m_sharedMem(right->m_sharedMem)
{
  m_addon               = new CAddonDll(*right->m_addon);
//   m_pHelpers            = new CAddonCallbacks(m_addon);
//   m_addonData.addonData = m_pHelpers;
//   m_addonCB = (V2::KodiAPI::CB_AddOnLib*)CAddonCallbacksAddonBase::CreateHelper(m_pHelpers, 2);
}

CBinaryAddon::~CBinaryAddon()
{
  if (m_isFather)
  {
    if (m_sharedMem)
      delete m_sharedMem;
    m_socket.close(); // force closing connection
    StopThread();
  }

  if (m_addon)
    delete m_addon;
//   if (m_pHelpers)
//   {
//     CAddonCallbacksAddonBase::DestroyHelper(m_pHelpers);
//     delete m_pHelpers;
//   }
}

bool CBinaryAddon::StartNetStreamThread()
{
  Create();
  return true;
}

bool CBinaryAddon::StartSharedMemoryThread(int rand)
{
#if (defined TARGET_WINDOWS)
  m_sharedMem = new CBinaryAddonSharedMemoryWindows(rand, this);
#elif (defined TARGET_POSIX)
  m_sharedMem = new CBinaryAddonSharedMemoryPosix(rand, this);
#endif
  return m_sharedMem->CreateSharedMemory();
}

void CBinaryAddon::Process(void)
{
  uint32_t channelID;
  uint32_t requestID;
  uint32_t opcode;
  uint32_t dataLength;
  uint8_t* data;

  while (!m_bStop && !g_application.m_bStop)
  {
    if (!m_socket.read((uint8_t*)&channelID, sizeof(uint32_t)))
      break;
    channelID = ntohl(channelID);

    if (channelID == 1)
    {
      if (!m_socket.read((uint8_t*)&requestID, sizeof(uint32_t), 10000))
        break;
      requestID = ntohl(requestID);

      if (!m_socket.read((uint8_t*)&opcode, sizeof(uint32_t), 10000))
        break;
      opcode = ntohl(opcode);

      if (!m_socket.read((uint8_t*)&dataLength, sizeof(uint32_t), 10000))
        break;
      dataLength = ntohl(dataLength);
      if (dataLength > 200000) // a random sanity limit
      {
        CLog::Log(LOGERROR, "dataLength > 200000!");
        break;
      }

      if (dataLength)
      {
        try
        {
          data = new uint8_t[dataLength];
        }
        catch (const std::bad_alloc &)
        {
          CLog::Log(LOGERROR, "Extra data buffer malloc error");
          break;
        }

        if (!m_socket.read(data, dataLength, 10000))
        {
          CLog::Log(LOGERROR, "Could not read data");
          free(data);
          break;
        }
      }
      else
      {
        data = NULL;
      }

      //fprintf(stderr, "Received chan=%u, ser=%u, op=%u, edl=%u\n", channelID, requestID, opcode, dataLength);

      if (!m_loggedIn && (opcode != KODICall_LoginVerify) && (opcode != KODICall_CreateSubThread))
      {
        CLog::Log(LOGERROR, "Add-ons must be logged in before sending commands! Aborting. (opcode = '%i')", opcode);
        if (data) free(data);
        break;
      }

      try
      {
        CRequestPacket req(requestID, opcode, data, dataLength);
        CResponsePacket resp;
        processRequest(req, resp);
        m_socket.write(resp.getPtr(), resp.getLen());
      }
      catch (const std::exception &e)
      {
        CLog::Log(LOGERROR, "%s", e.what());
        break;
      }
    }
    else
    {
      CLog::Log(LOGERROR, "Incoming stream channel number unknown %i", channelID);
      break;
    }
  }
}

//--- - --- - --- - --- - --- - --- - --- - --- - --- - --- - --- - --- - ---

bool CBinaryAddon::processRequest(CRequestPacket& req, CResponsePacket& resp)
{
  CSingleLock lock(m_msgLock);

  bool result = false;
  switch(req.getOpCode())
  {
  case KODICall_LoginVerify:
    result = process_Login(req, resp);
    break;

  case KODICall_Logout:
    result = process_Logout(req, resp);
    break;

  case KODICall_Ping:
    result = process_Ping(req, resp);
    break;

  case KODICall_Log:
    result = process_Log(req, resp);
    break;

  case KODICall_CreateSubThread:
    result = process_CreateSubThread(req, resp);
    break;

  case KODICall_DeleteSubThread:
    result = process_DeleteSubThread(req, resp);
    break;

  default:
    CLog::Log(LOGERROR, "Invalid add-on command opcode %i", req.getOpCode());
    break;
  }
  return result;
}

bool CBinaryAddon::process_Login(CRequestPacket& req, CResponsePacket& resp)
{
  if (req.getDataLength() <= 4)
    return false;

  char* str;
  bool useNet;
  req.pop(API_UINT32_T, &m_addonAPILevel);
  m_addonAPIVersion    = (char*)req.pop(API_STRING, &str);
  req.pop(API_UINT64_T, &m_addonAPIpid);
  m_addonId            = (char*)req.pop(API_STRING, &str);
  m_addonType          = (char*)req.pop(API_STRING, &str);
  m_addonVersion       = (char*)req.pop(API_STRING, &str);
  m_addonName          = (char*)req.pop(API_STRING, &str);

  if (!m_isSubThread)
  {
    CLog::Log(LOGINFO, "Binary AddOn: Welcome %s Add-on '%s' with API Level '%u' (Version: %s)",
                m_isIndependent ? "independent" : "child",
                m_addonName.c_str(),
                m_addonAPILevel,
                m_addonAPIVersion.c_str());
  }

  CAddonInfo addonInfo(m_addonName, CAddonInfo::TranslateType(m_addonType));

  addonInfo.m_name         = m_addonName;
  addonInfo.m_version = AddonVersion(m_addonVersion);
  addonInfo.m_minversion = AddonVersion(m_addonVersion);
  addonInfo.m_license      = (char*)req.pop(API_STRING, &str);
  addonInfo.m_summary      = (char*)req.pop(API_STRING, &str);
  addonInfo.m_description  = (char*)req.pop(API_STRING, &str);
  addonInfo.m_path         = (char*)req.pop(API_STRING, &str);
  addonInfo.m_libname      = (char*)req.pop(API_STRING, &str);
  addonInfo.m_author       = (char*)req.pop(API_STRING, &str);
  addonInfo.m_source       = (char*)req.pop(API_STRING, &str);
  addonInfo.m_icon         = (char*)req.pop(API_STRING, &str);
  addonInfo.m_disclaimer   = (char*)req.pop(API_STRING, &str);
  addonInfo.m_changelog    = (char*)req.pop(API_STRING, &str);
  addonInfo.m_art.insert(std::pair<std::string, std::string>("fanart", (char*)req.pop(API_STRING, &str)));
  req.pop(API_BOOL,  &m_isIndependent);
  req.pop(API_BOOL,  &useNet);
  req.pop(API_BOOL,  &m_isSubThread);

  m_addon               = new CAddonDll(addonInfo);
//   m_pHelpers            = new CAddonCallbacks(m_addon);
//   m_addonData.addonData = m_pHelpers;
//   m_addonCB             = (V2::KodiAPI::CB_AddOnLib*)CAddonCallbacksAddonBase::CreateHelper(m_pHelpers, 2);

  srand(clock());
  int     usedRand      = std::rand();
  int     sharedMemOK   = (!useNet && m_isLocal && StartSharedMemoryThread(usedRand)) ? 1 : 0;
  uint32_t netStreamOK  = API_SUCCESS;/*(m_addonAPILevel <= V2::KodiAPI::KODI_API_Level ? API_SUCCESS : API_ERR_REQUEST)*/
  if (netStreamOK != API_SUCCESS)
  {
    m_active = false;
    CLog::Log(LOGERROR, "Binary AddOn: Add-on '%s' have a not allowed API Version: %s, terminating client",
                m_addonName.c_str(),
                m_addonAPIVersion.c_str());
  }
  else
  {
    m_active = true;
    SetLoggedIn(true);
  }

  // Send the login reply
  resp.init(req.getRequestID());
  resp.push(API_UINT32_T, &netStreamOK);
  resp.push(API_INT,      &usedRand);
  int level = 2;
  resp.push(API_UINT32_T, &level);
  resp.push(API_STRING,    CCompileInfo::GetAppName());
  resp.push(API_STRING,    StringUtils::Format("%u.%u", CCompileInfo::GetMajor(), CCompileInfo::GetMinor()).c_str());
  resp.push(API_INT,  &sharedMemOK);
  int sharedMemSize = m_sharedMem ? m_sharedMem->m_sharedMemSize : 0;
  resp.push(API_INT,      &sharedMemSize);
  resp.finalise();

  return true;
}

bool CBinaryAddon::process_Logout(CRequestPacket& req, CResponsePacket& resp)
{
  ADDON_NET_SEND_RETURN(req.getRequestID(), API_SUCCESS);
  for (std::vector<CBinaryAddon*>::iterator itr = m_childThreads.begin(); itr != m_childThreads.end();)
  {
    delete (*itr);
    itr = m_childThreads.erase(itr);
  }

  m_active = false;

  if (m_isFather)
  {
    if (m_sharedMem)
      delete m_sharedMem;
    if (m_addon)
      delete m_addon;
//     if (m_pHelpers)
//     {
//       CAddonCallbacksAddonBase::DestroyHelper(m_pHelpers);
//       delete m_pHelpers;
//     }
  }

  m_sharedMem = nullptr;
  m_addon     = nullptr;
//   m_pHelpers  = nullptr;
//   m_addonCB   = nullptr;

  return true;
}

bool CBinaryAddon::process_Ping(CRequestPacket& req, CResponsePacket& resp)
{
  ADDON_NET_SEND_RETURN(req.getRequestID(), API_SUCCESS);
  return true;
}

bool CBinaryAddon::process_Log(CRequestPacket& req, CResponsePacket& resp)
{
  uint32_t logLevel;
  char* str;
  req.pop(API_UINT32_T, &logLevel);
  req.pop(API_STRING, &str);
  CAddonDll::addon_log_msg(m_addon, logLevel, str);
  ADDON_NET_SEND_RETURN(req.getRequestID(), API_SUCCESS);
  return true;
}

bool CBinaryAddon::process_CreateSubThread(CRequestPacket& req, CResponsePacket& resp)
{
  int rand;
  req.pop(API_INT, &rand);

  CBinaryAddon *childThread = new CBinaryAddon(this, rand);
  uint32_t ret = childThread->StartSharedMemoryThread(rand) ? API_SUCCESS : API_ERR_OP;
  if (ret == API_SUCCESS)
  {
    m_childThreads.push_back(childThread);
    childThread->m_active       = true;
    childThread->m_isSubThread  = true;
  }
  else
  {
    delete childThread;
  }
  resp.init(req.getRequestID());
  resp.push(API_UINT32_T, &ret);
  resp.finalise();

  return true;
}

bool CBinaryAddon::process_DeleteSubThread(CRequestPacket& req, CResponsePacket& resp)
{
  int rand;
  req.pop(API_INT, &rand);

  uint32_t ret = API_ERR_UNKNOWN;
  for (std::vector<CBinaryAddon*>::const_iterator itr = m_childThreads.begin(); itr != m_childThreads.end(); ++itr)
  {
    if ((*itr)->m_randomConnectionNumber == rand)
    {
      delete (*itr);
      m_childThreads.erase(itr);
      ret = API_SUCCESS;
      break;
    }
  }
  resp.init(req.getRequestID());
  resp.push(API_UINT32_T, &ret);
  resp.finalise();

  return true;
}

//--- - --- - --- - --- - --- - --- - --- - --- - --- - --- - --- - --- - ---

bool CBinaryAddon::addon_Ping()
{
  try
  {
    // if (!m_sharedMem->m_sharedMem_KodiToAddon)
    //   return false;
    //
    // m_sharedMem->m_sharedMem_KodiToAddon->message.messageId = KODICall_Ping;
    // m_sharedMem->m_sharedMem_KodiToAddon->message.retValue.bool_par = false;
    // m_sharedMem->Unlock_KodiToAddon_Addon();
    // m_sharedMem->Lock_KodiToAddon_Kodi();
    // bool ret = m_sharedMem->m_sharedMem_KodiToAddon->message.retValue.bool_par;
    // m_sharedMem->m_sharedMem_KodiToAddon->message.retValue.bool_par = false;
    // return ret;
  }
  catch (...)
  {
    CLog::Log(LOGERROR, "Binary AddOn::%s: Undefined exception", __FUNCTION__); // Show with normal output to prevent possible dead loops
  }
  return false;
}

} /* namespace ADDON */
