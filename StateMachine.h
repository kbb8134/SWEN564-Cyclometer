/*
 * StateMachine.h
 *
 *  Created on: May 4, 2016
 *      Author: Kristopher Brown & Madeleine Daigneau
 */

#ifndef STATEMACHINE_H_
#define STATEMACHINE_H_

class State;
class StateMachine {

	State* currentState;

public:
	StateMachine();
	virtual ~StateMachine();

	void transition(State* state);

};

#endif /* STATEMACHINE_H_ */
