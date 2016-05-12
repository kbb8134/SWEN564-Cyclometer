/*
 * TimeMode.h
 *
 *  Created on: May 4, 2016
 *      Author: Madeleine Daigneau & Kristopher Brown
 */

#ifndef TIMEMODE_H_
#define TIMEMODE_H_

#include "State.h"
#include "States.h"


class TimeMode: public State {
public:

	TimeMode(StateID ID) : State(ID) { }

	virtual void onEnter(StateMachine& statemachine);

	virtual void accept(StateMachine& statemachine, Event e);

	virtual void onExit(StateMachine& statemachine);

	virtual void update(StateMachine& statemachine);
};

#endif /* TIMEMODE_H_ */
