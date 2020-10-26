#ifndef vrtaStdDevicesH
#define vrtaStdDevicesH
/* --------------------------------------------------------------------------- */
/*  Fixed devices */
/* --------------------------------------------------------------------------- */
#define DM_DEVICE_ID  (0U)              /*  [VP_ECUIF 1016] */
#define ICU_DEVICE_ID (1U)              /*  [VP_ECUIF 1017] [VP_VECU 312] */
#define AM_DEVICE_ID  (2U)              /*  [VP_ECUIF 1018] */

/* --------------------------------------------------------------------------- */
/*  IDs of the actions that the Device Manager supports. */
/* --------------------------------------------------------------------------- */
#define DM_ACTION_ID_EventRegister      (1U)
#define DM_ACTION_ID_HookEvents         (2U)
#define DM_ACTION_ID_ListAll            (3U)
#define DM_ACTION_ID_GetDeviceActions   (4U)
#define DM_ACTION_ID_GetDeviceEvents    (5U)
#define DM_ACTION_ID_GetDeviceInfo      (6U)

/* --------------------------------------------------------------------------- */
/*  IDs of the events that the Device Manager supports. */
/* --------------------------------------------------------------------------- */
#define DM_EVENT_ID_DeviceList          (1U)
#define DM_EVENT_ID_DeviceActions       (2U)
#define DM_EVENT_ID_DeviceEvents        (3U)
#define DM_EVENT_ID_DeviceInfo          (4U)

/* --------------------------------------------------------------------------- */
/*  IDs of the actions that the ICU supports. */
/* --------------------------------------------------------------------------- */

#define ICU_ACTION_ID_Raise             (1U)    /*  [VP_VECU 314] [VP_ECUIF 1074] */
#define ICU_ACTION_ID_Clear             (2U)    /*  [VP_VECU 315] [VP_ECUIF 1076] */
#define ICU_ACTION_ID_Mask              (3U)    /*  [VP_VECU 316] [VP_ECUIF 1078] */
#define ICU_ACTION_ID_Unmask            (4U)    /*  [VP_VECU 317] [VP_ECUIF 1080] */
#define ICU_ACTION_ID_GetPending        (5U)    /*  [VP_VECU 318] [VP_ECUIF 1082] */
#define ICU_ACTION_ID_GetIPL            (6U)    /*  [VP_VECU 319] [VP_ECUIF 1083] */
#define ICU_ACTION_ID_SetIPL            (7U)    /*  [VP_VECU 320] */

/* --------------------------------------------------------------------------- */
/*  IDs of the events that the ICU supports. */
/* --------------------------------------------------------------------------- */

#define ICU_EVENT_ID_Pending            (1U)    /*  [VP_VECU 321] [VP_ECUIF 1084] */
#define ICU_EVENT_ID_Start              (2U)    /*  [VP_VECU 322] [VP_ECUIF 1086] */
#define ICU_EVENT_ID_Stop               (3U)    /*  [VP_VECU 323] [VP_ECUIF 1088] */
#define ICU_EVENT_ID_IPL                (4U)    /*  [VP_VECU 324] [VP_ECUIF 1090] */
#define ICU_EVENT_ID_MASKS              (5U)    /*  [VP_VECU 792] [VP_ECUIF 1121] */

/* --------------------------------------------------------------------------- */
/*  IDs of the actions that the Application Manager supports. */
/* --------------------------------------------------------------------------- */
#define AM_ACTION_ID_Start              (1U)
#define AM_ACTION_ID_Terminate          (2U)
#define AM_ACTION_ID_Pause              (3U)
#define AM_ACTION_ID_Restart            (4U)
#define AM_ACTION_ID_Reset              (5U)
#define AM_ACTION_ID_GetInfo            (6U)
#define AM_ACTION_ID_TestOption         (7U)
#define AM_ACTION_ID_ReadOption         (8U)
#define AM_ACTION_ID_ReadParam          (9U)

/* --------------------------------------------------------------------------- */
/*  IDs of the events that the Device Manager supports. */
/* --------------------------------------------------------------------------- */
#define AM_EVENT_ID_Started             (1U)
#define AM_EVENT_ID_Paused              (2U)
#define AM_EVENT_ID_Restarted           (3U)
#define AM_EVENT_ID_Reset               (4U)
#define AM_EVENT_ID_Terminated          (5U)
#define AM_EVENT_ID_Info                (6U)
#define AM_EVENT_ID_Option              (7U)
#define AM_EVENT_ID_OptionText          (8U)
#define AM_EVENT_ID_ParamText           (9U)
#define AM_EVENT_ID_State               (10U)

#endif /* vrtaStdDevicesH */
