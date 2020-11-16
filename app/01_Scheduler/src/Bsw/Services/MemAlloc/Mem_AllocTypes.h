/****************************************************************************************************/
/**
\file       Mem_AllocTypes.h
\brief      Types header file for mem alloc
\author     Jaime Leonel
\version    1.0
\project    Hw 2 
\date       05/October/2020
*/
/****************************************************************************************************/

#ifndef __MEM_ALLOCTYPES_H        /*prevent duplicated includes*/
#define __MEM_ALLOCTYPES_H

#include "Std_Types.h"

typedef void * MemReturnType;
typedef uint16_t MemSizeType;

typedef struct
{
  uint8_t * MemStart;
  uint8_t * MemEnd;
  uint8_t * CurrAddr;
  uint32_t  FreeBytes;
} MemHandlerType;


#endif