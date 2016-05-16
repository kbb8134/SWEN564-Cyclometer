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
	an1 = OFF;
	an2 = OFF;
	an3 = OFF;
	an4 = OFF;
	km = true;
}
//GETs
bool Status::getTimeout()
{
	return pulseTimeout;
}
bool Status::getCalc()
{
	return calc;
}

bool Status::getKm()
{
	return km;
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

float Status::getTime(){
	return elapsedTime;
}

int Status::getCount()
{
	return count;
}

// SETs
void Status::setTimeout(bool in)
{
	pulseTimeout = in;
}

void Status::setCalc(bool in)
{
	calc = in;
}

void Status::setKm(bool in)
{
	km = in;
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
	if( circumf > 220 )
		circumf = 190;
}

void Status::setTime(float in){
	this -> elapsedTime = in;
}

void Status::setCount(int in)
{
	count = in;
}

void Status::reset(){
	circumf = 210;
	distance = 0;
	currentSpeed = 0;
	avgSpeed = 0;
	elapsedTime = 0.0;
}

void Status::updateDisplay(StateID id)
{
	int min;
	int sec;
	int seg1000;
	int seg100;
	int seg10;
	int seg1;
	bool curr10 = false;
	bool avg10 = false;
	switch(id)
	{
	case SETTIRESIZEMODE:
		seg100 = circumf/100;
		seg10 = (circumf - 100*seg100)/10;
		seg1 = circumf - 100*seg100 - 10*seg10;
		setAnode(1,-1,false);
		setAnode(2,seg100,false);
		setAnode(3,seg10,false);
		setAnode(4,seg1,false);
		break;
	case SETKMMIMODE:
		setAnode(1,-1,false);
		setAnode(2,-1,false);
		setAnode(3,-1,false);
		if(km) setAnode(4,1,false);
		else setAnode(4,2,false);
		break;
	case TIMEMODE:
		min = (elapsedTime/60);
		sec = elapsedTime - min*60;
		seg1000 = (min/10);
		seg100 = min - seg1000*10;
		seg10 = (sec/10);
		seg1 = ( sec - seg10*10 )/1;
		setAnode(1,seg1000,false);
		setAnode(2,seg100,true);
		setAnode(3,seg10,false);
		setAnode(4,seg1,false);
		break;
	case DISTANCEMODE:
		seg1000 = (distance/100);
		seg100 = ((distance - seg1000*100)/10);
		seg10 = (distance - seg1000*100 - seg100*10);
		seg1 = ((distance - seg1000*100 - seg100*10 - seg10)*10)/1;
		if(seg1000 > 0) setAnode(1,seg1000,false);
		else setAnode(1,-1,false);
		if(seg100 > 0) setAnode(2,seg100,false);
		else setAnode(2,-1,false);
		setAnode(3,seg10,true);
		setAnode(4,seg1,false);
		break;
	case SPEEDMODE:
		curr10 = (currentSpeed < 10);
		avg10 = (avgSpeed < 10);
		if( curr10 )
		{
			seg1000 = (currentSpeed)/1;
			seg100 = (10*(currentSpeed - seg1000))/1;
		}
		else
		{
			seg1000 = (currentSpeed/10);
			seg100 = (currentSpeed - seg1000*10)/1;
		}
		if( avg10 )
		{
			seg10 = (avgSpeed)/1;
			seg1 = (10*(avgSpeed - seg10))/1;
		}
		else
		{
			seg10 = (avgSpeed/10);
			seg1 = (avgSpeed - seg10*10)/1;
		}
		setAnode(1,seg1000,curr10);
		setAnode(2,seg100,false);
		setAnode(3,seg10,avg10);
		setAnode(4,seg1,false);
		break;
	default:
		break;
	}
}

AN7SEG Status::getAnode(int id)
{
	switch(id)
	{
	case 1:
		return an1;
		break;
	case 2:
		return an2;
		break;
	case 3:
		return an3;
		break;
	case 4:
		return an4;
		break;
	default:
		break;
	}
}

void Status::setAnode(int id, int num, bool dp)
{
	AN7SEG an;
	switch(num)
	{
	case 0:
		an = ZERO;
		if(dp) an = ZERODP;
		break;
	case 1:
		an = ONE;
		if(dp) an = ONEDP;
		break;
	case 2:
		an = TWO;
		if(dp) an = TWODP;
		break;
	case 3:
		an = THREE;
		if(dp) an = THREEDP;
		break;
	case 4:
		an = FOUR;
		if(dp) an = FOURDP;
		break;
	case 5:
		an = FIVE;
		if(dp) an = FIVEDP;
		break;
	case 6:
		an = SIX;
		if(dp) an = SIXDP;
		break;
	case 7:
		an = SEVEN;
		if(dp) an = SEVENDP;
		break;
	case 8:
		an = EIGHT;
		if(dp) an = EIGHTDP;
		break;
	case 9:
		an = NINE;
		if(dp) an = NINEDP;
		break;
	default:
		an = OFF;
		break;
	}
	switch(id)
	{
	case 1:
		an1 = an;
		break;
	case 2:
		an2 = an;
		break;
	case 3:
		an3 = an;
		break;
	case 4:
		an4 = an;
		break;
	default:
		break;
	}
}
