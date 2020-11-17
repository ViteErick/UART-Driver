
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



void Uart_Init ( const UartConfigType* Config)
{
    
}

Std_ReturnType Uart_SetBaudrate ( uint8_t Channel, uint32_t Baudrate );

void Uart_SetTxEnable ( uint8_t Channel, uint32_t Enable )
{
    while (Enable)
    {
        UartChannel.ChannelId/
        Uart->UART_CR = UART_CR_TXEN;
    }
    	if (enabled) {
		uart->UART_CR = UART_CR_TXEN;
	} else {
		uart->UART_CR = UART_CR_TXDIS;
	}
}

Std_ReturnType Uart_SendByte ( uint8_t Channel, uint8_t Byte )
{
    if ((1 = STATREG_UART))
    {
        Uart_Reg
    }
    
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
