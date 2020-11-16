/****************************************************************************************************/
/**
\file       Mem_Alloc.h
\brief      Header file for mem alloc
\author     Jaime Leonel
\version    1.0
\project    Hw 2 
\date       05/October/2020
*/
/****************************************************************************************************/

#include "Mem_Alloc.h"

extern uint32_t _heap_mem_start;
extern uint32_t _heap_mem_end;
extern uint32_t heap_memsize;

MemHandlerType MemControl =
{
    .MemStart = (uint8_t *) &_heap_mem_start, /* Sets the start of the heap memory */
    .MemEnd = (uint8_t *) &_heap_mem_end, /* Sets the end of the heap memory */
    .CurrAddr = (uint8_t *) &_heap_mem_start, /* Initialize the current start address */
    .FreeBytes = (uint32_t ) &heap_memsize, 
};

MemReturnType Mem_Alloc ( MemSizeType size )
{
    //Returns a NULL pointer by default if not enough bytes are available
    MemReturnType ReturnData = NULL;
    printf( "Memory Allocation Initialization - %d bytes to be allocated\n\r",size);
    printf( "Memory Allocation Initialization - %d bytes left\n\r",MemControl.FreeBytes);
 
    if (  MemControl.FreeBytes > size )
    {
        ReturnData = MemControl.CurrAddr;
        MemControl.CurrAddr = MemControl.CurrAddr + ( size );
     
        while ( (uint32_t)MemControl.CurrAddr %4 != 0 )
        {
           MemControl.CurrAddr++;
        }
     MemControl.FreeBytes = MemControl.FreeBytes - size;
     printf( "Memory Allocation - %d bytes left\n\r",MemControl.FreeBytes) ;
     printf( "Memory Allocation - %p was the returned address\n\r",ReturnData) ;
    }
    
    return ReturnData;
}
