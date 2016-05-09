/*
 * SetKmMiMode.h
 *
 *  Created on: May 4, 2016
 *      Author: Kristopher Brown & Madeleine Daigneau
 */

#ifndef SETKMMIMODE_H_
#define SETKMMIMODE_H_

#include "State.h"

class SetKmMiMode: public State {
public:

	SetKmMiMode(const std::string &ID) : State(ID) { }

	virtual void onEnter(StateMachine& statemachine);

	virtual void accept(StateMachine& statemachine, Event e);

	virtual void onExit(StateMachine& statemachine);
};

#endif /* SETKMMIMODE_H_ */
