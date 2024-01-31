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

uint16 ADC_RESULT1;
uint16 ADC_RESULT2;
uint16 ADC_RESULT3;
uint16 ADC_RESULT4;

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
    ret = ADC_GetConversionResult(&adc1,&ADC_RESULT1);
        Req =1;
    }
    else if(1 == Req){
        ret = ADC_GetConversionResult(&adc1,&ADC_RESULT2);
        Req=2;
    }else if(2 == Req){
        ret = ADC_GetConversionResult(&adc1,&ADC_RESULT3);
        Req=3;
    }else if(3 == Req){
        ret = ADC_GetConversionResult(&adc1,&ADC_RESULT4);
        Req=0;
    }else{/*Nothing*/}
}
    

uint8 str1[6];
uint8 str2[6];
uint8 str3[6];
uint8 str4[6];


int main(){
     
    application_intialize();

    ret = lcd_4bit_send_string_pos(&lcd1 , 1 , 1 , "Sensor 1:");
    ret = lcd_4bit_send_string_pos(&lcd1 , 2 , 1 , "Sensor 2:");
    ret = lcd_4bit_send_string_pos(&lcd1 , 3 , 1 , "Sensor 3:");
    ret = lcd_4bit_send_string_pos(&lcd1 , 4 , 1 , "Sensor 4:");

    while(1)
    {
        if(0 == Req){
            ret = ADC_StartConversion_Asynchronous(&adc1 ,ADC_CHANNEL_AN0);
        }else if(1 == Req){
            ret = ADC_StartConversion_Asynchronous(&adc1, ADC_CHANNEL_AN1 );
        }else if(2 == Req){
            ret = ADC_StartConversion_Asynchronous(&adc1 ,ADC_CHANNEL_AN2 );
        }else if(3 == Req){
            ret = ADC_StartConversion_Asynchronous(&adc1 ,ADC_CHANNEL_AN3 );
        }else{/*Nothing*/}
                          
        ret = conv_uint16_to_string(ADC_RESULT1 , str1);
        ret = conv_uint16_to_string(ADC_RESULT2 , str2);
        ret = conv_uint16_to_string(ADC_RESULT3 , str3);
        ret = conv_uint16_to_string(ADC_RESULT4 , str4);
        
        ret = lcd_4bit_send_string_pos(&lcd1 , 1 , 10 , str1);
        ret = lcd_4bit_send_string_pos(&lcd1 , 2 , 10 , str2);
        ret = lcd_4bit_send_string_pos(&lcd1 , 3 , 10 , str3);
        ret = lcd_4bit_send_string_pos(&lcd1 , 4 , 10 , str4);
  } 
    return (EXIT_SUCCESS);
}

void application_intialize(void){
    Std_ReturnType ret = E_NOT_OK;

    ret = ADC_Init(&adc1);
    ret = lcd_4bit_initialize(&lcd1);


} 