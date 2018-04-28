
#ifndef __DS3231_H__
#define __DS3231_H__

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <stdio.h>
#include "esp_log.h"
#include"driver/uart.h"
#include"esp_err.h"
#include"string.h"
#include"driver/i2c.h"


#define SLAVE_ADDR 104                              // Address of DS3231 ( Real Time Clock ) 

char * bcd_char(uint8_t *arr,int length_arr);       // Function which converts the BCD no into the Character Array ( Used after receiving Time from RTC -- For Example : BCD NO : 2,3 to ASCII Code of '2','3')
uint8_t *convert_bcd(uint8_t *arr);                 // Function which converts the BCD no into Integer ( For Example : BCD NO : 2,3 to 23 )
char * DS3231_get_time();                           // Function which obtains the time from DS3231 ( Calls the raw I2C functions & receives the Data )
void DS3231_update_time(uint8_t *addr_register_write,uint8_t *data_register_write); // Function to Update the Time stores inside the RTC ( DS3231 )  ( Calls the raw I2C functions & sends the Data which needs to be written )



#endif