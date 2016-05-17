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
#define PULSETIMEOUT 7.92 // Seconds to wheel pulse timeout
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
#include <time.h>
#include <unistd.h>

#define CTRL_ADDRESS 0x288 // Base 280h + 8

#include <pthread.h>
#include <queue>

class Cyclometer {

	StateMachine* stateMachine;
	//Status* status;

	pthread_t thread;
	bool doCalculate; //false if it should not be calculating
	bool autoMode; //true if in automatic mode.
	float speedfactor;
    float distancefactor;
    bool units; //If ki or miles. false if km, true if miles
    long count;
    uintptr_t ctrlHandle;
    time_t lastPulse;
    time_t startTrip;

	std::queue< Event > *q;
	pthread_mutex_t *accessQ;
public:
	Cyclometer();
	Cyclometer( std::queue<Event>* qin, pthread_mutex_t *aQ );
	virtual ~Cyclometer();

	void calculate(int seconds);
	void setCalculations(bool);
	void setAutoMode(bool);
	void reset();
	void resetAll();
	void checkTimeout();
	void checkQ();
};

#endif /* CYCLOMETER_H_ */
