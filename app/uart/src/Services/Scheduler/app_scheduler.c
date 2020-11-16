/*******************************************************************************/
/**
\file       app_scheduler.c
\brief      Multi-thread Task scheduler.
\author     Abraham Tezmol
\version    0.1
\date       09/09/2008
*/

/** Variable types and common definitions */
#include "system_samv71.h"

/** Scheduler function prototypes definitions */
#include "app_scheduler.h"
/** Tasks definition */
#include "app_tasks.h"

/* -- Global Variables --------------------------------------------------------*/
uint8_t gu8Scheduler_Status;
uint8_t gu8Scheduler_Counter;
uint8_t gu8Scheduler_Thread_ID;
uint8_t gu8Scheduler_Thread_ID_Backup;
uint8_t u8_10ms_Counter;
uint8_t u8_50ms_Counter;
uint8_t u8_100ms_Counter;

tCallbackFunction ptrScheduler_Activate;
tCallbackFunction ptrScheduler_Start;

/*******************************************************************************/
/**
* \brief    Scheduler - Periodic Interrup Timer Initialization
* \author   Abraham Tezmol
* \param    void
* \return   void
* \todo     
*/
void vfnScheduler_Init(tCallbackFunction ptrFunction_act, tCallbackFunction ptrFunction_start)
{   
    
    /* Init Global and local Task Scheduler variables */
    gu8Scheduler_Counter = 0;   
    gu8Scheduler_Thread_ID = NO_TASK_PENDING;
    u8_10ms_Counter = 0;
    u8_50ms_Counter = 0;
    u8_100ms_Counter = 0;
    
    /* Store activate and start callbacks */
    ptrScheduler_Activate = ptrFunction_act;
    ptrScheduler_Start    = ptrFunction_start;
    
    gu8Scheduler_Status = TASK_SCHEDULER_INIT;
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
void vfnScheduler_Start(void)
{
	if (SysTick_Config(SystemCoreClock / TASK_SCHEDULER_BASE_FREQ)) 
	{
		while (1);
	}
    gu8Scheduler_Status = TASK_SCHEDULER_RUNNING;
}

/*******************************************************************************/
/**
* \brief    Scheduler Stop - stop execution of Multi-thread Round Robin scheduling scheme.
* \author   Abraham Tezmol
* \param    void
* \return   void
* \todo     
*/
void vfnScheduler_Stop(void)
{  
    /* Update scheduler status accordingly */
    gu8Scheduler_Status = TASK_SCHEDULER_HALTED;
}

/*******************************************************************************/
/**
* \brief    Multi-thread round robin task Scheduler  (non-preemtive)        \n
            It calls the different tasks based on the status of             \n   
            "gu8Scheduler_Thread_ID". This variable is modified by          \n
            ISR "vfnScheduler_PIT_Isr"                                        \n
            List of tasks shall be defined @ "tasks.h" file
* \author   Abraham Tezmol
* \param    void
* \return   void
* \todo     
*/
void vfnTask_Scheduler(void)
{
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*  1ms execution thread - used to derive two execution threads:                */
    /*  a) 1ms thread (high priority tasks)                                         */
    /*  b) 100ms thread (lowest priority tasks)                                     */
    /*  As any other thread on this scheduler, all tasks must be executed in <=500us*/
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/   
    if ((gu8Scheduler_Thread_ID == TASKS_1_MS) || (gu8Scheduler_Thread_ID == TASKS_100_MS))
    {
        /* Make a copy of scheduled task ID */
        gu8Scheduler_Thread_ID_Backup = gu8Scheduler_Thread_ID;
        
        #ifdef SCHEDULER_DIAG_1MS
			ptrScheduler_Start(TAKS_DIAG_CHANNEL);
		#endif
        EXECUTE_1MS_TASKS();
        if (gu8Scheduler_Thread_ID == TASKS_100_MS)
        {
            #ifdef SCHEDULER_DIAG_100MS
				ptrScheduler_Start(TAKS_DIAG_CHANNEL);
			#endif
            EXECUTE_100MS_TASKS();
        }
        /* Verify that thread execution took less than 500 us */
        if (gu8Scheduler_Thread_ID_Backup == gu8Scheduler_Thread_ID)
        {
             /* In case execution of all thread took less than 500us */
            gu8Scheduler_Thread_ID = NO_TASK_PENDING;
        }
        else
        {
            gu8Scheduler_Status = TASK_SCHEDULER_OVERLOAD_1MS;
        }
    }
    else
    {
        /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
        /*  2ms execution thread - used to derive two execution threads:                */
        /*  a) 2ms group A thread (high priority tasks)                                 */
        /*  b) 50ms thread (second lowest priority tasks)                               */
        /*  As any other thread on this scheduler, all tasks must be executed in <=500us*/
        /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
        if ((gu8Scheduler_Thread_ID == TASKS_2_MS_A) || (gu8Scheduler_Thread_ID == TASKS_50_MS))
        {
            /* Make a copy of scheduled task ID */
            gu8Scheduler_Thread_ID_Backup = gu8Scheduler_Thread_ID;
            
            #ifdef SCHEDULER_DIAG_2MS_A
				ptrScheduler_Start(TAKS_DIAG_CHANNEL);
			#endif
            EXECUTE_2MS_A_TASKS();
            if (gu8Scheduler_Thread_ID == TASKS_50_MS)
            {
                #ifdef SCHEDULER_DIAG_50MS
					ptrScheduler_Start(TAKS_DIAG_CHANNEL);
				#endif
                EXECUTE_50MS_TASKS();
            }
            /* Verify that thread execution took less than 500 us */
            if (gu8Scheduler_Thread_ID_Backup == gu8Scheduler_Thread_ID)
            {
                 /* In case execution of all thread took less than 500us */
                gu8Scheduler_Thread_ID = NO_TASK_PENDING;
            }
            else
            {
                gu8Scheduler_Status = TASK_SCHEDULER_OVERLOAD_2MS_A;
            }
        }
        else
        {
            /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
            /*  2ms execution thread - used to derive two execution threads:                */
            /*  a) 2ms group B thread (high priority tasks)                                 */
            /*  b) 10ms thread (medium priority tasks)                                      */
            /*  As any other thread on this scheduler, all tasks must be executed in <=500us*/
            /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
            if ((gu8Scheduler_Thread_ID == TASKS_2_MS_B) || (gu8Scheduler_Thread_ID == TASKS_10_MS))
            {
                /* Make a copy of scheduled task ID */
                gu8Scheduler_Thread_ID_Backup = gu8Scheduler_Thread_ID;
                
                #ifdef SCHEDULER_DIAG_2MS_B
					ptrScheduler_Start(TAKS_DIAG_CHANNEL);
				#endif
                EXECUTE_2MS_B_TASKS();
                if (gu8Scheduler_Thread_ID == TASKS_10_MS)
                {
                    #ifdef SCHEDULER_DIAG_10MS
						ptrScheduler_Start(TAKS_DIAG_CHANNEL);
					#endif
                    EXECUTE_10MS_TASKS();
                }
                 /* Verify that thread execution took less than 500 us */
                if (gu8Scheduler_Thread_ID_Backup == gu8Scheduler_Thread_ID)
                {
                    /* In case execution of all thread took less than 500us */
                    gu8Scheduler_Thread_ID = NO_TASK_PENDING;
                }
                else
                {
                    gu8Scheduler_Status = TASK_SCHEDULER_OVERLOAD_2MS_B;
                }
            }
        }
    }        
}

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

void SysTick_Handler(void)
{
	/*-- Update scheduler control variable --*/
	gu8Scheduler_Counter++;
	
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	/*  1ms execution thread - used to derive two execution threads:                */
	/*  a) 1ms thread (highest priority tasks)                                      */
	/*  b) 100ms thread (lowest priority tasks)                                     */
	/*  As any other thread on this scheduling scheme,                              */
	/*  all tasks must be executed in <= 500us                                      */
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	if ((gu8Scheduler_Counter & 0x01) == 0x01)
	{
		u8_100ms_Counter++;
		/*-- Allow 100 ms periodic tasks to be executed --*/
		if (u8_100ms_Counter >= 100)
		{
			gu8Scheduler_Thread_ID = TASKS_100_MS;
			#ifdef SCHEDULER_DIAG_100MS
				ptrScheduler_Activate(TAKS_DIAG_CHANNEL);
			#endif
			u8_100ms_Counter = 0;
		}
		/*-- Allow 1 ms periodic tasks to be executed --*/
		else
		{
			gu8Scheduler_Thread_ID = TASKS_1_MS;
			#ifdef SCHEDULER_DIAG_1MS
				ptrScheduler_Activate(TAKS_DIAG_CHANNEL);
			#endif
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
		if ((gu8Scheduler_Counter & 0x02) == 0x02)
		{
			u8_50ms_Counter++;
			/*-- Allow 50 ms periodic tasks to be executed --*/
			if (u8_50ms_Counter >= 25)
			{
				gu8Scheduler_Thread_ID = TASKS_50_MS;
				#ifdef SCHEDULER_DIAG_50MS
					ptrScheduler_Activate(TAKS_DIAG_CHANNEL);
				#endif
				u8_50ms_Counter = 0;
			}
			/*-- Allow 2 ms group A periodic tasks to be executed --*/
			else
			{
				gu8Scheduler_Thread_ID = TASKS_2_MS_A;
				#ifdef SCHEDULER_DIAG_2MS_A
					ptrScheduler_Activate(TAKS_DIAG_CHANNEL);
				#endif
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
			if ((gu8Scheduler_Counter & 0x03) == 0x00)
			{
				u8_10ms_Counter++;
				/*-- Allow 10 ms periodic tasks to be executed --*/
				if (u8_10ms_Counter >= 5)
				{
					gu8Scheduler_Thread_ID = TASKS_10_MS;
					#ifdef SCHEDULER_DIAG_10MS
						ptrScheduler_Activate(TAKS_DIAG_CHANNEL);
					#endif
					u8_10ms_Counter = 0;
				}
				/*-- Allow 2 ms group B periodic tasks to be executed --*/
				else
				{
					gu8Scheduler_Thread_ID = TASKS_2_MS_B;
					#ifdef SCHEDULER_DIAG_2MS_B
						ptrScheduler_Activate(TAKS_DIAG_CHANNEL);
					#endif
				}
			}
		}
	}
}