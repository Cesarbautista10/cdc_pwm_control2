.. this file is a guide for config pwm and freq of device ch552  


# Bridge CDC Interface to PWM and Freq. 

## 1. Introduction

This is a simple example of how to use the CH552 to control the PWM and frequency of the device.

## 2. Hardware

- CH552

## 3. Software

- sdcc compiler
- ch552.h

## 4. How to use

- Download the code
- Compile the code
- Upload the code to the CH552

## 5. Usage 

- Connect the CH552 to the computer
- Open the serial terminal with the baud rate of 9600

## 6. Instructions

- The CH552 will receive the commands from the serial terminal and will change the PWM and frequency of the device.

```bash
    pwm<0-255>;
    freq<0-30000>;
```
### Example

pwm100;
freq1000;

## 7. License

This code is under GPL v3 license.

