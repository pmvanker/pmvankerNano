/*============================================================================
 *  Name        : BlinkSample.cpp
 *  Author      : praful vanker
 *  Version     :
 *  Copyright   : GPL-3.0-only
 *  			  Everyone is permitted to copy and distribute verbatim copies
 *  			  of this license document, but changing it is not allowed.
 *  Description : Blink LED connected to Pin 40
============================================================================*/

#include <iostream>
#include <unistd.h>

#define LCD_16X2

#ifdef LED_BLINK
#include "gpio.h"
#endif

#ifdef LCD_16X2
#include "lcdI2C.h"
#endif

using namespace pmvankerNano;

int main() {

#ifdef LED_BLINK
	GPIO Led(40);
	Led.setDirection(OUTPUT);
	for(int i=0;i<2;i++)		// Blink LED for 5 time every 5 second interval
	{
		Led.setValue(HIGH);
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
		Led.setValue(LOW);
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}
	Led.toggleOutput(250);		// toggle every 500 mili-seconds
	while(1);
#endif

#ifdef LCD_16X2
	LiquidCrystal_I2C lcd(1, 0x27, 16, 2);
	lcd.setCursor(0,0);
	lcd.printstr("pmvanker");
	lcd.setCursor(0,1);
	lcd.printstr("like ,shr, sub");
	lcd.backlight();


#endif

	return 0;
}