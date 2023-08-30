/* 
 * File:   ecu_dc_motor.h
 * Author: AhmedSamy
 *
 * Created on August 29, 2023, 6:50 PM
 */

#ifndef ECU_DC_MOTOR_H
#define	ECU_DC_MOTOR_H

/* Section : Includes */
#include "../../MCAL/GPIO/GPIO.h"
#include "ecu_dc_motor_cfg.h"

/* Section: Macro Declarations */

#define DC_MOTOR_ON     0X01U
#define DC_MOTOR_OFF    0X00U

#define DC_MOTOR_PIN_1  0X01U
#define DC_MOTOR_PIN_2  0X02U

/* Section: Macro Functions Declarations */

/* Section: Data Type Declarations */
/*typedef struct{
    uint8 dc_motor_port   : 4;
    uint8 dc_motor_pin    : 3;
    uint8 dc_motor_status : 1;
}dc_motor_pins_t;
*/

typedef struct{
    PIN_config_t dc_motor_PIN[2];
}dc_motor_t;

/* Section: Function Declarations */

Std_ReturnType dc_motor_init( const dc_motor_t *__dc_motor);
Std_ReturnType dc_motor_Move_Right( const dc_motor_t *__dc_motor);
Std_ReturnType dc_motor_Move_Left( const dc_motor_t *__dc_motor);
Std_ReturnType dc_motor_Move_Stop( const dc_motor_t *__dc_motor);


#endif	/* ECU_DC_MOTOR_H */

