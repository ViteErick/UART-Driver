/****************************************************************************************************/
/**
  \mainpage
  \n 
  \brief        Main application (main module)
  \author       Abraham Tezmol Otero, M.S.E.E
  \project      Tau 
  \version      1.0
  \date         12/Jun/2016
   
  Program compiled with  WinIDEA Open Build 9.12.256 (54401), tested on Atmel SAMV71 Xplained Ultra
*/
/****************************************************************************************************/


/*~~~~~~  Headers ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/** Main group of includes for board definitions, chip definitions and type definitions */
#include    "Std_Types.h"
/** Task scheduler definitions */
#include    "SchM.h"
/** LED control definitions */ 
#include    "Led_Ctrl.h"
/** Watchdog control function prototypes definitions */
#include    "Wdg.h"

#include "SchM_Tasks.h"

/*~~~~~~  Local definitions ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/*~~~~~~  Global variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
SchMTaskType TaskConfig[TASK_MAX_NUM_TASKS]= 
{
	{ /*First element -> Task 1ms*/
	.TaskPriority = 5,
	.TaskId = TASKS_1_MS,
	.TaskFcnPtr = SchM_Task_1ms,
	},

	{/*Second element -> Task 2_MS_A*/
	.TaskPriority = 4,
	.TaskId = TASKS_2_MS_A,
	.TaskFcnPtr = SchM_Task_2ms_A,
	},

	{/*Third element -> Task 2_MS_B*/
	.TaskPriority = 4,
	.TaskId = TASKS_2_MS_B,
	.TaskFcnPtr = SchM_Task_2ms_B,
	},

	{/*Fourth element -> Task 10_MS*/
	.TaskPriority = 3,
	.TaskId = TASKS_10_MS,
	.TaskFcnPtr = SchM_Task_10ms,
	},
	
	{/*Fifth element -> Task 50_MS*/
	.TaskPriority = 2,
	.TaskId = TASKS_50_MS,
	.TaskFcnPtr = SchM_Task_50ms,
	},

	{/*Sixth element -> Task 100_MS*/
	.TaskPriority = 1,
	.TaskId = TASKS_100_MS,
	.TaskFcnPtr = SchM_Task_100ms,
	},

	{/*7th element -> SW1*/
	.TaskPriority = 5,
	.TaskId = TASKS_SW1,
	.TaskFcnPtr = SchM_Task_SW1,
	},
};

/*~~~~~~  Local functions ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/*----------------------------------------------------------------------------
 *        Exported functions
 *----------------------------------------------------------------------------*/
/**
 *  \brief getting-started Application entry point.
 *
 *  \return Unused (ANSI-C compatibility).
 */

extern int main( void )
{
	/* Disable watchdog */
	Wdg_Disable();
	printf( "\n\r-- Scheduler Project %s --\n\r", SOFTPACK_VERSION ) ;
	printf( "-- %s\n\r", BOARD_NAME ) ;
	printf( "-- Compiled: %s %s With %s --\n\r", __DATE__, __TIME__ , COMPILER_NAME);
	/* Enable I and D cache */
	SCB_EnableICache();
	/* SCB_EnableDCache(); */
	/* Configure LEDs */
	printf( "-- Led Control --\n\r" ) ;
	LedCtrl_Configure(); 
	/* Scheduler Inititalization */
	printf( "-- Scheduler Initialization --\n\r" ) ;
	SchM_Init(TaskConfig);
	
	/* Should never reach this code */
	for(;;)
    {
		printf( "-- Unexpected Error at Scheduler Initialization --\n\r" ) ;
	}
}
