/* 
 * File:   ecu_dc_motor.c
 * Author: AhmedSamy
 *
 * Created on August 29, 2023, 6:52 PM
 */

#include "ecu_dc_motor.h"

static PIN_config_t motor_pin1 ;
static PIN_config_t motor_pin2 ;

Std_ReturnType dc_motor_init( const dc_motor_t *__dc_motor){
    Std_ReturnType ret = E_OK;
    if(NULL == __dc_motor)
    {
        ret = E_OK;
    }else{
        motor_pin1.port = __dc_motor->dc_motor[DC_MOTOR_PIN_1].dc_motor_port;
        motor_pin1.pin = __dc_motor->dc_motor[DC_MOTOR_PIN_1].dc_motor_pin;
        motor_pin1.logic= __dc_motor->dc_motor[DC_MOTOR_PIN_1].dc_motor_status;
        motor_pin1.direction = GPIO_DIR_OUTPUT;
        
        motor_pin2.port = __dc_motor->dc_motor[DC_MOTOR_PIN_2].dc_motor_port;
        motor_pin2.pin = __dc_motor->dc_motor[DC_MOTOR_PIN_2].dc_motor_pin;
        motor_pin2.logic= __dc_motor->dc_motor[DC_MOTOR_PIN_2].dc_motor_status;
        motor_pin2.direction = GPIO_DIR_OUTPUT;
        
        ret = gpio_pin_direction_init(&motor_pin1);
        ret = gpio_pin_direction_init(&motor_pin2);
    }
    
    return ret;
}
Std_ReturnType dc_motor_Move_Right( const dc_motor_t *__dc_motor){
    Std_ReturnType ret = E_OK;
    if(NULL == __dc_motor)
    {
        ret = E_OK;
    }else{
        ret = gpio_pin_write_logic(&motor_pin1 , GPIO_HIGH);
        ret = gpio_pin_write_logic(&motor_pin2 , GPIO_LOW);
    }
    
    return ret;
    
}
Std_ReturnType dc_motor_Move_Left( const dc_motor_t *__dc_motor){
    Std_ReturnType ret = E_OK;
    if(NULL == __dc_motor)
    {
        ret = E_OK;
    }else{
        ret = gpio_pin_write_logic(&motor_pin1 , GPIO_LOW);
        ret = gpio_pin_write_logic(&motor_pin2 , GPIO_HIGH);
    }
    
    return ret;
    
}
Std_ReturnType dc_motor_Move_Stop( const dc_motor_t *__dc_motor){
    Std_ReturnType ret = E_OK;
    if(NULL == __dc_motor)
    {
        ret = E_OK;
    }else{
        ret = gpio_pin_write_logic(&motor_pin1 , GPIO_LOW);  
        ret = gpio_pin_write_logic(&motor_pin2 , GPIO_LOW);
    }
    
    return ret;
    
}
