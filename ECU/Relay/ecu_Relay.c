/* 
 * File:   Relay.c
 * Author: AhmedSamy
 *
 * Created on August 26, 2023, 1:47 AM
 */

#include "ecu_Relay.h"


/**
 * @brief Initialize the assigned pin to be (GPIO_DIR_OUTPUT)
 * @param relay pointer to the relay configuration @relay_t
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType relay_init( const relay_t * relay ){
    Std_ReturnType ret = E_OK;
    if(NULL == relay ){//validation
        ret = E_NOT_OK;
    }else{
        PIN_config_t pin_object = {
            .port = relay->relay_port,
            .pin  = relay->relay_pin,
            .direction = GPIO_DIR_OUTPUT, 
            .logic = relay->relay_state,
        };
        gpio_pin_direction_init( &pin_object );
    }
    return ret;
}

/**
 * @brief Turn the relay ON
 * @param relay pointer to the relay configuration @relay_t
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType relay_ON( const relay_t * relay ){
    Std_ReturnType ret = E_OK;
    if(NULL == relay ){
        ret = E_NOT_OK;
    }else{
        PIN_config_t pin_object = {
            .port = relay->relay_port,
            .pin  = relay->relay_pin,
            .direction = GPIO_DIR_OUTPUT, 
            .logic = relay->relay_state,
        };
        gpio_pin_write_logic( &pin_object , GPIO_HIGH );
    }
    return ret;
    
}

/**
 * @brief Turn the relay OFF
 * @param relay pointer to the relay configuration @relay_t
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType relay_OFF( const relay_t * relay ){
    Std_ReturnType ret = E_OK;
    if(NULL == relay ){
        ret = E_NOT_OK;
    }else{
         PIN_config_t pin_object = {
            .port = relay->relay_port,
            .pin  = relay->relay_pin,
            .direction = GPIO_DIR_OUTPUT, 
            .logic = relay->relay_state,
        };
        gpio_pin_write_logic( &pin_object , GPIO_LOW );
        
    }
    return ret;

}

