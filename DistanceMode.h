/*
 * DistanceMode.h
 *
 *  Created on: May 4, 2016
 *      Author: Madeleine Daigneau & Kristopher Brown
 */

#ifndef DISTANCEMODE_H_
#define DISTANCEMODE_H_

#include "State.h"

class DistanceMode: public State {
public:

	DistanceMode(const std::string &ID) : State(ID) { }

	virtual void onEnter(StateMachine& statemachine);

	virtual void accept(StateMachine& statemachine);

	virtual void onExit(StateMachine& statemachine);
};

#endif /* DISTANCEMODE_H_ */
