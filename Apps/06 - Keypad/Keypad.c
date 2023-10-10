 
  File   application.c
  Author AhmedElnozahy
 
  Created on August 3, 2023, 454 PM
 /*
#include application.h

/*
Std_ReturnType ret = E_NOT_OK;
uint8 keypad_val = 0 ;

int main(){
    Std_ReturnType ret = E_NOT_OK;
    application_intialize();
    while(1)
    {
        ret = keypad_get_value(&keypad1 , &keypad_val);
        switch(keypad_val)
        {
            case '1'
                ret = seven_segment_write_number(&seg1 , 1);
                break;
            case '2'
                ret = seven_segment_write_number(&seg1 , 2);
                break;
            case '3'
                ret = seven_segment_write_number(&seg1 , 3);
                break;
            case '4'
                ret = seven_segment_write_number(&seg1 , 4);
                break;
            case '5'
                ret = seven_segment_write_number(&seg1 , 5);
                break;
            case '6'
                ret = seven_segment_write_number(&seg1 , 6);
                break;
            case '7'
                ret = seven_segment_write_number(&seg1 , 7);
                break;
            case '8'
                ret = seven_segment_write_number(&seg1 , 8);
                break;
            case '9'
                ret = seven_segment_write_number(&seg1 , 9);
                break;
            default 
                break;
        }

    } 
    return (EXIT_SUCCESS);
}

void application_intialize(void){
    Std_ReturnType ret = E_NOT_OK;
    ecu_layer_intialize();

}*/