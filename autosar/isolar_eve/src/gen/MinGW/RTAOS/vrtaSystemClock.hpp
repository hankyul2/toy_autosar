/*
 * This is vrtaSystemClock.hpp, auto-generated for:
 *   Project: AFS
 *   Target:  VRTA
 *   Variant: MinGW
 *   Version: 3.0.23
 */
#ifndef VRTASystemClockHPP
#define VRTASystemClockHPP

// ---------------------------------------------------------------------------
// vrtaSystemClock is the single source of clock ticks for VECUs.
// It runs a 1ms tick when scale is 1/1.
// It can be:
//   - stopped
//   - started
//   - scaled
//   - ticked programatically
// Other clocks must get their time from here if they need to be synchronized.
// vrtaSystemClock acts as a singleton regardless of the number you create
// This is done because of the way that we have to operate in Linux, using a
// single higher priority timer thread..
//
// vrtaSystemClock feeds ticks to any number of secondary clocks that
// subscribe to it.
// By default the clock is in auto tick mode where an operating system
// timer is used to advance time. In in manual tick mode the Tick() method
// must be called to advance time.
// ---------------------------------------------------------------------------
class vrtaSystemClockType;

// ---------------------------------------------------------------------------
// Tick subscribers must inherit from this
// They will get ticks at the same rate as vrtaSystemClock
class vrtaSystemClockSubscriber {
public:
  vrtaSystemClockSubscriber *_next_subscriber;
  vrtaSystemClockType *_clock_source;

  vrtaSystemClockSubscriber();
  virtual ~vrtaSystemClockSubscriber();

  virtual void Tick(void) = 0;
};

// ---------------------------------------------------------------------------
class vrtaSystemClockType {

public:
    vrtaSystemClockType(void);

    void Subscribe(vrtaSystemClockSubscriber *subscriber);
    void Unsubscribe(vrtaSystemClockSubscriber *subscriber);

    // Pause the clock. Time will not advance irrespective of the tick mode.
    void Pause(void);
    bool IsPaused(void);

    // Resume a paused clock.
    void Resume(void);

    // Interval strategy
    void FavourFixedInterval(vrtaBoolean truth);
    bool IsFavourFixedInterval(void);

    // Switch to auto tick mode.
    void Auto(void);
    bool IsAuto(void);

    // Switch to manual tick mode.
    void Manual(unsigned);
    unsigned ManualTicksRemaining(void);
    bool ManualTicksCompleted(void);
    bool IsManual(void);
    void ManualFreezesOS(bool value);
    void ManualCanDoLowPower(bool value);
    bool ManualCanDoLowPower(void);

    // Switch to adaptive mode.
    void IdleTick(void);
    bool IsIdleTicked(void);

    // Advance time by one (when manual)
    void Tick(void);

    // Running tick count
    unsigned TickCount(void);

    // Wall time - unaffected by pauses or scale
    unsigned MillisecondsCount(void);

    // Slow down tick rate
    void Scale(unsigned multiplier);
    unsigned Scale(void);

};
extern vrtaSystemClockType vrtaSystemClock;

// ---------------------------------------------------------------------------
// Non-OS threads can use this to wait (block) for a number of ticks, where the
// duration of a tick is specified at construction in the ticks_per_s parameter.
// The implementation is linked to vrtaSystemClock, so it copes with scaling,
// pausing, idle and directed ticking.
// ---------------------------------------------------------------------------
class vrtaThreadWait {
  public:
    vrtaThreadWait(unsigned ticks_per_s);

    // Returns FALSE only when being idle-ticked or manually-ticked and the
    // interval has not expired.
    // When TRUE is returned, the number of ticks can be considered to be expired
    bool WaitForTicks(unsigned ticks);

  private:
    void *m_Implementation;
};

// ---------------------------------------------------------------------------
// vrtaCustomTickSource allows you to create a source of ticks where the duration
// of a tick is configurable (rather than the fixed 1ms in SystemClock).
// ---------------------------------------------------------------------------
class vrtaCustomTickSource {
  public:
    // Create the tick source - specifying the number of ticks in a second.
    vrtaCustomTickSource(unsigned ticks_per_s);

    // Returns the number of ticks
    unsigned TickCount(void);

  private:
    void *m_Implementation;
};

#endif /* VRTASystemClockHPP */


