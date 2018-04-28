/*
 * big_symbols.h
 *
 *  Created on: Apr 9, 2018
 *      Author: kartik
 */

#ifndef SRC_BIG_SYMBOLS_H_
#define SRC_BIG_SYMBOLS_H_
#include <stdint.h>

#ifndef _STRUCT_FONT_
#define _STRUCT_FONT_
// Structure Format for storing each character in Font 
typedef struct
{
	int w_px;
	int glyph_index;

}lv_font_glyph_dsc_t;



// Structure Format for storing compelete chracter set 

typedef struct
{
	int unicode_first;
	int unicode_last;
	int h_px;
	const uint8_t *glyph_bitmap;
	const lv_font_glyph_dsc_t *glyph_dsc;
	int unicode_list;


}lv_font_t;


#endif





extern const uint8_t big_symbols_glyph_bitmap[];
extern const lv_font_glyph_dsc_t big_symbols_glyph_dsc[];
extern  lv_font_t big_symbols;



#endif /* SRC_BIG_SYMBOLS_H_ */
