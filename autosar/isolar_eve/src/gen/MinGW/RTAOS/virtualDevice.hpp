/*
 * This is virtualDevice.hpp, auto-generated for:
 *   Project: AFS
 *   Target:  VRTA
 *   Variant: MinGW
 *   Version: 3.0.23
 */
#ifndef VirtualDeviceHPP
#define VirtualDeviceHPP

extern "C" {
#include /* no inline */ "vrtaVM.h"
#include <string.h>
#include <stdio.h>
}

// -----------------------------------------------------------------------------
class VECUAutoLock {
public:
  VECUAutoLock();
  ~VECUAutoLock();
};
#define VECU_LOCK() { VECUAutoLock lock;
#define VECU_UNLOCK() }

// -----------------------------------------------------------------------------
// Note: This is a revised version of vrtaDevice, hopefully with an improved
// API.
// Note: For portability, we do not use STL in this code.
// -----------------------------------------------------------------------------
class VirtualDevice {
public:

protected:
  // ---------------------------------------------------------------------------
  // Internal class used to build strings
  // ---------------------------------------------------------------------------
  class StringBuilder {
    protected:
      char *m_Buf;
      size_t m_Contentlen;
      size_t m_Buflen;

    public:
      StringBuilder(int default_size = 60);
      virtual ~StringBuilder();
      void Append(const char *str);
      virtual const char *Content(void);
      int Length(void);
  };

  // ---------------------------------------------------------------------------
  // Internal class used to construct vrtaOptStringlists (strings separated with
  // '\n')
  // ---------------------------------------------------------------------------
  class OptList: public StringBuilder {
    public:
      OptList(int default_size = 200);
      void Clear(void);
      void Add(const char *key, const char *value);
      void Replace(int index, const char *key, const char *value);
  };

  // ---------------------------------------------------------------------------
  // Internal base class for objects that can be linked together as a list
  // ---------------------------------------------------------------------------
  class Linkable {
    protected:
      Linkable *m_Next;
    public:
      Linkable();

      Linkable *Next() {return m_Next;}
      void LinkTo(Linkable *p) { m_Next = p;}
  };

  // ---------------------------------------------------------------------------
  // Internal class used to hold information about an action or event parameter
  // Instances can be linked together so that the device's action or event
  // description can be constructed and then converted into an OptList for
  // device registration.
  // NOTE: The class only holds references to the information - it does not
  // buffer it.
  // NOTE: The member variables are not wrapped in getters/setters because they
  // can only be accessed in the controlled environment of a VirtualDevice
  // ---------------------------------------------------------------------------
  class ParameterInfo;
  class ParameterInfo : public Linkable {
    public:
      const char *m_Name;
      const char *m_Info;
      const char *m_Format;

      ParameterInfo(const char *name, const char *info, const char *format);
      ParameterInfo *Next() {return static_cast<ParameterInfo *>(m_Next);}
  };

  // ---------------------------------------------------------------------------
  // Internal class to manage a list of objects
  // ---------------------------------------------------------------------------
  class List {
    protected:
      Linkable *m_Head;
      Linkable *m_Tail;

    public:
      List();
      Linkable *First();
      void Append(Linkable *p);
      void Replace(int index, Linkable *p);
  };

  // ---------------------------------------------------------------------------
  // Internal class to manage a list of ParameterInfo
  // ---------------------------------------------------------------------------
  class ParameterList : public List {
    public:
      ParameterList() {}
      ParameterInfo *First() { return static_cast<ParameterInfo *>(m_Head); }
  };

  // ---------------------------------------------------------------------------
  // Internal class used to construct a list of ParameterInfo that represents
  // the information about the parameters for a single action. An action can have
  // 0, 1 or many parameters
  // ---------------------------------------------------------------------------
  class ActionInfo;
  class ActionInfo : public Linkable {

    protected:
      ParameterList m_Parameters;
      const char *m_Name;
      const char *m_Description;
      const char *m_Usage;

    public:
      ActionInfo(const char *name, const char *description, const char *usage);
      ActionInfo *Next() {return static_cast<ActionInfo *>(m_Next);}
      void AddContent(OptList *list);
      ActionInfo &In(const char *name, const char *info, const char *format);

      const char *Name() {return m_Name;}
      const char *Description() {return m_Description;}
      const char *Usage() {return m_Usage;}
  };

  // ---------------------------------------------------------------------------
  // Internal class used to construct 2 lists of ParameterInfo that represent
  // the in/out information about the parameters for a single event. An event
  // can have 0, 1 or many in/out parameters
  // ---------------------------------------------------------------------------
  class EventInfo;
  class EventInfo : public Linkable {

    protected:
      ParameterList m_Out;
      ParameterList m_In;
      const char *m_Name;
      const char *m_Description;
      const char *m_Usage;

    public:
      EventInfo(const char *name, const char *description, const char *usage);
      EventInfo *Next() {return static_cast<EventInfo *>(m_Next);}
      void AddContent(OptList *list);
      EventInfo &Out(const char *name, const char *info, const char *format);
      EventInfo &In(const char *name, const char *info, const char *format);

      const char *Name() {return m_Name;}
      const char *Description() {return m_Description;}
      const char *Usage() {return m_Usage;}
  };

  // ---------------------------------------------------------------------------
  // Internal class to manage a list of EventInfo
  // ---------------------------------------------------------------------------
  class EventInfoList : public List {
    public:
      EventInfoList() {}
      EventInfo *First() { return static_cast<EventInfo *>(m_Head); }
  };

  // ---------------------------------------------------------------------------
  // Internal class used to construct the registration information needed for
  // all of the Events on a device.
  // It keeps a list of EventInfo
  // ---------------------------------------------------------------------------
  class EventList: public OptList {
    private:
      EventInfoList m_Info;
    public:
      EventList();
      EventInfo &Add(const char *name, const char *description, const char *usage);
      EventInfo &Replace(int index, const char *name, const char *description, const char *usage);
      void UpdateInfo(OptList &device_info);
      const char *Content(void);
  };

  // ---------------------------------------------------------------------------
  // Internal class to manage a list of EventInfo
  // ---------------------------------------------------------------------------
  class ActionInfoList : public List {
    public:
      ActionInfoList() {}
      ActionInfo *First() { return static_cast<ActionInfo *>(m_Head); }
  };

  // ---------------------------------------------------------------------------
  // Internal class used to construct the registration information needed for
  // all of the Actions on a device.
  // It keeps a list of ActionInfo
  // ---------------------------------------------------------------------------
  class ActionList: public OptList {
    ActionInfoList m_Info;
    public:
      ActionList();
      ActionInfo &Add(const char *name, const char *description, const char *usage);
      ActionInfo &Replace(int index, const char *name, const char *description, const char *usage);
      void UpdateInfo(OptList &device_info);
      const char *Content(void);
  };

protected:
  vrtaDevID m_ID;
  vrtaDevID m_CoreAssignment;
  vrtaDevID m_ICUAssignment;
  char *m_Name;

  /* Persistence of data/state over reset */
  vrtaBoolean m_PersistThroughReset;
  vrtaBoolean m_DataHasPersisted;
  virtual vrtaDataLen GetPersistentDataSize(void);
  virtual vrtaByte * GetPersistentData(void);
  virtual void SetPersistentData(vrtaByte *addr, vrtaDataLen len);

  /*  Critical sections */
  void LockDevice(void);
  void ReleaseDevice(void);

  /*  Device Manager Interface */
  vrtaErrType SendAction(vrtaDevID devID, vrtaActionID devAction, vrtaAction &a);
  void RaiseInterrupt(vrtaUInt vector);
  void SpawnThread(void (*func)(void));

  /*  Helper methods - actions */
  vrtaInt    SignedValueFor(const vrtaAction &action) { return action.devEmbeddedData.iVal; }
  vrtaUInt   UnsignedValueFor(const vrtaAction &action) { return action.devEmbeddedData.uVal; }
  vrtaDouble DoubleValueFor(const vrtaAction &action) { return action.devEmbeddedData.dVal; }
  void UnpackData(const vrtaAction &action, void *dest, unsigned sz);
  template<typename T> void UnpackData(const vrtaAction &action, T &dest) {
    UnpackData(action, &dest, sizeof(dest));
  };

  void NoData(vrtaAction &a) { a.devActionData = 0; a.devActionLen = 0; }
  template<typename T> void SetValue(vrtaAction &a, T value);
  template<typename T1, typename T2> void SetValue(vrtaAction &a, T1 value1, T2 value2);
  template<typename T1, typename T2, typename T3> void SetValue(vrtaAction &a, T1 value1, T2 value2, T3 value3);
  template<typename T> void PackData(vrtaAction &a, T &value, int sz) {
    a.devActionLen = (vrtaDataLen) sz;
    if (a.devActionLen <= sizeof(vrtaEmbed)) {
      a.devActionData = NULL;
      memcpy(&a.devEmbeddedData.bVal[0], &value, a.devActionLen);
    } else {
      a.devActionData = (vrtaByte*) &value;
    }
  }

  /*  Helper methods - events */
  vrtaInt    SignedValueFor(const vrtaEvent &event) { return event.devEmbeddedData.iVal; }
  vrtaUInt   UnsignedValueFor(const vrtaEvent &event) { return event.devEmbeddedData.uVal; }
  vrtaDouble DoubleValueFor(const vrtaEvent &event) { return event.devEmbeddedData.dVal; }
  void UnpackData(const vrtaEvent &event, void *dest, unsigned sz);
  template<typename T> void UnpackData(const vrtaEvent &event, T &dest) {
    UnpackData(event, &dest, sizeof(dest));
  };

  void NoData(vrtaEvent &e) { e.devEventData = 0; e.devEventLen = 0; }
  void SetValue(vrtaEvent &e, void *value, unsigned sz);
  template<typename T> void SetValue(vrtaEvent &e, T value);
  template<typename T1, typename T2> void SetValue(vrtaEvent &e, T1 value1, T2 value2);
  template<typename T1, typename T2, typename T3> void SetValue(vrtaEvent &e, T1 value1, T2 value2, T3 value3);
  void PackData(vrtaEvent &e, void *src, int sz) {
    e.devEventLen = (vrtaDataLen) sz;
    if (e.devEventLen <= sizeof(vrtaEmbed)) {
      e.devEventData = NULL;
      memcpy(&e.devEmbeddedData.bVal[0], src, e.devEventLen);
    } else {
      e.devEventData = (vrtaByte*)src;
    }
  }
  template<typename T> void PackData(vrtaEvent &e, T &value, int sz) {
    e.devEventLen = (vrtaDataLen) sz;
    if (e.devEventLen <= sizeof(vrtaEmbed)) {
      e.devEventData = NULL;
      memcpy(&e.devEmbeddedData.bVal[0], &value, e.devEventLen);
    } else {
      e.devEventData = (vrtaByte*) &value;
    }
  }

  void PersistThroughReset(vrtaBoolean f);
  vrtaBoolean DataHasPersisted(void);
  void DataHasPersisted(vrtaBoolean f);
  void ReadFromPersistentStorage(vrtaDataLen *len, vrtaByte **addr);
  void WriteToPersistentStorage(vrtaDataLen *len, vrtaByte **addr);

  void RegisterAs(const char * name);
    // Called from RegisterAs
    virtual void GetDeviceInfo(OptList &info) = 0;
    virtual void GetDeviceActions(ActionList &actions) = 0;
    virtual void GetDeviceEvents(EventList &events) = 0;

  virtual ~VirtualDevice();

protected:
  unsigned int m_MaxActions;
  unsigned int m_MaxEvents;
  unsigned int m_ActionCallbackCount;
  unsigned int m_EventCallbackCount;
  bool m_Running;

  typedef vrtaErrType (VirtualDevice::*actionCallback)(const vrtaAction &action);
  typedef vrtaErrType (VirtualDevice::*eventCallback)(const vrtaEvent &event);

  actionCallback *m_ActionCallbacks;
  eventCallback *m_EventCallbacks;

  vrtaErrType ActionZero(const vrtaAction &action);
  vrtaErrType EventZero(const vrtaEvent &event);
  void AddActionHandler(actionCallback handler);
  void AddEventHandler(eventCallback handler);

  #define ADD_ACTION_HANDLER(h)     AddActionHandler((actionCallback)&h);
  #define ADD_NULL_ACTION_HANDLER() AddActionHandler(&VirtualDevice::NullAction);
  #define REPLACE_ACTION_HANDLER(n,h) if (n < m_MaxActions) { m_ActionCallbacks[n] = (actionCallback)&h; }
  #define ADD_EVENT_HANDLER(h)      AddEventHandler((eventCallback)&h);
  #define ADD_NULL_EVENT_HANDLER()  AddEventHandler(&VirtualDevice::NullEvent);
  #define REPLACE_EVENT_HANDLER(n,h) if (n < m_MaxEvents) { m_EventCallbacks[n] = (eventCallback)&h; }

  #define EVENT_HANDLER(h) (eventCallback)&h
  void Raise(vrtaEvent &e);
  void Raise(eventCallback cbk);
  void Raise(eventCallback cbk, vrtaEvent &event);
  template<typename T1> void Raise(eventCallback cbk, T1 p1);
  template<typename T1, typename T2> void Raise(eventCallback cbk, T1 p1, T2 p2);
  template<typename T1, typename T2, typename T3> void Raise(eventCallback cbk, T1 p1, T2 p2, T3 p3);

  virtual void Starting(void) {};
  virtual void Stopping(void) {};

public:
  VirtualDevice(void);

  vrtaErrType ActionHandler(const vrtaAction &action);
  virtual vrtaErrType EventHandler(vrtaEvent &event);
  vrtaErrType NullAction(const vrtaAction &action);
  vrtaErrType NullEvent(const vrtaEvent &event);

  void SetID(vrtaDevID id);
  vrtaDevID GetID(void);
  void AssignCore(vrtaDevID id);

  bool IsRunning(void) {return m_Running;};
};

//---------------------------------------------------------------------------
template<typename T> void VirtualDevice::SetValue(vrtaAction &a, T value) {
  a.devActionLen = sizeof(value);
  if (a.devActionLen <= sizeof(vrtaEmbed)) {
    a.devActionData = NULL;
    if (a.devActionLen < sizeof(vrtaUInt)) {
      a.devEmbeddedData.uVal = 0U;  // Zero fill allows %u on short ints
    }
    memcpy(&a.devEmbeddedData.bVal[0], &value, sizeof(value));
  } else {
    a.devActionData = &value;
  }
}

//---------------------------------------------------------------------------
// Not suitable for data that won't fit in devEmbeddedData
template<typename T1, typename T2> void VirtualDevice::SetValue(vrtaAction &a, T1 value1, T2 value2) {
  a.devActionLen = sizeof(value1) + sizeof(value2);
  if (a.devActionLen <= sizeof(vrtaEmbed)) {
    a.devActionData = NULL;
    memcpy(&a.devEmbeddedData.bVal[0], &value1, sizeof(value1));
    memcpy(&a.devEmbeddedData.bVal[sizeof(value1)], &value2, sizeof(value2));
  } else {
    a.devActionLen = 0;
  }
}

//---------------------------------------------------------------------------
// Not suitable for data that won't fit in devEmbeddedData
template<typename T1, typename T2, typename T3> void VirtualDevice::SetValue(vrtaAction &a, T1 value1, T2 value2, T3 value3) {
  a.devActionLen = sizeof(value1) + sizeof(value2) + sizeof(value3);
  if (a.devActionLen <= sizeof(vrtaEmbed)) {
    a.devActionData = NULL;
    memcpy(&a.devEmbeddedData.bVal[0], &value1, sizeof(value1));
    memcpy(&a.devEmbeddedData.bVal[sizeof(value1)], &value2, sizeof(value2));
    memcpy(&a.devEmbeddedData.bVal[sizeof(value1) + sizeof(value2)], &value3, sizeof(value3));
  } else {
    a.devActionLen = 0;
  }
}

//---------------------------------------------------------------------------
template<typename T> void VirtualDevice::SetValue(vrtaEvent &e, T value) {
  e.devEventLen = sizeof(value);
  if (e.devEventLen <= sizeof(vrtaEmbed)) {
    e.devEventData = NULL;
    if (e.devEventLen < sizeof(vrtaUInt)) {
      e.devEmbeddedData.uVal = 0U;  // Zero fill allows %u on short ints
    }
    memcpy(&e.devEmbeddedData.bVal[0], &value, sizeof(value));
  } else {
    e.devEventData = &value;
  }
}

//---------------------------------------------------------------------------
// Not suitable for data that won't fit in devEmbeddedData
template<typename T1, typename T2> void VirtualDevice::SetValue(vrtaEvent &e, T1 value1, T2 value2) {
  e.devEventLen = sizeof(value1) + sizeof(value2);
  if (e.devEventLen <= sizeof(vrtaEmbed)) {
    e.devEventData = NULL;
    memcpy(&e.devEmbeddedData.bVal[0], &value1, sizeof(value1));
    memcpy(&e.devEmbeddedData.bVal[sizeof(value1)], &value2, sizeof(value2));
  } else {
    e.devEventLen = 0;
  }
}

//---------------------------------------------------------------------------
// Not suitable for data that won't fit in devEmbeddedData
template<typename T1, typename T2, typename T3> void VirtualDevice::SetValue(vrtaEvent &e, T1 value1, T2 value2, T3 value3) {
  e.devEventLen = sizeof(value1) + sizeof(value2) + sizeof(value3);
  if (e.devEventLen <= sizeof(vrtaEmbed)) {
    e.devEventData = NULL;
    memcpy(&e.devEmbeddedData.bVal[0], &value1, sizeof(value1));
    memcpy(&e.devEmbeddedData.bVal[sizeof(value1)], &value2, sizeof(value2));
    memcpy(&e.devEmbeddedData.bVal[sizeof(value1) + sizeof(value2)], &value3, sizeof(value3));
  } else {
    e.devEventLen = 0;
  }
}

template<typename T1> void VirtualDevice::Raise(eventCallback cbk, T1 p1) {
  vrtaEvent event;
  event.devID = m_ID;
  SetValue(event, p1);
  Raise(cbk, event);
}

template<typename T1, typename T2> void VirtualDevice::Raise(eventCallback cbk, T1 p1, T2 p2) {
  vrtaEvent event;
  event.devID = m_ID;
  SetValue(event, p1, p2);
  Raise(cbk, event);
}
template<typename T1, typename T2, typename T3> void VirtualDevice::Raise(eventCallback cbk, T1 p1, T2 p2, T3 p3) {
  vrtaEvent event;
  event.devID = m_ID;
  SetValue(event, p1, p2, p3);
  Raise(cbk, event);
}

#endif /* VirtualDeviceHPP */


