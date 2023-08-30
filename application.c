/* 
 * File:   application.c
 * Author: AhmedElnozahy
 *
 * Created on August 3, 2023, 4:54 PM
 */
#include "application.h"

//
//Led_t led_01 = {.port_name = PORTC_INDEX , .pin = GPIO_PIN0 , .led_status = GPIO_LOW};
//Led_t led_02 = {.port_name = PORTC_INDEX , .pin = GPIO_PIN1 , .led_status = GPIO_LOW};
//Led_t led_03 = {.port_name = PORTC_INDEX , .pin = GPIO_PIN2 , .led_status = GPIO_LOW};
//Led_t led_04 = {.port_name = PORTC_INDEX , .pin = GPIO_PIN3  , .led_status = GPIO_LOW};
//
//Led_t led_05 = {.port_name = PORTC_INDEX , .pin = GPIO_PIN4  , .led_status = GPIO_LOW};
//Led_t led_06 = {.port_name = PORTC_INDEX , .pin = GPIO_PIN5  , .led_status = GPIO_LOW};
//Led_t led_07 = {.port_name = PORTC_INDEX , .pin = GPIO_PIN6  , .led_status = GPIO_LOW};
//Led_t led_08 = {.port_name = PORTC_INDEX , .pin = GPIO_PIN7  , .led_status = GPIO_LOW};
//
//button_t btn1_active_high = {
//  .button_pin.port = PORTB_INDEX,
//  .button_pin.pin  = GPIO_PIN2,
//  .button_pin.direction = GPIO_DIR_INPUT,
//  .button_pin.logic = GPIO_LOW,
//  .button_active_t = BUTTON_ACTIVE_HIGH,
//  .button_state = BUTTON_RELEASED
//};
//        

relay_t relay_1 = { .relay_port = PORTC_INDEX , .relay_pin = GPIO_PIN0 , .relay_state = RELAY_OFF };
relay_t relay_2 = { .relay_port = PORTC_INDEX , .relay_pin = GPIO_PIN1 , .relay_state = RELAY_OFF };
dc_motor_t Dc_motor_1 = {
  .dc_motor[0].dc_motor_port = PORTC_INDEX,
  .dc_motor[0].dc_motor_pin = GPIO_PIN0,
  .dc_motor[0].dc_motor_status = DC_MOTOR_OFF,
  
  .dc_motor[1].dc_motor_port = PORTC_INDEX,
  .dc_motor[1].dc_motor_pin = GPIO_PIN1,
  .dc_motor[1].dc_motor_status = DC_MOTOR_OFF,
};

dc_motor_t Dc_motor_2 = {
  .dc_motor[0].dc_motor_port = PORTC_INDEX,
  .dc_motor[0].dc_motor_pin = GPIO_PIN2,
  .dc_motor[0].dc_motor_status = DC_MOTOR_OFF,
  
  .dc_motor[1].dc_motor_port = PORTC_INDEX,
  .dc_motor[1].dc_motor_pin = GPIO_PIN3,
  .dc_motor[1].dc_motor_status = DC_MOTOR_OFF,
};


Std_ReturnType ret = E_NOT_OK;


uint8 port_direction;
uint8 port_logic;
uint8 port_logic1;
button_state_t status1 = BUTTON_RELEASED;
button_state_t status2 = BUTTON_RELEASED;
button_state_t valid_status1 = BUTTON_RELEASED;
button_state_t last_valid_status1 = BUTTON_RELEASED;

Led_status_t status_led = LED_OFF;

button_state_t valid_status2 = BUTTON_RELEASED;
uint32 btn_High_valid = 0;
uint32 counter = 0;


int main(){
     Std_ReturnType ret = E_NOT_OK;
    application_intialize();
    while(1)
    {
        ret = dc_motor_Move_Right(& Dc_motor_1);
        ret = dc_motor_Move_Left(& Dc_motor_2);
        __delay_ms(1000);
        ret = dc_motor_Move_Left(& Dc_motor_1);
        ret = dc_motor_Move_Right(& Dc_motor_2);
        __delay_ms(1000);
        ret = dc_motor_Move_Stop(&Dc_motor_1);
        ret = dc_motor_Move_Stop(&Dc_motor_2);
        __delay_ms(1000);


    }
    return (EXIT_SUCCESS);
}

void application_intialize(void){
    Std_ReturnType ret = E_NOT_OK;
    
    ret = relay_init(&relay_1); 
    ret = relay_init(&relay_2); 
    
    ret = dc_motor_init(& Dc_motor_1);
    ret = dc_motor_init(& Dc_motor_2);
    
//    ret = button_init(&btn1_active_high);
//    ret = button_init(&btn1_active_low);
//    
//    ret = led_init( &led_01 );
//    ret = led_init( &led_02 );
//    ret = led_init( &led_03 );
//    ret = led_init( &led_04 );
//
//    ret = led_init( &led_05 );
//    ret = led_init( &led_06 );
//    ret = led_init( &led_07 );
//    ret = led_init( &led_08 );
}