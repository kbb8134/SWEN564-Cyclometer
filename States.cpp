/*
 * States.cpp
 *
 *  Created on: May 4, 2016
 *      Author: Madeleine Daigneau & Kristopher Brown
 */

#include "States.h"

State* States::TIRE_SIZE = new SetTireSizeMode(SETTIRESIZEMODE);
State* States::KM_MI = new SetKmMiMode(SETKMMIMODE);
State* States::TIME = new TimeMode(TIMEMODE);
State* States::DISTANCE = new DistanceMode(DISTANCEMODE);
State* States::SPEED = new SpeedMode(SPEEDMODE);
