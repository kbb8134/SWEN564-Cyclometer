/*
 * Cyclometer.cpp
 *
 *  Created on: May 4, 2016
 *      Author: Madeleine Daigneau & Kristopher Brown
 */

#include "Cyclometer.h"

Cyclometer::Cyclometer() {
	count = 0;

}

Cyclometer::~Cyclometer() {
	// TODO Auto-generated destructor stub
}

void Cyclometer::calculate(double seconds){

	double curr;
	double avg;
	double dist;
	int circumf;
	if(doCalculate){
		circumf = status->getCircumf();
		dist = status->getDistance();
		count++;
		avg = status->getAvgSpeed();
		curr = (circumf * speedfactor)/seconds;
		status->setCurrentSpeed(curr);
		status->setAvgSpeed(avg + ((curr-avg)/count));
		dist += circumf * distancefactor;
		status->setDistance(dist);
	}

}

void Cyclometer::setCalculations(bool in){
	this->doCalculate = in;
}

void Cyclometer::reset(){
	std::string id = stateMachine->getStateID();
	if(strcmp(id, "SetTireSizeMode") || strcmp(id, "SetKmMiMode")){

	}
	else{
		count = 0;
		status->reset();
	}
}

void Cyclometer::resetAll(){
	/*
	 * TODO Cyclometer tells statemachine a reset all request.
	 * Statemachine will have to transition to the intial state
	 */
	status -> reset();
	count = 0;

}
