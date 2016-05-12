/*
 * IOControl.h
 *
 *  Created on: May 4, 2016
 *      Author: Kristopher Brown & Madeleine Daigneau
 */

#ifndef IOCONTROL_H_
#define IOCONTROL_H_

#include "Event.h"
#include "StaticObj.h"

enum AN7SEG { // DECIMAL POINT ACTIVE - binary OR to deactivate = (1)|AN7SEG
	ZERO = 0x02,
	ONE = 0x9E,
	TWO = 0x28,
	THREE = 0x0C,
	FOUR = 0x98,
	FIVE = 0x48,
	SIX = 0x40,
	SEVEN = 0x1E,
	EIGHT = 0x00,
	NINE = 0x08
};

class IOControl {
public:

	/*
	 * Add I/O Registers and message_queue l8r
	 * 
	 * Also add functionality to write to 7 segment displays, LEDs
	 */

	IOControl();
	~IOControl();

	void receive();
	

};

#endif /* IOCONTROL_H_ */
