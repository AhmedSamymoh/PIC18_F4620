/* 
 * File:   application.c
 * Author: AhmedElnozahy
 *
 * Created on August 3, 2023, 4:54 PM
 */
#include "application.h"


Led_t led_01 = {.port_name = PORTC_INDEX , .pin = GPIO_PIN0 , .led_status = GPIO_LOW};
Led_t led_02 = {.port_name = PORTC_INDEX , .pin = GPIO_PIN1 , .led_status = GPIO_LOW};
Led_t led_03 = {.port_name = PORTC_INDEX , .pin = GPIO_PIN2 , .led_status = GPIO_LOW};
Led_t led_04 = {.port_name = PORTC_INDEX , .pin = GPIO_PIN3  , .led_status = GPIO_LOW};

Led_t led_05 = {.port_name = PORTC_INDEX , .pin = GPIO_PIN4  , .led_status = GPIO_LOW};
Led_t led_06 = {.port_name = PORTC_INDEX , .pin = GPIO_PIN5  , .led_status = GPIO_LOW};
Led_t led_07 = {.port_name = PORTC_INDEX , .pin = GPIO_PIN6  , .led_status = GPIO_LOW};
Led_t led_08 = {.port_name = PORTC_INDEX , .pin = GPIO_PIN7  , .led_status = GPIO_LOW};

button_t btn1_active_high = {
  .button_pin.port = PORTC_INDEX,
  .button_pin.pin  = GPIO_PIN3,
  .button_pin.direction = GPIO_DIR_INPUT,
  .button_pin.logic = GPIO_LOW,
  .button_active_t = BUTTON_ACTIVE_HIGH,
  .button_state = BUTTON_RELEASED
};
        
button_t btn1_active_low = {
  .button_pin.port = PORTD_INDEX,
  .button_pin.pin  = GPIO_PIN0,
  .button_pin.direction = GPIO_DIR_INPUT,
  .button_pin.logic = GPIO_LOW,
  .button_active_t = BUTTON_ACTIVE_HIGH,
  .button_state = BUTTON_RELEASED
};

PIN_config_t BUTTON2 = {
    .port = PORTB_INDEX,
    .pin = GPIO_PIN2,
    .direction = GPIO_DIR_INPUT,
    .logic = GPIO_LOW
};

Std_ReturnType ret = E_NOT_OK;
Logic_t status1;
Logic_t status2; 

uint8 port_direction;
uint8 port_logic;
uint8 port_logic1;

int main(){
    application_intialize();
    while(1)
    {
        ret = button_read();
        ret = led_TURN_ON( &led_01 );
        ret = led_TURN_ON( &led_02 );
        ret = led_TURN_ON( &led_03 );
        ret = led_TURN_ON( &led_04 );
        __delay_ms(1000);
        ret = led_TURN_OFF( &led_01 );
        ret = led_TURN_OFF( &led_02 );
        ret = led_TURN_OFF( &led_03 );
        ret = led_TURN_OFF( &led_04 );
        ret = led_TOG( &led_05 );
        ret = led_TOG( &led_06 );
        ret = led_TOG( &led_07 );
        ret = led_TOG( &led_08 );
        __delay_ms(1000);

    }
    return (EXIT_SUCCESS);
}

void application_intialize(void){
    Std_ReturnType ret = E_NOT_OK;
    
    ret = button_init(&btn1_active_high);
    ret = button_init(&btn1_active_low);
    
    ret = led_init( &led_01 );
    ret = led_init( &led_02 );
    ret = led_init( &led_03 );
    ret = led_init( &led_04 );

    ret = led_init( &led_05 );
    ret = led_init( &led_06 );
    ret = led_init( &led_07 );
    ret = led_init( &led_08 );
}