/* 
 * @File:   ecu_keypad.c
 * @Author: AhmedSamyElnozahy
 *
 * Created on Jun 11, 2023, 9:35 AM
 */

#include "ecu_keypad.h"
#define _XTAL_FREQ 8000000UL

static const uint8 btn_values[KEYPAD_ROWS][KEYPAD_COLUMNS] = {
                                                                {'7', '8', '9', '/'},
                                                                {'4', '5', '6', '*'},
                                                                {'1', '2', '3', '-'},
                                                                {'#', '0', '=', '+'}
                                                             };

/**
 * @brief Initialize the assigned pin of the keypad 
 * @param __keypad_obj pointer to the keypad configuration @keypad_t
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType keypad_init(const keypad_t * __keypad_obj){
    Std_ReturnType ret = E_OK;
    uint8 rows_c = 0 , columns_c = 0 ;
    if(NULL == __keypad_obj ){ //validation
        ret = E_NOT_OK;
    }else{
        for(rows_c = 0 ; rows_c < KEYPAD_ROWS ; rows_c++ )
        {
           ret = gpio_pin_init(& (__keypad_obj->keypad_row_pins[rows_c]) ); 
        }
        for(columns_c = 0 ; columns_c < KEYPAD_COLUMNS ; columns_c++ )
        {
            ret = gpio_pin_direction_init(& (__keypad_obj->keypad_columns_pins[columns_c]) ); 
        }
    }   
    return ret;
}

/**
 * @brief Initialize the assigned pin of the keypad 
 * @param __keypad_obj pointer to the keypad configuration @keypad_t
 * @param value
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType keypad_get_value(const keypad_t * __keypad_obj , uint8 * value){
    Std_ReturnType ret = E_OK;
    uint8 rows_c = 0 , columns_c = 0  ;
    Logic_t _logic = 0;
    
    if((NULL == __keypad_obj) || (NULL == value) ){ //validation
        ret = E_NOT_OK;
    }else{
        for(rows_c = 0 ; rows_c < KEYPAD_ROWS ; rows_c++ )
        {
            //configure all ROW pins to @GPIO_LOW
            for(uint8 i = 0 ; i < KEYPAD_ROWS ; i++){
                ret = gpio_pin_write_logic(&(__keypad_obj->keypad_row_pins[i]) , GPIO_LOW);
            }
            //configure a ROW pin for checking it with other Columns 
            ret = gpio_pin_write_logic(&(__keypad_obj->keypad_row_pins[rows_c]) , GPIO_HIGH);
            __delay_ms(10);
            
            //check
            for(columns_c = 0 ; columns_c < KEYPAD_COLUMNS ; columns_c++ )
            {
                ret = gpio_pin_read_logic( &(__keypad_obj->keypad_columns_pins[columns_c]) , &_logic);
                if(GPIO_HIGH == _logic)
                {
                    *value = btn_values[rows_c][columns_c];
                }
            }
        }
    }   
    return ret;
    
}