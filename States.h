/*
 * States.h
 *
 *  Created on: May 4, 2016
 *      Author: Madeleine Daigneau & Kristopher Brown
 */

#ifndef STATES_H_
#define STATES_H_

#include "State.h"
#include "SetTireSizeMode.h"
#include "SetKmMiMode.h"
#include "TimeMode.h"
#include "DistanceMode.h"
#include "SpeedMode.h"

class States {
public:

	static State* TIRE_SIZE;
	static State* KM_MI;
	static State* TIME;
	static State* DISTANCE;
	static State* SPEED;

};

#endif /* STATES_H_ */
