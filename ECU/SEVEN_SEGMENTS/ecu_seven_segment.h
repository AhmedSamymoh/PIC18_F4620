/* 
 * File:   ecu_seven_segment.h
 * Author: AhmedSamy
 *
 * Created on August 31, 2023, 7:50 PM
 */

#ifndef ECU_SEVEN_SEGMENT_H
#define	ECU_SEVEN_SEGMENT_H

/* Section : Includes */
#include "../../MCAL/GPIO/GPIO.h"
#include "ecu_seven_segment_cfg.h"

/* Section: Macro Declarations */
#define SEGMENT_PIN0    0 
#define SEGMENT_PIN1    1 
#define SEGMENT_PIN2    2 
#define SEGMENT_PIN3    3 

/* Section: Macro Functions Declarations */

/* Section: Data Type Declarations */
typedef enum{
    SEGMENT_COMMON_ANODE,
    SEGMENT_COMMON_CATHODE
}segment_type_t;

typedef struct{
    PIN_config_t segments_pins[4];
    segment_type_t seven_segment_mode;
}segment_pin_t;

 
/* Section: Function Declarations */
Std_ReturnType seven_segment_init(const segment_pin_t * segment);
Std_ReturnType seven_segment_write_number(const segment_pin_t * segment , uint8 number);



#endif	/* ECU_SEVEN_SEGMENT_H */

