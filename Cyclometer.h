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
#define IO_PORT_SIZE 1 //TODO Probably change this later

#include <pthread.h>
#include "StateMachine.h"
#include "Status.h"
#include <string>
#include <queue>
#include "StaticObj.h"
#include "State.h"

#include <cstdio>
#include <stdint.h>
#include <sys/neutrino.h>
#include <sys/mman.h>
#include <hw/inout.h>

#define CTRL_ADDRESS 0x288 // Base 280h + 8

class Cyclometer {

	StateMachine* stateMachine;
	//Status* status;

	pthread_t thread;
	bool doCalculate; //false if it should not be calculating
	float speedfactor;
    float distancefactor;
    bool units; //If ki or miles. false if km, true if miles
    long count;
    uintptr_t ctrlHandle;

public:
	Cyclometer();
	virtual ~Cyclometer();

	void calculate(double seconds);
	void setCalculations(bool);
	void reset();
	void resetAll();
	void checkQ();
};

#endif /* CYCLOMETER_H_ */
