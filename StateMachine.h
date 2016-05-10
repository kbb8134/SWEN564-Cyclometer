/*
 * StateMachine.h
 *
 *  Created on: May 4, 2016
 *      Author: Kristopher Brown & Madeleine Daigneau
 */

#ifndef STATEMACHINE_H_
#define STATEMACHINE_H_

#include <pthread.h>
#include <string>
//#include "State.h"
#include "Event.h"

class State;
class StateMachine {

	State* currentState;
	pthread_t thread;

public:
	StateMachine();
	virtual ~StateMachine();

	void transition(State* state);
	int getStateID();
	void acceptEvent(Event e);
};

#endif /* STATEMACHINE_H_ */
