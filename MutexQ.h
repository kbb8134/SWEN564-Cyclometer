/*
 * MutexQ.h
 *
 *  Created on: May 9, 2016
 *      Author: mad1948
 */

#ifndef MUTEXQ_H_
#define MUTEXQ_H_

#include <pthread.h>
#include <queue>
#include "Event.h"

class MutexQ {
private:
	std::queue< Event > q;
	pthread_mutex_t* accessQ;

public:
	MutexQ();
	virtual ~MutexQ();

	void lock();
	void unlock();
	Event read();
	void write(Event);

};

#endif /* MUTEXQ_H_ */
