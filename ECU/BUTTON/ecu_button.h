/* 
 * File:   ecu_button.h
 * Author: AhmedSamy
 *
 * Created on August 19, 2023, 11:26 PM
 */

#ifndef ECU_BUTTON_H
#define	ECU_BUTTON_H

/* Section : Includes */
#include "../../MCAL/GPIO/GPIO.h"
#include "ecu_button_config.h"

/* Section: Macro Declarations */

/* Section: Macro Functions Declarations */

/* Section: Data Type Declarations */
typedef enum{
    BUTTON_PRESSED,
    BUTTON_RELEASED
}button_state_t;
typedef enum{
    BUTTON_ACTIVE_HIGH,
    BUTTON_ACTIVE_LOW
}button_active_t;

typedef struct{
    PIN_config_t        button_pin;
    button_state_t      button_state;
    button_active_t     button_active_t;
}button_t;

/* Software Interfaces Declearations */
Std_ReturnType button_init(const button_t *btn);
Std_ReturnType button_read(const button_t *btn  ,button_state_t *btn_state );


#endif	/* ECU_BUTTON_H */

