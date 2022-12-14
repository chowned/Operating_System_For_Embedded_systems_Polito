/**
 * @file tpl_invoque.S
 *
 * @section descr File description
 *
 * System call user level invoque API.
 *
 * @warning this file is generated by gen_invoque.sh based on the 
 * tpl_os_service_ids.h header file.
 *
 * @section copyright Copyright
 *
 * Trampoline OS
 *
 * Trampoline is copyright (c) IRCCyN 2005+
 * Copyright ESEO for function and data structures documentation and ARM port
 * Trampoline is protected by the French intellectual property law.
 *
 * This software is distributed under the Lesser GNU Public Licence
 *
 * @section infos File informations
 *
 * $$Date$$
 * $$Rev$$
 * $$Author$$
 * $$URL$$
 */
#include "tpl_os_application_def.h"
#include "tpl_service_ids.h"

#if WITH_SYSTEM_CALL == NO
#error "This file should not be part of your project since WITH_SYSTEM_CALL is not defined"
#endif


#include "tpl_assembler.h"

#if WITH_MEMMAP == NO

#endif /* WITH_MEMMAP == NO */

#define API_START_SEC_CODE
#include "tpl_as_memmap.h"


  .global GetActiveApplicationMode
GetActiveApplicationMode:
  ldi r30,OSServiceId_GetActiveApplicationMode  /* load the service id in r30 */
  call tpl_sc_handler
  ret
  
  .type GetActiveApplicationMode,@function
//  .size GetActiveApplicationMode,$-GetActiveApplicationMode


  .global tpl_start_os
tpl_start_os:
  ldi r30,OSServiceId_StartOS  /* load the service id in r30 */
  call tpl_sc_handler
  ret
  
  .type tpl_start_os,@function
//  .size tpl_start_os,$-tpl_start_os


  .global ShutdownOS
ShutdownOS:
  ldi r30,OSServiceId_ShutdownOS  /* load the service id in r30 */
  call tpl_sc_handler
  ret
  
  .type ShutdownOS,@function
//  .size ShutdownOS,$-ShutdownOS


  .global EnableAllInterrupts
EnableAllInterrupts:
  ldi r30,OSServiceId_EnableAllInterrupts  /* load the service id in r30 */
  call tpl_sc_handler
  ret
  
  .type EnableAllInterrupts,@function
//  .size EnableAllInterrupts,$-EnableAllInterrupts


  .global DisableAllInterrupts
DisableAllInterrupts:
  ldi r30,OSServiceId_DisableAllInterrupts  /* load the service id in r30 */
  call tpl_sc_handler
  ret
  
  .type DisableAllInterrupts,@function
//  .size DisableAllInterrupts,$-DisableAllInterrupts


  .global ResumeAllInterrupts
ResumeAllInterrupts:
  ldi r30,OSServiceId_ResumeAllInterrupts  /* load the service id in r30 */
  call tpl_sc_handler
  ret
  
  .type ResumeAllInterrupts,@function
//  .size ResumeAllInterrupts,$-ResumeAllInterrupts


  .global SuspendAllInterrupts
SuspendAllInterrupts:
  ldi r30,OSServiceId_SuspendAllInterrupts  /* load the service id in r30 */
  call tpl_sc_handler
  ret
  
  .type SuspendAllInterrupts,@function
//  .size SuspendAllInterrupts,$-SuspendAllInterrupts


  .global ResumeOSInterrupts
ResumeOSInterrupts:
  ldi r30,OSServiceId_ResumeOSInterrupts  /* load the service id in r30 */
  call tpl_sc_handler
  ret
  
  .type ResumeOSInterrupts,@function
//  .size ResumeOSInterrupts,$-ResumeOSInterrupts


  .global SuspendOSInterrupts
SuspendOSInterrupts:
  ldi r30,OSServiceId_SuspendOSInterrupts  /* load the service id in r30 */
  call tpl_sc_handler
  ret
  
  .type SuspendOSInterrupts,@function
//  .size SuspendOSInterrupts,$-SuspendOSInterrupts


  .global CallTerminateISR2
CallTerminateISR2:
  ldi r30,OSServiceId_CallTerminateISR2  /* load the service id in r30 */
  call tpl_sc_handler
  ret
  
  .type CallTerminateISR2,@function
//  .size CallTerminateISR2,$-CallTerminateISR2


  .global ActivateTask
ActivateTask:
  ldi r30,OSServiceId_ActivateTask  /* load the service id in r30 */
  call tpl_sc_handler
  ret
  
  .type ActivateTask,@function
//  .size ActivateTask,$-ActivateTask


  .global TerminateTask
TerminateTask:
  ldi r30,OSServiceId_TerminateTask  /* load the service id in r30 */
  call tpl_sc_handler
  ret
  
  .type TerminateTask,@function
//  .size TerminateTask,$-TerminateTask


  .global ChainTask
ChainTask:
  ldi r30,OSServiceId_ChainTask  /* load the service id in r30 */
  call tpl_sc_handler
  ret
  
  .type ChainTask,@function
//  .size ChainTask,$-ChainTask


  .global Schedule
Schedule:
  ldi r30,OSServiceId_Schedule  /* load the service id in r30 */
  call tpl_sc_handler
  ret
  
  .type Schedule,@function
//  .size Schedule,$-Schedule


  .global GetTaskID
GetTaskID:
  ldi r30,OSServiceId_GetTaskID  /* load the service id in r30 */
  call tpl_sc_handler
  ret
  
  .type GetTaskID,@function
//  .size GetTaskID,$-GetTaskID


  .global GetTaskState
GetTaskState:
  ldi r30,OSServiceId_GetTaskState  /* load the service id in r30 */
  call tpl_sc_handler
  ret
  
  .type GetTaskState,@function
//  .size GetTaskState,$-GetTaskState


  .global CallTerminateTask
CallTerminateTask:
  ldi r30,OSServiceId_CallTerminateTask  /* load the service id in r30 */
  call tpl_sc_handler
  ret
  
  .type CallTerminateTask,@function
//  .size CallTerminateTask,$-CallTerminateTask


  .global GetResource
GetResource:
  ldi r30,OSServiceId_GetResource  /* load the service id in r30 */
  call tpl_sc_handler
  ret
  
  .type GetResource,@function
//  .size GetResource,$-GetResource


  .global ReleaseResource
ReleaseResource:
  ldi r30,OSServiceId_ReleaseResource  /* load the service id in r30 */
  call tpl_sc_handler
  ret
  
  .type ReleaseResource,@function
//  .size ReleaseResource,$-ReleaseResource


  .global GetAlarmBase
GetAlarmBase:
  ldi r30,OSServiceId_GetAlarmBase  /* load the service id in r30 */
  call tpl_sc_handler
  ret
  
  .type GetAlarmBase,@function
//  .size GetAlarmBase,$-GetAlarmBase


  .global GetAlarm
GetAlarm:
  ldi r30,OSServiceId_GetAlarm  /* load the service id in r30 */
  call tpl_sc_handler
  ret
  
  .type GetAlarm,@function
//  .size GetAlarm,$-GetAlarm


  .global SetRelAlarm
SetRelAlarm:
  ldi r30,OSServiceId_SetRelAlarm  /* load the service id in r30 */
  call tpl_sc_handler
  ret
  
  .type SetRelAlarm,@function
//  .size SetRelAlarm,$-SetRelAlarm


  .global SetAbsAlarm
SetAbsAlarm:
  ldi r30,OSServiceId_SetAbsAlarm  /* load the service id in r30 */
  call tpl_sc_handler
  ret
  
  .type SetAbsAlarm,@function
//  .size SetAbsAlarm,$-SetAbsAlarm


  .global CancelAlarm
CancelAlarm:
  ldi r30,OSServiceId_CancelAlarm  /* load the service id in r30 */
  call tpl_sc_handler
  ret
  
  .type CancelAlarm,@function
//  .size CancelAlarm,$-CancelAlarm



#define API_STOP_SEC_CODE
#include "tpl_as_memmap.h"


/* End of file tpl_invoque.S */

