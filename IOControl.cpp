/*
 * IOControl.cpp
 *
 *  Created on: May 4, 2016
 *      Author: Kristopher Brown & Madeleine Daigneau
 */

#include "IOControl.h"

IOControl::IOControl() {
	// TODO Auto-generated constructor stub
	if( ThreadCtl(_NTO_TCTL_IO, NULL) == -1 )
	{
		std::perror("Error - could not access I/O registers");
	}

	CONTROL_HANDLE = mmap_device_io(IO_PORT_SIZE, IO_CONTROL_REGISTER);
	A_HANDLE = mmap_device_io(IO_PORT_SIZE, IO_A_REGISTER);
	B_HANDLE = mmap_device_io(IO_PORT_SIZE, IO_B_REGISTER);
	C_HANDLE = mmap_device_io(IO_PORT_SIZE, IO_C_REGISTER);

    if(CONTROL_HANDLE == MAP_DEVICE_FAILED)
    {
        std::cout << "Failed to map control register";
    }

    if(A_HANDLE == MAP_DEVICE_FAILED)
    {
        std::cout << "Failed to map register A";
    }

    if(B_HANDLE == MAP_DEVICE_FAILED)
    {
        std::cout << "Failed to map register B";
    }

    if(C_HANDLE == MAP_DEVICE_FAILED)
    {
        std::cout << "Failed to map register C";
    }
    // Initialize control register
    // A is input
    // B,C are output
    out8(CONTROL_HANDLE,0x90);
}

IOControl::~IOControl() {
	// TODO Auto-generated destructor stub
}

/*
 * Function to receive input from the QNX box
 */
void IOControl::receive(){
	while(true)
	{
	//Read from inputs on FPGA
		uint8 inputs = in8(IO_A_REGISTER);
	// check for wheel pulse - compare prev reading to current
	//process inputs
	// -debouncing buttons
	//load queue with signals - StaticObj::mutexQ->write(event)
	// read output vars from status
		// - AN7SEG an1 = StaticObj::status->getAnode(1)
		// repeat for all 7 seg displays
	//write output signals
		// Anodes & LEDs - out8(IO_C_REGISTER,msg)
		// Segments - out8(IO_B_REGISTER,msg)
		//repeat for all 7 seg displays
	// wait a bit
		usleep(2000);
	}
}
