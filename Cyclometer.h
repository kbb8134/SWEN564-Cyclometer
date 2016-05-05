/*
 * Cyclometer.h
 *
 *  Created on: May 4, 2016
 *      Author: Madeleine Daigneau & Kristopher Brown
 */

#ifndef CYCLOMETER_H_
#define CYCLOMETER_H_

#define KMF .0036 // Factor of conversion for cm/s to km/hr
#define MIF .00223694 // Factor of conversion for cm/s to mph
#define MICMF .000006213711922 //Factor of conversion for cm to mi
#define KMCMF .00001 //Factor of conversion for cm to km

#include "StateMachine.h"
#include "Status.h"
#include <string>

class Cyclometer {

	StateMachine* stateMachine;
	Status* status;

	bool doCalculate; //false if it should not be calculating
	float speedfactor;
    float distancefactor;
    bool units; //If ki or miles. false if km, true if miles
    long count;

public:
	Cyclometer();
	virtual ~Cyclometer();

	void calculate(double seconds);
	void setCalculations(bool);
	void reset();
	void resetAll();
};

#endif /* CYCLOMETER_H_ */
