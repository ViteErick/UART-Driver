/*******************************************************************************/
/**
\file       SchM.h
\brief      Task scheduler function prototypes
   \~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
   \version       1.1
   \author        Francisco Martinez
   \description   Scheduler Interface name updates
   \date          20/Aug/2018
   \~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
   \version       1.0
   \author        Abraham Tezmol
   \description   Initial version
   \date          09/Sep/2008
*/

#ifndef SCHM_H        /*prevent duplicated includes*/
	#define SCHM_H

	/** Standard Types */
	#include "Std_Types.h"

	#include "SchM_Types.h"

	/* Task Scheduler Tasks state definitions */
	typedef enum  
	{   
		SUSPENDED,
		READY,
		RUNNING,
	}SchMTasksStateType;

	/* Task Scheduler Tasks control type*/
	typedef struct 
	{
		uint8_t TaskPriority;
		SchMTasksIdType TaskId;
		SchM_CallbackType TaskFcnPtr;
	}SchMTaskType;

	typedef struct 
	{   
		uint8_t TickCounter;
		uint8_t TaskRunning;
		uint8_t TaskOverload;
		SchMTasksStateType TaskState;
		SchMTaskType * TaskInfo;
	}SchMTaskCtrlType;

	/** Scheduler Initalization (arming) */
	void SchM_Init(SchMTaskType * TaskArray);

	/** Scheduler kick-off function */
	void SchM_Start(void);

	/** Scheduler stop function */
	void SchM_Stop(void);

	/** Multi-thread round robin task scheduler */
	void SchM_Scheduler(void);

	void SchM_SchedulePoint(void);

	void SchM_ActivateTask(SchMTasksIdType TaskId);
/*============================================================================*/
#endif /* SCHM_H */