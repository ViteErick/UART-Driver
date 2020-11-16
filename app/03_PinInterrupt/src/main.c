/* ----------------------------------------------------------------------------
 *         SAM Software Package License
 * ----------------------------------------------------------------------------
 * Copyright (c) 2011, Atmel Corporation
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * - Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the disclaimer below.
 *
 * Atmel's name may not be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * DISCLAIMER: THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
 * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * ----------------------------------------------------------------------------
 */


 /*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include "board.h"
#include <stdbool.h>
#include <stdio.h>
#include "pwmc.h"

/*----------------------------------------------------------------------------
 *        Local definitions
 *----------------------------------------------------------------------------*/

/** SW Version */
#define PINT_VERSION  "1.0"

/** Pin definition: Pin type definition is located at pio.h file */
/* 
  typedef struct _Pin
  {
  	uint32_t mask;     PIO_PA9                                      -> Bitmask indicating which pin(s) to configure.
  	Pio    *pio;       PIOA                                         -> Pointer to the PIO controller which has the pin(s).
  	uint8_t id;        ID_PIOA                                      -> Peripheral ID of the PIO controller which has the pin(s).
  	uint8_t type;      PIO_INPUT                                    -> Pin Type
  	uint8_t attribute; PIO_PULLUP | PIO_DEBOUNCE | PIO_IT_RISE_EDGE -> Pin attribute
  } Pin ;
*/
#define PIN_SW0 \
		{PIO_PA9, PIOA, ID_PIOA, PIO_INPUT, PIO_PULLUP | PIO_DEBOUNCE | PIO_IT_RISE_EDGE}

/*----------------------------------------------------------------------------
 *        Local variables
 *----------------------------------------------------------------------------*/

/** LED0 blinking control. */
volatile bool bLed0Active = false ;

/** LED1 blinking control. */
volatile bool bLed1Active = true ;

/** SW LED blinking control. */
volatile bool bSW0Active = true ;

/** SW0 Pin Definition, used to configure the Pin and Pin Interrupt, see ConfigureSW0Button function  */
static const Pin PinSW0 = PIN_SW0;

/*----------------------------------------------------------------------------
 *        Local functions
 *----------------------------------------------------------------------------*/

/**
 *  \brief Process Buttons Events
 *
 *  Change active states of LEDs when corresponding button events happened.
 */
static void ProcessButtonEvt( uint8_t ucButton )
{
	if ( ucButton == 0 ) {
		bLed0Active = true;
		bLed1Active = false;
		LED_Clear( 1 );
	}
	else
	{
		bLed0Active = false;
		bLed1Active = true ;
		LED_Clear( 0 );
	}
}

/**
 *  \brief Handler for Button 1 rising edge interrupt.
 *
 *  Handle process led status change.
 */
static void SW0_Handler( const Pin* pPin )
{
	if ( pPin == &PinSW0 ) {
		ProcessButtonEvt( bSW0Active ) ;
		bSW0Active = !bSW0Active;
		printf("SW0_Handler ... Rising Edge Detected.\n\r" );
	}
}

/**
 *  \brief Configure the SW0 Push-button
 *
 *  Configure the PIO as inputs and generate corresponding interrupt when
 *  pressed or released.
 */

static void ConfigureSW0Button( void )
{
	/* Configure PinSW0 as input. */
	PIO_Configure( &PinSW0, 1 ) ;

	/* Adjust PinSW0 denounce filter parameters, uses 10 Hz filter. */
	PIO_SetDebounceFilter( &PinSW0, 10 ) ;

	/* Initialize PinSW0 interrupt handler */
	PIO_ConfigureIt( &PinSW0, SW0_Handler ) ; /* Interrupt on rising edge, SW0_Handler as callback function */

	/* Enable PinSW0 controller IRQs. */
	NVIC_EnableIRQ( (IRQn_Type)PinSW0.id ) ;

	/* Enable PinSW0 line interrupts. */
	PIO_EnableIt( &PinSW0 ) ;
}

/**
 *  \brief Configure LEDs
 *
 *  Configures LEDs \#1 and \#2 (cleared by default).
 */
static void ConfigureLeds( void )
{
	LED_Configure( 0 ) ;
	LED_Configure( 1 ) ;
}

/*----------------------------------------------------------------------------
 *        Exported functions
 *----------------------------------------------------------------------------*/
/**
 *  \brief getting-started Application entry point.
 *
 *  \return Unused (ANSI-C compatibility).
 */
extern int main( void )
{

	/* Disable watchdog */
	WDT_Disable( WDT ) ;

	/* Output example information */
	printf( "\n\r-- Pin Interrupt (PIO_PA9) - Rising Edge Example %s --\n\r", PINT_VERSION ) ;
	printf( "-- %s\n\r", BOARD_NAME ) ;
	printf( "-- Compiled: %s %s With %s--\n\r", __DATE__, __TIME__ , COMPILER_NAME);

	/* Enable I and D cache */
	SCB_EnableICache();

	/* Configure systick for 1 ms. */
	TimeTick_Configure ();
  
    /* Pin configurations */

	printf( "Configure LED PIOs.\n\r" ) ;
	ConfigureLeds() ;

	printf( "Configure SW0 button with denouncing.\n\r" ) ;
	ConfigureSW0Button() ;
	printf( "Press SW0 to Switch the LEDs blinking.\n\r" ) ;

	while ( 1 ) {

		/* Toggle LED state if active */
		if ( bLed0Active ) {
			LED_Toggle( 0 );
			/* Wait for 500ms */
			Wait(500);
		}
		
		if(bLed1Active) {
		    LED_Toggle( 1 );
			/* Wait for 250ms */
			Wait(250);
	    } 
	}
}
