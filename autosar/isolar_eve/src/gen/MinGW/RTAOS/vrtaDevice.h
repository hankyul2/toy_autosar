#ifndef vrtaDeviceH
#define vrtaDeviceH
#ifdef __cplusplus
/*  [VP_VECU  452] */
/*  Defines the base class for all devices. */

#include /* no inline */ "vrtaVM.h"
#include <string.h>

/* [VP_VECU  418] */
/* [VP_VECU  419] */
/* [VP_VECU  420] */

#ifdef __cplusplus
extern "C" {
  extern void vrtaEnterUninterruptibleSection(void);
  extern void vrtaLeaveUninterruptibleSection(void);
  extern void vrtaEnterGlobalUninterruptibleSection(void);
  extern void vrtaLeaveGlobalUninterruptibleSection(void);
}
#endif

class vrtaDevice {
private:
protected:
  vrtaDevID m_ID; /*  [VP_VECU  455] */
  vrtaDevID m_CoreAssignment;
  vrtaDevID m_ICUAssignment;
  const vrtaTextPtr m_Name; /*  [VP_VECU  456] */
  const vrtaOptStringlistPtr m_Info; /*  [VP_VECU  457] */
  const vrtaOptStringlistPtr m_Events; /*  [VP_VECU  458] */
  const vrtaOptStringlistPtr m_Actions; /*  [VP_VECU  459] */

  /*  Persistence of data/state over reset */
  vrtaBoolean m_PersistThroughReset;
  vrtaBoolean m_DataHasPersisted;

  virtual vrtaDataLen GetPersistentDataSize(void) {
    return 0;
  };

  virtual vrtaByte * GetPersistentData(void) {
    return (vrtaByte *) 0;
  };

  virtual void SetPersistentData(vrtaByte *addr, vrtaDataLen len) {
  };

  /*  Critical sections */
  void LockDevice(void) {
    vrtaEnterGlobalUninterruptibleSection();
  };

  void ReleaseDevice(void) {
    vrtaLeaveGlobalUninterruptibleSection();
  };

  /*  Device Manager Interface */
  void RaiseEvent(vrtaEvent &e); /*  [VP_VECU  465] */
  vrtaErrType GetState(vrtaDevID id, vrtaEvent &e); /*  [VP_VECU  466] */
  vrtaErrType SendAction(vrtaDevID id, vrtaAction &a); /*  [VP_VECU  467] */
  void RaiseInterrupt(vrtaUInt vector); /*  [VP_VECU  582] */
  void SpawnThread(void (*func)(void)); /*  [VP_VECU  468] */
  void EventWithUVal(vrtaEvent *event, vrtaEventID evID, vrtaUInt uval) {
    event->devID = GetID();
    event->devEvent = evID;
    event->devEventLen = (vrtaDataLen)(sizeof (event->devEmbeddedData.uVal));
    event->devEmbeddedData.uVal = uval;
    event->devEventData = NULL;
  }
  void EventWithNoData(vrtaEvent *event, vrtaEventID evID) {
    event->devID = GetID();
    event->devEvent = evID;
    event->devEventLen = 0;
    event->devEventData = NULL;
  }
  void EventWithText(vrtaEvent *event, vrtaEventID evID, const char *text) {
    event->devID = GetID();
    event->devEvent = evID;
    event->devEventLen = (vrtaDataLen)(strlen(text) + 1);
    if (event->devEventLen == 1) {
      event->devEventLen = 0;
    } else {
      if (event->devEventLen <= sizeof (event->devEmbeddedData)) {
        strcpy((char *) event->devEmbeddedData.bVal, text);
        event->devEventData = event->devEmbeddedData.bVal;
      } else {
        event->devEventData = text;
      }
    }
  }

  /*  Helper methods */
  vrtaUInt uVal(const vrtaAction *a) {
    return a->devEmbeddedData.uVal;
  };

  vrtaUInt uVal(const vrtaEvent *e) {
    return e->devEmbeddedData.uVal;
  };

  vrtaUInt uVal(const vrtaAction *a, vrtaUInt offset) {
    return *(vrtaUInt *) & a->devEmbeddedData.bVal[offset];
  };

  vrtaUInt uVal(const vrtaEvent *e, vrtaUInt offset) {
    return *(vrtaUInt *) & e->devEmbeddedData.bVal[offset];
  };

  signed iVal(const vrtaAction *a) {
    return a->devEmbeddedData.iVal;
  };

  signed iVal(const vrtaEvent *e) {
    return e->devEmbeddedData.iVal;
  };

  signed iVal(const vrtaAction *a, vrtaUInt offset) {
    return *(signed *) & a->devEmbeddedData.bVal[offset];
  };

  signed iVal(const vrtaEvent *e, vrtaUInt offset) {
    return *(signed *) & e->devEmbeddedData.bVal[offset];
  };

  void Set_nil(vrtaEvent *e) {
    e->devEventData = 0;
    e->devEventLen = 0;
  };

  void Set_uVal(vrtaEvent *e, vrtaUInt v) {
    e->devEventData = 0;
    e->devEmbeddedData.uVal = v;
    e->devEventLen = (vrtaDataLen)(sizeof (e->devEmbeddedData.uVal));
  };

  void Set_uVal(vrtaEvent *e, vrtaUInt v, vrtaUInt offset) {
    e->devEventData = 0;
    *(vrtaUInt *) &e->devEmbeddedData.bVal[offset] = v;
    e->devEventLen = (vrtaDataLen)(offset + sizeof (e->devEmbeddedData.uVal));
  };

  void Set_iVal(vrtaEvent *e, signed v) {
    e->devEventData = 0;
    e->devEmbeddedData.iVal = v;
    e->devEventLen = (vrtaDataLen)(sizeof (e->devEmbeddedData.iVal));
  };

  void Set_iVal(vrtaEvent *e, signed v, vrtaUInt offset) {
    e->devEventData = 0;
    *(signed *)&e->devEmbeddedData.bVal[offset] = v;
    e->devEventLen = (vrtaDataLen)(offset + sizeof (e->devEmbeddedData.iVal));
  };

  void Set_aVal(vrtaEvent *e, void *src, vrtaUInt len) {
    if (len <= sizeof (e->devEmbeddedData)) {
      memcpy(e->devEmbeddedData.bVal, src, len);
      e->devEventData = e->devEmbeddedData.bVal;
    } else {
      e->devEventData = src;
    }
    e->devEventLen = (vrtaDataLen)(len);
  }

public:
  vrtaDevice(
    const vrtaTextPtr name,
    const vrtaTextPtr info,
    const vrtaOptStringlistPtr events,
    const vrtaOptStringlistPtr actions);

  virtual void Starting(void) = 0;
  virtual void Stopping(void) = 0;

  void PersistThroughReset(vrtaBoolean f);

  vrtaBoolean DataHasPersisted(void) {
    return m_DataHasPersisted;
  };

  void DataHasPersisted(vrtaBoolean f) {
    m_DataHasPersisted = f;
  };
  virtual void ReadFromPersistentStorage(vrtaDataLen *len, vrtaByte **addr);
  virtual void WriteToPersistentStorage(vrtaDataLen *len, vrtaByte **addr);

  virtual vrtaErrType OnAction(const vrtaAction *action) = 0;
  virtual vrtaErrType AsyncGetState(vrtaEvent *event) = 0;

  vrtaErrType ReadState(vrtaEvent *event, vrtaEventID ev) {
    event->devID = m_ID;
    event->devEvent = ev;
    event->devEventData = &event->devEmbeddedData;
    event->devEventLen = 0;
    return AsyncGetState(event);
  };

  vrtaErrType OKAction(const vrtaAction *action) {
    return RTVECUErr_NONE;
  };

  /*  [VP_VECU  461] */
  vrtaErrType ErrorAction(const vrtaAction *action) {
    return RTVECUErr_ID;
  };

  /*  [VP_VECU  462] */
  vrtaErrType OKState(const vrtaEvent *event) {
    return RTVECUErr_NONE;
  };

  /*  [VP_VECU  463] */
  vrtaErrType ErrorState(const vrtaEvent *event) {
    return RTVECUErr_ID;
  };

  /*  [VP_VECU  464] */
  void SetID(vrtaDevID id) {
    m_ID = id;
  };

  /*  [VP_VECU  471] */
  vrtaDevID GetID(void) {
    return m_ID;
  }; /*  [VP_VECU  472] */

  void AssignCore(vrtaDevID id);
  /*  [VP_VECU  460] No public data */
};

#endif /* __cplusplus */
#endif /* vrtaDeviceH */
