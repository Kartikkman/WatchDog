// Include Definations of the functions declared inside the " SSD.h "

#include"SSD.h"





void SSD_command(uint8_t command)
{
          i2c_cmd_handle_t handle = i2c_cmd_link_create();                                           
        ESP_ERROR_CHECK(i2c_master_start(handle));                                                    // Placing the Start Bit on the Line ( SDA --> HIGH to LOW when  SCL ---> HIGH )
        ESP_ERROR_CHECK(i2c_master_write_byte(handle,(SSD1306_ADDR<<1)|I2C_MASTER_WRITE,ACK_EN));    // Placing the Adress on the Line 
        ESP_ERROR_CHECK(i2c_master_write_byte(handle,CONTROL_BYTE,ACK_EN));                          // Placing out the Control Byte on I2C ( for Non Continous transmission) of COmmand 
        ESP_ERROR_CHECK(i2c_master_write_byte(handle,command,ACK_EN));                                                // Placing the Actual Command 
        //ESP_ERROR_CHECK(i2c_master_write_byte(handle,NOP,ACK_EN));                                                   // Placing the No-Operation command on the bus , ( it is done so as the Master Holds the bus if there is 
        ESP_ERROR_CHECK(i2c_master_stop(handle));  
        int error_code = i2c_master_cmd_begin(I2C_NUM_0,handle,portMAX_DELAY);                                                                                           // No data avaialble or one needs to send the STOP command ), that could have lead to Not execution of 
        i2c_cmd_link_delete(handle);                                                                                             // previous command until there is some other data placed on the bus        

        if(  error_code != 0)
        {
            printf("Error occured is : %d",error_code);
        }

}

void SSD_commands(uint8_t *commands , uint8_t no_commands)
{
          i2c_cmd_handle_t handle = i2c_cmd_link_create();                                           
        ESP_ERROR_CHECK(i2c_master_start(handle));                                                    // Placing the Start Bit on the Line ( SDA --> HIGH to LOW when  SCL ---> HIGH )
        ESP_ERROR_CHECK(i2c_master_write_byte(handle,(SSD1306_ADDR<<1)|I2C_MASTER_WRITE,ACK_EN));    // Placing the Adress on the Line 
        ESP_ERROR_CHECK(i2c_master_write_byte(handle,CONTROL_BYTE1,ACK_EN));                          // Placing out the Control Byte on I2C ( for Continous transmission) of COommand 
        ESP_ERROR_CHECK(i2c_master_write(handle,commands,no_commands,ACK_EN));                          // Placing the Actual Command 
        //ESP_ERROR_CHECK(i2c_master_write_byte(handle,NOP,ACK_EN));                                   // Placing the No-Operation command on the bus , ( it is done so as the Master Holds the bus if there is 
        ESP_ERROR_CHECK(i2c_master_stop(handle));  
        int error_code = i2c_master_cmd_begin(I2C_NUM_0,handle, portMAX_DELAY);                        // No data avaialble or one needs to send the STOP command ), that could have lead to Not execution of 
        i2c_cmd_link_delete(handle);                                                                   // previous command until there is some other data placed on the bus        

        if(  error_code != 0)
        {
            printf("Error occured is : %d",error_code);
        }

}

void set_GDRAM()
{
    uint8_t commands[6] = {S_COL_ADD,0,127,S_PAGE_ADD,0,7};

    SSD_commands(commands,6);


}


void SSD_initialize()
{

          i2c_cmd_handle_t handle = i2c_cmd_link_create();
        ESP_ERROR_CHECK(i2c_master_start(handle));
        ESP_ERROR_CHECK(i2c_master_write_byte(handle,(SSD1306_ADDR<<1)|I2C_MASTER_WRITE,ACK_EN));
        ESP_ERROR_CHECK(i2c_master_write_byte(handle,CONTROL_BYTE1,ACK_EN));                        // Control Byte indicating that , there will be transmission of Commands befor the stop of this comm.

        // Now writing out the commands 
        ESP_ERROR_CHECK(i2c_master_write_byte(handle,DISPLAY_OFF,ACK_EN));
        ESP_ERROR_CHECK(i2c_master_write_byte(handle,MUX_RAT,ACK_EN));
       
        ESP_ERROR_CHECK(i2c_master_write_byte(handle,MUX,ACK_EN));
        ESP_ERROR_CHECK(i2c_master_write_byte(handle,OFFSET,ACK_EN));
        
        ESP_ERROR_CHECK(i2c_master_write_byte(handle,0,ACK_EN));
        ESP_ERROR_CHECK(i2c_master_write_byte(handle,START_LINE,ACK_EN));

        // COM Pin Configuration
        ESP_ERROR_CHECK(i2c_master_write_byte(handle,0xDA,ACK_EN));
        ESP_ERROR_CHECK(i2c_master_write_byte(handle,0x12,ACK_EN));

        ESP_ERROR_CHECK(i2c_master_write_byte(handle,OSC_FR,ACK_EN));
        ESP_ERROR_CHECK(i2c_master_write_byte(handle,OSC,ACK_EN));

        ESP_ERROR_CHECK(i2c_master_write_byte(handle,PUMP,ACK_EN));
        ESP_ERROR_CHECK(i2c_master_write_byte(handle,CHARGE,ACK_EN));

        ESP_ERROR_CHECK(i2c_master_write_byte(handle,ADD_MODE,ACK_EN));
        ESP_ERROR_CHECK(i2c_master_write_byte(handle,HORIZ_ADD,ACK_EN)); 
        
        ESP_ERROR_CHECK(i2c_master_write_byte(handle,0xA0,ACK_EN));
        ESP_ERROR_CHECK(i2c_master_write_byte(handle,0xC0,ACK_EN));

        ESP_ERROR_CHECK(i2c_master_write_byte(handle,CONTRAST_CONTROL,ACK_EN));
        ESP_ERROR_CHECK(i2c_master_write_byte(handle,0,ACK_EN));


        ESP_ERROR_CHECK(i2c_master_write_byte(handle,PRECHARGE,ACK_EN));
        ESP_ERROR_CHECK(i2c_master_write_byte(handle,0xF1,ACK_EN));

        ESP_ERROR_CHECK(i2c_master_write_byte(handle,0xDB,ACK_EN));
        ESP_ERROR_CHECK(i2c_master_write_byte(handle,0x49,ACK_EN));

        ESP_ERROR_CHECK(i2c_master_write_byte(handle,RAM_DISPLAY,ACK_EN));
        ESP_ERROR_CHECK(i2c_master_write_byte(handle,NORMAL_DISPLAY,ACK_EN));

        ESP_ERROR_CHECK(i2c_master_write_byte(handle,0x2E,ACK_EN));
        ESP_ERROR_CHECK(i2c_master_write_byte(handle,DISPLAY_ON,ACK_EN));

        ESP_ERROR_CHECK(i2c_master_stop(handle));
        
        int error_code = i2c_master_cmd_begin(I2C_NUM_0,handle,portMAX_DELAY);
        if(error_code != 0)
        {
            char *response = "Couldn't Send the Data";
            uart_write_bytes(UART_NUM_1,response,strlen(response));

        }

        i2c_cmd_link_delete(handle);

}

void SSD_push_data(uint8_t data)
{
        i2c_cmd_handle_t handle = i2c_cmd_link_create();
        ESP_ERROR_CHECK(i2c_master_start(handle));
        ESP_ERROR_CHECK(i2c_master_write_byte(handle,(SSD1306_ADDR<<1)|I2C_MASTER_WRITE,ACK_EN));
        ESP_ERROR_CHECK(i2c_master_write_byte(handle,CONTROL_BYTE3,ACK_EN));                    // Control Byte , indicating that there will be continous stream of Data passing befire the stop condition arises 
        
        int index = 0 ; 
        for(index =0; index < 1024; index ++)
        {
            ESP_ERROR_CHECK(i2c_master_write_byte(handle,data,ACK_EN));

        }
        
        ESP_ERROR_CHECK(i2c_master_stop(handle));
       int error_code =  i2c_master_cmd_begin(I2C_NUM_0,handle,portMAX_DELAY);

        if(error_code != 0)
        {
           char *msg = "An Error Occured ";
            uart_write_bytes(UART_NUM_1,msg,strlen(msg));

        }

        i2c_cmd_link_delete(handle);

}

void SSD_push_mat()
{

       i2c_cmd_handle_t handle = i2c_cmd_link_create();
        ESP_ERROR_CHECK(i2c_master_start(handle));
        ESP_ERROR_CHECK(i2c_master_write_byte(handle,(SSD1306_ADDR<<1)|I2C_MASTER_WRITE,ACK_EN));
        ESP_ERROR_CHECK(i2c_master_write_byte(handle,CONTROL_BYTE3,ACK_EN));                    // Control Byte , indicating that there will be continous stream of Data passing befire the stop condition arises 
       
        // Loading our matrix onto the Dis

        ESP_ERROR_CHECK(i2c_master_write(handle,mat[0],128,ACK_EN));
        ESP_ERROR_CHECK(i2c_master_write(handle,mat[1],128,ACK_EN));
        ESP_ERROR_CHECK(i2c_master_write(handle,mat[2],128,ACK_EN));
        ESP_ERROR_CHECK(i2c_master_write(handle,mat[3],128,ACK_EN));
        ESP_ERROR_CHECK(i2c_master_write(handle,mat[4],128,ACK_EN));
        ESP_ERROR_CHECK(i2c_master_write(handle,mat[5],128,ACK_EN));
        ESP_ERROR_CHECK(i2c_master_write(handle,mat[6],128,ACK_EN));
        ESP_ERROR_CHECK(i2c_master_write(handle,mat[7],128,ACK_EN));

         ESP_ERROR_CHECK(i2c_master_stop(handle));

        int error_code =  i2c_master_cmd_begin(I2C_NUM_0,handle,portMAX_DELAY);

        if(error_code != 0)
        {
           char *msg = "An Error Occured ";
            uart_write_bytes(UART_NUM_1,msg,strlen(msg));

        }

        i2c_cmd_link_delete(handle);


}

void SSD_INVERT()
{

    SSD_command((uint8_t)INVERT_DISPLAY);

}

void SSD_NORMAL()
{

   SSD_command((uint8_t)NORMAL_DISPLAY);

}




void set_pixel(int x , int y , int val)
{

	int page = y / 8 ;
	int bit = y % 8 ;

	mat[page][x] |= (val<<bit);


}

void draw_char(char ch , int x , int y)
{
	int font_index = (ch -32 )* 8;
	int y_limit = y + 8 , x_limit = x + 8;

	for( int x_pos = x ; x_pos < x_limit ; x_pos ++)
	{
		int bit_pos = 0 ;

		for(int y_pos = y ; y_pos < y_limit ; y_pos ++)
		{
			int temp = (( font_3[font_index ] ) & ( 1 << bit_pos ));
			if(temp)
			set_pixel(x_pos , y_pos , 1);
			else
			set_pixel(x_pos , y_pos , 0);

			bit_pos ++ ;

		}

		font_index ++ ;

	}

}


void draw_message(char *str, int x ,int y , int len)
{

	for(int index =0 ; index < len ; index ++)
	{

		draw_char(str[index],(x + (index*8) )%128,y + x/128);

	}


}

void clear_mat()
{

    for(int page = 0 ; page < 8; page ++)
    {

        for(int col = 0; col < 128 ; col ++)
        {

            mat[page][col] = 0;


        }

    }


}

/*

void create_symbol(char ch , int x , int y)
{

	int pos_a_glyph_detail = ch - symbols.unicode_first ;
	int width = symbols.glyph_dsc[pos_a_glyph_detail].w_px;
	int index = symbols.glyph_dsc[pos_a_glyph_detail].glyph_index;


	int pos  = 0 , bit_pos =0,row =0;

	for( int h_index = 0  ;h_index < symbols.h_px ; h_index ++)
	{
		bit_pos =0;

		for(int w_index = 0 ; w_index < width ; w_index ++)
		{

			int temp = (( symbols.glyph_bitmap[index] << bit_pos) & 0b10000000);
			if(temp)
			set_pixel(w_index + x,row + y,1);


			if ( bit_pos == 7)
			{	index ++;
				bit_pos = -1 ;
			}

			bit_pos ++;
		}

		row ++;
		//cout << "\n";
		index ++ ;


	}

}
*/
void show_char(char ch , int x , int y , lv_font_t *symbols)
{

	int pos_a_glyph_detail = ch - symbols->unicode_first ;
	int width = symbols->glyph_dsc[pos_a_glyph_detail].w_px;
	int index = symbols->glyph_dsc[pos_a_glyph_detail].glyph_index;


	int pos  = 0 , bit_pos =0,row =0;

	for( int h_index = 0  ;h_index < symbols->h_px ; h_index ++)
	{
		bit_pos =0;

		for(int w_index = 0 ; w_index < width ; w_index ++)
		{

			int temp = (( symbols->glyph_bitmap[index] << bit_pos) & 0b10000000);
			if(temp)	
			set_pixel(w_index + x,row + y,1);


			if ( bit_pos == 7 && w_index != width -1 )
			{	index ++;
				bit_pos = -1 ;
			}

			bit_pos ++;
		}

		row ++;
		//cout << "\n";
		index ++ ;


	}

}

void draw_line(int s_x,int s_y , int e_x, int e_y )
{

	float slope = (float)(e_y - s_y) / ( e_x - s_x) ;
	float y = s_y , x = s_x;

	if ( slope > 1)
	{

		// For slope greater than 1 , there will be 1 step change in y & equational change in x

		if ( s_x == 0 && s_y == 0)
			slope = 0 ;
		else
			slope = 1 / slope;

		while( y <= e_y)
		{
			x = (slope) * (y - s_y) + s_x ;
			set_pixel(x + 0.5,y,1);
			y ++ ;

		}




	}else if ( slope < 1)
	{
		// For slope less than 1 , there will be 1 step change in x & equational change in y

		while( x <= e_x)
		{
			y = ( slope * (x - s_x) ) + s_y;
			set_pixel(x,y + 0.5,1);
			x++;

		}

	}else if( slope == 1)
	{
		while(x <= e_x)
		{
			set_pixel(x,y,1);
			x++;
			y++;

		}

	}

}


void draw_lines(int s_x,int s_y , int e_x, int e_y , int ptx)
{
	float slope = (float)(e_y - s_y) / ( e_x - s_x) ;

	while(ptx)
	{

		draw_line(s_x,s_y,e_x,e_y);
		if (slope > 1)
		{
			s_x ++ ;
			e_x ++ ;
		}
		else if ( slope < 1)
		{
			s_y ++;
			e_y ++;

		}

	ptx --;

	}

}
