/*
 * Cyclometer.cpp
 *
 *  Created on: May 4, 2016
 *      Author: Madeleine Daigneau & Kristopher Brown
 */

#include "Cyclometer.h"

/*
 * Cyclometer Thread - checks for timeout conditions, checks for queue messages, and delays 1 ms to next cycle
 */
void* thread_worker_cycl(void* arg)
{
	while( true )
	{
		//check for timeout
		((Cyclometer*)arg) -> checkTimeout();
		//check for events in queue
		((Cyclometer*)arg) -> checkQ();
		//wait a bit
		usleep(1000);
	}
}

Cyclometer::Cyclometer( std::queue<Event>* qin, pthread_mutex_t *aQ ) {
	// Initialize variables
	stateMachine = new StateMachine();
	q = qin;
	accessQ = aQ;
	units = false;
	distancefactor = 0.0;
	speedfactor = 0.0;
	count = 0;
	ms = 0;
	autoMode = true;
	lastPulse = time( NULL );

	// create thread
	pthread_create(&thread, NULL, &thread_worker_cycl, (void*)this);
}

Cyclometer::~Cyclometer() {}

/*
 * calculate - calls calculate for StateMachine to determine current Status values
 */
//Seconds are now milliseconds
void Cyclometer::calculate(int seconds){
	stateMachine->calculate(seconds);
}

/*
 * setCalculations - sets doCalculate in StateMachine
 */
void Cyclometer::setCalculations(bool in){
	stateMachine->setCalculations(in);
}

/*
 * setAutoMode - sets autoMode in StateMachine
 */
void Cyclometer::setAutoMode(bool in){
	stateMachine->setAutoMode(in);
}

/*
 * reset - resets the Status and StateMachine variables
 */
void Cyclometer::reset(){

	int id = stateMachine->getStateID();

	if(id == (int)SETKMMIMODE || id == (int)SETTIRESIZEMODE){}
	else{
		count = 0;
		StaticObj::status->reset();
		stateMachine->reset();
	}
}

/*
 * resetAll - resets Status and StateMachine variables and reconfigures settings
 */
void Cyclometer::resetAll(){
	/*
	 * TODO Cyclometer tells statemachine a reset all request.
	 * Statemachine will have to transition to the intial state
	 */
	StaticObj::status->reset();
	stateMachine->reset();
	count = 0;
}

/*
 * checkTimeout - increments millisecond timer and checks for timeout condition
 */
void Cyclometer::checkTimeout()
{
	//check for timeout since last wheel pulse
	++ms;
	if (ms > PULSETIMEOUT*1000)
	{
		//queue timeout event
		pthread_mutex_lock(accessQ);
		q->push(TIMEOUT);
		pthread_mutex_unlock(accessQ);
	}
}

/*
 * checkQ - checks the message queue for any Event signals
 */
void Cyclometer::checkQ()
{
	// Check Q for events
	Event e = NONE;
	pthread_mutex_lock(accessQ);
	if( !q->empty() )
	{
		e = q->front();
		q->pop();
	}
	pthread_mutex_unlock(accessQ);
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
		if(autoMode) setCalculations(true);
		t = time( NULL );
		seconds = -1*(difftime(lastPulse,t));
		calculate((double)ms); //seconds
		ms = 0;
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
