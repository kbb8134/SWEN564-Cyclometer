/*
 * StaticMutexQ.h
 *
 *  Created on: May 9, 2016
 *      Author: mad1948
 */

#ifndef STATICMUTEXQ_H_
#define STATICMUTEXQ_H_

#include "MutexQ.h"

class StaticMutexQ {
public:
	static MutexQ* mutexQ;
};

#endif /* STATICMUTEXQ_H_ */
