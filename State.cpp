/*
 * State.cpp
 *
 *  Created on: May 4, 2016
 *      Author: Kristopher Brown & Madeleine Daigneau
 */

#include "State.h"

State::State(StateID id) {
	this -> ID = id;

}

State::~State() {
	// TODO Auto-generated destructor stub
}

StateID State::getID(StateMachine& sm){
	return this->ID;
}

