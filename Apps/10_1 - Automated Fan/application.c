/* 
 * File:   application.c
 * Author: AhmedElnozahy
 *
 * Created on August 3, 2023, 4:54 PM
 */
#include "application.h"

void isr_int0();
Std_ReturnType ret = E_NOT_OK;

volatile uint8 adc_flag;

uint16 LM35_RESULT1;
uint16 LM35_RESULT2;
uint16 LM35_Celsuis_RESULT1;
uint16 LM35_Celsuis_RESULT2;


volatile uint8  Req = 0;
void ADC_DefaultInterruptHandler(void);

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

dc_motor_t motor_1 = {
    .dc_motor_PIN[0].port = PORTD_INDEX,
    .dc_motor_PIN[0].pin  = GPIO_PIN0,
    .dc_motor_PIN[0].direction = GPIO_DIR_OUTPUT,
    .dc_motor_PIN[0].logic = GPIO_LOW,
    
    .dc_motor_PIN[1].port = PORTD_INDEX,
    .dc_motor_PIN[1].pin  = GPIO_PIN1,
    .dc_motor_PIN[1].direction = GPIO_DIR_OUTPUT,
    .dc_motor_PIN[1].logic = GPIO_LOW,
 
};
dc_motor_t motor_2 = {
    .dc_motor_PIN[0].port = PORTD_INDEX,
    .dc_motor_PIN[0].pin  = GPIO_PIN2,
    .dc_motor_PIN[0].direction = GPIO_DIR_OUTPUT,
    .dc_motor_PIN[0].logic = GPIO_LOW,
    
    .dc_motor_PIN[1].port = PORTD_INDEX,
    .dc_motor_PIN[1].pin  = GPIO_PIN3,
    .dc_motor_PIN[1].direction = GPIO_DIR_OUTPUT,
    .dc_motor_PIN[1].logic = GPIO_LOW,
 
};

adc_config_t adc1 = {
    .ACD_InterruptHandler = ADC_DefaultInterruptHandler,
    .priority = INTERRUPT_HIGH_PRIORITY,
    .ADC_channel = ADC_CHANNEL_AN0,
    .Acqusition_time_TAD = ADC_12_TAD,
    .Conversion_clock_FOSC = ADC_CONVERSTION_CLOCK_FOSC_DIV_16,
    .Result_format = ADC_RESULT_RIGHT,
    .Voltage_reference = ADC_DISABLE_VREF
    
};

void ADC_DefaultInterruptHandler(void){ 
    
    if(0 == Req){
    ret = ADC_GetConversionResult(&adc1,&LM35_RESULT1);
        Req =1;
    }
    else if(1 == Req){
        ret = ADC_GetConversionResult(&adc1,&LM35_RESULT2);
        Req=0;
    }else{/*Nothing*/}
}
    

uint8 str1[7];
uint8 str2[7];



int main(){
     
    application_intialize();
    ret = lcd_4bit_send_string_pos(&lcd1 , 1 , 4 , "Automated Fan");
    __delay_ms(2000);
    

    ret = lcd_4bit_send_string_pos(&lcd1 , 3 , 1 , "Temperature 1:");
    ret = lcd_4bit_send_string_pos(&lcd1 , 4 , 1 , "Temperature 2:");
    
    while(1)
    {
        if(0 == Req){
            ret = ADC_StartConversion_Asynchronous(&adc1 ,ADC_CHANNEL_AN0);
        }else if(1 == Req){
            ret = ADC_StartConversion_Asynchronous(&adc1, ADC_CHANNEL_AN1 );
        }else{/*Nothing*/}
        
/*****************************************************
 * LM35 - Sensitivity is 10 mV/Degree Celsius
 * step = 5000(mV)/1024(10 bits) = 4.8828125 mV/bit
 * ADC_result = step * Output_ADC_Conversion
 * 1 Celsius - > 10 mV (ADC_result)
 * 25 Celsius - > 250 mV (ADC_result)
 * Temperature = step * ADC_result / 10         
 *****************************************************/
        LM35_Celsuis_RESULT1 = LM35_RESULT1 * 4.8828125 ;
        LM35_Celsuis_RESULT1 /= 10;
        LM35_Celsuis_RESULT2 = LM35_RESULT2 * 4.8828125 ;
        LM35_Celsuis_RESULT2 /= 10;
        
        ret = conv_uint16_to_string(LM35_Celsuis_RESULT1 , str1);
        ret = conv_uint16_to_string(LM35_Celsuis_RESULT2 , str2);
        
        ret = lcd_4bit_send_string_pos(&lcd1 , 3 , 15 , str1);
        ret = lcd_4bit_send_string_pos(&lcd1 , 3 , 18 , "C");
        ret = lcd_4bit_send_string_pos(&lcd1 , 4 , 15 , str2);
        ret = lcd_4bit_send_string_pos(&lcd1 , 4 , 18 , "C");
        
        if(LM35_Celsuis_RESULT1 >= 25){
            dc_motor_Move_Right(&motor_1);
        }else{
            dc_motor_Move_Stop(&motor_1);
        }
        if(LM35_Celsuis_RESULT2 >= 25){
            dc_motor_Move_Right(&motor_2);
        }else{
            dc_motor_Move_Stop(&motor_2);
        }

  } 
    return (EXIT_SUCCESS);
}

void application_intialize(void){
    Std_ReturnType ret = E_NOT_OK;

    ret = ADC_Init(&adc1);
    ret = lcd_4bit_initialize(&lcd1);
    ret = dc_motor_init(&motor_1);
    ret = dc_motor_init(&motor_2);

} 