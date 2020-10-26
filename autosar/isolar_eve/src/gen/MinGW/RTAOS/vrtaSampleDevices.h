#ifndef vrtaSampleDevicesH
#define vrtaSampleDevicesH
/* --------------------------------------------------------------------------- */
/*  Defines the sample devices. */
/* --------------------------------------------------------------------------- */
#include /* no inline */ "vrtaDevice.h"
#include /* no inline */ "vrtaSystemClock.hpp"

class vrtaCounter;
class vrtaCompare;
#define SAMPLE_DEVICES_VERSION "5.4.4"

/* --------------------------------------------------------------------------- */
/*  vrtaBaseClock - base class for all clocks */
/* --------------------------------------------------------------------------- */
class vrtaBaseClock : public vrtaDevice, public vrtaSystemClockSubscriber {
protected:

  vrtaCounter * m_NextCounter;

  struct s_persist {
    vrtaUInt Interval;
    vrtaUInt ScaleMult;
    vrtaUInt ScaleDiv;
  } m_Persist; /*  State that can be persisted over a reset */

  virtual void initialize_clock(void) = 0;
  virtual void ResetClock(void) = 0;

  vrtaUInt m_Interval;  /* Units depend on concrete implementation */
  vrtaUInt m_ScaleMult; /*  Rate multiplier */
  vrtaUInt m_ScaleDiv;  /*  Rate divisor */
  bool m_Running; /*  Running status */

  /* Derived from interval and scale */
  vrtaUInt m_MsPerTick;
  volatile vrtaUInt m_MsRemaining;

  virtual void Starting(void);
  virtual void Stopping(void) {};
  virtual vrtaErrType OnAction(const vrtaAction *action);
  virtual vrtaErrType AsyncGetState(vrtaEvent *event);

  /*  Persistence */
  vrtaDataLen GetPersistentDataSize(void) {
    return sizeof (m_Persist);
  };

  vrtaByte * GetPersistentData(void) {
    m_Persist.Interval = m_Interval;
    m_Persist.ScaleMult = m_ScaleMult;
    m_Persist.ScaleDiv = m_ScaleDiv;
    return (vrtaByte *)&m_Persist;
  };
  void SetPersistentData(vrtaByte *addr, vrtaDataLen len);

public:
  /*  Constructors */
  vrtaBaseClock(const vrtaTextPtr name, vrtaUInt interval, bool unused_option);
  vrtaBaseClock(
    const vrtaTextPtr name,
    vrtaUInt interval,
    const vrtaOptStringlistPtr info,
    const vrtaOptStringlistPtr events,
    const vrtaOptStringlistPtr actions,
    bool unused_option
  );

  virtual ~vrtaBaseClock();

  /*  Tick event */
  virtual void Tick(void);

  /*  Run-time control */
  void SetInterval(vrtaUInt interval);
  void SetScale(vrtaUInt mult, vrtaUInt div);
  virtual void Start(void);
  virtual void Stop(void) {};

  /*  Counter interface */
  vrtaCounter *Attach(vrtaCounter *counter) {
    vrtaCounter *last = m_NextCounter;
    m_NextCounter = counter;
    return last;
  };
};

/* --------------------------------------------------------------------------- */
/*  vrtaClock - 1 ms intervals */
/* --------------------------------------------------------------------------- */
class vrtaClock : public vrtaBaseClock {
protected:
  void initialize_clock(void);
  void ResetClock(void);
  virtual void Stopping(void);

public:
  /*  Constructors */
  vrtaClock(const vrtaTextPtr name, vrtaUInt interval, bool unused_option = true);
  vrtaClock(
    const vrtaTextPtr name,
    vrtaUInt interval,
    const vrtaOptStringlistPtr info,
    const vrtaOptStringlistPtr events,
    const vrtaOptStringlistPtr actions,
    bool unused_option = true
  );

  /*  Run-time control */
  virtual void Stop(void);
};

/* --------------------------------------------------------------------------- */
/*   vrtaAdaptiveClock                                                         */
/* --------------------------------------------------------------------------- */
class vrtaAdaptiveClock : public vrtaClock {

private:
  vrtaBoolean m_FreeRunning;

public:
  vrtaAdaptiveClock(const vrtaTextPtr name, unsigned interval, bool unused_option = true);

  // This method gets called from the real free-running timer. Ticks are ignored
  // unless we are free-running.
  void Tick(void);

  // This method gets called from software as often as it likes. It only
  // has an effect when we not free-running.
  // Typically it will be called repeatedly in the idle loop, so the clock
  // will run as fast as it can.
  // This clock does not get scaled.
  vrtaBoolean InjectTick(void);

  vrtaErrType OnAction(const vrtaAction *action);
};

/* --------------------------------------------------------------------------- */
/*                               vrtaComparable */
/* --------------------------------------------------------------------------- */

/*  Base class for all devices that can attach to one or more vrtaCompare devices */
class vrtaComparable : public vrtaDevice {
private:

  struct s_persist {
    vrtaUInt Value;
  } m_Persist; /*  State that can be persisted over a reset */

protected:
  vrtaUInt m_Value;
  vrtaCompare * m_NextCompare;
  void CheckComparators(void);

  /*  Persistence */
  vrtaDataLen GetPersistentDataSize(void) {
    return sizeof (m_Persist);
  };

  vrtaByte * GetPersistentData(void) {
    m_Persist.Value = m_Value;
    return (vrtaByte *)&m_Persist;
  };
  void SetPersistentData(vrtaByte *addr, vrtaDataLen len);

public:

  /*  Constructor */
  vrtaComparable(const vrtaTextPtr name,
    const vrtaTextPtr info,
    const vrtaOptStringlistPtr events,
    const vrtaOptStringlistPtr actions) : vrtaDevice(name, info, events, actions) {
    m_Value = 0;
    m_NextCompare = NULL;
  };

  /*  Compare interface */
  vrtaCompare * Attach(vrtaCompare *comp) {
    vrtaCompare *last = m_NextCompare;
    m_NextCompare = comp;
    return last;
  };

  virtual vrtaUInt Value(void) {
    return m_Value;
  };

  vrtaUInt GetValue(void) {
    return Value();
  };

  virtual void SetVal(vrtaUInt v) {
    m_Value = v;
  };

  void SetValue(vrtaUInt v) {
    SetVal(v);
  };
};

/* --------------------------------------------------------------------------- */
/*  vrtaCounter, vrtaUpCounter, vrtaDownCounter */
/* --------------------------------------------------------------------------- */

class vrtaCounter : public vrtaComparable {
private:

  struct s_persist {
    vrtaUInt Value;
    vrtaUInt Min;
    vrtaUInt Max;
  } m_Persist; /*  State that can be persisted over a reset */

protected:
  vrtaUInt m_Min;
  vrtaUInt m_Max;
  bool m_Running;

  vrtaBaseClock & m_Clock;
  vrtaCounter * m_NextCounter;

  void Starting(void);
  void Stopping(void);
  vrtaErrType OnAction(const vrtaAction *action);
  vrtaErrType AsyncGetState(vrtaEvent *event);

  /*  Persistence */
  vrtaDataLen GetPersistentDataSize(void) {
    return sizeof (m_Persist);
  };

  vrtaByte * GetPersistentData(void) {
    m_Persist.Value = Value();
    m_Persist.Min = m_Min;
    m_Persist.Max = m_Max;
    return (vrtaByte *)&m_Persist;
  };
  void SetPersistentData(vrtaByte *addr, vrtaDataLen len);

public:
  /*  Constructor */
  vrtaCounter(const vrtaTextPtr name, const vrtaTextPtr info, vrtaBaseClock &clock);

  /*  Tick event */
  virtual void Tick(void) = 0;

  /*  Direct access */
  vrtaUInt Min(void) {
    return m_Min;
  };

  vrtaUInt Max(void) {
    return m_Max;
  };
  void SetMin(vrtaUInt v);
  void SetMax(vrtaUInt v);
  void SetVal(vrtaUInt v);
  void Start(void);
  void Stop(void);
};

/* --------------------------------------------------------------------------- */
class vrtaUpCounter : public vrtaCounter {
public:

  /*  Constructor */
  vrtaUpCounter(const vrtaTextPtr name, vrtaBaseClock &clock) : vrtaCounter(name, (char*)
  "Type=Counter.Up\n"
  "Version="SAMPLE_DEVICES_VERSION "\n"
  "Action Minimum=Set the start value for the count\n"
  "Action Maximum=Set the maximum value for the count\n"
  "Action Set=Set the count value\n"
  "Action Start=Enable counting\n"
  "Action Stop=Disable counting\n"
  "Action Report=Causes the Set event to be raised (Raises Set Event)\n"
  "Event Set=The value of the count when Report action is raised (Raise,Poll)\n"
  , clock) {
  };

  /*  Up Tick */
  void Tick(void);
};

/* --------------------------------------------------------------------------- */
class vrtaDownCounter : public vrtaCounter {
public:

  /*  Constructor */
  vrtaDownCounter(const vrtaTextPtr name, vrtaBaseClock &clock) : vrtaCounter(name, (char*)
  "Type=Counter.Down\n"
  "Version="SAMPLE_DEVICES_VERSION"\n"
  "Action Minimum=Set the start value for the count\n"
  "Action Maximum=Set the maximum value for the count\n"
  "Action Set=Set the count value\n"
  "Action Start=Enable counting)\n"
  "Action Stop=Disable counting\n"
  "Action Report=Causes the Set event to be raised (Raises Set Event)\n"
  "Event Set=The value of the count when Report action is raised (Raise,Poll)\n"
  , clock) {
  };

  /*  Down Tick */
  void Tick(void);
};

/* --------------------------------------------------------------------------- */
/*  vrtaCompare */
/* --------------------------------------------------------------------------- */

class vrtaCompare : public vrtaDevice {
private:

  struct s_persist {
    vrtaUInt Match;
  } m_Persist; /*  State that can be persisted over a reset */

protected:
  vrtaComparable &m_Source;
  vrtaCompare * m_NextCompare;
  vrtaUInt m_Match;
  vrtaUInt m_Vector;

  void Starting(void) {
  };

  void Stopping(void) {
  };
  vrtaErrType OnAction(const vrtaAction *action);
  vrtaErrType AsyncGetState(vrtaEvent *event);

  /*  Persistence */
  vrtaDataLen GetPersistentDataSize(void) {
    return sizeof (m_Persist);
  };

  vrtaByte * GetPersistentData(void) {
    m_Persist.Match = m_Match;
    return (vrtaByte *)&m_Persist;
  };
  void SetPersistentData(vrtaByte *addr, vrtaDataLen len);

public:
  /*  Constructor */
  vrtaCompare(const vrtaTextPtr name, vrtaComparable &source, vrtaUInt match, vrtaUInt vector);

  /*  Set */
  void SetMatch(vrtaUInt val);

  vrtaUInt IncrementMatch(vrtaUInt val) {
    return (m_Match += val);
  };
  void SetVector(vrtaUInt val);
  void NewValue(vrtaUInt val);

  /*  Get */
  vrtaUInt GetMatch(void) {
    return m_Match;
  };

};

/* --------------------------------------------------------------------------- */
/*  vrtaSensor */
/* --------------------------------------------------------------------------- */

class vrtaSensor : public vrtaComparable {
private:

  struct s_persist {
    vrtaUInt Value;
    vrtaUInt Max;
  } m_Persist; /*  State that can be persisted over a reset */

protected:
  vrtaUInt m_Max;

  void Starting(void) {
  };

  void Stopping(void) {
  };
  vrtaErrType OnAction(const vrtaAction *action);
  vrtaErrType AsyncGetState(vrtaEvent *event);

  /*  Persistence */
  vrtaDataLen GetPersistentDataSize(void) {
    return sizeof (m_Persist);
  };

  vrtaByte * GetPersistentData(void) {
    m_Persist.Value = Value();
    m_Persist.Max = m_Max;
    return (vrtaByte *)&m_Persist;
  };
  void SetPersistentData(vrtaByte *addr, vrtaDataLen len);

public:
  /*  Constructor */
  vrtaSensor(const vrtaTextPtr name);
  vrtaSensor(const vrtaTextPtr name, const vrtaTextPtr info, const vrtaOptStringlistPtr events, const vrtaOptStringlistPtr actions);

  /*  Direct access */
  vrtaUInt GetMax(void) {
    return m_Max;
  };
  void SetMax(vrtaUInt v);
  void SetVal(vrtaUInt v);
};

/* --------------------------------------------------------------------------- */
/*  vrtaSensorToggleSwitch */
/* --------------------------------------------------------------------------- */

class vrtaSensorToggleSwitch : public vrtaSensor {
private:

protected:

public:
  /*  Constructor */
  vrtaSensorToggleSwitch(const vrtaTextPtr name);
};

/* --------------------------------------------------------------------------- */
/*  vrtaSensorMultiwaySwitch */
/* --------------------------------------------------------------------------- */

class vrtaSensorMultiwaySwitch : public vrtaSensor {
private:

protected:

public:
  /*  Constructor */
  vrtaSensorMultiwaySwitch(const vrtaTextPtr name, vrtaUInt ways);
};

/* --------------------------------------------------------------------------- */
/*  vrtaActuator */
/* --------------------------------------------------------------------------- */

class vrtaActuator : public vrtaComparable {
private:

  struct s_persist {
    vrtaUInt Max;
    vrtaUInt Value;
  } m_Persist; /*  State that can be persisted over a reset */

protected:
  vrtaUInt m_Max;

  void Starting(void) {
  };

  void Stopping(void) {
  };
  vrtaErrType OnAction(const vrtaAction *action);
  vrtaErrType AsyncGetState(vrtaEvent *event);

  /*  Persistence */
  vrtaDataLen GetPersistentDataSize(void) {
    return sizeof (m_Persist);
  };

  vrtaByte * GetPersistentData(void) {
    m_Persist.Value = Value();
    m_Persist.Max = m_Max;
    return (vrtaByte *)&m_Persist;
  };
  void SetPersistentData(vrtaByte *addr, vrtaDataLen len);

public:
  /*  Constructor */
  vrtaActuator(const vrtaTextPtr name);
  vrtaActuator(const vrtaTextPtr name, const vrtaTextPtr info);

  /*  Direct access */
  vrtaUInt GetMax(void) {
    return m_Max;
  };
  void SetMax(vrtaUInt v);
  void SetVal(vrtaUInt v);
};

/* --------------------------------------------------------------------------- */
/*  vrtaActuatorLight */
/* --------------------------------------------------------------------------- */

class vrtaActuatorLight : public vrtaActuator {
private:

protected:

public:
  /*  Constructor */
  vrtaActuatorLight(const vrtaTextPtr name);
};

/* --------------------------------------------------------------------------- */
/*  vrtaActuatorDimmableLight */
/* --------------------------------------------------------------------------- */

class vrtaActuatorDimmableLight : public vrtaActuator {
private:

protected:

public:
  /*  Constructor */
  vrtaActuatorDimmableLight(const vrtaTextPtr name, vrtaUInt levels);
};

/* --------------------------------------------------------------------------- */
/*  vrtaActuatorMultiColorLight */
/* --------------------------------------------------------------------------- */

class vrtaActuatorMultiColorLight : public vrtaActuator {
private:

protected:

public:
  /*  Constructor */
  vrtaActuatorMultiColorLight(const vrtaTextPtr name, vrtaUInt colors);
};

/* --------------------------------------------------------------------------- */
/*  vrtaIO */
/* --------------------------------------------------------------------------- */
class vrtaIO : public vrtaDevice {
private:
  void Init(vrtaUInt elements);

protected:
  vrtaUInt * m_Elements;
  vrtaUInt m_Size;

  void Starting(void);
  void Stopping(void);
  vrtaErrType OnAction(const vrtaAction *action);
  vrtaErrType AsyncGetState(vrtaEvent *event);

  /*  Persistence */
  vrtaDataLen GetPersistentDataSize(void);
  vrtaByte * GetPersistentData(void);
  void SetPersistentData(vrtaByte *addr, vrtaDataLen len);

public:
  /*  Constructors */
  vrtaIO(const vrtaTextPtr name, vrtaUInt elements);
  vrtaIO(const vrtaTextPtr name, vrtaUInt elements,
    const vrtaTextPtr info,
    const vrtaOptStringlistPtr events,
    const vrtaOptStringlistPtr actions);

  void SetValue(vrtaUInt offset, vrtaUInt value);
  void SetValues(vrtaUInt offset, const vrtaUInt *values, vrtaUInt number);

  vrtaUInt GetValue(vrtaUInt offset) const;
  const vrtaUInt *GetValues(void) const;
};

/* --------------------------------------------------------------------------- */
#endif
