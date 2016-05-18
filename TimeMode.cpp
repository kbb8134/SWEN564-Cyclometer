/*
 * TimeMode.cpp
 *
 *  Created on: May 4, 2016
 *      Author: Madeleine Daigneau & Kristopher Brown
 */

#include "TimeMode.h"

void TimeMode::onEnter(StateMachine& statemachine){
	update(statemachine);
}

void TimeMode::accept(StateMachine& statemachine, Event e){
	bool autoMode;
	switch(e)
	{
	case MODEBUTTON:
		statemachine.transition(States::SPEED);
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

void TimeMode::onExit(StateMachine& statemachine){

}

void TimeMode::update(StateMachine& stateMachine){
}
