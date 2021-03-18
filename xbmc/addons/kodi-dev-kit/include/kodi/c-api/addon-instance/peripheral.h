/*
 *  Copyright (C) 2005-2018 Team Kodi
 *  This file is part of Kodi - https://kodi.tv
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

/*---AUTO_GEN_PARSE<OVERRIDE;USE_DIRECT_API_ONLY>---*/

#ifndef C_API_ADDONINSTANCE_PERIPHERAL_H
#define C_API_ADDONINSTANCE_PERIPHERAL_H

#include "../addon_base.h"

#include <stdint.h>

/* indicates a joystick has no preference for port number */
#define NO_PORT_REQUESTED (-1)

/* joystick's driver button/hat/axis index is unknown */
#define DRIVER_INDEX_UNKNOWN (-1)

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

  typedef void* KODI_ADDON_PERIPHERAL_HDL;

  typedef enum PERIPHERAL_ERROR
  {
    PERIPHERAL_NO_ERROR = 0,
    PERIPHERAL_ERROR_UNKNOWN = -1,
    PERIPHERAL_ERROR_FAILED = -2,
    PERIPHERAL_ERROR_INVALID_PARAMETERS = -3,
    PERIPHERAL_ERROR_NOT_IMPLEMENTED = -4,
    PERIPHERAL_ERROR_NOT_CONNECTED = -5,
    PERIPHERAL_ERROR_CONNECTION_FAILED = -6,
  } PERIPHERAL_ERROR;

  typedef enum PERIPHERAL_TYPE
  {
    PERIPHERAL_TYPE_UNKNOWN,
    PERIPHERAL_TYPE_JOYSTICK,
    PERIPHERAL_TYPE_KEYBOARD,
  } PERIPHERAL_TYPE;

  struct PERIPHERAL_INFO
  {
    enum PERIPHERAL_TYPE type; /*!< type of peripheral */
    char* name; /*!< name of peripheral */
    uint16_t vendor_id; /*!< vendor ID of peripheral, 0x0000 if unknown */
    uint16_t product_id; /*!< product ID of peripheral, 0x0000 if unknown */
    unsigned int index; /*!< the order in which the add-on identified this peripheral */
  };

  struct PERIPHERAL_CAPABILITIES
  {
    bool provides_joysticks; /*!< true if the add-on provides joysticks */
    bool provides_joystick_rumble;
    bool provides_joystick_power_off;
    bool provides_buttonmaps; /*!< true if the add-on provides button maps */
  };

  typedef enum PERIPHERAL_EVENT_TYPE
  {
    PERIPHERAL_EVENT_TYPE_NONE,
    PERIPHERAL_EVENT_TYPE_DRIVER_BUTTON,
    PERIPHERAL_EVENT_TYPE_DRIVER_HAT,
    PERIPHERAL_EVENT_TYPE_DRIVER_AXIS,
    PERIPHERAL_EVENT_TYPE_SET_MOTOR,
  } PERIPHERAL_EVENT_TYPE;

  typedef enum JOYSTICK_STATE_BUTTON
  {
    JOYSTICK_STATE_BUTTON_UNPRESSED = 0x0,
    JOYSTICK_STATE_BUTTON_PRESSED = 0x1,
  } JOYSTICK_STATE_BUTTON;

  typedef enum JOYSTICK_STATE_HAT
  {
    JOYSTICK_STATE_HAT_UNPRESSED = 0x0,
    JOYSTICK_STATE_HAT_LEFT = 0x1,
    JOYSTICK_STATE_HAT_RIGHT = 0x2,
    JOYSTICK_STATE_HAT_UP = 0x4,
    JOYSTICK_STATE_HAT_DOWN = 0x8,
    JOYSTICK_STATE_HAT_LEFT_UP = JOYSTICK_STATE_HAT_LEFT | JOYSTICK_STATE_HAT_UP,
    JOYSTICK_STATE_HAT_LEFT_DOWN = JOYSTICK_STATE_HAT_LEFT | JOYSTICK_STATE_HAT_DOWN,
    JOYSTICK_STATE_HAT_RIGHT_UP = JOYSTICK_STATE_HAT_RIGHT | JOYSTICK_STATE_HAT_UP,
    JOYSTICK_STATE_HAT_RIGHT_DOWN = JOYSTICK_STATE_HAT_RIGHT | JOYSTICK_STATE_HAT_DOWN,
  } JOYSTICK_STATE_HAT;

  typedef float JOYSTICK_STATE_AXIS;
  typedef float JOYSTICK_STATE_MOTOR;

  struct PERIPHERAL_EVENT
  {
    unsigned int peripheral_index;
    enum PERIPHERAL_EVENT_TYPE type;
    unsigned int driver_index;

    enum JOYSTICK_STATE_BUTTON driver_button_state;
    enum JOYSTICK_STATE_HAT driver_hat_state;
    JOYSTICK_STATE_AXIS driver_axis_state;
    JOYSTICK_STATE_MOTOR motor_state;
  };

  struct JOYSTICK_INFO
  {
    struct PERIPHERAL_INFO peripheral; /*!< @brief peripheral info for this joystick */
    char* provider; /*!< @brief name of the driver or interface providing the joystick */
    int requested_port; /*!< @brief requested port number (such as for 360 controllers), or NO_PORT_REQUESTED */
    unsigned int button_count; /*!< @brief number of buttons reported by the driver */
    unsigned int hat_count; /*!< @brief number of hats reported by the driver */
    unsigned int axis_count; /*!< @brief number of axes reported by the driver */
    unsigned int motor_count; /*!< @brief number of motors reported by the driver */
    bool supports_poweroff; /*!< @brief whether the joystick supports being powered off */
  };

  typedef enum JOYSTICK_DRIVER_PRIMITIVE_TYPE
  {
    JOYSTICK_DRIVER_PRIMITIVE_TYPE_UNKNOWN,
    JOYSTICK_DRIVER_PRIMITIVE_TYPE_BUTTON,
    JOYSTICK_DRIVER_PRIMITIVE_TYPE_HAT_DIRECTION,
    JOYSTICK_DRIVER_PRIMITIVE_TYPE_SEMIAXIS,
    JOYSTICK_DRIVER_PRIMITIVE_TYPE_MOTOR,
    JOYSTICK_DRIVER_PRIMITIVE_TYPE_KEY,
    JOYSTICK_DRIVER_PRIMITIVE_TYPE_MOUSE_BUTTON,
    JOYSTICK_DRIVER_PRIMITIVE_TYPE_RELPOINTER_DIRECTION,
  } JOYSTICK_DRIVER_PRIMITIVE_TYPE;

  struct JOYSTICK_DRIVER_BUTTON
  {
    int index;
  };

  typedef enum JOYSTICK_DRIVER_HAT_DIRECTION
  {
    JOYSTICK_DRIVER_HAT_UNKNOWN,
    JOYSTICK_DRIVER_HAT_LEFT,
    JOYSTICK_DRIVER_HAT_RIGHT,
    JOYSTICK_DRIVER_HAT_UP,
    JOYSTICK_DRIVER_HAT_DOWN,
  } JOYSTICK_DRIVER_HAT_DIRECTION;

  struct JOYSTICK_DRIVER_HAT
  {
    int index;
    enum JOYSTICK_DRIVER_HAT_DIRECTION direction;
  };

  typedef enum JOYSTICK_DRIVER_SEMIAXIS_DIRECTION
  {
    JOYSTICK_DRIVER_SEMIAXIS_NEGATIVE = -1,
    JOYSTICK_DRIVER_SEMIAXIS_UNKNOWN = 0,
    JOYSTICK_DRIVER_SEMIAXIS_POSITIVE = 1,
  } JOYSTICK_DRIVER_SEMIAXIS_DIRECTION;

  struct JOYSTICK_DRIVER_SEMIAXIS
  {
    int index;
    int center;
    enum JOYSTICK_DRIVER_SEMIAXIS_DIRECTION direction;
    unsigned int range;
  };

  struct JOYSTICK_DRIVER_MOTOR
  {
    int index;
  };

  struct JOYSTICK_DRIVER_KEY
  {
    char keycode[16];
  };

  typedef enum JOYSTICK_DRIVER_MOUSE_INDEX
  {
    JOYSTICK_DRIVER_MOUSE_INDEX_UNKNOWN,
    JOYSTICK_DRIVER_MOUSE_INDEX_LEFT,
    JOYSTICK_DRIVER_MOUSE_INDEX_RIGHT,
    JOYSTICK_DRIVER_MOUSE_INDEX_MIDDLE,
    JOYSTICK_DRIVER_MOUSE_INDEX_BUTTON4,
    JOYSTICK_DRIVER_MOUSE_INDEX_BUTTON5,
    JOYSTICK_DRIVER_MOUSE_INDEX_WHEEL_UP,
    JOYSTICK_DRIVER_MOUSE_INDEX_WHEEL_DOWN,
    JOYSTICK_DRIVER_MOUSE_INDEX_HORIZ_WHEEL_LEFT,
    JOYSTICK_DRIVER_MOUSE_INDEX_HORIZ_WHEEL_RIGHT,
  } JOYSTICK_DRIVER_MOUSE_INDEX;

  struct JOYSTICK_DRIVER_MOUSE_BUTTON
  {
    enum JOYSTICK_DRIVER_MOUSE_INDEX button;
  };

  typedef enum JOYSTICK_DRIVER_RELPOINTER_DIRECTION
  {
    JOYSTICK_DRIVER_RELPOINTER_UNKNOWN,
    JOYSTICK_DRIVER_RELPOINTER_LEFT,
    JOYSTICK_DRIVER_RELPOINTER_RIGHT,
    JOYSTICK_DRIVER_RELPOINTER_UP,
    JOYSTICK_DRIVER_RELPOINTER_DOWN,
  } JOYSTICK_DRIVER_RELPOINTER_DIRECTION;

  struct JOYSTICK_DRIVER_RELPOINTER
  {
    enum JOYSTICK_DRIVER_RELPOINTER_DIRECTION direction;
  };

  struct JOYSTICK_DRIVER_PRIMITIVE
  {
    enum JOYSTICK_DRIVER_PRIMITIVE_TYPE type;
    union
    {
      struct JOYSTICK_DRIVER_BUTTON button;
      struct JOYSTICK_DRIVER_HAT hat;
      struct JOYSTICK_DRIVER_SEMIAXIS semiaxis;
      struct JOYSTICK_DRIVER_MOTOR motor;
      struct JOYSTICK_DRIVER_KEY key;
      struct JOYSTICK_DRIVER_MOUSE_BUTTON mouse;
      struct JOYSTICK_DRIVER_RELPOINTER relpointer;
    };
  };

  typedef enum JOYSTICK_FEATURE_TYPE
  {
    JOYSTICK_FEATURE_TYPE_UNKNOWN,
    JOYSTICK_FEATURE_TYPE_SCALAR,
    JOYSTICK_FEATURE_TYPE_ANALOG_STICK,
    JOYSTICK_FEATURE_TYPE_ACCELEROMETER,
    JOYSTICK_FEATURE_TYPE_MOTOR,
    JOYSTICK_FEATURE_TYPE_RELPOINTER,
    JOYSTICK_FEATURE_TYPE_ABSPOINTER,
    JOYSTICK_FEATURE_TYPE_WHEEL,
    JOYSTICK_FEATURE_TYPE_THROTTLE,
    JOYSTICK_FEATURE_TYPE_KEY,
  } JOYSTICK_FEATURE_TYPE;

  typedef enum JOYSTICK_FEATURE_PRIMITIVE
  {
    JOYSTICK_SCALAR_PRIMITIVE = 0,

    JOYSTICK_ANALOG_STICK_UP = 0,
    JOYSTICK_ANALOG_STICK_DOWN = 1,
    JOYSTICK_ANALOG_STICK_RIGHT = 2,
    JOYSTICK_ANALOG_STICK_LEFT = 3,

    JOYSTICK_ACCELEROMETER_POSITIVE_X = 0,
    JOYSTICK_ACCELEROMETER_POSITIVE_Y = 1,
    JOYSTICK_ACCELEROMETER_POSITIVE_Z = 2,

    JOYSTICK_MOTOR_PRIMITIVE = 0,

    JOYSTICK_WHEEL_LEFT = 0,
    JOYSTICK_WHEEL_RIGHT = 1,

    JOYSTICK_THROTTLE_UP = 0,
    JOYSTICK_THROTTLE_DOWN = 1,

    JOYSTICK_KEY_PRIMITIVE = 0,

    JOYSTICK_MOUSE_BUTTON = 0,

    JOYSTICK_RELPOINTER_UP = 0,
    JOYSTICK_RELPOINTER_DOWN = 1,
    JOYSTICK_RELPOINTER_RIGHT = 2,
    JOYSTICK_RELPOINTER_LEFT = 3,

    JOYSTICK_PRIMITIVE_MAX = 4,
  } JOYSTICK_FEATURE_PRIMITIVE;

  struct JOYSTICK_FEATURE
  {
    char* name;
    enum JOYSTICK_FEATURE_TYPE type;
    struct JOYSTICK_DRIVER_PRIMITIVE primitives[JOYSTICK_PRIMITIVE_MAX];
  };

  //--==----==----==----==----==----==----==----==----==----==----==----==----==
  // General interface functions
  typedef KODI_ADDON_PERIPHERAL_HDL(ATTR_APIENTRYP PFN_KODI_ADDON_PERIPHERAL_CREATE_V1)(
      KODI_OWN_HDL kodi_hdl);
  typedef void(ATTR_APIENTRYP PFN_KODI_ADDON_PERIPHERAL_DESTROY_V1)(KODI_ADDON_PERIPHERAL_HDL hdl);

  typedef void(ATTR_APIENTRYP PFN_KODI_ADDON_PERIPHERAL_GET_CAPABILITIES_V1)(
      KODI_ADDON_PERIPHERAL_HDL hdl, struct PERIPHERAL_CAPABILITIES* capabilities);
  typedef enum PERIPHERAL_ERROR(ATTR_APIENTRYP PFN_KODI_ADDON_PERIPHERAL_PERFORM_DEVICE_SCAN_V1)(
      KODI_ADDON_PERIPHERAL_HDL hdl,
      struct PERIPHERAL_INFO** scan_results, size_t* peripheral_count);
  typedef void(ATTR_APIENTRYP PFN_KODI_ADDON_PERIPHERAL_FREE_SCAN_RESULTS_V1)(
      KODI_ADDON_PERIPHERAL_HDL hdl, struct PERIPHERAL_INFO* scan_results, size_t peripheral_count);
  typedef enum PERIPHERAL_ERROR(ATTR_APIENTRYP PFN_KODI_ADDON_PERIPHERAL_GET_EVENTS_V1)(
      KODI_ADDON_PERIPHERAL_HDL hdl, struct PERIPHERAL_EVENT** events, size_t* event_count);
  typedef void(ATTR_APIENTRYP PFN_KODI_ADDON_PERIPHERAL_FREE_EVENTS_V1)(KODI_ADDON_PERIPHERAL_HDL hdl,
                                                             struct PERIPHERAL_EVENT* events,
                                                             size_t event_count);
  typedef bool(ATTR_APIENTRYP PFN_KODI_ADDON_PERIPHERAL_SEND_EVENT_V1)(KODI_ADDON_PERIPHERAL_HDL hdl,
                                                            const struct PERIPHERAL_EVENT* event);

  //--==----==----==----==----==----==----==----==----==----==----==----==----==
  // Joystick operations
  typedef enum PERIPHERAL_ERROR(ATTR_APIENTRYP PFN_KODI_ADDON_PERIPHERAL_GET_JOYSTICK_INFO_V1)(
      KODI_ADDON_PERIPHERAL_HDL hdl, unsigned int index, struct JOYSTICK_INFO* info);
  typedef void(ATTR_APIENTRYP PFN_KODI_ADDON_PERIPHERAL_FREE_JOYSTICK_INFO_V1)(KODI_ADDON_PERIPHERAL_HDL hdl,
                                                                    struct JOYSTICK_INFO* info);
  typedef enum PERIPHERAL_ERROR(ATTR_APIENTRYP PFN_KODI_ADDON_PERIPHERAL_GET_FEATURES_V1)(
      KODI_ADDON_PERIPHERAL_HDL hdl,
      const struct JOYSTICK_INFO* joystick,
      const char* controller_id,
      struct JOYSTICK_FEATURE** features,
      size_t* feature_count);
  typedef void(ATTR_APIENTRYP PFN_KODI_ADDON_PERIPHERAL_FREE_FEATURES_V1)(KODI_ADDON_PERIPHERAL_HDL hdl,
                                                               struct JOYSTICK_FEATURE* features,
                                                               size_t feature_count);
  typedef enum PERIPHERAL_ERROR(ATTR_APIENTRYP PFN_KODI_ADDON_PERIPHERAL_MAP_FEATURES_V1)(
      KODI_ADDON_PERIPHERAL_HDL hdl,
      const struct JOYSTICK_INFO* joystick,
      const char* controller_id,
      const struct JOYSTICK_FEATURE* features,
      size_t feature_count);
  typedef enum PERIPHERAL_ERROR(ATTR_APIENTRYP PFN_KODI_ADDON_PERIPHERAL_GET_IGNORED_PRIMITIVES_V1)(
      KODI_ADDON_PERIPHERAL_HDL hdl,
      const struct JOYSTICK_INFO* joystick,
      struct JOYSTICK_DRIVER_PRIMITIVE** primitives,
      size_t* primitive_count);
  typedef void(ATTR_APIENTRYP PFN_KODI_ADDON_PERIPHERAL_FREE_PRIMITIVES_V1)(KODI_ADDON_PERIPHERAL_HDL hdl,
                                               struct JOYSTICK_DRIVER_PRIMITIVE* primitives,
                                               size_t primitive_count);
  typedef enum PERIPHERAL_ERROR(ATTR_APIENTRYP PFN_KODI_ADDON_PERIPHERAL_SET_IGNORED_PRIMITIVES_V1)(
      KODI_ADDON_PERIPHERAL_HDL hdl,
      const struct JOYSTICK_INFO* joystick,
      const struct JOYSTICK_DRIVER_PRIMITIVE* primitives,
      size_t primitive_count);
  typedef void(ATTR_APIENTRYP PFN_KODI_ADDON_PERIPHERAL_SAVE_BUTTON_MAP_V1)(
      KODI_ADDON_PERIPHERAL_HDL hdl, const struct JOYSTICK_INFO* joystick);
  typedef void(ATTR_APIENTRYP PFN_KODI_ADDON_PERIPHERAL_REVERT_BUTTON_MAP_V1)(
      KODI_ADDON_PERIPHERAL_HDL hdl, const struct JOYSTICK_INFO* joystick);
  typedef void(ATTR_APIENTRYP PFN_KODI_ADDON_PERIPHERAL_RESET_BUTTON_MAP_V1)(
      KODI_ADDON_PERIPHERAL_HDL hdl, const struct JOYSTICK_INFO* joystick, const char* controller_id);
  typedef void(ATTR_APIENTRYP PFN_KODI_ADDON_PERIPHERAL_POWER_OFF_JOYSTICK_V1)(KODI_ADDON_PERIPHERAL_HDL hdl,
                                                                    unsigned int index);

  typedef struct KODI_ADDON_PERIPHERAL_FUNC
  {
    PFN_KODI_ADDON_PERIPHERAL_CREATE_V1 create;
    PFN_KODI_ADDON_PERIPHERAL_DESTROY_V1 destroy;

    PFN_KODI_ADDON_PERIPHERAL_GET_CAPABILITIES_V1 get_capabilities;
    PFN_KODI_ADDON_PERIPHERAL_PERFORM_DEVICE_SCAN_V1 perform_device_scan;
    PFN_KODI_ADDON_PERIPHERAL_FREE_SCAN_RESULTS_V1 free_scan_results;
    PFN_KODI_ADDON_PERIPHERAL_GET_EVENTS_V1 get_events;
    PFN_KODI_ADDON_PERIPHERAL_FREE_EVENTS_V1 free_events;
    PFN_KODI_ADDON_PERIPHERAL_SEND_EVENT_V1 send_event;

    //--==----==----==----==----==----==----==----==----==----==----==----==----==
    // Joystick operations
    PFN_KODI_ADDON_PERIPHERAL_GET_JOYSTICK_INFO_V1 get_joystick_info;
    PFN_KODI_ADDON_PERIPHERAL_FREE_JOYSTICK_INFO_V1 free_joystick_info;
    PFN_KODI_ADDON_PERIPHERAL_GET_FEATURES_V1 get_features;
    PFN_KODI_ADDON_PERIPHERAL_FREE_FEATURES_V1 free_features;
    PFN_KODI_ADDON_PERIPHERAL_MAP_FEATURES_V1 map_features;
    PFN_KODI_ADDON_PERIPHERAL_GET_IGNORED_PRIMITIVES_V1 get_ignored_primitives;
    PFN_KODI_ADDON_PERIPHERAL_FREE_PRIMITIVES_V1 free_primitives;
    PFN_KODI_ADDON_PERIPHERAL_SET_IGNORED_PRIMITIVES_V1 set_ignored_primitives;
    PFN_KODI_ADDON_PERIPHERAL_SAVE_BUTTON_MAP_V1 save_button_map;
    PFN_KODI_ADDON_PERIPHERAL_REVERT_BUTTON_MAP_V1 revert_button_map;
    PFN_KODI_ADDON_PERIPHERAL_RESET_BUTTON_MAP_V1 reset_button_map;
    PFN_KODI_ADDON_PERIPHERAL_POWER_OFF_JOYSTICK_V1 power_off_joystick;
  } KODI_ADDON_PERIPHERAL_FUNC;

  ATTR_DLL_EXPORT void kodi_addon_peripheral_trigger_scan(KODI_OWN_HDL hdl) __INTRODUCED_IN_KODI(1);
  ATTR_DLL_EXPORT void kodi_addon_peripheral_refresh_button_maps(KODI_OWN_HDL hdl,
                                                                 const char* device_name,
                                                                 const char* controller_id)
      __INTRODUCED_IN_KODI(1);
  ATTR_DLL_EXPORT unsigned int kodi_addon_peripheral_feature_count(KODI_OWN_HDL hdl,
                                                                   const char* controller_id,
                                                                   enum JOYSTICK_FEATURE_TYPE type)
      __INTRODUCED_IN_KODI(1);
  ATTR_DLL_EXPORT enum JOYSTICK_FEATURE_TYPE kodi_addon_peripheral_feature_type(
      KODI_OWN_HDL hdl, const char* controller_id, const char* feature_name)
      __INTRODUCED_IN_KODI(1);

#ifdef __cplusplus
} /* extern "C" */
#endif /* __cplusplus */

#endif /* !C_API_ADDONINSTANCE_PERIPHERAL_H */
