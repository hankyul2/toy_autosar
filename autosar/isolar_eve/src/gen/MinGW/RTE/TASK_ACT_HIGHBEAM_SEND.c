/** @file     TASK_ACT_HIGHBEAM_SEND.c
  * 
  * @brief    Task TASK_ACT_HIGHBEAM_SEND body
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
#include "TASK_ACT_HIGHBEAM_SEND.h"
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

#define RTE_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h" /*lint !e537 permit multiple inclusion */
extern CONST(Rte_QTaskType, RTE_DATA) Rte_Queue_CPT_ACT_HIGHBEAM_P_HIGBEAMMODE_TO_ECU_ABS_AFS_OPER_ACT_TO_ECU;
#define RTE_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h" /*lint !e537 permit multiple inclusion */

/* Runnable entity prototypes */
#define ACT_HIGHBEAM_START_SEC_CODE
#include "ACT_HIGHBEAM_MemMap.h" /*lint !e537 permit multiple inclusion */
FUNC(void, ACT_HIGHBEAM_CODE) RE_HIGHBEAM_SEND(CONSTP2VAR(sint32, AUTOMATIC, RTE_APPL_DATA) ADP_ACT_TO_ECU);
#define ACT_HIGHBEAM_STOP_SEC_CODE
#include "ACT_HIGHBEAM_MemMap.h" /*lint !e537 permit multiple inclusion */

#define RTE_START_SEC_TASKBODY
#include "MemMap.h" /*lint !e537 permit multiple inclusion */
TASK(TASK_ACT_HIGHBEAM_SEND)
{
   /* Box: Implicit Buffer Initialization begin */
   /* Box: Implicit Buffer Initialization end */
   /* Box: Implicit Buffer Fill begin */
   /* Box: Implicit Buffer Fill end */
   {
      /* Box: CPT_ACT_HIGHBEAM begin */
      /* P_HIGBEAMMODE_TO_ECU_ABS_AFS */
      {
         Rte_CPT_ACT_HIGHBEAM_P_HIGBEAMMODE_TO_ECU_ABS_AFS_OPER_ACT_TO_ECU_RtnQEType cliQEl;
         Std_ReturnType rtn;
         Rte_CPT_ACT_HIGHBEAM_P_HIGBEAMMODE_TO_ECU_ABS_AFS_OPER_ACT_TO_ECU_QEType srvQEl;

         for (;;) {
            rtn = Rte_ReadQueue(&Rte_Queue_CPT_ACT_HIGHBEAM_P_HIGBEAMMODE_TO_ECU_ABS_AFS_OPER_ACT_TO_ECU.cmn, &srvQEl);
            if ( ( ((VAR(Std_ReturnType, AUTOMATIC))RTE_E_OK) == rtn ) || ( ((VAR(Std_ReturnType, AUTOMATIC))RTE_E_LOST_DATA) == rtn ) )
            {
               cliQEl.ADP_ACT_TO_ECU = srvQEl.ADP_ACT_TO_ECU;
               /* SpecReq: Measurement point CS begin */
               /* SpecReq: Measurement point CS end */
               RE_HIGHBEAM_SEND(&cliQEl.ADP_ACT_TO_ECU);
               /* SpecReq: Measurement point CS begin */
               /* SpecReq: Measurement point CS end */
               Rte_WriteQueue(srvQEl.clientQueue, &cliQEl);
            }
            else
            {
               break;
            }
         }
      }
      /* Box: CPT_ACT_HIGHBEAM end */
   }
   /* Box: Implicit Buffer Flush begin */
   /* Box: Implicit Buffer Flush end */
   TerminateTask();
} /* TASK_ACT_HIGHBEAM_SEND */
#define RTE_STOP_SEC_TASKBODY
#include "MemMap.h" /*lint !e537 permit multiple inclusion */

