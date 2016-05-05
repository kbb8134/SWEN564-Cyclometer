/*
 * States.cpp
 *
 *  Created on: May 4, 2016
 *      Author: Madeleine Daigneau & Kristopher Brown
 */

#include "States.h"

State* States::TIRE_SIZE = new SetTireSizeMode("SetTireSizeMode");
State* States::KM_MI = new SetKmMiMode("SetKmMiMode");
State* States::TIME = new TimeMode("TimeMode");
State* States::DISTANCE = new DistanceMode("DistanceMode");
State* States::SPEED = new SpeedMode("SpeedMode");
