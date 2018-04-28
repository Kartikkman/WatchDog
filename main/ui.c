#include"ui.h"
#include"fonts.h"
#include"globals.h"


int (*func_ptr[])(int touch) = {time_display,sub_menu,led_gui,alert_gui};
int status = TIME ;

int led_gui(int touch)
{
    clear_mat();                                      // Clearing the previous data out of Mat 
    char ch[2] = {'w','v'};                           // At the v: LED ON , w : LED OFF     
    bool current_state = gpio_get_level(LED);   
    show_char(ch[current_state],30,10,&big_symbols);  // Drawing out the symbols onto the display    

    if ( touch == SELECT)
    {
        current_state = (!current_state) ;
        gpio_set_level(LED,current_state);
        printf("LED status Now %d",current_state);

    }

    return 0;

}



int alert_gui(int touch)
{
    if( touch == SELECT)
    status = TIME;
    
    
    char *alert_msg = "ALERTS !!!";

    clear_mat();
    draw_message(alert_msg,20,10,strlen(alert_msg));

    char *alert_msgs[60] ; 
    // char ch = trial[0].no_notify + '0';
    // draw_message(&ch,20,19,1);


       for(int alert_no = 1 ; alert_no < 4; alert_no ++)
    {

        draw_message(&alert_categories[alert_no],20,( alert_no -1 )*8 + 30,strlen(alert_categories[alert_no]));
        char ch = trial[alert_no].no_notify + '0' ;
        draw_message(&ch,60,( alert_no -1 )*8 + 30,1);
        draw_message(trial[alert_no].text,70,( alert_no -1 )*8 + 30,strlen(trial[alert_no].text));


    }




    // Raw Code for printing the msgs on Screen , as snprintf not giving desired results ( Need to Debug it later !! ) 
/*


       for(int alert_no = 1 ; alert_no < 5; alert_no ++)
    {

        snprintf(alert_msgs,60,"%s : %d ; %s ",alert_categories[alert_no],trial[alert_no].no_notify ,trial[alert_no].text);
        draw_message(alert_msgs,20,alert_no*8 + 30,strlen(alert_msg));

    }

    */

   return 0 ;

}



int sub_menu(int touch)
{
	// C : Messages , F : Games , N : Heart Rate Sensor , U : Calls , V : Settings , i : Bluetooth , m : Whatsapp , u : Flashlight , W : Left Arrow for Pointing
		char list_seq[] = {'F','C','m','N','i','u','V'};
        static int curr_pos = 1;
        static int prev_pos = 0 ;
        static int next_pos = 2 ;

			if ( touch == RIGHT_SLIDE)
			{
				curr_pos ++;
				prev_pos ++;
				next_pos ++;

			}else if (touch == LEFT_SLIDE)
			{
				curr_pos --;
				prev_pos --;
				next_pos --;

			}else if ( touch == SELECT)
			{
				printf("Current Position is : %d",curr_pos);
                
                if ( curr_pos == 5)
                {
                    status = LED_GUI ; 
                    printf(" LED status has been selectd ");
                }
                 if ( curr_pos == 1)
                {
                    status = ALERT_GUI ;
                    printf("Alert Status Selected from Menu ");

                }


			}

			clear_mat();
			show_char(list_seq[prev_pos], 95 , 5,&small_symbols);
			show_char(list_seq[curr_pos], 95 , 25,&small_symbols);
			show_char(list_seq[next_pos], 95 , 45,&small_symbols);
			show_char('W',120,26,&small_symbols);
			show_char(list_seq[curr_pos], 10, 14,&big_symbols);
			draw_lines(70,0,85,60,3);

    return 0 ;
}


int time_display(int touch)
{

        draw_message("Time",64,10,strlen("Time"));
        
         //char *Date_msg = time.date[0] + time.date[1] + ' \\ ' + time.month[0] + time.month[1] + ' \\ ' + time.century[0] + time.century[1] + time.year[0] + time.year[1] +'\0' ;

        //char *sample_msg = "Kartik";

        if((touch == RIGHT_SLIDE ))
        {
            status = MENU;
            printf("Status has been changed ");
        }
        char *time_msg = (char *) malloc(sizeof(char) * 8);
        char *date_msg = (char *) malloc(sizeof(char) * 10);

        time_msg[0] = time.hour[0] ; 
        time_msg[1] = time.hour[1] ; 
        time_msg[2] = ':' ;
        time_msg[3] = time.min[0] ; 
        time_msg[4] = time.min[1] ; 
        time_msg[5] = ':' ;
        time_msg[6] = time.seconds[0] ; 
        time_msg[7] = time.seconds[1] ; 

        date_msg[0] = time.date[0];
        date_msg[1] = time.date[1];
        date_msg[2] = '/';
        date_msg[3] = time.month[0];
        date_msg[4] = time.month[1];
        date_msg[5] = '/';
        date_msg[6] = time.century[0];
        date_msg[7] = time.century[1];
        date_msg[8] = time.year[0];
        date_msg[9] = time.year[1];


         clear_mat();
         draw_message("Time & Date ",10,10,strlen("Time & Date "));
         draw_message(time_msg,30,34,8);
         draw_message(date_msg,30,54,10);
        free(time_msg);
        free(date_msg);

        return 0;

}

