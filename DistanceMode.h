/*
 * DistanceMode.h
 *
 *  Created on: May 4, 2016
 *      Author: Madeleine Daigneau & Kristopher Brown
 */

#ifndef DISTANCEMODE_H_
#define DISTANCEMODE_H_

#include "State.h"
#include "States.h"


class DistanceMode: public State {
public:

	DistanceMode(StateID ID) : State(ID) { }

	virtual void onEnter(StateMachine& statemachine);

	virtual void accept(StateMachine& statemachine, Event e);

	virtual void onExit(StateMachine& statemachine);

	virtual void update(StateMachine& statemachine);
};

#endif /* DISTANCEMODE_H_ */
