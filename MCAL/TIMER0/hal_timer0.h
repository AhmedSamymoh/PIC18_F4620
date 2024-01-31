/* 
 * File:   hal_timer.h
 * Author: AhmedSamy
 *
 * Created on October 29, 2023, 2:06 PM
 */

#ifndef HAL_TIMER_H
#define	HAL_TIMER_H

/*---------------------------- Section: Includes -----------------------------*/
#include <pic18f4620.h>
#include "../std_types.h"
#include "../../MCAL/Interrupt/mcal_internal_interrupt.h"
#include "../../MCAL/GPIO/GPIO.h"


/*----------------------- Section: Macro Declarations ------------------------*/
#define TIMER0_CFG_PRESCALER_ENABLE           1 
#define TIMER0_CFG_PRESCALER_DISABLE          0 
#define TIMER0_CFG_RISING_EDGE                1 
#define TIMER0_CFG_FALLING_EDGE               0 
#define TIMER0_CFG_COUNTER_MODE               1 
#define TIMER0_CFG_TIMER_MODE                 0 
#define TIMER0_CFG_8BIT_REGISTER              1 
#define TIMER0_CFG_16BIT_REGISTER             0 

/*------------------- Section: Macro Functions Declarations ------------------*/

/*PSA: Timer0 Prescaler Assignment bit */
#define TIMER0_PRESCALER_ENABLE()            (T0CONbits.PSA = 0)
#define TIMER0_PRESCALER_DISABLE()           (T0CONbits.PSA = 1)
/*T0SE: Timer0 Source Edge Select bit*/
#define TIMER0_RISING_EDGE()                 (T0CONbits.T0SE = 0)
#define TIMER0_FALLING_EDGE()                (T0CONbits.T0SE = 1)
/*T0CS: Timer0 Clock Source Select bit*/
#define TIMER0_TIMER_MODE()                  (T0CONbits.T0CS = 0)
#define TIMER0_COUNTER_MODE()                (T0CONbits.T0CS = 1)
/*T08BIT: Timer0 8-Bit/16-Bit Control bit*/
#define TIMER0_8BIT_REGISTER_MODE()          (T0CONbits.T08BIT = 1)
#define TIMER0_16BIT_REGISTER_MODE()         (T0CONbits.T08BIT = 0)
/*TMR0ON: Timer0 On/Off Control bit*/
#define TIMER0_ENABLE()                      (T0CONbits.TMR0ON = 1)
#define TIMER0_DISABLE()                     (T0CONbits.TMR0ON = 0)

/* --------------------- Section: Data Type Declarations -------------------- */

typedef enum {
    TIMER0_PRESCALER_DIV_BY_2 = 0,
    TIMER0_PRESCALER_DIV_BY_4,
    TIMER0_PRESCALER_DIV_BY_8,
    TIMER0_PRESCALER_DIV_BY_16,
    TIMER0_PRESCALER_DIV_BY_32,
    TIMER0_PRESCALER_DIV_BY_64,
    TIMER0_PRESCALER_DIV_BY_128,
    TIMER0_PRESCALER_DIV_BY_256,
} timer0_prescaler_select_t;

typedef struct{
#if TIMER0_INTERRUPT_FEATURE_ENABLE  == INTERRUPT_FEATURE_ENABLE
    void (*TMR0_InterruptHandler)(void);
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
    interrupt_priority_config    priority;
#endif
#endif   
    
    timer0_prescaler_select_t timer0_prescaler_value ;
    uint8 timer0_PreLoad_value    : 3;
    uint8 timer0_prescaler_enable : 1;
    uint8 timer0_source_edge      : 1;
    uint8 timer0_mode             : 1;
    uint8 timer0_register_size    : 1;
} timer0_t;

/* ---------------------- Section: Function Declarations ---------------------*/
Std_ReturnType TIMER0_Init(const timer0_t *_timer0);
Std_ReturnType TIMER0_DeInit(const timer0_t *_timer0);
Std_ReturnType TIMER0_READ(const timer0_t *_timer0 , uint16 * value);
Std_ReturnType TIMER0_WRITE(const timer0_t *_timer0 , uint16  value);

#endif	/* HAL_TIMER_H */

