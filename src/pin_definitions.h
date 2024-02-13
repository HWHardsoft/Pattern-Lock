// pin definitions for different microcontrollerboards
// for AZ-Touch MOD, AZ-Touch MKR and AZ-Touch feather

#if defined(ARDUINO_SAMD_MKRWIFI1010) || defined(ARDUINO_SAMD_MKR1000) // Arduino MKR
  #define TFT_CS   10
  #define TFT_DC   2
  #define TFT_LED  A2 
  #define TOUCH_CS A0
  #define TOUCH_IRQ A7
  #define BEEPER A3

#elif defined(ADAFRUIT_FEATHER_M0) || defined(ADAFRUIT_FEATHER_M0_EXPRESS) || defined(ARDUINO_SAMD_FEATHER_M0)  // Feather M0 w/Radio
  #define TFT_CS   10
  #define TFT_DC   9
  #define TFT_LED  13
  #define TOUCH_CS 6
  #define TOUCH_IRQ 5 
  #define BEEPER 11

#elif defined(ARDUINO_ADAFRUIT_FEATHER_ESP32S3) || (ADAFRUIT_FEATHER_ESP32S3_NOPSRAM)  // ESP32 feather S3 
  #define TFT_CS   10
  #define TFT_DC   9
  #define TFT_LED  13 
  #define TOUCH_CS 6
  #define TOUCH_IRQ 5
  #define BEEPER 11

#elif defined(ARDUINO_ADAFRUIT_FEATHER_ESP32S2) || defined(ARDUINO_NRF52840_FEATHER) || defined(ARDUINO_NRF52840_FEATHER_SENSE)
  #define TFT_CS   10
  #define TFT_DC   9
  #define TFT_LED  13 
  #define TOUCH_CS 6
  #define TOUCH_IRQ 5
  #define BEEPER 11

#elif defined(ARDUINO_FEATHER_ESP32) || (ADAFRUIT_FEATHER_ESP32_V2) // Feather ESP32
  #define TFT_CS   33
  #define TFT_DC   15
  #define TFT_LED  13
  #define TOUCH_CS 32
  #define TOUCH_IRQ 14 
  #define BEEPER  27

#elif defined(ARDUINO_ESP32_THING_PLUS)  // Sparkfun ESP32 THING PLUS
  #define TFT_CS   33
  #define TFT_DC   15
  #define TFT_LED  13
  #define TOUCH_CS 32
  #define TOUCH_IRQ 14 
  #define BEEPER  27
  
#elif defined(ARDUINO_ESP32_DEV)  // ESP32 DEV KITC (AZ-Touch MOD)
  #define TFT_CS   5
  #define TFT_DC   4
  #define TFT_LED  15
  #define TFT_RST  22
  #define TOUCH_CS 14
  #define TOUCH_IRQ 27
  #define BEEPER  21

#elif defined(ARDUINO_ESP8266_WEMOS_D1MINI) || (ARDUINO_ESP8266_WEMOS_D1WROOM02)  // D1 Mini (AZ-Touch MOD) 
  #error "Board currently not supported!"

#elif defined(ARDUINO_SPARKFUN_THINGPLUS_RP2040) // Sparkfun RP2040 THING PLUS
  //#error "Sparkfun RP2040 THING PLUS detected!"
  #define TFT_CS   19
  #define TFT_DC   20
  #define TFT_LED  16

  #define TOUCH_CS 21
  #define TOUCH_IRQ 22 

  #define BEEPER 18

#else  
  #error "Board not supported!"
  
#endif  
 
