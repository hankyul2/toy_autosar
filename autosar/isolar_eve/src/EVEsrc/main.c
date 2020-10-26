/** \file         main.c
  *
  * \brief        Main loop for ISOLAR-EVE ( target platform: VRTA-ux/VRTA-win )
  *
  * [$crn:2007:dox
  * \copyright Copyright 2014 ETAS GmbH
  * $]
  *
  * \note         PLATFORM DEPENDENT [yes/no]: yes
  *
  * \note         TO BE CHANGED BY USER [yes/no]: no
  *
  * $Id: main.c 2379 2014-08-10 12:55:57Z pin9fe $
  */

#include "Std_Types.h"
#include "Main_Cfg.h"
#include "target.h"
#include "Os.h"

#ifdef USES_BSW
#   include "EcuM.h"
#endif

void StartAUTOSAR()
{
#ifdef USES_BSW
    /* Call Autosar EcuM_Init() */
    EcuM_Init();
#else
    StartOS(OSDEFAULTAPPMODE);
#endif
}

OS_MAIN()
{
#ifdef VRTA_ux
    char *argv[] = { "VECU" };
    rtos_init(1, argv);
#endif
    TargetInit();
    StartAUTOSAR();
}
