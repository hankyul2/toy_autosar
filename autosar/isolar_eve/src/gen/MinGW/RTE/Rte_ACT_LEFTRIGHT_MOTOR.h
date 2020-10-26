/** @file     Rte_ACT_LEFTRIGHT_MOTOR.h
  * 
  * @brief    Application header file
  * 
  * @note     AUTOMATICALLY GENERATED FILE! DO NOT EDIT!
  * 
  * @note     Generated by ETAS GmbH  RTA-RTE v5.8.4  (R4.0 backend version: v7.8.7 (Build 46772))
  */

#ifndef RTE_ACT_LEFTRIGHT_MOTOR_H
#define RTE_ACT_LEFTRIGHT_MOTOR_H

#ifndef RTE_CORE
#ifdef RTE_APPLICATION_HEADER_FILE
#error Multiple application header files included.
#endif /* RTE_APPLICATION_HEADER_FILE */
#define RTE_APPLICATION_HEADER_FILE
#endif /* RTE_CORE */

/*******************************************************
 ***
 *** Includes
 ***
 *******************************************************/

#include "Rte.h"
#include "Rte_Intl.h"
#include "Rte_ACT_LEFTRIGHT_MOTOR_Type.h"

#include "Rte_DataHandleType.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#if defined(RTE_RUNNABLEAPI_RE_LEFTRIGHTANGLE_RECEIVE)
   /* Do nothing for this and all elif clauses below (rte_sws_2751) */
#elif defined(RTE_RUNNABLEAPI_RE_LEFTRIGHTANGLE_SEND)
#else
   /* None of above defined so define value including all APIs (rte_sws_2751) */
   #define RTE_PRV_ALL_API
#endif

/*******************************************************
 ***
 *** Constants
 ***
 *******************************************************/


/*******************************************************
 ***
 *** Public Types
 ***
 *******************************************************/

/* BEGIN: SWC types (core visible) */
struct Rte_CDS_ACT_LEFTRIGHT_MOTOR {
   uint8 _dummy;
};
typedef struct Rte_CDS_ACT_LEFTRIGHT_MOTOR Rte_CDS_ACT_LEFTRIGHT_MOTOR;

/* END: SWC types (core visible) */

/*******************************************************
 ***
 *** Private Types
 ***
 *******************************************************/

/* BEGIN: SWC types (private) */
/* END: SWC types (private) */

/*******************************************************
 ***
 *** Instance Declarations
 ***
 *******************************************************/

#define RTE_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h" /*lint !e537 permit multiple inclusion */
extern CONST(struct Rte_CDS_ACT_LEFTRIGHT_MOTOR, RTE_CONST) Rte_Inst_ACT_LEFTRIGHT_MOTOR;
#define RTE_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h" /*lint !e537 permit multiple inclusion */


#ifndef RTE_CORE
typedef CONSTP2CONST(struct Rte_CDS_ACT_LEFTRIGHT_MOTOR, AUTOMATIC, RTE_CONST) Rte_Instance;
#endif /* RTE_CORE */

/*******************************************************
 ***
 *** API Mapping macros
 ***
 *******************************************************/

/* API Mapping Macros */
#ifndef RTE_CORE

#define RTE_START_SEC_CODE
#include "MemMap.h" /*lint !e537 permit multiple inclusion */
FUNC(sint32, RTE_CODE) Rte_DRead_ACT_LEFTRIGHT_MOTOR_R_LEFTRIGHTANGLE_FROM_APP_MOTOR_VDP_APP_TO_ACT(void);
#define RTE_STOP_SEC_CODE
#include "MemMap.h" /*lint !e537 permit multiple inclusion */
#if defined(RTE_PRV_ALL_API) || defined(RTE_RUNNABLEAPI_RE_LEFTRIGHTANGLE_RECEIVE)
#define Rte_DRead_R_LEFTRIGHTANGLE_FROM_APP_MOTOR_VDP_APP_TO_ACT() (Rte_DRead_ACT_LEFTRIGHT_MOTOR_R_LEFTRIGHTANGLE_FROM_APP_MOTOR_VDP_APP_TO_ACT())
#endif

/* IRV externs (explicit access) */
#define RTE_START_SEC_VAR_32BIT
#include "MemMap.h" /*lint !e537 permit multiple inclusion */
extern VAR(sint32, RTE_DATA) CPT_ACT_LEFTRIGHT_MOTOR_IB_ACT_LEFTRIGHT_MOTOR_Explicit_VariableDataPrototype_0;
#define RTE_STOP_SEC_VAR_32BIT
#include "MemMap.h" /*lint !e537 permit multiple inclusion */


/* Rte_Irv API (explicit access) */
/* Inline read optimization; Rte_IrvRead_RE_LEFTRIGHTANGLE_SEND_Explicit_VariableDataPrototype_0 to direct read */
#define Rte_IrvRead_RE_LEFTRIGHTANGLE_SEND_Explicit_VariableDataPrototype_0()  ( CPT_ACT_LEFTRIGHT_MOTOR_IB_ACT_LEFTRIGHT_MOTOR_Explicit_VariableDataPrototype_0 )

/* Inline IrvWrite optimization; Rte_IrvWrite_RE_LEFTRIGHTANGLE_RECEIVE_Explicit_VariableDataPrototype_0 to direct write */
#define Rte_IrvWrite_RE_LEFTRIGHTANGLE_RECEIVE_Explicit_VariableDataPrototype_0(data) ( (CPT_ACT_LEFTRIGHT_MOTOR_IB_ACT_LEFTRIGHT_MOTOR_Explicit_VariableDataPrototype_0 = data) )


#endif /* RTE_CORE */

/*******************************************************
 ***
 *** RE Prototypes
 ***
 *******************************************************/

#define ACT_LEFTRIGHT_MOTOR_START_SEC_CODE
#include "ACT_LEFTRIGHT_MOTOR_MemMap.h" /*lint !e537 permit multiple inclusion */
FUNC(void, ACT_LEFTRIGHT_MOTOR_CODE) RE_LEFTRIGHTANGLE_RECEIVE(void);
FUNC(void, ACT_LEFTRIGHT_MOTOR_CODE) RE_LEFTRIGHTANGLE_SEND(CONSTP2VAR(sint32, AUTOMATIC, RTE_APPL_DATA) ADP_ACT_TO_ECU);
#define ACT_LEFTRIGHT_MOTOR_STOP_SEC_CODE
#include "ACT_LEFTRIGHT_MOTOR_MemMap.h" /*lint !e537 permit multiple inclusion */

/* Initial values for data element prototypes */

#ifdef __cplusplus
} /* extern C */
#endif /* __cplusplus */

#endif /* RTE_ACT_LEFTRIGHT_MOTOR_H */
