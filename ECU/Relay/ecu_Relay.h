/* 
 * File:   ecu_Relay.h
 * Author: AhmedSamy
 *
 * Created on August 26, 2023, 1:48 AM
 */

#ifndef ECU_RELAY_H
#define	ECU_RELAY_H

/* Section : Includes */
#include "../../MCAL/GPIO/GPIO.h"

/* Section: Macro Declarations */
#define     RELAY_ON        0x01U
#define     RELAY_OFF       0x00U

/* Section: Macro Functions Declarations */
typedef struct {
    uint8  relay_port : 4 ; 
    uint8  relay_pin  : 3 ;
    uint8  relay_state: 1 ;
} relay_t; 

/* Section: Data Type Declarations */

/* Section: Function Declarations */
Std_ReturnType relay_init( const relay_t * relay );
Std_ReturnType relay_ON( const relay_t * relay );
Std_ReturnType relay_OFF( const relay_t * relay );


#endif	/* ECU_RELAY_H */

