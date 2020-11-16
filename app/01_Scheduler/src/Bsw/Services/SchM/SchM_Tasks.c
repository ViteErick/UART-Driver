/****************************************************************************************************/
/**
\file       SchM_Tasks.c
\brief      List of Tasks
   \~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
   \version       1.1
   \author        Francisco Martinez
   \description   List of task name updates
   \date          20/08/2018
   \~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
   \version       1.0
   \author        Abraham Tezmol
   \description   Multi-thread Task scheduler - list of tasks.   
   \date          07/09/2013
*/
/****************************************************************************************************/

/*****************************************************************************************************
* Include files
*****************************************************************************************************/

/** Scheduler function prototypes definitions */
#include    "SchM_Tasks.h"
/* LED control definitions */ 
#include    "Led_Ctrl.h"

/*****************************************************************************************************
* Definition of  VARIABLEs - 
*****************************************************************************************************/


/*****************************************************************************************************
* Definition of module wide (CONST-) CONSTANTs 
*****************************************************************************************************/

/*****************************************************************************************************
* Code of module wide FUNCTIONS
*****************************************************************************************************/

/* List of tasks to be executed @ 1ms */
void SchM_Task_1ms( void )
{
    //printf( "SchM_Task_1ms\n\r");
    PingOsc(0);
}

/* List of tasks to be executed @ 2ms, first group */
void SchM_Task_2ms_A(void)
{
	  //printf( "SchM_Task_2ms_A\n\r");
    PingOsc(1);
}

/* List of tasks to be executed @ 2ms, second group */
void SchM_Task_2ms_B( void )
{
	 //printf( "SchM_Task_2ms_B\n\r");
   PingOsc(2);
}
    
/* List of tasks to be executed @ 10ms */
void SchM_Task_10ms( void )
{
    //printf( "SchM_Task_10ms\n\r"); 
    PingOsc(3);
}

/* List of tasks to be executed @ 50ms */
void SchM_Task_50ms( void )
{      
    //printf( "SchM_Task_50ms\n\r");
    PingOsc(4);
    
}

/* List of tasks to be executed @ 100ms */
void SchM_Task_100ms( void )
{ 
    printf( "SchM_Task_100ms\n\r");
    LedCtrl_BlinkingPattern();
    PingOsc(5);
}

/* List of tasks to be executed on SW0 interruot */
void SchM_Task_SW0( void )
{ 
    //printf( "SchM_Task_SW0 - SW0 was pressed!\n\r");
    LED_Toggle( 0 );
    printf( "Before Schedule Point\n\r");
    PingOsc(6);
    SchM_SchedulePoint();
   printf( "After Schedule Point\n\r");
    PingOsc(6);
} 