/*
 * TimeMode.h
 *
 *  Created on: May 4, 2016
 *      Author: Madeleine Daigneau & Kristopher Brown
 */

#ifndef TIMEMODE_H_
#define TIMEMODE_H_

#include "State.h"

class TimeMode: public State {
public:

	TimeMode(const std::string &ID) : State(ID) { }

	virtual void onEnter(StateMachine& statemachine);

	virtual void accept(StateMachine& statemachine, Event e);

	virtual void onExit(StateMachine& statemachine);
};

#endif /* TIMEMODE_H_ */
