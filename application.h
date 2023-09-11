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
extern keypad_t keypad1;
extern segment_pin_t seg1 ;
/* Section: Function Declarations */
void application_intialize(void);

#define _XTAL_FREQ 8000000UL

#endif	/* APPLICATION_H */

