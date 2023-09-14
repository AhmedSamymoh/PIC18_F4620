/* 
 * File:   application.c
 * Author: AhmedElnozahy
 *
 * Created on August 3, 2023, 4:54 PM
 */
#include "application.h"


Std_ReturnType ret = E_NOT_OK;
uint8 keypad_val = 0 ;
uint8 time = 0 ;
uint8 time_str[4];
uint8 customChar1[] = {0x0E , 0X0A , 0X11 , 0X11 , 0X11 , 0X1F , 0X00};
uint8 customChar2[] = {0x0E , 0X0A , 0X11 , 0X11 , 0X1F , 0X1F , 0X00};
uint8 customChar3[] = {0x0E , 0X0A , 0X11 , 0X1F , 0X1F , 0X1F , 0X00};
uint8 customChar4[] = {0x0E , 0X0A , 0X1F , 0X1F , 0X1F , 0X1F , 0X00};
uint8 customChar5[] = {0x0E , 0X0A , 0X1F , 0X1F , 0X1F , 0X1F , 0X00};
uint8 customChar6[] = {0x0E , 0X0E , 0X1F , 0X1F , 0X1F , 0X1F , 0X00};


void loading()
{
    ret = lcd_4bit_send_string_pos(&lcd_1 ,1,5,"Loading");
    __delay_ms(250);
    for(int i = 0 ; i < 4 ; i++)
    {
        ret = lcd_4bit_send_char_data(&lcd_1 , '.');
        __delay_ms(250);

    }
    ret = lcd_4bit_send_string_pos(&lcd_1 ,1,5,"            ");
 
}
void battery(void)
{   
    ret = lcd_4bit_send_command(&lcd_1 , _LCD_CLEAR); 
    ret = lcd_4bit_send_string_pos(&lcd_1 ,1,3,"Charging Battery");
    for(int i = 0 ; i < 100 ; i++)
    {
        ret = conv_byte_to_string(i ,time_str );
        ret = lcd_4bit_send_string_pos(&lcd_1 ,3,9, time_str);
        ret = lcd_4bit_send_string_pos(&lcd_1 ,3,13, "%");
        __delay_ms(250);

    }
    time_str[4] = "000";
    for(int i = 0 ; i < 12 ; i++)
    {
        ret = lcd_4bit_send_command(&lcd_1 , _LCD_CLEAR);
        __delay_ms(250);

        ret = lcd_8bit_send_command(&lcd_1 , (0x94 + 2) );
                __delay_ms(250);
 
        ret = lcd_4bit_send_string_pos(&lcd_1 ,3,3, "BATTERY CHARGED !!");
        __delay_ms(250);
        ret = lcd_8bit_send_custom_char(&lcd_2 , 4, 10 ,customChar4 , 0);


    }
   

}

int main(){
    Std_ReturnType ret = E_NOT_OK;
    application_intialize();
    
    while(1)
    {
        //battery();
        ret = lcd_8bit_send_custom_char(&lcd_2 , 4 ,10 ,customChar1 , 0);
        __delay_ms(250);
        ret = lcd_8bit_send_custom_char(&lcd_2 , 4 ,10 ,customChar2 , 0);
        __delay_ms(250);
        ret = lcd_8bit_send_custom_char(&lcd_2 , 4 ,10 ,customChar3 , 0);
        __delay_ms(250);
        ret = lcd_8bit_send_custom_char(&lcd_2 , 4 ,10 ,customChar4 , 0);
        __delay_ms(250);


    } 
    return (EXIT_SUCCESS);
}

void application_intialize(void){
    Std_ReturnType ret = E_NOT_OK;
    ecu_layer_intialize();

}