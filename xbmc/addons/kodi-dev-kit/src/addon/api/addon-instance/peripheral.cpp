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
#include "src/shared/Instances.h"

// Lib code
#include "core/addon_control.h"

/* Code below becomes on auto generation reused, hand edited parts should included here */
/*---AUTO_GEN_PARSE<HAND_EDITED_FIELD_1>---*/
/*---AUTO_GEN_PARSE<HAND_EDITED_FIELD_1_END>---*/

using namespace KODI::ADDONS::INTERFACE;
using namespace KODI_ADDON::INTERNAL;

namespace KODI_ADDON
{
namespace INTERNAL
{

/* Code below becomes on auto generation reused, hand edited parts should included here */
/*---AUTO_GEN_PARSE<HAND_EDITED_FIELD_2>---*/
/*---AUTO_GEN_PARSE<HAND_EDITED_FIELD_2_END>---*/

void CHdl_kodi_addoninstance_peripheral_h::InitDirect(
    directFuncToAddon_addoninstance_peripheral_h* ifcToAddon)
{
  ifcToAddon->thisClassHdl = this;
  ifcToAddon->kodi_addon_peripheral_create_v1 = kodi_addon_peripheral_create_v1;
  ifcToAddon->kodi_addon_peripheral_destroy_v1 = kodi_addon_peripheral_destroy_v1;
  ifcToAddon->kodi_addon_peripheral_get_capabilities_v1 = kodi_addon_peripheral_get_capabilities_v1;
  ifcToAddon->kodi_addon_peripheral_perform_device_scan_v1 =
      kodi_addon_peripheral_perform_device_scan_v1;
  ifcToAddon->kodi_addon_peripheral_free_scan_results_v1 =
      kodi_addon_peripheral_free_scan_results_v1;
  ifcToAddon->kodi_addon_peripheral_get_events_v1 = kodi_addon_peripheral_get_events_v1;
  ifcToAddon->kodi_addon_peripheral_free_events_v1 = kodi_addon_peripheral_free_events_v1;
  ifcToAddon->kodi_addon_peripheral_send_event_v1 = kodi_addon_peripheral_send_event_v1;
  ifcToAddon->kodi_addon_peripheral_get_joystick_info_v1 =
      kodi_addon_peripheral_get_joystick_info_v1;
  ifcToAddon->kodi_addon_peripheral_free_joystick_info_v1 =
      kodi_addon_peripheral_free_joystick_info_v1;
  ifcToAddon->kodi_addon_peripheral_get_features_v1 = kodi_addon_peripheral_get_features_v1;
  ifcToAddon->kodi_addon_peripheral_free_features_v1 = kodi_addon_peripheral_free_features_v1;
  ifcToAddon->kodi_addon_peripheral_map_features_v1 = kodi_addon_peripheral_map_features_v1;
  ifcToAddon->kodi_addon_peripheral_get_ignored_primitives_v1 =
      kodi_addon_peripheral_get_ignored_primitives_v1;
  ifcToAddon->kodi_addon_peripheral_free_primitives_v1 = kodi_addon_peripheral_free_primitives_v1;
  ifcToAddon->kodi_addon_peripheral_set_ignored_primitives_v1 =
      kodi_addon_peripheral_set_ignored_primitives_v1;
  ifcToAddon->kodi_addon_peripheral_save_button_map_v1 = kodi_addon_peripheral_save_button_map_v1;
  ifcToAddon->kodi_addon_peripheral_revert_button_map_v1 =
      kodi_addon_peripheral_revert_button_map_v1;
  ifcToAddon->kodi_addon_peripheral_reset_button_map_v1 = kodi_addon_peripheral_reset_button_map_v1;
  ifcToAddon->kodi_addon_peripheral_power_off_joystick_v1 =
      kodi_addon_peripheral_power_off_joystick_v1;
}

#ifndef KODI_INHIBIT_SHARED
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
      break;
  }
  return false;
}
#endif /* !KODI_INHIBIT_SHARED */

/* Code below becomes on auto generation reused, hand edited parts should included here */
/*---AUTO_GEN_PARSE<HAND_EDITED_FIELD_3>---*/
/*---AUTO_GEN_PARSE<HAND_EDITED_FIELD_3_END>---*/


KODI_ADDON_PERIPHERAL_HDL CHdl_kodi_addoninstance_peripheral_h::kodi_addon_peripheral_create_v1(
    void* thisClassHdl, KODI_OWN_HDL kodi_hdl) // Added with API 1
{
  auto thisClass = reinterpret_cast<CHdl_kodi_addoninstance_peripheral_h*>(thisClassHdl);
  if (thisClass == nullptr)
    return nullptr;

  UnionAddonFunctions* union_data = reinterpret_cast<UnionAddonFunctions*>(kodi_hdl);
  KODI_ADDON_PERIPHERAL_HDL auto_gen_ret = nullptr;
  if (union_data->types.kodi_addon_peripheral.v1.create)
  {
    auto_gen_ret = union_data->types.kodi_addon_peripheral.v1.create(kodi_hdl);
  }
  return auto_gen_ret;
}

void CHdl_kodi_addoninstance_peripheral_h::kodi_addon_peripheral_destroy_v1(
    void* thisClassHdl, KODI_ADDON_PERIPHERAL_HDL hdl) // Added with API 1
{
  auto thisClass = reinterpret_cast<CHdl_kodi_addoninstance_peripheral_h*>(thisClassHdl);
  if (thisClass == nullptr)
    return;

  UnionAddonFunctions* union_data = reinterpret_cast<UnionAddonFunctions*>(hdl);
  if (union_data->types.kodi_addon_peripheral.v1.destroy)
  {
    union_data->types.kodi_addon_peripheral.v1.destroy(union_data->hdl);
  }
}

void CHdl_kodi_addoninstance_peripheral_h::kodi_addon_peripheral_get_capabilities_v1(
    void* thisClassHdl,
    KODI_ADDON_PERIPHERAL_HDL hdl,
    struct PERIPHERAL_CAPABILITIES* capabilities) // Added with API 1
{
  auto thisClass = reinterpret_cast<CHdl_kodi_addoninstance_peripheral_h*>(thisClassHdl);
  if (thisClass == nullptr)
    return;

  UnionAddonFunctions* union_data = reinterpret_cast<UnionAddonFunctions*>(hdl);
  if (union_data->types.kodi_addon_peripheral.v1.get_capabilities)
  {
    union_data->types.kodi_addon_peripheral.v1.get_capabilities(union_data->hdl, capabilities);
  }
}

enum PERIPHERAL_ERROR CHdl_kodi_addoninstance_peripheral_h::
    kodi_addon_peripheral_perform_device_scan_v1(void* thisClassHdl,
                                                 KODI_ADDON_PERIPHERAL_HDL hdl,
                                                 struct PERIPHERAL_INFO** scan_results,
                                                 size_t* peripheral_count) // Added with API 1
{
  auto thisClass = reinterpret_cast<CHdl_kodi_addoninstance_peripheral_h*>(thisClassHdl);
  if (thisClass == nullptr)
    return PERIPHERAL_NO_ERROR;

  UnionAddonFunctions* union_data = reinterpret_cast<UnionAddonFunctions*>(hdl);
  enum PERIPHERAL_ERROR auto_gen_ret = PERIPHERAL_NO_ERROR;
  if (union_data->types.kodi_addon_peripheral.v1.perform_device_scan)
  {
    auto_gen_ret = union_data->types.kodi_addon_peripheral.v1.perform_device_scan(
        union_data->hdl, scan_results, peripheral_count);
  }
  return auto_gen_ret;
}

void CHdl_kodi_addoninstance_peripheral_h::kodi_addon_peripheral_free_scan_results_v1(
    void* thisClassHdl,
    KODI_ADDON_PERIPHERAL_HDL hdl,
    struct PERIPHERAL_INFO* scan_results,
    size_t peripheral_count) // Added with API 1
{
  auto thisClass = reinterpret_cast<CHdl_kodi_addoninstance_peripheral_h*>(thisClassHdl);
  if (thisClass == nullptr)
    return;

  UnionAddonFunctions* union_data = reinterpret_cast<UnionAddonFunctions*>(hdl);
  if (union_data->types.kodi_addon_peripheral.v1.free_scan_results)
  {
    union_data->types.kodi_addon_peripheral.v1.free_scan_results(union_data->hdl, scan_results,
                                                                 peripheral_count);
  }
}

enum PERIPHERAL_ERROR CHdl_kodi_addoninstance_peripheral_h::kodi_addon_peripheral_get_events_v1(
    void* thisClassHdl,
    KODI_ADDON_PERIPHERAL_HDL hdl,
    struct PERIPHERAL_EVENT** events,
    size_t* event_count) // Added with API 1
{
  auto thisClass = reinterpret_cast<CHdl_kodi_addoninstance_peripheral_h*>(thisClassHdl);
  if (thisClass == nullptr)
    return PERIPHERAL_NO_ERROR;

  UnionAddonFunctions* union_data = reinterpret_cast<UnionAddonFunctions*>(hdl);
  enum PERIPHERAL_ERROR auto_gen_ret = PERIPHERAL_NO_ERROR;
  if (union_data->types.kodi_addon_peripheral.v1.get_events)
  {
    auto_gen_ret =
        union_data->types.kodi_addon_peripheral.v1.get_events(union_data->hdl, events, event_count);
  }
  return auto_gen_ret;
}

void CHdl_kodi_addoninstance_peripheral_h::kodi_addon_peripheral_free_events_v1(
    void* thisClassHdl,
    KODI_ADDON_PERIPHERAL_HDL hdl,
    struct PERIPHERAL_EVENT* events,
    size_t event_count) // Added with API 1
{
  auto thisClass = reinterpret_cast<CHdl_kodi_addoninstance_peripheral_h*>(thisClassHdl);
  if (thisClass == nullptr)
    return;

  UnionAddonFunctions* union_data = reinterpret_cast<UnionAddonFunctions*>(hdl);
  if (union_data->types.kodi_addon_peripheral.v1.free_events)
  {
    union_data->types.kodi_addon_peripheral.v1.free_events(union_data->hdl, events, event_count);
  }
}

bool CHdl_kodi_addoninstance_peripheral_h::kodi_addon_peripheral_send_event_v1(
    void* thisClassHdl,
    KODI_ADDON_PERIPHERAL_HDL hdl,
    const struct PERIPHERAL_EVENT* event) // Added with API 1
{
  auto thisClass = reinterpret_cast<CHdl_kodi_addoninstance_peripheral_h*>(thisClassHdl);
  if (thisClass == nullptr)
    return false;

  UnionAddonFunctions* union_data = reinterpret_cast<UnionAddonFunctions*>(hdl);
  bool auto_gen_ret = false;
  if (union_data->types.kodi_addon_peripheral.v1.send_event)
  {
    auto_gen_ret = union_data->types.kodi_addon_peripheral.v1.send_event(union_data->hdl, event);
  }
  return auto_gen_ret;
}

enum PERIPHERAL_ERROR CHdl_kodi_addoninstance_peripheral_h::
    kodi_addon_peripheral_get_joystick_info_v1(void* thisClassHdl,
                                               KODI_ADDON_PERIPHERAL_HDL hdl,
                                               unsigned int index,
                                               struct JOYSTICK_INFO* info) // Added with API 1
{
  auto thisClass = reinterpret_cast<CHdl_kodi_addoninstance_peripheral_h*>(thisClassHdl);
  if (thisClass == nullptr)
    return PERIPHERAL_NO_ERROR;

  UnionAddonFunctions* union_data = reinterpret_cast<UnionAddonFunctions*>(hdl);
  enum PERIPHERAL_ERROR auto_gen_ret = PERIPHERAL_NO_ERROR;
  if (union_data->types.kodi_addon_peripheral.v1.get_joystick_info)
  {
    auto_gen_ret =
        union_data->types.kodi_addon_peripheral.v1.get_joystick_info(union_data->hdl, index, info);
  }
  return auto_gen_ret;
}

void CHdl_kodi_addoninstance_peripheral_h::kodi_addon_peripheral_free_joystick_info_v1(
    void* thisClassHdl,
    KODI_ADDON_PERIPHERAL_HDL hdl,
    struct JOYSTICK_INFO* info) // Added with API 1
{
  auto thisClass = reinterpret_cast<CHdl_kodi_addoninstance_peripheral_h*>(thisClassHdl);
  if (thisClass == nullptr)
    return;

  UnionAddonFunctions* union_data = reinterpret_cast<UnionAddonFunctions*>(hdl);
  if (union_data->types.kodi_addon_peripheral.v1.free_joystick_info)
  {
    union_data->types.kodi_addon_peripheral.v1.free_joystick_info(union_data->hdl, info);
  }
}

enum PERIPHERAL_ERROR CHdl_kodi_addoninstance_peripheral_h::kodi_addon_peripheral_get_features_v1(
    void* thisClassHdl,
    KODI_ADDON_PERIPHERAL_HDL hdl,
    const struct JOYSTICK_INFO* joystick,
    const char* controller_id,
    struct JOYSTICK_FEATURE** features,
    size_t* feature_count) // Added with API 1
{
  auto thisClass = reinterpret_cast<CHdl_kodi_addoninstance_peripheral_h*>(thisClassHdl);
  if (thisClass == nullptr)
    return PERIPHERAL_NO_ERROR;

  UnionAddonFunctions* union_data = reinterpret_cast<UnionAddonFunctions*>(hdl);
  enum PERIPHERAL_ERROR auto_gen_ret = PERIPHERAL_NO_ERROR;
  if (union_data->types.kodi_addon_peripheral.v1.get_features)
  {
    auto_gen_ret = union_data->types.kodi_addon_peripheral.v1.get_features(
        union_data->hdl, joystick, controller_id, features, feature_count);
  }
  return auto_gen_ret;
}

void CHdl_kodi_addoninstance_peripheral_h::kodi_addon_peripheral_free_features_v1(
    void* thisClassHdl,
    KODI_ADDON_PERIPHERAL_HDL hdl,
    struct JOYSTICK_FEATURE* features,
    size_t feature_count) // Added with API 1
{
  auto thisClass = reinterpret_cast<CHdl_kodi_addoninstance_peripheral_h*>(thisClassHdl);
  if (thisClass == nullptr)
    return;

  UnionAddonFunctions* union_data = reinterpret_cast<UnionAddonFunctions*>(hdl);
  if (union_data->types.kodi_addon_peripheral.v1.free_features)
  {
    union_data->types.kodi_addon_peripheral.v1.free_features(union_data->hdl, features,
                                                             feature_count);
  }
}

enum PERIPHERAL_ERROR CHdl_kodi_addoninstance_peripheral_h::kodi_addon_peripheral_map_features_v1(
    void* thisClassHdl,
    KODI_ADDON_PERIPHERAL_HDL hdl,
    const struct JOYSTICK_INFO* joystick,
    const char* controller_id,
    const struct JOYSTICK_FEATURE* features,
    size_t feature_count) // Added with API 1
{
  auto thisClass = reinterpret_cast<CHdl_kodi_addoninstance_peripheral_h*>(thisClassHdl);
  if (thisClass == nullptr)
    return PERIPHERAL_NO_ERROR;

  UnionAddonFunctions* union_data = reinterpret_cast<UnionAddonFunctions*>(hdl);
  enum PERIPHERAL_ERROR auto_gen_ret = PERIPHERAL_NO_ERROR;
  if (union_data->types.kodi_addon_peripheral.v1.map_features)
  {
    auto_gen_ret = union_data->types.kodi_addon_peripheral.v1.map_features(
        union_data->hdl, joystick, controller_id, features, feature_count);
  }
  return auto_gen_ret;
}

enum PERIPHERAL_ERROR CHdl_kodi_addoninstance_peripheral_h::
    kodi_addon_peripheral_get_ignored_primitives_v1(void* thisClassHdl,
                                                    KODI_ADDON_PERIPHERAL_HDL hdl,
                                                    const struct JOYSTICK_INFO* joystick,
                                                    struct JOYSTICK_DRIVER_PRIMITIVE** primitives,
                                                    size_t* primitive_count) // Added with API 1
{
  auto thisClass = reinterpret_cast<CHdl_kodi_addoninstance_peripheral_h*>(thisClassHdl);
  if (thisClass == nullptr)
    return PERIPHERAL_NO_ERROR;

  UnionAddonFunctions* union_data = reinterpret_cast<UnionAddonFunctions*>(hdl);
  enum PERIPHERAL_ERROR auto_gen_ret = PERIPHERAL_NO_ERROR;
  if (union_data->types.kodi_addon_peripheral.v1.get_ignored_primitives)
  {
    auto_gen_ret = union_data->types.kodi_addon_peripheral.v1.get_ignored_primitives(
        union_data->hdl, joystick, primitives, primitive_count);
  }
  return auto_gen_ret;
}

void CHdl_kodi_addoninstance_peripheral_h::kodi_addon_peripheral_free_primitives_v1(
    void* thisClassHdl,
    KODI_ADDON_PERIPHERAL_HDL hdl,
    struct JOYSTICK_DRIVER_PRIMITIVE* primitives,
    size_t primitive_count) // Added with API 1
{
  auto thisClass = reinterpret_cast<CHdl_kodi_addoninstance_peripheral_h*>(thisClassHdl);
  if (thisClass == nullptr)
    return;

  UnionAddonFunctions* union_data = reinterpret_cast<UnionAddonFunctions*>(hdl);
  if (union_data->types.kodi_addon_peripheral.v1.free_primitives)
  {
    union_data->types.kodi_addon_peripheral.v1.free_primitives(union_data->hdl, primitives,
                                                               primitive_count);
  }
}

enum PERIPHERAL_ERROR CHdl_kodi_addoninstance_peripheral_h::
    kodi_addon_peripheral_set_ignored_primitives_v1(
        void* thisClassHdl,
        KODI_ADDON_PERIPHERAL_HDL hdl,
        const struct JOYSTICK_INFO* joystick,
        const struct JOYSTICK_DRIVER_PRIMITIVE* primitives,
        size_t primitive_count) // Added with API 1
{
  auto thisClass = reinterpret_cast<CHdl_kodi_addoninstance_peripheral_h*>(thisClassHdl);
  if (thisClass == nullptr)
    return PERIPHERAL_NO_ERROR;

  UnionAddonFunctions* union_data = reinterpret_cast<UnionAddonFunctions*>(hdl);
  enum PERIPHERAL_ERROR auto_gen_ret = PERIPHERAL_NO_ERROR;
  if (union_data->types.kodi_addon_peripheral.v1.set_ignored_primitives)
  {
    auto_gen_ret = union_data->types.kodi_addon_peripheral.v1.set_ignored_primitives(
        union_data->hdl, joystick, primitives, primitive_count);
  }
  return auto_gen_ret;
}

void CHdl_kodi_addoninstance_peripheral_h::kodi_addon_peripheral_save_button_map_v1(
    void* thisClassHdl,
    KODI_ADDON_PERIPHERAL_HDL hdl,
    const struct JOYSTICK_INFO* joystick) // Added with API 1
{
  auto thisClass = reinterpret_cast<CHdl_kodi_addoninstance_peripheral_h*>(thisClassHdl);
  if (thisClass == nullptr)
    return;

  UnionAddonFunctions* union_data = reinterpret_cast<UnionAddonFunctions*>(hdl);
  if (union_data->types.kodi_addon_peripheral.v1.save_button_map)
  {
    union_data->types.kodi_addon_peripheral.v1.save_button_map(union_data->hdl, joystick);
  }
}

void CHdl_kodi_addoninstance_peripheral_h::kodi_addon_peripheral_revert_button_map_v1(
    void* thisClassHdl,
    KODI_ADDON_PERIPHERAL_HDL hdl,
    const struct JOYSTICK_INFO* joystick) // Added with API 1
{
  auto thisClass = reinterpret_cast<CHdl_kodi_addoninstance_peripheral_h*>(thisClassHdl);
  if (thisClass == nullptr)
    return;

  UnionAddonFunctions* union_data = reinterpret_cast<UnionAddonFunctions*>(hdl);
  if (union_data->types.kodi_addon_peripheral.v1.revert_button_map)
  {
    union_data->types.kodi_addon_peripheral.v1.revert_button_map(union_data->hdl, joystick);
  }
}

void CHdl_kodi_addoninstance_peripheral_h::kodi_addon_peripheral_reset_button_map_v1(
    void* thisClassHdl,
    KODI_ADDON_PERIPHERAL_HDL hdl,
    const struct JOYSTICK_INFO* joystick,
    const char* controller_id) // Added with API 1
{
  auto thisClass = reinterpret_cast<CHdl_kodi_addoninstance_peripheral_h*>(thisClassHdl);
  if (thisClass == nullptr)
    return;

  UnionAddonFunctions* union_data = reinterpret_cast<UnionAddonFunctions*>(hdl);
  if (union_data->types.kodi_addon_peripheral.v1.reset_button_map)
  {
    union_data->types.kodi_addon_peripheral.v1.reset_button_map(union_data->hdl, joystick,
                                                                controller_id);
  }
}

void CHdl_kodi_addoninstance_peripheral_h::kodi_addon_peripheral_power_off_joystick_v1(
    void* thisClassHdl, KODI_ADDON_PERIPHERAL_HDL hdl, unsigned int index) // Added with API 1
{
  auto thisClass = reinterpret_cast<CHdl_kodi_addoninstance_peripheral_h*>(thisClassHdl);
  if (thisClass == nullptr)
    return;

  UnionAddonFunctions* union_data = reinterpret_cast<UnionAddonFunctions*>(hdl);
  if (union_data->types.kodi_addon_peripheral.v1.power_off_joystick)
  {
    union_data->types.kodi_addon_peripheral.v1.power_off_joystick(union_data->hdl, index);
  }
}

} /* namespace INTERNAL */
} /* namespace KODI_ADDON */

ATTR_DLL_EXPORT void kodi_addon_peripheral_trigger_scan(KODI_OWN_HDL hdl)
{
  // Original API call: ATTR_DLL_EXPORT void kodi_addon_peripheral_trigger_scan(KODI_OWN_HDL hdl) __INTRODUCED_IN_KODI(1);
  if (hdl == nullptr)
    return;

  const auto& auto_gen_group = AddonIfc::g_ifc->direct->to_kodi.addoninstance_peripheral_h;
  auto_gen_group.kodi_addon_peripheral_trigger_scan_v1(auto_gen_group.thisClassHdl, hdl);
}

ATTR_DLL_EXPORT void kodi_addon_peripheral_refresh_button_maps(KODI_OWN_HDL hdl,
                                                               const char* device_name,
                                                               const char* controller_id)
{
  // Original API call: ATTR_DLL_EXPORT void kodi_addon_peripheral_refresh_button_maps(KODI_OWN_HDL hdl, const char* device_name, const char* controller_id) __INTRODUCED_IN_KODI(1);
  if (hdl == nullptr || device_name == nullptr || controller_id == nullptr)
    return;

  const auto& auto_gen_group = AddonIfc::g_ifc->direct->to_kodi.addoninstance_peripheral_h;
  auto_gen_group.kodi_addon_peripheral_refresh_button_maps_v1(auto_gen_group.thisClassHdl, hdl,
                                                              device_name, controller_id);
}

ATTR_DLL_EXPORT unsigned int kodi_addon_peripheral_feature_count(KODI_OWN_HDL hdl,
                                                                 const char* controller_id,
                                                                 enum JOYSTICK_FEATURE_TYPE type)
{
  // Original API call: ATTR_DLL_EXPORT unsigned int kodi_addon_peripheral_feature_count(KODI_OWN_HDL hdl, const char* controller_id, enum JOYSTICK_FEATURE_TYPE type) __INTRODUCED_IN_KODI(1);
  if (hdl == nullptr || controller_id == nullptr)
    return 0;

  const auto& auto_gen_group = AddonIfc::g_ifc->direct->to_kodi.addoninstance_peripheral_h;
  return auto_gen_group.kodi_addon_peripheral_feature_count_v1(auto_gen_group.thisClassHdl, hdl,
                                                               controller_id, type);
}

ATTR_DLL_EXPORT enum JOYSTICK_FEATURE_TYPE kodi_addon_peripheral_feature_type(
    KODI_OWN_HDL hdl, const char* controller_id, const char* feature_name)
{
  // Original API call: ATTR_DLL_EXPORT enum JOYSTICK_FEATURE_TYPE kodi_addon_peripheral_feature_type( KODI_OWN_HDL hdl, const char* controller_id, const char* feature_name) __INTRODUCED_IN_KODI(1);
  if (hdl == nullptr || controller_id == nullptr || feature_name == nullptr)
    return JOYSTICK_FEATURE_TYPE_UNKNOWN;

  const auto& auto_gen_group = AddonIfc::g_ifc->direct->to_kodi.addoninstance_peripheral_h;
  return auto_gen_group.kodi_addon_peripheral_feature_type_v1(auto_gen_group.thisClassHdl, hdl,
                                                              controller_id, feature_name);
}

/* Code below becomes on auto generation reused, hand edited parts should included here */
/*---AUTO_GEN_PARSE<HAND_EDITED_FIELD_4>---*/
/*---AUTO_GEN_PARSE<HAND_EDITED_FIELD_4_END>---*/
