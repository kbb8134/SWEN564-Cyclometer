/*
 * Cyclometer.h
 *
 *  Created on: May 4, 2016
 *      Author: Madeleine Daigneau & Kristopher Brown
 */

#ifndef CYCLOMETER_H_
#define CYCLOMETER_H_

#include "StateMachine.h"
#include "Status.h"

class Cyclometer {

	StateMachine* stateMachine;
	Status* status;
	bool doCalculate;

public:
	Cyclometer();
	virtual ~Cyclometer();

	void calculate();
	void setCalculations(bool);
};

#endif /* CYCLOMETER_H_ */
