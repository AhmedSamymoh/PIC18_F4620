/* 
 * File:   ecu_keypad.h
 * Author: AhmedSamy
 *
 * Created on September 11, 2023, 4:35 AM
 */

#ifndef ECU_KEYPAD_H
#define	ECU_KEYPAD_H

/* Section : Includes */

#include"../../MCAL/GPIO/GPIO.h"


/* Section: Macro Declarations */
#define KEYPAD_ROWS      4
#define KEYPAD_COLUMNS   4

/* Section: Macro Functions Declarations */

/* Section: Data Type Declarations */
typedef struct{
    PIN_config_t keypad_row_pins[KEYPAD_ROWS]; //R1 , R2 ,R3 ,R4 -> Output pins 
    PIN_config_t keypad_columns_pins[KEYPAD_COLUMNS];//C1 , C2 ,C3 ,C4 -> Input pins 
} keypad_t;

/* Section: Function Declarations */
Std_ReturnType keypad_init(const keypad_t * __keypad_obj);
Std_ReturnType keypad_get_value(const keypad_t * __keypad_obj , uint8 * value);


#endif	/* ECU_KEYPAD_H */

