
/****************************************************************************************************/
/**
\file       Uart_Cfg.h
\brief      
\author     Erick Vite
\version    1.0
\date       11/15/2020
*/
/****************************************************************************************************/
#ifndef UART_CFG_H        /*prevent duplicated includes*/ 
#define UART_CFG_H    

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include    <stdint.h>


typedef void (*TxNotification) ( void );
typedef void (*RxNotification) ( void );

typedef void (*ErrorNotification) ( UartErrorType Error );

typedef struct 
{
    uint8_t ChannelId;
    uint32_t IsrEn;
    uint8_t Mode;
    uint8_t Parity;
    uint32_t Baudrate;
    TxNotification UartTxNotification;
    RxNotification UartRxNotification;
    ErrorNotification UartErrorNotification;
}UartChannelType;


typedef struct 
{
    uint8_t         UartNumberOfChannels;
    uint8_t         ClkSrc;
    UartChannelType UartChannel;
}UartConfigType;

#endif  /* UART_CFG_H */ 