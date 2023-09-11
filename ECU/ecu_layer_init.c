/* 
 * File:   ecu_layer_init.c
 * Author: AhmedElnozahy
 *
 * Created on August 3, 2023, 4:54 PM
 */

#include "ecu_layer_init.h"



Std_ReturnType ret = E_NOT_OK;
segment_pin_t seg1 = {
    
    .segments_pins[0].port = PORTD_INDEX,
    .segments_pins[0].pin = GPIO_PIN0,
    .segments_pins[0].logic = GPIO_LOW,
    .segments_pins[0].direction = GPIO_DIR_OUTPUT,
    
    .segments_pins[1].port = PORTD_INDEX,
    .segments_pins[1].pin = GPIO_PIN1,
    .segments_pins[1].logic = GPIO_LOW,
    .segments_pins[1].direction = GPIO_DIR_OUTPUT,
    
 
    .segments_pins[2].port = PORTD_INDEX,
    .segments_pins[2].pin = GPIO_PIN2,
    .segments_pins[2].logic = GPIO_LOW,
    .segments_pins[2].direction = GPIO_DIR_OUTPUT,
    
    .segments_pins[3].port = PORTD_INDEX,
    .segments_pins[3].pin = GPIO_PIN3,
    .segments_pins[3].logic = GPIO_LOW,
    .segments_pins[3].direction = GPIO_DIR_OUTPUT,
    
    .seven_segment_mode = SEGMENT_COMMON_CATHODE
};
keypad_t keypad1 = {
   /*Rows*/
  .keypad_row_pins[0].port = PORTC_INDEX,  
  .keypad_row_pins[0].pin =  GPIO_PIN0,  
  .keypad_row_pins[0].direction = GPIO_DIR_OUTPUT,  
  .keypad_row_pins[0].logic = GPIO_HIGH,
  
  .keypad_row_pins[1].port = PORTC_INDEX,  
  .keypad_row_pins[1].pin =  GPIO_PIN1,  
  .keypad_row_pins[1].direction = GPIO_DIR_OUTPUT,  
  .keypad_row_pins[1].logic = GPIO_HIGH,  
  
  .keypad_row_pins[2].port = PORTC_INDEX,  
  .keypad_row_pins[2].pin =  GPIO_PIN2,  
  .keypad_row_pins[2].direction = GPIO_DIR_OUTPUT,  
  .keypad_row_pins[2].logic = GPIO_HIGH, 
  
  .keypad_row_pins[3].port = PORTC_INDEX,  
  .keypad_row_pins[3].pin =  GPIO_PIN3,  
  .keypad_row_pins[3].direction = GPIO_DIR_OUTPUT,  
  .keypad_row_pins[3].logic = GPIO_HIGH,
  
   /*Columns*/
  .keypad_columns_pins[0].port = PORTC_INDEX,  
  .keypad_columns_pins[0].pin =  GPIO_PIN4,  
  .keypad_columns_pins[0].direction = GPIO_DIR_INPUT,  
  .keypad_columns_pins[0].logic = GPIO_LOW,
  
  .keypad_columns_pins[1].port = PORTC_INDEX,  
  .keypad_columns_pins[1].pin =  GPIO_PIN5,  
  .keypad_columns_pins[1].direction = GPIO_DIR_INPUT,  
  .keypad_columns_pins[1].logic = GPIO_LOW,  
  
  .keypad_columns_pins[2].port = PORTC_INDEX,  
  .keypad_columns_pins[2].pin =  GPIO_PIN6,  
  .keypad_columns_pins[2].direction = GPIO_DIR_INPUT,  
  .keypad_columns_pins[2].logic = GPIO_LOW, 
  
  .keypad_columns_pins[3].port = PORTC_INDEX,  
  .keypad_columns_pins[3].pin =  GPIO_PIN7,  
  .keypad_columns_pins[3].direction = GPIO_DIR_INPUT,  
  .keypad_columns_pins[3].logic = GPIO_LOW,
  
};

void ecu_layer_intialize(void){
    Std_ReturnType ret = E_NOT_OK;
    ret = keypad_init(&keypad1);
    ret = seven_segment_init(&seg1);

  
}


