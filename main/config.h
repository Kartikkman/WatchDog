// Contains Declarations of Functions to configure the I2C , UART interface for the uC 

#ifndef __CONFIG_H__
#define __CONFIG_H__

#include"driver/gpio.h"
#include"stdlib.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <stdio.h>
#include "esp_log.h"
#include"driver/uart.h"
#include"esp_err.h"
#include"string.h"
#include"driver/i2c.h"



uint8_t mat[8][128] ;


// Aknowledgement Constants 

#define ACK_EN 0x00                          // Sending the Acknowledgement after receiving the byte 
#define ACK_DIS 0x1                          // For NOt sending the Acknowledgement after receiving the Byte 


// UART Constants ( Pin No , Baud Rate , Buffer Size ) 

#define TX 21
#define RX 22 
#define RTS 14
#define CTS 15
#define UART_BUF_SIZE 1024
#define BAUD_RATE 115200

//I2C Constants ( Clock Speed , Pin No , Buffer Size , Slave Address )

#define CLK_SPEED 390000                      // Running the SSD1306 Display @ max speed 
#define SDA 4                           
#define SCL 5 
#define SLAVE_ADDR 104
#define BUFFER_SIZE 1024
#define SSD1306_ADDR 0x3C                     // Address of the Display 




void uart_config();                           // Function for configuring & Installing the Driver for UART ( Pin No , Baud Rate , Parity , Stop Bit , Flow Control )
void configure_I2C();                         // Function for configuring & Installing the Drive for I2C ( Pin No , Mode : Slave / Master , Clock Speed  , Address , Pull Up Modes) 

#endif