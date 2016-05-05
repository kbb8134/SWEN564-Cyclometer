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


class State {

	std::string ID;

public:
	State(std::string name);
	virtual ~State();

	virtual void onEnter(StateMachine& statemachine) = 0;
	virtual void onExit(StateMachine& statemachine)= 0;
	virtual void accept(StateMachine& statemachine) =0;

	std::string getID(StateMachine&);

};

#endif /* STATE_H_ */
