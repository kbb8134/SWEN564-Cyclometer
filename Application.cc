/*Application.cc
 *
 * The main file for running the Cyclometer simulation
 *
 * Author: Kristopher Brown & Madeleine Daigneau
 *
 */

#include "IOControl.h"
#include "Cyclometer.h"

int main(int argc, char** argv){

	// Construct Cyclometer
	printf("Create Cyclometer\n");
	//Cyclometer cycl;

	// Construct IOControl
	printf("Create IOControl\n");
	IOControl ioctrl;

	// Infinite read/write signals loop
	printf("IOControl receive\n");
	ioctrl.receive();

	return 0;
}
