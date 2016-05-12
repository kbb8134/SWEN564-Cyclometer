/*
 * IOControl.cpp
 *
 *  Created on: May 4, 2016
 *      Author: Kristopher Brown & Madeleine Daigneau
 */

#include "IOControl.h"

IOControl::IOControl() {
	// TODO Auto-generated constructor stub

}

IOControl::~IOControl() {
	// TODO Auto-generated destructor stub
}

/*
 * Function to receive input from the QNX box
 */
void IOControl::receive(){
	//Read from inputs on FPGA
	// check for wheel pulse
	//process inputs
	// -debouncing buttons
	//load queue with signals - StaticObj::mutexQ->write(event)
	// read output vars from status - StaticObj::status
	//write output signals
	// wait a bit
}
