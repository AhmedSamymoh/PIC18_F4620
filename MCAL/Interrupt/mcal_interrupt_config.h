/* 
 * File:   mcal_interrupt_config.h
 * Author: AhmedSamy
 *
 * Created on September 27, 2023, 7:15 AM
 */

#ifndef MCAL_INTERRUPT_CONFIG_H
#define	MCAL_INTERRUPT_CONFIG_H

/* ------------- Section : Includes ------------- */
#include"../compiler.h"
#include "../std_lib.h"
#include "../std_types.h"
#include "mcal_interrupt_gen_config.h"

/* ------------- Section: Macro Declarations ------------- */
#define INTERRUPT_ENABLE               1
#define INTERRUPT_DISABLE              0
#define INTERRUPT_OCCUR                1
#define INTERRUPT__NOT_OCCUR           0
#define INTERRUPT_PRIORITY_ENABLE      1 
#define INTERRUPT_PRIORITY_DISENABLE   0


/* ------------- Section: Macro Functions Declarations ------------- */

/*      Pre-Compile Configuration       */
/*===================================================================*/
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
/*===================================================================*/
/*A macro will @Enable Interrupt Priority Level Feature  (RCON <7> IPEN)    */
#define INTERRUPT_PriorityLevel_Enable()              (RCONbits.IPEN = 1 )
/*A macro will @Enable Interrupt Priority Level Feature  (RCON <7> IPEN)    */
#define INTERRUPT_PriorityLevel_Disable()             (RCONbits.IPEN = 0 )

/*A macro will @Enable High Priority global interrupts (INTCON <7> GIEH)    */
#define INTERRUPT_GlobleaInterrupt_HIGH_Enable()      (INTCONbits.GIEH = 1) 
/*A macro will @Disable High Priority global interrupts (INTCON <7> GIEH)   */
#define INTERRUPT_GlobleaInterrupt_HIGH_Disable()     (INTCONbits.GIEH = 0) 

/*A macro will @Enable Low Priority global interrupts  (INTCON <6> GIEL)    */
#define INTERRUPT_GlobleaInterrupt_LOW_Enable()       (INTCONbits.GIEL = 1)
/*A macro will @Disable Low Priority global interrupts  (INTCON <6> GIEL)   */
#define INTERRUPT_GlobleaInterrupt_LOW_Disable()      (INTCONbits.GIEL = 0)

#else

/*A macro will @Enable Global interrupt  (INTCON <7> GIE)                  */
#define INTERRUPT_GlobalInterrupt_Enable()           (INTCONbits.GIE = 1)
/*A macro will @Disable Global interrupt  (INTCON <7> GIE)                 */
#define INTERRUPT_GlobalInterrupt_Disable()          (INTCONbits.GIE = 0)
 
/*A macro will @Enable General interrupt  (INTCON <6> PEIE)                 */
#define INTERRUPT_PeripheralInterrupt_Enable()        (INTCONbits.PEIE = 1)
/*A macro will @Disable General interrupt  (INTCON <6> PEIE)                */
#define INTERRUPT_PeripheralInterrupt_Disable()       (INTCONbits.PEIE = 0)
#endif

/* ------------- Section: Data Type Declarations ------------- */

typedef enum{
    INTERRUPT_LOW_PRIORITY,
    INTERRUPT_HIGH_PRIORITY
} interrupt_priority_config;

/* ------------- Section: Function Declarations -------------*/



#endif	/* MCAL_INTERRUPT_CONFIG_H */
