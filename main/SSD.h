#ifndef __SSD_H__
#define __SSD_H__


#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <stdio.h>
#include "esp_log.h"
#include"driver/uart.h"
#include"esp_err.h"
#include"string.h"
#include"driver/i2c.h"
#include"fonts.h"
#include"config.h"

// OLED Display ( 128 * 64 ) Commands , Commands of Page 28 of Data sheet

#define ENTIRE_DISPLAY 0xA5
#define RAM_DISPLAY 0xA4

#define NORMAL_DISPLAY 0xA6
#define INVERT_DISPLAY 0xA7

#define DISPLAY_ON 0xAF
#define DISPLAY_OFF 0xAE


#define PUMP 0x8D
#define CHARGE 0x14

#define PRECHARGE 0xD9


#define MUX_RAT 0xA8
#define MUX 0x3F

#define OSC_FR 0xD5
#define OSC 0x80

#define CONTROL_BYTE 0b10000000          // Control Byte for non-continuous , COmmand Mode
#define CONTROL_BYTE1 0b00000000         // COntrol Byte for continuous , Command Mode

#define CONTROL_BYTE2 0b1100000000      // Control Byte for non-continuous , Data Mode
#define CONTROL_BYTE3 0x40      		// Control Byte for continuous , Data Mode


#define OFFSET 0xD3
#define START_LINE 0x40

#define CONTRAST_CONTROL 0x81

#define ADD_MODE 0x20

#define HORIZ_ADD 0b00000000			// In Horizontal Addressing Mode , Page Address is automatically incremented 
#define PAGE_ADD 0b0000001
#define VERTI_ADD 0b000010

#define S_COL_ADD 0x21
#define S_PAGE_ADD 0x22

#define COL_START 0
#define PAGE_START 0

#define COL_END 127
#define PAGE_END 7

#define NOP 0xE3


void SSD_command(uint8_t command);	// Function to send a single Command to Display ( makes the call to RAW I2C functions & writes command acc. to format specified in the Dev. Guide )
void SSD_commands(uint8_t *commands , uint8_t no_commands); // FUnction to send multiple Commands at one GO !! ( makes the call to RAW I2C functions )
void set_GDRAM();// For setting the Pointer to the positon (0,0) in GDRAM 
void SSD_initialize();// Function to initialize the SSD display ( Battery Powered , Coloumn Config , Row Config , Multiplex , Oscillator Period)
void SSD_push_mat();//Function to send Data to Display ( Pushes the Software Buffer Data onto the Display )( makes call to RAW I2C functions , sends Data acc. to Format)
void SSD_INVERT(); // Function to invert the Display ( 1 treated as OFF , 0 as ON for the pixel ) 
void SSD_NORMAL(); // FUnction usually called after Inverting the Display to make it back to normal 
void set_pixel(int x , int y , int val);//Function to set pixel at the particular position in Display ( Core function, utilized to draw character where position of the pixel is specified to draw at  )
void draw_char(char ch , int x , int y);//Takes the character out of Fonts & draws on the Buffer ( makes call to set_pixel )
void draw_message(char *str, int x ,int y , int len);// Draws out the complete message onto the screen ( makes call to draw char function)
void clear_mat();// Used for clearing out the buffer ( filling it with zeroes , Used before drawing any new message onto the screen ) 
void show_char(char ch , int x , int y , lv_font_t *symbols);// Draws Icon/Symbol on Screen of those taken from libvfont
void draw_line(int s_x,int s_y , int e_x, int e_y );// For drawing out the line on the screen ( DDA Line drawing algorithm ) 
void draw_lines(int s_x,int s_y , int e_x, int e_y , int ptx); // Draws Line ( taking the width of the line as input ) 



#endif