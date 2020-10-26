/*
 * This is Platform_Types.h for target platform: VRTA/MinGW
 */

#ifndef PLATFORM_TYPES_H
#define PLATFORM_TYPES_H
/*
  File version information [PLATFORM012]
*/
#define PLATFORM_VENDOR_ID        (11U)
#define PLATFORM_AR_MAJOR_VERSION (4U)
#define PLATFORM_AR_MINOR_VERSION (0U)
#define PLATFORM_AR_PATCH_VERSION (3U)
#define PLATFORM_TYPES_AR_RELEASE_MAJOR_VERSION (4U)
#define PLATFORM_TYPES_AR_RELEASE_MINOR_VERSION (0U)
#define PLATFORM_TYPES_AR_RELEASE_REVISION_VERSION (3U)
#define PLATFORM_SW_MAJOR_VERSION (5U)
#define PLATFORM_SW_MINOR_VERSION (4U)
#define PLATFORM_SW_PATCH_VERSION (4U)

/*
  CPU register type width
*/
#define CPU_TYPE_8  8
#define CPU_TYPE_16 16
#define CPU_TYPE_32 32

/*
  Bit order definition [PLATFORM038]
*/
#define MSB_FIRST 0                 /* Big endian bit ordering        */
#define LSB_FIRST 1                 /* Little endian bit ordering     */

/*
  Byte order definition [PLATFORM039]
*/
#define HIGH_BYTE_FIRST 0           /* Big endian byte ordering       */
#define LOW_BYTE_FIRST  1           /* Little endian byte ordering    */

/*
  Platform type and endianess definitions
*/
#define CPU_TYPE CPU_TYPE_32 /* [PLATFORM044] [PLATFORM045] */
#define CPU_BIT_ORDER LSB_FIRST /* [PLATFORM043] [PLATFORM048] [PLATFORM049] */
#define CPU_BYTE_ORDER LOW_BYTE_FIRST /* [PLATFORM049] [PLATFORM050] [PLATFORM051] */

/*
  AUTOSAR integer data types
  [PLATFORM061] - signed integer types are implemented using 2 complement arithmetic.
*/
typedef unsigned char uint8;   /* [PLATFORM013]          0 .. 255             */
typedef unsigned short uint16; /* [PLATFORM014]          0 .. 65535           */
typedef unsigned int uint32;  /* [PLATFORM014]          0 .. 4294967295      */
typedef signed char sint8;     /* [PLATFORM016]       -128 .. +127            */
typedef signed short sint16;   /* [PLATFORM017]     -32768 .. +32767          */
typedef signed int sint32;    /* [PLATFORM018]-2147483648 .. +2147483647     */
typedef float float32; /* [PLATFORM041] */
typedef double float64; /* [PLATFORM042] */

/* [PLATFORM005] - chosen for best performance */
/* [PLATFORM032] - these must only be used with a local scope inside a module. They are not allowed to be used within the API of a module. */
typedef unsigned char uint8_least; /* [PLATFORM020] At least 8 bit */
typedef unsigned short uint16_least; /* [PLATFORM021] At least 16 bit */
typedef unsigned int uint32_least; /* [PLATFORM022] At least 32 bit */
typedef signed char sint8_least; /* [PLATFORM023] At least 7 bit + 1 bit sign */
typedef signed short sint16_least; /* [PLATFORM024] At least 15 bit + 1 bit sign */
typedef signed int sint32_least; /* [PLATFORM025] At least 31 bit + 1 bit sign */

/* [PLATFORM026] [PLATFORM034] Only to be used with TRUE and FALSE */
typedef unsigned char boolean; /* [PLATFORM027] [PLATFORM060] Addressable 8 bits for use with TRUE/FALSE */

/* [PLATFORM054] [PLATFORM055] [PLATFORM056] Only use in conjunction with the boolean type */
#ifndef TRUE
 #define TRUE      1U
#endif

#ifndef FALSE
 #define FALSE     0U
#endif

#endif /* PLATFORM_TYPES_H */
