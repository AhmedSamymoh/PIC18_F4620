# PIC18_F4620
 my PIC18F4620 drivers journey. Effortlessly integrate microcontroller peripherals. Simplify development with clear documentation and modular code for smooth hardware interaction."

## Layered Architecture

The project is structured into the following layers:

### [MCAL (Microcontroller Abstraction Layer)](MCAL/)

This layer provides low-level hardware abstraction for the PIC18 microcontroller.

- [GPIO](MCAL/GPIO/): General-Purpose Input/Output module.

### [ECU (Electronic Control Unit) Layer](ECU/)

This layer contains Electronic Control Units for various hardware components.

- [BUTTON](ECU/BUTTON/): Button control module.
- [DC_MOTOR](ECU/DC_MOTOR/): DC motor control module.
- [LED](ECU/LED/): LED control module.
- [RELAY](ECU/RELAY/): Relay control module.
- [SEVEN_SEGMENTS](ECU/SEVEN_SEGMENTS/): Seven-segment display control module.

### Application Layer

- [application.c](application.c): Main application code file.
- [application.h](application.h): Header file for the application code.
- [Apps](Apps/): Directory containing application-specific modules.

## Modules

Each module within the layers has its own code files and configuration.

### [BUTTON Module](ECU/BUTTON/)

- [ecu_button.c](ECU/BUTTON/ecu_button.c): Button control implementation.
- [ecu_button.h](ECU/BUTTON/ecu_button.h): Header file for button control.
- [ecu_button_config.h](ECU/BUTTON/ecu_button_config.h): Configuration file for button control.

### [DC_MOTOR Module](ECU/DC_MOTOR/)

- [ecu_dc_motor.c](ECU/DC_MOTOR/ecu_dc_motor.c): DC motor control implementation.
- [ecu_dc_motor.h](ECU/DC_MOTOR/ecu_dc_motor.h): Header file for DC motor control.
- [ecu_dc_motor_cfg.h](ECU/DC_MOTOR/ecu_dc_motor_cfg.h): Configuration file for DC motor control.

### [LED Module](ECU/LED/)

- [ECU_LEC_Config.h](ECU/LED/ECU_LEC_Config.h): LED configuration file.
- [ECU_LED.c](ECU/LED/ECU_LED.c): LED control implementation.
- [ECU_LED.h](ECU/LED/ECU_LED.h): Header file for LED control.

### [RELAY Module](ECU/RELAY/)

- [ecu_Relay.c](ECU/RELAY/ecu_Relay.c): Relay control implementation.
- [ecu_Relay.h](ECU/RELAY/ecu_Relay.h): Header file for relay control.

### [SEVEN_SEGMENTS Module](ECU/SEVEN_SEGMENTS/)

- [ecu_seven_segment.c](ECU/SEVEN_SEGMENTS/ecu_seven_segment.c): Seven-segment display control implementation.
- [ecu_seven_segment.h](ECU/SEVEN_SEGMENTS/ecu_seven_segment.h): Header file for seven-segment display control.
- [ecu_seven_segment_cfg.h](ECU/SEVEN_SEGMENTS/ecu_seven_segment_cfg.h): Configuration file for seven-segment display control.

### [GPIO Module](MCAL/GPIO/)

- [GPIO.c](MCAL/GPIO/GPIO.c): GPIO control implementation.
- [GPIO.h](MCAL/GPIO/GPIO.h): Header file for GPIO control.
- [GPIO_Config.h](MCAL/GPIO/GPIO_Config.h): Configuration file for GPIO.

## Build and Usage

Please refer to the specific module's README file within their respective directories for detailed build instructions and usage details.

## License

This project is licensed under the [LICENSE](LICENSE) file found in the root directory.

## Contributors

- List contributors and maintainers here.

