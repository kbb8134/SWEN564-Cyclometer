/*
 * IOControl.cpp
 *
 *  Created on: May 4, 2016
 *      Author: Kristopher Brown & Madeleine Daigneau
 */

#include "IOControl.h"

/*
 * IOControl constructor - initializes I/O settings and controls
 */
IOControl::IOControl( std::queue<Event>* qin, pthread_mutex_t *aQ ) {
	// Initialize variables
	accessQ = aQ;
	q = qin;

	// Initialize HW I/O control handlers
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

IOControl::~IOControl() {}

/*
 * receive - Function to receive input from and write output to the FPGA via the QNX box
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
	int count = 0;
	int countHold = 0;
	int statusCnt = 0;
	bool holdDone = false;
	//Status vars
	AN7SEG anode3;
	AN7SEG anode2;
	AN7SEG anode1;
	AN7SEG anode0;
	bool km;
	bool calc;
	bool to;
	double currSpeed;
	double avgSpeed;
	double dist;
	//Read/write signals
	uint8_t inputs;
	uint8_t msg;
	while(true)
	{
	//Read from inputs on FPGA
		inputs = in8(IO_A_REGISTER);
	// check for wheel pulse rising edge- compare prev reading to current
		currPulse = inputs & (1);
		if( currPulse && !prevPulse )
		{
			//printf("-- Wheel Pulse --\n");
			pthread_mutex_lock(accessQ);
			q->push(WHEELPULSE);
			pthread_mutex_unlock(accessQ);
		}
	// process inputs
	// load queue with signals - StaticObj::mutexQ->write(event)
		currSET = inputs & (1<<1);
		currSTRTSTP = inputs & (1<<2);
		currMODE = inputs & (1<<3);
		if( currSET && currSTRTSTP && currMODE && (countHold > 100) && !holdDone )
		{
			printf("-- RESETALL --\n");
			pthread_mutex_lock(accessQ);
			q->push(RESETALL);
			pthread_mutex_unlock(accessQ);
			holdDone = true;
			countHold = 0;
		}
		else if( currSET && currMODE && (countHold > 100) && !holdDone )
		{
			printf( "-- RESET --\n");
			pthread_mutex_lock(accessQ);
			q->push(RESET);
			pthread_mutex_unlock(accessQ);
			holdDone = true;
			countHold = 0;
		}
		else if( !currSET && prevSET && !holdDone )
		{
			printf("-- SET --\n");
			pthread_mutex_lock(accessQ);
			q->push(SETBUTTON);
			pthread_mutex_unlock(accessQ);
		}
		else if( !currSTRTSTP && prevSTRTSTP && !holdDone )
		{
			printf("-- START/STOP --\n");
			pthread_mutex_lock(accessQ);
			q->push(STARTSTOPBUTTON);
			pthread_mutex_unlock(accessQ);
		}
		else if( !currMODE && prevMODE && !holdDone )
		{
			printf("-- MODE --\n");
			/*StaticObj::mutexQ->lock();
			StaticObj::mutexQ->write(MODEBUTTON);
			StaticObj::mutexQ->unlock();*/
			pthread_mutex_lock(accessQ);
			q->push(MODEBUTTON);
			pthread_mutex_unlock(accessQ);
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
		anode3 = StaticObj::status->getAnode(1);
		anode2 = StaticObj::status->getAnode(2);
		anode1 = StaticObj::status->getAnode(3);
		anode0 = StaticObj::status->getAnode(4);
		currSpeed = StaticObj::status->getCurrentSpeed();
		avgSpeed = StaticObj::status->getAvgSpeed();
		dist = StaticObj::status->getDistance();
	// write output signals
		//AN0
		msg = 0x00;
		msg = (1<<4)|(1<<5)|(1<<6)|((calc && halfsec))|((!to && halfsec)<<1)|(km<<2);//
		out8(IO_C_REGISTER,msg);
		out8(IO_B_REGISTER,anode0);
		usleep(1);
		//AN1
		msg = 0x00;
		msg = (1<<3)|(1<<5)|(1<<6)|(1<<7)|((calc && halfsec))|((!to && halfsec)<<1)|(km<<2);//
		out8(IO_C_REGISTER,msg);
		out8(IO_B_REGISTER,anode1);
		usleep(1);
		//AN2
		msg = 0x00;
		msg = (1<<3)|(1<<4)|(1<<6)|(1<<7)|((calc && halfsec))|((!to && halfsec)<<1)|(km<<2);//
		out8(IO_C_REGISTER,msg);
		out8(IO_B_REGISTER,anode2);
		usleep(1);
		//AN3
		msg = 0x00;
		msg = (1<<3)|(1<<4)|(1<<5)|(1<<7)|((calc && halfsec))|((!to && halfsec)<<1)|(km<<2); //
		out8(IO_C_REGISTER,msg);
		out8(IO_B_REGISTER,anode3);
		usleep(1);
	// wait a bit
		prevPulse = currPulse;
		prevSET = currSET;
		prevSTRTSTP = currSTRTSTP;
		prevMODE = currMODE;
		count++;
		if(count > 25)
		{
			halfsec = !halfsec;
			count = 0;
		}
		if( statusCnt > 50 )
		{
			printf("-------------------------------------------------\n");
			printf("STATUS\n km: %d\n calc: %d\n to: %d\n anode3: %x\n anode2: %x\n anode1: %x\n anode0: %x\n currSpeed: %f\n avgSpeed: %f\n dist: %f\n",km,calc,to,anode3,anode2,anode1,anode0,currSpeed,avgSpeed,dist);
			printf("-------------------------------------------------\n");
			statusCnt = 0;
		}
		else statusCnt++;
		usleep(2000); // = 2ms
	}
}
