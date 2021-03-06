/****************************************************************************************************/
/**
\file       Button_Ctrl.h
\brief      MCU abstraction level - Button control
\author     Francisco Martinez
\version    1.0
\date       2/Sep/2018
*/
/****************************************************************************************************/

#ifndef __BUTTON_CTRL_H        /*prevent duplicated includes*/
#define __BUTTON_CTRL_H

/*****************************************************************************************************
* Include files
*****************************************************************************************************/

/** Standard Types */
#include "Std_Types.h"

/** Used modules */

/*****************************************************************************************************
* Declaration of module wide TYPEs 
*****************************************************************************************************/

/*****************************************************************************************************
* Definition of module wide MACROs / #DEFINE-CONSTANTs 
*****************************************************************************************************/


/*****************************************************************************************************
* Declaration of module wide FUNCTIONS
*****************************************************************************************************/

/** Configures SW0 of SAMV71 board */
extern void ButtonCtrl_ConfigureSW0Button( void );





/**************************************************************************************************/

#endif /* __BUTTON_CTRL_H */