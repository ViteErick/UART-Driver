/*******************************************************************************/
/**
\file       SchM.c
\brief      Multi-thread Task scheduler.
   \~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
   \version       1.1
   \author        Francisco Martinez
   \description   Scheduler updates
   \date          20/Aug/2018
   \~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
   \version       1.0
   \author        Abraham Tezmol
   \description   Initial version
   \date          09/Sep/2008
*/

/** Standard Types */
#include "Std_Types.h"
/** Scheduler function prototypes definitions */
#include "SchM.h"
/** Scheduler Type definitions */
#include "SchM_Types.h"
/** Tasks definition */
#include "SchM_Tasks.h"
/** Dynamic Memory Allocation */
#include "MemAlloc.h"


typedef struct
{
  uint8_t           TickCounter;
  uint8_t           TaskOverload;
  SchMTaskStateType TaskState;
  SchMTaskType *    TaskInfo;
}SchMTaskCtrlType;

/*****************************************************************************************************
* Definition of module wide (CONST-) CONSTANTs 
*****************************************************************************************************/
/* Global Task Scheduler Status definitions */

/*#define    SCHM_TASK_MAX_NUMBER_TASKS            (uint8_t)TASK_BKG*/
#define    SCHM_TASK_SCHEDULER_BASE_FREQ		     2000u

#define    SCHM_TASK_SCHEDULER_INIT              0x00u
#define    SCHM_TASK_SCHEDULER_RUNNING           0x01u
#define    SCHM_TASK_SCHEDULER_OVERLOAD          0x02u
#define    SCHM_TASK_SCHEDULER_HALTED            0xAAu

/*****************************************************************************************************
* Definition of  VARIABLEs - 
*****************************************************************************************************/

/* Global pointer used to invoke callback function upon Timer event*/
SchMCallbackType pfctnSysTick = (SchMCallbackType)NULL;
/*SchMTaskCtrlType TaskControl[SCHM_TASK_MAX_NUMBER_TASKS];*/
SchMTaskCtrlType *TaskControl;
SchMTaskIdType SchMTaskRunning;
SchMConfigType *SchMConfigGlobal;
uint8_t SchM_Status;
uint8_t SchM_Counter;
uint8_t SchM_10ms_Counter;
uint8_t SchM_50ms_Counter;
uint8_t SchM_100ms_Counter;


/*****************************************************************************************************
* Code of module wide private FUNCTIONS
*****************************************************************************************************/
/*******************************************************************************/
/**
* \brief    Periodic Interrupt Timer Service routine.                            \n
            This interrupt is the core of the task scheduler.                   \n
            It is executed every 500us                                          \n
            It defines 3 basic threads from which other 3 threads are derived:  \n
            a) 1ms thread (basic) ->  100ms thread (derived)                    \n
            b) 2ms A thread (basic)-> 50ms thread (derived)                     \n
            c) 2ms B thread (basic)-> 10ms thread (derived)                     \n
            It partitions core execution time into time slices (500us each one).\n 
            This arrangement assures core will have equal task loading across time.\n   
            For more information on how time slice is assigned to each thread,  \n
            refer to file "S12X Task Scheduler Layout.xls"
* \author   Abraham Tezmol
* \param    void
* \return   void
* \todo
*/

void SchM_Callback(void)
{
    /*-- Update scheduler control variable --*/
    SchM_Counter++;
    
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*  1ms execution thread - used to derive two execution threads:                */
    /*  a) 1ms thread (highest priority tasks)                                      */
    /*  b) 100ms thread (lowest priority tasks)                                     */
    /*  As any other thread on this scheduling scheme,                              */
    /*  all tasks must be executed in <= 500us                                      */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    if( ( SchM_Counter & 0x01u ) == 0x01u )
    {
        SchM_100ms_Counter++;
        
        /*-- Allow 1 ms periodic tasks to be executed --*/
        TaskControl[(uint8_t)TASK_1MS].TaskState = READY;
        
        if (TASK_1MS == SchMTaskRunning)
        {
          TaskControl[TASK_1MS].TaskOverload = 1;
          SchM_Status = SCHM_TASK_SCHEDULER_OVERLOAD;
        }
        
        /*-- Allow 100 ms periodic tasks to be executed --*/
        if( SchM_100ms_Counter >= 100u )
        {
            /* Indicate that Task is Ready to be executed */
            TaskControl[(uint8_t)TASK_100MS].TaskState = READY;
            if (TASK_100MS == SchMTaskRunning)
            {
              TaskControl[TASK_100MS].TaskOverload = 1;
              SchM_Status = SCHM_TASK_SCHEDULER_OVERLOAD;
            }
            SchM_100ms_Counter = 0u;
        }
    }
    else
    {
        /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
        /*  2ms execution thread - used to derive two execution threads:                */
        /*  a) 2ms group A thread (high priority tasks)                                 */
        /*  b) 50ms thread (second lowest priority tasks)                               */
        /*  As any other thread on this scheduling scheme,                              */
        /*  all tasks must be executed in <= 500us                                      */
        /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
        if( ( SchM_Counter & 0x02u ) == 0x02u )
        {
            SchM_50ms_Counter++;
            
            /*-- Allow 2 ms group A periodic tasks to be executed --*/
            TaskControl[(uint8_t)TASK_2MSA].TaskState = READY;
            
            if (TASK_2MSA == SchMTaskRunning)
            {
              TaskControl[TASK_2MSA].TaskOverload = 1;
              SchM_Status = SCHM_TASK_SCHEDULER_OVERLOAD;
            }
            /*-- Allow 50 ms periodic tasks to be executed --*/
            if( SchM_50ms_Counter >= 25u )
            {
                TaskControl[(uint8_t)TASK_50MS].TaskState = READY;
                if (TASK_50MS == SchMTaskRunning)
                {
                  TaskControl[TASK_50MS].TaskOverload = 1;
                  SchM_Status = SCHM_TASK_SCHEDULER_OVERLOAD;
                }
                SchM_50ms_Counter = 0u;
            }
        }
        else
        {
            /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
            /*  2ms execution thread - used to derive two execution threads:                */
            /*  a) 2ms group B thread (high priority tasks)                                 */
            /*  b) 10ms thread (medium priority tasks)                                      */
            /*  As any other thread on this scheduling scheme,                              */
            /*  all tasks must be executed in <= 500us                                      */
            /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
            if( ( SchM_Counter & 0x03u ) == 0x00u )
            {
                SchM_10ms_Counter++;
                
                /*-- Allow 2 ms group B periodic tasks to be executed --*/
                TaskControl[(uint8_t)TASK_2MSB].TaskState = READY;
                
                if (TASK_2MSB == SchMTaskRunning)
                {
                  TaskControl[TASK_2MSB].TaskOverload = 1;
                  SchM_Status = SCHM_TASK_SCHEDULER_OVERLOAD;
                }
                
                /*-- Allow 10 ms periodic tasks to be executed --*/
                if( SchM_10ms_Counter >= 5u )
                {
                    TaskControl[(uint8_t)TASK_10MS].TaskState = READY;
                    if (TASK_10MS == SchMTaskRunning)
                    {
                      TaskControl[TASK_10MS].TaskOverload = 1;
                      SchM_Status = SCHM_TASK_SCHEDULER_OVERLOAD;
                    }
                    SchM_10ms_Counter = 0u;
                }
            }
        }
    }
}

/****************************************************************************************************/
/**
* \brief    SysTick - Initialization
* \author   Abraham Tezmol
* \param    int32_t base_freq	--> Requested SysTick interrupt frequency
* \param    SchMCallbackType sysTick_handler	--> Callback function to handle SysTick ISR.
* \return   uint8_t --> 0 - Successful configuration of SysTick IRQ and SysTick Timer, 1 - Invalid configuration
* \todo
*/

uint8_t SysTick_init(uint32_t base_freq, SchMCallbackType sysTick_handler)
{
	pfctnSysTick = sysTick_handler;
	return SysTick_Config(SystemCoreClock / base_freq);
}

/*******************************************************************************/
/**
* \brief    Scheduler Start - Once time base is armed, start execution of   \n
            Multi-thread Round Robin scheduling scheme.                     \n
            This function requires prior execution of "vfnScheduler_Init"
* \author   Abraham Tezmol
* \param    void
* \return   void
* \todo     
*/

void SchM_Start(void)
{
	if (SysTick_init(SCHM_TASK_SCHEDULER_BASE_FREQ, SchM_Callback)) 
	{
		printf( "-- SysTick Initialization Failed --\n\r" ) ;    
		while (1);
	}
	SchM_Status = SCHM_TASK_SCHEDULER_RUNNING;
	printf( "-- Scheduler Running --\n\r" ) ;
	/* Once all the basic services have been started, go to infinite loop to serviced activated tasks */
	while(1)
  {
		SchM_Scheduler();
	}
}

/*******************************************************************************/
/**
* \brief    Multi-thread round robin task Scheduler  (non-preemtive)        \n
            It calls the different tasks based on the status of             \n   
            List of tasks shall be defined @ "tasks.h" file
* \author   Abraham Tezmol
* \param    void
* \return   void
* \todo     
*/

void SchM_Scheduler(void)
{
  uint8_t LocTaskIdx;
  for (LocTaskIdx = 0; LocTaskIdx < SchMConfigGlobal->NumberOfTasks; LocTaskIdx++)
  {
    if (TaskControl[LocTaskIdx].TaskState == READY)
    {
      if (TaskControl[LocTaskIdx].TaskInfo->TaskFcnPtr != NULL)
      {

          cpu_irq_disable();
          SchMTaskRunning = TaskControl[LocTaskIdx].TaskInfo->TaskId;
          TaskControl[LocTaskIdx].TaskState = RUNNING;
          TaskControl[LocTaskIdx].TickCounter++;
          cpu_irq_enable();
          TaskControl[LocTaskIdx].TaskInfo->TaskFcnPtr();
          cpu_irq_disable();
          TaskControl[LocTaskIdx].TaskState = SUSPENDED;
          SchMTaskRunning = (SchMTaskIdType)TASK_BKG;
          cpu_irq_enable();

      }
    }
  } 
}

/*****************************************************************************************************
* Code of public FUNCTIONS
*****************************************************************************************************/

/****************************************************************************************************/
/**
* \brief    Scheduler - Initialization
* \author   Abraham Tezmol
* \param    void
* \return   void
* \todo     
*/
/*void SchM_Init(SchMTaskType *TaskArray)*/
void SchM_Init(SchMConfigType *SchMConfig)
{
  uint8_t LocTaskIdx;
  /* Init Global and local Task Scheduler variables */
  SchMConfigGlobal = SchMConfig;
  SchM_Counter   = 0u;
  TaskControl = (SchMTaskCtrlType *)MemAlloc( SchMConfigGlobal->NumberOfTasks * sizeof(SchMTaskCtrlType));
  SchMTaskRunning = (SchMTaskIdType)TASK_BKG;
  SchM_10ms_Counter        = 0u;
  SchM_50ms_Counter        = 0u;
  SchM_100ms_Counter       = 0u;
  for (LocTaskIdx = 0; LocTaskIdx < SchMConfigGlobal->NumberOfTasks; LocTaskIdx++)
  {
    TaskControl[LocTaskIdx].TickCounter = 0;
    TaskControl[LocTaskIdx].TaskOverload = 0;
    TaskControl[LocTaskIdx].TaskState = SUSPENDED;
    TaskControl[LocTaskIdx].TaskInfo = &SchMConfigGlobal->SchMTaskConfig[LocTaskIdx];
/*	&TaskArray[LocTaskIdx]; */
  }
  SchM_Status    = SCHM_TASK_SCHEDULER_INIT;
	/* Start scheduler */
	SchM_Start();
}

/*******************************************************************************/
/**
* \brief    Scheduler Stop - stop execution of Multi-thread Round Robin scheduling scheme.
* \author   Abraham Tezmol
* \param    void
* \return   void
* \todo     
*/
void SchM_Stop(void)
{  
    /* Update scheduler status accordingly */
    SchM_Status = SCHM_TASK_SCHEDULER_HALTED;
}

void SchM_SchedulePoint(void)
{
  SchMTaskIdType TaskRunningBackUp;
  uint8_t LocTaskIdx;
  
  cpu_irq_disable();
  TaskRunningBackUp = SchMTaskRunning;
  cpu_irq_enable();
  
  
  for (LocTaskIdx = 0; LocTaskIdx < SchMConfigGlobal->NumberOfTasks; LocTaskIdx++)
  {
    if ( TaskControl[LocTaskIdx].TaskInfo->TaskId != TaskControl[(uint8_t)TaskRunningBackUp].TaskInfo->TaskId )
    {
      if (TaskControl[LocTaskIdx].TaskState == READY)
      {      
        if ( TaskControl[LocTaskIdx].TaskInfo->TaskPriority > TaskControl[(uint8_t)TaskRunningBackUp].TaskInfo->TaskPriority )
        {
          cpu_irq_disable();
          TaskControl[(uint8_t)TaskRunningBackUp].TaskState = READY;
          SchMTaskRunning = TaskControl[LocTaskIdx].TaskInfo->TaskId;
          TaskControl[LocTaskIdx].TaskState = RUNNING;
          TaskControl[LocTaskIdx].TickCounter++;
          cpu_irq_enable();
          TaskControl[LocTaskIdx].TaskInfo->TaskFcnPtr();
          cpu_irq_disable();
          TaskControl[LocTaskIdx].TaskState = SUSPENDED;
          TaskControl[(uint8_t)TaskRunningBackUp].TaskState = RUNNING;
          SchMTaskRunning = TaskRunningBackUp;
          cpu_irq_enable();
        }
      }
    }
  }
}

void SchM_ActivateTask (SchMTaskIdType TaskId)
{
  if ( (uint8_t)TaskId < SchMConfigGlobal->NumberOfTasks )
  {
    TaskControl[(uint8_t)TaskId].TaskState = READY;
  }
}

/***************************************************************************************************/

/****************************************************************************************************/
/**
* \brief    SysTick - interrupt handling
* \author   Abraham Tezmol
* \param    void
* \return   void
* \todo
*/
/* SysTick interrupt handler */
void SysTick_Handler(void)
{
	if (pfctnSysTick)
	{
		(*pfctnSysTick)();
	}
}
