/**
 * @file bcd.h
 * @author Alex Mikhalev
 * @date Sep 11, 2015
 */

#ifndef BCD_H_
#define BCD_H_

#include <stdint.h>

typedef union {
	uint8_t bcd;
	struct {
		uint8_t ones :4;
		uint8_t tens :4;
	};
} bcd8;

uint8_t bcd8_to_uint(bcd8 bcd);

bcd8 uint_to_bcd8(uint8_t uint);

int bcd8_cmp(bcd8 bcd_left, bcd8 bcd_right);

bcd8 bcd8_normalize(bcd8 bcd);

bcd8 bcd8_bounded_add(bcd8 bcd_left, bcd8 bcd_right, bcd8 bcd_min, bcd8 bcd_max);

bcd8 bcd8_bounded_sub(bcd8 bcd_left, bcd8 bcd_right, bcd8 bcd_min, bcd8 bcd_max);

#endif /* BCD_H_ */
