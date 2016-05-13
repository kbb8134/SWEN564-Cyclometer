/*
 * DistanceMode.cpp
 *
 *  Created on: May 4, 2016
 *      Author: Madeleine Daigneau & Kristopher Brown
 */

#include "DistanceMode.h"

void DistanceMode::onEnter(StateMachine& statemachine){

	update(statemachine);
}

void DistanceMode::accept(StateMachine& statemachine, Event e){
	switch(e){
	case SETBUTTON:
		statemachine.transition(States::TIRE_SIZE);
		break;
	case RESETALL:
		statemachine.transition(States::KM_MI);
	default:
		break;
	}
}

void DistanceMode::onExit(StateMachine& statemachine){

}

void DistanceMode::update(StateMachine& statemachine){
	// TODO change status output vars
}
