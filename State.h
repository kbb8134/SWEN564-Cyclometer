/*
 * State.h
 *
 *  Created on: May 4, 2016
 *      Author: Kristopher Brown & Madeleine Daigneau
 */

#ifndef STATE_H_
#define STATE_H_

#include <string>
#include "StateMachine.h"
#include "Event.h"

enum StateID {

	SETTIRESIZEMODE = 1,
	SETKMMIMODE = 2,
	TIMEMODE = 3,
	DISTANCEMODE = 4,
	SPEEDMODE = 5

};

class State {

	StateID ID;

public:
	State(StateID);
	virtual ~State();

	virtual void onEnter(StateMachine& statemachine) = 0;
	virtual void onExit(StateMachine& statemachine)= 0;
	virtual void accept(StateMachine& statemachine, Event e) =0;
	virtual void update(StateMachine& statemachine) = 0;

	StateID getID(StateMachine&);

};

#endif /* STATE_H_ */
