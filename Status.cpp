/*
 * Status.cpp
 *
 *  Created on: May 4, 2016
 *      Author: Madeleine Daigneau & Kristopher Brown
 */

#include "Status.h"

Status::Status() {
	this -> currentSpeed = 0.0;
	this -> avgSpeed = 0.0;
	this -> distance = 0.0;
}

double Status::getAvgSpeed(){
	return this -> avgSpeed;
}

double Status::getCurrentSpeed(){
	return this -> currentSpeed;
}

double Status::getDistance(){
	return this -> distance;
}

int Status::getCircumf(){
	return circumf;
}

void Status::setAvgSpeed(double in){
	this -> avgSpeed = in;
}

void Status::setCurrentSpeed(double in){
	this -> currentSpeed = in;
}

void Status::setDistance(double in){
	this -> distance = in;
}

void Status::setCircumf(int in){
	circumf = in;
}

void Status::reset(){
	circumf = 210;
	distance = 0;
	currentSpeed = 0;
	avgSpeed = 0;
}
