/*
 * Cyclometer.cpp
 *
 *  Created on: May 4, 2016
 *      Author: Madeleine Daigneau & Kristopher Brown
 */

#include "Cyclometer.h"

void* thread_worker_cycl(void* arg)
{
	// TODO
	while( true )
	{
		// read queue
		((Cyclometer*)arg) -> checkQ();
		// TODO wait a bit
	}
}

Cyclometer::Cyclometer() {
	// Initialize variables
	stateMachine = new StateMachine();
	//status = new Status();
	units = false;
	distancefactor = 0.0;
	speedfactor = 0.0;
	count = 0;

	// create thread
	pthread_create(&thread, NULL, &thread_worker_cycl, (void*)this);
	// HW IO registers
	if( ThreadCtl(_NTO_TCTL_IO, NULL) == -1 )
	{
		std::perror("Error - could not access I/O registers");
	}
	// QNX Control registers
	ctrlHandle = mmap_device_io(IO_PORT_SIZE, CTRL_ADDRESS);
	if(ctrlHandle == MAP_DEVICE_FAILED)
	{
		std::perror("Could not map control register");
	}
}

Cyclometer::~Cyclometer() {
	// TODO Auto-generated destructor stub
}

void Cyclometer::calculate(double seconds){

	double curr;
	double avg;
	double dist;
	int circumf;
	if(doCalculate){
		circumf = StaticObj::status->getCircumf();
		dist = StaticObj::status->getDistance();
		count++;
		avg = StaticObj::status->getAvgSpeed();
		curr = (circumf * speedfactor)/seconds;
		StaticObj::status->setCurrentSpeed(curr);
		StaticObj::status->setAvgSpeed(avg + ((curr-avg)/count));
		dist += circumf * distancefactor;
		StaticObj::status->setDistance(dist);
	}

}

void Cyclometer::setCalculations(bool in){
	this->doCalculate = in;
}

void Cyclometer::reset(){

	int id = stateMachine->getStateID();

	if(id == (int)SETKMMIMODE || id == (int)SETTIRESIZEMODE){

	}
	else{
		count = 0;
		StaticObj::status->reset();
	}
}

void Cyclometer::resetAll(){
	/*
	 * TODO Cyclometer tells statemachine a reset all request.
	 * Statemachine will have to transition to the intial state
	 */
	StaticObj::status -> reset();
	count = 0;
}

void Cyclometer::checkQ()
{
	// Check Q for events
	Event e = StaticObj::mutexQ->read();
	// TODO Do stuff with events
	switch(e)
	{
	case SETBUTTON:
		stateMachine->acceptEvent(e);
		break;
	case MODEBUTTON:
		stateMachine->acceptEvent(e);
		break;
	case STARTSTOPBUTTON:
		stateMachine->acceptEvent(e);
		break;
	case RESET:
		reset();
		break;
	case RESETALL:
		resetAll();
		stateMachine->acceptEvent(e);
		break;
	case WHEELPULSE:
		//calculate(seconds);
		break;
	default:
		break;
	}
}
