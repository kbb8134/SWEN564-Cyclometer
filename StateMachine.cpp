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
	}
}

StateMachine::StateMachine() {
	currentState = States::KM_MI;
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

int StateMachine::getStateID(){
	return currentState->getID(*this);
}

void StateMachine::acceptEvent(Event e)
{
	//TODO
	currentState->accept(*this, e);
}

