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
	// Handle readings
	bool prevPulse = false; // Last cycle's waveform (wheel pulse) reading
	bool currPulse; // Current waveform reading
	bool prevSET = false;
	bool currSET;
	bool prevMODE = false;
	bool currMODE;
	bool prevSTRTSTP = false;
	bool currSTRTSTP;
	bool halfsec = false;
	int count;
	int countHold;
	bool holdDone = false;
	//Status vars
	AN7SEG anode;
	bool km;
	bool calc;
	bool to;
	//Read/write signals
	uint8_t inputs;
	uint8_t msg;
	while(true)
	{
	//Read from inputs on FPGA
		inputs = in8(IO_A_REGISTER);
		//printf("Inputs: %x\n",inputs);
	// check for wheel pulse rising edge- compare prev reading to current
		currPulse = inputs & (1);
		if( currPulse && (!prevPulse) )
		{
			printf("-- Wheel Pulse %d %d --\n", prevPulse, currPulse);
			StaticObj::mutexQ->lock();
			StaticObj::mutexQ->write(WHEELPULSE);
			StaticObj::mutexQ->unlock();
		}
	// process inputs
	// load queue with signals - StaticObj::mutexQ->write(event)
		currSET = inputs & (1<<1);
		currSTRTSTP = inputs & (1<<2);
		currMODE = inputs & (1<<3);
		if( currSET && currSTRTSTP && currMODE && (countHold > 1000) && !holdDone )
		{
			printf("-- RESETALL --\n");
			StaticObj::mutexQ->lock();
			StaticObj::mutexQ->write(RESETALL);
			StaticObj::mutexQ->unlock();
			holdDone = true;
			countHold = 0;
		}
		else if( currSET && currMODE && (countHold > 1000) && !holdDone )
		{
			printf( "-- RESET --\n");
			StaticObj::mutexQ->lock();
			StaticObj::mutexQ->write(RESET);
			StaticObj::mutexQ->unlock();
			holdDone = true;
			countHold = 0;
		}
		else if( !currSET && prevSET && !holdDone )
		{
			printf("-- SET --\n");
			StaticObj::mutexQ->lock();
			StaticObj::mutexQ->write(SETBUTTON);
			StaticObj::mutexQ->unlock();
		}
		else if( !currSTRTSTP && prevSTRTSTP && !holdDone )
		{
			printf("-- START/STOP --\n");
			StaticObj::mutexQ->lock();
			StaticObj::mutexQ->write(STARTSTOPBUTTON);
			StaticObj::mutexQ->unlock();
		}
		else if( !currMODE && prevMODE && !holdDone )
		{
			printf("-- MODE --\n");
			StaticObj::mutexQ->lock();
			StaticObj::mutexQ->write(MODEBUTTON);
			StaticObj::mutexQ->unlock();
		}
		else if( (currSET && currMODE) || (currSET && currSTRTSTP && currMODE) )
		{
			countHold++;
		}
		else if( holdDone && (!currSET && !currSTRTSTP && !currMODE) )
		{
			countHold = 0;
			holdDone = false;
		}
		else
		{
			countHold = 0;
		}
	// read output vars from status
		km = StaticObj::status->getKm();
		calc = StaticObj::status->getCalc();
		to = StaticObj::status->getTimeout();
	// write output signals
		//AN3
		anode = StaticObj::status->getAnode(3);
		msg = 0x00;
		msg = (1<<3)|((calc && halfsec)<<2)|((!to && halfsec)<<1)|(km);
		//printf("B: %x\n",msg);
		//printf("C: %x\n",anode);
		out8(IO_B_REGISTER,msg);
		out8(IO_C_REGISTER,anode);
		//AN2
		anode = StaticObj::status->getAnode(2);
		msg = 0x00;
		msg = (1<<4)|((calc && halfsec)<<2)|((!to && halfsec)<<1)|(km);
		//printf("B: %x\n",msg);
		//printf("C: %x\n",anode);
		out8(IO_B_REGISTER,msg);
		out8(IO_C_REGISTER,anode);
		//AN1
		anode = StaticObj::status->getAnode(1);
		msg = 0x00;
		msg = (1<<5)|((calc && halfsec)<<2)|((!to && halfsec)<<1)|(km);
		//printf("B: %x\n",msg);
		//printf("C: %x\n",anode);
		out8(IO_B_REGISTER,msg);
		out8(IO_C_REGISTER,anode);
		//AN0
		anode = StaticObj::status->getAnode(4);
		msg = 0x00;
		msg = (1<<6)|((calc && halfsec)<<2)|((!to && halfsec)<<1)|(km);
		//printf("B: %x\n",msg);
		//printf("C: %x\n",anode);
		out8(IO_B_REGISTER,msg);
		out8(IO_C_REGISTER,anode);
	// wait a bit
		prevPulse = currPulse;
		prevSET = currSET;
		prevSTRTSTP = currSTRTSTP;
		prevMODE = currMODE;
		count++;
		if(count > 250)
		{
			halfsec = !halfsec;
			count = 0;
		}
		usleep(2000);
	}
}
