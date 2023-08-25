/* 
 * File:   ecu_button.c
 * Author: AhmedSamy
 *
 * Created on August 19, 2023, 11:27 PM
 */

#include "ecu_button.h"

/**
 * @brief Initialize the assigned pin to be (GPIO_DIR_INPUT)
 * @param btn pointer to the button configuration @button_t
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType button_init(const button_t *btn){
    Std_ReturnType ret = E_OK; 
    if(NULL == btn)
    {
        ret = E_NOT_OK;
    }else
    {
        ret = gpio_pin_direction_init( &(btn->button_pin) );
    }
    return ret;
}

/**
 * @brief Read the state assigned pin  
 * @param btn_state @ref @button_state_t
 * @param btn pointer to the button configuration @button_t
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType button_read(const button_t *btn  ,button_state_t *btn_state ){
    Std_ReturnType ret = E_OK;
    Logic_t logic = GPIO_LOW;
    if(NULL == btn)
    {
        ret = E_NOT_OK;
    }else
    {
        gpio_pin_read_logic(&(btn->button_pin) , &logic);
        if(btn->button_active_t == BUTTON_ACTIVE_HIGH )
        {
            if(GPIO_HIGH == logic)
            {
                *btn_state = BUTTON_PRESSED;
            }
            else{
                *btn_state = BUTTON_RELEASED;
            }
        }
        else if(btn->button_active_t == BUTTON_ACTIVE_LOW )
        {
            if(GPIO_HIGH == logic)
            {
                *btn_state = BUTTON_RELEASED;
            }
            else{
                *btn_state = BUTTON_PRESSED;
            }
        }else{/*NOTHING*/}
        ret = E_OK;
    }
    return ret;
    
}