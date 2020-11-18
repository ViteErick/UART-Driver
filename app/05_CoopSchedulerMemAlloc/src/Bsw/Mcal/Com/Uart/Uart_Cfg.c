
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
#include    "Uart.h"

/*   UART CHANNEL CONFIGURATION DEFINITIONS    */
#define UART_CFG_PHY_CHANNEL0    =   0
#define UART_CFG_PHY_CHANNEL1    =   1
#define UART_CFG_PHY_CHANNEL2    =   2
#define UART_CFG_PHY_CHANNEL3    =   3
#define UART_CFG_PHY_CHANNEL4       4
/*  INTERRUPT CONFIGURATION DEFINITIONS */
#define UART_CFG_INT_DISABLE        =   0
#define UART_CFG_INT_RXRDY          =   1
#define UART_CFG_INT_TXRDY          =   2
#define UART_CFG_INT_OVR_ERROR      =   32
#define UART_CFG_INT_FRAME_ERROR    =   64
#define UART_CFG_INT_PAR_ERROR      =   128
#define UART_CFG_INT_TXEMPTY        =   512
/*  MODE CONFIGURATION DEFINES  */
#define UART_CFG_MODE_NORMAL    =   0   
#define UART_CFG_MODE_AUTO      =   1
#define UART_CFG_MODE_LOOPBACK  =   2
/*  CLOCK CONFIGURATION DEFINES */
#define UART_CFG_PER_CLK    =   0
#define UART_CFG_PMC_CLK    =   1






UartChannelType UartChannelConfig[]=
{
        /* UART Logical Channel 0  */
    {
        UART_CFG_PHY_CHANNEL4,
        UART_CFG_INT_RXRDY,
        UART_CFG_MODE_NORMAL,
        NULL,
        UART_CFG_PER_CLK,
        *TxNotification,
        (*RxNotification) ,
        (*ErrorNotification),
    };
    
        /* UART Logical Channel 1  */
};

UartConfigType UartConfig[]=
{
    sizeof(UartChannelConfig) / sizeof(UartChannelType),
    PMC,
    &UartChannelConfig[0],
}
