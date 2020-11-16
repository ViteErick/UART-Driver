/* ---------------------------------------------------------------------------- */
/*                  Atmel Microcontroller Software Support                      */
/*                       SAM Software Package License                           */
/* ---------------------------------------------------------------------------- */
/* Copyright (c) 2014, Atmel Corporation                                        */
/*                                                                              */
/* All rights reserved.                                                         */
/*                                                                              */
/* Redistribution and use in source and binary forms, with or without           */
/* modification, are permitted provided that the following condition is met:    */
/*                                                                              */
/* - Redistributions of source code must retain the above copyright notice,     */
/* this list of conditions and the disclaimer below.                            */
/*                                                                              */
/* Atmel's name may not be used to endorse or promote products derived from     */
/* this software without specific prior written permission.                     */
/*                                                                              */
/* DISCLAIMER:  THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR   */
/* IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF */
/* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE   */
/* DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR ANY DIRECT, INDIRECT,      */
/* INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT */
/* LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,  */
/* OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF    */
/* LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING         */
/* NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, */
/* EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.                           */
/* ---------------------------------------------------------------------------- */

INPUT (C:\embeddedSystems\003\3.UART\SAMx_713\SAMx\SAMV7x\SAMV71x\app\05_CoopSchedulerMemAlloc\SAMV71_Xplained_Ultra\Debug\system_sam.o 
C:\embeddedSystems\003\3.UART\SAMx_713\SAMx\SAMV7x\SAMV71x\app\05_CoopSchedulerMemAlloc\SAMV71_Xplained_Ultra\Debug\syscalls.o 
C:\embeddedSystems\003\3.UART\SAMx_713\SAMx\SAMV7x\SAMV71x\app\05_CoopSchedulerMemAlloc\SAMV71_Xplained_Ultra\Debug\startup_sam.o 
C:\embeddedSystems\003\3.UART\SAMx_713\SAMx\SAMV7x\SAMV71x\app\05_CoopSchedulerMemAlloc\SAMV71_Xplained_Ultra\Debug\dbg_console.o 
C:\embeddedSystems\003\3.UART\SAMx_713\SAMx\SAMV7x\SAMV71x\app\05_CoopSchedulerMemAlloc\SAMV71_Xplained_Ultra\Debug\board_lowlevel.o 
C:\embeddedSystems\003\3.UART\SAMx_713\SAMx\SAMV7x\SAMV71x\app\05_CoopSchedulerMemAlloc\SAMV71_Xplained_Ultra\Debug\board_memories.o 
C:\embeddedSystems\003\3.UART\SAMx_713\SAMx\SAMV7x\SAMV71x\app\05_CoopSchedulerMemAlloc\SAMV71_Xplained_Ultra\Debug\led.o 
C:\embeddedSystems\003\3.UART\SAMx_713\SAMx\SAMV7x\SAMV71x\app\05_CoopSchedulerMemAlloc\SAMV71_Xplained_Ultra\Debug\wdt.o 
C:\embeddedSystems\003\3.UART\SAMx_713\SAMx\SAMV7x\SAMV71x\app\05_CoopSchedulerMemAlloc\SAMV71_Xplained_Ultra\Debug\pmc.o 
C:\embeddedSystems\003\3.UART\SAMx_713\SAMx\SAMV7x\SAMV71x\app\05_CoopSchedulerMemAlloc\SAMV71_Xplained_Ultra\Debug\pio.o 
C:\embeddedSystems\003\3.UART\SAMx_713\SAMx\SAMV7x\SAMV71x\app\05_CoopSchedulerMemAlloc\SAMV71_Xplained_Ultra\Debug\pio_it.o 
C:\embeddedSystems\003\3.UART\SAMx_713\SAMx\SAMV7x\SAMV71x\app\05_CoopSchedulerMemAlloc\SAMV71_Xplained_Ultra\Debug\supc.o 
C:\embeddedSystems\003\3.UART\SAMx_713\SAMx\SAMV7x\SAMV71x\app\05_CoopSchedulerMemAlloc\SAMV71_Xplained_Ultra\Debug\exceptions.o 
C:\embeddedSystems\003\3.UART\SAMx_713\SAMx\SAMV7x\SAMV71x\app\05_CoopSchedulerMemAlloc\SAMV71_Xplained_Ultra\Debug\mpu.o 
C:\embeddedSystems\003\3.UART\SAMx_713\SAMx\SAMV7x\SAMV71x\app\05_CoopSchedulerMemAlloc\SAMV71_Xplained_Ultra\Debug\Main.o 
C:\embeddedSystems\003\3.UART\SAMx_713\SAMx\SAMV7x\SAMV71x\app\05_CoopSchedulerMemAlloc\SAMV71_Xplained_Ultra\Debug\Led_Ctrl.o 
C:\embeddedSystems\003\3.UART\SAMx_713\SAMx\SAMV7x\SAMV71x\app\05_CoopSchedulerMemAlloc\SAMV71_Xplained_Ultra\Debug\Button_Ctrl.o 
C:\embeddedSystems\003\3.UART\SAMx_713\SAMx\SAMV7x\SAMV71x\app\05_CoopSchedulerMemAlloc\SAMV71_Xplained_Ultra\Debug\SchM.o 
C:\embeddedSystems\003\3.UART\SAMx_713\SAMx\SAMV7x\SAMV71x\app\05_CoopSchedulerMemAlloc\SAMV71_Xplained_Ultra\Debug\SchM_Tasks.o 
C:\embeddedSystems\003\3.UART\SAMx_713\SAMx\SAMV7x\SAMV71x\app\05_CoopSchedulerMemAlloc\SAMV71_Xplained_Ultra\Debug\Wdg.o 
C:\embeddedSystems\003\3.UART\SAMx_713\SAMx\SAMV7x\SAMV71x\app\05_CoopSchedulerMemAlloc\SAMV71_Xplained_Ultra\Debug\MemAlloc.o 
C:\embeddedSystems\003\3.UART\SAMx_713\SAMx\SAMV7x\SAMV71x\app\05_CoopSchedulerMemAlloc\SAMV71_Xplained_Ultra\Debug\SchM_Cfg.o)

/*------------------------------------------------------------------------------
 *      Linker script for running in internal FLASH on the ATSAMV71Q21
 *----------------------------------------------------------------------------*/

OUTPUT_FORMAT("elf32-littlearm", "elf32-littlearm", "elf32-littlearm")
OUTPUT_ARCH(arm)
SEARCH_DIR(.)

/* Memory Spaces Definitions */
MEMORY
{
  rom (rx)  : ORIGIN = 0x00400000, LENGTH = 0x00200000
  heap_memalloc(rwx) : ORIGIN = 0x20400000, LENGTH = 0x00010000
  ram (rwx) : ORIGIN = 0x20410000, LENGTH = 0x00050000
  sdram(rwx): ORIGIN = 0x70000000, LENGTH = 0x00200000
}

/* The stack size used by the application. NOTE: you need to adjust according to your application. */
STACK_SIZE = DEFINED(STACK_SIZE) ? STACK_SIZE : 0x2000;

/* The heapsize used by the application. NOTE: you need to adjust according to your application. */
HEAP_SIZE = DEFINED(HEAP_SIZE) ? HEAP_SIZE : 0x1000;

heap_memsize = DEFINED(heap_memsize) ? heap_memsize : 0x1000; 

INCLUDE ..\..\..\toolset\gcc\sam_flash.ld
INCLUDE ..\..\..\toolset\gcc\sam_sdram.ld
