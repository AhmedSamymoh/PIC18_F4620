/* 
 * File:   hal_adc.h
 * Author: AhmedElnozahy
 *
 * Created on October 6, 2023, 9:16 PM
 */

#ifndef HAL_ADC_H
#define	HAL_ADC_H

/*--------------------------- Section: Includes ----------------------------*/
#include <pic18f4620.h>
#include "../std_types.h"
#include "../../MCAL/Interrupt/mcal_internal_interrupt.h"
#include "../../MCAL/GPIO/GPIO.h"
#include "hal_adc_config.h"


/*---------------------- Section: Macro Declarations -----------------------*/


/* Analog-To-Digital Port Configuration Control */
#define ADC_AN0_ANALOG_FUNCTIONALITY            0x0E
#define ADC_AN1_ANALOG_FUNCTIONALITY            0x0D
#define ADC_AN2_ANALOG_FUNCTIONALITY            0x0C
#define ADC_AN3_ANALOG_FUNCTIONALITY            0x0B
#define ADC_AN4_ANALOG_FUNCTIONALITY            0x0A
#define ADC_AN5_ANALOG_FUNCTIONALITY            0x09
#define ADC_AN6_ANALOG_FUNCTIONALITY            0x08
#define ADC_AN7_ANALOG_FUNCTIONALITY            0x07
#define ADC_AN8_ANALOG_FUNCTIONALITY            0x06
#define ADC_AN9_ANALOG_FUNCTIONALITY            0x05
#define ADC_AN10_ANALOG_FUNCTIONALITY           0x04
#define ADC_AN11_ANALOG_FUNCTIONALITY           0x03
#define ADC_AN12_ANALOG_FUNCTIONALITY           0x02

#define ADC_ALL__ANALOG_FUNCTIONALITY           0x00U
#define ADC_ALL__DIGITAL_FUNCTIONALITY          0x0FU

#define ADC_RESULT_RIGHT                        0x01U
#define ADC_RESULT_LEFT                         0x00U

#define ADC_ENABLE_VREF                         0x01U
#define ADC_DISABLE_VREF                        0x00U

/*----------------- Section: Macro Functions Declarations ------------------*/

/* @brief A/D Conversion Status :  In progress (1) - A/D Idle (0)  */
#define ADC_CONVERSION_STATUS()             (ADCON0bits.GO_nDONE )

/* @brief A/D Start The Analog-To-Digital Conversion  */
#define ADC_START_CONVERSION()              (ADCON0bits.GODONE = 1)


/* @brief A/D Converter module : Enable - Disable  */
#define ADC_CONVERSION_ENABLE()             (ADCON0bits.ADON = 1)
#define ADC_CONVERSION_DISABLE()            (ADCON0bits.ADON = 0)


/*
 * @brief   Voltage Reference Configuration:
 * @Note    ADC_ENABLE_VOLTAGE_REFERENCE() : Voltage Reference is VREF- & VREF+
 *          ADC_DISABLE_VOLTAGE_REFERENCE() : Voltage Reference is VSS & VDD
 */
#define ADC_ENABLE_VOLTAGE_REFERENCE()      do{ADCON1bits.VCFG1 = 1;\
                                               ADCON1bits.VCFG0 = 1;\
                                               }while(0)/*MultiLine Function Like Micro*/

#define ADC_DISABLE_VOLTAGE_REFERENCE()      do{ADCON1bits.VCFG1 = 0;\
                                                ADCON1bits.VCFG0 = 0;\
                                               }while(0)/*MultiLine Function Like Micro*/

/*
 * @brief   ADC PORT Configuration Control:
 * @Note    Ex: ADC_ANALOG_DIGITAL_PORT_CONFIG(ADC_AN2_ANALOG_FUNCTIONALITY);
 *              that means  AN2, AN1, AN0 are Analog Functionality
 * @ref     Analog-To-Digital Port Configuration Control
 */
#define ADC_ANALOG_DIGITAL_PORT_CONFIG(_CONFIG)     ( ADCON1bits.PCFG = _CONFIG )

/* @brief   ADC Result Format Select */
#define ADC_RESULT_RIGHT_FORMAT()               ( ADCON2bits.ADFM = 1 )
#define ADC_RESULT_LEFT_FORMAT()                ( ADCON2bits.ADFM = 0 )
                    

/*-------------------- Section: Data Type Declarations -------------------- */

/*  @Brief : Analog Channel Select  */
typedef enum{
    ADC_CHANNEL_AN0 = 0,
    ADC_CHANNEL_AN1,
    ADC_CHANNEL_AN2,
    ADC_CHANNEL_AN3,
    ADC_CHANNEL_AN4,
    ADC_CHANNEL_AN5,
    ADC_CHANNEL_AN6,
    ADC_CHANNEL_AN7,
    ADC_CHANNEL_AN8,
    ADC_CHANNEL_AN9,
    ADC_CHANNEL_AN10,
    ADC_CHANNEL_AN11,
    ADC_CHANNEL_AN12
} adc_channel_select_t;

/*  @Brief : A/D Acquisition Time Selection
 *  @Note  : Acquisition time "Sampling time" is the time required for ADC 
 *           to @Capture the input voltage during sampling rate    
 */
typedef enum{
    ADC_0_TAD = 0,
    ADC_2_TAD,  
    ADC_4_TAD,  
    ADC_6_TAD,  
    ADC_8_TAD,  
    ADC_12_TAD,  
    ADC_16_TAD,  
    ADC_20_TAD
} adc_acqusition_time_t;

/*  @Brief : A/D Conversion Clock Selection  */
typedef enum{
    ADC_CONVERSTION_CLOCK_FOSC_DIV_2 = 0,
    ADC_CONVERSTION_CLOCK_FOSC_DIV_8,
    ADC_CONVERSTION_CLOCK_FOSC_DIV_32,
    ADC_CONVERSTION_CLOCK_FOSC_DIV_FRC,
    ADC_CONVERSTION_CLOCK_FOSC_DIV2_4,
    ADC_CONVERSTION_CLOCK_FOSC_DIV_16,
    ADC_CONVERSTION_CLOCK_FOSC_DIV_64
} adc_conversion_clock_t;


typedef struct{
#if ADC_INTERRUPT_FEATURE_ENABLE == 1
    void (* ACD_InterruptHandler)(void);
    interrupt_priority_config priority;
#endif
    adc_acqusition_time_t    Acqusition_time_TAD;     /* @ref : adc_acqusition_time_t */
    adc_conversion_clock_t   Conversion_clock_FOSC;   /* @ref : adc_conversion_clock_t */ 
    adc_channel_select_t     ADC_channel;             /* @ref : adc_channel_select_t */
    uint8 Voltage_reference  : 1;
    uint8 Result_format      : 1; 
    uint8 ADC_Reserved       : 6; 
}adc_config_t;

/*--------------- Section: Software Interfaces Declarations --------------- */

Std_ReturnType ADC_Init(const adc_config_t *_adc);
Std_ReturnType ADC_DeInit(const adc_config_t *_adc);
Std_ReturnType ADC_SelectChannel(const adc_config_t *_adc , adc_channel_select_t channel);
Std_ReturnType ADC_StartConversion(const adc_config_t *_adc);
Std_ReturnType ADC_IsConversionDone(const adc_config_t *_adc , uint8 *conversion_status);
Std_ReturnType ADC_GetConversionResult(const adc_config_t *_adc , uint16 *conversion_result);

Std_ReturnType ADC_GetConversion_Synchronous(const adc_config_t *_adc , adc_channel_select_t channel ,
                                 uint16 *conversion_result);
Std_ReturnType ADC_StartConversion_Asynchronous(const adc_config_t *_adc , adc_channel_select_t channel );


#endif	/* HAL_ADC_H */

