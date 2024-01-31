/* 
 * File:   mcal_internal_interrupt.h
 * Author: AhmedSamy
 *
 * Created on September 27, 2023, 7:16 AM
 */

#ifndef MCAL_INTERNAL_INTERRUPT_H
#define	MCAL_INTERNAL_INTERRUPT_H

/* ------------- Section : Includes ------------- */
#include "mcal_interrupt_config.h"
#include "mcal_exernal_interrupt.h"

/* ------------- Section: Macro Declarations ------------- */

/*===================================================================*/
#if ADC_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
/*===================================================================*/

/*A macro will @Disable Interrupt For ADC Module */
#define ADC_Interrupt_Disable()                    (PIE1bits.ADIE = 0)
/*A macro will @Enable Interrupt For ADC Module */
#define ADC_Interrupt_Enable()                     (PIE1bits.ADIE = 1)
/*A macro will @Clear Flag ADC Interrupt */
#define ADC_Interrupt_Flag_Clear()                 (PIR1bits.ADIF = 0)


#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE

/*A macro will @Set ADC Module Interrupt to be @HIGH Priority    */
#define ADC_High_PrioritySet()                     (IPR1bits.ADIP = 1)
/*A macro will @Set ADC Module Interrupt to be @LOW Priority    */
#define ADC_Low_PrioritySet()                      (IPR1bits.ADIP = 0)
#endif 

#endif 


/*===================================================================*/
#if TIMER0_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
/*===================================================================*/

/*A macro will @Disable Interrupt For TIMER0_Module */
#define TIMER0_Interrupt_Disable()                    (INTCONbits.TMR0IE = 0)
/*A macro will @Enable Interrupt For TIMER0_Module */
#define TIMER0_Interrupt_Enable()                     (INTCONbits.TMR0IE = 1)
/*A macro will @Clear Flag TIMER0_Interrupt */
#define TIMER0_Interrupt_Flag_Clear()                 (INTCONbits.TMR0IF = 0)


#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE

/*A macro will @Set TIMER0_Module Interrupt to be @HIGH Priority    */
#define TIMER0_High_PrioritySet()                     (INTCON2bits.TMR0IP = 1)
/*A macro will @Set TIMER0_Module Interrupt to be @LOW Priority    */
#define TIMER0_Low_PrioritySet()                      (INTCON2bits.TMR0IP = 0)
#endif 

#endif 
/* ------------- Section: Macro Functions Declarations ------------- */

/* ------------- Section: Data Type Declarations ------------- */

/* ------------- Section: Function Declarations -------------*/




#endif	/* MCAL_INTERNAL_INTERRUPT_H */

