/*
 * SetTireSizeMode.cpp
 *
 *  Created on: May 4, 2016
 *      Author: Madeleine Daigneau & Kristopher Brown
 */

#include "SetTireSizeMode.h"

void SetTireSizeMode::onEnter(StateMachine& statemachine){
	update(statemachine);

}

void SetTireSizeMode::accept(StateMachine& statemachine, Event e){
	switch(e)
	{
	case SETBUTTON:
		statemachine.transition(States::SPEED);
		break;
	case RESETALL:
		statemachine.transition(States::KM_MI);
		break;
	default:
		break;
	}
}

void SetTireSizeMode::onExit(StateMachine& statemachine){

}


void SetTireSizeMode::update(StateMachine& statemachine){
	// TODO change status output vars
}
