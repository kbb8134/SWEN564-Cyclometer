/*
 * StaticMutexQ.cpp
 *
 *  Created on: May 9, 2016
 *      Author: mad1948
 */

#include "StaticMutexQ.h"

MutexQ* StaticMutexQ::mutexQ = new MutexQ();
