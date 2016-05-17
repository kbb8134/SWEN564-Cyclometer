/*
 * StateMachine.cpp
 *
 *  Created on: May 4, 2016
 *      Author: Madeleine Daigneau & Kristopher Brown
 */

#include "StateMachine.h"
#include "States.h"

void* thread_worker_sm(void* arg)
{
	while(true)
	{
		// TODO
		((StateMachine*)arg)->update();
		// Wait a bit
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

StateMachine::~StateMachine() {
	// TODO Auto-generated destructor stub
}

void StateMachine::transition(State* state){
	currentState->onExit(*this);
	currentState = state;
	currentState->onEnter(*this);
}

void StateMachine::setCalculations(bool in){
	this->doCalculate = in;
}

void StateMachine::setAutoMode(bool in){
	this->autoMode = in;
	if(~in) setCalculations(false);
	else setCalculations(true);
}

StateID StateMachine::getStateID(){
	return currentState->getID(*this);
}

void StateMachine::acceptEvent(Event e)
{
	//TODO
	currentState->accept(*this, e);
}

void StateMachine::update()
{
	StaticObj::status->updateDisplay(getStateID());
}

void StateMachine::calculate(int seconds)
{
	// TODO
	double curr;
	double avg;
	double dist;
	int circumf;
	int count;
	circumf = StaticObj::status->getCircumf();
	curr = (circumf * speedfactor)/seconds;
	if( curr > 99 || curr < 0 ) curr = 0.0;
	//if(isinf(curr)) curr = 0.0;
	StaticObj::status->setCurrentSpeed(curr);
	double t = StaticObj::status->getTime();
	time_t currtime = time(NULL);
	double diff = -1*difftime(startTrip,currtime);
	StaticObj::status->setTime(t+diff);
	startTrip = currtime;
	if(doCalculate){
		count = StaticObj::status->getCount();
		dist = StaticObj::status->getDistance();
		count++;
		avg = StaticObj::status->getAvgSpeed();
		StaticObj::status->setAvgSpeed(avg + ((curr-avg)/count));
		dist += circumf * distancefactor;
		StaticObj::status->setDistance(dist);
		StaticObj::status->setCount(count);
	}
}

void StateMachine::reset()
{
	count = 0;
	startTrip = time(NULL);
}

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
