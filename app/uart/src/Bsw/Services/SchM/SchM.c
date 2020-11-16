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

/*****************************************************************************************************
* Definition of module wide (CONST-) CONSTANTs 
*****************************************************************************************************/
/* Global Task Scheduler Status definitions */

#define    SCHM_TASK_SCHEDULER_BASE_FREQ		 2000u
#define    SCHM_TASK_SCH_MAX_NUMBER_TIME_TASKS   0x06u

#define    SCHM_TASK_SCHEDULER_INIT              0x00u
#define    SCHM_TASK_SCHEDULER_RUNNING           0x01u
#define    SCHM_TASK_SCHEDULER_OVERLOAD_1MS      0x02u
#define    SCHM_TASK_SCHEDULER_OVERLOAD_2MS_A    0x03u
#define    SCHM_TASK_SCHEDULER_OVERLOAD_2MS_B    0x04u
#define    SCHM_TASK_SCHEDULER_HALTED            0xAAu


/*****************************************************************************************************
* SW1 
*****************************************************************************************************/

/** SW Version */
#define PINT_VERSION  "1.0"

/** Pin definition: Pin type definition is located at pio.h file */
#define PIN_SW0 \
		{PIO_PA9, PIOA, ID_PIOA, PIO_INPUT, PIO_PULLUP | PIO_DEBOUNCE | PIO_IT_RISE_EDGE}

/** LED0 blinking control. */
volatile bool bLed0Active = false ;

/** LED1 blinking control. */
volatile bool bLed1Active = true ;

/** SW LED blinking control. */
volatile bool bSW0Active = true ;

/** SW0 Pin Definition, used to configure the Pin and Pin Interrupt, see ConfigureSW0Button function  */
static const Pin PinSW0 = PIN_SW0;


static void ProcessButtonEvt( uint8_t ucButton )
{
	if ( ucButton == 0 ) {
		bLed0Active = true;
		bLed1Active = false;
		LED_Clear( 1 );
	}
	else
	{
		bLed0Active = false;
		bLed1Active = true ;
		LED_Clear( 0 );
	}
}

static void SW0_Handler( const Pin* pPin )
{
    
	if ( pPin == &PinSW0 ) {
		ProcessButtonEvt( bSW0Active ) ;
		bSW0Active = !bSW0Active;
		printf("SW0_Handler ... Rising Edge Detected.\n\r" );
	}
    
    SchM_ActivateTask(TASKS_SW1);
}

static void ConfigureSW0Button( void )
{
	/* Configure PinSW0 as input. */
	PIO_Configure( &PinSW0, 1 ) ;

	/* Adjust PinSW0 denounce filter parameters, uses 10 Hz filter. */
	PIO_SetDebounceFilter( &PinSW0, 10 ) ;

	/* Initialize PinSW0 interrupt handler */
	PIO_ConfigureIt( &PinSW0, SW0_Handler ) ; /* Interrupt on rising edge, SW0_Handler as callback function */

	/* Enable PinSW0 controller IRQs. */
	NVIC_EnableIRQ( (IRQn_Type)PinSW0.id ) ;

	/* Enable PinSW0 line interrupts. */
	PIO_EnableIt( &PinSW0 ) ;
}
/*****************************************************************************************************
* Definition of  VARIABLEs - 
*****************************************************************************************************/

/* Global pointer used to invoke callback function upon Timer event*/
SchM_CallbackType pfctnSysTick = (SchM_CallbackType)NULL;


uint8_t SchM_Status;
uint8_t SchM_Counter;

SchMTasksIdType SchM_Task_ID_Activated;
SchMTasksIdType SchM_Task_ID_Running;
SchMTasksIdType SchM_Task_ID_Backup;

uint8_t SchM_10ms_Counter;
uint8_t SchM_50ms_Counter;
uint8_t SchM_100ms_Counter;

SchMTaskCtrlType TaskCtrl[TASK_MAX_NUM_TASKS];

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
        //SchM_100ms_Counter++;
        TaskCtrl[TASKS_100_MS].TickCounter++;
        /*-- Allow 100 ms periodic tasks to be executed --*/
        if( TaskCtrl[TASKS_100_MS].TickCounter >= 100u )
        {
            /* Indicate that Task is Ready to be executed */ 
            TaskCtrl[TASKS_100_MS].TaskState = READY;
            TaskCtrl[TASKS_100_MS].TickCounter = 0u;
        }
        /*-- Allow 1 ms periodic tasks to be executed --*/
        //SchM_Task_ID_Activated = TASKS_1_MS;
        TaskCtrl[TASKS_1_MS].TaskState = READY;
        
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
        if( ( SchM_Counter & 0x03u ) == 0x02u )
        {
            //SchM_50ms_Counter++;
            TaskCtrl[TASKS_50_MS].TickCounter++;
            /*-- Allow 50 ms periodic tasks to be executed --*/
            if( TaskCtrl[TASKS_50_MS].TickCounter >= 25u )
            {
            TaskCtrl[TASKS_50_MS].TaskState = READY;
            TaskCtrl[TASKS_50_MS].TickCounter = 0u;
            }
            /*-- Allow 2 ms group A periodic tasks to be executed --*/
           // SchM_Task_ID_Activated = TASKS_2_MS_A;
           TaskCtrl[TASKS_2_MS_A].TaskState = READY;
            
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
                //SchM_10ms_Counter++;
                TaskCtrl[TASKS_10_MS].TickCounter++;
                /*-- Allow 10 ms periodic tasks to be executed --*/
                if( TaskCtrl[TASKS_10_MS].TickCounter >= 5u )
                {
                    TaskCtrl[TASKS_10_MS].TaskState = READY;
                    TaskCtrl[TASKS_10_MS].TickCounter = 0u;                    
                }
                /*-- Allow 2 ms group B periodic tasks to be executed --*/
                //SchM_Task_ID_Activated = TASKS_2_MS_B;
                TaskCtrl[TASKS_2_MS_B].TaskState = READY;               
            }
        }
    }
}

/****************************************************************************************************/
/**
* \brief    SysTick - Initialization
* \author   Abraham Tezmol
* \param    int32_t base_freq	--> Requested SysTick interrupt frequency
* \param    SchM_CallbackType sysTick_handler	--> Callback function to handle SysTick ISR.
* \return   uint8_t --> 0 - Successful configuration of SysTick IRQ and SysTick Timer, 1 - Invalid configuration
* \todo
*/

uint8_t SysTick_init(uint32_t base_freq, SchM_CallbackType sysTick_handler)
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
		while (1);
		printf( "-- SysTick Initialization Failed --\n\r" ) ;
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
    //TaskCtrl[TASKS_1_MS].TaskInfo->TaskFcnPtr();
    uint8_t TaskIndex = 0;

    for (TaskIndex ; TaskIndex < TASK_MAX_NUM_TASKS ; TaskIndex++)
    {
        if (READY == TaskCtrl[TaskIndex].TaskState)
        {
            TaskCtrl[TaskIndex].TaskState = RUNNING ;
            TaskCtrl[TaskIndex].TaskInfo->TaskFcnPtr();
            TaskCtrl[TaskIndex].TaskState = SUSPENDED;
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
void SchM_Init(SchMTaskType * TaskArray)
{    
    ConfigureSW0Button();
    uint8_t TaskIndex = 0;
    /* Init Global and local Task Scheduler variables */
    SchM_Counter   = 0u;
    SchM_Task_ID_Activated   = TASK_MAX_NUM_TASKS;
    SchM_Task_ID_Running     = TASK_MAX_NUM_TASKS;
    SchM_Task_ID_Backup      = TASK_MAX_NUM_TASKS;
    SchM_10ms_Counter        = 0u;
    SchM_50ms_Counter        = 0u;
    SchM_100ms_Counter       = 0u;
    SchM_Status    = SCHM_TASK_SCHEDULER_INIT;
	/* Start scheduler */

    for (TaskIndex ; TaskIndex < TASK_MAX_NUM_TASKS ; TaskIndex++)
    {
        TaskCtrl[TaskIndex].TickCounter = 0;
        TaskCtrl[TaskIndex].TaskRunning = 0;
        TaskCtrl[TaskIndex].TaskOverload = 0;
        TaskCtrl[TaskIndex].TaskState = SUSPENDED;

        TaskCtrl[TaskIndex].TaskInfo = &TaskArray[TaskIndex];
        
        TaskCtrl[TaskIndex].TaskInfo->TaskPriority = TaskArray[TaskIndex].TaskPriority;
        TaskCtrl[TaskIndex].TaskInfo->TaskId       = TaskArray[TaskIndex].TaskId;
        TaskCtrl[TaskIndex].TaskInfo->TaskFcnPtr   = TaskArray[TaskIndex].TaskFcnPtr; 
    }

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

/***************************************************************************************************/
void SchM_SchedulePoint(void)
{/* This function allows activated higher priority tasks to run */

}

void SchM_ActivateTask(SchMTasksIdType TaskId)
{/* This function supports the tasks activation */
    TaskCtrl[TaskId].TaskState = READY;
}

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
