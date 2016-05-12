/*
 * Status.h
 *
 *  Created on: May 4, 2016
 *      Author: Madeleine Daigneau & Kristopher Brown
 */

#ifndef STATUS_H_
#define STATUS_H_

class Status {

	double currentSpeed;
	double avgSpeed;
	double distance;
	int circumf;
	// variables for seven segment displays & LEDs

public:

	Status();

	double getCurrentSpeed();
	double getAvgSpeed();
	double getDistance();
	int getCircumf();
	void setCurrentSpeed(double);
	void setAvgSpeed(double);
	void setDistance(double);
	void setCircumf(int);
	void reset();
};

#endif /* STATUS_H_ */
