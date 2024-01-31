/* 
 * File:   application.c
 * Author: AhmedElnozahy
 *
 * Created on August 3, 2023, 4:54 PM
 */
#include "application.h"

Std_ReturnType ret = E_NOT_OK;
Led_t led1={
  .port_name = PORTC_INDEX , 
  .pin = GPIO_PIN0,
  .led_status = LED_OFF
};
Led_t led2={
  .port_name = PORTC_INDEX , 
  .pin = GPIO_PIN1,
  .led_status = LED_OFF
};
Led_t led3={
  .port_name = PORTC_INDEX , 
  .pin = GPIO_PIN2,
  .led_status = LED_OFF
};
Led_t led4={
  .port_name = PORTC_INDEX , 
  .pin = GPIO_PIN3,
  .led_status = LED_OFF
};

void RB4_HIGH_myISR(void){
    ret = led_TOG(&led1);
    __delay_ms(250);
    ret = led_TOG(&led1);
    __delay_ms(250);
};
void RB4_LOW_myISR(void){
    ret = led_TURN_OFF(&led2);
};
void RB5_HIGH_myISR(void){
    ret = led_TURN_ON(&led2);

};
void RB5_LOW_myISR(void){
    ret = led_TURN_OFF(&led2);
};

void RB6_HIGH_myISR(void){
    ret = led_TURN_OFF(&led3);

};

void RB6_LOW_myISR(void){
    ret = led_TURN_ON(&led3);


};
void RB7_HIGH_myISR(void){
    ret = led_TOG(&led4);
    __delay_ms(250);
    ret = led_TOG(&led4);
    __delay_ms(250);

};

void RB7_LOW_myISR(void){
    ret = led_TURN_ON(&led4);


};

interrupt_RBx_t int0_obj = {
    .EXT_InterruptHandler_HIGH = RB4_HIGH_myISR,
    .EXT_InterruptHandler_LOW = RB4_LOW_myISR,
    .priority = INTERRUPT_HIGH_PRIORITY,
    .mcu_pin.port = PORTB_INDEX , 
    .mcu_pin.pin = GPIO_PIN4 ,
    .mcu_pin.direction  = GPIO_DIR_INPUT
};

interrupt_RBx_t int1_obj = {
    .EXT_InterruptHandler_HIGH = RB5_HIGH_myISR,
    .EXT_InterruptHandler_LOW = RB5_LOW_myISR,
    .priority = INTERRUPT_LOW_PRIORITY,
    .mcu_pin.port = PORTB_INDEX , 
    .mcu_pin.pin = GPIO_PIN5 ,
    .mcu_pin.direction  = GPIO_DIR_INPUT
};

interrupt_RBx_t int2_obj = {
    .EXT_InterruptHandler_HIGH = RB6_HIGH_myISR,
    .EXT_InterruptHandler_LOW = RB6_LOW_myISR,
    .priority = INTERRUPT_HIGH_PRIORITY,
    .mcu_pin.port = PORTB_INDEX , 
    .mcu_pin.pin = GPIO_PIN6 ,
    .mcu_pin.direction  = GPIO_DIR_INPUT
};
interrupt_RBx_t int3_obj = {
    .EXT_InterruptHandler_HIGH = RB7_HIGH_myISR,
    .EXT_InterruptHandler_LOW = RB7_LOW_myISR,
    .priority = INTERRUPT_HIGH_PRIORITY,
    .mcu_pin.port = PORTB_INDEX , 
    .mcu_pin.pin = GPIO_PIN7 ,
    .mcu_pin.direction  = GPIO_DIR_INPUT
};


int main(){
    
    application_intialize();
    ret = interrupt_RBx_init(&int0_obj);
    ret = interrupt_RBx_init(&int1_obj);
    ret = interrupt_RBx_init(&int2_obj);
    ret = interrupt_RBx_init(&int3_obj);
    while(1)
    {
        
    } 
    return (EXIT_SUCCESS);
}

void application_intialize(void){
    Std_ReturnType ret = E_NOT_OK;
    //ecu_layer_intialize();
    ret = led_init(&led1); 
    ret = led_init(&led2); 
    ret = led_init(&led3); 
    ret = led_init(&led4); 


}