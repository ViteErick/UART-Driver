/*******************************************************************************/
/**
\file       SchM_Cfg.h
\brief      
   \~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

*/

#ifndef SCHM_CFG_H
	#define SCHM_CFG_H

#include "Std_Types.h"
#include "SchM_Types.h"

  typedef struct
  {
    uint8_t           TaskPriority;
    SchMTaskIdType    TaskId;
    SchMCallbackType TaskFcnPtr;
  }SchMTaskType;
  
  typedef struct
  {
    uint8_t           NumberOfTasks;
    SchMTaskType      *SchMTaskConfig;
  }SchMConfigType;
  
  
  extern SchMTaskType TaskList[];
  extern SchMConfigType SchMConfigTask[];

/*============================================================================*/
#endif /* SCHM_CFG_H */
