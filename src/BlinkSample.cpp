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
#include "gpio.h"
using namespace pmvankerNano;

int main() {
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
	return 0;
}
