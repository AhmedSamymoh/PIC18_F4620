 
  File   application.c
  Author AhmedElnozahy
 
  Created on August 3, 2023, 454 PM
 

/*#include application.h


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

 
 
uint8 seconds = 45;
uint8 minutes = 12;
uint8 hours = 23;

#define data    PORTC_INDEX
#define mode    PORTD_INDEX

void clock(){
    for(uint8 c = 0 ; c  60 ; c++)  60 ( 6   3333 ) = 1 sec
        {
            ret = gpio_port_write_logic(mode , 0b11011111);
            ret = gpio_port_write_logic(data  , (uint8)(seconds % 10));
            __delay_us(3333);
            ret = gpio_port_write_logic(mode , 0b11101111);
            ret = gpio_port_write_logic(data  , (uint8)(seconds  10));
            __delay_us(3333);

            ret = gpio_port_write_logic(mode , 0b11110111);   
            ret = gpio_port_write_logic(data  , (uint8)(minutes % 10) );
            __delay_us(3333);
            ret = gpio_port_write_logic(mode , 0b11111011);
            ret = gpio_port_write_logic(data  , (uint8)(minutes  10));
            __delay_us(3333);

            ret = gpio_port_write_logic(mode , 0b11111101);
            ret = gpio_port_write_logic(data  , (uint8)(hours % 10));
            __delay_us(3333);
            ret = gpio_port_write_logic(mode , 0b11111110); 0b0011 1111
            ret = gpio_port_write_logic(data  , (uint8)(hours  10));
            __delay_us(3333);
        }
        seconds++;
        
        if(60 == seconds){
            seconds = 0;
            minutes++;
        }
        
        if(60 == minutes){
            seconds = 0;
            hours++;
        }
        if(24 == hours){
            hours = 0;
        }
}
 
int main(){
    Std_ReturnType ret = E_NOT_OK;
    application_intialize();
    while(1)
    {
        clock();
    } 
    return (EXIT_SUCCESS);
}

void application_intialize(void){
    Std_ReturnType ret = E_NOT_OK;
    
    ret = gpio_port_direction_init(PORTC_INDEX , 0x00);  
    ret = gpio_port_direction_init(PORTD_INDEX , 0x00);  
    
    ret = button_init(&btn1_active_high);
    ret = button_init(&btn2_active_high);
    ret = button_init(&btn3_active_high);
    ret = button_init(&btn4_active_high);
    
}
*/