/*
 * This is Os_MemMap.h, auto-generated for:
 *   Project: AFS
 *   Target:  VRTA
 *   Variant: MinGW
 *   Version: 3.0.23
 *   It should be either copied into MemMap.h by the integrator OR #included into it.
 */
/* Generator info: generate_always */
/* This file is a sample version of Os_MemMap.h that can be used
 * as a starting template.
 * [$UKS 652] [$UKS 653] [$UKS 655] [$UKS 656] [$UKS 657]
 */
#if defined (NOT_DEFINED)

/* OS Uninitialized RAM: trace data */
#elif defined (OS_START_SEC_VAR_TRACE)
  #undef      OS_START_SEC_VAR_TRACE
  #define DEFAULT_START_SEC_VAR_NO_INIT_UNSPECIFIED
#elif defined (OS_STOP_SEC_VAR_TRACE)
  #undef      OS_STOP_SEC_VAR_TRACE
  #define DEFAULT_STOP_SEC_VAR_NO_INIT_UNSPECIFIED

/* OS Uninitialized RAM: boolean */
#elif defined (OS_START_SEC_VAR_NO_INIT_BOOLEAN)
  #undef      OS_START_SEC_VAR_NO_INIT_BOOLEAN
  #define DEFAULT_START_SEC_VAR_NO_INIT_BOOLEAN
#elif defined (OS_STOP_SEC_VAR_NO_INIT_BOOLEAN)
  #undef      OS_STOP_SEC_VAR_NO_INIT_BOOLEAN
  #define DEFAULT_STOP_SEC_VAR_NO_INIT_BOOLEAN

/* OS Uninitialized RAM: 8 bit values */
#elif defined (OS_START_SEC_VAR_NO_INIT_8)
  #undef      OS_START_SEC_VAR_NO_INIT_8
  #define DEFAULT_START_SEC_VAR_NO_INIT_8
#elif defined (OS_STOP_SEC_VAR_NO_INIT_8)
  #undef      OS_STOP_SEC_VAR_NO_INIT_8
  #define DEFAULT_STOP_SEC_VAR_NO_INIT_8

/* OS Uninitialized RAM: 16 bit values */
#elif defined (OS_START_SEC_VAR_NO_INIT_16)
  #undef      OS_START_SEC_VAR_NO_INIT_16
  #define DEFAULT_START_SEC_VAR_NO_INIT_16
#elif defined (OS_STOP_SEC_VAR_NO_INIT_16)
  #undef      OS_STOP_SEC_VAR_NO_INIT_16
  #define DEFAULT_STOP_SEC_VAR_NO_INIT_16

/* OS Uninitialized RAM: 32 bit values */
#elif defined (OS_START_SEC_VAR_NO_INIT_32)
  #undef      OS_START_SEC_VAR_NO_INIT_32
  #define DEFAULT_START_SEC_VAR_NO_INIT_32
#elif defined (OS_STOP_SEC_VAR_NO_INIT_32)
  #undef      OS_STOP_SEC_VAR_NO_INIT_32
  #define DEFAULT_STOP_SEC_VAR_NO_INIT_32

/* OS Uninitialized RAM: unspecified size */
#elif defined (OS_START_SEC_VAR_NO_INIT_UNSPECIFIED)
  #undef      OS_START_SEC_VAR_NO_INIT_UNSPECIFIED
  #define DEFAULT_START_SEC_VAR_NO_INIT_UNSPECIFIED
#elif defined (OS_STOP_SEC_VAR_NO_INIT_UNSPECIFIED)
  #undef      OS_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
  #define DEFAULT_STOP_SEC_VAR_NO_INIT_UNSPECIFIED

/* OS reset cleared RAM: boolean */
#elif defined (OS_START_SEC_VAR_CLEARED_BOOLEAN)
  #undef      OS_START_SEC_VAR_CLEARED_BOOLEAN
  #define DEFAULT_START_SEC_VAR_CLEARED_BOOLEAN
#elif defined (OS_STOP_SEC_VAR_CLEARED_BOOLEAN)
  #undef      OS_STOP_SEC_VAR_CLEARED_BOOLEAN
  #define DEFAULT_STOP_SEC_VAR_CLEARED_BOOLEAN

/* OS reset cleared RAM: 8 bit values */
#elif defined (OS_START_SEC_VAR_CLEARED_8)
  #undef      OS_START_SEC_VAR_CLEARED_8
  #define DEFAULT_START_SEC_VAR_CLEARED_8
#elif defined (OS_STOP_SEC_VAR_CLEARED_8)
  #undef      OS_STOP_SEC_VAR_CLEARED_8
  #define DEFAULT_STOP_SEC_VAR_CLEARED_8

/* OS reset cleared RAM: 16 bit values */
#elif defined (OS_START_SEC_VAR_CLEARED_16)
  #undef      OS_START_SEC_VAR_CLEARED_16
  #define DEFAULT_START_SEC_VAR_CLEARED_16
#elif defined (OS_STOP_SEC_VAR_CLEARED_16)
  #undef      OS_STOP_SEC_VAR_CLEARED_16
  #define DEFAULT_STOP_SEC_VAR_CLEARED_16

/* OS reset cleared RAM: 32 bit values */
#elif defined (OS_START_SEC_VAR_CLEARED_32)
  #undef      OS_START_SEC_VAR_CLEARED_32
  #define DEFAULT_START_SEC_VAR_CLEARED_32
#elif defined (OS_STOP_SEC_VAR_CLEARED_32)
  #undef      OS_STOP_SEC_VAR_CLEARED_32
  #define DEFAULT_STOP_SEC_VAR_CLEARED_32

/* OS reset cleared RAM: unspecified size */
#elif defined (OS_START_SEC_VAR_CLEARED_UNSPECIFIED)
  #undef      OS_START_SEC_VAR_CLEARED_UNSPECIFIED
  #define DEFAULT_START_SEC_VAR_CLEARED_UNSPECIFIED
#elif defined (OS_STOP_SEC_VAR_CLEARED_UNSPECIFIED)
  #undef      OS_STOP_SEC_VAR_CLEARED_UNSPECIFIED
  #define DEFAULT_STOP_SEC_VAR_CLEARED_UNSPECIFIED

/* OS reset initialized RAM: boolean */
#elif defined (OS_START_SEC_VAR_INIT_BOOLEAN)
  #undef      OS_START_SEC_VAR_INIT_BOOLEAN
  #define DEFAULT_START_SEC_VAR_INIT_BOOLEAN
#elif defined (OS_STOP_SEC_VAR_INIT_BOOLEAN)
  #undef      OS_STOP_SEC_VAR_INIT_BOOLEAN
  #define DEFAULT_STOP_SEC_VAR_INIT_BOOLEAN

/* OS reset initialized RAM: 8 bit values */
#elif defined (OS_START_SEC_VAR_INIT_8)
  #undef      OS_START_SEC_VAR_INIT_8
  #define DEFAULT_START_SEC_VAR_INIT_8
#elif defined (OS_STOP_SEC_VAR_INIT_8)
  #undef      OS_STOP_SEC_VAR_INIT_8
  #define DEFAULT_STOP_SEC_VAR_INIT_8

/* OS reset initialized RAM: 16 bit values */
#elif defined (OS_START_SEC_VAR_INIT_16)
  #undef      OS_START_SEC_VAR_INIT_16
  #define DEFAULT_START_SEC_VAR_INIT_16
#elif defined (OS_STOP_SEC_VAR_INIT_16)
  #undef      OS_STOP_SEC_VAR_INIT_16
  #define DEFAULT_STOP_SEC_VAR_INIT_16

/* OS reset initialized RAM: 32 bit values */
#elif defined (OS_START_SEC_VAR_INIT_32)
  #undef      OS_START_SEC_VAR_INIT_32
  #define DEFAULT_START_SEC_VAR_INIT_32
#elif defined (OS_STOP_SEC_VAR_INIT_32)
  #undef      OS_STOP_SEC_VAR_INIT_32
  #define DEFAULT_STOP_SEC_VAR_INIT_32

/* OS reset initialized RAM: unspecified size */
#elif defined (OS_START_SEC_VAR_INIT_UNSPECIFIED)
  #undef      OS_START_SEC_VAR_INIT_UNSPECIFIED
  #define DEFAULT_START_SEC_VAR_INIT_UNSPECIFIED
#elif defined (OS_STOP_SEC_VAR_INIT_UNSPECIFIED)
  #undef      OS_STOP_SEC_VAR_INIT_UNSPECIFIED
  #define DEFAULT_STOP_SEC_VAR_INIT_UNSPECIFIED

/* OS Power-on cleared RAM: boolean */
#elif defined (OS_START_SEC_VAR_POWER_ON_CLEARED_BOOLEAN)
  #undef      OS_START_SEC_VAR_POWER_ON_CLEARED_BOOLEAN
  #define DEFAULT_START_SEC_VAR_POWER_ON_CLEARED_BOOLEAN
#elif defined (OS_STOP_SEC_VAR_POWER_ON_CLEARED_BOOLEAN)
  #undef      OS_STOP_SEC_VAR_POWER_ON_CLEARED_BOOLEAN
  #define DEFAULT_STOP_SEC_VAR_POWER_ON_CLEARED_BOOLEAN

/* OS Power-on cleared RAM: 8 bit values */
#elif defined (OS_START_SEC_VAR_POWER_ON_CLEARED_8)
  #undef      OS_START_SEC_VAR_POWER_ON_CLEARED_8
  #define DEFAULT_START_SEC_VAR_POWER_ON_CLEARED_8
#elif defined (OS_STOP_SEC_VAR_POWER_ON_CLEARED_8)
  #undef      OS_STOP_SEC_VAR_POWER_ON_CLEARED_8
  #define DEFAULT_STOP_SEC_VAR_POWER_ON_CLEARED_8

/* OS Power-on cleared RAM: 16 bit values */
#elif defined (OS_START_SEC_VAR_POWER_ON_CLEARED_16)
  #undef      OS_START_SEC_VAR_POWER_ON_CLEARED_16
  #define DEFAULT_START_SEC_VAR_POWER_ON_CLEARED_16
#elif defined (OS_STOP_SEC_VAR_POWER_ON_CLEARED_16)
  #undef      OS_STOP_SEC_VAR_POWER_ON_CLEARED_16
  #define DEFAULT_STOP_SEC_VAR_POWER_ON_CLEARED_16

/* OS Power-on cleared RAM: 32 bit values */
#elif defined (OS_START_SEC_VAR_POWER_ON_CLEARED_32)
  #undef      OS_START_SEC_VAR_POWER_ON_CLEARED_32
  #define DEFAULT_START_SEC_VAR_POWER_ON_CLEARED_32
#elif defined (OS_STOP_SEC_VAR_POWER_ON_CLEARED_32)
  #undef      OS_STOP_SEC_VAR_POWER_ON_CLEARED_32
  #define DEFAULT_STOP_SEC_VAR_POWER_ON_CLEARED_32

/* OS Power-on cleared RAM: unspecified size */
#elif defined (OS_START_SEC_VAR_POWER_ON_CLEARED_UNSPECIFIED)
  #undef      OS_START_SEC_VAR_POWER_ON_CLEARED_UNSPECIFIED
  #define DEFAULT_START_SEC_VAR_POWER_ON_CLEARED_UNSPECIFIED
#elif defined (OS_STOP_SEC_VAR_POWER_ON_CLEARED_UNSPECIFIED)
  #undef      OS_STOP_SEC_VAR_POWER_ON_CLEARED_UNSPECIFIED
  #define DEFAULT_STOP_SEC_VAR_POWER_ON_CLEARED_UNSPECIFIED

/* OS Power-on initialized RAM: boolean */
#elif defined (OS_START_SEC_VAR_POWER_ON_INIT_BOOLEAN)
  #undef      OS_START_SEC_VAR_POWER_ON_INIT_BOOLEAN
  #define DEFAULT_START_SEC_VAR_POWER_ON_INIT_BOOLEAN
#elif defined (OS_STOP_SEC_VAR_POWER_ON_INIT_BOOLEAN)
  #undef      OS_STOP_SEC_VAR_POWER_ON_INIT_BOOLEAN
  #define DEFAULT_STOP_SEC_VAR_POWER_ON_INIT_BOOLEAN

/* OS Power-on initialized RAM: 8 bit values */
#elif defined (OS_START_SEC_VAR_POWER_ON_INIT_8)
  #undef      OS_START_SEC_VAR_POWER_ON_INIT_8
  #define DEFAULT_START_SEC_VAR_POWER_ON_INIT_8
#elif defined (OS_STOP_SEC_VAR_POWER_ON_INIT_8)
  #undef      OS_STOP_SEC_VAR_POWER_ON_INIT_8
  #define DEFAULT_STOP_SEC_VAR_POWER_ON_INIT_8

/* OS Power-on initialized RAM: 16 bit values */
#elif defined (OS_START_SEC_VAR_POWER_ON_INIT_16)
  #undef      OS_START_SEC_VAR_POWER_ON_INIT_16
  #define DEFAULT_START_SEC_VAR_POWER_ON_INIT_16
#elif defined (OS_STOP_SEC_VAR_POWER_ON_INIT_16)
  #undef      OS_STOP_SEC_VAR_POWER_ON_INIT_16
  #define DEFAULT_STOP_SEC_VAR_POWER_ON_INIT_16

/* OS Power-on initialized RAM: 32 bit values */
#elif defined (OS_START_SEC_VAR_POWER_ON_INIT_32)
  #undef      OS_START_SEC_VAR_POWER_ON_INIT_32
  #define DEFAULT_START_SEC_VAR_POWER_ON_INIT_32
#elif defined (OS_STOP_SEC_VAR_POWER_ON_INIT_32)
  #undef      OS_STOP_SEC_VAR_POWER_ON_INIT_32
  #define DEFAULT_STOP_SEC_VAR_POWER_ON_INIT_32

/* OS Power-on initialized RAM: unspecified size */
#elif defined (OS_START_SEC_VAR_POWER_ON_INIT_UNSPECIFIED)
  #undef      OS_START_SEC_VAR_POWER_ON_INIT_UNSPECIFIED
  #define DEFAULT_START_SEC_VAR_POWER_ON_INIT_UNSPECIFIED
#elif defined (OS_STOP_SEC_VAR_POWER_ON_INIT_UNSPECIFIED)
  #undef      OS_STOP_SEC_VAR_POWER_ON_INIT_UNSPECIFIED
  #define DEFAULT_STOP_SEC_VAR_POWER_ON_INIT_UNSPECIFIED

/* OS Initialized RAM: boolean */
#elif defined (OS_START_SEC_VAR_BOOLEAN)
  #undef      OS_START_SEC_VAR_BOOLEAN
  #define DEFAULT_START_SEC_VAR_BOOLEAN
#elif defined (OS_STOP_SEC_VAR_BOOLEAN)
  #undef      OS_STOP_SEC_VAR_BOOLEAN
  #define DEFAULT_STOP_SEC_VAR_BOOLEAN

/* OS Initialized RAM: 8 bit values */
#elif defined (OS_START_SEC_VAR_8)
  #undef      OS_START_SEC_VAR_8
  #define DEFAULT_START_SEC_VAR_8
#elif defined (OS_STOP_SEC_VAR_8)
  #undef      OS_STOP_SEC_VAR_8
  #define DEFAULT_STOP_SEC_VAR_8

/* OS Initialized RAM: 16 bit values */
#elif defined (OS_START_SEC_VAR_16)
  #undef      OS_START_SEC_VAR_16
  #define DEFAULT_START_SEC_VAR_16
#elif defined (OS_STOP_SEC_VAR_16)
  #undef      OS_STOP_SEC_VAR_16
  #define DEFAULT_STOP_SEC_VAR_16

/* OS Initialized RAM: 32 bit values */
#elif defined (OS_START_SEC_VAR_32)
  #undef      OS_START_SEC_VAR_32
  #define DEFAULT_START_SEC_VAR_32
#elif defined (OS_STOP_SEC_VAR_32)
  #undef      OS_STOP_SEC_VAR_32
  #define DEFAULT_STOP_SEC_VAR_32

/* OS Initialized RAM: unspecified size */
#elif defined (OS_START_SEC_VAR_UNSPECIFIED)
  #undef      OS_START_SEC_VAR_UNSPECIFIED
  #define DEFAULT_START_SEC_VAR_UNSPECIFIED
#elif defined (OS_STOP_SEC_VAR_UNSPECIFIED)
  #undef      OS_STOP_SEC_VAR_UNSPECIFIED
  #define DEFAULT_STOP_SEC_VAR_UNSPECIFIED

/* OS Initialized fast RAM: boolean */
#elif defined (OS_START_SEC_VAR_FAST_BOOLEAN)
  #undef      OS_START_SEC_VAR_FAST_BOOLEAN
  #define DEFAULT_START_SEC_VAR_FAST_BOOLEAN
#elif defined (OS_STOP_SEC_VAR_FAST_BOOLEAN)
  #undef      OS_STOP_SEC_VAR_FAST_BOOLEAN
  #define DEFAULT_STOP_SEC_VAR_FAST_BOOLEAN

/* OS Initialized fast RAM: 8 bit values */
#elif defined (OS_START_SEC_VAR_FAST_8)
  #undef      OS_START_SEC_VAR_FAST_8
  #define DEFAULT_START_SEC_VAR_FAST_8
#elif defined (OS_STOP_SEC_VAR_FAST_8)
  #undef      OS_STOP_SEC_VAR_FAST_8
  #define DEFAULT_STOP_SEC_VAR_FAST_8

/* OS Initialized fast RAM: 16 bit values */
#elif defined (OS_START_SEC_VAR_FAST_16)
  #undef      OS_START_SEC_VAR_FAST_16
  #define DEFAULT_START_SEC_VAR_FAST_16
#elif defined (OS_STOP_SEC_VAR_FAST_16)
  #undef      OS_STOP_SEC_VAR_FAST_16
  #define DEFAULT_STOP_SEC_VAR_FAST_16

/* OS Initialized fast RAM: 32 bit values */
#elif defined (OS_START_SEC_VAR_FAST_32)
  #undef      OS_START_SEC_VAR_FAST_32
  #define DEFAULT_START_SEC_VAR_FAST_32
#elif defined (OS_STOP_SEC_VAR_FAST_32)
  #undef      OS_STOP_SEC_VAR_FAST_32
  #define DEFAULT_STOP_SEC_VAR_FAST_32

/* OS Initialized fast RAM: unspecified size */
#elif defined (OS_START_SEC_VAR_FAST_UNSPECIFIED)
  #undef      OS_START_SEC_VAR_FAST_UNSPECIFIED
  #define DEFAULT_START_SEC_VAR_FAST_UNSPECIFIED
#elif defined (OS_STOP_SEC_VAR_FAST_UNSPECIFIED)
  #undef      OS_STOP_SEC_VAR_FAST_UNSPECIFIED
  #define DEFAULT_STOP_SEC_VAR_FAST_UNSPECIFIED

/* OS Const (ROM): boolean */
#elif defined (OS_START_SEC_CONST_BOOLEAN)
  #undef      OS_START_SEC_CONST_BOOLEAN
  #define DEFAULT_START_SEC_CONST_BOOLEAN
#elif defined (OS_STOP_SEC_CONST_BOOLEAN)
  #undef      OS_STOP_SEC_CONST_BOOLEAN
  #define DEFAULT_STOP_SEC_CONST_BOOLEAN

/* OS Const (ROM): 8 bit values */
#elif defined (OS_START_SEC_CONST_8)
  #undef      OS_START_SEC_CONST_8
  #define DEFAULT_START_SEC_CONST_8
#elif defined (OS_STOP_SEC_CONST_8)
  #undef      OS_STOP_SEC_CONST_8
  #define DEFAULT_STOP_SEC_CONST_8

/* OS Const (ROM): 16 bit values */
#elif defined (OS_START_SEC_CONST_16)
  #undef      OS_START_SEC_CONST_16
  #define DEFAULT_START_SEC_CONST_16
#elif defined (OS_STOP_SEC_CONST_16)
  #undef      OS_STOP_SEC_CONST_16
  #define DEFAULT_STOP_SEC_CONST_16

/* OS Const (ROM): 32 bit values */
#elif defined (OS_START_SEC_CONST_32)
  #undef      OS_START_SEC_CONST_32
  #define DEFAULT_START_SEC_CONST_32
#elif defined (OS_STOP_SEC_CONST_32)
  #undef      OS_STOP_SEC_CONST_32
  #define DEFAULT_STOP_SEC_CONST_32

/* OS Const (ROM): Often accessed */
#elif defined (OS_START_SEC_CONST_FAST_UNSPECIFIED)
  #undef      OS_START_SEC_CONST_FAST_UNSPECIFIED
  #define DEFAULT_START_SEC_CONST_FAST_UNSPECIFIED
#elif defined (OS_STOP_SEC_CONST_FAST_UNSPECIFIED)
  #undef      OS_STOP_SEC_CONST_FAST_UNSPECIFIED
  #define DEFAULT_STOP_SEC_CONST_FAST_UNSPECIFIED

/* OS Const (ROM): unspecified size */
#elif defined (OS_START_SEC_CONST_UNSPECIFIED)
  #undef      OS_START_SEC_CONST_UNSPECIFIED
  #define DEFAULT_START_SEC_CONST_UNSPECIFIED
#elif defined (OS_STOP_SEC_CONST_UNSPECIFIED)
  #undef      OS_STOP_SEC_CONST_UNSPECIFIED
  #define DEFAULT_STOP_SEC_CONST_UNSPECIFIED

/* OS Code */
#elif defined (OS_START_SEC_CODE)
  #undef      OS_START_SEC_CODE
  #define DEFAULT_START_SEC_CODE
#elif defined (OS_STOP_SEC_CODE)
  #undef      OS_STOP_SEC_CODE
  #define DEFAULT_STOP_SEC_CODE

/* OS Fast Code */
#elif defined (OS_START_SEC_CODE_FAST)
  #undef      OS_START_SEC_CODE_FAST
  #define DEFAULT_START_SEC_CODE_FAST
#elif defined (OS_STOP_SEC_CODE_FAST)
  #undef      OS_STOP_SEC_CODE_FAST
  #define DEFAULT_STOP_SEC_CODE_FAST

/* OS Slow Code */
#elif defined (OS_START_SEC_CODE_SLOW)
  #undef      OS_START_SEC_CODE_SLOW
  #define DEFAULT_START_SEC_CODE_SLOW
#elif defined (OS_STOP_SEC_CODE_SLOW)
  #undef      OS_STOP_SEC_CODE_SLOW
  #define DEFAULT_STOP_SEC_CODE_SLOW

/* OS Library Code */
#elif defined (OS_START_SEC_CODE_LIB)
  #undef      OS_START_SEC_CODE_LIB
  #define DEFAULT_START_SEC_CODE_LIB
#elif defined (OS_STOP_SEC_CODE_LIB)
  #undef      OS_STOP_SEC_CODE_LIB
  #define DEFAULT_STOP_SEC_CODE_LIB

/* OS Interrupt vectors */
#elif defined (OS_START_SEC_VECTORS)
  #undef      OS_START_SEC_VECTORS
  #define DEFAULT_START_SEC_VECTORS
#elif defined (OS_STOP_SEC_VECTORS)
  #undef      OS_STOP_SEC_VECTORS
  #define DEFAULT_STOP_SEC_VECTORS

/* (Compatability) Callouts from the OS. */
#elif defined (OS_START_SEC_APPL_CODE)
  #undef      OS_START_SEC_APPL_CODE
  #define DEFAULT_START_SEC_APPL_CODE
#elif defined (OS_STOP_SEC_APPL_CODE)
  #undef      OS_STOP_SEC_APPL_CODE
  #define DEFAULT_STOP_SEC_APPL_CODE

/* Callouts from the OS. */
#elif defined (OS_START_SEC_CALLOUT_CODE)
  #undef      OS_START_SEC_CALLOUT_CODE
  #define DEFAULT_START_SEC_CALLOUT_CODE
#elif defined (OS_STOP_SEC_CALLOUT_CODE)
  #undef      OS_STOP_SEC_CALLOUT_CODE
  #define DEFAULT_STOP_SEC_CALLOUT_CODE

#endif
