/**
 * @file    ds1337.c
 * @author  Alex Mikhalev
 * @date    May 20, 2015
 */

#include <ds1337.h>

#include <i2cmaster.h>
#include <stddef.h>

void ds1337_init() {
	i2c_init();
}

static uint8_t read_byte(uint8_t reg) {
	i2c_start_wait(DS1337_ADDRESS + I2C_WRITE);
	i2c_write(reg);
	i2c_rep_start(DS1337_ADDRESS + I2C_READ);
	uint8_t byte = i2c_readNak();
	i2c_stop();
	return byte;
}

static void write_byte(uint8_t reg, uint8_t byte) {
	i2c_start_wait(DS1337_ADDRESS + I2C_WRITE);
	i2c_write(reg);
	i2c_write(byte);
	i2c_stop();
}

#define GETTER_METHOD(NAME, REG_NAME) \
	bcd8 inline ds1337_get_ ## NAME () { \
		return (bcd8) { .bcd = read_byte(DS1337_REG_ ## REG_NAME) }; \
	}

#define SETTER_METHOD(NAME, REG_NAME) \
	void inline ds1337_set_ ## NAME (bcd8 bcd) { \
		write_byte(DS1337_REG_ ## REG_NAME, bcd.bcd); \
	}

#define REG_METHODS(NAME, REG_NAME) \
	GETTER_METHOD(NAME, REG_NAME) \
	SETTER_METHOD(NAME, REG_NAME)

REG_METHODS(seconds, SECONDS);
REG_METHODS(minutes, MINUTES);
REG_METHODS(hour, HOUR);
REG_METHODS(day, DAY);
REG_METHODS(control, CONTROL);
REG_METHODS(status, STATUS);
