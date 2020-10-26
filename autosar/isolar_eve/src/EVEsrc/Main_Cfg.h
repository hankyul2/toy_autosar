/** \file         Main_Cfg.h
  *
  * \brief        General settings (BSW, XCP) for ISOLAR-EVE ( target platform: VRTA-ux/VRTA-win )
  *
  * [$crn:2007:dox
  * \copyright Copyright 2014 ETAS GmbH
  * $]
  *
  * \note         PLATFORM DEPENDENT [yes/no]: yes
  *
  * \note         TO BE CHANGED BY USER [yes/no]: yes
  *
  * $Id: Main_Cfg.h 2379 2014-08-10 12:55:57Z pin9fe $
  */

#ifndef __MAIN_CFG_H__
#define __MAIN_CFG_H__

/* ------------------------------------------------------------
 * Global settings that you may need to adapt according to your
 * AUTOSAR and OS configuration.
 * ------------------------------------------------------------
 */


/* VECU System Clock Periode:
 * Duration of one Clock cycle in milli seconds.
 */
#define VECU_SYSTEMCLOCK_PERIOD 1

/* Number of the VRTA interrupt used by the VECU System Clock
 * (see VECU_SystemClock.cpp). This must match the interrupt number
 * specified in your RTA OS timer configuration (see there).
 */
#define VECU_SYSTEMCLOCK_IRQ 7

/* Name of the ISR Timer defined in the OS */
#define VECU_SYSTEMCLOCK_ISR VECU_SystemClock_ISR

/* If defined, your AUTOSAR VECU contains a BSW stack. In that
 * case, you must either configure and provide the EcuM module
 * or modify main.c accordingly.
 * Remove this #define for VECUs that only contain ASW, RTE and OS.
 */
//#define USES_BSW



#ifdef USES_BSW
/* ------------------------------------------------------------
 * BSW Modules which are configured
 * ------------------------------------------------------------
 */

/*
 * remove this #define if your VECU has no Can configuration
 * The Com functions are included
 */
#   define BSW_WITH_CAN

/*
 * remove this #define if your VECU has no ComM configuration
 */
#   define BSW_WITH_COMM

/* Default names of the ComM User and ComM Channel defined in the BSW
 * To be changed by the user accordingly.
 */
#define VECU_COMMUSER ComMConf_ComMUser_ComMUser_0
#define VECU_COMMCHANNEL ComMConf_ComMChannel_ComMChannel_0

/*
 * remove this #define if your VECU has no NvM configuration
 */
//#   define BSW_WITH_NVM


/* ------------------------------------------------------------
 * Names and activation of BSW standard task implementations.
 * Those are provided in case you don't want to specify your
 * own implementation.
 *
 * Please see BswTasks.c for additional changes that may be necessary.
 * ------------------------------------------------------------
 */

/* If defined, this will implement a cyclic BSW schedule task with
 * the specified name. The latter must match your OS configuration.
 * Please note that you must trigger the execution of this tasks,
 * e.g. specifying an Alarm in the VRTA OS configuration.
 */
#   define DEFAULT_BSW_TASK BswTask

/* If defined, this will implement a single-shot task (with the
 * specified name) used to initialize BSW modules. The name must
 * match your OS configuration.
 */
#   define DEFAULT_BSW_INIT BswInit



#endif /* USES_BSW */


#endif /*__MAIN_CFG_H__*/
