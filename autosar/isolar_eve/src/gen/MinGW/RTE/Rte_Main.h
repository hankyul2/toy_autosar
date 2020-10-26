/** @file         Rte_Main.h
  *
  * @brief        RTE/BSW Scheduler lifecycle definitions
  *
  * @copyright    Copyright 2007-2008 ETAS Engineering Tools Application and Services Ltd.
  *               Copyright 2008-2013 ETAS GmbH.
  *
  * @note         Implemented SWS: 4.0
  *
  * @note         PLATFORM DEPENDANT [yes/no]: no
  *
  * @note         TO BE CHANGED BY USER [yes/no]: no
  *
  * Template:     Id: Rte_Main_h.template 35352 2013-07-30 14:06:45Z sha1yok
  */

#ifndef RTEMAIN_H
#define RTEMAIN_H

#include "Rte.h"  /* [$Satisfies $SWS 1159] */

#define RTE_START_SEC_LIBCODE
#include "MemMap.h" /*lint !e537 permit multiple inclusion */

/* BEGIN: RTE Lifecycle API */

extern FUNC(Std_ReturnType, RTE_LIBCODE) Rte_Start(void);
extern FUNC(Std_ReturnType, RTE_LIBCODE) Rte_Stop(void);

extern FUNC(void, RTE_LIBCODE) Rte_MainFunction(void);

/* END: RTE Lifecycle API */

/* BEGIN: BSW Scheduler Lifecycle API */

/* [$Satisfies $SWS40 7270] [$Satisfies $SWS40 6544] [$Satisfies $SWS40 6545] */
extern FUNC(void, RTE_LIBCODE) SchM_Init( void );

/* [$Satisfies $SWS40 7274] */
extern FUNC(void, RTE_LIBCODE) SchM_Deinit(void);

/* END: BSW Scheduler Lifecycle API */

#define RTE_STOP_SEC_LIBCODE
#include "MemMap.h" /*lint !e537 permit multiple inclusion */


#endif /* RTEMAIN_H */

