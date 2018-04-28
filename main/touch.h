
#ifndef __TOUCH_H__
#define __TOUCH_H__


#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <stdio.h>
#include "esp_log.h"
#include"driver/uart.h"
#include"esp_err.h"
#include"string.h"
#include"driver/i2c.h"
#include"fonts.h"


#define THRESHOLD 600                               // The threshold value has been determined through Polling approach 
#define LED 19                                      // LED ( can be used for Notification or Flash Light )
TaskHandle_t task_handle;                    // Task Handles are used to refer the task from another task or Interrupt , Example Case may be of waking up a task from interrupt .



int compare_arr(uint32_t *arr1 , uint32_t *arr2, int len);  // Used for chechking whether two arrays are equal or not ( utilized in Slide Detection )
void configure_gpio(int arr[],int len_arr);                // Function to configure the GPIO for Touch as well as for LED 
void touch_handler(void *args);                             // Interrupt Handler for Touch 

#endif