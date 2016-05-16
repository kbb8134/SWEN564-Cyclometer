/*
 * SetKmMiMode.cpp
 *
 *  Created on: May 4, 2016
 *      Author: Kristopher Brown & Madeleine Daigneau
 */

#include "SetKmMiMode.h"

void SetKmMiMode::onEnter(StateMachine& statemachine){
	update(statemachine);

}

void SetKmMiMode::accept(StateMachine& statemachine, Event e){
	bool km;
	switch(e)
	{
	case SETBUTTON:
		statemachine.transition(States::TIRE_SIZE);
		break;
	case MODEBUTTON:
		km = StaticObj::status->getKm();
		statemachine.setUnits(km);
		StaticObj::status->setKm(!km);
		break;
	default:
		break;
	}
}

void SetKmMiMode::onExit(StateMachine& statemachine){

}

void SetKmMiMode::update(StateMachine& statemachine){
	// TODO change status output vars
}
