/*
 * This is Std_Types.h for target platform: VRTA/MinGW
 *   [STD003]
 *   [STD004]
 */

#ifndef STD_TYPES_H /* [STD014] */
#define STD_TYPES_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include <Platform_Types.h>             /* platform specific type definitions */
#include <Compiler.h>                   /* mapping compiler specific keywords */

/* File version information */
#define STD_MAJOR_VERSION  (4U)
#define STD_MINOR_VERSION  (0U)
#define STD_PATCH_VERSION  (3U)
#define STD_TYPES_AR_RELEASE_MAJOR_VERSION  (4U)
#define STD_TYPES_AR_RELEASE_MINOR_VERSION  (0U)
#define STD_TYPES_AR_RELEASE_REVISION_VERSION  (3U)

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/
typedef uint8 Std_ReturnType;

typedef struct {
   uint16 vendorID;
   uint16 moduleID;
   uint8  sw_major_version;
   uint8  sw_minor_version;
   uint8  sw_patch_version;
} Std_VersionInfoType; /* [STD015] */

#ifndef STATUSTYPEDEFINED
  #define STATUSTYPEDEFINED
  #define E_OK 0x00U
  typedef unsigned char StatusType; /* OSEK compliance */
#endif
#define E_NOT_OK 0x01U

#define STD_HIGH    0x01U  /* Physical state 5V or 3.3V */
#define STD_LOW     0x00U  /* Physical state 0V */

#define STD_ACTIVE  0x01U  /* Logical state active */
#define STD_IDLE    0x00U  /* Logical state idle */

#define STD_ON      0x01U
#define STD_OFF     0x00U

#endif /* STD_TYPES_H */
