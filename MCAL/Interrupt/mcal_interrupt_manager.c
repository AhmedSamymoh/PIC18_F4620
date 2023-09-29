/* 
 * File:   mcal_interrupt_manager.h
 * Author: AhmedSamy
 *
 * Created on September 27, 2023, 7:18 AM
 */
#include "mcal_interrupt_manager.h"

#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE

void __interrupt() InterruptMangerHigh(void){
    if((INTERRUPT_ENABLE == INTCONbits.INT0IE) && (INTERRUPT_ENABLE == INTCONbits.INT0IF)){
        INT0_ISR();
    }   
    else{/*Nothing*/}
}
void __interrupt(low_priority) InterruptMangerLow(void){
    if((INTERRUPT_ENABLE == INTCONbits.INT0IE) && (INTERRUPT_ENABLE == INTCONbits.INT0IF)){
        INT0_ISR();
    }   
    else{/*Nothing*/}
}


#else

void __interrupt() InterruptManger(void){
    if((INTERRUPT_ENABLE == INTCONbits.INT0IE) && (INTERRUPT_ENABLE == INTCONbits.INT0IF) ){
        INT0_ISR();
    }   
    if((INTERRUPT_ENABLE == INTCON3bits.INT1IE) && (INTERRUPT_ENABLE == INTCON3bits.INT1IF) ){
        INT1_ISR();
    }   
    if((INTERRUPT_ENABLE == INTCON3bits.INT2IE) && (INTERRUPT_ENABLE == INTCON3bits.INT2IF) ){
        INT2_ISR();
    }   
    else{ /* Nothing */ }
}


#endif