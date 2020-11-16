/****************************************************************************************************/
/**
\file       Led_Ctrl.c
\brief      MCU abstraction level - LED control
\author     Abraham Tezmol
\version    1.0
\project    Tau 
\date       24/June/2016
*/
/****************************************************************************************************/

/*****************************************************************************************************
* Include files
*****************************************************************************************************/
/** Own headers */
#include     "Led_Ctrl.h"
/** Other modules */
#include     "led.h"

/*****************************************************************************************************
* Definition of module wide VARIABLEs 
*****************************************************************************************************/

/****************************************************************************************************
* Declaration of module wide FUNCTIONs 
****************************************************************************************************/

/****************************************************************************************************
* Definition of module wide MACROs / #DEFINE-CONSTANTs 
*****************************************************************************************************/

/****************************************************************************************************
* Declaration of module wide TYPEs 
*****************************************************************************************************/

/****************************************************************************************************
* Definition of module wide (CONST-) CONSTANTs 
*****************************************************************************************************/
 #define PIN_1MS \
		{PIO_PA2, PIOA, ID_PIOA, PIO_OUTPUT_1, PIO_DEFAULT}

 #define PIN_2AMS \
		{PIO_PC19, PIOC, ID_PIOC, PIO_OUTPUT_1, PIO_DEFAULT}

 #define PIN_2BMS \
		{PIO_PD28, PIOD, ID_PIOD, PIO_OUTPUT_1, PIO_DEFAULT}

 #define PIN_10MS \
		{PIO_PD27, PIOD, ID_PIOD, PIO_OUTPUT_1, PIO_DEFAULT}

 #define PIN_50MS \
		{PIO_PA6, PIOA, ID_PIOA, PIO_OUTPUT_1, PIO_DEFAULT}

 #define PIN_100MS \
		{PIO_PA0, PIOA, ID_PIOA, PIO_OUTPUT_1, PIO_DEFAULT}

#define PIN_SWint \
		{PIO_PD30, PIOD, ID_PIOD, PIO_OUTPUT_1, PIO_DEFAULT}


#define OSC_CHANNELS 7



static const Pin analizerOut[OSC_CHANNELS] = {PIN_1MS,
                                              PIN_2AMS,
                                              PIN_2BMS,
                                              PIN_10MS,
                                              PIN_50MS,
                                              PIN_100MS,
                                              PIN_SWint};
/****************************************************************************************************
* Code of module wide FUNCTIONS
*****************************************************************************************************/
void ConfigureScopeOut( void )
{
  uint8_t channel = 0;
  for (channel = 0; channel < OSC_CHANNELS; channel++)
  {
    PIO_Configure( &analizerOut[channel], 1 );
  }
}

void PingOsc( uint8_t channel )
{
  PIO_Set( &analizerOut[channel] );
  PIO_Clear( &analizerOut[channel] );
}



/*****************************************************************************************************/
/**
* \brief    Configures LED 0 and 1 of SAMV71 board
* \author   Abraham Tezmol
* \param    void
* \return   void
*/
void LedCtrl_Configure( void )
{
	LED_Configure( 0 ) ;
	LED_Configure( 1 ) ;
}

/*****************************************************************************************************/
/**
* \brief    Turn a combination of 2 LEDs with a unique blinking pattern.
			Call this function periodically @ 10ms to operate
* \author   Abraham Tezmol
* \param    void
* \return   void
*/
void LedCtrl_BlinkingPattern(void)
{
/* Global state machine status for LED flashing control  */
	static uint8_t LocPatternIndex;

    LocPatternIndex++;
    
    switch ((LocPatternIndex))
    {
        case  1:
            LED_Set(STD_OFF);
            LED_Set(STD_ON);
            break;
        case  11:
            LED_Set(STD_OFF);
            LED_Set(STD_ON);
            break;
        case  3:
            LED_Clear(STD_OFF);
            LED_Clear(STD_ON);
            break;
        case  13:
            LED_Clear(STD_OFF);
            LED_Clear(STD_ON);
            break;
        case 101:
            LocPatternIndex = 0;
            break;
        default:
            break;
    }
}
/*******************************************************************************/