/*
 * This is Os_Cfg.h, auto-generated for:
 *   Project: AFS
 *   Target:  VRTA
 *   Variant: MinGW
 *   Version: 3.0.23
 *   [$UKS 650]
 */
#ifndef OS_CFG_H
#define OS_CFG_H
/* -- Start expansion of <Os_Safe_Cfg.h> -- */
/* -- Start expansion of <Os_Target_Cfg.h> -- */
#define OS_ISR_VECTOR_VECU_SystemClock_ISR (7U)

/* -- End expansion of <Os_Target_Cfg.h> -- */
#define OS_NUM_APPMODES (2U)
#define OS_NUM_APPLICATIONS (0U)
#define OS_NUM_SPINLOCKS (0U)
#define OS_NUM_TRUSTED_FUNCTIONS (0U)
#define OS_NUM_EVENTS (3U)
#define OS_NUM_TASKS (22U)
#define OS_NUM_ISRS (1U)
#define OS_NUM_RESOURCES (2U)
#define OS_NUM_ALARMS (6U)
#define OS_NUM_SCHEDULETABLES (1U)
#define OS_NUM_TRACEPOINTS (0U)
#define OS_NUM_TASKTRACEPOINTS (0U)
#define OS_NUM_INTERVALS (0U)
#define OS_NUM_TRACECATEGORIES (0U)
#define OS_TRACE_CATEGORY_ALWAYS ((Os_TraceCategoriesType)(0x80000000UL))
#define OS_TRACE_CATEGORY_NEVER  ((Os_TraceCategoriesType)(0x00000000UL))
/* [MISRA 2004 Rule 19.7] */ /*lint -estring(961, OS_TICKS2*) */
#define OS_NUM_COUNTERS (2U)
#define OSCYCLEDURATION (1000) /* [$UKS 1224] */
#define OSCYCLESPERSECOND (1000000U) /* [$UKS 1225] */
#define OSSWTICKDURATION (1000000) /* [$UKS 1226] */
#define OSSWTICKSPERSECOND (1000U) /* [$UKS 1227] */
#define OS_TICKS2NS_Rte_TOutCounter(ticks) ((PhysicalTimeType)((ticks) * 1000000000U /* Default: SecondsPerTick not set */)) /* [$UKS 843] */
#define OS_TICKS2US_Rte_TOutCounter(ticks) ((PhysicalTimeType)((ticks) * 1000000U /* Default: SecondsPerTick not set */)) /* [$UKS 843] */
#define OS_TICKS2MS_Rte_TOutCounter(ticks) ((PhysicalTimeType)((ticks) * 1000U /* Default: SecondsPerTick not set */)) /* [$UKS 843] */
#define OS_TICKS2SEC_Rte_TOutCounter(ticks) ((PhysicalTimeType)((ticks) * 1U /* Default: SecondsPerTick not set */)) /* [$UKS 843] */
#define OSMAXALLOWEDVALUE_Rte_TOutCounter (65535U) /* [$UKS 219] */
#define OSTICKSPERBASE_Rte_TOutCounter (1U) /* [$UKS 220] */
#define OSTICKDURATION_Rte_TOutCounter OS_TICKS2NS_Rte_TOutCounter(1U) /* [$UKS 221] */
#define OSMINCYCLE_Rte_TOutCounter (1U) /* [$UKS 222] */
#define OS_TICKS2NS_Rte_TickCounter(ticks) ((PhysicalTimeType)((ticks) * 1000000000U /* Default: SecondsPerTick not set */)) /* [$UKS 843] */
#define OS_TICKS2US_Rte_TickCounter(ticks) ((PhysicalTimeType)((ticks) * 1000000U /* Default: SecondsPerTick not set */)) /* [$UKS 843] */
#define OS_TICKS2MS_Rte_TickCounter(ticks) ((PhysicalTimeType)((ticks) * 1000U /* Default: SecondsPerTick not set */)) /* [$UKS 843] */
#define OS_TICKS2SEC_Rte_TickCounter(ticks) ((PhysicalTimeType)((ticks) * 1U /* Default: SecondsPerTick not set */)) /* [$UKS 843] */
#define OSMAXALLOWEDVALUE_Rte_TickCounter (65535U) /* [$UKS 219] */
#define OSTICKSPERBASE_Rte_TickCounter (1U) /* [$UKS 220] */
#define OSTICKDURATION_Rte_TickCounter OS_TICKS2NS_Rte_TickCounter(1U) /* [$UKS 221] */
#define OSMINCYCLE_Rte_TickCounter (1U) /* [$UKS 222] */
#define OSMAXALLOWEDVALUE OSMAXALLOWEDVALUE_SystemCounter /* [$UKS 215] */
#define OSTICKSPERBASE OSTICKSPERBASE_SystemCounter /* [$UKS 216] */
#define OSMINCYCLE OSMINCYCLE_SystemCounter /* [$UKS 218] */
#define OSTICKDURATION OSTICKDURATION_SystemCounter /* [$UKS 217] */
#define OS_NUM_CORES (1U)
#define OS_NUM_OS_CORES (1U)
#define OS_CORE_ID_MASTER (0U)  /* [$UKS 1609] */


/* ------------------------------------------------- */
/* [MISRA 2004 Rule 19.1] */ /*lint -save -esym(961, 19.1) */
#define OS_START_SEC_CALLOUT_CODE
#include "MemMap.h" /* [MISRA 2004 Rule 19.15] */ /*lint !e537 !e451 */
/*lint -restore */
extern FUNC(void, OS_CALLOUT_CODE) Os_Cbk_Alarm_Rte_NullAlarmCallback(void);
/* [MISRA 2004 Rule 19.1] */ /*lint -save -esym(961, 19.1) */
#define OS_STOP_SEC_CALLOUT_CODE
#include "MemMap.h" /* [MISRA 2004 Rule 19.15] */ /*lint !e537 !e451 */
/*lint -restore */

/* ------------------------------------------------- */
/* [MISRA 2004 Rule 19.1] */ /*lint -save -esym(961, 19.1) */
#define OS_START_SEC_CODE_LIB
#include "MemMap.h" /* [MISRA 2004 Rule 19.15] */ /*lint !e537 !e451 */
/*lint -restore */
extern FUNC(StatusType, OS_CODE) Os_IncrementCounter_Rte_TOutCounter(void);
extern FUNC(StatusType, OS_CODE) Os_IncrementCounter_Rte_TickCounter(void);
extern FUNC(void, OS_CODE) Os_Entry_TAKS_ECU_SPEED(void);
extern FUNC(void, OS_CODE) Os_Entry_TASK_ECU_ACTUATOR(void);
extern FUNC(void, OS_CODE) Os_Entry_TASK_ECU_DISTANCE(void);
extern FUNC(void, OS_CODE) Os_Entry_TASK_ECU_LIGHT(void);
extern FUNC(void, OS_CODE) Os_Entry_TASK_ECU_LIGHTMODE(void);
extern FUNC(void, OS_CODE) Os_Entry_TASK_EUC_STEERINGANGLE(void);
extern FUNC(void, OS_CODE) Os_Entry_TASK_ACT_HIGHBEAM_RECEIVE(void);
extern FUNC(void, OS_CODE) Os_Entry_TASK_ACT_HIGHBEAM_SEND(void);
extern FUNC(void, OS_CODE) Os_Entry_TASK_ACT_LEFTRIGHTANGLE_RECEIVE(void);
extern FUNC(void, OS_CODE) Os_Entry_TASK_ACT_LEFTRIGHTANGLE_SEND(void);
extern FUNC(void, OS_CODE) Os_Entry_TASK_ACT_LOWBEAM_RECEIVE(void);
extern FUNC(void, OS_CODE) Os_Entry_TASK_ACT_LOWBEAM_SEND(void);
extern FUNC(void, OS_CODE) Os_Entry_TASK_ACT_UPDOWNANGLE_RECEIVE(void);
extern FUNC(void, OS_CODE) Os_Entry_TASK_ACT_UPDOWNANGLE_SEND(void);
extern FUNC(void, OS_CODE) Os_Entry_TASK_SENSOR_DISTANCE(void);
extern FUNC(void, OS_CODE) Os_Entry_TASK_SENSOR_LIGHT(void);
extern FUNC(void, OS_CODE) Os_Entry_TASK_SENSOR_LIGHTMODE(void);
extern FUNC(void, OS_CODE) Os_Entry_TASK_SENSOR_SPEED(void);
extern FUNC(void, OS_CODE) Os_Entry_TASK_SENSOR_STEERINGANGLE(void);
extern FUNC(void, OS_CODE) Os_Entry_TASK_APP_HIGHBEAM(void);
extern FUNC(void, OS_CODE) Os_Entry_TASK_APP_LOWBEAM(void);
extern FUNC(void, OS_CODE) Os_Entry_TASK_APP_MOTOR(void);
extern FUNC(void, OS_CODE) Os_Entry_VECU_SystemClock_ISR(void);
/* [MISRA 2004 Rule 19.1] */ /*lint -save -esym(961, 19.1) */
#define OS_STOP_SEC_CODE_LIB
#include "MemMap.h" /* [MISRA 2004 Rule 19.15] */ /*lint !e537 !e451 */
/*lint -restore */


/* -- End expansion of <Os_Safe_Cfg.h> -- */

/* -------- AppMode declarations --------- */
#define OS_NOAPPMODE ((AppModeType)0U)
#define OSDEFAULTAPPMODE ((AppModeType)1U)  /* [$UKS 381] [$UKS 383] */

/* ----- OS-Application declarations ----- */

/* -------- Event declarations --------- */
#define Rte_Activity (1U)
#define Rte_Timeout (2U)
#define Rte_Ev_100000000_0 (4U)
DeclareEvent(Rte_Activity)
DeclareEvent(Rte_Timeout)
DeclareEvent(Rte_Ev_100000000_0)

/* -------- Task declarations --------- */
#define TAKS_ECU_SPEED (&Os_const_tasks[0U])
DeclareTask(TAKS_ECU_SPEED)
#define TASK_ECU_ACTUATOR (&Os_const_tasks[1U])
DeclareTask(TASK_ECU_ACTUATOR)
#define TASK_ECU_DISTANCE (&Os_const_tasks[2U])
DeclareTask(TASK_ECU_DISTANCE)
#define TASK_ECU_LIGHT (&Os_const_tasks[3U])
DeclareTask(TASK_ECU_LIGHT)
#define TASK_ECU_LIGHTMODE (&Os_const_tasks[4U])
DeclareTask(TASK_ECU_LIGHTMODE)
#define TASK_EUC_STEERINGANGLE (&Os_const_tasks[5U])
DeclareTask(TASK_EUC_STEERINGANGLE)
#define TASK_ACT_HIGHBEAM_RECEIVE (&Os_const_tasks[6U])
DeclareTask(TASK_ACT_HIGHBEAM_RECEIVE)
#define TASK_ACT_HIGHBEAM_SEND (&Os_const_tasks[7U])
DeclareTask(TASK_ACT_HIGHBEAM_SEND)
#define TASK_ACT_LEFTRIGHTANGLE_RECEIVE (&Os_const_tasks[8U])
DeclareTask(TASK_ACT_LEFTRIGHTANGLE_RECEIVE)
#define TASK_ACT_LEFTRIGHTANGLE_SEND (&Os_const_tasks[9U])
DeclareTask(TASK_ACT_LEFTRIGHTANGLE_SEND)
#define TASK_ACT_LOWBEAM_RECEIVE (&Os_const_tasks[10U])
DeclareTask(TASK_ACT_LOWBEAM_RECEIVE)
#define TASK_ACT_LOWBEAM_SEND (&Os_const_tasks[11U])
DeclareTask(TASK_ACT_LOWBEAM_SEND)
#define TASK_ACT_UPDOWNANGLE_RECEIVE (&Os_const_tasks[12U])
DeclareTask(TASK_ACT_UPDOWNANGLE_RECEIVE)
#define TASK_ACT_UPDOWNANGLE_SEND (&Os_const_tasks[13U])
DeclareTask(TASK_ACT_UPDOWNANGLE_SEND)
#define TASK_SENSOR_DISTANCE (&Os_const_tasks[14U])
DeclareTask(TASK_SENSOR_DISTANCE)
#define TASK_SENSOR_LIGHT (&Os_const_tasks[15U])
DeclareTask(TASK_SENSOR_LIGHT)
#define TASK_SENSOR_LIGHTMODE (&Os_const_tasks[16U])
DeclareTask(TASK_SENSOR_LIGHTMODE)
#define TASK_SENSOR_SPEED (&Os_const_tasks[17U])
DeclareTask(TASK_SENSOR_SPEED)
#define TASK_SENSOR_STEERINGANGLE (&Os_const_tasks[18U])
DeclareTask(TASK_SENSOR_STEERINGANGLE)
#define TASK_APP_HIGHBEAM (&Os_const_tasks[19U])
DeclareTask(TASK_APP_HIGHBEAM)
#define TASK_APP_LOWBEAM (&Os_const_tasks[20U])
DeclareTask(TASK_APP_LOWBEAM)
#define TASK_APP_MOTOR (&Os_const_tasks[21U])
DeclareTask(TASK_APP_MOTOR)

/* -------- ISR declarations --------- */
#define VECU_SystemClock_ISR (&Os_const_isrs[0U])
DeclareISR(VECU_SystemClock_ISR)

/* -------- Resource declarations --------- */
#define RTE_RESOURCE (&Os_const_resources[0U])
DeclareResource(RTE_RESOURCE)
#define RES_SCHEDULER (&Os_const_resources[1U])
DeclareResource(RES_SCHEDULER)

/* -------- Counter declarations --------- */
#define Rte_TOutCounter (&Os_const_counters[0U])
DeclareCounter(Rte_TOutCounter)
#define Rte_TickCounter (&Os_const_counters[1U])
DeclareCounter(Rte_TickCounter)

/* -------- Alarm declaration --------- */
#define Rte_TimeoutAlarm1 (0U)
DeclareAlarm(Rte_TimeoutAlarm1)
#define Rte_TimeoutAlarm2 (1U)
DeclareAlarm(Rte_TimeoutAlarm2)
#define Rte_TimeoutAlarm3 (2U)
DeclareAlarm(Rte_TimeoutAlarm3)
#define Rte_TimeoutAlarm4 (3U)
DeclareAlarm(Rte_TimeoutAlarm4)
#define Rte_TimeoutAlarm5 (4U)
DeclareAlarm(Rte_TimeoutAlarm5)
#define Rte_TimeoutAlarm6 (5U)
DeclareAlarm(Rte_TimeoutAlarm6)

/* -------- ScheduleTable declaration --------- */
#define Rte_ScheduleTable (&Os_const_scheduletables[0U])
#define OS_DURATION_Rte_ScheduleTable (1U)
DeclareScheduleTable(Rte_ScheduleTable)

/* -------- Tracepoint declarations --------- */

/* -------- TaskTracepoint declarations --------- */

/* -------- Interval declarations --------- */

/* -------- Filtered APIs --------- */
#define Os_LogTracepoint(TpointID,Category) /* never */
#define Os_LogTracepointValue(TpointID,Value,Category) /* never */
#define Os_LogTracepointData(TpointID,Data,Length,Category) /* never */
#define Os_LogTaskTracepoint(TTpointID,Category) /* never */
#define Os_LogTaskTracepointValue(TTpointID,Value,Category) /* never */
#define Os_LogTaskTracepointData(TTpointID,Data,Length,Category) /* never */
#define Os_LogIntervalStart(IntervalID,Category) /* never */
#define Os_LogIntervalStartValue(IntervalID,Value,Category) /* never */
#define Os_LogIntervalStartData(IntervalID,Data,Length,Category) /* never */
#define Os_LogIntervalEnd(IntervalID,Category) /* never */
#define Os_LogIntervalEndValue(IntervalID,Value,Category) /* never */
#define Os_LogIntervalEndData(IntervalID,Data,Length,Category) /* never */
#ifndef OS_TRACE_NAMESPACE_PURE /* [$UKS 1154] */
/* [MISRA 2004 Rule 19.7] */ /*lint -estring(961, LogTrace* ,LogTaskTrace* ,LogInterval*) */  #define LogTracepoint(TpointID,Category) Os_LogTracepoint(TpointID,Category)
  #define LogTracepointValue(TpointID,Value,Category) Os_LogTracepointValue(TpointID,Value,Category)
  #define LogTracepointData(TpointID,Data,Length,Category) Os_LogTracepointData(TpointID,Data,Length,Category)
  #define LogTaskTracepoint(TTpointID,Category) Os_LogTaskTracepoint(TTpointID,Category)
  #define LogTaskTracepointValue(TTpointID,Value,Category) Os_LogTaskTracepointValue(TTpointID,Value,Category)
  #define LogTaskTracepointData(TTpointID,Data,Length,Category) Os_LogTaskTracepointData(TTpointID,Data,Length,Category)
  #define LogIntervalStart(IntervalID,Category) Os_LogIntervalStart(IntervalID,Category)
  #define LogIntervalStartValue(IntervalID,Value,Category) Os_LogIntervalStartValue(IntervalID,Value,Category)
  #define LogIntervalStartData(IntervalID,Data,Length,Category) Os_LogIntervalStartData(IntervalID,Data,Length,Category)
  #define LogIntervalEnd(IntervalID,Category) Os_LogIntervalEnd(IntervalID,Category)
  #define LogIntervalEndValue(IntervalID,Value,Category) Os_LogIntervalEndValue(IntervalID,Value,Category)
  #define LogIntervalEndData(IntervalID,Data,Length,Category) Os_LogIntervalEndData(IntervalID,Data,Length,Category)
#endif

#endif /* OS_CFG_H */
