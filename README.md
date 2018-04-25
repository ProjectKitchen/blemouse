#BLE Mouse

this repository contains a firmware of a BLE mouse, that can be controlled by head movements.
The head movments are detected by an 6dof IMU. 
 
The yaw axis of the head controls the y-axis of the mouse and the 
pitch axis of the head controls the x-axis of the mouse on the screen. 


Hardware

Metawear C Board
based on Nordic nRF51822 32-bit ARM® Cortex™ M0 CPU
with a BMI160 6 Dof IMU from Bosch Sensortec
https://mbientlab.com/product/metawearc/

Nordic Semiconductors - nRF51 DK used for flashing the Metawear C Board
https://www.nordicsemi.com/eng/Products/nRF51-DK

Firmware 

to flash a custom firmware to the Metawear C board the nRF51-DK is used:
https://devzone.nordicsemi.com/blogs/803/programming-and-debugging-custom-nrf5x-devices/
https://devzone.nordicsemi.com/question/80853/external-programming-using-nrf52-dk/

nrf5 Software Development Kit (SDK)

the firmware is based on the HID mouse application of the nRF5 SDK 12.3.4 
https://www.nordicsemi.com/eng/nordic/download_resource/54291/56/40822464/32925

and the driver for the BMI160 from Bosch Sensortec:
https://github.com/BoschSensortec/BMI160_driver

Bootloader

in the folder "bootloader_secure" a bootloader firmware is included.
the keys for security already have been generated. 
check the tutorial how to use the bootloader:
https://devzone.nordicsemi.com/b/blog/posts/getting-started-with-nordics-secure-dfu-bootloader 

Setup Project 

- Download and Install nRF5 SDK 12.3.4
- Setup IDE (https://devzone.nordicsemi.com/tutorials/7/) 
- Copy ble_mouse/ folder to examples/ble_peripheral/ 






