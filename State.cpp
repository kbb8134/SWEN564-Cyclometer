/*
 * State.cpp
 *
 *  Created on: May 4, 2016
 *      Author: Kristopher Brown & Madeleine Daigneau
 */

#include "State.h"

State::State(std::string id) {
	this -> ID = id;

}

State::~State() {
	// TODO Auto-generated destructor stub
}

std::string State::getID(StateMachine& sm){
	return this->ID;
}

