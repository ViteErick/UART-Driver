
/****************************************************************************************************/
/**
\file       Uart_Types.h
\brief      
\author     Erick Vite
\version    1.0
\date       11/15/2020
*/
/****************************************************************************************************/
#ifndef UART_TYPES_H        /*prevent duplicated includes*/ 
#define UART_TYPES_H    

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/
#include    "Std_Types.h"


typedef enum
{
    UART_ERROR_OVERRUN,
    UART_ERROR_FRAMING,
    UART_ERROR_PARITY,
}UartErrorType;





#endif  /* UART_TYPES_H */ 