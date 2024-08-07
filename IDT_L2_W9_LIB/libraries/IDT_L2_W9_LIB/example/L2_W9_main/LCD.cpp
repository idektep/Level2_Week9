#include "LCD.h"
#include "DHTZ.h"
#include <Arduino.h>


String LCDText0 = "IDEKTEP";
String LCDText1 = "Robot Expoler";
DHTZ dht_s;

LiquidCrystal_I2C lcd(0x27, 16, 2); // 0x27 or 0x3F

void LCD::LcdInit()
{
    lcd.init();
    lcd.display();
    lcd.backlight();
    lcd.clear();
    lcd.noBacklight();
    
}

void LCD::LcdShowLight()
{
    lcd.backlight();
}

void LCD::LcdNoLight()
{
    lcd.noBacklight();
}

void LCD::LcdDisplayDHT()
{
    float temp = dht_s.DHTZReadTemp();
    float humid = dht_s.DHTZReadHumid();
    unsigned long currentMillis = millis();
    
    if (currentMillis - previousMillis_lcd >= lcd_refresh)
    {
        previousMillis_lcd = currentMillis;
        lcd.clear();

        lcd.setCursor(0, 0);
        lcd.print("Temp : " + String(temp, 1) + " c");
        lcd.setCursor(0, 1);
        lcd.print("Humidity : " + String(humid, 1) + " %");
    }
}

void LCD::LcdDisplay()
{
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis_lcd >= lcd_refresh)
    {
        previousMillis_lcd = currentMillis;
        lcd.clear();

        
        lcd.setCursor(0, 0);
        lcd.print(LCDText0);
        lcd.setCursor(0, 1);
        lcd.print(LCDText1);
        
    }
}
