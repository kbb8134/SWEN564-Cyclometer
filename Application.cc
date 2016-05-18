/*Application.cc
 *
 * The main file for running the Cyclometer simulation
 *
 * Author: Kristopher Brown & Madeleine Daigneau
 *
 */

#include "IOControl.h"
#include "Cyclometer.h"

#include <pthread.h>
#include <queue>

int main(int argc, char** argv){
	// Create message queue
	std::queue< Event > q;
	pthread_mutex_t accessQ;
	pthread_mutex_init(&accessQ, NULL);

	// Construct Cyclometer
	printf("Create Cyclometer\n");
	Cyclometer cycl(&q,&accessQ);

	// Construct IOControl
	printf("Create IOControl\n");
	IOControl ioctrl(&q,&accessQ);

	// Infinite read/write signals loop
	printf("IOControl receive\n");
	ioctrl.receive();

	return 0;
}
