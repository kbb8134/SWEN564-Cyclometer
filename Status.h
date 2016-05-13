/*
 * Status.h
 *
 *  Created on: May 4, 2016
 *      Author: Madeleine Daigneau & Kristopher Brown
 */

#ifndef STATUS_H_
#define STATUS_H_

#include "An7Seg.h"
#include "StateID.h"

class Status {

	double currentSpeed;
	double avgSpeed;
	double distance;
	int circumf;
	float elapsedTime;
	bool km;
	int count;
	AN7SEG an1;
	AN7SEG an2;
	AN7SEG an3;
	AN7SEG an4;
	// variables for seven segment displays & LEDs

public:

	Status();

	// GETs
	bool getKm();
	double getCurrentSpeed();
	double getAvgSpeed();
	double getDistance();
	int getCircumf();
	float getTime();
	int getCount();
	// SETs
	void setKm(bool);
	void setCurrentSpeed(double);
	void setAvgSpeed(double);
	void setDistance(double);
	void setCircumf(int);
	void setTime(float);
	void setCount(int);
	// Reset variables
	void reset();
	// 7 segment displays
	AN7SEG getAnode(int id);
	void setAnode(int id, int num, bool dp);
	void updateDisplay(StateID);
};

#endif /* STATUS_H_ */
