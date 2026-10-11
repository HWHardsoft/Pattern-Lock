/*
 * Pin definitions for AZ-Touch variants and supported controller boards.
 *
 * Manual selection is normally not required; the Arduino board macros are
 * detected automatically.
 *
 * If a generic ESP32 board definition is used and the automatic detection
 * does not match, uncomment ONE of these overrides:
 */
// #define AZTOUCH_FORCE_MOD_ESP32
// #define AZTOUCH_FORCE_FEATHER_ESP32


// -----------------------------------------------------------------------------
// AZ-Touch MKR
// -----------------------------------------------------------------------------
#if defined(ARDUINO_SAMD_MKRWIFI1010) || defined(ARDUINO_SAMD_MKR1000)

  #define TFT_CS      10
  #define TFT_DC       2
  #define TFT_LED     A2
  #define TOUCH_CS    A0
  #define TOUCH_IRQ   A7
  #define BEEPER      A3


// -----------------------------------------------------------------------------
// AZ-Touch Feather - SAMD
// -----------------------------------------------------------------------------
#elif defined(ADAFRUIT_FEATHER_M0) || \
      defined(ADAFRUIT_FEATHER_M0_EXPRESS) || \
      defined(ARDUINO_SAMD_FEATHER_M0)

  #define TFT_CS      10
  #define TFT_DC       9
  #define TFT_LED     13
  #define TOUCH_CS     6
  #define TOUCH_IRQ    5
  #define BEEPER      11


// -----------------------------------------------------------------------------
// AZ-Touch Feather - ESP32-S3
// -----------------------------------------------------------------------------
#elif defined(ARDUINO_ADAFRUIT_FEATHER_ESP32S3) || \
      defined(ADAFRUIT_FEATHER_ESP32S3_NOPSRAM)

  #define TFT_CS      10
  #define TFT_DC       9
  #define TFT_LED     13
  #define TOUCH_CS     6
  #define TOUCH_IRQ    5
  #define BEEPER      11


// -----------------------------------------------------------------------------
// AZ-Touch Feather - ESP32-S2 / nRF52
// -----------------------------------------------------------------------------
#elif defined(ARDUINO_ADAFRUIT_FEATHER_ESP32S2) || \
      defined(ARDUINO_NRF52840_FEATHER) || \
      defined(ARDUINO_NRF52840_FEATHER_SENSE)

  #define TFT_CS      10
  #define TFT_DC       9
  #define TFT_LED     13
  #define TOUCH_CS     6
  #define TOUCH_IRQ    5
  #define BEEPER      11


// -----------------------------------------------------------------------------
// AZ-Touch Feather - classic ESP32 / Feather V2
// -----------------------------------------------------------------------------
#elif defined(AZTOUCH_FORCE_FEATHER_ESP32) || \
      defined(ARDUINO_FEATHER_ESP32) || \
      defined(ADAFRUIT_FEATHER_ESP32_V2)

  #define TFT_CS      33
  #define TFT_DC      15
  #define TFT_LED     13
  #define TOUCH_CS    32
  #define TOUCH_IRQ   14
  #define BEEPER      27


// SparkFun Thing Plus uses the same AZ-Touch Feather pin mapping
#elif defined(ARDUINO_ESP32_THING_PLUS)

  #define TFT_CS      33
  #define TFT_DC      15
  #define TFT_LED     13
  #define TOUCH_CS    32
  #define TOUCH_IRQ   14
  #define BEEPER      27


// -----------------------------------------------------------------------------
// AZ-Touch MOD - ESP32 DevKit
// -----------------------------------------------------------------------------
#elif defined(AZTOUCH_FORCE_MOD_ESP32) || \
      defined(ARDUINO_ESP32_DEV)

  #define TFT_CS       5
  #define TFT_DC       4
  #define TFT_LED     15
  #define TFT_RST     22
  #define TOUCH_CS    14
  #define TOUCH_IRQ   27
  #define BEEPER      21


#elif defined(ARDUINO_ESP8266_WEMOS_D1MINI) || \
      defined(ARDUINO_ESP8266_WEMOS_D1WROOM02)

  #error "Board currently not supported!"


// -----------------------------------------------------------------------------
// SparkFun RP2040 Thing Plus
// -----------------------------------------------------------------------------
#elif defined(ARDUINO_SPARKFUN_THINGPLUS_RP2040)

  #define TFT_CS      19
  #define TFT_DC      20
  #define TFT_LED     16
  #define TOUCH_CS    21
  #define TOUCH_IRQ   22
  #define BEEPER      18

#else

  #error "Board not supported! Select the correct Arduino board or use an AZTOUCH_FORCE_* override in pin_definitions.h."

#endif
