/*============================================================================
 *  Name        : bus.h
 *  Author      : praful vanker
 *  Version     :
 *  Copyright   : GPL-3.0-only
 *  			  Everyone is permitted to copy and distribute verbatim copies
 *  			  of this license document, but changing it is not allowed.
 *  Description :
============================================================================*/
#ifndef BUS_H_
#define BUS_H_

#include<chrono>
#include<thread>


namespace pmvankerNano {

/**
 * @class BusDevice
 * @brief This class is the parent of I2C and SPI devices, so that devices that use both
 * SPI and I2C interfaces can use those interfaces interchangeably. Because it contains
 * abstract methods, the child classes MUST implement the methods that are listed in this
 * class.
 */
class BusDevice {
protected:
	unsigned int bus;    /**< the bus number */
	unsigned int device; /**< the device number on the bus  */
	int file;            /**< the file handle to the device */
public:
	BusDevice(unsigned int bus, unsigned int device);
	virtual int open()=0;
	virtual unsigned char readRegister(unsigned int registerAddress)=0;
	virtual unsigned char* readRegisters(unsigned int number, unsigned int fromAddress=0)=0;
	virtual int write(unsigned char value)=0;
	virtual int writeRegister(unsigned int registerAddress, unsigned char value)=0;
	virtual void debugDumpRegisters(unsigned int number = 0xff)=0;
	virtual void close()=0;
	virtual ~BusDevice();
};

} /* namespace pmvankerNano */




#endif /* BUS_H_ */
