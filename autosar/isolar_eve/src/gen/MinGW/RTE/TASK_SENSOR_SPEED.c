/** @file     TASK_SENSOR_SPEED.c
  * 
  * @brief    Task TASK_SENSOR_SPEED body
  * 
  * @note     AUTOMATICALLY GENERATED FILE! DO NOT EDIT!
  * 
  * @note     Generated by ETAS GmbH  RTA-RTE v5.8.4  (R4.0 backend version: v7.8.7 (Build 46772))
  */

#define RTE_CORE

#include "Rte_Const.h"
#if !defined(RTE_VENDOR_MODE)
#pragma message "Compiling an individual task file but RTE_VENDOR_MODE not defined. Compiling a stale file?"
#endif /* !defined(RTE_VENDOR_MODE) */
#if defined(RTE_USE_TASK_HEADER)
#include "TASK_SENSOR_SPEED.h"
#else /* defined(RTE_USE_TASK_HEADER) */
#include "Os.h"
#endif /* defined(RTE_USE_TASK_HEADER) */
#if defined(RTE_REQUIRES_IOC)
#include "Ioc.h"
#endif /* defined(RTE_REQUIRES_IOC) */
#include "Rte.h"
#include "Rte_Intl.h"
#include "Rte_Type.h"
#include "Rte_DataHandleType.h"

/* Runnable entity prototypes */
#define SENSOR_SPEED_START_SEC_CODE
#include "SENSOR_SPEED_MemMap.h" /*lint !e537 permit multiple inclusion */
FUNC(void, SENSOR_SPEED_CODE) RE_SPEED(void);
#define SENSOR_SPEED_STOP_SEC_CODE
#include "SENSOR_SPEED_MemMap.h" /*lint !e537 permit multiple inclusion */

#define RTE_START_SEC_TASKBODY
#include "MemMap.h" /*lint !e537 permit multiple inclusion */
TASK(TASK_SENSOR_SPEED)
{
   /* Box: Implicit Buffer Initialization begin */
   /* Box: Implicit Buffer Initialization end */
   /* Box: Implicit Buffer Fill begin */
   /* Box: Implicit Buffer Fill end */
   {
      /* Box: CPT_SENSOR_SPEED begin */
      RE_SPEED();
      /* Box: CPT_SENSOR_SPEED end */
   }
   /* Box: Implicit Buffer Flush begin */
   /* Box: Implicit Buffer Flush end */
   TerminateTask();
} /* TASK_SENSOR_SPEED */
#define RTE_STOP_SEC_TASKBODY
#include "MemMap.h" /*lint !e537 permit multiple inclusion */

