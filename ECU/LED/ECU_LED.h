/* 
 * File:   ECU_LED.h
 * Author: AhmedElnozahy
 *
 * Created on August 12, 2023, 7:50 PM
 */

#ifndef ECU_LED_H
#define	ECU_LED_H

/* Section : Includes */
#include "../../MCAL/GPIO/GPIO.h"
#include "ECU_LEC_Config.h"

/* Section: Macro Declarations */

/* Section: Macro Functions Declarations */

/* Section: Data Type Declarations */

typedef enum{
    LED_OFF,
    LED_ON
}Led_status_t;

typedef struct{
    uint8 port_name  : 4;
    uint8 pin        : 3;
    uint8 led_status : 1;
} Led_t;

/* Section: Function Declarations */
Std_ReturnType led_init(const Led_t * led);
Std_ReturnType led_TURN_ON(const Led_t * led);
Std_ReturnType led_TURN_OFF(const Led_t * led);
Std_ReturnType led_TOG(const Led_t * led);


#endif	/* ECU_LED_H */

