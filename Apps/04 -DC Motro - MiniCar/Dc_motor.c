/* 
 * File:   application.c
 * Author: AhmedElnozahy
 *
 * Created on August 3, 2023, 4:54 PM
 */
/*#include "application.h"

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
button_t btn3_active_high = {
  .button_pin.port = PORTB_INDEX,
  .button_pin.pin  = GPIO_PIN2,
  .button_pin.direction = GPIO_DIR_INPUT,
  .button_pin.logic = GPIO_LOW,
  .button_active_t = BUTTON_ACTIVE_HIGH,
  .button_state = BUTTON_RELEASED
};
button_t btn4_active_high = {
  .button_pin.port = PORTB_INDEX,
  .button_pin.pin  = GPIO_PIN3,
  .button_pin.direction = GPIO_DIR_INPUT,
  .button_pin.logic = GPIO_LOW,
  .button_active_t = BUTTON_ACTIVE_HIGH,
  .button_state = BUTTON_RELEASED
};
        
Led_t led_01 = {.port_name = PORTB_INDEX , .pin = GPIO_PIN3 , .led_status = GPIO_LOW};
Led_t led_02 = {.port_name = PORTB_INDEX , .pin = GPIO_PIN4 , .led_status = GPIO_LOW};

relay_t relay_1 = { .relay_port = PORTC_INDEX , .relay_pin = GPIO_PIN0 , .relay_state = RELAY_OFF };
relay_t relay_2 = { .relay_port = PORTC_INDEX , .relay_pin = GPIO_PIN1 , .relay_state = RELAY_OFF };

dc_motor_t Dc_motor_1 = {
  .dc_motor_PIN[0].port = PORTC_INDEX,
  .dc_motor_PIN[0].pin = GPIO_PIN0,
  .dc_motor_PIN[0].logic = DC_MOTOR_OFF,
  .dc_motor_PIN[0].direction = GPIO_DIR_OUTPUT,
  
  .dc_motor_PIN[1].port = PORTC_INDEX,
  .dc_motor_PIN[1].pin = GPIO_PIN1,
  .dc_motor_PIN[1].logic = DC_MOTOR_OFF,
  .dc_motor_PIN[1].direction = GPIO_DIR_OUTPUT,
};

dc_motor_t Dc_motor_2 = {
  .dc_motor_PIN[0].port = PORTC_INDEX,
  .dc_motor_PIN[0].pin = GPIO_PIN2,
  .dc_motor_PIN[0].logic = DC_MOTOR_OFF,
  .dc_motor_PIN[0].direction = GPIO_DIR_OUTPUT,
  
  .dc_motor_PIN[1].port = PORTC_INDEX,
  .dc_motor_PIN[1].pin = GPIO_PIN3,
  .dc_motor_PIN[1].logic = DC_MOTOR_OFF,
  .dc_motor_PIN[1].direction = GPIO_DIR_OUTPUT,
};


Std_ReturnType ret = E_NOT_OK;


uint8 port_direction;
uint8 port_logic;
uint8 port_logic1;
button_state_t status1 = BUTTON_RELEASED;
button_state_t status2 = BUTTON_RELEASED;
button_state_t status3 = BUTTON_RELEASED;
button_state_t status4 = BUTTON_RELEASED;

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
        ret = button_read(&btn1_active_high , &status1);
        ret = button_read(&btn2_active_high , &status2);
        ret = button_read(&btn3_active_high , &status3);
        ret = button_read(&btn4_active_high , &status4);
        
        if( BUTTON_PRESSED == status1 )
        {
            ret = dc_motor_Move_Right(& Dc_motor_1);
            ret = dc_motor_Move_Right(& Dc_motor_2);
            ret = led_TURN_ON(&led_01);
        }else if( BUTTON_PRESSED == status2 ){
            ret = dc_motor_Move_Left(& Dc_motor_1);
            ret = dc_motor_Move_Left(& Dc_motor_2);
            ret = led_TURN_ON(&led_02);

        }else if( BUTTON_PRESSED == status3 ){
            ret = dc_motor_Move_Stop(&Dc_motor_1);
            ret = dc_motor_Move_Stop(&Dc_motor_2);
            ret = led_TURN_ON(&led_01);
            ret = led_TURN_ON(&led_02);

        }else{
            ret = led_TURN_OFF(&led_01);
            ret = led_TURN_OFF(&led_02);
        }
        

    }
    return (EXIT_SUCCESS);
}

void application_intialize(void){
    Std_ReturnType ret = E_NOT_OK;
    
    ret = relay_init(&relay_1); 
    ret = relay_init(&relay_2); 
    
    ret = dc_motor_init(& Dc_motor_1);
    ret = dc_motor_init(& Dc_motor_2);
    
    ret = button_init(&btn1_active_high);
    ret = button_init(&btn2_active_high);
    ret = button_init(&btn3_active_high);
    ret = button_init(&btn4_active_high);
    ret = led_init( &led_01 );
    ret = led_init( &led_02 );

}*/