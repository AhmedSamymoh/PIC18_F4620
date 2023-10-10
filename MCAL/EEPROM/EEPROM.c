/* 
 * File:   EEPROM.c
 * Author: AhmedSamy
 *
 * Created on October 10, 2023, 4:56 AM
 */

#include "EEPROM.h"


/**
 * 
 * @param bAdd
 * @param bData
 * @return 
 */
Std_ReturnType EEPROM_WriteByte(uint16 bAdd , uint8 bData){
    Std_ReturnType ret = E_NOT_OK;
    /* Read the Interrupt status "Disable" , "Enable" */
    uint8 GlobleInterruptStatus = INTCONbits.GIE;
    /* Update the Address Register - bADD = 0 > 0b0000 0011 1111 1111 */ 
    EEADRH = (uint8)( ( (bAdd) >> 8) & 0x03 );
    EEADR = (uint8)( (bAdd) & 0xFF );
    /* Update the data Register */
    EEDATA = bData;
    /* Select Access data EEPROM memory  */
    EECON1bits.EEPGD = ACCESS_EEPROM_PROGRAM_MEMORY;
    EECON1bits.CFGS = ACCESS_EEPROM_FLASH_MEMORY;

    /* Allows write cycles to Flash program/data EEPROM */
    EECON1bits.WREN = ALLOW_WRITE_CYCLES_FLASH_EEPROM;
    /* Disable Global Interrupt */
    INTERRUPT_GlobleaInterrupt_HIGH_Disable();
    /* Write Sequence : 0x55 - > 0xAA */
    EECON2 = 0x55;
    EECON2 = 0xAA;
 
    /* Initiates a data EEPROM Erase/Write Cycle */
    EECON1bits.WR = INITIATE_DATA_EEPROM_WRITE_ERASE;
    while(EECON1bits.WR);
    /* Inhibites write cycle to Flash Program/Data EEPROM */
    EECON1bits.WREN = INHABIT_WRITE_CYCLES_FLASH_EEPROM;
    /* Restore the Interrupt Status "Enable or Disable" */
    INTCONbits.GIE = GlobleInterruptStatus ;
    ret = E_OK;
}

/** 
 * 
 * @param bAdd
 * @param bData
 * @return 
 */
Std_ReturnType EEPROM_ReadByte(uint16 bAdd , uint8 *bData){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL = bData){
        ret = E_NOT_OK;
    }else{
        
    }
    
    ret = E_OK;
}

