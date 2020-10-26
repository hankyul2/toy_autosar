/** \file         EVE_SystemClock.cpp
  *
  * \brief        System clock functions for ISOLAR-EVE ( target platform: VRTA-ux/VRTA-win )
  *
  * [$crn:2007:dox
  * \copyright Copyright 2014 ETAS GmbH
  * $]
  *
  * \note         PLATFORM DEPENDENT [yes/no]: yes
  *
  * \note         TO BE CHANGED BY USER [yes/no]: no
  *
  * $Id: EVE_SystemClock.cpp 5465 2014-09-04 09:11:47Z sui9fe $
  */

#include "Main_Cfg.h"
#include "EVE_SystemClock.h"
#include "vrtaSampleDevices.h"
#ifdef VRTA_ux
#include "rtos.h"
#endif


/** VECU System Clock */
static vrtaClock VECU_SystemClock((vrtaTextPtr)"SystemTick", VECU_SYSTEMCLOCK_PERIOD);

/** Periodic Counter providing number of VECU System Clock Ticks */
static vrtaUpCounter VECU_SystemClockCounter( (vrtaTextPtr)"VECU_SystemClockCounter", VECU_SystemClock);

/** Periodic Counter used by VECU_SystemClockCompare */
static vrtaUpCounter VECU_SystemClockPeriodicCounter( (vrtaTextPtr)"VECU_SystemClockPeriodicCounter", VECU_SystemClock );

/** Comparer is used to raise VECU System Clock Interrupt */
static vrtaCompare VECU_SystemClockCompare( (vrtaTextPtr)"VECU_SystemClockCompare",
                                             VECU_SystemClockPeriodicCounter,
                                             0,
                                             VECU_SYSTEMCLOCK_IRQ );

/**
 * Initialize VECU System Clock.
 *
 * This function does the initialization of the VECU System Clock
 * and its counters. The clock mode is set according to the
 * content of the file <vecuWorkspace>/var/conf.adaptive-time. The
 * default setting of the clock mode is REALTIME.
 */
extern "C" void VECU_SystemClock_Init()
{
   VECU_SystemClockPeriodicCounter.SetMin( 0 );
   VECU_SystemClockPeriodicCounter.SetMax( 0 );

   VECU_SystemClockCounter.SetMin( 0 );
#ifdef OSMAXALLOWEDVALUE_Rte_TickCounter
   VECU_SystemClockCounter.SetMax( OSMAXALLOWEDVALUE_Rte_TickCounter );
#else
   VECU_SystemClockCounter.SetMax( 0 );
#endif
   vrtaSystemClock.Subscribe(&VECU_SystemClock);
}

/**
 * Start VECU System Clock.
 *
 * This function is called TargetInit.
 */
extern "C" void VECU_SystemClock_Start()
{
   VECU_SystemClockPeriodicCounter.Stop();
   VECU_SystemClockPeriodicCounter.SetVal( 0 );
   VECU_SystemClock.Start();
   VECU_SystemClockCounter.Start();
   VECU_SystemClockPeriodicCounter.Start();
}

/**
 * Get System Clock Value.
 *
 * This function returns the value of the VECU System Clock counter.
 *
 * @return Number of System Counter Ticks
 */
extern "C" vrtaUInt VECU_SystemClock_GetValue()
{
    return VECU_SystemClockCounter.Value();
}

