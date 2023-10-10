/* 
 * File:   mcal_interrupt_manager.h
 * Author: AhmedSamy
 *
 * Created on September 27, 2023, 7:18 AM
 */
#include "mcal_interrupt_manager.h"
#include "../../MCAL/GPIO/GPIO.h"

static volatile uint8 RB4_flag = 1, RB5_flag = 1, RB6_flag = 1, RB7_flag = 1;

#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE

void __interrupt() InterruptMangerHigh(void){
    if((INTERRUPT_ENABLE == INTCONbits.INT0IE) && (INTERRUPT_ENABLE == INTCONbits.INT0IF)){
        INT0_ISR();
    }   
    else{/*Nothing*/}

    if((INTERRUPT_ENABLE == INTCON3bits.INT2IE) && (INTERRUPT_ENABLE == INTCON3bits.INT2IF) ){
        INT2_ISR();
    }else{ /* Nothing */ }
}
void __interrupt(low_priority) InterruptMangerLow(void){
    if((INTERRUPT_ENABLE == INTCON3bits.INT1IE) && (INTERRUPT_ENABLE == INTCON3bits.INT1IF) ){
        INT1_ISR();
    }else{ /* Nothing */ }
}


#else

void __interrupt() InterruptManger(void){
    
/*=============== INTx External Interrupt ===============*/

    if( (INTERRUPT_ENABLE == INTCONbits.INT0IE) && (INTERRUPT_OCCUR == INTCONbits.INT0IF) ){
        INT0_ISR();
    }else{ /* Nothing */ }   
    if( (INTERRUPT_ENABLE == INTCON3bits.INT1IE) && (INTERRUPT_OCCUR == INTCON3bits.INT1IF) ){
        INT1_ISR();
    }else{ /* Nothing */ }   
    if( (INTERRUPT_ENABLE == INTCON3bits.INT2IE) && (INTERRUPT_OCCUR == INTCON3bits.INT2IF) ){
        INT2_ISR();
    }else{ /* Nothing */ }
    
/*=============== RBx On Change Interrupt ===============*/

    
    if( (INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF) &&
        (PORTBbits.RB4 == GPIO_HIGH) && (RB4_flag == 1) ){
        RB4_flag = 0;
        RB4_ISR(HIGH);
    }else if( (INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF) &&
        (PORTBbits.RB4 == GPIO_LOW) && (RB4_flag == 0) ){
        RB4_flag = 1;
        RB4_ISR(LOW);
    }else{ /* Nothing */ }
/*=======================================================*/    
    if( (INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF) &&
        (PORTBbits.RB5 == GPIO_HIGH) && (RB5_flag == 1) ){
        
        RB5_flag = 0;
        RB5_ISR(HIGH);
    }else if( (INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF) &&
        (PORTBbits.RB5 == GPIO_LOW) && (RB5_flag == 0) ){
        
        RB5_flag = 1;
        RB5_ISR(LOW);
    }else{ /* Nothing */ }
/*=======================================================*/
    if( (INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF) &&
        (PORTBbits.RB6 == GPIO_HIGH) && (RB6_flag == 1)  ){
        
        RB6_flag = 0;
        RB6_ISR(HIGH);
    }else if( (INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF) &&
        (PORTBbits.RB6 == GPIO_LOW) && (RB6_flag == 0) ){
        
        RB6_flag = 1;
        RB6_ISR(LOW);
    }else{ /* Nothing */ }
/*=======================================================*/    
    if( (INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF) &&
        (PORTBbits.RB7 == GPIO_HIGH) && (RB7_flag == 1) ){
        
        RB7_flag = 0;
        RB7_ISR(HIGH);
    }else if( (INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF) && 
        (PORTBbits.RB7 == GPIO_LOW) && (RB7_flag == 0)){
        
        RB7_flag = 1;
        RB7_ISR(LOW);
    }else{ /* Nothing */ }
    
/*=======================================================*/

}


#endif