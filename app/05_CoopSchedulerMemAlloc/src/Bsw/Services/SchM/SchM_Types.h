/*******************************************************************************/
/**
\file       SchM_Types.h
\brief      Scheduler Type Definitions.
   \~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
   \version       1.0
   \author        Francisco Martinez
   \description   Initial version of Task Type Definitios
   \date          20/08/2018
*/

#ifndef SCHM_TYPES
#define SCHM_TYPES

	/** Standard Types */
	#include "Std_Types.h"

	typedef  void  ( * SchMCallbackType )( void );

	/* Task Scheduler Tasks IDs definitions */
	typedef enum  
	{   
		TASK_1MS,
		TASK_2MSA,
		TASK_2MSB,
		TASK_10MS,
		TASK_50MS,
		TASK_100MS,
    TASK_SW0,
		TASK_BKG,
	}SchMTaskIdType;

  typedef enum
  {
    SUSPENDED,
    READY,
    RUNNING
  }SchMTaskStateType;


/*============================================================================*/
#endif /* SCHM_TYPES */
