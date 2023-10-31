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

uint16 ADC_RESULT1;
uint16 ADC_RESULT2;
uint16 ADC_RESULT3;
uint16 ADC_RESULT4;

adc_config_t adc1 = {
    .ACD_InterruptHandler = NULL,
    .ADC_channel = ADC_CHANNEL_AN0,
    .Acqusition_time_TAD = ADC_12_TAD,
    .Conversion_clock_FOSC = ADC_CONVERSTION_CLOCK_FOSC_DIV_16,
    .Result_format = ADC_RESULT_RIGHT,
    .Voltage_reference = ADC_DISABLE_VREF
    
};
adc_config_t adc2 = {
    .ACD_InterruptHandler = NULL,
    .ADC_channel = ADC_CHANNEL_AN1,
    .Acqusition_time_TAD = ADC_12_TAD,
    .Conversion_clock_FOSC = ADC_CONVERSTION_CLOCK_FOSC_DIV_16,
    .Result_format = ADC_RESULT_RIGHT,
    .Voltage_reference = ADC_DISABLE_VREF
    
};
adc_config_t adc3 = {
    .ACD_InterruptHandler = NULL,
    .ADC_channel = ADC_CHANNEL_AN2,
    .Acqusition_time_TAD = ADC_12_TAD,
    .Conversion_clock_FOSC = ADC_CONVERSTION_CLOCK_FOSC_DIV_16,
    .Result_format = ADC_RESULT_RIGHT,
    .Voltage_reference = ADC_DISABLE_VREF
    
};
adc_config_t adc4 = {
    .ACD_InterruptHandler = NULL,
    .ADC_channel = ADC_CHANNEL_AN3,
    .Acqusition_time_TAD = ADC_12_TAD,
    .Conversion_clock_FOSC = ADC_CONVERSTION_CLOCK_FOSC_DIV_16,
    .Result_format = ADC_RESULT_RIGHT,
    .Voltage_reference = ADC_DISABLE_VREF
    
};

int main(){
     
    application_intialize();
    
    
    while(1)
    {
        ret = ADC_GetConversion(&adc1 ,ADC_CHANNEL_AN0 , &ADC_RESULT1 );
        ret = ADC_GetConversion(&adc1, ADC_CHANNEL_AN1 , &ADC_RESULT2 );
        ret = ADC_GetConversion(&adc1 ,ADC_CHANNEL_AN2 , &ADC_RESULT3 );
        ret = ADC_GetConversion(&adc1 ,ADC_CHANNEL_AN3 , &ADC_RESULT4 );
    } 
    return (EXIT_SUCCESS);
}

void application_intialize(void){
    Std_ReturnType ret = E_NOT_OK;
    //ecu_layer_intialize();
    ret = ADC_Init(&adc1);

} 