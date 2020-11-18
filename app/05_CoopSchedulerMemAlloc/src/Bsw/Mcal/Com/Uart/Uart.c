
/****************************************************************************************************/
/**
\file       Uart.c
\brief      
\author     Erick Vite
\version    1.0
\date       11/15/2020
*/
/****************************************************************************************************/


/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/
#include    <stdint.h>
#include    "Uart.h"






uint32_t Uart_GetStatus ( uint8_t Channel )
{
    return Channel->UART_SR;
}








void Uart_Isr(uint8_t Uart_Channel)
{

}

void UART0_Handler( void )
{
    Uart_Isr(0);
}

void UART1_Handler( void )
{
    Uart_Isr(1);
}

void UART2_Handler( void )
{
    Uart_Isr(2);
}

void UART3_Handler( void )
{
    Uart_Isr(3);
}

void UART4_Handler( void )
{
    Uart_Isr(4);
}
