/* 
 * File:   application.h
 * Author: AhmedElnozahy
 *
 * Created on August 3, 2023, 4:54 PM
 */

#ifndef APPLICATION_H
#define	APPLICATION_H

/* Section : Includes */
#include "MCAL/GPIO/GPIO.h"
#include "ECU/ecu_layer_init.h"

/* Section: Macro Declarations */

/* Section: Macro Functions Declarations */

/* Section: Data Type Declarations */
extern lcd_4bit_t lcd_1;
extern lcd_8bit_t lcd_2;
//extern keypad_t ke
/* Section: Function Declarations */
void application_intialize(void);

#define _XTAL_FREQ 8000000UL

#endif	/* APPLICATION_H */

