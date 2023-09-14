/* 
 * File:   ecu_lcd.h
 * Author: AhmedSamy
 *
 * Created on September 13, 2023, 11:03 PM
 */

#ifndef ECU_LCD_H
#define	ECU_LCD_H

/* Section : Includes */
#include "../../MCAL/GPIO/GPIO.h"
#include "ecu_lcd_cfg.h"

/* Section: Macro Declarations */
#define _LCD_CLEAR                             0x01
#define _LCD_RETURN_HOME                       0x02
#define _LCD_ENTRY_MODE                        0x06

#define _LCD_CURSOR_OFF_DISPLAY_ON             0x0C
#define _LCD_CURSOR_OFF_DISPLAY_OFF            0x08

#define _LCD_CURSOR_ON_BLINK_ON                0x0F
#define _LCD_CURSOR_ON_BLINK_OFF               0x0E

#define _LCD_DISPLAY_SHIFT_RIGHT               0x1C
#define _LCD_DISPLAY_SHIFT_LIFT                0x18

#define _LCD_8BIT_MODE_2_LINE                  0x38
#define _LCD_4BIT_MODE_2_LINE                  0x28

#define _LCD_CGRAM_START                       0x40
#define _LCD_DDRAM_START                       0x80

#define ROW1     1
#define ROW2     2
#define ROW3     3
#define ROW4     4

/* Section: Macro Functions Declarations */

/* Section: Data Type Declarations */
typedef struct{
    PIN_config_t lcd_rs;
    PIN_config_t lcd_en;
    PIN_config_t lcd_data[4];
} lcd_4bit_t;

typedef struct{
    PIN_config_t lcd_rs;
    PIN_config_t lcd_en;
    PIN_config_t lcd_data[8];
} lcd_8bit_t;

/* Section: Function Declarations *//* Section: Function Declarations */

/* 4 BIT MODE  */
Std_ReturnType lcd_4bit_initialize(const lcd_4bit_t *lcd);
Std_ReturnType lcd_4bit_send_command(const lcd_4bit_t *lcd , uint8 command);
Std_ReturnType lcd_4bit_send_char_data(const lcd_4bit_t *lcd , uint8 data);
Std_ReturnType lcd_4bit_send_char_data_pos(const lcd_4bit_t *lcd , uint8 row , uint8 column, uint8 data);
Std_ReturnType lcd_4bit_send_string(const lcd_4bit_t *lcd , uint8 *str);
Std_ReturnType lcd_4bit_send_string_pos(const lcd_4bit_t *lcd  , uint8 row , uint8 column , uint8 *str);
Std_ReturnType lcd_4bit_send_custom_char(const lcd_4bit_t *lcd , uint8 row , uint8 column , 
                                          const uint8 _char[] , uint8 mem_pos);


/* 8 BIT MODE  */
Std_ReturnType lcd_8bit_initialize(const lcd_8bit_t *lcd);
Std_ReturnType lcd_8bit_send_command(const lcd_8bit_t *lcd , uint8 command);
Std_ReturnType lcd_8bit_send_char_data(const lcd_8bit_t *lcd , uint8 data);
Std_ReturnType lcd_8bit_send_char_data_pos(const lcd_8bit_t *lcd , uint8 row , uint8 column, uint8 data);
Std_ReturnType lcd_8bit_send_string(const lcd_8bit_t *lcd , uint8 *str);
Std_ReturnType lcd_8bit_send_string_pos(const lcd_8bit_t *lcd  , uint8 row , uint8 column , uint8 *str);
Std_ReturnType lcd_8bit_send_custom_char(const lcd_8bit_t *lcd , uint8 row , uint8 column , 
                                          const uint8 _char[] , uint8 mem_pos);


Std_ReturnType conv_byte_to_string(uint8 value , uint8 *str);
Std_ReturnType conv_short_to_string(uint16 value , uint8 *str);
Std_ReturnType conv_int_to_string(uint32 value , uint8 *str); 


#endif	/* ECU_LCD_H */

