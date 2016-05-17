/*
 * IOControl.h
 *
 *  Created on: May 4, 2016
 *      Author: Kristopher Brown & Madeleine Daigneau
 */

#ifndef IOCONTROL_H_
#define IOCONTROL_H_

#include <cstdio>
#include <stdint.h>
#include <sys/neutrino.h>
#include <sys/mman.h>
#include <hw/inout.h>
#include <unistd.h>
#include <iostream.h>

#define IO_PORT_SIZE 1
#define IO_CONTROL_REGISTER 0x28B

#define IO_A_REGISTER 0x288
#define IO_B_REGISTER 0x289
#define IO_C_REGISTER 0x28A
#define IO_PORT_SIZE 1 //TODO Probably change this later

#include "Event.h"
#include "StaticObj.h"
#include "An7Seg.h"

#include <pthread.h>
#include <queue>

class IOControl {
	uintptr_t CONTROL_HANDLE;
	uintptr_t A_HANDLE;
	uintptr_t B_HANDLE;
	uintptr_t C_HANDLE;
	std::queue< Event > *q;
	pthread_mutex_t *accessQ;
public:

	/*
	 * Add I/O Registers and message_queue l8r
	 * 
	 * Also add functionality to write to 7 segment displays, LEDs
	 */

	IOControl();
	IOControl( std::queue<Event>* qin, pthread_mutex_t *aQ );
	~IOControl();

	void receive();

};

#endif /* IOCONTROL_H_ */
