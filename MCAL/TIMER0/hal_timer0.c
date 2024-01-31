/* 
 * File:   hal_timer0.c
 * Author: AhmedSamy
 *
 * Created on October 29, 2023, 2:06 PM
 */
#include "hal_timer0.h"
#include <pic18f4620.h>

#if TIMER0_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    static void (*TIMER0_InterruptHandler)(void) = NULL ; 
#endif  
 

    
static uint16 timer0_preload = 0;    

/*============================================================================*/
/*====                         Software Interfaces                        ====*/
/*============================================================================*/
    
Std_ReturnType TIMER0_Init(const timer0_t *_timer0){
       
    Std_ReturnType ret = E_OK;
    if(NULL == _timer0){
        ret = E_NOT_OK;
    }else{
        /*Disable TIMER0 Module*/
        TIMER0_DISABLE();
        
        
#if TIMER0_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
        
        TIMER0_Interrupt_Enable();
        TIMER0_Interrupt_Flag_Clear();
        TIMER0_InterruptHandler = _timer0->TMR0_InterruptHandler;
        
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
        INTERRUPT_PriorityLevel_Enable();
        if(INTERRUPT_HIGH_PRIORITY == _timer0->priority){
            INTERRUPT_GlobleaInterrupt_HIGH_Enable();
            TIMER0_High_PrioritySet()
        }else if(INTERRUPT_LOW_PRIORITY == _timer0->priority){
            INTERRUPT_GlobleaInterrupt_LOW_Enable();
            TIMER0_Low_PrioritySet()
        }else{ /*Nothing*/ }
#else 
        INTERRUPT_GlobalInterrupt_Enable();
        INTERRUPT_PeripheralInterrupt_Enable();
#endif

#endif    
       
        
        /*Configure TIMER0 Mode*/
        if( _timer0->timer0_mode == TIMER0_CFG_TIMER_MODE)
        {
            TIMER0_TIMER_MODE();    
        }else if( _timer0->timer0_mode == TIMER0_CFG_COUNTER_MODE){
            TIMER0_COUNTER_MODE();
            /*Configure TIMER0 Source Edge*/
            if( _timer0->timer0_source_edge == TIMER0_CFG_RISING_EDGE)
            {
                TIMER0_RISING_EDGE();    
            }else if( _timer0->timer0_mode == TIMER0_CFG_FALLING_EDGE ){
                TIMER0_FALLING_EDGE();
            }else{ /*Nothing*/ }
            
        }else{ /*Nothing*/ }
        

        /*Configure TIMER0 Prescaler*/
        if( _timer0->timer0_prescaler_enable == TIMER0_CFG_PRESCALER_ENABLE)
        {
            TIMER0_PRESCALER_ENABLE();
            /*Configure TIMER0 Prescaler Value*/ 
            T0CONbits.T0PS0 = (_timer0->timer0_prescaler_value) & 0X01;
            T0CONbits.T0PS1 = (_timer0->timer0_prescaler_value) & 0X02;
            T0CONbits.T0PS2 = (_timer0->timer0_prescaler_value) & 0X04;
            
        }else if( _timer0->timer0_mode == TIMER0_CFG_PRESCALER_DISABLE ){
            TIMER0_PRESCALER_DISABLE(); 
        }else{ /*Nothing*/ }
        
        
        /*Configure TIMER0 Counter Register Size*/
        if( _timer0->timer0_register_size == TIMER0_CFG_8BIT_REGISTER)
        {
            TIMER0_8BIT_REGISTER_MODE();    
        }else if( _timer0->timer0_register_size == TIMER0_CFG_16BIT_REGISTER ){
            TIMER0_16BIT_REGISTER_MODE();
        }else{ /*Nothing*/ }
        
        TMR0H = (_timer0->timer0_PreLoad_value) >> 8;
        TMR0L = (uint8)(_timer0->timer0_PreLoad_value);
        timer0_preload = (_timer0->timer0_PreLoad_value); 
        
        /*Finally Enable TIMER0 Module*/
        TIMER0_ENABLE();
 
        ret = E_OK;
    }
    return ret;

    
    
}

Std_ReturnType TIMER0_DeInit(const timer0_t *_timer0){
    
    Std_ReturnType ret = E_OK;
    if(NULL == _timer0){
        ret = E_NOT_OK;
    }else{
        
#if TIMER0_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
        TIMER0_Interrupt_Disable();
        TIMER0_Interrupt_Flag_Clear();        
#endif   
        
        /*Disable TIMER0 Module*/
        TIMER0_DISABLE();
        
        ret = E_OK;
    }
    return ret;
    
}
Std_ReturnType TIMER0_READ(const timer0_t *_timer0 , uint16 *value){
    uint8 TMR0_L = 0  , TMR0_H = 0;
    Std_ReturnType ret = E_OK;
    if(NULL == _timer0){
        ret = E_NOT_OK;
    }else{
        TMR0_L = TMR0L ;
        TMR0_H = TMR0H ;
        *value = (uint16)(((TMR0_H) << 8) + TMR0_L );
        ret = E_OK;
    }
    return ret;
}

Std_ReturnType TIMER0_WRITE(const timer0_t *_timer0 , uint16  value){
    
    Std_ReturnType ret = E_OK;
    if(NULL == _timer0){
        ret = E_NOT_OK;
    }else{
        TMR0H = (value) >> 8;
        TMR0L = (uint8)(value);
        ret = E_OK;
    }
    return ret;
}

void TMR0_ISR(void){
    TIMER0_Interrupt_Flag_Clear();
    
    /*To reload the register every OVF*/
    TMR0H = (timer0_preload) >> 8;
    TMR0L = (uint8)(timer0_preload);

    if(TIMER0_InterruptHandler)
        TIMER0_InterruptHandler();
}
