/****************************************************************************************************/
/**
\file       SchM_Cfg.c
\brief      

*/
/****************************************************************************************************/

/*****************************************************************************************************
* Include files
*****************************************************************************************************/
#include "SchM_Cfg.h"
#include "SchM_Tasks.h"

SchMTaskType TaskList[]=
{
 /*  TaskPriority ,  TaskId ,       TaskFcnPtr       */
  {  8,              TASK_1MS,    SchM_Task_1ms   },
  {  7,              TASK_2MSA,   SchM_Task_2ms_A },
  {  6,              TASK_2MSB,   SchM_Task_2ms_B },
  {  5,              TASK_10MS,   SchM_Task_10ms  },
  {  4,              TASK_50MS,   SchM_Task_50ms  },
  {  3,              TASK_100MS,  SchM_Task_100ms },
  { 10,              TASK_SW0,    SchM_Task_SW0   }
};

SchMConfigType SchMConfigTask[]=
{
	{
		sizeof(TaskList)/sizeof(SchMTaskType),
		&TaskList[0]
	}
};
