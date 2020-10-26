/** \file         Can_GeneralTypes.h
  *
  * \brief        General settings (BSW, XCP) for ISOLAR-EVE ( target platform: VRTA-ux/VRTA-win)
  *
  * [$crn:2007:dox
  * \copyright Copyright 2014 ETAS GmbH
  * $]
  *
  * \note         PLATFORM DEPENDENT [yes/no]: yes
  *
  * \note         TO BE CHANGED BY USER [yes/no]: yes
  *
  * $Id: Can_GeneralTypes.h 2379 2014-08-10 12:55:57Z pin9fe $
  */

#ifndef CAN_GENERAL_TYPES_H_
#define CAN_GENERAL_TYPES_H_

/*
 * A sample version of the content of a minimal
 * "Can_GeneralTypes.h" file. This is common for
 * all the CAN modules.
 */
//------------------------------------------------------------------------------
//  CanTrcv type specifications.
//------------------------------------------------------------------------------
/* [$CanTrcv 166] */
typedef enum {
  CANTRCV_TRCVMODE_NORMAL,
  CANTRCV_TRCVMODE_SLEEP,
  CANTRCV_TRCVMODE_STANDBY
} CanTrcv_TrcvModeType; /* [$CanTrcv 163] */

typedef enum {
  CANTRCV_WUMODE_ENABLE,
  CANTRCV_WUMODE_CLEAR,
  CANTRCV_WUMODE_DISABLE
} CanTrcv_TrcvWakeupModeType; /* [$CanTrcv 164] */

typedef enum {
  CANTRCV_WU_ERROR,
  CANTRCV_WU_BY_BUS,
  CANTRCV_WU_BY_PIN,
  CANTRCV_WU_INTERNALLY,
  CANTRCV_WU_NOT_SUPPORTED,
  CANTRCV_WU_POWER_ON,
  CANTRCV_WU_RESET,
  CANTRCV_WU_BY_SYSERR
} CanTrcv_TrcvWakeupReasonType; /* [$CanTrcv 165] */

//------------------------------------------------------------------------------
//  Can type specifications.
//------------------------------------------------------------------------------
typedef uint32 Can_IdType; /* [$CAN 416] */
typedef uint16 Can_HwHandleType; /*[$CAN 429]*/

typedef struct /* Can_PduType */ {
  PduIdType swPduHandle;
  uint8 length;
  Can_IdType id;
  uint8* sdu;
} Can_PduType;  /*[$CAN 415]*/

typedef enum /* Can_StateTransitionType */ {
  CAN_T_START,
  CAN_T_STOP,
  CAN_T_SLEEP,
  CAN_T_WAKEUP
} Can_StateTransitionType; /* [$CAN 417] */

typedef enum /* Can_ReturnType */ {
  CAN_OK,
  CAN_NOT_OK,
  CAN_BUSY
} Can_ReturnType;/* [$CAN 39] */

typedef struct /* Can_HwType */ {
  Can_IdType id;
  Can_HwHandleType hoh;
  uint8 ctrlId;
} Can_HwType;/* [$CAN 1137] */

#endif