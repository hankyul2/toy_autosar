#ifndef vrtaVMH
#define vrtaVMH
/*  [VP_VECU  5] */
/*  This file specifies the VM DLL API. */
/* [VP_VECU  4] */
/* [VP_VECU  418] */
/* [VP_VECU  419] */
/* [VP_VECU  420] */

#ifdef __cplusplus
#define EXPORT extern "C" __declspec(dllexport)
extern "C" {
#else
#define EXPORT __declspec(dllexport)
#endif /* __cplusplus */

#define VRTA_win /* Windows version */
#define VRTA_VM_VERSION (2)
#include /* no inline */ "vrtaTypes.h"

#define RTVECU_NUM_VECTORS  (32)        /* [VP_VECU  234] Number of interrupt vectors in the vector table */
typedef struct {
  vrtaUInt numVectors; /* Must be RTVECU_NUM_VECTORS. */
  vrtaIntVector vectors[RTVECU_NUM_VECTORS]; /* [VP_VECU  549] [VP_VECU  235] [VP_VECU  236] */
} vrtaVectorTable; /* [VP_VECU  548] Interrupt vector table */

typedef vrtaErrType(*vrtaSendActionPtr)(vrtaDevID id, const vrtaAction *a); /*  [VP_VECU  72] */
typedef vrtaErrType(*vrtaRaiseEventPtr)(vrtaDevID id, const vrtaEvent *e); /*  [VP_VECU  81] */
typedef vrtaErrType(*vrtaGetStatePtr)(vrtaDevID id, vrtaEvent *e); /*  [VP_VECU  88] */
typedef const void *vrtaEventListener;
typedef vrtaErrType(*vrtaEventCallback)(const void *instance, const vrtaEvent *event); /*  [VP_VECU  97] */
typedef vrtaEventListener(*vrtaEventRegisterPtr)(vrtaEventCallback eCallback, const void *tag); /*  [VP_VECU  96] */
typedef vrtaErrType(*vrtaEventUnregisterPtr)(vrtaEventListener listener); /*  [VP_VECU  102] */
typedef vrtaErrType(*vrtaHookEventPtr)(vrtaEventListener listener, vrtaDevID dev, vrtaEventID ev, vrtaBoolean capture); /*  [VP_VECU  106] */
typedef void (*vrtaEventRaiseCbk)(vrtaDevID id, vrtaEventID ev_id, const vrtaEvent *ev);
typedef vrtaEventRaiseCbk (*vrtaHookEventNotificationsPtr)(vrtaEventRaiseCbk new_hook);
typedef vrtaBoolean *(*vrtaOSSetInterruptDeferVarPtr)(vrtaBoolean *newVar);
typedef vrtaIntPriority(*vrtaOSSetIPLPtr)(vrtaIntPriority newIPL);
typedef vrtaIntPriority(*vrtaOSGetIPLPtr)(void);
typedef vrtaDevID (*vrtaGetCoreICUIDPtr)(vrtaDevID core);
typedef void (*vrtaOSSetIrqMaskPtr)(vrtaVecNumber vectorNumber);
typedef void (*vrtaOSClearIrqMaskPtr)(vrtaVecNumber vectorNumber);
typedef void (*vrtaOSSetIrqPendingPtr)(vrtaVecNumber vectorNumber);
typedef void (*vrtaOSClearIrqPendingPtr)(vrtaVecNumber vectorNumber);
typedef vrtaBoolean (*vrtaOSIsIrqPendingPtr)(vrtaVecNumber vectorNumber);
typedef void (*vrtaStartPtr)(void);
typedef vrtaInt (*vrtaStartCorePtr)(vrtaInt coreID);
typedef void (*vrtaTerminatePtr)(void); /*  [VP_VECU  177] */
typedef void (*vrtaResetPtr)(void); /*  [VP_VECU  175] */
typedef void (*vrtaEnterUninterruptibleSectionPtr)(void);
typedef void (*vrtaLeaveUninterruptibleSectionPtr)(void);
typedef void (*vrtaEnterGlobalUninterruptibleSectionPtr)(void);
typedef void (*vrtaLeaveGlobalUninterruptibleSectionPtr)(void);
typedef void (*vrtaIsIdlePtr)(vrtamillisecond msecs); /*  [VP_VECU  183] */
typedef void (*vrtaSpawnThreadPtr)(void (*func)(void));
typedef void (*vrtaInitializePtr)(vrtaAppMain app_main, vrtaInt argc, const vrtaTextPtr argv[], const vrtaVectorTable *app_vec);
typedef vrtaInt (*vrtaAddCorePtr)(vrtaAppMain app_main, const vrtaVectorTable *app_vec);
typedef vrtaInt (*vrtaGetCoreIDPtr)(void);
typedef vrtaErrType(*vrtaActionCallback)(void *instance, const vrtaAction *action); /*  [VP_VECU  64] */
typedef vrtaErrType(*vrtaStateCallback)(void *instance, vrtaEvent *state); /*  [VP_VECU  67] */
typedef vrtaDevID(*vrtaRegisterVirtualDevicePtr)(/*  [VP_VECU  46] */
  const vrtaTextPtr name, const vrtaOptStringlistPtr info, const vrtaOptStringlistPtr events,
  const vrtaOptStringlistPtr actions, const vrtaActionCallback aCallback, const vrtaStateCallback eCallback,
  const void *tag);
typedef vrtaBoolean(*vrtaIsAppThreadPtr)(void); /*  [VP_VECU  188] */
typedef vrtaBoolean(*vrtaIsAppFinishedPtr)(void); /*  [VP_VECU  568] */
typedef vrtaBoolean(*vrtaIsAppRunningPtr)(void);
typedef void (*vrtaNoneUserThreadPtr)(vrtaTextPtr name); /*  [VP_VECU  570] */
typedef vrtaInt     (*vrtaCoreCountPtr)(void);
typedef vrtaByte *  (*vrtaOSGetUserStackBasePtr)(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */

enum vrtaResetTypes {
  vrtaDevStart, vrtaDevStop, vrtaDevWriteToPersistentStorage, vrtaDevReadFromPersistentStorage
};

typedef struct {
  vrtaDataLen * vPSLen; /*  Pointer to length of persistent data for device */
  vrtaByte ** vPSAddr; /*  Pointer to persistent data for device */
  vrtaByte vResetType; /*  Contains an 'enum vrtaResetTypes' */
} vrtaDevResetInfo;
#endif /* vrtaVMH */
