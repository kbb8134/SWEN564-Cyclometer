/*
 * An7Seg.h
 *
 *  Created on: May 13, 2016
 *      Author: kbb8134
 */

#ifndef AN7SEG_H_
#define AN7SEG_H_


enum AN7SEG { // DECIMAL POINT ACTIVE - binary OR to deactivate = (1)|AN7SEG
	OFF = 0xFE, 	//11111111 -> all segments off
	ZERO = 0x02, 	//00000010
	ONE = 0x9E,
	TWO = 0x28,
	THREE = 0x0C,
	FOUR = 0x98,
	FIVE = 0x48,
	SIX = 0x40,
	SEVEN = 0x1E,
	EIGHT = 0x00,
	NINE = 0x08,
	OFFDP = 0xFF, 	//11111111 -> all segments off
	ZERODP = 0x03, 	//00000010
	ONEDP = 0x9F,
	TWODP = 0x29,
	THREEDP = 0x0D,
	FOURDP = 0x99,
	FIVEDP = 0x49,
	SIXDP = 0x41,
	SEVENDP = 0x1F,
	EIGHTDP = 0x01,
	NINEDP = 0x09
};


#endif /* AN7SEG_H_ */
