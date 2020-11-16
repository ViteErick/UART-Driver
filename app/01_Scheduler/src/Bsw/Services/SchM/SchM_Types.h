/*******************************************************************************/
/**
\file       SchM_Types.h
\brief      Scheduler Type Definitions.
   \~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
   \version       1.0
   \author        Francisco Martinez
   \description   Initial version of Task Type Definitios
   \date          20/08/2018
 
*/

#ifndef SCHM_TYPES
#define SCHM_TYPES

	/** Standard Types */
	#include "Std_Types.h"

	typedef  void  ( * SchM_CallbackType )( void );

	/* Task Scheduler Tasks IDs definitions */
	typedef enum  
	{   
		TASKS_1_MS,
		TASKS_2_MS_A,
		TASKS_2_MS_B,
		TASKS_10_MS,
		TASKS_50_MS,
		TASKS_100_MS,
    TASK_SW0,
		TASK_MAX_NUM_TASKS,
    TASK_NULL,
	}SchMTasksIdType;

 typedef struct 
	{   
		uint8_t TaskPriority;
    SchMTasksIdType TaskId;
    SchM_CallbackType TaskFcnPtr;
  
	}SchMTaskType;

	/* Task Scheduler Tasks STATE definitions */
	typedef enum  
	{   
		SUSPENDED,
    READY,
    RUNNING,
	}SchMTaskStateType;

  
	/* Task Scheduler Tasks STATE definitions */
	typedef struct 
	{   
		uint8_t TickCounter;
    uint8_t TaskRunning;
    uint8_t TaskOverload;
    SchMTaskStateType TaskState;
    SchMTaskType * TaskInfo;
    
	}SchMTaskCtrlType;


 
/*============================================================================*/
#endif /* SCHM_TYPES */
