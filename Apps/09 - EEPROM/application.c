/* 
 * File:   application.c
 * Author: AhmedElnozahy
 *
 * Created on August 3, 2023, 4:54 PM
 */
#include "application.h"

Std_ReturnType ret = E_NOT_OK;
int val = 0 , read = 0;

int main(){
    
    application_intialize();
    ret = EEPROM_WriteByte(0x3ff , 0);
    ret = EEPROM_WriteByte(0x0260 , 1234);
    while(1)
    {
        ret = EEPROM_WriteByte(0x3ff , val++);
        __delay_ms(1000);
        ret = EEPROM_ReadByte(0x3ff , &read);
        __delay_ms(1000);

    } 
    return (EXIT_SUCCESS);
}

void application_intialize(void){
    Std_ReturnType ret = E_NOT_OK;
    //ecu_layer_intialize();

} 