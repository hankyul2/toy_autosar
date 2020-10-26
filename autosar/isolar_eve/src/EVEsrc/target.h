/** \file         target.h
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
  * $Id: target.h 2379 2014-08-10 12:55:57Z pin9fe $
  */

#ifndef __TARGET_H__
#define __TARGET_H__

#include "Rte_Type.h"
#include "vrtaTypes.h"

typedef vrtaUInt TargetClockType;

#ifdef __cplusplus
extern "C" {
#endif

void TargetInit(void);
void TargetEnableInterrupts(void);
TargetClockType TargetReadClock( void );

#ifdef __cplusplus
}
#endif

#endif /*__TARGET_H__*/
