// ===================================================================================
// User configurations
// ===================================================================================

#pragma once

// Pin definitions
#define PIN_BUZZER          P11       // buzzer pin
#define PIN_LED             P34       // LED pin
#define PIN_SDA             P15// P31       // I2C SDA
#define PIN_SCL             P32//P30       // I2C SCL
#define PIN_NEO             P33       // pin connected to NeoPixel
#define NEO_GRB                         // type of pixel: NEO_GRB or NEO_RGB


// USB device descriptor

#define USB_VENDOR_ID       0x1209    // VID (shared www.voti.nl)
#define USB_PRODUCT_ID      0x27DD    // PID (shared CDC)
#define USB_DEVICE_VERSION  0x0100    // v1.0 (BCD-format)

// USB configuration descriptor
#define USB_MAX_POWER_mA    100       // max power in mA 

// #define UART_BAUD         115200
#define UART_BAUD         9600
#define CDC_BAUD          9600
// USB descriptor strings
#define MANUFACTURER_STR    'U','N','T','e','l','e','c','t','r','o','n','i','c','s'
#define PRODUCT_STR         'I','2','C','-','B','r','i','d','g','e'
#define SERIAL_STR          'g','i','t','h','u','b','.','c','o','m','/', \
                            'U','N','T','e','l','e','c','t','r','o','n','i','c','s'
#define INTERFACE_STR       'M','i','c','r','o','H','o','n','i','t', \
                            'o',' ','r','e','v','0','.','0','.','1'
