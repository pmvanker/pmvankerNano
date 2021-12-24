/*============================================================================
 *  Name        : gpio.cpp
 *  Author      : praful vanker
 *  Version     :
 *  Copyright   : GPL-3.0-only
 *  			  Everyone is permitted to copy and distribute verbatim copies
 *  			  of this license document, but changing it is not allowed.
 *  Description : GPIO library for JetsonNano
============================================================================*/

#include "gpio.h"
#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include<cstdlib>
#include<map>
#include<cstdint>
using namespace std;

namespace pmvankerNano {
map <uint8_t, uint8_t> GpioMap = {
									{40,78} /* GPIO_78 */,
								  	{38,77} /* GPIO_77 */,
									{36,51} /* GPIO_51 */,
									{32,168}/* GPIO_168 */,
									{26,20} /* GPIO_20 */,
									{24,19} /* GPIO_19 */,
									{22,13} /* GPIO_13 */,
									{18,15} /* GPIO_15 */,
									{16,232}/* GPIO_232 */,
									{12,79} /* GPIO_79 */,
									{7,216} /* GPIO_216 */,
									{11,50} /* GPIO_50 */,
									{13,14} /* GPIO_14 */,
									{15,194}/* GPIO_194 */,
									{19,16} /* GPIO_16 */,
									{21,17} /* GPIO_17 */,
									{23,18}/* GPIO_18 */,
									{29,149} /* GPIO_149 */,
									{31,200} /* GPIO_200 */,
									{33,38}/* GPIO_38 */,
									{35,76} /* GPIO_76 */,
									{37,12} /* GPIO_12 */
								};
GPIO::GPIO(int number) {
	this->number = GpioMap[number];
	this->debounceTime = 0;
	this->togglePeriod=100;
	this->toggleNumber=-1; //infinite number
	this->callbackFunction = NULL;
	this->threadRunning = false;
	ostringstream s;
	s << "gpio" << this->number;
	this->name = string(s.str());
	this->path = GPIO_PATH + this->name + "/";
	this->exportGPIO();
	// need to give Linux time to set up the sysfs structure
	std::this_thread::sleep_for(std::chrono::milliseconds(250));
}

int GPIO::write(string path, string filename, string value){
   ofstream fs;
   fs.open((path + filename).c_str());
   if (!fs.is_open()){
	   perror("GPIO: write failed to open file ");
	   return -1;
   }
   fs << value;
   fs.close();
   return 0;
}

int GPIO::exportGPIO(){
   return this->write(GPIO_PATH, "export", this->number);
}

int GPIO::unexportGPIO(){
   return this->write(GPIO_PATH, "unexport", this->number);
}

string GPIO::read(string path, string filename){
   ifstream fs;
   fs.open((path + filename).c_str());
   if (!fs.is_open()){
	   perror("GPIO: read failed to open file ");
    }
   string input;
   getline(fs,input);
   fs.close();
   return input;
}

int GPIO::write(string path, string filename, int value){
   stringstream s;
   s << value;
   return this->write(path,filename,s.str());
}

int GPIO::setDirection(GPIO_DIRECTION dir){
   switch(dir){
   case INPUT: return this->write(this->path, "direction", "in");
      break;
   case OUTPUT:return this->write(this->path, "direction", "out");
      break;
   }
   return -1;
}

int GPIO::setValue(GPIO_VALUE value){
   switch(value){
   case HIGH: return this->write(this->path, "value", "1");
      break;
   case LOW: return this->write(this->path, "value", "0");
      break;
   }
   return -1;
}

GPIO_VALUE GPIO::getValue(){
	string input = this->read(this->path, "value");
	if (input == "0") return LOW;
	else return HIGH;
}

GPIO_DIRECTION GPIO::getDirection(){
	string input = this->read(this->path, "direction");
	if (input == "in") return INPUT;
	else return OUTPUT;
}

int GPIO::streamOpen(){
	stream.open((path + "value").c_str());
	return 0;
}
int GPIO::streamWrite(GPIO_VALUE value){
	stream << value << std::flush;
	return 0;
}
int GPIO::streamClose(){
	stream.close();
	return 0;
}

int GPIO::toggleOutput(int time){ return this->toggleOutput(-1, time); }
int GPIO::toggleOutput(int numberOfTimes, int time){
	this->setDirection(OUTPUT);
	this->toggleNumber = numberOfTimes;
	this->togglePeriod = time;
	this->threadRunning = true;

	this->ThreadObj = new thread(threadedToggle, static_cast<void*>(this));
    return 0;
}

// This thread function is a friend function of the class
void* threadedToggle(void *value){
	GPIO *gpio = static_cast<GPIO*>(value);
	bool isHigh = (bool) gpio->getValue(); //find current value
	while(gpio->threadRunning){
		if (isHigh)	gpio->setValue(HIGH);
		else gpio->setValue(LOW);
		std::this_thread::sleep_for(std::chrono::milliseconds(gpio->togglePeriod));
		isHigh=!isHigh;
		if(gpio->toggleNumber>0) gpio->toggleNumber--;
		if(gpio->toggleNumber==0) gpio->threadRunning=false;
	}
	return 0;
}

GPIO::~GPIO() {
	this->threadRunning = false;
	if (this->ThreadObj->joinable())
		this->ThreadObj->join();
	this->unexportGPIO();
}

} /* namespace pmvankerNano */
