#ifndef LCD_H
#define LCD_H

#include <LiquidCrystal_I2C.h>

class LCD
{
private:
   const long lcd_refresh = 2000;
   unsigned long  previousMillis_lcd = 0;
   
public:
   void LcdInit();
   void LcdDisplayDHT();
   void LcdDisplay();
   void LcdShowLight();
   void LcdNoLight();
};
#endif