// ===================================================================================
// Project:   USB-UART (CH552) Virtual COM Port to control PWM and frequency
// Version:   v1.0
// Year:      2024
// Author:    Cesar Bautista
// License:   http://creativecommons.org/licenses/by-sa/3.0/
// ===================================================================================
//
// Description:
// ------------

// This example demonstrates how to create a virtual COM port using the CH552 microcontroller.
// The virtual COM port is created using the USB CDC protocol.
//
// References:
// -----------
// - CH552-DAPLink: https://github.com/wagiminator/CH552-DAPLink/tree/main
// - Blinkinlabs: https://github.com/Blinkinlabs/ch554_sdcc
// - Deqing Sun: https://github.com/DeqingSun/ch55xduino
// - Ralph Doncaster: https://github.com/nerdralph/ch554_sdcc
// - WCH Nanjing Qinheng Microelectronics: http://wch.cn
// - ARMmbed DAPLink: https://github.com/ARMmbed/DAPLink
// - picoDAP: https://github.com/wagiminator/CH552-picoDAP
//
// Compilation Instructions:
// -------------------------
// - Chip:  CH552
// - Clock: 12 MHz internal
// - Adjust the firmware parameters in src/config.h if necessary.
// - Make sure SDCC toolchain and Python3 with PyUSB is installed.
// - Press BOOT button on the board and keep it pressed while connecting it via USB
//   with your PC.

//



#include "src/config.h"                   // user configurations
#include "src/system.h"                   // system functions
#include "src/gpio.h"                     // for GPIO
#include "src/delay.h"                    // for delays
#include "src/oled_term.h"                // for OLED
#include "src/neo.h"                      // NeoPixel functions
#include "src/usb_cdc.h"                  // for USB-CDC serial
#include <stdio.h>                        // for sprintf
#include <stdint.h>                       // standard integer types
#include <string.h>                       // for memcmp

void USB_interrupt(void);
void USB_ISR(void) __interrupt(INT_NO_USB) {
    USB_interrupt();
}

void change_pwm(int value) {
    char buffer[10];
    PWM_write(PIN_LED, value);
    sprintf(buffer, "PWM changed to %d", value);
    CDC_println(buffer);
}

void change_freq(int value) {
    PWM_set_freq(value);
}

// Función para convertir cadena a entero
int my_atoi(const char* str) {
    int res = 0;
    for (int i = 0; str[i] != '\0'; ++i) {
        if (str[i] >= '0' && str[i] <= '9') {
            res = res * 10 + str[i] - '0';
        } else {
            // Manejar caracteres no numéricos
            return -1;
        }
    }
    return res;
}

void parse_command(char *cmd) {
    CDC_println("Parsing command...");
    CDC_println(cmd);

    if (strncmp(cmd, "pwm", 3) == 0) {
        CDC_println("Detected pwm command");
        int pwm_value = my_atoi(cmd + 3);
        if (pwm_value != -1) {
            change_pwm(pwm_value);
            CDC_println("PWM changed");
        } else {
            CDC_println("Invalid PWM value");
        }
    } else if (strncmp(cmd, "freq", 4) == 0) {
        CDC_println("Detected freq command");
        int freq_value = my_atoi(cmd + 4);
        if (freq_value != -1) {
            change_freq(freq_value);
            CDC_println("Frequency changed");
        } else {
            CDC_println("Invalid frequency value");
        }
    } else {
        CDC_println("Unknown command");
    }
}

// ===================================================================================
// Main Function
// ===================================================================================
void main(void) {
    // Configuración inicial
    CLK_config();
    DLY_ms(5);
    CDC_init();

    PIN_output(PIN_BUZZER);
    PIN_output(PIN_LED);
    PWM_set_freq(100);
    PWM_start(PIN_LED);
    PWM_write(PIN_LED, 0);
    __xdata char buffer[64];
    int index = 0;

    // init cdc starting ...
    CDC_println("I2C Bridge ready");
    for (int i = 0; i < 10; i++) {
        CDC_println("...");
    }
    // init cdc done

    while (1) {
        if (CDC_available()) {
            char c = CDC_read();
            CDC_print("Read character: ");
            CDC_write(c);
            CDC_println("");

            if (c == ';') {
                buffer[index] = '\0'; // Null-terminate the command
                CDC_println("Full command received:");
                CDC_println(buffer);

                // Limpieza de espacios y caracteres no deseados al inicio
                char *start = buffer;
                while (*start == ' ' || *start == '\n' || *start == '\r') {
                    start++;
                }

                parse_command(start);
                index = 0; // Reset buffer index for next command
                memset(buffer, 0, sizeof(buffer)); // Clear buffer
            } else {
                if (c != '\n' && c != '\r') { // Evitar caracteres de nueva línea
                    buffer[index] = c;
                    index++;
                    if (index >= sizeof(buffer)) {
                        index = 0; // Reset index if buffer overflows
                        CDC_println("Buffer overflow, resetting...");
                        memset(buffer, 0, sizeof(buffer)); // Clear buffer
                    }
                }
            }
        }
    }
}
