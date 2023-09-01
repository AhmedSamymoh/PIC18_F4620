/* 
 * File:   application.c
 * Author: AhmedElnozahy
 *
 * Created on August 3, 2023, 4:54 PM
 */
/*
#include "application.h"


PIN_config_t seg1_enable = {
    .port = PORTD_INDEX,
    .pin = GPIO_PIN0,
    .direction = GPIO_DIR_OUTPUT,
    .logic = GPIO_LOW
};

PIN_config_t seg2_enable = {
    .port = PORTD_INDEX,
    .pin = GPIO_PIN1,
    .direction = GPIO_DIR_OUTPUT,
    .logic = GPIO_LOW
};

segment_pin_t seg1 = {
    
    .segments_pins[0].port = PORTC_INDEX,
    .segments_pins[0].pin = GPIO_PIN0,
    .segments_pins[0].logic = GPIO_LOW,
    .segments_pins[0].direction = GPIO_DIR_OUTPUT,
    
    .segments_pins[1].port = PORTC_INDEX,
    .segments_pins[1].pin = GPIO_PIN1,
    .segments_pins[1].logic = GPIO_LOW,
    .segments_pins[1].direction = GPIO_DIR_OUTPUT,
    
 
    .segments_pins[2].port = PORTC_INDEX,
    .segments_pins[2].pin = GPIO_PIN2,
    .segments_pins[2].logic = GPIO_LOW,
    .segments_pins[2].direction = GPIO_DIR_OUTPUT,
    
    .segments_pins[3].port = PORTC_INDEX,
    .segments_pins[3].pin = GPIO_PIN3,
    .segments_pins[3].logic = GPIO_LOW,
    .segments_pins[3].direction = GPIO_DIR_OUTPUT,
    
    .seven_segment_mode = SEGMENT_COMMON_ANODE
};

button_t btn1_active_high = {
  .button_pin.port = PORTB_INDEX,
  .button_pin.pin  = GPIO_PIN0,
  .button_pin.direction = GPIO_DIR_INPUT,
  .button_pin.logic = GPIO_LOW,
  .button_active_t = BUTTON_ACTIVE_HIGH,
  .button_state = BUTTON_RELEASED
};
button_t btn2_active_high = {
  .button_pin.port = PORTB_INDEX,
  .button_pin.pin  = GPIO_PIN1,
  .button_pin.direction = GPIO_DIR_INPUT,
  .button_pin.logic = GPIO_LOW,
  .button_active_t = BUTTON_ACTIVE_HIGH,
  .button_state = BUTTON_RELEASED
};

Led_t led_01 = {.port_name = PORTB_INDEX , .pin = GPIO_PIN3 , .led_status = GPIO_LOW};

relay_t relay_1 = { .relay_port = PORTC_INDEX , .relay_pin = GPIO_PIN0 , .relay_state = RELAY_OFF };

Std_ReturnType ret = E_NOT_OK;


uint8 port_direction;
uint8 port_logic;
uint8 port_logic1;
button_state_t status1 = BUTTON_RELEASED;

button_state_t valid_status1 = BUTTON_RELEASED;
button_state_t last_valid_status1 = BUTTON_RELEASED;

Led_status_t status_led = LED_OFF;

button_state_t valid_status2 = BUTTON_RELEASED;



#define data    PORTC_INDEX
#define mode    PORTD_INDEX


uint8 n = 0 ; 
uint32 counter = 0;


int main(){
    Std_ReturnType ret = E_NOT_OK;
    application_intialize();
    while(1)
    {
        for(counter = 0; counter <= 50 ; counter++){
            ret = seven_segment_write_number(&seg1 , (uint8)(n %10));
            ret = gpio_pin_write_logic(&seg2_enable , GPIO_LOW);
            __delay_ms(10);
            ret = gpio_pin_write_logic(&seg2_enable , GPIO_HIGH);

            ret = seven_segment_write_number(&seg1 , (uint8)(n /10));
            ret = gpio_pin_write_logic(&seg1_enable , GPIO_LOW);
            __delay_ms(10);
            ret = gpio_pin_write_logic(&seg1_enable , GPIO_HIGH);
        }
        n++;
        if(100 == n)
            n=0;
    } 
    return (EXIT_SUCCESS);
}

void application_intialize(void){
    Std_ReturnType ret = E_NOT_OK;

    ret = seven_segment_init(&seg1);
     
    ret = gpio_pin_direction_init(&seg1_enable);
    ret = gpio_pin_direction_init(&seg2_enable);
    
    ret = button_init(&btn1_active_high);
    ret = button_init(&btn2_active_high);

    
}
*/