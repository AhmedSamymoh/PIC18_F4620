/* 
 * File:   application.c
 * Author: AhmedElnozahy
 *
 * Created on August 3, 2023, 4:54 PM
 */
/*#include "application.h"


Led_t led_01 = {.port_name = PORTC_INDEX , .pin = GPIO_PIN0 , .led_status = GPIO_LOW};
Led_t led_02 = {.port_name = PORTC_INDEX , .pin = GPIO_PIN1 , .led_status = GPIO_LOW};
Led_t led_03 = {.port_name = PORTC_INDEX , .pin = GPIO_PIN2 , .led_status = GPIO_LOW};
Led_t led_04 = {.port_name = PORTC_INDEX , .pin = GPIO_PIN3  , .led_status = GPIO_LOW};

Led_t led_05 = {.port_name = PORTC_INDEX , .pin = GPIO_PIN4  , .led_status = GPIO_LOW};
Led_t led_06 = {.port_name = PORTC_INDEX , .pin = GPIO_PIN5  , .led_status = GPIO_LOW};
Led_t led_07 = {.port_name = PORTC_INDEX , .pin = GPIO_PIN6  , .led_status = GPIO_LOW};
Led_t led_08 = {.port_name = PORTC_INDEX , .pin = GPIO_PIN7  , .led_status = GPIO_LOW};

button_t btn1_active_high = {
  .button_pin.port = PORTB_INDEX,
  .button_pin.pin  = GPIO_PIN2,
  .button_pin.direction = GPIO_DIR_INPUT,
  .button_pin.logic = GPIO_LOW,
  .button_active_t = BUTTON_ACTIVE_HIGH,
  .button_state = BUTTON_RELEASED
};
        
button_t btn1_active_low = {
  .button_pin.port = PORTB_INDEX,
  .button_pin.pin  = GPIO_PIN1,
  .button_pin.direction = GPIO_DIR_INPUT,
  .button_pin.logic = GPIO_LOW,
  .button_active_t = BUTTON_ACTIVE_LOW,
  .button_state = BUTTON_RELEASED
};

PIN_config_t BUTTON2 = {
    .port = PORTB_INDEX,
    .pin = GPIO_PIN2,
    .direction = GPIO_DIR_INPUT,
    .logic = GPIO_LOW
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

void porgram_1()
{
    uint8 c = 0;
    for(c = 0 ; c < 2 ; c++ ){
        __delay_ms(1000);
        led_TURN_ON(&led_01);
        __delay_ms(1000);
        led_TURN_OFF(&led_01);
    }
}
void porgram_2()
{
    uint8 c = 0;
    for(c = 0 ; c < 3 ; c++ ){
        __delay_ms(500);
        led_TURN_ON(&led_02);
        __delay_ms(500);
        led_TURN_OFF(&led_02);
    }
}
void porgram_3()
{
    uint8 c = 0;
    for(c = 0 ; c < 6 ; c++ ){
        __delay_ms(500);
        led_TURN_ON(&led_03);
        __delay_ms(500);
        led_TURN_OFF(&led_03);
    }
}

int main(){
    application_intialize();
    while(1)
    {
        ret = button_read( &btn1_active_high , &status1 );
        ret = button_read( &btn1_active_low , &status2 );
        ret = gpio_pin_read_logic( &led_01, &status_led );
        
        //De-bouncing state (Should done using timers)
        /*if(status1 == BUTTON_PRESSED)
        {
            btn_High_valid++;
            if( btn_High_valid > 100){
                valid_status1 = BUTTON_PRESSED;                
            }
        }
        else{
            btn_High_valid = 0;
            valid_status1 = BUTTON_RELEASED;                
        }*/
        
//        if (valid_status1 != last_valid_status1)
//        {
//            last_valid_status1 = valid_status1;
/*
        if (BUTTON_PRESSED == status1 )
        {
                counter++;
                switch(counter)
                {
                    case 1: porgram_1(); break;
                    case 2: porgram_2(); break;
                    case 3: porgram_3(); break;
                    default:
                        counter = 0;
                        break;
                }

            
        }
        
       
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
*/