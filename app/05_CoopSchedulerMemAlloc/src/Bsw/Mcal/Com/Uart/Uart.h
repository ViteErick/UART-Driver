
/****************************************************************************************************/
/**
\file       Uart.h
\brief      
\author     Erick Vite
\version    1.0
\date       11/15/2020
*/
/****************************************************************************************************/
#ifndef UART_H        /*prevent duplicated includes*/ 
#define UART_H    

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/
#include    "Uart_Types.h"
#include    "Uart_Cfg.h"



#define UART_MASK_RXRDY     = 1
#define UART_MASK_TXRDY     = 2
#define UART_MASK_OVRE      = 32
#define UART_MASK_FRAME     = 64
#define UART_MASK_PARE      = 128
#define UART_MASK_TXEMPTY   = 512

#endif  /* UART_H */ 