/* 
 * File:   ECU_LED.c
 * Author: AhmedElnozahy
 *
 * Created on August 12, 2023, 11:44 PM
 */

#include "ECU_LED.h"

/**
 * 
 * @param led
 * @return 
 */
Std_ReturnType led_init(const Led_t * led){
    Std_ReturnType ret = E_OK;
    if(NULL == led)
    {
        ret = E_NOT_OK;
    }else{
        PIN_config_t pin_obj =  {
                                .port = led->port_name ,
                                .pin = led->pin ,
                                .direction = GPIO_DIR_OUTPUT,
                                .logic = led->led_status  
                                };
        gpio_pin_init(&pin_obj);
    }
    
    return ret;
}

/**
 * 
 * @param led
 * @return 
 */
Std_ReturnType led_TURN_ON(const Led_t * led){
    Std_ReturnType ret = E_OK;

    if(NULL == led)
    {
        ret = E_NOT_OK;
    }else{
        PIN_config_t pin_obj =  {
                                .port = led->port_name  ,
                                .pin = led->pin ,
                                .direction = GPIO_DIR_OUTPUT,
                                .logic = led->led_status  
                                };
        gpio_pin_write_logic(&pin_obj , GPIO_HIGH);
    }
    return ret;
}


/**
 * 
 * @param led
 * @return 
 */
Std_ReturnType led_TURN_OFF(const Led_t * led){
    Std_ReturnType ret = E_OK;

    if(NULL == led)
    {
        ret = E_NOT_OK;
    }else{
        PIN_config_t pin_obj =  {
                                .port      = led->port_name  ,
                                .pin       = led->pin ,
                                .direction = GPIO_DIR_OUTPUT,
                                .logic     = led->led_status  
                                };
        gpio_pin_write_logic(&pin_obj , GPIO_LOW);
    }
    
    return ret;

}

/**
 * 
 * @param led
 * @return 
 */
Std_ReturnType led_TOG(const Led_t * led){
    Std_ReturnType ret = E_OK;

    if(NULL == led)
    {
        ret = E_NOT_OK;
    }else{
        PIN_config_t pin_obj =  {
                                .port      = led->port_name  ,
                                .pin       = led->pin ,
                                .direction = GPIO_DIR_OUTPUT,
                                .logic     = led->led_status  
                                };
        gpio_pin_toggle_logic( &pin_obj );
    }
    
    return ret;

}

