/*----------------------------------------------------------------------------*/
/************** *SAMPLE* of MemMap.h. Not for production purposes *************/
/*----------------------------------------------------------------------------*/
#define MEM_VENDOR_ID        (11U)
#define MEM_AR_MAJOR_VERSION (4U)
#define MEM_AR_MINOR_VERSION (0U)
#define MEM_AR_PATCH_VERSION (3U)
#define MEM_SW_MAJOR_VERSION (5U)
#define MEM_SW_MINOR_VERSION (4U)
#define MEM_SW_PATCH_VERSION (4U)

/* -------------------------------------------------------------------------- */
/*             OS (Operating System)                                          */
/* -------------------------------------------------------------------------- */
#include <Os_MemMap.h>

/*******************************************************************************
**                      Default section mapping                               **
*******************************************************************************/
#if defined (START_WITH_IF)

/* -------------------------------------------------------------------------- */
/* RAM variables not initialized                                              */
/* -------------------------------------------------------------------------- */
#elif defined (DEFAULT_START_SEC_VAR_NOINIT_BOOLEAN)
  #undef      DEFAULT_START_SEC_VAR_NOINIT_BOOLEAN
#elif defined (DEFAULT_STOP_SEC_VAR_NOINIT_BOOLEAN)
  #undef      DEFAULT_STOP_SEC_VAR_NOINIT_BOOLEAN

#elif defined (DEFAULT_START_SEC_VAR_NOINIT_8BIT)
  #undef      DEFAULT_START_SEC_VAR_NOINIT_8BIT
#elif defined (DEFAULT_STOP_SEC_VAR_NOINIT_8BIT)
  #undef      DEFAULT_STOP_SEC_VAR_NOINIT_8BIT

#elif defined (DEFAULT_START_SEC_VAR_NOINIT_16BIT)
  #undef      DEFAULT_START_SEC_VAR_NOINIT_16BIT
#elif defined (DEFAULT_STOP_SEC_VAR_NOINIT_16BIT)
  #undef      DEFAULT_STOP_SEC_VAR_NOINIT_16BIT

#elif defined (DEFAULT_START_SEC_VAR_NOINIT_32BIT)
  #undef      DEFAULT_START_SEC_VAR_NOINIT_32BIT
#elif defined (DEFAULT_STOP_SEC_VAR_NOINIT_32BIT)
  #undef      DEFAULT_STOP_SEC_VAR_NOINIT_32BIT

#elif defined (DEFAULT_START_SEC_VAR_NOINIT_UNSPECIFIED)
  #undef      DEFAULT_START_SEC_VAR_NOINIT_UNSPECIFIED
#elif defined (DEFAULT_STOP_SEC_VAR_NOINIT_UNSPECIFIED)
  #undef      DEFAULT_STOP_SEC_VAR_NOINIT_UNSPECIFIED

/* -------------------------------------------------------------------------- */
/* RAM variables power-on initialized                                         */
/* -------------------------------------------------------------------------- */
#elif defined (DEFAULT_START_SEC_VAR_POWER_ON_INIT_BOOLEAN)
  #undef      DEFAULT_START_SEC_VAR_POWER_ON_INIT_BOOLEAN
#elif defined (DEFAULT_STOP_SEC_VAR_POWER_ON_INIT_BOOLEAN)
  #undef      DEFAULT_STOP_SEC_VAR_POWER_ON_INIT_BOOLEAN

#elif defined (DEFAULT_START_SEC_VAR_POWER_ON_INIT_8BIT)
  #undef      DEFAULT_START_SEC_VAR_POWER_ON_INIT_8BIT
#elif defined (DEFAULT_STOP_SEC_VAR_POWER_ON_INIT_8BIT)
  #undef      DEFAULT_STOP_SEC_VAR_POWER_ON_INIT_8BIT

#elif defined (DEFAULT_START_SEC_VAR_POWER_ON_INIT_16BIT)
  #undef      DEFAULT_START_SEC_VAR_POWER_ON_INIT_16BIT
#elif defined (DEFAULT_STOP_SEC_VAR_POWER_ON_INIT_16BIT)
  #undef      DEFAULT_STOP_SEC_VAR_POWER_ON_INIT_16BIT

#elif defined (DEFAULT_START_SEC_VAR_POWER_ON_INIT_32BIT)
  #undef      DEFAULT_START_SEC_VAR_POWER_ON_INIT_32BIT
#elif defined (DEFAULT_STOP_SEC_VAR_POWER_ON_INIT_32BIT)
  #undef      DEFAULT_STOP_SEC_VAR_POWER_ON_INIT_32BIT

#elif defined (DEFAULT_START_SEC_VAR_POWER_ON_INIT_UNSPECIFIED)
  #undef      DEFAULT_START_SEC_VAR_POWER_ON_INIT_UNSPECIFIED
#elif defined (DEFAULT_STOP_SEC_VAR_POWER_ON_INIT_UNSPECIFIED)
  #undef      DEFAULT_STOP_SEC_VAR_POWER_ON_INIT_UNSPECIFIED

/* -------------------------------------------------------------------------- */
/* RAM variables initialized from ROM on reset                                */
/* -------------------------------------------------------------------------- */
#elif defined (DEFAULT_START_SEC_VAR_BOOLEAN)
  #undef      DEFAULT_START_SEC_VAR_BOOLEAN
#elif defined (DEFAULT_STOP_SEC_VAR_BOOLEAN)
  #undef      DEFAULT_STOP_SEC_VAR_BOOLEAN

#elif defined (DEFAULT_START_SEC_VAR_8BIT)
  #undef      DEFAULT_START_SEC_VAR_8BIT
#elif defined (DEFAULT_STOP_SEC_VAR_8BIT)
  #undef      DEFAULT_STOP_SEC_VAR_8BIT

#elif defined (DEFAULT_START_SEC_VAR_16BIT)
  #undef      DEFAULT_START_SEC_VAR_16BIT
#elif defined (DEFAULT_STOP_SEC_VAR_16BIT)
  #undef      DEFAULT_STOP_SEC_VAR_16BIT

#elif defined (DEFAULT_START_SEC_VAR_32BIT)
  #undef      DEFAULT_START_SEC_VAR_32BIT
#elif defined (DEFAULT_STOP_SEC_VAR_32BIT)
  #undef      DEFAULT_STOP_SEC_VAR_32BIT

#elif defined (DEFAULT_START_SEC_VAR_UNSPECIFIED)
  #undef      DEFAULT_START_SEC_VAR_UNSPECIFIED
#elif defined (DEFAULT_STOP_SEC_VAR_UNSPECIFIED)
  #undef      DEFAULT_STOP_SEC_VAR_UNSPECIFIED

/* -------------------------------------------------------------------------- */
/* RAM variables frequently used or accessed bitwise                          */
/* -------------------------------------------------------------------------- */
#elif defined (DEFAULT_START_SEC_VAR_FAST_BOOLEAN)
  #undef      DEFAULT_START_SEC_VAR_FAST_BOOLEAN
#elif defined (DEFAULT_STOP_SEC_VAR_FAST_BOOLEAN)
  #undef      DEFAULT_STOP_SEC_VAR_FAST_BOOLEAN

#elif defined (DEFAULT_START_SEC_VAR_FAST_8BIT)
  #undef      DEFAULT_START_SEC_VAR_FAST_8BIT
#elif defined (DEFAULT_STOP_SEC_VAR_FAST_8BIT)
  #undef      DEFAULT_STOP_SEC_VAR_FAST_8BIT

#elif defined (DEFAULT_START_SEC_VAR_FAST_16BIT)
  #undef      DEFAULT_START_SEC_VAR_FAST_16BIT
#elif defined (DEFAULT_STOP_SEC_VAR_FAST_16BIT)
  #undef      DEFAULT_STOP_SEC_VAR_FAST_16BIT

#elif defined (DEFAULT_START_SEC_VAR_FAST_32BIT)
  #undef      DEFAULT_START_SEC_VAR_FAST_32BIT
#elif defined (DEFAULT_STOP_SEC_VAR_FAST_32BIT)
  #undef      DEFAULT_STOP_SEC_VAR_FAST_32BIT

#elif defined (DEFAULT_START_SEC_VAR_FAST_UNSPECIFIED)
  #undef      DEFAULT_START_SEC_VAR_FAST_UNSPECIFIED
#elif defined (DEFAULT_STOP_SEC_VAR_FAST_UNSPECIFIED)
  #undef      DEFAULT_STOP_SEC_VAR_FAST_UNSPECIFIED

/* -------------------------------------------------------------------------- */
/* ROM constants                                                              */
/* -------------------------------------------------------------------------- */
#elif defined (DEFAULT_START_SEC_CONST_BOOLEAN)
  #undef      DEFAULT_START_SEC_CONST_BOOLEAN
#elif defined (DEFAULT_STOP_SEC_CONST_BOOLEAN)
  #undef      DEFAULT_STOP_SEC_CONST_BOOLEAN

#elif defined (DEFAULT_START_SEC_CONST_8BIT)
  #undef      DEFAULT_START_SEC_CONST_8BIT
#elif defined (DEFAULT_STOP_SEC_CONST_8BIT)
  #undef      DEFAULT_STOP_SEC_CONST_8BIT

#elif defined (DEFAULT_START_SEC_CONST_16BIT)
  #undef      DEFAULT_START_SEC_CONST_16BIT
#elif defined (DEFAULT_STOP_SEC_CONST_16BIT)
  #undef      DEFAULT_STOP_SEC_CONST_16BIT

#elif defined (DEFAULT_START_SEC_CONST_32BIT)
  #undef      DEFAULT_START_SEC_CONST_32BIT
#elif defined (DEFAULT_STOP_SEC_CONST_32BIT)
  #undef      DEFAULT_STOP_SEC_CONST_32BIT

#elif defined (DEFAULT_START_SEC_CONST_FAST_UNSPECIFIED)
  #undef      DEFAULT_START_SEC_CONST_FAST_UNSPECIFIED
#elif defined (DEFAULT_STOP_SEC_CONST_FAST_UNSPECIFIED)
  #undef      DEFAULT_STOP_SEC_CONST_FAST_UNSPECIFIED

#elif defined (DEFAULT_START_SEC_CONST_UNSPECIFIED)
  #undef      DEFAULT_START_SEC_CONST_UNSPECIFIED
#elif defined (DEFAULT_STOP_SEC_CONST_UNSPECIFIED)
  #undef      DEFAULT_STOP_SEC_CONST_UNSPECIFIED

/* -------------------------------------------------------------------------- */
/* ROM FAR constants                                                          */
/* -------------------------------------------------------------------------- */
#elif defined (DEFAULT_START_SEC_CONST_BOOLEAN_FAR)
  #undef      DEFAULT_START_SEC_CONST_BOOLEAN_FAR
#elif defined (DEFAULT_STOP_SEC_CONST_BOOLEAN_FAR)
  #undef      DEFAULT_STOP_SEC_CONST_BOOLEAN_FAR

#elif defined (DEFAULT_START_SEC_CONST_8BIT_FAR)
  #undef      DEFAULT_START_SEC_CONST_8BIT_FAR
#elif defined (DEFAULT_STOP_SEC_CONST_8BIT_FAR)
  #undef      DEFAULT_STOP_SEC_CONST_8BIT_FAR

#elif defined (DEFAULT_START_SEC_CONST_16BIT_FAR)
  #undef      DEFAULT_START_SEC_CONST_16BIT_FAR
#elif defined (DEFAULT_STOP_SEC_CONST_16BIT_FAR)
  #undef      DEFAULT_STOP_SEC_CONST_16BIT_FAR

#elif defined (DEFAULT_START_SEC_CONST_32BIT_FAR)
  #undef      DEFAULT_START_SEC_CONST_32BIT_FAR
#elif defined (DEFAULT_STOP_SEC_CONST_32BIT_FAR)
  #undef      DEFAULT_STOP_SEC_CONST_32BIT_FAR

#elif defined (DEFAULT_START_SEC_CONST_UNSPECIFIED_FAR)
  #undef      DEFAULT_START_SEC_CONST_UNSPECIFIED_FAR
#elif defined (DEFAULT_STOP_SEC_CONST_UNSPECIFIED_FAR)
  #undef      DEFAULT_STOP_SEC_CONST_UNSPECIFIED_FAR

/* -------------------------------------------------------------------------- */
/* ROM code                                                                   */
/* -------------------------------------------------------------------------- */
#elif defined (DEFAULT_START_SEC_CODE)
  #undef      DEFAULT_START_SEC_CODE
#elif defined (DEFAULT_STOP_SEC_CODE)
  #undef      DEFAULT_STOP_SEC_CODE

#elif defined (DEFAULT_START_SEC_CODE_FAST)
  #undef      DEFAULT_START_SEC_CODE_FAST
#elif defined (DEFAULT_STOP_SEC_CODE_FAST)
  #undef      DEFAULT_STOP_SEC_CODE_FAST

#elif defined (DEFAULT_START_SEC_CODE_SLOW)
  #undef      DEFAULT_START_SEC_CODE_SLOW
#elif defined (DEFAULT_STOP_SEC_CODE_SLOW)
  #undef      DEFAULT_STOP_SEC_CODE_SLOW

#elif defined (DEFAULT_START_SEC_CODE_LIB)
  #undef      DEFAULT_START_SEC_CODE_LIB
#elif defined (DEFAULT_STOP_SEC_CODE_LIB)
  #undef      DEFAULT_STOP_SEC_CODE_LIB

#elif defined (DEFAULT_START_SEC_VECTORS)
  #undef      DEFAULT_START_SEC_VECTORS
#elif defined (DEFAULT_STOP_SEC_VECTORS)
  #undef      DEFAULT_STOP_SEC_VECTORS

#else

/* -------------------------------------------------------------------------- */
/* End of default section mapping                                             */
/* -------------------------------------------------------------------------- */
#endif  /* START_WITH_IF */

/*** End of file **************************************************************/
