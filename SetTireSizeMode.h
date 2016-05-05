/*
 * SetTireSizeMode.h
 *
 *  Created on: May 4, 2016
 *      Author: Madeleine Daigneau & Kristopher Brown
 */

#ifndef SETTIRESIZEMODE_H_
#define SETTIRESIZEMODE_H_

#include "State.h"

class SetTireSizeMode: public State {
public:

	SetTireSizeMode(const std::string &ID) : State(ID) { }

	virtual void onEnter(StateMachine& statemachine);

	virtual void accept(StateMachine& statemachine);

	virtual void onExit(StateMachine& statemachine);

};

#endif /* SETTIRESIZEMODE_H_ */