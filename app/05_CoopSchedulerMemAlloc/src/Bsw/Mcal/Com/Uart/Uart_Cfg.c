
/****************************************************************************************************/
/**
\file       Uart_Cfg.c
\brief      
\author     Erick Vite
\version    1.0
\date       11/15/2020
*/
/****************************************************************************************************/


/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/
#include    "Uart_Cfg.h"

UartChannelType UartChannelConfig[]=
{
        /* UART Logical Channel 0  */
    {
        NULL,//(uint8_t)UART_CFG_PHY_CHANNEL4;
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL
    };
    
        /* UART Logical Channel 1  */

}

UartConfigType UartConfig[]=
{
    sizeof(UartChannelConfig) / sizeof(UartChannelType),
    PMC,
    &UartChannelConfig[0],
}
