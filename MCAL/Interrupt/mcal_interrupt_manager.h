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
#define LOW             0
#define HIGH            1
/* ------------- Section: Macro Functions Declarations ------------- */

/* ------------- Section: Data Type Declarations ------------- */

/* ------------- Section: Function Declarations -------------*/

void INT0_ISR(void);
void INT1_ISR(void);
void INT2_ISR(void);
void RB4_ISR(uint8 RBx_Source);
void RB5_ISR(uint8 RBx_Source);
void RB6_ISR(uint8 RBx_Source);
void RB7_ISR(uint8 RBx_Source);



#endif	/* MCAL_INTERRUPT_MANAGER_H */

