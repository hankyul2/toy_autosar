/** \file         Compiler_Cfg.h
  *
  * \brief        System-wide compiler configuration settings for ISOLAR-EVE ( target platform: VRTA-ux/VRTA-win )
  *
  * [$crn:2007:dox
  * \copyright Copyright 2014 ETAS GmbH
  * $]
  *
  * \note         PLATFORM DEPENDENT [yes/no]: yes
  *
  * \note         TO BE CHANGED BY USER [yes/no]: yes
  *
  * $Id: Compiler_Cfg.h 2379 2014-08-10 12:55:57Z pin9fe $
  */


#ifndef COMPILER_CFG_H
#define COMPILER_CFG_H

/* 
 * Compiler_Cfg.c is normally a system-wide header file.
 * Typically the system integrator will take the settings
 * from each module and construct this by hand. 
 * The contents of "Os_Compiler_Cfg.h" can be used by
 * the system integrator for this purpose.
 */
#include <Os_Compiler_Cfg.h>

/*
 *******************************************************************************
 * Compiler dependent macro for unused parameter to avoid compiler warnings.
 *
 * Usage:   PARAM_UNUSED(xNotUsed_u16)
 *
 *          for structures:
 *          PARAM_UNUSED(&xNotUsed_s)
 *
 *******************************************************************************
*/
#ifndef PARAM_UNUSED
    #define PARAM_UNUSED(param) if ((param) != 0) {}
#endif

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/


/*******************************************************************************
**                      Configuration data                                    **
*******************************************************************************/
/*
 * The following memory and pointer classes can be configured per module.
 * Those defines are passed to the compiler abstraction macros in Compiler.h
 *
 * Note:
 * On 32bit platforms these macros have to be empty definitions!
 */

/* -------------------------------------------------------------------------- */
/*                      General Data pointer                                  */
/* -------------------------------------------------------------------------- */

#define COMSTACK_GENERAL_PTR    /* Data are treated read-only, but may be in ROM or RAM */
#define AUTOSAR_COMSTACKDATA    /* Distance of pointers of SduDataPtr in PduInfoType */

/* -------------------------------------------------------------------------- */
/*                    RTE (Run-time Environment)                              */
/* -------------------------------------------------------------------------- */

#define RTE_CONST               /* RTE Generated constant */
#define RTE_DATA                /* RTE Generated data */
#define RTE_CODE                /* RTE Generated code */

#define RTE_LIBCODE             /* RTE library code */

#define RTE_APPL_CONST          /* RTE access to application constants */
#define RTE_APPL_DATA           /* RTE access to application data */
#define RTE_APPL_CODE           /* RTE access to application code */

#define RTE_OS_CDATA            /* OS constant data used by RTE */

/* -------------------------------------------------------------------------- */
/*                                    ECUM                                    */
/* -------------------------------------------------------------------------- */

#define ECUM_CODE               /* module functions         */
#define EcuM_CODE               /* module functions         */
#define ECUM_VAR_NOINIT         /* uninitialized variables */
#define ECUM_VAR_FAST           /* variables requiring bitwise or frequent access */
#define ECUM_VAR                /* global/static variables initialized after reset */
#define ECUM_CONST              /* module constants            */
#define ECUM_APPL_DATA          /* pointers to application data passed via API */
#define ECUM_APPL_CONST         /* application constants passed via API */
#define ECUM_APPL_CODE          /* pointers to application functions - callbacks */
#define ECUM_FAR                /* Data provided by another layer. COM never modifies the
								   data, but the data may be in either ROM or RAM */
/* -------------------------------------------------------------------------- */
/*                                    Fee                                    */
/* -------------------------------------------------------------------------- */

#define FEE_CODE               /* module functions         */
#define FEE_VAR_NOINIT         /* uninitialized variables */
#define FEE_VAR_FAST           /* variables requiring bitwise or frequent access */
#define FEE_VAR                /* global/static variables initialized after reset */
#define FEE_CONST              /* module consts            */
#define FEE_APPL_DATA          /* pointers to application data passed via API */
#define FEE_APPL_CONST         /* application constants passed via API */
#define FEE_APPL_CODE          /* pointers to application functions - callbacks */
#define FEE_FAR                /* Data provided by another layer. COM never modifies the data, but the data may be in either ROM or RAM */


/* -------------------------------------------------------------------------- */
/*                                    SCHM                                    */
/* -------------------------------------------------------------------------- */

#define SCHM_CODE               /* module functions         */
#define SCHM_VAR_NOINIT         /* uninitialized variables */
#define SCHM_VAR_FAST           /* variables requiring bitwise or frequent access */
#define SCHM_VAR                /* global/static variables initialized after reset */
#define SCHM_CONST              /* module constants            */
#define SCHM_APPL_DATA          /* pointers to application data passed via API */
#define SCHM_APPL_CONST         /* application constants passed via API */
#define SCHM_APPL_CODE          /* pointers to application functions - callbacks */
#define SCHM_FAR                /* Data provided by another layer. COM never modifies the
                                   data, but the data may be in either ROM or RAM */

/* -------------------------------------------------------------------------- */
/*                                    WDGM                                    */
/* -------------------------------------------------------------------------- */

#define WDGM_CODE               /* module functions         */
#define WDGM_VAR_NOINIT         /* uninitialized variables */
#define WDGM_VAR_FAST           /* variables requiring bitwise or frequent access */
#define WDGM_VAR                /* global/static variables initialized after reset */
#define WDGM_CONST              /* module constants            */
#define WDGM_APPL_DATA          /* pointers to application data passed via API */
#define WDGM_APPL_CONST         /* application constants passed via API */
#define WDGM_APPL_CODE          /* pointers to application functions - callbacks */
#define WDGM_FAR                /* Data provided by another layer. COM never modifies the
                                   data, but the data may be in either ROM or RAM */

/* -------------------------------------------------------------------------- */
/*                                    COM                                     */
/* -------------------------------------------------------------------------- */

#define COM_CODE                /* module functions         */
#define COM_VAR_NOINIT          /* uninitialized variables */
#define COM_VAR_FAST            /* variables requiring bitwise or frequent access */
#define COM_VAR                 /* global/static variables initialized after reset */
#define COM_CONST               /* module constants            */
#define COM_APPL_DATA           /* pointers to application data passed via API */
#define COM_APPL_CONST          /* application constants passed via API */
#define COM_APPL_CODE           /* pointers to application functions - callbacks */
#define COM_FAR                 /* Data provided by another layer. COM never modifies the
                                   data, but the data may be in either ROM or RAM */

/* -------------------------------------------------------------------------- */
/*                             PduR (Pdu Router)                              */
/* -------------------------------------------------------------------------- */

#define PDUR_CODE               /* Code */
#define PDUR_VAR_NOINIT         /* Globals or statics which are never initialized. */
#define PDUR_VAR_POWER_ON_INIT  /* Globals or statics which are initialized after PO reset. */
#define PDUR_VAR_FAST           /* Globals or statics which require fast or bitwise access. */
#define PDUR_VAR                /* Globals or statics which are initialized after every reset. */
#define PDUR_CONST              /* Global or static constants. */
#define PDUR_APPL_DATA          /* Distance of pointers (passed via API) to application data. */
#define PDUR_APPL_CONST         /* Distance of pointers (passed via API) to application constants. */
#define PDUR_APPL_CODE          /* Distance of pointers (passed via API) to application functions. */

/* -------------------------------------------------------------------------- */
/*                               CAN Interface                                */
/* -------------------------------------------------------------------------- */

#define CANIF_CODE              /* Code */
#define CANIF_VAR_NOINIT         /* Globals or statics which are never initialized. */
#define CANIF_VAR_POWER_ON_INIT  /* Globals or statics which are initialized after PO reset. */
#define CANIF_VAR_FAST           /* Globals or statics which require fast or bitwise access. */
#define CANIF_VAR                /* Globals or statics which are initialized after every reset. */
#define CANIF_CFG_CONST          /* Configuration constants that CanIf either owns or has a
                                    pointer to */
#define CANIF_CONST              /* Global or static constants. */
#define CANIF_APPL_DATA          /* Distance of pointers (passed via API) to application data. */
#define CANIF_APPL_CONST         /* Distance of pointers (passed via API) to application constants. */
#define CANIF_APPL_CODE          /* Distance of pointers (passed via API) to application functions. */

/* -------------------------------------------------------------------------- */
/*                                 CAN Driver                                 */
/* -------------------------------------------------------------------------- */

#define CANDRV_CODE             /* Code */
#define CANDRV_CONST            /* Global or static constants. */
#define CANDRV_CFG_CONST        /* Configuration constants that CanDrv either owns or has a
                                   pointer to */
#define CANDRV_VAR              /* Global/static variables */
#define CANDRV_UPPER_READONLY   /* Data provided by an upper layer. CanDrv never modifies the
                                   data, but the data may be in either ROM or RAM */

/* -------------------------------------------------------------------------- */
/*                          FrTp (Flexray Transport Protocol                  */
/* -------------------------------------------------------------------------- */

#define FRTP_CODE               /* Code */
#define FRTP_VAR_NOINIT         /* Globals or statics which are never initialized. */
#define FRTP_VAR_POWER_ON_INIT  /* Globals or statics which are initialized after PO reset. */
#define FRTP_VAR_FAST           /* Globals or statics which require fast or bitwise access. */
#define FRTP_VAR                /* Globals or statics which are initialized after every reset. */
#define FRTP_CONST              /* Global or static constants. */
#define FRTP_APPL_DATA          /* Distance of pointers (passed via API) to application data. */
#define FRTP_APPL_CONST         /* Distance of pointers (passed via API) to application constants. */
#define FRTP_APPL_CODE          /* Distance of pointers (passed via API) to application functions. */

/* -------------------------------------------------------------------------- */
/*                          FrNm (FlexRay Network Management                  */
/* -------------------------------------------------------------------------- */

#define FRNM_CODE               /* Code section                                                     */
#define FRNM_VAR_NOINIT         /* Globals or statics which are never initialized.                  */
#define FRNM_VAR_POWER_ON_INIT  /* Globals or statics which are initialized after PO reset.         */
#define FRNM_VAR_FAST           /* Globals or statics which require fast or bitwise access.         */
#define FRNM_VAR                /* Globals or statics which are initialized after every reset.      */
#define FRNM_CONST              /* Global or static constants.                                      */
#define FRNM_APPL_DATA          /* Distance of pointers (passed via API) to application data.       */
#define FRNM_APPL_CONST         /* Distance of pointers (passed via API) to application constants.  */
#define FRNM_APPL_CODE          /* Distance of pointers (passed via API) to application functions.  */

/* -------------------------------------------------------------------------- */
/*                          Nm (Generic Network Management Interface          */
/* -------------------------------------------------------------------------- */

#define NM_CODE               /* Code section                                                       */
#define NM_VAR_NOINIT         /* Globals or statics which are never initialized.                    */
#define NM_VAR_POWER_ON_INIT  /* Globals or statics which are initialized after PO reset.           */
#define NM_VAR_FAST           /* Globals or statics which require fast or bitwise access.           */
#define NM_VAR                /* Globals or statics which are initialized after every reset.        */
#define NM_CONST              /* Global or static constants.                                        */
#define NM_APPL_DATA          /* Distance of pointers (passed via API) to application data.         */
#define NM_APPL_CONST         /* Distance of pointers (passed via API) to application constants.    */
#define NM_APPL_CODE          /* Distance of pointers (passed via API) to application functions.    */
/* -------------------------------------------------------------------------- */
/*                          NvM (Generic Non Volatile Memory)          		  */
/* -------------------------------------------------------------------------- */

#define NvM_CODE               /* Code section                                                       */
#define NvM_VAR_NOINIT         /* Globals or statics which are never initialized.                    */
#define NvM_VAR_POWER_ON_INIT  /* Globals or statics which are initialized after PO reset.           */
#define NvM_VAR_FAST           /* Globals or statics which require fast or bitwise access.           */
#define NvM_VAR                /* Globals or statics which are initialized after every reset.        */
#define NvM_CONST              /* Global or static constants.                                        */
#define NvM_APPL_DATA          /* Distance of pointers (passed via API) to application data.         */
#define NvM_APPL_CONST         /* Distance of pointers (passed via API) to application constants.    */
#define NvM_APPL_CODE          /* Distance of pointers (passed via API) to application functions.    */


/* -------------------------------------------------------------------------- */
/*                          DCM (Diagnostic Communication Manager)            */
/* -------------------------------------------------------------------------- */

#define DCM_CODE               /* Code section                                                       */
#define DCM_VAR_NOINIT         /* Globals or statics which are never initialized.                    */
#define DCM_VAR_POWER_ON_INIT  /* Globals or statics which are initialized after PO reset.           */
#define DCM_VAR_FAST           /* Globals or statics which require fast or bitwise access.           */
#define DCM_VAR                /* Globals or statics which are initialized after every reset.        */
#define DCM_CONST              /* Global or static constants.                                        */
#define DCM_APPL_DATA          /* Distance of pointers (passed via API) to application data.         */
#define DCM_APPL_CONST         /* Distance of pointers (passed via API) to application constants.    */
#define DCM_APPL_CODE          /* Distance of pointers (passed via API) to application functions.    */
#define DCM_INTERN_DATA        /* Distance of pointers to DCM internal data                          */
#define DCM_INTERN_CONST       /* Distance of pointers to DCM internal constant                      */

/* -------------------------------------------------------------------------- */
/*                          DET                                               */
/* -------------------------------------------------------------------------- */

#define DET_CODE               /* Code section                                                       */
#define DET_VAR_NOINIT         /* Globals or statics which are never initialized.                    */
#define DET_VAR_POWER_ON_INIT  /* Globals or statics which are initialized after PO reset.           */
#define DET_VAR_FAST           /* Globals or statics which require fast or bitwise access.           */
#define DET_VAR                /* Globals or statics which are initialized after every reset.        */
#define DET_CONST              /* Global or static constants.                                        */
#define DET_APPL_DATA          /* Distance of pointers (passed via API) to application data.         */
#define DET_APPL_CONST         /* Distance of pointers (passed via API) to application constants.    */
#define DET_APPL_CODE          /* Distance of pointers (passed via API) to application functions.    */
#define DET_INTERN_DATA        /* Distance of pointers to DET internal data                          */
#define DET_INTERN_CONST       /* Distance of pointers to DET internal constant                      */

/* -------------------------------------------------------------------------- */
/*                          CanTp (CAN Transport Protocol)                    */
/* -------------------------------------------------------------------------- */

#define CANTP_CODE                  /* Code */
#define CANTP_VAR_NOINIT            /* Globals or statics which are never initialized. */
#define CANTP_VAR_POWER_ON_INIT     /* Globals or statics which are initialized after PO reset. */
#define CANTP_VAR_FAST              /* Globals or statics which require fast or bitwise access. */
#define CANTP_VAR                   /* Globals or statics which are initialized after every reset. */
#define CANTP_CONST                 /* Global or static constants. */
#define CANTP_APPL_DATA             /* Distance of pointers (passed via API) to application data. */
#define CANTP_APPL_CONST            /* Distance of pointers (passed via API) to application constants. */
#define CANTP_APPL_CODE             /* Distance of pointers (passed via API) to application functions. */

/* -------------------------------------------------------------------------- */
/*                          CanNm (CAN NM)                                    */
/* -------------------------------------------------------------------------- */

#define CANNM_CODE                /* Code                                                             */
#define CANNM_VAR_NOINIT          /* Globals or statics which are never initialized.                  */
#define CANNM_VAR_POWER_ON_INIT   /* Globals or statics which are initialized after PO reset.         */
#define CANNM_VAR_FAST            /* Globals or statics which require fast or bitwise access.         */
#define CANNM_VAR                 /* Globals or statics which are initialized after every reset.      */
#define CANNM_CONST               /* Global or static constants.                                      */
#define CANNM_APPL_DATA           /* Distance of pointers (passed via API) to application data.       */
#define CANNM_APPL_CONST          /* Distance of pointers (passed via API) to application constants.  */
#define CANNM_APPL_CODE           /* Distance of pointers (passed via API) to application functions.  */

/* -------------------------------------------------------------------------- */
/*            LIN Module                                                      */
/* -------------------------------------------------------------------------- */

#define LIN_CODE                  /* Code                                                             */
#define LIN_VAR_NOINIT            /* Globals or statics which are never initialized.                  */
#define LIN_VAR_POWER_ON_INIT     /* Globals or statics which are initialized after PO reset.         */
#define LIN_VAR_FAST              /* Globals or statics which require fast or bitwise access.         */
#define LIN_VAR                   /* Globals or statics which are initialized after every reset.      */
#define LIN_CONST                 /* Global or static constants.                                      */
#define LIN_APPL_DATA             /* Distance of pointers (passed via API) to application data.       */
#define LIN_APPL_CONST            /* Distance of pointers (passed via API) to application constants.  */
#define LIN_APPL_CODE             /* Distance of pointers (passed via API) to application functions.  */

/* -------------------------------------------------------------------------- */
/*             LIN INTERFACE                                                  */
/* -------------------------------------------------------------------------- */

#define LINIF_CODE                /* Code                                                             */
#define LINIF_VAR_NOINIT          /* Globals or statics which are never initialized.                  */
#define LINIF_VAR_POWER_ON_INIT   /* Globals or statics which are initialized after PO reset.         */
#define LINIF_VAR_FAST            /* Globals or statics which require fast or bitwise access.         */
#define LINIF_VAR                 /* Globals or statics which are initialized after every reset.      */
#define LINIF_CONST               /* Global or static constants.                                      */
#define LINIF_APPL_DATA           /* Distance of pointers (passed via API) to application data.       */
#define LINIF_APPL_CONST          /* Distance of pointers (passed via API) to application constants.  */
#define LINIF_APPL_CODE           /* Distance of pointers (passed via API) to application functions.  */

/* -------------------------------------------------------------------------- */
/*             FLEXRAY STATE MANAGER                                          */
/* -------------------------------------------------------------------------- */

#define FRSM_CODE                /* Code                                                             */
#define FRSM_VAR_NOINIT          /* Globals or statics which are never initialized.                  */
#define FRSM_VAR_POWER_ON_INIT   /* Globals or statics which are initialized after PO reset.         */
#define FRSM_VAR_FAST            /* Globals or statics which require fast or bitwise access.         */
#define FRSM_VAR                 /* Globals or statics which are initialized after every reset.      */
#define FRSM_CONST               /* Global or static constants.                                      */
#define FRSM_APPL_DATA           /* Distance of pointers (passed via API) to application data.       */
#define FRSM_APPL_CONST          /* Distance of pointers (passed via API) to application constants.  */
#define FRSM_APPL_CODE           /* Distance of pointers (passed via API) to application functions.  */


/* -------------------------------------------------------------------------- */
/*                                    COMM                                     */
/* -------------------------------------------------------------------------- */

#define COMM_CODE                /* module functions         */
#define COMM_VAR_NOINIT          /* uninitialized variables */
#define COMM_VAR_FAST            /* variables requiring bitwise or frequent access */
#define COMM_VAR                 /* global/static variables initialized after reset */
#define COMM_CONST               /* module constants            */
#define COMM_APPL_DATA           /* pointers to application data passed via API */
#define COMM_APPL_CONST          /* application constants passed via API */
#define COMM_APPL_CODE           /* pointers to application functions - callbacks */
#define COMM_FAR                 /* Data provided by another layer. COM never modifies the data, but the data may be in either ROM or RAM */

/* -------------------------------------------------------------------------- */
/*                                    FlexRay Interface                                     */
/* -------------------------------------------------------------------------- */

#define FRIF_CODE                /* module functions         */
#define FRIF_VAR_NOINIT          /* uninitialized variables */
#define FRIF_VAR_FAST            /* variables requiring bitwise or frequent access */
#define FRIF_VAR                 /* global/static variables initialized after reset */
#define FRIF_CONST               /* module consts            */
#define FRIF_APPL_DATA           /* pointers to application data passed via API */
#define FRIF_APPL_CONST          /* application constants passed via API */
#define FRIF_APPL_CODE           /* pointers to application functions - callbacks */
#define FRIF_FAR                 /* Data provided by another layer. COM never modifies the data, but the data may be in either ROM or RAM */

/* -------------------------------------------------------------------------- */
/*                                    Can State Manager                                     */
/* -------------------------------------------------------------------------- */

#define CANSM_CODE                /* module functions         */
#define CANSM_VAR_NOINIT          /* uninitialized variables */
#define CANSM_VAR_FAST            /* variables requiring bitwise or frequent access */
#define CANSM_VAR                 /* global/static variables initialized after reset */
#define CANSM_CONST               /* module constants            */
#define CANSM_APPL_DATA           /* pointers to application data passed via API */
#define CANSM_APPL_CONST          /* application constants passed via API */
#define CANSM_APPL_CODE           /* pointers to application functions - callbacks */
#define CANSM_FAR                 /* Data provided by another layer. COM never modifies the data, but the data may be in either ROM or RAM */

/* -------------------------------------------------------------------------- */
/*                                    FlexRay Interface                                     */
/* -------------------------------------------------------------------------- */

#define FR_CODE                /* module functions         */
#define FR_VAR_NOINIT          /* uninitialized variables */
#define FR_VAR_FAST            /* variables requiring bitwise or frequent access */
#define FR_VAR                 /* global/static variables initialized after reset */
#define FR_CONST               /* module consts            */
#define FR_APPL_DATA           /* pointers to application data passed via API */
#define FR_APPL_CONST          /* application constants passed via API */
#define FR_APPL_CODE           /* pointers to application functions - callbacks */
#define FR_FAR                 /* Data provided by another layer. COM never modifies the data, but the data may be in either ROM or RAM */

/* -------------------------------------------------------------------------- */
/*                          IPduM (IPdu Multiplexer)                          */
/* -------------------------------------------------------------------------- */

#define IPDUM_CODE                /* Code                                                             */
#define IPDUM_CONST               /* Global or static constants.                                      */
#define IPDUM_APPL_DATA           /* Distance of pointers (passed via API) to application data.       */
#define IPDUM_APPL_CONST          /* Distance of pointers (passed via API) to application constants.  */
#define IPDUM_APPL_CODE           /* Distance of pointers (passed via API) to application functions.  */
#define IPDUM_VAR_NOINIT          /* Globals or statics which are never initialized.                  */
#define IPDUM_VAR_POWER_ON_INIT   /* Globals or statics which are initialized after PO reset.         */
#define IPDUM_VAR_FAST            /* Globals or statics which require fast or bitwise access.         */
#define IPDUM_VAR                 /* Globals or statics which are initialized after every reset.      */

#endif /* COMPILER_CFG_H */
