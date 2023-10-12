/* 
 * File:   application.c
 * Author: AhmedElnozahy
 *
 * Created on August 3, 2023, 4:54 PM
 */
#include "application.h"

void isr_int0();
Std_ReturnType ret = E_NOT_OK;

volatile uint8 Program_Select = 0 ;
uint8 btn_State = 0  , high_Valid = 0  , btn_State_Valid = 0 , last_btn_State_Valid = 0;

Led_t led1 = {.port_name = PORTC_INDEX , .pin = GPIO_PIN0 , .led_status = LED_OFF };
Led_t led2 = {.port_name = PORTC_INDEX , .pin = GPIO_PIN1 , .led_status = LED_OFF };

interrupt_INTx_t  int0 = {
    .EXT_InterruptHandler = isr_int0 ,
    .edge = INTERRUPT_RISING_EDGE ,  
    .mcu_pin.port = PORTB_INDEX,
    .mcu_pin.pin = GPIO_PIN0,
    .mcu_pin.direction = GPIO_DIR_INPUT,
    .mcu_pin.logic = GPIO_LOW,
    .source = EXTERNAL_INT0,
 
};

void isr_int0(){
    Program_Select++;
    ret = EEPROM_WriteByte(0x01B, Program_Select);
}
void Program1(void){
    led_TURN_ON(&led1);
    __delay_ms(1000);
    led_TURN_OFF(&led1);
    __delay_ms(1000);
}
void Program2(void){
    led_TURN_ON(&led2);
    __delay_ms(1000);
    led_TURN_OFF(&led2);
    __delay_ms(1000);
}
void Program3(void){
    led_TURN_ON(&led1);
    led_TURN_ON(&led2);
    __delay_ms(1000);
    led_TURN_OFF(&led1);
    led_TURN_OFF(&led2);
    __delay_ms(1000);
}

int main(){
     
    application_intialize();
    ret = interrupt_INTx_Init(&int0);

    ret = EEPROM_ReadByte(0x01B , &Program_Select);
    
    while(1)
    {
        if (1 == Program_Select){
            Program1();
        }else if (2 == Program_Select){
            Program2();
        }else if (3 == Program_Select){
            Program3();
        }else{
            led_TURN_OFF(&led1);
            led_TURN_OFF(&led2);
            
            if(Program_Select >= 4)
                Program_Select = 0;
        }
    
    } 
    return (EXIT_SUCCESS);
}

void application_intialize(void){
    Std_ReturnType ret = E_NOT_OK;
    //ecu_layer_intialize();
    ret = led_init(&led1);
    ret = led_init(&led2);

} 