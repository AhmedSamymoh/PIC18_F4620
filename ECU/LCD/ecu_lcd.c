/* 
 * File:   ecu_lcd.h
 * Author: AhmedSamy
 *
 * Created on September 13, 2023, 11:03 PM
 */

#include "ecu_lcd.h"

#define _XTAL_FREQ 8000000UL

/* Helper Functions Declarations */
static Std_ReturnType lcd_send_4bits(const lcd_4bit_t *lcd  , uint8 _data_command);
static Std_ReturnType lcd_send_4bits_send_enable_sig(const lcd_4bit_t *lcd  );
static Std_ReturnType lcd_send_8bits_send_enable_sig(const lcd_8bit_t *lcd  );
static Std_ReturnType lcd_4bit_Set_Cursor(const lcd_4bit_t *lcd , uint8 raw , uint8 column );
static Std_ReturnType lcd_8bit_Set_Cursor(const lcd_8bit_t *lcd , uint8 raw , uint8 column );


/********************************************************************************/
/*****************************    4 BIT MODE    *********************************/
/********************************************************************************/

/**
 * @brief Initialize the pins of @LCD for 4 bit configuration
 * @param lcd pointer to the LCD's pins configuration @lcd_4bit_t
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType lcd_4bit_initialize(const lcd_4bit_t *lcd){
    
    Std_ReturnType ret = E_OK;
    
    uint8 l_data_pins_Counter = 0;
    if((NULL == lcd) ){ //validation
        ret = E_NOT_OK;
    }else{
        /*Enable Pins to be Output pins*/
        ret = gpio_pin_init(&(lcd->lcd_rs));
        ret = gpio_pin_init(&(lcd->lcd_en));
        for(l_data_pins_Counter = 0 ; l_data_pins_Counter < 4 ; l_data_pins_Counter++ ){
            ret = gpio_pin_init(&(lcd->lcd_data[l_data_pins_Counter]));
        }
        __delay_ms(20);
        ret = lcd_4bit_send_command(lcd , _LCD_8BIT_MODE_2_LINE);
        __delay_ms(5);
        ret = lcd_4bit_send_command(lcd , _LCD_8BIT_MODE_2_LINE);
        __delay_us(150);
        ret = lcd_4bit_send_command(lcd , _LCD_8BIT_MODE_2_LINE);
        
        
        ret = lcd_4bit_send_command(lcd , _LCD_CLEAR);
        ret = lcd_4bit_send_command(lcd , _LCD_RETURN_HOME);
        ret = lcd_4bit_send_command(lcd , _LCD_ENTRY_MODE);
        ret = lcd_4bit_send_command(lcd , _LCD_CURSOR_OFF_DISPLAY_ON);
        ret = lcd_4bit_send_command(lcd , _LCD_4BIT_MODE_2_LINE);
        
        ret = lcd_4bit_send_command(lcd , 0x80);
       
    }   
    return ret;
}

Std_ReturnType lcd_4bit_send_command(const lcd_4bit_t *lcd , uint8 command){
    Std_ReturnType ret = E_OK;
    if((NULL == lcd) ){ //validation
        ret = E_NOT_OK;
    }else{
        /*to Write in The Instruction Register (IR)*/
        ret = gpio_pin_write_logic(&(lcd->lcd_rs) , GPIO_LOW); 
        /*Sending Higher 4 bits*/ 
        ret = lcd_send_4bits(lcd , command >> 4 ); 
        /*Enable*/
        lcd_send_4bits_send_enable_sig(lcd);
        
        /*Sending LOWER 4 bits*/ 
        ret = lcd_send_4bits(lcd , command ); 
        /*Enable*/
        lcd_send_4bits_send_enable_sig(lcd);
         
    }   
    return ret;
    
}

Std_ReturnType lcd_4bit_send_char_data(const lcd_4bit_t *lcd , uint8 data){
    Std_ReturnType ret = E_OK;
    if((NULL == lcd) ){ //validation
        ret = E_NOT_OK;
    }else{
        /*to Write in The Data Register (DR)*/
        ret = gpio_pin_write_logic(&(lcd->lcd_rs) , GPIO_HIGH); 
        
        /*Sending Higher 4 bits*/ 
        ret = lcd_send_4bits(lcd , data >> 4 ); 
        /*Enable*/
        lcd_send_4bits_send_enable_sig(lcd);
        
        /*Sending LOWER 4 bits*/ 
        ret = lcd_send_4bits(lcd , data ); 
        /*Enable*/
        lcd_send_4bits_send_enable_sig(lcd);
    }   
    return ret;
    
}

Std_ReturnType lcd_4bit_send_char_data_pos(const lcd_4bit_t *lcd , uint8 row , uint8 column, uint8 data){
    
    Std_ReturnType ret = E_OK;
    if((NULL == lcd) ){ //validation
        ret = E_NOT_OK;
    }else{
        ret = lcd_4bit_Set_Cursor(lcd , row , column);
        lcd_4bit_send_char_data(lcd , data);
    }   
    return ret;
}

Std_ReturnType lcd_4bit_send_string(const lcd_4bit_t *lcd , uint8 *str){
    
    Std_ReturnType ret = E_OK;
    if((NULL == lcd) ){ //validation
        ret = E_NOT_OK;
    }else{
        while(*str){
            ret = lcd_4bit_send_char_data(lcd , *str++ );
        }
    }   
    return ret;
}

Std_ReturnType lcd_4bit_send_string_pos(const lcd_4bit_t *lcd  , uint8 row , uint8 column , uint8 *str){
    Std_ReturnType ret = E_OK;
    if((NULL == lcd) ){ //validation
        ret = E_NOT_OK;
    }else{
        ret = lcd_4bit_Set_Cursor(lcd , row , column );
        while(*str){
            ret = lcd_4bit_send_char_data(lcd , *str++ );
        }
    }   
    return ret;
    
}

Std_ReturnType lcd_4bit_send_custom_char(const lcd_4bit_t *lcd , uint8 row , uint8 column , 
                                          const uint8 _char[] , uint8 mem_pos){
    
    Std_ReturnType ret = E_OK;
    uint8 l_counter = 0 ;
    if((NULL == lcd) ){ //validation
        ret = E_NOT_OK;
    }else{
        ret = lcd_4bit_send_command(lcd , (_LCD_CGRAM_START + (mem_pos * 8)));
        for(l_counter = 0 ; l_counter < 7 ; l_counter++)
        {
            ret = lcd_4bit_send_char_data(lcd ,_char[l_counter] );
        }
        ret = lcd_4bit_send_char_data_pos(lcd , row , column , mem_pos);
    }   
    return ret;
    
}


/********************************************************************************/
/*****************************    8 BIT MODE    *********************************/
/********************************************************************************/

Std_ReturnType lcd_8bit_initialize(const lcd_8bit_t *lcd){
     Std_ReturnType ret = E_OK;
    
    uint8 l_data_pins_Counter = 0;
    if((NULL == lcd) ){ //validation
        ret = E_NOT_OK;
    }else{
        ret = gpio_pin_init(&(lcd->lcd_rs));
        ret = gpio_pin_init(&(lcd->lcd_en));
        for(l_data_pins_Counter = 0 ; l_data_pins_Counter < 8 ; l_data_pins_Counter++ ){
            ret = gpio_pin_init(&(lcd->lcd_data[l_data_pins_Counter]));
        }
         __delay_ms(20);
        ret = lcd_8bit_send_command(lcd , _LCD_8BIT_MODE_2_LINE);
        __delay_ms(5);
        ret = lcd_8bit_send_command(lcd , _LCD_8BIT_MODE_2_LINE);
        __delay_us(150);
        ret = lcd_8bit_send_command(lcd , _LCD_8BIT_MODE_2_LINE);
        
        
        ret = lcd_8bit_send_command(lcd , _LCD_CLEAR);
        ret = lcd_8bit_send_command(lcd , _LCD_RETURN_HOME);
        ret = lcd_8bit_send_command(lcd , _LCD_ENTRY_MODE);
        ret = lcd_8bit_send_command(lcd , _LCD_CURSOR_OFF_DISPLAY_ON);
        ret = lcd_8bit_send_command(lcd , _LCD_8BIT_MODE_2_LINE);
        
        ret = lcd_8bit_send_command(lcd , 0x80);
    }   
    return ret;
    
}

Std_ReturnType lcd_8bit_send_command(const lcd_8bit_t *lcd , uint8 command){
    Std_ReturnType ret = E_OK;
    uint8 l_pin_counter = 0 ;
    
    if((NULL == lcd) ){ //validation
        ret = E_NOT_OK;
    }else{
        /*to Write in The Instruction Register (IR)*/
        ret = gpio_pin_write_logic(&(lcd->lcd_rs) , GPIO_LOW); 
        
        for(l_pin_counter = 0 ; l_pin_counter < 8 ; l_pin_counter++){
            ret = gpio_pin_write_logic(&(lcd->lcd_data[l_pin_counter]) , ((command >> l_pin_counter) & (uint8)0x01 ));
        }
        /*Enable*/
        lcd_send_8bits_send_enable_sig(lcd);
    }   
    return ret;
    
}

Std_ReturnType lcd_8bit_send_char_data(const lcd_8bit_t *lcd , uint8 data){
    Std_ReturnType ret = E_OK;
    uint8 l_pin_counter = 0 ;

    if((NULL == lcd) ){ //validation
        ret = E_NOT_OK;
    }else{
        /*to Write in The Data Register (DR)*/
        ret = gpio_pin_write_logic(&(lcd->lcd_rs) , GPIO_HIGH); 
        for(l_pin_counter = 0 ; l_pin_counter < 8 ; l_pin_counter++){
            ret = gpio_pin_write_logic(&(lcd->lcd_data[l_pin_counter]) , ((data >> l_pin_counter) & (uint8)0x01 ));
        }
        /*Enable*/
        lcd_send_8bits_send_enable_sig(lcd);
    }   
    return ret;
    
}

Std_ReturnType lcd_8bit_send_char_data_pos(const lcd_8bit_t *lcd , uint8 row , uint8 column, uint8 data){
    Std_ReturnType ret = E_OK;
    if((NULL == lcd) ){ //validation
        ret = E_NOT_OK;
    }else{
        ret = lcd_8bit_Set_Cursor(lcd , row , column);
        ret = lcd_8bit_send_char_data(lcd , data );
    }   
    return ret;
    
}

Std_ReturnType lcd_8bit_send_string(const lcd_8bit_t *lcd , uint8 *str){
    Std_ReturnType ret = E_OK;
    if((NULL == lcd) ){ //validation
        ret = E_NOT_OK;
    }else{
        while(*str){
            ret = lcd_8bit_send_char_data(lcd , *str++ );
        }
    }   
    return ret;
    
}

Std_ReturnType lcd_8bit_send_string_pos(const lcd_8bit_t *lcd  , uint8 row , uint8 column , uint8 *str){
    Std_ReturnType ret = E_OK;
    if((NULL == lcd) ){ //validation
        ret = E_NOT_OK;
    }else{
        ret = lcd_8bit_Set_Cursor(lcd , row , column);
        while(*str){
            ret = lcd_8bit_send_char_data(lcd , *str++ );
        }
    }   
    return ret;
}

Std_ReturnType lcd_8bit_send_custom_char(const lcd_8bit_t *lcd , uint8 row , uint8 column ,
                                          const uint8 _char[] , uint8 mem_pos){
    Std_ReturnType ret = E_OK;
    uint8 l_counter = 0 ;
    if((NULL == lcd) ){ //validation
        ret = E_NOT_OK;
    }else{
        ret = lcd_8bit_send_command(lcd , (_LCD_CGRAM_START + (mem_pos * 8)));
        for(l_counter = 0 ; l_counter < 7 ; l_counter++)
        {
            ret = lcd_8bit_send_char_data(lcd ,_char[l_counter] );
        }
        ret = lcd_8bit_send_char_data_pos(lcd , row , column , mem_pos);
    }   
    return ret;
    
}

/*****************************    Helper Functions    *********************************/

Std_ReturnType conv_uint8_to_string(uint8 value , uint8 *str){
    
    Std_ReturnType ret = E_OK;
    if((NULL == str) ){ //validation
        ret = E_NOT_OK;
    }else{
        memset(str , '\0' , 4);
        sprintf(str , "%i" , value);        
    }   
    return ret;
}

Std_ReturnType conv_uint16_to_string(uint16 value , uint8 *str){
    Std_ReturnType ret = E_OK;
    if((NULL == str) ){ //validation
        ret = E_NOT_OK;
    }else{
        memset(str , '\0' , 6);
        sprintf(str , "%i" , value);     
    }   
    return ret;
}

Std_ReturnType conv_uint32_to_string(uint32 value , uint8 *str){
    Std_ReturnType ret = E_OK;
    if((NULL == str) ){ //validation
        ret = E_NOT_OK;
    }else{
        memset(str , '\0' , 11);
        sprintf(str , "%i" , value);  
    }   
    return ret;    
    
}

Std_ReturnType lcd_send_4bits(const lcd_4bit_t *lcd  , uint8 _data_command){
     Std_ReturnType ret = E_OK;
    if((NULL == lcd) ){ //validation
        ret = E_NOT_OK;
    }else{
        ret = gpio_pin_write_logic(&(lcd->lcd_data[0]) , ( (_data_command >> 0) & (uint8)0x01 ) );
        ret = gpio_pin_write_logic(&(lcd->lcd_data[1]) , ( (_data_command >> 1) & (uint8)0x01 ) );
        ret = gpio_pin_write_logic(&(lcd->lcd_data[2]) , ( (_data_command >> 2) & (uint8)0x01 ) );
        ret = gpio_pin_write_logic(&(lcd->lcd_data[3]) , ( (_data_command >> 3) & (uint8)0x01 ) );
    }   
    return ret; 
}

/*Enable Signal to latch the data in Data Register or Instruction Register*/
Std_ReturnType lcd_send_4bits_send_enable_sig(const lcd_4bit_t *lcd  ){
     Std_ReturnType ret = E_OK;
    if((NULL == lcd) ){ //validation
        ret = E_NOT_OK;
    }else{
        ret = gpio_pin_write_logic(&(lcd->lcd_en) , GPIO_HIGH );
        __delay_us(5);
        ret = gpio_pin_write_logic(&(lcd->lcd_en) , GPIO_LOW );
    }   
    return ret; 
}


/*Enable Signal to latch the data in Data Register or Instruction Register*/
Std_ReturnType lcd_send_8bits_send_enable_sig(const lcd_8bit_t *lcd  ){
    Std_ReturnType ret = E_OK;
    if((NULL == lcd) ){ //validation
        ret = E_NOT_OK;
    }else{
        ret = gpio_pin_write_logic(&(lcd->lcd_en) , GPIO_HIGH );
        __delay_us(5);
        ret = gpio_pin_write_logic(&(lcd->lcd_en) , GPIO_LOW );
    }   
    return ret; 
}


Std_ReturnType lcd_8bit_Set_Cursor(const lcd_8bit_t *lcd , uint8 raw , uint8 column ){
    Std_ReturnType ret = E_OK;
    column--;
    if((NULL == lcd) ){ //validation
        ret = E_NOT_OK;
    }else{
        switch(raw)
        {
            case ROW1 : ret = lcd_8bit_send_command(lcd , (0x80 + column) ); break; //Start address for ROW1 + Column
            case ROW2 : ret = lcd_8bit_send_command(lcd , (0xC0 + column) ); break; //Start address for ROW2 + Column
            case ROW3 : ret = lcd_8bit_send_command(lcd , (0x94 + column) ); break; //Start address for ROW3 + Column
            case ROW4 : ret = lcd_8bit_send_command(lcd , (0xD4 + column) ); break; //Start address for ROW4 + Column
            default : ;
        }
    }   
    return ret; 
}
Std_ReturnType lcd_4bit_Set_Cursor(const lcd_4bit_t *lcd , uint8 raw , uint8 column ){
    Std_ReturnType ret = E_OK;
    column--;
    if((NULL == lcd) ){ //validation
        ret = E_NOT_OK;
    }else{
        switch(raw)
        {
            case ROW1 : ret = lcd_4bit_send_command(lcd , (0x80 + column) ); break; //Start address for ROW1 + Column
            case ROW2 : ret = lcd_4bit_send_command(lcd , (0xC0 + column) ); break; //Start address for ROW2 + Column
            case ROW3 : ret = lcd_4bit_send_command(lcd , (0x94 + column) ); break; //Start address for ROW3 + Column
            case ROW4 : ret = lcd_4bit_send_command(lcd , (0xD4 + column) ); break; //Start address for ROW4 + Column
            default : ;
        }
    }   
    return ret; 
}
