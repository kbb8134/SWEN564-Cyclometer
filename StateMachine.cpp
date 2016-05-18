/*
 * StateMachine.cpp
 *
 *  Created on: May 4, 2016
 *      Author: Madeleine Daigneau & Kristopher Brown
 */

#include "StateMachine.h"
#include "States.h"

/*
 * StateMachine Thread - updates the Status's display (anodes/7-segments)
 */
void* thread_worker_sm(void* arg)
{
	while(true)
	{
		// TODO
		((StateMachine*)arg)->update();
		// Wait a bit
		usleep(1000);
	}
}

StateMachine::StateMachine() {
	currentState = States::KM_MI;
	setUnits( false );
	count = 0;
	autoMode = true;
	// create thread
	pthread_create(&thread, NULL, &thread_worker_sm, (void*)this);

}

StateMachine::~StateMachine() {}

/*
 * transition - executes transition to input state from currentState
 */
void StateMachine::transition(State* state){
	currentState->onExit(*this);
	currentState = state;
	currentState->onEnter(*this);
}

/*
 * getCalculations - returns doCalculate (indicator of calculations in operation)
 */
bool StateMachine::getCalculations()
{
	return doCalculate;
}

/*
 * setCalculations - sets doCalculate to input bool
 */
void StateMachine::setCalculations(bool in){
	this->doCalculate = in;
	StaticObj::status->setCalc(in);
}

/*
 * setAutoMode - sets autoMode to input
 * 			if set to TRUE, calculations turned on
 * 			if set to FALSE, calculations turned off
 */
void StateMachine::setAutoMode(bool in){
	this->autoMode = in;
	if(~in) setCalculations(false);
	else setCalculations(true);
}

/*
 * getAutoMode - returns autoMode
 */
bool StateMachine::getAutoMode()
{
	return autoMode;
}

/*
 * getStateID - returns the stateID of the current state
 */
StateID StateMachine::getStateID(){
	return currentState->getID(*this);
}

/*
 * acceptEvent - queries the currentstate to accept a given Event
 */
void StateMachine::acceptEvent(Event e)
{
	currentState->accept(*this, e);
}

/*
 * update - triggers Status to update FPGA display variables based on current variables
 */
void StateMachine::update()
{
	StaticObj::status->updateDisplay(getStateID());
}

/*
 * calculate - sets Status variables based on the time between wheel pulses in seconds
 * 	*** seconds is now milliseconds
 */
void StateMachine::calculate(double seconds)
{
	// TODO - seconds = milliseconds now
	double curr;
	double avg;
	double dist;
	int circumf;
	int count;
	circumf = StaticObj::status->getCircumf();
	curr = (circumf * speedfactor)*1000/seconds;
	if( curr > 99 ) curr = 99;
	if( curr < 0 ) curr = 0.0;
	StaticObj::status->setCurrentSpeed(curr);
	double t = StaticObj::status->getTime();
	time_t currtime = time(NULL);
	//double diff = -1*difftime(startTrip,currtime);
	double diff = seconds/1000;
	StaticObj::status->setTime(t+diff);
	startTrip = currtime;
	if(doCalculate){
		count = StaticObj::status->getCount();
		dist = StaticObj::status->getDistance();
		++count;
		avg = StaticObj::status->getAvgSpeed();
		StaticObj::status->setAvgSpeed(avg + ((curr-avg)/count));
		dist += circumf*distancefactor;
		StaticObj::status->setDistance(dist);
		StaticObj::status->setCount(count);
	}
}

/*
 * reset - resets the variables used for calculating/updates
 */
void StateMachine::reset()
{
	count = 0;
	startTrip = time(NULL);
	elapsedTime = 0.0;
}

/*
 * setUnits - sets the units of conversion to kilometers or miles
 */
// miles if TRUE, km if FALSE
void StateMachine::setUnits(bool in)
{
	units = in;
	if(units)
	{
		distancefactor = MICMF;
		speedfactor = MIF;
	}
	else
	{
		distancefactor = KMCMF;
		speedfactor = KMF;
	}
}
