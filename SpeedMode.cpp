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
	bool autoMode;
	switch(e)
	{
	case MODEBUTTON:
		statemachine.transition(States::DISTANCE);
		break;
	case RESETALL:
		statemachine.transition(States::KM_MI);
		break;
	case SETBUTTON:
		// manual/auto mode
		autoMode = statemachine.getAutoMode();
		statemachine.setAutoMode(!autoMode);
		break;
	case STARTSTOPBUTTON:
		// manual/auto mode
		autoMode = statemachine.getCalculations();
		statemachine.setCalculations(!autoMode);
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

