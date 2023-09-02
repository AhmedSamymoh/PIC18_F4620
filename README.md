# *PIC18_F4620*
 my PIC18F4620 drivers journey. Effortlessly integrate microcontroller peripherals. Simplify development with clear documentation and modular code for smooth hardware interaction."

## Layered Architecture

The driver is structured into the following layers:

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


## Contributing
Contributions to Employees_Data are welcome!

#### License
licensed under the MIT License.


