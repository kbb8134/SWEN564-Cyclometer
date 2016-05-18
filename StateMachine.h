/*
 * StateMachine.h
 *
 *  Created on: May 4, 2016
 *      Author: Kristopher Brown & Madeleine Daigneau
 */

#ifndef STATEMACHINE_H_
#define STATEMACHINE_H_

#define KMF .0036 // Factor of conversion for cm/s to km/hr
#define MIF .00223694 // Factor of conversion for cm/s to mph
#define MICMF .000006213711922 //Factor of conversion for cm to mi
#define KMCMF .00001 //Factor of conversion for cm to km

#include <pthread.h>
#include <string>
#include <time.h>
#include <unistd.h>
#include <cmath>
#include <cfloat>

#include "StaticObj.h"
#include "Event.h"
#include "StateID.h"

class State;
class StateMachine {

	State* currentState;
	pthread_t thread;
    time_t startTrip;
	bool doCalculate; //false if it should not be calculating
	bool autoMode; //true if in automatic mode.
	float speedfactor;
    float distancefactor;
    bool units; //If ki or miles. false if km, true if miles
    long count;

public:
	StateMachine();
	virtual ~StateMachine();

	void transition(State* state);
	StateID getStateID();
	void acceptEvent(Event e);
	void update();
	void calculate(double seconds);
	void setCalculations(bool);
	void setAutoMode(bool);
	void reset();
	void setUnits(bool);

	bool getCalculations();
	bool getAutoMode();
};

#endif /* STATEMACHINE_H_ */
