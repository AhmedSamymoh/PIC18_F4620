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
        
        ret = gpio_pin_direction_init(& (__dc_motor->dc_motor_PIN[0]) );
        ret = gpio_pin_direction_init(& (__dc_motor->dc_motor_PIN[1]) );
    }
    
    return ret;
}
Std_ReturnType dc_motor_Move_Right( const dc_motor_t *__dc_motor){
    Std_ReturnType ret = E_OK;
    if(NULL == __dc_motor)
    {
        ret = E_OK;
    }else{
        ret = gpio_pin_write_logic(& (__dc_motor->dc_motor_PIN[0]) , GPIO_HIGH);
        ret = gpio_pin_write_logic(& (__dc_motor->dc_motor_PIN[1]) , GPIO_LOW);
    }
    
    return ret;
    
}
Std_ReturnType dc_motor_Move_Left( const dc_motor_t *__dc_motor){
    Std_ReturnType ret = E_OK;
    if(NULL == __dc_motor)
    {
        ret = E_OK;
    }else{
        ret = gpio_pin_write_logic(& (__dc_motor->dc_motor_PIN[0]) , GPIO_LOW);
        ret = gpio_pin_write_logic(& (__dc_motor->dc_motor_PIN[1]) , GPIO_HIGH);
    }
    
    return ret;
    
}
Std_ReturnType dc_motor_Move_Stop( const dc_motor_t *__dc_motor){
    Std_ReturnType ret = E_OK;
    if(NULL == __dc_motor)
    {
        ret = E_OK;
    }else{
        ret = gpio_pin_write_logic(& (__dc_motor->dc_motor_PIN[0]) , GPIO_LOW);  
        ret = gpio_pin_write_logic(& (__dc_motor->dc_motor_PIN[1]) , GPIO_LOW);
    }
    
    return ret;
    
}
