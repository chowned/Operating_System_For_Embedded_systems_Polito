/**
 * @file tpl_app_config.c
 *
 * @section desc File description
 *
 * OS data structure generated from application only_one_periodic_task
 * Automatically generated by goil on Thu Nov 17 22:29:30 2022
 * from root OIL file lab02_ex01.oil
 *
 * @section copyright Copyright
 *
 * Trampoline OS
 *
 * Trampoline is copyright (c) IRCCyN 2005-2007
 * Trampoline is protected by the French intellectual property law.
 *
 * This software is distributed under the Lesser GNU Public Licence
 *
 * @section infos File informations
 *
 * $Date$
 * $Rev$
 * $Author$
 * $URL$
 */

#include <stdbool.h>
#include <stdint.h>

#include "tpl_app_config.h"

#include "tpl_os_internal_types.h"
#include "tpl_machine.h"
#include "tpl_os_interrupt.h"
#include "tpl_os_interrupt_kernel.h"
#include "tpl_os_alarm_kernel.h"
#include "tpl_os_alarm.h"
#include "tpl_os_resource_kernel.h"
#include "tpl_os_resource.h"
#include "tpl_os_event_kernel.h"
#include "tpl_os_event.h"
#include "tpl_os_action.h"
#include "tpl_os_kernel.h"
#include "tpl_os_definitions.h"


#include "tpl_com_notification.h"
#include "tpl_com_mo.h"
#include "tpl_com_internal.h"
#include "tpl_com_internal_com.h"
/*#include "tpl_com_external_com.h"*/
#include "tpl_com_app_copy.h"
#include "tpl_com_filters.h"

/*=============================================================================
 * Application Modes tables for tasks, alarms and schedule tables
 * Application Modes masks are as follow:
 * stdAppmode = 1
 */

CONST(tpl_application_mode, OS_CONST) stdAppmode = 0; /* mask = 1 */
CONST(tpl_application_mode, OS_CONST) OSDEFAULTAPPMODE = 0;
CONST(tpl_appmode_mask, OS_CONST) tpl_task_app_mode[TASK_COUNT] = {
  0 /* task TaskPWM :  */ ,
  1 /* task TaskADC : stdAppmode */ 
};

CONST(tpl_appmode_mask, OS_CONST) tpl_alarm_app_mode[ALARM_COUNT] = {
  1 /* alarm aADC : stdAppmode */ ,
  1 /* alarm aPWM : stdAppmode */ 
};

#define API_START_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"

/*=============================================================================
 * Declaration of processes IDs
 */

/* Task TaskPWM identifier */
#define TaskPWM_id 0
CONST(TaskType, AUTOMATIC) TaskPWM = TaskPWM_id;

/* Task TaskADC identifier */
#define TaskADC_id 1
CONST(TaskType, AUTOMATIC) TaskADC = TaskADC_id;

/*=============================================================================
 * Declaration of Alarm IDs
 */

/* Alarm aADC identifier */
#define aADC_id 0
CONST(AlarmType, AUTOMATIC) aADC = aADC_id;

/* Alarm aPWM identifier */
#define aPWM_id 1
CONST(AlarmType, AUTOMATIC) aPWM = aPWM_id;

/*=============================================================================
 * Declaration of receive messages IDs
 */

/* Message msgDataReceiveUnqueued identifier */
#define msgDataReceiveUnqueued_id 0
CONST(MessageIdentifier, AUTOMATIC) msgDataReceiveUnqueued = msgDataReceiveUnqueued_id;

/*=============================================================================
 * Declaration of send messages IDs
 */

/* Message msgDataSend identifier */
#define msgDataSend_id 0
CONST(MessageIdentifier, AUTOMATIC) msgDataSend = msgDataSend_id;

#define API_STOP_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"

/**
 * The scheduler resource descriptor.
 * One scheduler resource is defined per core.
 *
 * @see #RES_SCHEDULER
 */

#define OS_START_SEC_VAR_UNSPECIFIED
#include "tpl_memmap.h"
VAR(tpl_resource, OS_VAR) res_sched_rez_desc = {
  RES_SCHEDULER_PRIORITY,   /*  ceiling priority                            */
  0,                        /*  owner_prev_priority                         */
  INVALID_PROC_ID,          /*  owner                                       */
#if WITH_OSAPPLICATION == YES
  INVALID_OSAPPLICATION_ID, /*  OS Application id                           */
#endif

  NULL                      /*  next_res                                    */
};
#define OS_STOP_SEC_VAR_UNSPECIFIED
#include "tpl_memmap.h"

#define OS_START_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"
CONSTP2VAR(tpl_resource, AUTOMATIC, OS_APPL_DATA)
tpl_resource_table[RESOURCE_COUNT] = {
  &res_sched_rez_desc
};

#define OS_STOP_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"

/*=============================================================================
 * Definition and initialization of Counters related defines and structures
 */
/*-----------------------------------------------------------------------------
 * Counter SystemCounter descriptor
 */

#define API_START_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"

CONST(tpl_tick, OS_CONST) OSTICKSPERBASE = 1;
CONST(tpl_tick, OS_CONST) OSMAXALLOWEDVALUE = 65535;
CONST(tpl_tick, OS_CONST) OSMINCYCLE = 1;

#define API_STOP_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"

#define OS_START_SEC_VAR_UNSPECIFIED
#include "tpl_memmap.h"

VAR(tpl_counter, OS_VAR) SystemCounter_counter_desc = {
  /* ticks per base       */  1,
  /* max allowed value    */  65535,
  /* minimum cycle        */  1,
  /* current tick         */  0,
  /* current date         */  0,
#if WITH_OSAPPLICATION == YES
    /* OS Application id    */  
#endif
    /* first alarm          */  NULL_PTR,
    /* next alarm to raise  */  NULL_PTR
};

#define OS_STOP_SEC_VAR_UNSPECIFIED
#include "tpl_memmap.h"

#include "tpl_os_kernel.h"          /* tpl_schedule */
#include "tpl_os_timeobj_kernel.h"  /* tpl_counter_tick */
#include "tpl_machine_interface.h"  /* tpl_switch_context_from_it */

#define OS_START_SEC_CODE
#include "tpl_memmap.h"

//gcc uses ISR as a keyword to define an interrupt handler.
//Osek uses ISR to define an ISR2 :-/
#ifdef ISR
 #undef ISR
#endif
#include <avr/interrupt.h>

//function defined in avr assembly files.
FUNC(void, OS_CODE) tpl_avr_counter_tick(
    P2VAR(tpl_counter, AUTOMATIC, OS_APPL_DATA) counter);


void trampolineSystemCounter()
{
  tpl_avr_counter_tick(&SystemCounter_counter_desc);
}
  
#define OS_STOP_SEC_CODE
#include "tpl_memmap.h"

/*=============================================================================
 * Descriptor(s) of the idle task(s)
 */
/*-----------------------------------------------------------------------------
 * Task IDLE_TASK descriptor
 */
#define OS_START_SEC_CODE
#include "tpl_memmap.h"
/*
 * Task IDLE_TASK function prototype
 */

FUNC(void, OS_APPL_CODE) idle_function(void);
#define OS_STOP_SEC_CODE
#include "tpl_memmap.h"

/*-----------------------------------------------------------------------------
 * Target specific structures
 */

/*
 * Task IDLE_TASK stack
 *
 */
#define APP_Task_IDLE_TASK_START_SEC_STACK
#include "tpl_memmap.h"
tpl_stack_word IDLE_TASK_stack_zone[IDLE_STACK_SIZE/sizeof(tpl_stack_word)];
#define APP_Task_IDLE_TASK_STOP_SEC_STACK
#include "tpl_memmap.h"

#define OS_START_SEC_VAR_UNSPECIFIED
#include "tpl_memmap.h"

#define IDLE_TASK_STACK { IDLE_TASK_stack_zone, IDLE_STACK_SIZE }

/*
 * Task IDLE_TASK context
 */
avr_context IDLE_TASK_int_context;
#define IDLE_TASK_CONTEXT &IDLE_TASK_int_context

#define OS_STOP_SEC_VAR_UNSPECIFIED
#include "tpl_memmap.h"




/*
  No timing protection
 */

#define OS_START_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"


/*
 * Static descriptor of task IDLE_TASK
 */
CONST(tpl_proc_static, OS_CONST) IDLE_TASK_task_stat_desc = {
  /* context                  */  IDLE_TASK_CONTEXT,
  /* stack                    */  IDLE_TASK_STACK,
  /* entry point (function)   */  idle_function,
  /* internal ressource       */  NULL,
  /* task id                  */  IDLE_TASK_ID,
#if WITH_OSAPPLICATION == YES
  /* OS application id        */  
#endif
  /* task base priority       */  0,
  /* max activation count     */  1,
  /* task type                */  TASK_BASIC,
#if WITH_AUTOSAR_TIMING_PROTECTION == YES

  /* execution budget */        0,
  /* timeframe        */        0, 
  /* pointer to the timing
     protection descriptor    */ NULL

#endif
};

#define OS_STOP_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"


#define OS_START_SEC_VAR_UNSPECIFIED
#include "tpl_memmap.h"
/*
 * Dynamic descriptor of task IDLE_TASK
 */
VAR(tpl_proc, OS_VAR) IDLE_TASK_task_desc = {
  /* resources                      */  NULL,
#if WITH_OSAPPLICATION == YES
  /* if > 0 the process is trusted  */  0,    
#endif /* WITH_OSAPPLICATION */
  /* activate count                 */  0,
  /* task priority                  */  0,
  /* task state                     */  SUSPENDED
};

#define OS_STOP_SEC_VAR_UNSPECIFIED
#include "tpl_memmap.h"


/*=============================================================================
 * Definition and initialization of Task related defines and structures
 */
/*-----------------------------------------------------------------------------
 * Task TaskPWM descriptor
 */
#define APP_Task_TaskPWM_START_SEC_CODE

#include "tpl_memmap.h"
/*
 * Task TaskPWM function prototype
 */

FUNC(void, OS_APPL_CODE) TaskPWM_function(void);
#define APP_Task_TaskPWM_STOP_SEC_CODE

#include "tpl_memmap.h"

/*-----------------------------------------------------------------------------
 * Target specific structures
 */

/*
 * Task TaskPWM stack
 *
 */
#define APP_Task_TaskPWM_START_SEC_STACK
#include "tpl_memmap.h"
tpl_stack_word TaskPWM_stack_zone[256/sizeof(tpl_stack_word)];
#define APP_Task_TaskPWM_STOP_SEC_STACK
#include "tpl_memmap.h"

#define OS_START_SEC_VAR_UNSPECIFIED
#include "tpl_memmap.h"

#define TaskPWM_STACK { TaskPWM_stack_zone, 256 }

/*
 * Task TaskPWM context
 */
avr_context TaskPWM_int_context;
#define TaskPWM_CONTEXT &TaskPWM_int_context

#define OS_STOP_SEC_VAR_UNSPECIFIED
#include "tpl_memmap.h"




/*
  No timing protection
 */

#define OS_START_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"


/*
 * Static descriptor of task TaskPWM
 */
CONST(tpl_proc_static, OS_CONST) TaskPWM_task_stat_desc = {
  /* context                  */  TaskPWM_CONTEXT,
  /* stack                    */  TaskPWM_STACK,
  /* entry point (function)   */  TaskPWM_function,
  /* internal ressource       */  NULL,
  /* task id                  */  TaskPWM_id,
#if WITH_OSAPPLICATION == YES
  /* OS application id        */  
#endif
  /* task base priority       */  1,
  /* max activation count     */  1,
  /* task type                */  TASK_BASIC,
#if WITH_AUTOSAR_TIMING_PROTECTION == YES

  /* execution budget */        0,
  /* timeframe        */        0, 
  /* pointer to the timing
     protection descriptor    */ NULL

#endif
};

#define OS_STOP_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"


#define OS_START_SEC_VAR_UNSPECIFIED
#include "tpl_memmap.h"
/*
 * Dynamic descriptor of task TaskPWM
 */
VAR(tpl_proc, OS_VAR) TaskPWM_task_desc = {
  /* resources                      */  NULL,
#if WITH_OSAPPLICATION == YES
  /* if > 0 the process is trusted  */  0,    
#endif /* WITH_OSAPPLICATION */
  /* activate count                 */  0,
  /* task priority                  */  1,
  /* task state                     */  SUSPENDED
};

#define OS_STOP_SEC_VAR_UNSPECIFIED
#include "tpl_memmap.h"

/*-----------------------------------------------------------------------------
 * Task TaskADC descriptor
 */
#define APP_Task_TaskADC_START_SEC_CODE

#include "tpl_memmap.h"
/*
 * Task TaskADC function prototype
 */

FUNC(void, OS_APPL_CODE) TaskADC_function(void);
#define APP_Task_TaskADC_STOP_SEC_CODE

#include "tpl_memmap.h"

/*-----------------------------------------------------------------------------
 * Target specific structures
 */

/*
 * Task TaskADC stack
 *
 */
#define APP_Task_TaskADC_START_SEC_STACK
#include "tpl_memmap.h"
tpl_stack_word TaskADC_stack_zone[256/sizeof(tpl_stack_word)];
#define APP_Task_TaskADC_STOP_SEC_STACK
#include "tpl_memmap.h"

#define OS_START_SEC_VAR_UNSPECIFIED
#include "tpl_memmap.h"

#define TaskADC_STACK { TaskADC_stack_zone, 256 }

/*
 * Task TaskADC context
 */
avr_context TaskADC_int_context;
#define TaskADC_CONTEXT &TaskADC_int_context

#define OS_STOP_SEC_VAR_UNSPECIFIED
#include "tpl_memmap.h"




/*
  No timing protection
 */

#define OS_START_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"


/*
 * Static descriptor of task TaskADC
 */
CONST(tpl_proc_static, OS_CONST) TaskADC_task_stat_desc = {
  /* context                  */  TaskADC_CONTEXT,
  /* stack                    */  TaskADC_STACK,
  /* entry point (function)   */  TaskADC_function,
  /* internal ressource       */  NULL,
  /* task id                  */  TaskADC_id,
#if WITH_OSAPPLICATION == YES
  /* OS application id        */  
#endif
  /* task base priority       */  2,
  /* max activation count     */  1,
  /* task type                */  TASK_BASIC,
#if WITH_AUTOSAR_TIMING_PROTECTION == YES

  /* execution budget */        0,
  /* timeframe        */        0, 
  /* pointer to the timing
     protection descriptor    */ NULL

#endif
};

#define OS_STOP_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"


#define OS_START_SEC_VAR_UNSPECIFIED
#include "tpl_memmap.h"
/*
 * Dynamic descriptor of task TaskADC
 */
VAR(tpl_proc, OS_VAR) TaskADC_task_desc = {
  /* resources                      */  NULL,
#if WITH_OSAPPLICATION == YES
  /* if > 0 the process is trusted  */  0,    
#endif /* WITH_OSAPPLICATION */
  /* activate count                 */  0,
  /* task priority                  */  2,
  /* task state                     */  AUTOSTART
};

#define OS_STOP_SEC_VAR_UNSPECIFIED
#include "tpl_memmap.h"


#include "tpl_machine.h"
#define OS_START_SEC_CODE
#include "tpl_memmap.h"

//function defined in avr assembly files.
FUNC(void, OS_CODE) tpl_avr_ISR2_handler(CONST(uint16, AUTOMATIC) id);


#define OS_STOP_SEC_CODE
#include "tpl_memmap.h"

#define OS_START_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"
/*=============================================================================
 * Definition and initialization of process tables (tasks and isrs)
 */
CONSTP2CONST(tpl_proc_static, AUTOMATIC, OS_APPL_DATA)
tpl_stat_proc_table[TASK_COUNT+ISR_COUNT+1] = {
  &TaskPWM_task_stat_desc,
  &TaskADC_task_stat_desc,
  &IDLE_TASK_task_stat_desc
};

CONSTP2VAR(tpl_proc, AUTOMATIC, OS_APPL_DATA)
tpl_dyn_proc_table[TASK_COUNT+ISR_COUNT+1] = {
  &TaskPWM_task_desc,
  &TaskADC_task_desc,
  &IDLE_TASK_task_desc
};

#define OS_STOP_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"


/*=============================================================================
 * Definition and initialization of Alarm related structures
 */
/*-----------------------------------------------------------------------------
 * Alarm aADC descriptor
 *
 * This alarm does the activation of task TaskADC
 */


#define OS_START_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"

CONST(tpl_task_activation_action, OS_CONST) aADC_action = {
  {
    /* action function  */  tpl_action_activate_task
  },
  /* task id            */  TaskADC_id
};

#define OS_STOP_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"
 
#define OS_START_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"

CONST(tpl_alarm_static, OS_CONST) aADC_static = {
  {
    /* pointer to counter           */  &SystemCounter_counter_desc,
    /* pointer to the expiration    */  tpl_raise_alarm
#if (WITH_ID == YES)
    /* id of the alarm for tracing  */  , aADC_id
#endif
#if WITH_OSAPPLICATION == YES
    /* OS application id            */  , 
#endif
  },
  /* action of the alarm  */  (tpl_action *)&aADC_action
};

#define OS_STOP_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"

#define OS_START_SEC_VAR_UNSPECIFIED
#include "tpl_memmap.h"

VAR(tpl_time_obj, OS_VAR) aADC_alarm_desc = {
    /* pointer to the static part   */  (tpl_time_obj_static *)&aADC_static,
    /* next alarm                   */  NULL,
    /* prev alarm                   */  NULL,
    /* cycle                        */  293,
    /* date                         */  293,
    /* State of the alarm           */  ALARM_AUTOSTART
};

#define OS_STOP_SEC_VAR_UNSPECIFIED
#include "tpl_memmap.h"

/*-----------------------------------------------------------------------------
 * Alarm aPWM descriptor
 *
 * This alarm does the activation of task TaskPWM
 */


#define OS_START_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"

CONST(tpl_task_activation_action, OS_CONST) aPWM_action = {
  {
    /* action function  */  tpl_action_activate_task
  },
  /* task id            */  TaskPWM_id
};

#define OS_STOP_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"
 
#define OS_START_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"

CONST(tpl_alarm_static, OS_CONST) aPWM_static = {
  {
    /* pointer to counter           */  &SystemCounter_counter_desc,
    /* pointer to the expiration    */  tpl_raise_alarm
#if (WITH_ID == YES)
    /* id of the alarm for tracing  */  , aPWM_id
#endif
#if WITH_OSAPPLICATION == YES
    /* OS application id            */  , 
#endif
  },
  /* action of the alarm  */  (tpl_action *)&aPWM_action
};

#define OS_STOP_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"

#define OS_START_SEC_VAR_UNSPECIFIED
#include "tpl_memmap.h"

VAR(tpl_time_obj, OS_VAR) aPWM_alarm_desc = {
    /* pointer to the static part   */  (tpl_time_obj_static *)&aPWM_static,
    /* next alarm                   */  NULL,
    /* prev alarm                   */  NULL,
    /* cycle                        */  2,
    /* date                         */  2,
    /* State of the alarm           */  ALARM_AUTOSTART
};

#define OS_STOP_SEC_VAR_UNSPECIFIED
#include "tpl_memmap.h"


#define OS_START_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"
CONSTP2VAR(tpl_time_obj, AUTOMATIC, OS_APPL_DATA)
  tpl_alarm_table[ALARM_COUNT] = {
  &aADC_alarm_desc,
  &aPWM_alarm_desc
};
#define OS_STOP_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"

/*=============================================================================
 * Declaration of flags functions
 */
/* $FLAGSFUNCTIONS$ */


/*=============================================================================
 * Definitions of the custom filter functions
 * filter functions are generated according to the type
 * used for the corresponding message object
 */
/*
 * ALWAYS filter function for type uint8
 */

/*=============================================================================
 * Definition and initialization of Receive Messages related structures
 */

/*-----------------------------------------------------------------------------
 * Action of message msgDataReceiveUnqueued
 */

#define OS_START_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"

CONST(tpl_task_activation_action, OS_CONST) msgDataReceiveUnqueued_action = {
  {
    /* action function  */  tpl_action_activate_task
  },
  /* task id            */  TaskPWM_id
};

#define OS_STOP_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"
/*-----------------------------------------------------------------------------
 * ALWAYS filter of message object msgDataReceiveUnqueued
 */
#define OS_START_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"

tpl_noparam_filter_desc msgDataReceiveUnqueued_filter = {
    /*  filtering function          */  tpl_filter_always
};

#define OS_STOP_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"

/*-----------------------------------------------------------------------------
 * Static internal receiving unqueued message object msgDataReceiveUnqueued
 */
#define OS_START_SEC_VAR_UNSPECIFIED
#include "tpl_memmap.h"

VAR(uint8, OS_VAR) msgDataReceiveUnqueued_buffer = 0;

#define OS_STOP_SEC_VAR_UNSPECIFIED
#include "tpl_memmap.h"

#define OS_START_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"

CONST(tpl_internal_receiving_unqueued_mo, OS_CONST) msgDataReceiveUnqueued_message = {
  { /* data receiving mo struct   */
    { /* base receiving mo struct */
      /* notification pointer     */  (tpl_action *)&msgDataReceiveUnqueued_action,
      /*  next receiving mo       */  NULL
    },
    /*  receiving function      */  (tpl_receiving_func)tpl_receive_static_internal_unqueued_message,
    /*  copy function           */  (tpl_data_copy_func)tpl_copy_from_unqueued,
    /*  filter pointer          */  (tpl_filter_desc *)&msgDataReceiveUnqueued_filter
  },
  { /* buffer struct    */
    /*  buffer  */  (tpl_com_data *)&msgDataReceiveUnqueued_buffer,
    /*  size    */  sizeof(uint8)
  }
};

#define OS_STOP_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"

/*=============================================================================
 * Definition and initialization of the receive messages table
 */
#define OS_START_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"

CONSTP2CONST(tpl_base_receiving_mo, AUTOMATIC, OS_CONST)
tpl_receive_message_table[RECEIVE_MESSAGE_COUNT] = {
  (tpl_base_receiving_mo*)&msgDataReceiveUnqueued_message
};

#define OS_STOP_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"

/*=============================================================================
 * Definition and initialization of Send Messages related structures
 */
#define OS_START_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"

/*-----------------------------------------------------------------------------
 * Static internal sending static message object msgDataSend
 */
CONST(tpl_internal_sending_mo, OS_CONST) msgDataSend_message = {
  { /* base message object       */
    /* sending function          */ tpl_send_static_internal_message
  },
  /* pointer to the receiving mo */ (tpl_base_receiving_mo *)&msgDataReceiveUnqueued_message
};

#define OS_STOP_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"


/*=============================================================================
 * Definition and initialization of the send messages table
 */
#define OS_START_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"

CONSTP2CONST(tpl_base_sending_mo, AUTOMATIC, OS_CONST)
tpl_send_message_table[SEND_MESSAGE_COUNT] = {
  (tpl_base_sending_mo*)&msgDataSend_message
};

#define OS_STOP_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"
/*=============================================================================
 * Definition and initialization of Ready List structures
 */
#define OS_START_SEC_VAR_UNSPECIFIED
#include "tpl_memmap.h"

VAR(tpl_heap_entry, OS_VAR) tpl_ready_list[4];
VAR(tpl_rank_count, OS_VAR) tpl_tail_for_prio[4] = {
  0,
  0,
  0
};

#define OS_STOP_SEC_VAR_UNSPECIFIED
#include "tpl_memmap.h"

/**
 * @internal
 *
 * tpl_kern gather informations on the current executing object and
 * the previous one
 */
VAR(tpl_kern_state, OS_VAR) tpl_kern =
{
  NULL,                      /* no running task static descriptor   */
  &IDLE_TASK_task_stat_desc, /* elected task to run is idle task    */
  NULL,                      /* no running task dynamic descriptor  */
  &IDLE_TASK_task_desc,      /* elected task to run is idle task    */
  INVALID_PROC_ID,           /* no running task so no ID            */
  INVALID_PROC_ID,           /* idle task has no ID                 */
  NO_NEED_SWITCH,            /* no context switch needed at start   */
  FALSE,                     /* no schedule needed at start         */
#if WITH_MEMORY_PROTECTION == YES
  1,                         /* at early system startup, we run in  */
                             /*  kernel mode, so in trusted mode    */
#endif /* WITH_MEMORY_PROTECTION */
};

#define API_START_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"
CONSTP2CONST(char, AUTOMATIC, OS_APPL_DATA) proc_name_table[TASK_COUNT + ISR_COUNT + 1] = {

  "TaskPWM",
  "TaskADC",
  "*idle*"
};
#define API_STOP_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"


/* End of file tpl_app_config.c */
