/** \file         VECU_SystemClock_ISR.c
  *
  * \brief        RTE tick counter handling for ISOLAR-EVE ( target platform: VRTA-ux/VRTA-win )
  *
  * [$crn:2007:dox
  * \copyright Copyright 2014 ETAS GmbH
  * $]
  *
  * \note         PLATFORM DEPENDENT [yes/no]: no
  *
  * \note         TO BE CHANGED BY USER [yes/no]: maybe
  *
  * $Id: VECU_SystemClock_ISR.c 2379 2014-08-10 12:55:57Z pin9fe $
  */

#include "Os_EVE.h"
#include "Main_Cfg.h"
#include "Rte_Const.h"

/* This interrupt occurs every 1ms */
#define VECU_SYSTEMCLOCK_INTERVAL_US (1000)

/* Calculate rate to call Rte counter */
#ifdef RTE_PERIODIC_COUNTER_TICK_INTERVAL_US
#define ms_per_rte_tick (RTE_PERIODIC_COUNTER_TICK_INTERVAL_US / VECU_SYSTEMCLOCK_INTERVAL_US)
static int rte_tick_interval_count = 0;
#endif

/* Calculate rate to call Rte main function */
#define ms_per_rte_main (RTE_MAINFUNCTION_PERIOD_US / VECU_SYSTEMCLOCK_INTERVAL_US)
static int rte_main_interval_count = 0;

/* In the default configuration, this ISR is driven by the
 * VECU_SystemClock defined in VECU_SystemClock.cpp.
 * You may add further actions here as well as you may choose
 * a different method to stimulate the RTE tick counter in
 * VRTA OS configuration.
 */
EVE_ISR(VECU_SYSTEMCLOCK_ISR)
{
#ifdef DEFAULT_BSW_TASK
    Os_IncrementCounter_BswCounter();
#endif

#ifdef RTE_PERIODIC_COUNTER_TICK_INTERVAL_US
    if (ms_per_rte_tick == ++rte_tick_interval_count) {
    rte_tick_interval_count = 0;
    Os_IncrementCounter_Rte_TickCounter();
  }
#endif

  if (ms_per_rte_main == ++rte_main_interval_count) {
    rte_main_interval_count = 0;
    Rte_MainFunction();
  }
}
