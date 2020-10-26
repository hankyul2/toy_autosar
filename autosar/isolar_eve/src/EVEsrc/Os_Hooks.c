/** \file         Os_Hooks.c
  *
  * \brief        Example for general service interfaces (Startup/Idle/...) for ISOLAR-EVE ( target platform: VRTA-ux/VRTA-win )
  *
  * [$crn:2007:dox
  * \copyright Copyright 2014 ETAS GmbH
  * $]
  *
  * \note         PLATFORM DEPENDENT [yes/no]: yes
  *
  * \note         TO BE CHANGED BY USER [yes/no]: yes
  *
  * $Id: Os_Hooks.c 2379 2014-08-10 12:55:57Z pin9fe $
  */

#include "Os.h"
#include "Main_Cfg.h"
#include "target.h"
#include "Rte_Intl.h"		/* If RTE is used */
#include "Vrta_Cfg.h"

/* ------------------------------------------------------------------------- */
/* This is called during StartOS() and before RTA-OS starts the scheduler.
 * It is the safest place to enable interrupt sources that have been initialized
 * before StartOS() was called. */
FUNC(void, OS_APPL_CODE)
StartupHook(void)
{
    TargetEnableInterrupts();

}

/* ------------------------------------------------------------------------- */
FUNC(void, OS_APPL_CODE) ShutdownHook(StatusType Error)
{
    /* OS has shut down */
}

/* ------------------------------------------------------------------------- */
FUNC(boolean,OS_APPL_CODE)
Os_Cbk_Idle(void)
{
    if ( !Rte_Initialized ) {
        /* Start the RTE */
        Rte_Start();

        /* TODO:
		 * Enable interrupts used that drive periodic runnables (e.g. schedule
         * table, periodic alarms, etc.). This should be done only after
         * Rte_Start to ensure that no runnable is triggered until the RTE is
         * initialized. */
    }

    while(!vrtaIsAppFinished()) {
#ifdef VRTA_ux
		rtos_log_flush();
		/* To support VRTA Implementation */
		vrtaActionHandler();
#endif
		vrtaIsIdle(5);

#ifdef OS_TRACE
		Os_CheckTraceOutput();
#endif
    }

	vrtaTerminate();

    return TRUE;
}


/*****************************************************************************
 * \brief Return value of the stopwatch counter
 *
 * \return Current tick value of OS stopwatch
 */

FUNC(Os_StopwatchTickType, OS_APPL_CODE)
Os_Cbk_GetStopwatch( void )
{
#ifdef OS_TRACE
	return (Os_StopwatchTickType)vrtaReadHPTime(OSSWTICKSPERSECOND);
#else
    return (Os_StopwatchTickType) (1000 * TargetReadClock());
#endif /* defined(OS_TRACE) */
}

/*****************************************************************************
 * \brief Os_Cbk_CheckMemoryAccess dummy implementation.
 */

FUNC(AccessType, OS_APPL_CODE)
Os_Cbk_CheckMemoryAccess(ApplicationType Application, TaskType TaskID, ISRType ISRID, MemoryStartAddressType Address, MemorySizeType Size)
{
    (void)Application;
    (void)TaskID;
    (void)ISRID;
    (void)Address;
    (void)Size;

    return (AccessType)(0U);
}
