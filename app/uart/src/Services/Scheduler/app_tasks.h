/*******************************************************************************/
/**
\file       app_tasks.h
\brief      Tasks to be assigned to each execution thread of Task scheduler.
\author     Abraham Tezmol
\version    0.1
\date       10/Feb/2008
*/

#ifndef __APP_TASKS
#define __APP_TASKS

/*-- Includes ----------------------------------------------------------------*/
#include "compiler.h"
/* LED control definitions */ 
#include     "led_ctrl.h"
/* UART communication */
#include     "serial_ctrl.h"

/*-- Variables -------------------------------------------------------*/

/*-- Defines -----------------------------------------------------------------*/

/*-- Macros ------------------------------------------------------------------*/

/* List of tasks to be executed @ 1ms */
#define EXECUTE_1MS_TASKS()                 \
{											\
}
/* List of tasks to be executed @ 2ms, first group */
#define EXECUTE_2MS_A_TASKS()				\
{											\
}
/* List of tasks to be executed @ 2ms, second group */
#define EXECUTE_2MS_B_TASKS()				\
{											\
}
/* List of tasks to be executed @ 10ms */
#define EXECUTE_10MS_TASKS()				\
{											\
	vfnLedCtrl_BlinkingPattern();			\
}
/* List of tasks to be executed @ 50ms */
#define EXECUTE_50MS_TASKS()				\
{											\
  vfnSerialCtrl_Transfer();				\
}
/* List of tasks to be executed @ 100ms */
#define EXECUTE_100MS_TASKS()				\
{											\
}

/*============================================================================*/
#endif /*__APP_TASKS */
