/**
 * @file bcd.c
 * @author Alex Mikhalev
 * @date Sep 14, 2015
 */

#include "bcd.h"

uint8_t bcd8_to_uint(bcd8 bcd) {
	return bcd.tens * 10 + bcd.ones;
}

bcd8 uint_to_bcd8(uint8_t uint) {
	bcd8 result = { .ones = 0, .tens = 0 };
	while (uint >= 10) {
		uint -= 10;
		result.tens += 1;
	}
	result.ones = uint;
	return result;
}

int bcd8_cmp(bcd8 bcd_left, bcd8 bcd_right) {
	if (bcd_left.tens == bcd_right.tens) {
		return ((int) bcd_left.ones) - ((int) bcd_right.ones);
	} else {
		return ((int) bcd_left.tens) - ((int) bcd_right.tens);
	}
}

bcd8 bcd8_normalize(bcd8 bcd) {
	while (bcd.ones >= 10) {
		bcd.ones -= 10;
		bcd.tens++;
	}
	return bcd;
}

bcd8 bcd8_bounded_add(bcd8 bcd_left, bcd8 bcd_right, bcd8 bcd_min, bcd8 bcd_max) {
	bcd8 result = { .ones = bcd_left.ones + bcd_right.ones, .tens =
			bcd_left.tens + bcd_right.tens };
	result = bcd8_normalize(result);
	if (bcd8_cmp(result, bcd_max) > 0) {
		return bcd_min;
	} else {
		return result;
	}
}

bcd8 bcd8_bounded_sub(bcd8 bcd_left, bcd8 bcd_right, bcd8 bcd_min, bcd8 bcd_max) {
	int16_t ones = ((int16_t) bcd_left.ones) - ((int16_t) bcd_right.ones);
	int16_t tens = ((int16_t) bcd_left.tens) - ((int16_t) bcd_right.tens);
	while (ones < 0) {
		ones += 10;
		tens--;
	}
	bcd8 result = bcd8_normalize((bcd8) { .ones = ones, .tens = tens });
	if (bcd8_cmp(result, bcd_min) < 0) {
		return bcd_min;
	} else {
		return result;
	}
}


