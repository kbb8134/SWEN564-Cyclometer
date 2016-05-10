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

	// Construct IOControl
	IOControl ioctrl;
	Cyclometer cycl;

	ioctrl.receive();

	return 0;
}
