/* 
 * File:   mcal_exernal_interrupt.h
 * Author: AhmedSamy
 *
 * Created on September 27, 2023, 7:17 AM
 */

#ifndef MCAL_EXERNAL_INTERRUPT_H
#define	MCAL_EXERNAL_INTERRUPT_H

/* ------------- Section : Includes ------------- */
#include "mcal_interrupt_config.h"
#include "../GPIO/GPIO.h"

/* ------------- Section: Macro Functions Declarations ------------- */

/*===================================================================*/
#if EXT_INTERRUPT_INTx_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
/*===================================================================*/

/*=============================== INT0 ===============================*/
/*A macro will @Enable External Interrupt , @INT0  (INTCON <4> INT0IE)    */
#define EXT_INT0_Enable()                  (INTCONbits.INT0IE = 1)
/*A macro will @Disable External Interrupt , @INT0 (INTCON <4> INT0IE)    */
#define EXT_INT0_Disable()                 (INTCONbits.INT0IE = 0)

/*A macro will @Clear Flag External Interrupt , @INT0 (INTCON <1> INT0IF) */
#define EXT_INT0_Flag_Clear()              (INTCONbits.INT0IF = 0)

/*NOTE : INT0 IS ALWASYS HIGH PRIORITY*/

/*A macro will @SET Edge Detect to Interrupt on @Rising edge , @INT0 (INTCON2 <6> INTEDG0)    */
#define EXT_INT0_RisingEdgeSet()           (INTCON2bits.INTEDG0 = 1)
/*A macro will @SET Edge Detect to Interrupt on @Falling edge , @INT0 (INTCON2 <6> INTEDG0)    */
#define EXT_INT0_FallingEdgeSet()          (INTCON2bits.INTEDG0 = 0)

/*=============================== INT1 ===============================*/
/*A macro will @Enable External Interrupt , @INT1  (INTCON3 <3> INT1IE)   */
#define EXT_INT1_Enable()                  (INTCON3bits.INT1IE = 1)
/*A macro will @Disable External Interrupt , @INT1 (INTCON3 <3> INT1IE)   */
#define EXT_INT1_Disable()                 (INTCON3bits.INT1IE = 0)

/*A macro will @Clear Flag External Interrupt , @INT1 (INTCON3 <0> INT1IF) */
#define EXT_INT1_Flag_Clear()              (INTCON3bits.INT1IF = 0)

/*A macro will @SET Edge Detect to Interrupt on @Rising edge , @INT1 (INTCON2 <5> INTEDG1)    */
#define EXT_INT1_RisingEdgeSet()          (INTCON2bits.INTEDG1 = 1)
/*A macro will @SET Edge Detect to Interrupt on @Falling edge , @INT1 (INTCON2 <5> INTEDG1)    */
#define EXT_INT1_FallingEdgeSet()          (INTCON2bits.INTEDG1 = 0)
/*=============================== INT2 ===============================*/
/*A macro will @Enable External Interrupt , @INT2  (INTCON3 <4> INT0IE)    */
#define EXT_INT2_Enable()                  (INTCON3bits.INT2IE = 1)
/*A macro will @Disable External Interrupt , @INT2 (INTCON3 <4> INT0IE)    */
#define EXT_INT2_Disable()                 (INTCON3bits.INT2IE = 0)

/*A macro will @Clear Flag External Interrupt , @INT2 (INTCON3 <1> INT0IF)    */
#define EXT_INT2_Flag_Clear()              (INTCON3bits.INT2IF = 0)

/*A macro will @SET Edge Detect to Interrupt on @Rising edge , @INT2 (INTCON2 <4> INTEDG2)    */
#define EXT_INT2_RisingEdgeSet()          (INTCON2bits.INTEDG2 = 1)
/*A macro will @SET Edge Detect to Interrupt on @Falling edge , @INT2 (INTCON2 <4> INTEDG2)    */
#define EXT_INT2_FallingEdgeSet()          (INTCON2bits.INTEDG2 = 0)
/*===================================================================*/
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE

/*A macro will @Set INT1  External Interrupt to be @HIGH Priority    */
#define EXT_INT1_High_PrioritySet()        (INTCON3bits.INT1IP = 1)
/*A macro will @Set INT1  External Interrupt to be @LOW Priority    */
#define EXT_INT1_Low_PrioritySet()         (INTCON3bits.INT1IP = 0)

/*A macro will @Set INT2  External Interrupt to be @HIGH Priority    */
#define EXT_INT2_High_PrioritySet()        (INTCON3bits.INT2IP = 1)
/*A macro will @Set INT2  External Interrupt to be @LOW Priority    */
#define EXT_INT2_Low_PrioritySet()         (INTCON3bits.INT2IP = 0)

#endif
#endif
/*=====================================================================*/

/*===================================================================*/
#if EXT_INTERRUPT_OnChange_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
/*===================================================================*/
/*A macro will @Enable External Interrupt , @RBx   */
#define EXT_RBX_Enable()                  (INTCONbits.RBIE = 1)
/*A macro will @Disable External Interrupt , @RBx   */
#define EXT_RBX_Disable()                 (INTCONbits.RBIE = 0)
 
/*A macro will @Clear Flag External Interrupt , RBx*/
#define EXT_RBX_Clear_Flag()              (INTCONbits.RBIF = 0)

/*===================================================================*/
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE

/*A macro will @Set External Interrupt @RBx to be @HIGH Priority    */
#define EXT_RBX_High_PrioritySet()        (INTCON2bits.RBIP = 1)
/*A macro will @Set External Interrupt @RBx to be @LOW Priority    */
#define EXT_RBX_Low_PrioritySet()         (INTCON2bits.RBIP = 0)

#endif


#endif


/* ------------- Section: Data Type Declarations ------------- */
typedef enum{
    INTERRUPT_FALLING_EDGE = 0,
    INTERRUPT_RISING_EDGE
}interrupt_INTx_Edge;

typedef enum{
    EXTERNAL_INT0,
    EXTERNAL_INT1,
    EXTERNAL_INT2
}interrupt_INTx_Src;

typedef struct{
    void (*EXT_InterruptHandler)();
    PIN_config_t                mcu_pin;
    interrupt_INTx_Edge         edge;
    interrupt_INTx_Src          source;
    interrupt_priority_config   priority;
}interrupt_INTx_t;

typedef struct{
    void (*EXT_InterruptHandler_HIGH)();
    void (*EXT_InterruptHandler_LOW)();
    PIN_config_t                mcu_pin;
    interrupt_priority_config   priority;
}interrupt_RBx_t;

/* ------------- Section: Function Declarations -------------*/

Std_ReturnType interrupt_INTx_Init(const interrupt_INTx_t *int_obj);
Std_ReturnType interrupt_INTx_DeInit(const interrupt_INTx_t *int_obj);
Std_ReturnType interrupt_RBx_init(const interrupt_RBx_t *int_obj);
Std_ReturnType interrupt_RBx_Deinit(const interrupt_RBx_t *int_obj);



#endif	/* MCAL_EXERNAL_INTERRUPT_H */

