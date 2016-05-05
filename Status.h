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

public:

	Status();

	double getCurrentSpeed();
	double getAvgSpeed();
	double getDistance();
	void setCurrentSpeed(double);
	void setAvgSpeed(double);
	void setDistance(double);
};

#endif /* STATUS_H_ */
