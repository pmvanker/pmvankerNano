/*============================================================================
 *  Name        : bus.cpp
 *  Author      : praful vanker
 *  Version     :
 *  Copyright   : GPL-3.0-only
 *  			  Everyone is permitted to copy and distribute verbatim copies
 *  			  of this license document, but changing it is not allowed.
 *  Description :
============================================================================*/
#include "bus.h"
namespace pmvankerNano {

/**
 * Constructor for a generic bus device
 * @param bus the bus number
 * @param device the device number
 */
BusDevice::BusDevice(unsigned int bus, unsigned int device) {
	this->bus = bus;
	this->device = device;
	this->file=-1;
}

/**
 * Destructor is unused
 */
BusDevice::~BusDevice() {}

} /* namespace pmvankernano */

