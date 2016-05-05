/*
 * StateMachine.cpp
 *
 *  Created on: May 4, 2016
 *      Author: Madeleine Daigneau & Kristopher Brown
 */

#include "StateMachine.h"
#include "States.h"

StateMachine::StateMachine() {


}

StateMachine::~StateMachine() {
	// TODO Auto-generated destructor stub
}

void StateMachine::transition(State* state){

}

std::string StateMachine::getStateID(){
	return currentState->getID(*this);
}

