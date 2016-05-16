/*
 * MutexQ.cpp
 *
 *  Created on: May 9, 2016
 *      Author: mad1948
 */

#include "MutexQ.h"

MutexQ::MutexQ() {
	// TODO Auto-generated constructor stub
	 pthread_mutex_init(accessQ, NULL);
}

MutexQ::~MutexQ() {
	// TODO Auto-generated destructor stub
}

void MutexQ::lock(){
	//pthread_mutex_lock(accessQ);
}

void MutexQ::unlock(){
	//pthread_mutex_unlock(accessQ);
}

void MutexQ::write(Event e){
	q.push(e);
}

Event MutexQ::read(){
	Event e = NONE;
	if( ~q.empty() )
	{
		e = q.front();
		q.pop();
	}
	return e;
}
