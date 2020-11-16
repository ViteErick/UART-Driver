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

/* Main group of includes for board definitions, chip definitions and type definitions */
#include "board.h"
/* Task scheduler definitions */
#include "app_scheduler.h"
/* LED control definitions */ 
#include     "led_ctrl.h"
/* UART communication */
#include     "serial_ctrl.h"

/*~~~~~~  Local definitions ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/*~~~~~~  Global variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

tCallbackFunction aptrTaskFunctions[] = 
{
	LED_Set,	/* Function to execute upon task activation */
	LED_Clear   /* Function to execute upon task start */
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
	WDT_Disable( WDT ) ;
	/* Enable I and D cache */
	SCB_EnableICache();
	/* SCB_EnableDCache(); */
	
	/* Configure LEDs */
	vfnLedCtrl_Configure(); 
	/* Initialize UART communicaiton */
	vfnSerialCtrl_Init();
	/* Configure Non-preemtive scheduler */
	vfnScheduler_Init(aptrTaskFunctions[0], aptrTaskFunctions[1]);
	/* Start scheduler */
	vfnScheduler_Start();
  
  printf( "UART Example ...\n\r" );
	
	/* Once all the basic services have been started, go to infinite loop to serviced activated tasks */
	for(;;)
    {
		vfnTask_Scheduler();
	}
}
