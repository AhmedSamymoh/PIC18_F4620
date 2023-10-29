/* 
 * File:   GPIO.h
 * Author: AhmedElnozahy
 *
 * Created on August 3, 2023, 4:53 PM
 */

#ifndef HAL_GPIO_H
#define	HAL_GPIO_H

/* Section : Includes */
#include"../compiler.h"
#include "../std_lib.h"
#include "../std_types.h"
#include "../device_config.h"
#include "GPIO_Config.h"


/* Section : Macro Declarations */
#define BIT_MASK            1
#define PORT_MASK           0xFF 

#define PIN_MAX_NUMBER      8
#define PORT_MAX_NUMBER     5

#define PORT_PIN_CONFIG     CONFIG_ENABLE


/* Section : Macro Functions Declarations */
#define HWREG8(_address)                ( *((volatile uint8*)(_address)) )

#define SET_BIT(REG , BIT_POSN)         (REG |=  (BIT_MASK << BIT_POSN))   
#define CLR_BIT(REG , BIT_POSN)         (REG &= ~(BIT_MASK << BIT_POSN))   
#define TOG_BIT(REG , BIT_POSN)         (REG ^=  (BIT_MASK << BIT_POSN))   
#define READ_BIT(REG , BIT_POSN)        ((REG >> BIT_POSN ) & BIT_MASK )


/* Section : Data Type Declarations */
typedef enum
{
    GPIO_PIN0,
    GPIO_PIN1,
    GPIO_PIN2,
    GPIO_PIN3,
    GPIO_PIN4,
    GPIO_PIN5,
    GPIO_PIN6,
    GPIO_PIN7,
}PIN_index_t;

typedef enum
{
    PORTA_INDEX,
    PORTB_INDEX,
    PORTC_INDEX,
    PORTD_INDEX,
    PORTE_INDEX,
}PORT_index_t;

typedef enum
{
    GPIO_DIR_OUTPUT = 0,
    GPIO_DIR_INPUT
}Direction_t;

typedef enum
{
    GPIO_LOW = 0,
    GPIO_HIGH
}Logic_t;

typedef struct
{
    uint8  port : 3;      /* 100 (4)    @REF  PORT_index_t    */
    uint8  pin  : 3;      /* 111 (7)    @REF  PIN_index_t     */
    uint8  direction : 1; /*            @REF  Direction_t     */
    uint8  logic : 1;     /*            @REF  Logic_t         */
} PIN_config_t; // 1 Byte


/* Section : Function Declarations */
Std_ReturnType gpio_pin_direction_init(const PIN_config_t *_pin_config);
Std_ReturnType gpio_pin_get_direction_status(const PIN_config_t *_pin_config, Direction_t *direction_status);
Std_ReturnType gpio_pin_write_logic(const PIN_config_t *_pin_config, Logic_t logic);
Std_ReturnType gpio_pin_read_logic(const PIN_config_t *_pin_config, Logic_t *logic);
Std_ReturnType gpio_pin_toggle_logic(const PIN_config_t *_pin_config);
Std_ReturnType gpio_pin_init(const PIN_config_t *_pin_config);

Std_ReturnType gpio_port_direction_init(PORT_index_t port, uint8 direction);
Std_ReturnType gpio_port_get_direction_status(PORT_index_t port , uint8* direction);
Std_ReturnType gpio_port_write_logic(PORT_index_t port , uint8 logic);
Std_ReturnType gpio_port_read_logic(PORT_index_t port , uint8 *logic);
Std_ReturnType gpio_port_toggle_logic(PORT_index_t port);


#endif	/* HAL_GPIO_H */









/*
#define PORTA_REG  ( *((volatile unsigned char*)0xF80) )
#define PORTB_REG  ( *((volatile unsigned char*)0xF81) )
#define PORTC_REG  ( *((volatile unsigned char*)0xF82) )
#define PORTD_REG  ( *((volatile unsigned char*)0xF83) )
#define PORTE_REG  ( *((volatile unsigned char*)0xF84) )
 */
