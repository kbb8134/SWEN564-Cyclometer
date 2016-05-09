/*
 * StateMachine.cpp
 *
 *  Created on: May 4, 2016
 *      Author: Madeleine Daigneau & Kristopher Brown
 */

#include "StateMachine.h"
#include "States.h"

StateMachine::StateMachine() {
	currentState = States::KM_MI;
}

StateMachine::~StateMachine() {
	// TODO Auto-generated destructor stub
}

void StateMachine::transition(State* state){
	currentState->onExit(*this);
	currentState = state;
	currentState->onEnter(*this);
}

std::string StateMachine::getStateID(){
	return currentState->getID(*this);
}

void StateMachine::acceptEvent(Event e)
{
	//TODO
	currentState->accept(e);
}

