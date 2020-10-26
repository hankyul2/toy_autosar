/** \file         target.cpp
  *
  * \brief        Target initialization and timing functions for ISOLAR-EVE ( target platform: VRTA-ux/VRTA-win )
  *
  * [$crn:2007:dox
  * \copyright Copyright 2014 ETAS GmbH
  * $]
  *
  * \note         PLATFORM DEPENDENT [yes/no]: yes
  *
  * \note         TO BE CHANGED BY USER [yes/no]: no
  *
  * $Id: target.cpp 2379 2014-08-10 12:55:57Z pin9fe $
  */

#include "target.h"
#include "Main_Cfg.h"
#include "EVE_SystemClock.h"

/**
 * Initialize vrtaDeivce.
 *
 * This function is called by VRTA-OS to initialize vrtaDevices.
 */
void InitializeDevices( void )
{
    VECU_SystemClock_Init();
}

/**
 * Initialize the VECU
 *
 * This function is called by OS_MAIN (see main.c) before the AUTOSAR-OS
 * is started.
 */
extern "C" void TargetInit(void)
{
   /* Prepare the target. */
   VECU_SystemClock_Start();
}

/**
 * Enable Interrupts.
 *
 * This function is called by the OS Startup Hook (see OS_Hooks.c). The
 * interrupts are enabled by sending a vrtaAction the ICU-Manager.
 */
extern "C" void TargetEnableInterrupts( void )
{
   vrtaAction action;

   action.devID         = ICU_DEVICE_ID;
   action.devAction     = ICU_ACTION_ID_Unmask;
   action.devActionLen  = sizeof(action.devEmbeddedData.uVal);
   action.devActionData = NULL;

   for ( unsigned int i = 1; i < 32; ++i )
   {
      action.devEmbeddedData.uVal = i;
      vrtaSendAction( ICU_DEVICE_ID, &action );
   }
}

/**
 * Get value of VECU System Clock counter
 *
 * @return Number of ticks
 */
extern "C" TargetClockType TargetReadClock( void )
{
   return VECU_SystemClock_GetValue();
}
