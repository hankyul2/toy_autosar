/** \file         ComStack_Types.h
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
  * $Id: ComStack_Types.h 2379 2014-08-10 12:55:57Z pin9fe $
  */

#ifndef COMSTACK_TYPES_H
#define COMSTACK_TYPES_H


#include "Std_Types.h"
#define AUTOSAR_COMSTACKDATA    /* Distance of pointers of SduDataPtr in PduInfoType */

/*Define COMTYPE_AR_RELEASE_MAJOR_VERSION */
#define COMTYPE_AR_RELEASE_MAJOR_VERSION 4u
#define COMTYPE_AR_RELEASE_MINOR_VERSION 0
//***********************************************

typedef uint16 PduIdType;
typedef uint32 PduLengthType;

typedef struct {

    P2VAR(uint8,AUTOMATIC,AUTOSAR_COMSTACKDATA) SduDataPtr;
    PduLengthType SduLength;
} PduInfoType;


typedef enum
{
    BUFREQ_OK,
    BUFREQ_E_NOT_OK,
    BUFREQ_E_BUSY,
    BUFREQ_E_OVFL,
}
BufReq_ReturnType;

typedef uint8 NotifResultType;

#define NTFRSLT_OK 0x00
#define NTFRSLT_E_NOT_OK 0x01
#define NTFRSLT_E_TIMEOUT_A 0x02
#define NTFRSLT_E_TIMEOUT_BS 0x03
#define NTFRSLT_E_TIMEOUT_CR 0x04
#define NTFRSLT_E_WRONG_SN 0x05
#define NTFRSLT_E_INVALID_FS 0x06
#define NTFRSLT_E_UNEXP_PDU 0x07
#define NTFRSLT_E_WFT_OVRN 0x08
#define NTFRSLT_E_NO_BUFFER 0x09
#define NTFRSLT_E_CANCELATION_OK 0x0a
#define NTFRSLT_E_CANCELATION_NOT_OK 0x0b



typedef uint8 BusTrcvErrorType;
#define BUSTRCV_OK 0x00
#define BUSTRCV_E_ERROR 0x01


typedef uint8 NetworkHandleType;

typedef uint8 IcomConfigIdType; /* This is used only for AR 4.2.2 release */

/* Comm parameter passed to comm main function, must defined in DEM */
#define COMM_E_NET_START_IND_CHANNEL_0	0

typedef enum
{
    TP_DATACONF,
    TP_DATARETRY,
    TP_CONFPENDING,
    TP_NORETRY
} TpDataStateType;
/* Chapter 8.1.9: Information about Tp buffer handling */
typedef struct
{
    TpDataStateType TpDataState;
    PduLengthType TxTpDataCnt;
} RetryInfoType;
//*******************************************************************************

#endif
