/* 
 * File:   EEPROM.h
 * Author: AhmedSamy
 *
 * Created on October 10, 2023, 4:56 AM
 */

#ifndef EEPROM_H
#define	EEPROM_H

/*--------------------------- Section: Includes ----------------------------*/
#include "../compiler.h"
#include "../std_types.h"
#include "../../MCAL/Interrupt/mcal_internal_interrupt.h"

/*---------------------- Section: Macro Declarations -----------------------*/
#define ACCESS_FLASH_PROGRAM_MEMORY             1
#define ACCESS_EEPROM_PROGRAM_MEMORY            0

#define ACCESS_CONFIG_REGISTERS                 1
#define ACCESS_EEPROM_FLASH_MEMORY              0

#define ALLOW_WRITE_CYCLES_FLASH_EEPROM         1
#define INHABIT_WRITE_CYCLES_FLASH_EEPROM       0

#define INITIATE_DATA_EEPROM_WRITE_ERASE        1
#define INITIATE_DATA_EEPROM_READ               0
/*----------------- Section: Macro Functions Declarations ------------------*/

/*-------------------- Section: Data Type Declarations -------------------- */

/*--------------- Section: Software Interfaces Declarations --------------- */
Std_ReturnType EEPROM_WriteByte(uint16 bAdd , uint8 bData);
Std_ReturnType EEPROM_ReadByte(uint16 bAdd , uint8 *bData);



#endif	/* EEPROM_H */

