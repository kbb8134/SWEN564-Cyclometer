/*
 * SpeedMode.h
 *
 *  Created on: May 4, 2016
 *      Author: Madeleine Daigneau & Kristopher Brown
 */

#ifndef SPEEDMODE_H_
#define SPEEDMODE_H_

#include "State.h"
#include "States.h"


class SpeedMode: public State {
public:

	SpeedMode(StateID ID) : State(ID) { }

	virtual void onEnter(StateMachine& statemachine);

	virtual void accept(StateMachine& statemachine, Event e);

	virtual void onExit(StateMachine& statemachine);

};

#endif /* SPEEDMODE_H_ */
