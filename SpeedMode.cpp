/*
 * SpeedMode.cpp
 *
 *  Created on: May 4, 2016
 *      Author: Madeleine Daigneau & Kristopher Brown
 */

#include "SpeedMode.h"


void SpeedMode::onEnter(StateMachine& statemachine){
	update(statemachine);

}

void SpeedMode::accept(StateMachine& statemachine, Event e){
	switch(e)
	{
	case MODEBUTTON:
		statemachine.transition(States::DISTANCE);
		break;
	case RESETALL:
		statemachine.transition(States::KM_MI);
		break;
	default:
		break;
	}
}

void SpeedMode::onExit(StateMachine& statemachine){

}

void SpeedMode::update(StateMachine& statemachine){
	// TODO change status output vars
}

