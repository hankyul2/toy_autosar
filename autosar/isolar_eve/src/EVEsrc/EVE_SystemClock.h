/** \file         EVE_SystemClock.h
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
  * $Id: EVE_SystemClock.h 5460 2014-08-14 13:20:09Z sui9fe $
  */

#include "vrtaCore.h"
 
#ifdef __cplusplus
extern "C" {
#endif
 
void VECU_SystemClock_Init();
void VECU_SystemClock_Start();

vrtaUInt VECU_SystemClock_GetValue();


#ifdef __cplusplus
}
#endif
