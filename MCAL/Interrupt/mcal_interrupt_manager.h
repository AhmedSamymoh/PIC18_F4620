/* 
 * File:   mcal_interrupt_manager.h
 * Author: AhmedSamy
 *
 * Created on September 27, 2023, 7:18 AM
 */

#ifndef MCAL_INTERRUPT_MANAGER_H
#define	MCAL_INTERRUPT_MANAGER_H

/* ------------- Section : Includes ------------- */
#include "mcal_interrupt_config.h"

/* ------------- Section: Macro Declarations ------------- */

/* ------------- Section: Macro Functions Declarations ------------- */

/* ------------- Section: Data Type Declarations ------------- */

/* ------------- Section: Function Declarations -------------*/

void INT0_ISR(void);
void INT1_ISR(void);
void INT2_ISR(void);



#endif	/* MCAL_INTERRUPT_MANAGER_H */

