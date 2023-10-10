/* 
 * File:   mcal_exernal_interrupt.c
 * Author: AhmedSamy
 *
 * Created on September 27, 2023, 7:17 AM
 */
#include "mcal_exernal_interrupt.h"


/*=========================================================================================*/
/*===============================      Helper Functions     ===============================*/
/*=========================================================================================*/

/* Pointer to function to hold the Call backs for @INTx */
static void (*INT0_InterruptHandler)(void) = NULL ;
static void (*INT1_InterruptHandler)(void) = NULL ;
static void (*INT2_InterruptHandler)(void) = NULL ;
/* Pointer to function to hold the Call backs for @RBx */
static void (*RB4_InterruptHandler_HIGH)(void) = NULL ;
static void (*RB4_InterruptHandler_LOW)(void) = NULL ;
static void (*RB5_InterruptHandler_HIGH)(void) = NULL ;
static void (*RB5_InterruptHandler_LOW)(void) = NULL ;
static void (*RB6_InterruptHandler_HIGH)(void) = NULL ;
static void (*RB6_InterruptHandler_LOW)(void) = NULL ;
static void (*RB7_InterruptHandler_HIGH)(void) = NULL ;
static void (*RB7_InterruptHandler_LOW)(void) = NULL ;

static Std_ReturnType interrupt_INTx_Enable(const interrupt_INTx_t *int_obj);
static Std_ReturnType interrupt_INTx_Disable(const interrupt_INTx_t *int_obj);
static Std_ReturnType interrupt_INTx_Priority_Init(const interrupt_INTx_t *int_obj);
static Std_ReturnType interrupt_INTx_Edge_Init(const interrupt_INTx_t *int_obj);
static Std_ReturnType interrupt_INTx_Pin_Init(const interrupt_INTx_t *int_obj);
static Std_ReturnType interrupt_INTx_Clear_Flag(const interrupt_INTx_t *int_obj);
static Std_ReturnType Interrupt_INTx_SetInterruptHandler(const interrupt_INTx_t *int_obj);

static Std_ReturnType INT0_SetInterruptHandler(void (*InterruptHandler)(void));
static Std_ReturnType INT1_SetInterruptHandler(void (*InterruptHandler)(void));
static Std_ReturnType INT2_SetInterruptHandler(void (*InterruptHandler)(void));

static Std_ReturnType RB4_SetInterruptHandler(void (*InterruptHandler)(void));
static Std_ReturnType RB5_SetInterruptHandler(void (*InterruptHandler)(void));
static Std_ReturnType RB6_SetInterruptHandler(void (*InterruptHandler)(void));
static Std_ReturnType RB7_SetInterruptHandler(void (*InterruptHandler)(void));

static Std_ReturnType interrupt_RBx_Enable(const interrupt_RBx_t *int_obj);
static Std_ReturnType interrupt_RBx_Disable(const interrupt_RBx_t *int_obj);
static Std_ReturnType interrupt_RBx_Priority_Init(const interrupt_RBx_t *int_obj);
static Std_ReturnType interrupt_RBx_Pin_Init(const interrupt_RBx_t *int_obj);



/*=========================================================================================*/
/*======================================= INTx_ISRs =======================================*/
/*=========================================================================================*/
void INT0_ISR(void)
{
    /* The INT0 external interrupt occurred (must be cleared in Software) */
    EXT_INT0_Flag_Clear();
    /*Code*/
    
    /*Callback function*/
    if(INT0_InterruptHandler){ INT0_InterruptHandler(); }
    else{/* Nothing */}
}
void INT1_ISR(void)
{
    /* The INT1 external interrupt occurred (must be cleared in Software) */
    EXT_INT1_Flag_Clear();
    /*Code*/
    
    /*Callback function*/
    if(INT1_InterruptHandler){ INT1_InterruptHandler(); }
    else{/* Nothing */}
}
void INT2_ISR(void)
{
    /* The INT2 external interrupt occurred (must be cleared in Software) */
    EXT_INT2_Flag_Clear();
    /*Code*/
    
    /*Callback function*/
    if(INT2_InterruptHandler){ INT2_InterruptHandler(); }
    else{/* Nothing */}

}
/*=========================================================================================*/
/*======================================= RBx_ISRs  =======================================*/
/*=========================================================================================*/
void RB4_ISR(uint8 RBx_Source)
{
    /* The RB4 external interrupt occurred (must be cleared in Software) */
    EXT_RBX_Clear_Flag();
    /*Code*/
    
    /*Callback function*/
    if(0 == RBx_Source){
        if(RB4_InterruptHandler_LOW){ RB4_InterruptHandler_LOW(); }
        else{/* Nothing */}
    }else if(1 == RBx_Source){
        if(RB4_InterruptHandler_HIGH){ RB4_InterruptHandler_HIGH(); }
        else{/* Nothing */}
    }else{/* Nothing */}


}
void RB5_ISR(uint8 RBx_Source)
{
    /* The RB5 external interrupt occurred (must be cleared in Software) */
    EXT_RBX_Clear_Flag();
    /*Code*/
    
    /*Callback function*/
    if(0 == RBx_Source){
        if(RB5_InterruptHandler_LOW){ RB5_InterruptHandler_LOW(); }
        else{/* Nothing */}
    }else if(1 == RBx_Source){
        if(RB5_InterruptHandler_HIGH){ RB5_InterruptHandler_HIGH(); }
        else{/* Nothing */}
    }else{/* Nothing */}


}
void RB6_ISR(uint8 RBx_Source)
{
    /* The RB6 external interrupt occurred (must be cleared in Software) */
    EXT_RBX_Clear_Flag();
    /*Code*/
    
    /*Callback function*/
    if(0 == RBx_Source){
        if(RB6_InterruptHandler_LOW){ RB6_InterruptHandler_LOW(); }
        else{/* Nothing */}
    }else if(1 == RBx_Source){
        if(RB6_InterruptHandler_HIGH){ RB6_InterruptHandler_HIGH(); }
        else{/* Nothing */}
    }else{/* Nothing */}


}
void RB7_ISR(uint8 RBx_Source)
{
    /* The RB7 external interrupt occurred (must be cleared in Software) */
    EXT_RBX_Clear_Flag();
    /*Code*/
    
    /*Callback function*/
    if(0 == RBx_Source){
        if(RB7_InterruptHandler_LOW){ RB7_InterruptHandler_LOW(); }
        else{/* Nothing */}
    }else if(1 == RBx_Source){
        if(RB7_InterruptHandler_HIGH){ RB7_InterruptHandler_HIGH(); }
        else{/* Nothing */}
    }else{/* Nothing */}


}

/*=========================================================================================*/
/*====                                                                                 ====*/
/*====                               Software Interfaces                               ====*/
/*====                                                                                 ====*/
/*=========================================================================================*/

/***********************************************************************
 * @brief Initialize the external interrupt INT0, INT1 and INT2
 * @param int_obj  Pointer to the Interrupt configuration object
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 ***********************************************************************/
Std_ReturnType interrupt_INTx_Init(const interrupt_INTx_t *int_obj){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == int_obj){
        ret = E_NOT_OK;
    }else{
        /*Disable the External Interrupt*/
        ret = interrupt_INTx_Disable(int_obj);
        /*Clear interrupt flag*/
        ret = interrupt_INTx_Clear_Flag(int_obj);
        /*Configure External interrupt : edge */
        ret = interrupt_INTx_Edge_Init(int_obj);
        #if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
            /*Configure External interrupt : Priority */
            ret = interrupt_INTx_Priority_Init(int_obj);
        #endif
        /*Configure External interrupt : I/O Pin */
        ret = interrupt_INTx_Pin_Init(int_obj);
        /*Configure Default Interrupt CallBack */
        ret = Interrupt_INTx_SetInterruptHandler(int_obj);
        /* Enable the External Interrupt*/
        ret = interrupt_INTx_Enable(int_obj);
    }
    return ret;
}

/***********************************************************************
 * @brief DeInitialize the interrupt module
 * @param int_obj  Pointer to the Interrupt configuration object
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 ***********************************************************************/
Std_ReturnType interrupt_INTx_DeInit(const interrupt_INTx_t *int_obj){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == int_obj){
        ret = E_NOT_OK;
    }else{
        ret = interrupt_INTx_Disable(int_obj);
    }
    return ret; 
}

/***********************************************************************
 * @brief  
 * @param int_obj  Pointer to the Interrupt configuration object
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 ***********************************************************************/
Std_ReturnType interrupt_RBx_init(const interrupt_RBx_t *int_obj){
    
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == int_obj){
        ret = E_NOT_OK;
    }else{
        /*Disable External Interrupt , @RBx   */
        EXT_RBX_Disable();
        
        /*Clear Flag External Interrupt , @RBx*/
        EXT_RBX_Clear_Flag();
        
                        
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
        /*IPEN*/
        INTERRUPT_PriorityLevel_Enable(); 
        
         if(INTERRUPT_LOW_PRIORITY == int_obj->priority){
        /*@Enable Low Priority global interrupts              */
            INTERRUPT_GlobleaInterrupt_LOW_Enable(); 
        /*Set External Interrupt @RBx to be @LOW Priority     */
            EXT_RBX_Low_PrioritySet();
        }else if(INTERRUPT_HIGH_PRIORITY == int_obj->priority){
        /*@Enable High Priority global interrupts             */
            INTERRUPT_GlobleaInterrupt_HIGH_Enable();
        /*Set External Interrupt @RBx to be @HIGH Priority    */
            EXT_RBX_High_PrioritySet();
        }else{/*  Nothing  */}
        
#else
        INTERRUPT_GlobalInterrupt_Enable(); 
        INTERRUPT_PeripheralInterrupt_Enable();
#endif          
        /*Initialize the RBx to Be Input  < TRISB(4-7) = 0 >*/
        ret = gpio_pin_direction_init(&( int_obj->mcu_pin ));
        
        /*Initialize the Call back Functions*/
        switch(int_obj->mcu_pin.pin){
            case GPIO_PIN4 :
                RB4_InterruptHandler_HIGH = int_obj->EXT_InterruptHandler_HIGH;
                RB4_InterruptHandler_LOW = int_obj->EXT_InterruptHandler_LOW;
                break;
            case GPIO_PIN5 :
                RB5_InterruptHandler_HIGH = int_obj->EXT_InterruptHandler_HIGH;
                RB5_InterruptHandler_LOW = int_obj->EXT_InterruptHandler_LOW;
                break ;
            case GPIO_PIN6 :
                RB6_InterruptHandler_HIGH = int_obj->EXT_InterruptHandler_HIGH;
                RB6_InterruptHandler_LOW = int_obj->EXT_InterruptHandler_LOW;
                break;
            case GPIO_PIN7 :
                RB7_InterruptHandler_HIGH = int_obj->EXT_InterruptHandler_HIGH;
                RB7_InterruptHandler_LOW = int_obj->EXT_InterruptHandler_LOW;
                break;
                
            default:
                ret = E_NOT_OK;
                break;
        }
        
        /*Enable External Interrupt , @RBx   */
        EXT_RBX_Enable();
        
        ret = E_OK;
    }
    return ret;
}


 /***********************************************************************
 * @brief  
 * @param int_obj  Pointer to the Interrupt configuration object
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 ***********************************************************************/
Std_ReturnType interrupt_RBx_Deinit(const interrupt_RBx_t *int_obj){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == int_obj){
        ret = E_NOT_OK;
    }else{
        
        EXT_RBX_Disable();
        ret = E_OK;
    }
    return ret;
}

/*=========================================================================================*/
/*===============================      Helper Functions     ===============================*/
/*=========================================================================================*/

/***********************************************************************
 * @brief Enable the INTx interrupt source
 * @param int_obj  Pointer to the Interrupt configuration object
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 ***********************************************************************/
static Std_ReturnType interrupt_INTx_Enable(const interrupt_INTx_t *int_obj){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == int_obj){
        ret = E_NOT_OK;
    }else{
        switch(int_obj->source)
        {
            case EXTERNAL_INT0:
                
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
                /*IPEN*/
                INTERRUPT_PriorityLevel_Enable(); 
                /*EXTERNAL INT0 is always High Priority*/
                INTERRUPT_GlobleaInterrupt_HIGH_Enable();
                
               
#else
                INTERRUPT_GlobalInterrupt_Enable(); 
                INTERRUPT_PeripheralInterrupt_Enable();
#endif                

                EXT_INT0_Enable();
                
                ret = E_OK;
                break;

            case EXTERNAL_INT1:
                
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
                INTERRUPT_PriorityLevel_Enable(); 
                if(INTERRUPT_LOW_PRIORITY == int_obj->priority){
                   INTERRUPT_GlobleaInterrupt_LOW_Enable();
                }else if(INTERRUPT_HIGH_PRIORITY == int_obj->priority){
                   INTERRUPT_GlobleaInterrupt_HIGH_Enable();
                }else{/*  Nothing  */}
#else
                INTERRUPT_GlobalInterrupt_Enable(); 
                INTERRUPT_PeripheralInterrupt_Enable();
#endif                
                EXT_INT1_Enable();
                
                ret = E_OK;
                break;

            case EXTERNAL_INT2: 
                
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
                /*IPEN*/
                INTERRUPT_PriorityLevel_Enable(); 
                
                if(INTERRUPT_LOW_PRIORITY == int_obj->priority){
                     INTERRUPT_GlobleaInterrupt_LOW_Enable();
                }else if(INTERRUPT_HIGH_PRIORITY == int_obj->priority){
                   INTERRUPT_GlobleaInterrupt_HIGH_Enable();
                }else{/*  Nothing  */}
                
#else
                INTERRUPT_GlobalInterrupt_Enable(); 
                INTERRUPT_PeripheralInterrupt_Enable();
#endif                

                EXT_INT2_Enable();
                
                ret = E_OK;  
                break;
            
            default: 
                ret = E_NOT_OK ;
                break;    
        }
        
    }
    return ret;
}
/***********************************************************************
 * @brief DeInitialize the interrupt module
 * @param int_obj  Pointer to the Interrupt configuration object
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 ***********************************************************************/

static Std_ReturnType interrupt_INTx_Disable(const interrupt_INTx_t *int_obj){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == int_obj){
        ret = E_NOT_OK;
    }else{
        switch(int_obj->source)
        {
            case EXTERNAL_INT0:   EXT_INT0_Disable(); ret = E_OK;  break;
            case EXTERNAL_INT1:   EXT_INT1_Disable(); ret = E_OK;  break;
            case EXTERNAL_INT2:   EXT_INT2_Disable(); ret = E_OK;  break;
            
            default: 
                ret = E_NOT_OK ;
                break;    
        }
    }
    return ret;
}

#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
static Std_ReturnType interrupt_INTx_Priority_Init(const interrupt_INTx_t *int_obj){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == int_obj){
        ret = E_NOT_OK;
    }else{
        switch(int_obj->source)
        { 
            case EXTERNAL_INT1:
                if(INTERRUPT_LOW_PRIORITY == int_obj->priority){
                    EXT_INT1_Low_PrioritySet();
                }else if(INTERRUPT_HIGH_PRIORITY == int_obj->priority){
                    EXT_INT1_High_PrioritySet();
                }else{/*  Nothing  */}
                
                ret = E_OK;
                break;
                
            case EXTERNAL_INT2:    
                if(INTERRUPT_LOW_PRIORITY == int_obj->priority){
                    EXT_INT2_Low_PrioritySet();
                }else if(INTERRUPT_HIGH_PRIORITY == int_obj->priority){
                    EXT_INT2_High_PrioritySet();
                }else{/*  Nothing  */}
                ret = E_OK;
                break;
            
            default: 
                ret = E_NOT_OK ;
                break;    
        }
    }
    return ret;
}
#endif

static Std_ReturnType interrupt_INTx_Edge_Init(const interrupt_INTx_t *int_obj){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == int_obj){
        ret = E_NOT_OK;
    }else{
        switch(int_obj->source)
        {
            case EXTERNAL_INT0:   
                if(INTERRUPT_FALLING_EDGE == int_obj->edge)
                    EXT_INT0_FallingEdgeSet();
                else if(INTERRUPT_RISING_EDGE == int_obj->edge)
                    EXT_INT0_RisingEdgeSet();
                else{ /* Nothing */ }
                
                ret = E_OK; 
                break;
                
            case EXTERNAL_INT1:
                if(INTERRUPT_FALLING_EDGE == int_obj->edge)
                    EXT_INT1_FallingEdgeSet();
                else if(INTERRUPT_RISING_EDGE == int_obj->edge)
                    EXT_INT1_RisingEdgeSet();
                else{ /* Nothing */ }
                    
                ret = E_OK;
                break;
                
            case EXTERNAL_INT2:  
                if(INTERRUPT_FALLING_EDGE == int_obj->edge)
                    EXT_INT2_FallingEdgeSet();
                else if(INTERRUPT_RISING_EDGE == int_obj->edge)
                    EXT_INT2_RisingEdgeSet();
                else{ /* Nothing */ }                
                ret = E_OK; 
                break;
            
            default: 
                ret = E_NOT_OK ;
                break;    
        }
        
    }
    return ret;    
    
}
static Std_ReturnType interrupt_INTx_Pin_Init(const interrupt_INTx_t *int_obj){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == int_obj){
        ret = E_NOT_OK;
    }else{
        ret = gpio_pin_direction_init( &(int_obj->mcu_pin));
        }
        
    return ret;    
}

static Std_ReturnType interrupt_INTx_Clear_Flag(const interrupt_INTx_t *int_obj){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == int_obj){
        ret = E_NOT_OK;
    }else{
        switch(int_obj->source)
        {
            case EXTERNAL_INT0: 
                EXT_INT0_Flag_Clear();
                ret = E_OK;  
                break;
            case EXTERNAL_INT1:   
                EXT_INT1_Flag_Clear();
                ret = E_OK;  
                break;
            case EXTERNAL_INT2:   
                EXT_INT2_Flag_Clear();
                ret = E_OK;
                break;
            
            default: 
                ret = E_NOT_OK ;
                break;    
        }
    }
        
    return ret;    
}

static Std_ReturnType INT0_SetInterruptHandler(void (*InterruptHandler)(void)){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == InterruptHandler){
        ret = E_NOT_OK;
    }else{
        INT0_InterruptHandler = InterruptHandler;
        ret = E_OK;
    }
        
    return ret;
}

static Std_ReturnType INT1_SetInterruptHandler(void (*InterruptHandler)(void)){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == InterruptHandler){
        ret = E_NOT_OK;
    }else{
        INT1_InterruptHandler = InterruptHandler;
        ret = E_OK;
    }
        
    return ret;
}

static Std_ReturnType INT2_SetInterruptHandler(void (*InterruptHandler)(void)){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == InterruptHandler){
        ret = E_NOT_OK;
    }else{
        INT2_InterruptHandler = InterruptHandler;
        ret = E_OK;
    }
        
    return ret;    
}
 
static Std_ReturnType Interrupt_INTx_SetInterruptHandler(const interrupt_INTx_t *int_obj){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == int_obj){
        ret = E_NOT_OK;
    }else{
        switch(int_obj->source)
        {
            case EXTERNAL_INT0: 
                ret = INT0_SetInterruptHandler(int_obj->EXT_InterruptHandler);
                ret = E_OK;  
                break;
            case EXTERNAL_INT1:   
                ret = INT1_SetInterruptHandler(int_obj->EXT_InterruptHandler);
                ret = E_OK;  
                break;
            case EXTERNAL_INT2:   
                ret = INT2_SetInterruptHandler(int_obj->EXT_InterruptHandler);
                ret = E_OK;
                break;
            
            default: 
                ret = E_NOT_OK ;
                break;    
        }
    }
        
    return ret; 
}




static Std_ReturnType interrupt_RBx_Enable(const interrupt_RBx_t *int_obj){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == int_obj){
        ret = E_NOT_OK;
    }else{


                EXT_RBX_Enable();
                
                ret = E_OK;
    }
    return ret;     
}
static Std_ReturnType interrupt_RBx_Disable(const interrupt_RBx_t *int_obj){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == int_obj){
        ret = E_NOT_OK;
    }else{


                EXT_RBX_Disable();
                
                ret = E_OK;
    }
    return ret;     
}
