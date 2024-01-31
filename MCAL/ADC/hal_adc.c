/* 
 *@File:   hal_adc.h
 *@Author: AhmedElnozahy
 *
 *@Created on October 6, 2023, 9:16 PM
 */

#include "hal_adc.h"

#if ADC_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
static void (*ADC_InterruptHandler)(void) = NULL ;  
#endif


/*=========================================================================================*/
/*====                                Helper Functions                                 ====*/
/*=========================================================================================*/
static inline void adc_input_channel_port_Configuration(const adc_channel_select_t channel );
static inline void Select_result_format(const adc_config_t *_adc);
static inline void Configurate_voltage_Reference(const adc_config_t *_adc );


/*=========================================================================================*/
/*====                               Software Interfaces                               ====*/
/*=========================================================================================*/


/*******************************************************************************
 * @Summary Initializes the ADC
 * 
 * @param _adc a Pointer to ADC configuration @adc_config_t
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 ******************************************************************************/
Std_ReturnType ADC_Init(const adc_config_t *_adc){
    Std_ReturnType ret = E_OK;
    if(NULL == _adc){
        ret = E_NOT_OK;
    }else{
        /*Disable the ADC*/
        ADC_CONVERSION_DISABLE();
        /*Configure the conversion Clock (F_osc)*/
        ADCON2bits.ADCS = _adc->Conversion_clock_FOSC;
        /*Configure the Acquisition time (T_AD)*/
        ADCON2bits.ACQT = _adc->Acqusition_time_TAD;
        /*Configure the Default channel */
        ADCON0bits.CHS = _adc->ADC_channel;
        adc_input_channel_port_Configuration(_adc->ADC_channel);
        
        /*Configure the Interrupt */
#if ADC_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
        
        ADC_Interrupt_Enable();
        ADC_Interrupt_Flag_Clear();
        ADC_InterruptHandler = _adc->ACD_InterruptHandler;
        
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
        if(INTERRUPT_HIGH_PRIORITY == _adc->priority){ADC_High_PrioritySet();}
        else if(INTERRUPT_LOW_PRIORITY == _adc->priority){ADC_Low_PrioritySet();}
        else{/*Nothing*/}
#else
        INTERRUPT_GlobalInterrupt_Enable();
        INTERRUPT_PeripheralInterrupt_Enable();
#endif
        
#endif
        ADC_InterruptHandler = _adc->ACD_InterruptHandler;
        /*Configure the Result format */
        Select_result_format(_adc);
        
        /*Configure the voltage reference */
        Configurate_voltage_Reference(_adc);
        
        /*Enable the ADC*/
        ADC_CONVERSION_ENABLE();
        
        ret = E_OK;
    }
    return ret;
}

/*******************************************************************************
 * @Summary De-Initializes the ADC
 * @param _adc a Pointer to ADC configuration @adc_config_t
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 ******************************************************************************/
Std_ReturnType ADC_DeInit(const adc_config_t *_adc){
        Std_ReturnType ret = E_OK;
    if(NULL == _adc){
        ret = E_NOT_OK;
    }else{
        /*Disable the ADC*/
        ADC_CONVERSION_DISABLE();
        /*Disable the Interrupt Configuration */
#if ADC_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
        ADC_Interrupt_Disable();
#endif
         
        ret = E_OK;
    }
    return ret;
    
}

/*******************************************************************************
 * @Summary Selecting the ADC Channel for Conversion 
 * @preconditions ADC_Init 
 * @param _adc a Pointer to ADC configuration        @adc_config_t
 * @param channel Define the Channel for conversion  @adc_channel_select_t
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 ******************************************************************************/
Std_ReturnType ADC_SelectChannel(const adc_config_t *_adc , adc_channel_select_t channel){
    Std_ReturnType ret = E_OK;
    if(NULL == _adc){
        ret = E_NOT_OK;
    }else{
        /*Select A/D Channel */
        ADCON0bits.CHS = channel;
        adc_input_channel_port_Configuration(channel);
        
        
        ret = E_OK;
    }
    return ret;
}


/*******************************************************************************
 * @Summary Starts the ADC Conversion 
 * @preconditions ADC_Init 
 * @param _adc a Pointer to ADC configuration        @adc_config_t
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 ******************************************************************************/
Std_ReturnType ADC_StartConversion(const adc_config_t *_adc){
    Std_ReturnType ret = E_OK;
    if(NULL == _adc){
        ret = E_NOT_OK;
    }else{
        
        ADC_START_CONVERSION();
        ret = E_OK;
    }
    return ret;
}

/*******************************************************************************
 * @Summary Return the State of the ADC Conversion 
 * @preconditions ADC_Init 
 * @param _adc a Pointer to ADC configuration        @adc_config_t
 * @param conversion_status 
 *           - true  : If Conversion is Done
 *           - false : If Conversion is not Completed yet
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 ******************************************************************************/
Std_ReturnType ADC_IsConversionDone(const adc_config_t *_adc , uint8 *conversion_status){
    Std_ReturnType ret = E_OK;
    if(NULL == _adc){
        ret = E_NOT_OK;
    }else{
        /*GO.nDONE Bit Status*/
        *conversion_status = (uint8)(!ADC_CONVERSION_STATUS());
    
        ret = E_OK;
    }
    return ret;
}

/*******************************************************************************
 * @Summary Return the ADC Conversion Result
 * @preconditions ADC_Init 
 * @param _adc a Pointer to ADC configuration        @adc_config_t
 * @param conversion_result
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 ******************************************************************************/
Std_ReturnType ADC_GetConversionResult(const adc_config_t *_adc , uint16 *conversion_result){
    Std_ReturnType ret = E_OK;
    if(NULL == _adc){
        ret = E_NOT_OK;
    }else{
        switch(_adc->Result_format){
            case ADC_RESULT_RIGHT: 
                *conversion_result = (uint16)((ADRESH<<8) + ADRESL );
                break;
            case ADC_RESULT_LEFT: 
                *conversion_result = (uint16)((ADRESH<<8) + (ADRESL<<6));
                break;
            default:
                *conversion_result = (uint16)((ADRESH<<8) + ADRESL );
                break;
        }
        
                
        ret = E_OK;
    }
    return ret;
}

/*******************************************************************************
 * @Summary Return the ADC Conversion Result and Allows Selection of ADC Channel
 * @preconditions ADC_Init 
 * @param _adc a Pointer to ADC configuration        @adc_config_t
 * @param channel Define the Channel for conversion  @adc_channel_select_t
 * @param conversion_result 
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 ******************************************************************************/
Std_ReturnType ADC_GetConversion_Synchronous(const adc_config_t *_adc , adc_channel_select_t channel ,uint16 *conversion_result){
    Std_ReturnType ret = E_OK;
    static uint8 l_status = 0;
    if(NULL == _adc){
        ret = E_NOT_OK;
    }else{
        /*Select A/D Channel */
        ret = ADC_SelectChannel(_adc , channel);
        /*Start CONVERSTION */ 
        ret = ADC_StartConversion(_adc);
      
        /*Polling til the Conversion is Done*/
        while(!ADCON0bits.GO_nDONE );
        
        /*Return the ADC Conversion Result*/
        ret = ADC_GetConversionResult(_adc,conversion_result);
        
        ret = E_OK;
    }
    return ret;
    
}

/*******************************************************************************
 * @Summary Return the ADC Conversion Result and Allows Selection of ADC Channel
 * @preconditions ADC_Init 
 * @param _adc a Pointer to ADC configuration        @adc_config_t
 * @param channel Define the Channel for conversion  @adc_channel_select_t
 * @param conversion_result 
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 ******************************************************************************/
Std_ReturnType ADC_StartConversion_Asynchronous(const adc_config_t *_adc , adc_channel_select_t channel ){
    Std_ReturnType ret = E_OK;
    static uint8 l_status = 0;
    if(NULL == _adc){
        ret = E_NOT_OK;
    }else{
        /*Select A/D Channel */
        ret = ADC_SelectChannel(_adc , channel);
        /*Start CONVERSTION */ 
        ret = ADC_StartConversion(_adc);
//        //
//        /*Return the ADC Conversion Result*/
//        ret = ADC_GetConversionResult(_adc,conversion_result);
//        
        ret = E_OK;
    }
    return ret;
    
}


/*=========================================================================================*/
/*====                                Helper Functions                                 ====*/
/*=========================================================================================*/
static inline void adc_input_channel_port_Configuration(const adc_channel_select_t channel ){
    switch (channel){
        /*Disable the Digital Output Driver*/
        case ADC_CHANNEL_AN0 :
            SET_BIT(TRISA , GPIO_PIN0); break;
        case ADC_CHANNEL_AN1 :
            SET_BIT(TRISA, GPIO_PIN1); break;
        case ADC_CHANNEL_AN2 :
            SET_BIT(TRISA ,GPIO_PIN2); break;            
        case ADC_CHANNEL_AN3 :
            SET_BIT(TRISA , GPIO_PIN3); break;
        case ADC_CHANNEL_AN4 :
            SET_BIT(TRISA , GPIO_PIN4); break;
            
        case ADC_CHANNEL_AN5 :
            SET_BIT(TRISE , GPIO_PIN0); break;            
        case ADC_CHANNEL_AN6 :
            SET_BIT(TRISE , GPIO_PIN1); break;            
        case ADC_CHANNEL_AN7 :
            SET_BIT(TRISE , GPIO_PIN2); break;    
            
        case ADC_CHANNEL_AN8 :
            SET_BIT(TRISB , GPIO_PIN2); break;            
        case ADC_CHANNEL_AN9 :
            SET_BIT(TRISB , GPIO_PIN3); break;            
        case ADC_CHANNEL_AN10 :
            SET_BIT(TRISB , GPIO_PIN1); break;            
        case ADC_CHANNEL_AN11 :
            SET_BIT(TRISB , GPIO_PIN4); break;            
        case ADC_CHANNEL_AN12:
            SET_BIT(TRISB , GPIO_PIN0); break;            
    }
}

static inline void Select_result_format(const adc_config_t *_adc ){
        if(ADC_RESULT_RIGHT == (_adc->Result_format)) 
            ADC_RESULT_RIGHT_FORMAT();
        else if(ADC_RESULT_LEFT == (_adc->Result_format))
            ADC_RESULT_LEFT_FORMAT();
        else
            ADC_RESULT_RIGHT_FORMAT(); /*Default*/
}

static inline void Configurate_voltage_Reference(const adc_config_t *_adc ){
        if(ADC_ENABLE_VREF == (_adc->Voltage_reference)) 
            ADC_ENABLE_VOLTAGE_REFERENCE();
        else if(ADC_DISABLE_VREF == (_adc->Voltage_reference))
            ADC_DISABLE_VOLTAGE_REFERENCE();
        else
            ADC_DISABLE_VOLTAGE_REFERENCE(); /*Default*/
}
void ADC_ISR(void){
    ADC_Interrupt_Flag_Clear();
    if(ADC_InterruptHandler)
        ADC_InterruptHandler();
}
