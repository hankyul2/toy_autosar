/** \file         BSWTasks.c
  *
  * \brief        Default task definitions for ISOLAR-EVE ( target platform: VRTA-ux/VRTA-win )
  *
  * [$crn:2007:dox
  * \copyright Copyright 2014 ETAS GmbH
  * $]
  *
  * \note         PLATFORM DEPENDENT [yes/no]: yes
  *
  * \note         TO BE CHANGED BY USER [yes/no]: yes
  *
  * $Id: BswTasks.c 2379 2014-08-10 12:55:57Z pin9fe $
  */

#include "Os_EVE.h"
#include "Main_Cfg.h"

#ifdef BSW_WITH_CAN
#   include "Com.h"
#   include "CanIf.h"
#   include "ComM.h"
#endif

#ifdef USES_BSW
#   include "EcuM.h"
#endif

#ifdef BSW_WITH_COMM
#   include "ComM.h"
#endif

#ifdef BSW_WITH_NVM
#  include "NvM.h"
#  include "fee.h"
#  include "MemIf.h"
#endif

#ifdef DEFAULT_BSW_TASK
EVE_TASK(DEFAULT_BSW_TASK)
{
    /* Typical BSW module sequence for CAN.
       Modify depending on which modules have been configured.
     */
#ifdef BSW_WITH_CAN
    Can_MainFunction_Read();
#endif

    EcuM_MainFunction();

#ifdef BSW_WITH_CAN
    CanSM_MainFunction();
#endif

#ifdef BSW_WITH_COMM
    ComM_MainFunction_0();
#endif

#ifdef BSW_WITH_CAN
    Com_MainFunctionTx();
    Com_MainFunctionRx();
    Can_MainFunction_Write();
#endif

#ifdef BSW_WITH_NVM
    NvM_MainFunction();
    Fee_MainFunction();
#endif
    TerminateTask();
}
#endif

#ifdef DEFAULT_BSW_INIT
EVE_TASK(DEFAULT_BSW_INIT)
{
    /* Typical BSW module initialization sequence for COM.
       Modify depending on which modules etc. have been configured.
     */
	/* Example of initialization of COM Ipud groups. */

	/* Com_IpduGroupVector Vector_IPduGrpVctr;
    Com_ClearIpduGroupVector(Vector_IPduGrpVctr);
    Com_SetIpduGroup(Vector_IPduGrpVctr, 0, TRUE);
    Com_SetIpduGroup(Vector_IPduGrpVctr, 1, TRUE);
    Com_IpduGroupControl(Vector_IPduGrpVctr, TRUE); */

#ifdef BSW_WITH_COMM
    (void)ComM_RequestComMode(VECU_COMMUSER, COMM_FULL_COMMUNICATION);
    ComM_CommunicationAllowed(VECU_COMMCHANNEL,TRUE);
#endif
    TerminateTask();
}
#endif


