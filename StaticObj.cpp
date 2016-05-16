/*
 * StaticMutexQ.cpp
 *
 *  Created on: May 9, 2016
 *      Author: mad1948
 */

#include "StaticObj.h"

MutexQ* StaticObj::mutexQ = new MutexQ();
Status* StaticObj::status = new Status();

