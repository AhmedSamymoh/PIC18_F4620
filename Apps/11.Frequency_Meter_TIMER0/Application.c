/* 
 * File:   application.c
 * Author: AhmedElnozahy
 *
 * Created on August 3, 2023, 4:54 PM
 */
#include "application.h"

Std_ReturnType ret = E_NOT_OK;

uint16 countervalue = 0;
void TMR0_InterruptHANDLER(){
     
    countervalue++;
    
}
lcd_4bit_t lcd1 = {
    .lcd_rs.port = PORTC_INDEX,
    .lcd_rs.pin = GPIO_PIN0,
    .lcd_rs.logic = GPIO_LOW,
    .lcd_rs.direction = GPIO_DIR_OUTPUT,
    
    .lcd_en.port = PORTC_INDEX,
    .lcd_en.pin = GPIO_PIN1,
    .lcd_en.logic = GPIO_LOW,
    .lcd_en.direction = GPIO_DIR_OUTPUT,
    
    .lcd_data[0].port = PORTC_INDEX , 
    .lcd_data[0].pin = GPIO_PIN2 , 
    .lcd_data[0].logic = GPIO_LOW , 
    .lcd_data[0].direction = GPIO_DIR_OUTPUT , 
    
    .lcd_data[1].port = PORTC_INDEX , 
    .lcd_data[1].pin = GPIO_PIN3 , 
    .lcd_data[1].logic = GPIO_LOW , 
    .lcd_data[1].direction = GPIO_DIR_OUTPUT , 
    
    .lcd_data[2].port = PORTC_INDEX , 
    .lcd_data[2].pin = GPIO_PIN4 , 
    .lcd_data[2].logic = GPIO_LOW , 
    .lcd_data[2].direction = GPIO_DIR_OUTPUT , 
    
    .lcd_data[3].port = PORTC_INDEX , 
    .lcd_data[3].pin = GPIO_PIN5 , 
    .lcd_data[3].logic = GPIO_LOW , 
    .lcd_data[3].direction = GPIO_DIR_OUTPUT , 
    
};


timer0_t timer0_obj = {
    .timer0_source_edge = TIMER0_CFG_RISING_EDGE,
    .timer0_mode = TIMER0_CFG_COUNTER_MODE,
    .TMR0_InterruptHandler = TMR0_InterruptHANDLER,
    .timer0_register_size = TIMER0_CFG_16BIT_REGISTER,

};    

uint8 str[7];

int main(){

    application_intialize();
    ret = lcd_4bit_send_string_pos(&lcd1 , 1 , 1 , "Frequency Meter");
    __delay_ms(2000);
    
    ret = TIMER0_Init(&timer0_obj);

    while(1)
    {
        /*Disable TIMER0 TO GET THE Frequency every 1sec*/
        TIMER0_Interrupt_Enable();
        /*read the timer0 Counter */
        ret = TIMER0_READ(&timer0_obj , &countervalue);
        ret = TIMER0_WRITE(&timer0_obj , 0);
        __delay_ms(1000);
        ret = conv_uint8_to_string(countervalue , &str);
        ret = lcd_4bit_send_string_pos(&lcd1 , 2 , 1 , str);
        ret = lcd_4bit_send_string_pos(&lcd1 , 2 , 4 , " Hz");
        countervalue = 0;   
        /*Disable TIMER0 TO GET THE Frequency every 1sec*/
        TIMER0_Interrupt_Disable();

    } 
    return (EXIT_SUCCESS);
}

void application_intialize(void){
    Std_ReturnType ret = E_NOT_OK;
    ret = lcd_4bit_initialize(&lcd1);
} 