#ifndef vrtaTypesH
#define vrtaTypesH
/* [VP_VECU  6] */
/* [VP_VECU  418] */
/* [VP_VECU  419] */
/* [VP_VECU  420] */

typedef char * vrtaTextPtr;             /* [VP_VECU  7] ASCIIZ string pointer e.g. "Hello World" */
typedef char * vrtaStringlistPtr;       /* [VP_VECU  8] ASCIIZ stringlist pointer e.g. "Jan\nFeb\nMar" */
typedef char * vrtaOptStringlistPtr;    /* [VP_VECU  9] ASCIIZ option-stringlist pointer e.g. "Name=Jim\nAge=99" */
typedef unsigned short vrtaMsgType;     /* [VP_VECU  10] Inter-module message type */
typedef unsigned short vrtaDevID;       /* [VP_VECU  11] Device ID */
typedef unsigned short vrtaActEvID;     /* [VP_VECU  12] Action or Event ID */
typedef unsigned short vrtaISRID;       /* [VP_VECU  13] ISR ID */
typedef vrtaActEvID vrtaActionID;       /* [VP_VECU  14] Action ID */
typedef vrtaActEvID vrtaEventID;        /* [VP_VECU  15] Event ID */
typedef unsigned short vrtaErrType;     /* [VP_VECU  16] Error ID */
typedef unsigned char vrtaByte;         /* [VP_VECU  17] Data bytes */
typedef unsigned short vrtaDataLen;     /* [VP_VECU  18] Data size */
#define vrtaDataLenMax 0xffff
typedef unsigned long vrtamillisecond;  /* [VP_VECU 552] A Number of milliseconds */
typedef unsigned long vrtaTimestamp;    /* [VP_VECU 553] A timestamp */
typedef signed vrtaBoolean;             /* [VP_VECU 554] A boolean */
typedef void * vrtaLinkageTablePtr;     /* [VP_VECU 555] Pointer to a linkage table */
typedef void * vrtaAppTag;              /* [VP_VECU 556] An application supplied tag value */

typedef signed int vrtaInt;
typedef unsigned int vrtaUInt;
typedef double vrtaDouble;
/* [MISRA 2004 Rule 18.4] */ /*lint -save -esym(960, 18.4) */
typedef union {
  vrtaInt        iVal;           /* [VP_VECU  20] */
  vrtaUInt       uVal;           /* [VP_VECU  21] */
  vrtaDouble     dVal;           /* [VP_VECU  22] */
  vrtaByte       bVal[16];       /* [VP_VECU  23] */
} vrtaEmbed;                     /* [VP_VECU  19] Embedded data */
/*lint -restore */

typedef struct {
  vrtaDevID devID; /* [VP_VECU  25] */
  vrtaActionID devAction; /* [VP_VECU  26] */
  vrtaDataLen devActionLen; /* [VP_VECU  27] */
  const void * devActionData; /* [VP_VECU  28] */
  vrtaEmbed devEmbeddedData; /* [VP_VECU  29] */
  vrtaTimestamp devTimeStamp; /* [VP_VECU  575] */
} vrtaAction;

/* [VP_VECU  24] Device action */

typedef struct {
  vrtaDevID devID; /* [VP_VECU  31] */
  vrtaEventID devEvent; /* [VP_VECU  32] */
  vrtaDataLen devEventLen; /* [VP_VECU  33] */
  const void * devEventData; /* [VP_VECU  34] */
  vrtaEmbed devEmbeddedData; /* [VP_VECU  35] */
  vrtaTimestamp devTimeStamp; /* [VP_VECU  576] */
} vrtaEvent; /* [VP_VECU  30] Device Event */

typedef unsigned vrtaVecNumber; /* [VP_VECU  36] Interrupt vector number */
typedef unsigned vrtaIntPriority; /* [VP_VECU  37] Interrupt priority */
typedef unsigned vrtaIntMask; /* [VP_VECU  38] Bit mask */
typedef void (*vrtaIntHandler)(vrtaAppTag tag, vrtaIntPriority oldIPL);

/* [VP_VECU  39] Interrupt Handler */
typedef struct {
  vrtaIntHandler handler; /* [VP_VECU  41] */
  vrtaIntPriority priority; /* [VP_VECU  42] */
  vrtaAppTag tag; /* [VP_VECU  557] */
} vrtaIntVector; /* [VP_VECU  40] Interrupt vector */

typedef void (*vrtaAppMain)(void); /* [VP_VECU  43] */

#define RTVECUErr_NONE  (0)
#define RTVECUErr_Dev   (1)
#define RTVECUErr_ID    (2)
#define RTVECUErr_VAL   (3)
#define RTVECUErr_Conn  (4)

#endif /* vrtaTypesH */
