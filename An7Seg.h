/*
 * An7Seg.h
 *
 *  Created on: May 13, 2016
 *      Author: kbb8134
 */

#ifndef AN7SEG_H_
#define AN7SEG_H_


enum AN7SEG { // DECIMAL POINT ACTIVE - binary OR to deactivate = (1)|AN7SEG
	OFF = 0xFF, 	//11111111 -> all segments off
	ZERO = 0x03, 	//00000011
	ONE = 0x9F,
	TWO = 0x29,
	THREE = 0x0D,
	FOUR = 0x99,
	FIVE = 0x49,
	SIX = 0x41,
	SEVEN = 0x1F,
	EIGHT = 0x01,
	NINE = 0x09,
	OFFDP = 0xFE, 	//11111110 -> all segments off w/ decimal point
	ZERODP = 0x02, 	//00000010
	ONEDP = 0x9E,
	TWODP = 0x28,
	THREEDP = 0x0C,
	FOURDP = 0x98,
	FIVEDP = 0x48,
	SIXDP = 0x40,
	SEVENDP = 0x1E,
	EIGHTDP = 0x00,
	NINEDP = 0x08
};


#endif /* AN7SEG_H_ */
