/*******************************************************************************/
/**
\file       MemAlloc.c
\brief      Memory Allocation Handler
   \~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
   \version       1.0
   \author        Francisco Martinez Chavez
   \description   Initial version of Memory Allocation Handler
   \date          31/08/2018
*/

#include "MemAlloc.h"

#if TARGET_ARCH == ALLIGNMENT_64BIT
	#define TARGET_ARCH_MASK (0xFFFFFFFFFFFFFFF0)
#elif TARGET_ARCH == ALLIGNMENT_32BIT
	#define TARGET_ARCH_MASK (0xFFFFFFFC)
#elif TARGET_ARCH == ALLIGNMENT_16BIT
	#define TARGET_ARCH_MASK (0xFFFE)
#elif TARGET_ARCH == ALLIGNMENT_8BIT
	#define TARGET_ARCH_MASK (0xFF)	
#endif

/* Import labels from linker configuration */
extern uint32_t _heap_mem_start;
extern uint32_t _heap_mem_end;

/* Memory allocation control */
typedef struct 
{
	uint8_t *heap_start;
	uint8_t *heap_end;
	uint8_t *current_address;
}EsMallocType;

EsMallocType EsMallocControl =
{
	.heap_start = (uint8_t *)&_heap_mem_start,
	.heap_end = (uint8_t *)&_heap_mem_end,
	.current_address = (uint8_t *)&_heap_mem_start
};

/*
	Function: MemAlloc
		Allocates 
	Param: size 
		Type is uint16_t: max 65535 bytes size
*/
void * MemAlloc ( uint16_t size )
{
	uint8_t *Return_Val;
	uint32_t CurrentEndAddress;
	
	CurrentEndAddress = (uint32_t)EsMallocControl.current_address + size;
	
	if ( CurrentEndAddress > (uint32_t)EsMallocControl.heap_end )
	{
		printf( "Unnable to allocate. Heap End address exceeded.\n\r" );
		Return_Val = (void *)0; /* Null */
	}
	else
	{
		/* Allocated Pointer Address Update */
		Return_Val = (void *)EsMallocControl.current_address;
		/* 
			Allign current address to:
				8bytes (64bit architecture) -> #define TARGET_ARCH ALLIGNMENT_64BIT 
				4bytes (32bit architecture) -> #define TARGET_ARCH ALLIGNMENT_32BIT
				2bytes (16bit architecture) -> #define TARGET_ARCH ALLIGNMENT_16BIT
		*/
		CurrentEndAddress = (CurrentEndAddress + (TARGET_ARCH-1)) & TARGET_ARCH_MASK;
		/* Update current address for next MemAlloc invocation */
		EsMallocControl.current_address = (uint8_t *)CurrentEndAddress;
		printf( "Data allocated.\n\r" );
	}	 
	return(Return_Val);
}
