/*
 *  Application note: Simple Pattern Lock for AZ-Touch MKR and Feather 
 *  Version 1.0
 *  Copyright (C) 2024  Hartmut Wendt  www.zihatec.de
 *  
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/   

 

/*______Import Libraries_______*/
#include <Arduino.h>
#include <SPI.h>
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"
#include <XPT2046_Touchscreen.h>
#include <Fonts/FreeSans9pt7b.h>
#include <Fonts/FreeSansBold9pt7b.h>
#include <Fonts/FreeSansBold24pt7b.h>

#include "usergraphics.h"
#include "pin_definitions.h"

/*______End of Libraries_______*/



/*____Calibrate Touchscreen_____*/
#define MINPRESSURE 5      // minimum required force for touch event
#define TS_MINX 370
#define TS_MINY 470
#define TS_MAXX 3700
#define TS_MAXY 3600

#define touch_yellow_header // ili9341 touch screen with yellow header
/*______End of Calibration______*/


/*___Pattern Lock spezific definitions___*/
// position and numbering of pattern points
// 1 2 3
// 4 5 6
// 7 8 9
// Examples:
//#define pattern_OK (int[]){1, 5, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,}  // diagonal line from top left corner to lower right corner
#define pattern_OK (int[]){1, 4, 7, 8, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,}  // L Shape pattern (starting on upper left point)
//#define pattern_OK (int[]){7, 4, 1, 5, 3, 6, 9, 0, 0, 0, 0, 0, 0, 0, 0,}  // M Shape pattern (starting on lower left point)

#define max_points 15 //maximum count of points for a pattern


// Point positions 
#define POINT_X_POS (int[]){40, 120, 200, 40, 120, 200, 40, 120, 200}
#define POINT_Y_POS (int[]){80, 80, 80, 160, 160, 160, 240, 240, 240}



/*___End of Keylock spezific definitions___*/

#if defined(ARDUINO_ESP32_DEV)  // ESP32 DEV KITC (AZ-Touch MOD only)
  Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_RST);
#else  
  Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);
#endif
  
XPT2046_Touchscreen touch(TOUCH_CS, TOUCH_IRQ);

int X,Y;
int p_old = 0;
int point_counter = 0;
int detected_pattern[max_points];
char action;
boolean result = false;
bool Touch_pressed = false;
TS_Point p;



void setup() {
  Serial.begin(115200); //Use serial monitor for debugging

  pinMode(TFT_LED, OUTPUT); // define as output for backlight control
  digitalWrite(TFT_LED, HIGH); // turn backlight off; 

  Serial.println("Init TFT and Touch...");
  tft.begin();
  touch.begin();

  Serial.print("tftx ="); Serial.print(tft.width()); Serial.print(" tfty ="); Serial.println(tft.height());
  tft.fillScreen(ILI9341_BLACK);
  
  IntroScreen();
  digitalWrite(TFT_LED, LOW);    // LOW to turn backlight on; 
  delay(1500);

  // draw screen for pattern input
  drawlockScreen(); 
  

  //sound configuration
  #if defined(ESP32) 
    ledcSetup(0,1E5,12);
    ledcAttachPin(BEEPER,0);
  #endif

   Serial.println("Initialization finished!");
   
}

void loop() {
  // check touch screen for new events
  if (Touch_Event()== true) {  
    X = p.y; Y = p.x;
    Touch_pressed = true;
    EnterPattern();
    
  } else {
    if (Touch_pressed) {
      if (ComparePattern()) {
        Serial.println("Pattern OK");
        Granted_Screen();
      } else {
        Serial.println("Pattern not equal");
        Denied_Screen();
      }
      p_old = 0;
      point_counter = 0;
      drawlockScreen();
    }
    Touch_pressed = false;
  }

  
  delay(20);
  sound(0);  // buzzer off
 
}


/********************************************************************//**
 * @brief     detects a touch event and converts touch data 
 * @param[in] None
 * @return    boolean (true = touch pressed, false = touch unpressed) 
 *********************************************************************/
bool Touch_Event() {
  p = touch.getPoint(); 
  delay(1);
  #ifdef touch_yellow_header
    p.x = map(p.x, TS_MINX, TS_MAXX, 320, 0); // yellow header
    p.y = map(p.y, TS_MINY, TS_MAXY, 0, 240);
  #else
    p.x = map(p.x, TS_MINX, TS_MAXX, 0, 320); // black header
    p.y = map(p.y, TS_MINY, TS_MAXY, 240, 0);
  #endif
  
  if (p.z > MINPRESSURE) return true;  
  return false;  
}



/********************************************************************//**
 * @brief     shows the intro screen in setup procedure
 * @param[in] None
 * @return    None
 *********************************************************************/
void IntroScreen()
{
  //Draw the Result Box
  tft.fillRect(0, 0, 240, 320, ILI9341_WHITE);
  tft.drawRGBBitmap(20,80, Zihatec_Logo,200,60);
  tft.setTextSize(0);
  tft.setTextColor(ILI9341_BLACK);
  tft.setFont(&FreeSansBold9pt7b);  

  tft.setCursor(80, 190);
  tft.println(F("AZ-Touch"));
  
  tft.setCursor(25, 215);
  tft.println("Pattern Lock Example");

}


/********************************************************************//**
 * @brief     draw the pattern lock screen
 * @param[in] None
 * @return    None
 *********************************************************************/
void drawlockScreen()
{
  digitalWrite(TFT_LED, HIGH);    // HIGH to turn backlight off - will hide the display during drawing
   Serial.println("draw lock screen...");
  //Draw the screen for unlocking
  tft.fillRect(0, 0, 240, 320, ILI9341_BLACK);
  for(int i1=0; i1<9; i1++) {
    tft.fillCircle(POINT_X_POS[i1], POINT_Y_POS[i1], 5, ILI9341_WHITE);
  }

  digitalWrite(TFT_LED, LOW);    // LOW to turn backlight on - will show the screen again

  // delete last entered pattern
  DeletePattern();
   
}


/********************************************************************//**
 * @brief     Proceed pattern entering
 * @param[in] None
 * @return    None
 *********************************************************************/
void EnterPattern()
{
  // Detecting position
  int p_new = PointDetection();

  if (p_new == 0) return;
  
  if ((p_new) && (p_new != p_old)) {
     Serial.print("detecting new point: ");
     Serial.println(p_new);
     
     // draw circle surrounding detected point
     tft.drawCircle(POINT_X_POS[p_new - 1], POINT_Y_POS[p_new - 1], 20, ILI9341_WHITE);    

     // draw line between detected points
     if (p_old) tft.drawLine(POINT_X_POS[p_new - 1], POINT_Y_POS[p_new - 1], POINT_X_POS[p_old - 1], POINT_Y_POS[p_old - 1], ILI9341_WHITE);      
     p_old = p_new; 

     if (point_counter < max_points) 
     {
       detected_pattern[point_counter] = p_new;
       point_counter++;
     }
  }
  
}


/********************************************************************//**
 * @brief     Detect pattern point
 * @param[in] None
 * @return    0 for no detected point or 1-9 for a detected point
 *********************************************************************/
int PointDetection()
{
  // Detecting position
  for(int i1=0; i1<9; i1++) {
    if ((abs(POINT_X_POS[i1] - X) < 25) && (abs(POINT_Y_POS[i1] - Y) < 25)) {
      return(++i1);
    }
  }
  return(0);
}


/********************************************************************//**
 * @brief     Delete entered pattern 
 * @param[in] None
 * @return    None
 *********************************************************************/
void DeletePattern()
{
  for(int i1=0; i1<max_points; i1++) {
    detected_pattern[i1] = 0; 
  }  
}


/********************************************************************//**
 * @brief     Compare entered pattern with stored pattern (pattern_OK)
 * @param[in] None
 * @return    0 comparison failed, 1 patterns are equal
 *********************************************************************/
int ComparePattern()
{
  for(int i1=0; i1<max_points; i1++) {
    if (pattern_OK[i1] != detected_pattern[i1]) return(0);    
  }
  return(1);
}





/********************************************************************//**
 * @brief     shows the granted screen on tft 
 * @param[in] None
 * @return    None
 *********************************************************************/
void Granted_Screen(){
  digitalWrite(TFT_LED, HIGH);   // HIGH to turn backlight off    
  tft.fillRect(0, 0, 240, 320, ILI9341_BLACK); 
  // show symbol
  tft.drawBitmap(55,60, padlock_unlocked,128,128,ILI9341_GREEN);
  tft.setTextSize(0);
  tft.setTextColor(ILI9341_WHITE); 
  tft.setFont(&FreeSansBold24pt7b); 
  tft.setCursor(35, 240 );
  tft.println(F("Access"));
  tft.setCursor(30, 290);
  tft.println("granted"); 
  digitalWrite(TFT_LED, LOW);    // LOW to turn backlight on
  sound(1000);
  delay(1200);
  sound(0);
}




/********************************************************************//**
 * @brief     shows the access denied screen on tft
 * @param[in] None
 * @return    None
 *********************************************************************/
void Denied_Screen() {
  digitalWrite(TFT_LED, HIGH);   // HIGH to turn backlight off 
  tft.fillRect(0, 0, 240, 320, ILI9341_BLACK);
  // show symbol
  tft.drawBitmap(55,60, padlock_locked,128,128,ILI9341_RED);
  // show result text
  tft.setTextSize(0);
  tft.setTextColor(ILI9341_WHITE); 
  tft.setFont(&FreeSansBold24pt7b); 
  tft.setCursor(35, 240 );
  tft.println("Access");
  tft.setCursor(38, 290);
  tft.println("denied"); 
  digitalWrite(TFT_LED, LOW); // LOW to turn backlight on
  for (int i=0;i< 3;i++) {
          sound(4000);
          delay(100);
          sound(0);
          delay(50);      
  }   
  delay(1500);  
}


/********************************************************************//**
 * @brief     universal sound output for different boards
 * @param[in] freq - frequency
 * @return    None
 *********************************************************************/
void sound(int freq) {
  #if defined(ESP32)  // ESP32 feather w/wing
  
  // ESP32
  ledcWriteTone(0,freq);
  
  #else
  if (freq) tone(BEEPER,freq);
  else noTone(BEEPER);
  
  #endif
}
