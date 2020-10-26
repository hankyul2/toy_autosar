/** @file         Rte_Lib.c
  *
  * @brief        RTE library implementation
  *               [$Satisfies $SRD 62321] RTE library template
  *
  * @copyright    Copyright 2007-2008 ETAS Engineering Tools Application and Services Ltd.
  *               Copyright 2008-2013 ETAS GmbH.
  *
  * @note         Implemented SWS: 4.0
  *
  * @note         PLATFORM DEPENDANT [yes/no]: no
  *
  * @note         TO BE CHANGED BY USER [yes/no]: no
  *
  * @note         RTE_WOWP_EVENTS              = 4
  *               RTE_NUM_ALARMS               = 0
  *               RTE_NUM_TASKS                = 22
  *               RTE_TASKS_ARRAYSIZE          = 22
  *               RTE_MSITABLE_SIZE            = 0
  *               RTE_NULL_SCHEDULE            = 0
  *               RTE_OS_EVENTS                = 1
  *               RTE_CALPRM_INITRAM           = 0
  *               RTE_IMODEINIT                = 0
  *               RTE_ONSTART                  = 0
  *               SCHM_IMODEINIT               = 0
  *               RTE_INITIALIZING             = 0
  *               RTE_REQUIRES_IOC             = 0
  *               RTE_RIPS_SUPPORT             = 0
  *               RTE_USE_GETCURRENTTASKALARM  = 0
  *               RTE_CALPRM_INITRAM_DEFAULTS  = 0
  *
  *               OPT_MEMMAP_DECLARATIONS      = 1
  *               OPT_OS_TASK_AS_FUNCTION      = 0
  *
  *               RTE_LIB_VER                  = 2
  *               RTE_VFBTRACECLIENTPREFIX     = []
  *               RTE_ARMAJOR                  = 4
  *               RTE_ARMINOR                  = 0
  *               RTE_ARPATCH                  = 3
  *
  * Template:     Id: Rte_Lib_c.template 45752 2015-03-04 19:46:15Z sha1yok
  */

/* [$Satisfies $SWS 2734] Generated code is independent of the micro-controller
 * Note that this requirement applies to the generated output as a whole. This
 * is just one place where we don't use micro-controller specific code!
 */

/* [$Satisfies $SWS 2250] RTE limited to AUTOSAR OS and COM APIs
 * Note that OS-vendor-specific extensions may be used but only when protected
 * with pre-processor guards on the appropriate OSENV_<name> symbol.
 */
/* [$Satisfies $SWS40 7519] SchM limited to AUTOSAR OS APIs
 * Note that OS-vendor-specific extensions may be used but only when protected
 * with pre-processor guards on the appropriate OSENV_<name> symbol.
 */


#define RTE_CORE


#include "Rte_Const.h" /* Must be included before os.h */
#include <Os.h>

#include "Rte.h"
#include "Rte_Main.h"
#include "Rte_Intl.h"
#ifndef RTE_OMIT_HOOKS
#include "Rte_Hook.h"
#endif

#define RTE_START_SEC_VAR_16BIT
#include "MemMap.h" /*lint !e537 permit multiple inclusion */
VAR(uint16, RTE_DATA) Rte_ResourceCount  = 0;
#define RTE_STOP_SEC_VAR_16BIT
#include "MemMap.h" /*lint !e537 permit multiple inclusion */

/* [$Satisfies $SWS 2535] */
/* [$Satisfies $SWS 2536] */
#define RTE_START_SEC_VAR_BOOLEAN
#include "MemMap.h" /*lint !e537 permit multiple inclusion */
VAR(boolean, RTE_DATA) Rte_Initialized = FALSE;
VAR(boolean, RTE_DATA) SchM_Initialized = FALSE;
#define RTE_STOP_SEC_VAR_BOOLEAN
#include "MemMap.h" /*lint !e537 permit multiple inclusion */






#define RTE_START_SEC_LIBCODE
#include "MemMap.h" /*lint !e537 permit multiple inclusion */

/* --------------------------------------------------------------------------- */
/** @brief Activate single runnable
  *
  * @param[in] c        Pointer to Rte_REContainerType defining runnable's tasks
  *                     and activation counter.
  *
  * @retval E_OK        No errror
  * @retval E_NOT_OK    Task activation failed
  */

/* [$Satisfies $SWS 3600] */

FUNC(Std_ReturnType, RTE_LIBCODE)
Rte_ActivateRE( Rte_REContainerRefType c )
{
   Std_ReturnType          status   = RTE_E_OK;

   /* [$Satisfies $SWS 3520] [$Satisfies $SWS40 7526] */
   if ( c->acnt )
   {
      *(c->acnt) = TRUE;
   }

   if ( c->task != RTE_TASK_REF_NO_TASK )
   {
      StatusType stat;

#if defined(RTE_VFB_TRACE)
#if (RTE_VFB_TRACE != 0)
      Rte_Task_Activate( RTE_TASK_FROM_REF( c->task ) );            /* [$Satisfies $SWS40 5091] */
#endif /* (RTE_VFB_TRACE != 0) */
#endif /* defined(RTE_VFB_TRACE)  */

      stat = ActivateTask( RTE_TASK_FROM_REF( c->task ) );
      if ( ( E_OK != stat ) && ( E_OS_LIMIT != stat ) )
      {
         /* E_OS_LIMIT is an acceptable return code, because that
          * means that the task is already running. */
         status = E_NOT_OK;
      }
   }
   /* rte_sws_end 3520 */
   /* rte_sws_end 7526 */

   return status;
}
/* rte_sws_end 3600 */

/* --------------------------------------------------------------------------- */
/** @brief Remove task \\a index from `waiting' for the referenced waitable datum
  *
  * @param[in] datum    RTE waitable datum
  * @param[in] index    Task index
  * @param[in] event    RTE event
  *
  * @return None
  */

FUNC(void, RTE_LIBCODE)
Rte_DecrementWaitingCount( P2VAR(Rte_WaitableDatum, AUTOMATIC, RTE_DATA) datum,
                           Rte_TaskArrayIndex index,
                           Rte_EventType event )
{
   *Rte_Tasks[index].waitingEv = RTE_WOWP_EVENTS;
   if ( 0 < --datum->count )
   {
      /* There is still something waiting */

      boolean found = FALSE;

      for ( index = 0; ( !found ) && ( index < RTE_TASKS_ARRAYSIZE ); index++ )
      {
         P2CONST(Rte_EventType, AUTOMATIC, RTE_DATA)  evPtr = Rte_Tasks[index].waitingEv;
         if ( (evPtr) && (*evPtr == event) )
         {
            datum->firstWaitingTask = index;
            found = TRUE;
         }
      }
   }
}


/* --------------------------------------------------------------------------- */
/** @brief Get index of specified task
  *
  * @param[in] taskref  Reference to a task
  *
  * @return Task index
  */

FUNC(Rte_TaskArrayIndex, RTE_LIBCODE)
Rte_GetCurrentTaskIndex( P2VAR(TaskType, AUTOMATIC, RTE_DATA) taskRef )
{
   Rte_TaskArrayIndex   i;

   if ( E_OK == GetTaskID( taskRef ) )
   {
      /* search a table mapping task ids to alarms for the currently running task */
      for ( i = 0; i < RTE_TASKS_ARRAYSIZE; i++ )
      {
         if ( RTE_TASK_FROM_REF( Rte_Tasks[i].task ) == *taskRef )
         {
            /*lint -e(904) Allow early return */
            return i;
         }
      }
   }

   return RTE_TASKS_ARRAYSIZE;
}



/* --------------------------------------------------------------------------- */
/** @brief RTE Main function
  *
  * @return None
  *
  * @note   Required to be invoked at the specified rate (default: 10ms) when
  *         at least one runnable has a positive minimum start interval defined.
  *         In no runnables have a minimum start interval then the body of this
  *         function is empty.
  */

FUNC(void, RTE_LIBCODE)
Rte_MainFunction(void)
{
   /* No MSI -- empty function */
}

/* --------------------------------------------------------------------------- */
/** @brief Read entry from RTE managed queue
  *
  * @param[in] q        Handle of queue common data structure
  * @param[out] data    Pointer to output data location
  *
  * @retval RTE_E_NO_DATA   No data to read
  * @retval RTE_E_TIMEOUT   Timeout expired before data available to read
  * @retval RTE_E_LOST_DATA Data returned but (at least one) previous value lost
  * @retval RTE_OK          No error
  */

/* [$Satisfies $SWS 2519] */
FUNC(Std_ReturnType, RTE_LIBCODE)
Rte_ReadQueue( Rte_QCmnRefType  q,
               Rte_VarDataPtr   data )
{
   Std_ReturnType  status   = RTE_E_OK;                         /* [$Satisfies $SWS 1093] [$Satisfies $SWS 2598] */
   P2VAR(Rte_QDynType, AUTOMATIC, RTE_DATA)   dynamic  = q->dynamic;

   /* If this is a WOWP queue then wait for some data to arrive if there is
    * none */
   if ( RTE_WOWP == q->notification_type )
   {
      Rte_WOWP_NotificationRefType  wowp  = ((Rte_QRefWWPType)q)->wwp;
      if ( 0u == dynamic->used )
      {
         status = Rte_WaitWithTimeout( wowp->wd, wowp->event_id, wowp->timeout ); /* [$Satisfies $SWS 6013] */
      }
      else
      {
         wowp->wd->pending = 0;
      }
   }

   if ( RTE_E_OK == status )
   {
      /* [$Satisfies $SWS40 7673] */

      /* protect queue access */
      Rte_SuspendOSInterrupts();

      if ( 0u == dynamic->used )
      {
         if ( dynamic->lost_data != RTE_E_COM_STOPPED ) /* [$Satisfies $SWS 1106] [$Satisfies $SWS 3606] */
         {
            status = RTE_E_NO_DATA;    /* [$Satisfies $SWS 1113] [$Satisfies $SWS 1084] [$Satisfies $SWS 1094] [$Satisfies $SWS 6012] [$Satisfies $SWS 2525] */
         }
      }
      else
      {
         /* [$Satisfies $SWS 2522] [$Satisfies $SWS 2527] */
         /* copy data (be it the actual data, or a pointer) from the
          * queue buffer to the address specified by data */
         ( void )Rte_memcpy( data, dynamic->out, q->element_size );

         /*lint --e{960} Allow pointer arithmetic other than array indexing */
         dynamic->out = (P2VAR(uint8, AUTOMATIC, RTE_DATA)) ( dynamic->out ) + q->element_size;

         /*lint --e{946} Relational operation for pointers valid */
         if ( dynamic->out >= q->buffer_end )
         {
            /* wrap the out pointer */
            dynamic->out = q->buffer_start;
         }
         dynamic->used--;
      }

      Rte_ResumeOSInterrupts();
   }

   /* [$Satisfies $SWS 2524] */
   status |= dynamic->lost_data;
   dynamic->lost_data = 0;

   return status;
}

/* --------------------------------------------------------------------------- */
/** @brief Set event for specified RTE waitable datum
  */

FUNC(Std_ReturnType, RTE_LIBCODE)
Rte_SetEvent( P2VAR(Rte_WaitableDatum, AUTOMATIC, RTE_DATA) datum,
              Rte_EventType event )
{
   Std_ReturnType status   = RTE_E_OK;

   /* Note that events are numbered from 1 */
   if ( event > (Rte_EventType)RTE_WOWP_EVENTS )
   {
      status = E_NOT_OK;
   }
   else
   {
      Rte_SuspendOSInterrupts();
      if ( datum->count )
      {
         /* There is at least one task waiting on this datum */
         Rte_TaskArrayIndex   index = datum->firstWaitingTask;
         TaskType tref = RTE_TASK_FROM_REF( Rte_Tasks[index].task );

         Rte_ResumeOSInterrupts();

#if defined(RTE_VFB_TRACE)
#if (RTE_VFB_TRACE != 0)
         Rte_Task_SetEvent( tref , Rte_Activity ); /* [$Satisfies $SWS40 5091] */
#endif /* (RTE_VFB_TRACE != 0) */
#endif /* defined(RTE_VFB_TRACE)  */
         if ( E_OK != SetEvent( tref, Rte_Activity ) )
         {
            status = E_NOT_OK;
         }

         Rte_SuspendOSInterrupts();

         Rte_DecrementWaitingCount( datum, index, event );
      }
      else
      {
         datum->pending = 1;
      }

      Rte_ResumeOSInterrupts();
   }

   return status;
}

/* --------------------------------------------------------------------------- */
/** @brief Start RTE
  *
  * @retval RTE_E_LIMIT Failed to start periodic REs
  * @retval RTE_E_OK    No error detected
  */

/* [$Satisfies $SWS 1197] */
/* [$Satisfies $SWS 1309] */
/* [$Satisfies $SRD 87483] Rte_Start starts RTE for entire ECU */
/* [$Satisfies $SRD 87726] */
FUNC(Std_ReturnType, RTE_LIBCODE)
Rte_Start(void)                          /* [$Satisfies $SWS 2569] */
{
   Std_ReturnType rtn = RTE_E_OK;                       /* [$Satisfies $SWS 1261] */


  Rte_StartHook_Start();                               /* [$Satisfies $SWS 1238] [$Satisfies $SWS 5091] */




   Rte_Initialized = TRUE;                              /* [$Satisfies $SWS 2535] [$Satisfies $SWS 2536] */



#if defined(RTE_OSAPI_AUTOSAR_R10)
   /* [$Satisfies $SWS40 7575] */
   if ( E_OK != StartScheduleTable(Rte_ScheduleTable, (TickType)0u) )
   {
      rtn = RTE_E_LIMIT;                                /* [$Satisfies $SWS 1262] */
   }
#elif defined(RTE_OSAPI_AUTOSAR_R30) || defined(RTE_OSAPI_AUTOSAR_R40)
   /* [$Satisfies $SWS40 7575] */
   if ( E_OK != StartScheduleTableRel( Rte_ScheduleTable, (TickType)1u ) )
   {
      rtn = RTE_E_LIMIT;                                /* [$Satisfies $SWS 1262] */
   }
#endif /* !defined(RTE_OSAPI_AUTOSAR_R30) */


#if defined(RTE_OSAPI_ERCOSEK)
   /* [$Satisfies $SWS40 7575] */
   if ( E_OK != ActivateTimeTableRel(MICROSECONDS_TO_TICKS(0)) )
   {
      rtn = RTE_E_LIMIT;
   }
#endif /* defined(RTE_OSAPI_ERCOSEK) */


   Rte_StartHook_Return();                              /* [$Satisfies $SWS 1239] [$Satisfies $SWS40 5091] */

   return rtn;                                          /* [$Satisfies $SWS 2585] */
}
/* rte_sws_end 1309 */
/* rte_sws_end 1197 */

/* --------------------------------------------------------------------------- */
/** @brief Stop RTE
  *
  * @retval RTE_E_LIMIT Failed to stop periodic REs
  * @retval RTE_E_OK    No error detected
  */

/* [$Satisfies $SWS 1197] */
/* [$Satisfies $SWS 1310] */
FUNC(Std_ReturnType, RTE_LIBCODE)
Rte_Stop(void)                           /* [$Satisfies $SWS 2570] */
{
   Std_ReturnType rtn = RTE_E_OK;                       /* [$Satisfies $SWS 1259] */


   Rte_StopHook_Start(); /* [$Satisfies $SWS 1238] [$Satisfies $SWS40 5091] */

   Rte_Initialized = FALSE;                             /* [$Satisfies $SWS 2535] [$Satisfies $SWS 2536] */

   /*lint --e(960) Allow multiple defined(xxx) with logical operator */
#if defined(RTE_OSAPI_AUTOSAR_R10) || defined(RTE_OSAPI_AUTOSAR_R30) || defined(RTE_OSAPI_AUTOSAR_R40)
   if ( E_OK != StopScheduleTable(Rte_ScheduleTable) )
   {
      rtn = RTE_E_LIMIT;                                /* [$Satisfies $SWS 1260] */
   }
#endif /* defined(RTE_OSAPI_AUTOSAR_R10) */


#if defined(RTE_OSAPI_ERCOSEK)
   if ( E_OK != CancelTimeTable() )
   {
      rtn = RTE_E_LIMIT;
   }
#endif /* defined(RTE_OSAPI_ERCOSEK) */

   /* [$Satisfies $SWS 2538] All (periodic) REs stopped, all communication activity stopped. */

   Rte_StopHook_Return();                               /* [$Satisfies $SWS 1239] [$Satisfies $SWS40 5091] */

   return rtn;                                          /* [$Satisfies $SWS 2584] */
}
/* rte_sws_end 1310 */
/* rte_sws_end 1197 */

/* --------------------------------------------------------------------------- */
/** @brief Initialize SchM
  *
  */

/* [$Satisfies $SWS40 7271] */
/* [$Satisfies $SWS40 7273] */
FUNC(void, RTE_LIBCODE)
SchM_Init( void )     /* [$Satisfies $SWS40 7270] [$Satisfies $SWS40 6544] [$Satisfies $SWS40 6545] */
{
#if !defined(RTE_OMIT_UNINIT_CHECK)
   if ( SchM_Initialized ) {
       /* [$Satisfies $ExternalSWS40 7272] Called SchM_Init more than once */
   }
   else
#endif /* !defined(RTE_OMIT_UNINIT_CHECK) */
   {
      /* [$Satisfies $SWS40 7532] */
      SchM_Initialized = TRUE;
   }
}
/* rte_sws_end 7273 */
/* rte_sws_end 7271 */

/* --------------------------------------------------------------------------- */
/** @brief De-Initialize SchM
  *
  */

/* [$Satisfies $SWS40 7275] */
/* [$Satisfies $SWS40 7277] */
FUNC(void, RTE_LIBCODE)
SchM_Deinit(void)                          /* [$Satisfies $SWS40 7274] */
{
#if !defined(RTE_OMIT_UNINIT_CHECK)
   if ( SchM_Initialized )
   {
       /* Do what? [$Satisfies $ExternalSWS40 7272] */
       SchM_Initialized = FALSE;
   }
#endif /* !defined(RTE_OMIT_UNINIT_CHECK) */
}
/* rte_sws_end 7277 */
/* rte_sws_end 7275 */

/* --------------------------------------------------------------------------- */
/** @brief Suspend waiting on WaitableDatum with optional timeout
  *
  * @param[in] datum    RTE waitable datum
  * @param[in] index    Task index
  * @param[in] timeout  Duration (in ticks) for timeout. If 0 no timeout applied.
  *
  * @return None
  */

FUNC(Std_ReturnType, RTE_LIBCODE)
Rte_WaitWithTimeout( P2VAR(Rte_WaitableDatum, AUTOMATIC, RTE_DATA) datum,
                     Rte_EventType event,
                     const TickType timeout )
{
   TaskType             task;
   AlarmType            alarm = 0;                    /* Initial value serves only to avoid compiler warnings */
   EventMaskType        hit_event;
   Rte_TaskArrayIndex   index = Rte_GetCurrentTaskIndex( &task );    /* task gets initialised during this call */

   if ( index == RTE_TASKS_ARRAYSIZE )
   {
      /*lint -e(904) Allow early return */
      return E_NOT_OK;
   }

   /* Set up the timeout alarm */
   if ( (TickType)0 != timeout )
   {
      alarm = RTE_ALARM_FROM_INDEX( Rte_Tasks[index].alarm );
      if ( E_OK != SetRelAlarm( alarm, timeout, 0uL ) )
      {
         /*lint -e(904) Allow early return */
         return E_NOT_OK;
      }
   }

   /* Record what we're waiting for */
   Rte_SuspendOSInterrupts();

   if ( 0 == datum->count++ )
   {
      /* We're the first task waiting on the datum */
      if ( datum->pending != 0 )
      {
         /* Event already happened... consume it */
         datum->count = 0;
         datum->pending = 0;
         Rte_ResumeOSInterrupts();

         /* Activity occurred: perform tidy up */
         if ( (TickType)0 != timeout )
         {
            ( void )CancelAlarm( alarm );
         }

         /*lint -e(904) Allow early return */
         return RTE_E_OK;
      }

      /* Claim this datum as ours */
      datum->firstWaitingTask = index;
   }
   *Rte_Tasks[index].waitingEv = event;

   /* Wait */
   Rte_ResumeOSInterrupts();

#if defined(RTE_VFB_TRACE)
#if (RTE_VFB_TRACE != 0)
   Rte_Task_WaitEvent( task, Rte_Activity | Rte_Timeout ); /* [$Satisfies $SWS40 5091] */
#endif /* (RTE_VFB_TRACE != 0) */
#endif /* defined(RTE_VFB_TRACE)  */
   /*lint --e(506) */
   if ( E_OK != WaitEvent( Rte_Activity | Rte_Timeout ) )
   {
      /*lint -e(904) Allow early return */
      return E_NOT_OK;
   }

   /* Determine what event(s) caused us to exit WaitEvent */
   if ( E_OK != GetEvent( task, &hit_event ) )
   {
      /*lint -e(904) Allow early return */
      return E_NOT_OK;
   }

#if defined(RTE_VFB_TRACE)
#if (RTE_VFB_TRACE != 0)
   Rte_Task_WaitEventRet( task, hit_event ); /* [$Satisfies $SWS40 5091] */
#endif /* (RTE_VFB_TRACE != 0) */
#endif /* defined(RTE_VFB_TRACE)  */

   /* Act on the event(s) */
   if ( (EventMaskType)0 == ( hit_event & Rte_Activity ) )
   {
      /* no activity => timeout */
      ( void )ClearEvent( Rte_Timeout );

      Rte_SuspendOSInterrupts();
      /* Decrement the waiting count */
      Rte_DecrementWaitingCount( datum, index, event );

      Rte_ResumeOSInterrupts();

      /*lint -e(904) Allow early return */
      return RTE_E_TIMEOUT;   /* [$Satisfies $SWS 1095] [$Satisfies $SWS 1107] */
   }

   /* Activity occurred: perform tidy up */
   if ( (TickType)0 != timeout )
   {
      ( void )CancelAlarm( alarm );
   }

   /* clear event just in case alarm went off in the mean time */
   ( void )ClearEvent( Rte_Activity | Rte_Timeout );

   return RTE_E_OK;
}

/* --------------------------------------------------------------------------- */
/** @brief Write \\c data to RTE managed queue \\c q
  *
  * @param[in] q        Handle of queue common data structure
  * @param[in] data     Pointer to input data
  *
  * @retval RTE_E_LIMIT     Queue full (data discarded)
  * @retval RTE_E_NOT_OK    Call failed
  * @retval RTE_E_OK        No error detected
  */

/* [$Satisfies $SWS 6016] */
FUNC(Std_ReturnType, RTE_LIBCODE)
Rte_WriteQueue( Rte_QCmnRefType    q,
                Rte_ConstDataPtr   data )
{
   Std_ReturnType                            status   = RTE_E_OK;
   P2VAR(Rte_QDynType, AUTOMATIC, RTE_DATA)  dynamic  = q->dynamic;
   P2VAR(void, AUTOMATIC, RTE_DATA)          old_in;

   /* protect queue access */
   Rte_GetResource();

   if ( dynamic->used == q->queue_size )
   {
      /* [$Satisfies $SWS 2523] */
      dynamic->lost_data = RTE_E_LOST_DATA;          /* [$Satisfies $SWS 2572] */
      status = RTE_E_LIMIT;                          /* [$Satisfies $SWS 2634] */
   }
   else
   {
      /* [$Satisfies $SWS 2522] [$Satisfies $SWS 2527] */
      if ( q->copy )
      {
         /* queue keeps a copy of the data as its source does not persist */
         ( void )Rte_memcpy( dynamic->in, data, q->element_size );
      }
      else
      {
         /* queue keeps a reference to the data as its source persists
          * long enough for the item to be consumed */
         *( P2VAR(Rte_ConstDataPtr, AUTOMATIC, RTE_DATA) )dynamic->in = data;
      }
      /* rte_sws_end 2522 rte_sws_end 2527 */

      old_in = dynamic->in;

      /*lint --e{960} Allow pointer arithmetic other than array indexing */
      dynamic->in = (P2VAR(uint8, AUTOMATIC, RTE_DATA)) ( dynamic->in ) + q->element_size;

      /*lint  --e{946} Relational operation for pointers valid */
      if ( dynamic->in >= q->buffer_end )
      {
         dynamic->in = q->buffer_start;
      }
      dynamic->used++;

      switch ( q->notification_type )
      {
         default:
         case RTE_DRA:
            /* No notification required */
            break;

         case RTE_WOWP:
         {
            Rte_WOWP_NotificationRefType  wowp  = ((Rte_QRefWWPType)q)->wwp;

            status = Rte_SetEvent( wowp->wd, wowp->event_id );
            break;
         }

         case RTE_TASK:
         {
            StatusType act_stat;
#if defined(RTE_VFB_TRACE)
#if (RTE_VFB_TRACE != 0)
            Rte_Task_Activate( RTE_TASK_FROM_REF( ((Rte_QRefTaskType)q)->task ) ); /* [$Satisfies $SWS40 5091] */
#endif /* (RTE_VFB_TRACE != 0) */
#endif /* defined(RTE_VFB_TRACE) */
            act_stat = ActivateTask( RTE_TASK_FROM_REF( ((Rte_QRefTaskType)q)->task ) ); /* [$Satisfies $SWS 2203] */
            if ( ( E_OK != act_stat ) && ( E_OS_LIMIT != act_stat ) )
            {
               /* E_OS_LIMIT is an acceptable return code, because that means
                * that the task is already running and already activated (tasks
                * contain OperationInvokedEvents are required to have
                * activation limit two), so it will run again. */

               /* restore 'in' and 'used' */
               dynamic->in = old_in;
               dynamic->used--;
               status = E_NOT_OK;
            }
            break;
         }

         case RTE_ARE:
         {
            /* rte_srd_req 482 begin */
            if ( RTE_E_OK != Rte_ActivateRE( ((Rte_QRefREType)q)->re ) ) /* [$Satisfies $SWS 2203] */
            {
               /* restore 'in' and 'used' */
               dynamic->in = old_in;
               dynamic->used--;
               status = E_NOT_OK;
            }
            /* rte_srd_req 482 end */
            break;
         }


         case RTE_EV:
         {
#if defined(RTE_VFB_TRACE)
#if (RTE_VFB_TRACE != 0)
            Rte_Task_SetEvent( RTE_TASK_FROM_REF( ((Rte_QRefEvType)q)->task ),
                               RTE_EVENT_FROM_REF( ((Rte_QRefEvType)q)->mask ) ); /* [$Satisfies $SWS40 5091] */
#endif /* (RTE_VFB_TRACE != 0) */
#endif /* defined(RTE_VFB_TRACE)  */
            if ( E_OK != SetEvent( RTE_TASK_FROM_REF(  ((Rte_QRefEvType)q)->task ),
                                   RTE_EVENT_FROM_REF( ((Rte_QRefEvType)q)->mask ) ) )
            {
               status = E_NOT_OK;
            }
         }
         break;
      }
   }

   Rte_ReleaseResource();

   return status;
}

/* --------------------------------------------------------------------------- */
/** @brief RTE memcpy replacement
  *
  * @param[in] dst      Destination pointer
  * @param[in] src      Pointer to data source
  * @param[in] length   Data length (in bytes)
  *
  * @return None
  *
  * @note Used to avoid dependency on run-time C library
  */

#if defined(Rte_memcpy)
#undef Rte_memcpy
#endif

#if !defined(RTE_LIBC_MEMCPY)
FUNC(void, RTE_LIBCODE)
Rte_memcpy(P2VAR(void, AUTOMATIC, RTE_DATA) dst,
           P2CONST(void, AUTOMATIC, RTE_APPL_DATA) src,
           uint16 length)
{
   P2VAR(uint8, AUTOMATIC, RTE_DATA)           d = (P2VAR(uint8, AUTOMATIC, RTE_DATA))dst;
   P2CONST(uint8, AUTOMATIC, RTE_APPL_DATA)    s = (P2CONST(uint8, AUTOMATIC, RTE_APPL_DATA))src;

   while(length--)
   {
      /*lint --e{960} Allow pointer arithmetic by increment or decrement */
      *d++ = *s++;
   }
}
#endif /* !defined(RTE_LIBC_MEMCPY) */

#define RTE_STOP_SEC_LIBCODE
#include "MemMap.h" /*lint !e537 permit multiple inclusion */

