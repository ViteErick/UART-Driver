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

/** Task scheduler Functions */
#include    "SchM_Tasks.h"

#include "Mem_Alloc.h"
/*~~~~~~  Local definitions ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
#define TASK_1MS_PRIORITY   5
#define TASK_2MSA_PRIORITY  4
#define TASK_2MSB_PRIORITY  4
#define TASK_10MS_PRIORITY  3
#define TASK_50MS_PRIORITY  2
#define TASK_100MS_PRIORITY 1
#define TASK_SW0_PRIORITY   2

#define PIN_SW0 \
		{PIO_PA9, PIOA, ID_PIOA, PIO_INPUT, PIO_PULLUP | PIO_DEBOUNCE | PIO_IT_RISE_EDGE}


/*~~~~~~  Global variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
 SchMTaskType TaskConfig[TASK_MAX_NUM_TASKS] = 
  {
    /*Priority , ID, Task Function */
    {TASK_1MS_PRIORITY,   TASKS_1_MS,    SchM_Task_1ms},
    {TASK_2MSA_PRIORITY,  TASKS_2_MS_A,  SchM_Task_2ms_A},
    {TASK_2MSB_PRIORITY,  TASKS_2_MS_B,  SchM_Task_2ms_B},
    {TASK_10MS_PRIORITY,  TASKS_10_MS,   SchM_Task_10ms},
    {TASK_50MS_PRIORITY,  TASKS_50_MS,   SchM_Task_50ms},
    {TASK_100MS_PRIORITY, TASKS_100_MS,  SchM_Task_100ms},
    {TASK_SW0_PRIORITY,   TASK_SW0,      SchM_Task_SW0},
  };

SchMTaskType *TestTaskConfig;
    
SchMTaskType *TestTaskConfig2;
   /** LED0 blinking control. */
volatile bool bLed0Active = false ;

/** LED1 blinking control. */
volatile bool bLed1Active = true ;

/** SW LED blinking control. */
volatile bool bSW0Active = true ;

/** SW0 Pin Definition, used to configure the Pin and Pin Interrupt, see ConfigureSW0Button function  */
static const Pin PinSW0 = PIN_SW0;



/*~~~~~~  Local functions ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/**
 /**
 *  \brief Process Buttons Events
 *
 *  Change active states of LEDs when corresponding button events happened.
 */
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

/**
 *  \brief Handler for Button 1 rising edge interrupt.
 *
 *  Handle process led status change.
 */
static void SW0_Handler( const Pin* pPin )
{
	if ( pPin == &PinSW0 ) {
		ProcessButtonEvt( bSW0Active ) ;
		bSW0Active = !bSW0Active;
		//printf("SW0_Handler ... Rising Edge Detected.\n\r" );
    SchM_ActivateTask(TASK_SW0);
	}
}

/**
 *  \brief Configure the SW0 Push-button
 *
 *  Configure the PIO as inputs and generate corresponding interrupt when
 *  pressed or released.
 */

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


/**
 *  \brief Configure LEDs
 *
 *  Configures LEDs \#1 and \#2 (cleared by default).
 */
static void ConfigureLeds( void )
{
	LED_Configure( 0 ) ;
	LED_Configure( 1 ) ;
}

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
  
  
  /* Pin configurations */

	printf( "Configure LED PIOs.\n\r" ) ;
	ConfigureLeds() ;

	printf( "Configure SW0 button with denouncing.\n\r" ) ;
	ConfigureSW0Button() ;
	printf( "Press SW0 to Switch the LEDs blinking.\n\r" ) ;
  
  //Configures debug scope
  ConfigureScopeOut();

	/* Scheduler Inititalization */
	printf( "-- Scheduler Initialization --\n\r" ) ;
 
  TestTaskConfig = ( SchMTaskType * ) Mem_Alloc ( sizeof(SchMTaskType) * (uint8_t) TASK_MAX_NUM_TASKS );
 /* uint8_t temp = 0;
  temp = sizeof(SchMTaskType);
  printf("Size of SchMTaskType: %d bytes.\n\r" ,temp); */
  TestTaskConfig[0].TaskPriority = TASK_1MS_PRIORITY;
  TestTaskConfig[0].TaskId       = TASKS_1_MS;
  TestTaskConfig[0].TaskFcnPtr   = SchM_Task_1ms;
  
  TestTaskConfig[1].TaskPriority = TASK_2MSA_PRIORITY;
  TestTaskConfig[1].TaskId       = TASKS_2_MS_A;
  TestTaskConfig[1].TaskFcnPtr   = SchM_Task_2ms_A;
  
  TestTaskConfig[2].TaskPriority = TASK_2MSB_PRIORITY;
  TestTaskConfig[2].TaskId       = TASKS_2_MS_B;
  TestTaskConfig[2].TaskFcnPtr   = SchM_Task_2ms_B;
  
  TestTaskConfig[3].TaskPriority = TASK_10MS_PRIORITY;
  TestTaskConfig[3].TaskId       = TASKS_10_MS;
  TestTaskConfig[3].TaskFcnPtr   = SchM_Task_10ms;
  
  TestTaskConfig[4].TaskPriority = TASK_50MS_PRIORITY;
  TestTaskConfig[4].TaskId       = TASKS_50_MS;
  TestTaskConfig[4].TaskFcnPtr   = SchM_Task_50ms;
  
  TestTaskConfig[5].TaskPriority = TASK_100MS_PRIORITY;
  TestTaskConfig[5].TaskId       = TASKS_100_MS;
  TestTaskConfig[5].TaskFcnPtr   = SchM_Task_100ms;
  
  TestTaskConfig[6].TaskPriority = TASK_SW0_PRIORITY;
  TestTaskConfig[6].TaskId       = TASK_SW0;
  TestTaskConfig[6].TaskFcnPtr   = SchM_Task_SW0;
  
 
  TestTaskConfig2 = ( SchMTaskType * ) Mem_Alloc ( sizeof(SchMTaskType) * (uint8_t) TASK_MAX_NUM_TASKS );
  TestTaskConfig2[0].TaskPriority = TASK_1MS_PRIORITY;
  TestTaskConfig2[0].TaskId       = TASKS_1_MS;
  TestTaskConfig2[0].TaskFcnPtr   = SchM_Task_1ms;
  
  TestTaskConfig2[1].TaskPriority = TASK_1MS_PRIORITY;
  TestTaskConfig2[1].TaskId       = TASKS_1_MS;
  TestTaskConfig2[1].TaskFcnPtr   = SchM_Task_1ms;
  
  TestTaskConfig2[2].TaskPriority = TASK_1MS_PRIORITY;
  TestTaskConfig2[2].TaskId       = TASKS_1_MS;
  TestTaskConfig2[2].TaskFcnPtr   = SchM_Task_1ms;
  
  TestTaskConfig2[3].TaskPriority = TASK_1MS_PRIORITY;
  TestTaskConfig2[3].TaskId       = TASKS_1_MS;
  TestTaskConfig2[3].TaskFcnPtr   = SchM_Task_1ms;
  
  TestTaskConfig2[4].TaskPriority = TASK_1MS_PRIORITY;
  TestTaskConfig2[4].TaskId       = TASKS_1_MS;
  TestTaskConfig2[4].TaskFcnPtr   = SchM_Task_1ms;
    
  TestTaskConfig2[5].TaskPriority = TASK_1MS_PRIORITY;
  TestTaskConfig2[5].TaskId       = TASKS_1_MS;
  TestTaskConfig2[5].TaskFcnPtr   = SchM_Task_1ms;
  
  TestTaskConfig2[6].TaskPriority = TASK_1MS_PRIORITY;
  TestTaskConfig2[6].TaskId       = TASKS_1_MS;
  TestTaskConfig2[6].TaskFcnPtr   = SchM_Task_1ms;
  
 
  
	SchM_Init(TestTaskConfig);
	
	/* Should never reach this code */
	for(;;)
    {
		printf( "-- Unexpected Error at Scheduler Initialization --\n\r" ) ;
	}
}
