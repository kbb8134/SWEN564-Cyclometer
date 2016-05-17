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
		//check for timeout
		((Cyclometer*)arg) -> checkTimeout();
		//check for events in queue
		((Cyclometer*)arg) -> checkQ();
		//wait a bit
		usleep(2000);
	}
}

Cyclometer::Cyclometer( std::queue<Event>* qin, pthread_mutex_t *aQ ) {
	// Initialize variables
	stateMachine = new StateMachine();
	q = qin;
	accessQ = aQ;
	//status = new Status();
	units = false;
	distancefactor = 0.0;
	speedfactor = 0.0;
	count = 0;
	autoMode = true;
	lastPulse = time( NULL );

	// create thread
	pthread_create(&thread, NULL, &thread_worker_cycl, (void*)this);
	// HW IO registers
	/*if( ThreadCtl(_NTO_TCTL_IO, NULL) == -1 )
	{
		std::perror("Error - could not access I/O registers");
	}
	// QNX Control registers
	ctrlHandle = mmap_device_io(IO_PORT_SIZE, CTRL_ADDRESS);
	if(ctrlHandle == MAP_DEVICE_FAILED)
	{
		std::perror("Could not map control register");
	}*/
}

Cyclometer::~Cyclometer() {
	// TODO Auto-generated destructor stub
}

void Cyclometer::calculate(int seconds){
	stateMachine->calculate(seconds);
}

void Cyclometer::setCalculations(bool in){
	//this->doCalculate = in;
	stateMachine->setCalculations(in);
	StaticObj::status->setCalc(in);
}

void Cyclometer::setAutoMode(bool in){
	/*this->autoMode = in;
	if(~in) setCalculations(false);
	else setCalculations(true);*/
	stateMachine->setAutoMode(in);
}

void Cyclometer::reset(){

	int id = stateMachine->getStateID();

	if(id == (int)SETKMMIMODE || id == (int)SETTIRESIZEMODE){}
	else{
		count = 0;
		StaticObj::status->reset();
		stateMachine->reset();
	}
}

void Cyclometer::resetAll(){
	/*
	 * TODO Cyclometer tells statemachine a reset all request.
	 * Statemachine will have to transition to the intial state
	 */
	StaticObj::status -> reset();
	stateMachine->reset();
	count = 0;
}

void Cyclometer::checkTimeout()
{
	//check for timeout since last wheel pulse
	time_t t = time( NULL );
	float seconds = difftime(lastPulse,t);
	if (seconds > PULSETIMEOUT)
	{
		//queue timeout event
		/*StaticObj::mutexQ->lock();
		StaticObj::mutexQ->write(TIMEOUT);
		StaticObj::mutexQ->unlock();*/
		pthread_mutex_lock(accessQ);
		q->push(TIMEOUT);
		pthread_mutex_lock(accessQ);
	}
}

void Cyclometer::checkQ()
{
	// Check Q for events
	/*StaticObj::mutexQ->lock();
	Event e = StaticObj::mutexQ->read();
	StaticObj::mutexQ->unlock();*/
	Event e = NONE;
	pthread_mutex_lock(accessQ);
	if( !q->empty() )
	{
		e = q->front();
		q->pop();
	}
	pthread_mutex_lock(accessQ);
	// TODO Do stuff with events
	time_t t;
	int seconds;
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
		StaticObj::status->setTimeout(false);
		setCalculations(true);
		t = time( NULL );
		seconds = -1*(difftime(lastPulse,t));
		calculate(seconds);
		lastPulse = t;
		break;
	case TIMEOUT:
		StaticObj::status->setTimeout(true);
		if(autoMode) setCalculations(false);
		break;
	default:
		break;
	}
}
