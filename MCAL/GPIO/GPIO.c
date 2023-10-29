/* 
 * File:   application.c
 * Author: AhmedElnozahy
 *
 * Created on July 25, 2023, 4:24 PM
 */

#include "GPIO.h"


/*Reference to the Data Direction Control Registers*/
volatile uint8 * TRIS_Registers[] = { &TRISA , &TRISB , &TRISC , &TRISD , &TRISE };
/*Reference to the Data LATCH Register (Read and Write to Data Latch)*/
volatile uint8 * LAT_Registers[] = {&LATA , &LATB , &LATC , &LATD, &LATE };
/*Reference to the Port Status Register*/
volatile uint8 * PORT_Registers[] = {&PORTA , &PORTB , &PORTC , &PORTD, &PORTE };


/*******************************************************************************
 * @brief Initialize the direction of a specific pin @ref Direction_t
 * @param _pin_config pointer to the configurations @ref PIN_config_t 
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 *******************************************************************************/
#if GPIO_PORT_CONFIGURATIONS == CONFIG_ENABLE
Std_ReturnType gpio_pin_direction_init(const PIN_config_t *_pin_config){
    Std_ReturnType ret = E_OK;
    if(NULL == _pin_config || _pin_config->pin > PIN_MAX_NUMBER-1){
        ret = E_NOT_OK;
    }
    else{
        switch(_pin_config->direction){
            case GPIO_DIR_OUTPUT :
                CLR_BIT(*TRIS_Registers[_pin_config->port], _pin_config->pin);
                break;
            case GPIO_DIR_INPUT :
                SET_BIT(*TRIS_Registers[_pin_config->port], _pin_config->pin);
                break;
            default : ret = E_NOT_OK;
        }
    }
    return ret;
}
#endif

/*******************************************************************************
 * @param _pin_config pointer to the configurations @ref PIN_config_t 
 * @param direction_status
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action 
 ******************************************************************************/
#if GPIO_PORT_CONFIGURATIONS==CONFIG_ENABLE
Std_ReturnType gpio_pin_get_direction_status(const PIN_config_t *_pin_config, Direction_t *direction_status){
    Std_ReturnType ret = E_OK;
    if(NULL == _pin_config || NULL == direction_status || _pin_config->pin > PIN_MAX_NUMBER-1){
        ret = E_NOT_OK;
    }
    else{
        *direction_status = READ_BIT(*TRIS_Registers[_pin_config->port], _pin_config->pin);
    }
    return ret;
}
#endif

/*******************************************************************************
 * @param _pin_config pointer to the configurations @ref PIN_config_t 
 * @param logic
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 ******************************************************************************/
#if GPIO_PORT_CONFIGURATIONS == CONFIG_ENABLE
Std_ReturnType gpio_pin_write_logic(const PIN_config_t *_pin_config, Logic_t logic){
    Std_ReturnType ret = E_OK;
    if(NULL == _pin_config || _pin_config->pin > PIN_MAX_NUMBER-1){
        ret = E_NOT_OK;
    }
    else{
        switch(logic){
            case GPIO_LOW :
                CLR_BIT(*LAT_Registers[_pin_config->port], _pin_config->pin);
                break;
            case GPIO_HIGH :
                SET_BIT(*LAT_Registers[_pin_config->port], _pin_config->pin);
                break;
            default : ret = E_NOT_OK;
        }
    }
    return ret;
}
#endif

/*******************************************************************************
 * @param _pin_config pointer to the configurations @ref PIN_config_t 
 * @param logic
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 *******************************************************************************/
#if GPIO_PORT_CONFIGURATIONS==CONFIG_ENABLE
Std_ReturnType gpio_pin_read_logic(const PIN_config_t *_pin_config, Logic_t *logic){
    Std_ReturnType ret = E_OK;
    if(NULL == _pin_config || NULL == logic || _pin_config->pin > PIN_MAX_NUMBER-1){
        ret = E_NOT_OK;
    }
    else{
        *logic = READ_BIT(*PORT_Registers[_pin_config->port], _pin_config->pin);
    }
    return ret;
}
#endif

/*******************************************************************************
 * @param _pin_config pointer to the configurations @ref PIN_config_t 
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 *******************************************************************************/
#if GPIO_PORT_CONFIGURATIONS==CONFIG_ENABLE
Std_ReturnType gpio_pin_toggle_logic(const PIN_config_t *_pin_config){
    Std_ReturnType ret = E_OK;
    if(NULL == _pin_config || _pin_config->pin > PIN_MAX_NUMBER-1){
        ret = E_NOT_OK;
    }
    else{
        TOG_BIT(*LAT_Registers[_pin_config->port], _pin_config->pin);
    }
    return ret;
}
#endif

/*******************************************************************************
 * @param _pin_config pointer to the configurations @ref PIN_config_t 
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 ******************************************************************************/
#if GPIO_PORT_CONFIGURATIONS == CONFIG_ENABLE
Std_ReturnType gpio_pin_init(const PIN_config_t *_pin_config){
    Std_ReturnType ret = E_OK;
    if(NULL == _pin_config || _pin_config->pin > PIN_MAX_NUMBER-1){
        ret = E_NOT_OK;
    }
    else{
        ret = gpio_pin_direction_init(_pin_config);
        ret = gpio_pin_write_logic(_pin_config, _pin_config->logic);
    }
    return ret;
}
#endif

/* --------------------------------------------------------------------------- */
/* ----------                         PORT                          ---------- */
/* --------------------------------------------------------------------------- */

/**
 * 
 * @param port          @ref PORT_index_t
 * @param direction     GPIO_DIR_INPUT  - GPIO_DIR_OUTPUT
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
#if GPIO_PORT_CONFIGURATIONS == CONFIG_ENABLE
Std_ReturnType gpio_port_direction_init(PORT_index_t port , uint8 direction){
    Std_ReturnType ret = E_OK;
    if(port > PORT_MAX_NUMBER-1){
        ret = E_NOT_OK;
    }
    else{
        *TRIS_Registers[port] = direction ; 
    }

    return ret;
}
#endif

/**
 * 
 * @param port           @ref PORT_index_t
 * @param direction      
 * @return Status of the function & Returning by ref the direction of the port
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
*/
#if GPIO_PORT_CONFIGURATIONS == CONFIG_ENABLE
Std_ReturnType gpio_port_get_direction_status(PORT_index_t port , uint8* direction){
    Std_ReturnType ret = E_OK;
    if( (NULL == direction) || port > PORT_MAX_NUMBER-1){//Port validation
        ret = E_NOT_OK;
    }
    else{
        *direction = *TRIS_Registers[port]; 
    }
    return ret;
}
#endif

/*******************************************************************************
 * @param port           @ref PORT_index_t
 * @param logic
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
*******************************************************************************/
#if GPIO_PORT_CONFIGURATIONS == CONFIG_ENABLE
Std_ReturnType gpio_port_write_logic(PORT_index_t port , uint8 logic){
    Std_ReturnType ret = E_OK;
    if (port > PORT_MAX_NUMBER-1){
        ret = E_NOT_OK;
    }
    else{
        *LAT_Registers[port] = logic;
    }

    return ret;
}
#endif

/*******************************************************************************
 * @param port           @ref PORT_index_t
 * @param logic
 * @return Status of the function & Returning by ref the logic of the port
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
*******************************************************************************/
#if GPIO_PORT_CONFIGURATIONS == CONFIG_ENABLE
Std_ReturnType gpio_port_read_logic(PORT_index_t port , uint8 *logic){
    Std_ReturnType ret = E_OK;
    if(NULL == logic || (port > PORT_MAX_NUMBER-1))
    {
        ret = E_NOT_OK;
    }else{
        *logic = *LAT_Registers[port];
    }
    
    return ret;
}
#endif

/*******************************************************************************
 * @param port           @ref PORT_index_t
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
*******************************************************************************/
#if GPIO_PORT_CONFIGURATIONS == CONFIG_ENABLE
Std_ReturnType gpio_port_toggle_logic(PORT_index_t port)
{
    Std_ReturnType ret = E_OK;
    
    if(port > PORT_MAX_NUMBER-1){
        ret = E_NOT_OK;
    }
    else{
       *TRIS_Registers[port] ^= PORT_MASK;
    }

    
    return ret;
}
#endif