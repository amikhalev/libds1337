/**
 * A library for interfacing with the DS1337 I2C real time clock on AVR devices.
 * @file    ds1337.h
 * @author  Alex Mikhalev
 * @date    May 20, 2015
 */

#ifndef DS1337_H_
#define DS1337_H_

/************
 * Includes *
 ************/

#include <stdint.h>
#include "bcd.h"

/*********************
 * Address constants *
 *********************/

#define DS1337_ADDRESS				(0b11010000)
#define DS1337_REG_SECONDS			(0x00)
#define DS1337_REG_MINUTES			(0x01)
#define DS1337_REG_HOUR				(0x02)
#define DS1337_REG_DAY				(0x03)
#define DS1337_REG_DATE				(0x04)
#define DS1337_REG_MONTH_CENT		(0x05)
#define DS1337_REG_YEAR				(0x06)
#define DS1337_REG_ALARM1_SECONDS	(0x07)
#define DS1337_REG_ALARM1_MINUTES	(0x08)
#define DS1337_REG_ALARM1_HOUR		(0x09)
#define DS1337_REG_ALARM1_DAY_DATE	(0x0A)
#define DS1337_REG_ALARM2_MINUTES	(0x0B)
#define DS1337_REG_ALARM2_HOUR		(0x0C)
#define DS1337_REG_ALARM2_DAY_DATE	(0x0D)
#define DS1337_REG_CONTROL			(0x0E)
#define DS1337_REG_STATUS 			(0x0F)

/*******************
 * Limit constants *
 *******************/

#define DS1337_MIN_SECONDS			(0)
#define DS1337_MIN_MINUTES			(0)
#define DS1337_MIN_HOUR_12			(1)
#define DS1337_MIN_HOUR_24			(0)
#define DS1337_MIN_DAY				(1)
#define DS1337_MIN_DATE				(1)
#define DS1337_MIN_MONTH			(1)
#define DS1337_MIN_YEAR				(0)

#define DS1337_MAX_SECONDS			(59)
#define DS1337_MAX_MINUTES			(59)
#define DS1337_MAX_HOUR_12			(12)
#define DS1337_MAX_HOUR_24			(23)
#define DS1337_MAX_DAY				(7)
#define DS1337_MAX_DATE				(31)
#define DS1337_MAX_MONTH			(12)
#define DS1337_MAX_YEAR				(99)

#define DS1337_INCR(VALUE, TYPE) \
	VALUE = bcd8_bounded_add(VALUE, (bcd8) { .ones = 1 }, uint_to_bcd8(DS1337_MIN_ ## TYPE), \
			uint_to_bcd8(DS1337_MAX_ ## TYPE))

/********************
 * Public functions *
 ********************/

/**
 * Initializes i2c communications with the RTC.
 */
void ds1337_init();

/**
 * Gets the seconds byte from the RTC.
 * @return The seconds byte, BCD-encoded.
 */
bcd8 ds1337_get_seconds();

/**
 * Sets the seconds byte in the RTC.
 * @param seconds What to set the seconds byte to, BCD-encoded
 */
void ds1337_set_seconds(bcd8 seconds);

/**
 * Gets the minutes byte from the RTC.
 * @return The minutes byte, BCD-encoded.
 */
bcd8 ds1337_get_minutes();

/**
 * Sets the minutes byte in the RTC.
 * @param minutes What to set the minutes byte to, BCD-encoded
 */
void ds1337_set_minutes(bcd8 minutes);

/**
 * Gets the hour byte from the RTC.
 * @return The hour byte, BCD-encoded.
 */
bcd8 ds1337_get_hour();

/**
 * Sets the hour byte in the RTC.
 * @param hour What to set the hour byte to, BCD-encoded
 */
void ds1337_set_hour(bcd8 hour);

/**
 * Gets the day byte from the RTC.
 * @return The day byte, with 1 being Sunday and 7 being Saturday.
 */
bcd8 ds1337_get_day();

/**
 * Sets the day byte in the RTC.
 * @param day The day byte, with 1 being Sunday and 7 being Saturday.
 */
void ds1337_set_day(bcd8 day);

/**
 * Gets the control byte from the RTC.
 * @return The control byte
 */
bcd8 ds1337_get_control();

/**
 * Sets the control byte in the RTC.
 * @param control What to set the control byte to.
 */
void ds1337_set_control(bcd8 control);

/**
 * Gets the status byte from the RTC.
 * @return The status byte
 */
bcd8 ds1337_get_status();

/**
 * Sets the status byte in the RTC.
 * @param status What to set the status byte to.
 */
void ds1337_set_status(bcd8 status);

#endif /* DS1337_H_ */
