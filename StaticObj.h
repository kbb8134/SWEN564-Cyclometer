/*
 * StaticObj.h
 *
 *  Created on: May 9, 2016
 *      Author: mad1948
 */

#ifndef STATICOBJ_H_
#define STATICOBJ_H_

#include "MutexQ.h"
#include "Status.h"

class StaticObj {
public:
	static MutexQ* mutexQ;
	static Status* status;
};

#endif /* STATICOBJ_H_ */
