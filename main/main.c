// A menu based UART program for the testing purposes of I2C communication with DS3231 

/*

Here is the procedure to be followed for impolementing the above details : 

As the program is based on UART protocol : 
1. Configuring the UART interface for the MCU 
2.Writing the lower level functions for sending & receiving of bytes  ( Already provided by the RTOS -- missing in the case of MSP430 )
3.Presenting the Menu form this UART interface 

 Here are the following pins used for Touch : 

TOUCH_PAD_NUM5 --> GPIO12 ( Used for Turning ON the LED ) 
TOUCH_PAD_NUM4 --> GPIO13 ( Used for Turning OFF the LED )
TOCUH_PAD_NUM7 --> GPIO27 (Used for Initiating a task to TURN ON & TURN OFF the LED ) 
TOUCH_PAD_NUM8 --> GPIO 33

*/

// Interrupt is a combined interrupt for all the GPIOs ,so we will be chekcing out the GPIO which was touched inside the interrupt & taking the action based upon it . 

#include"globals.h"
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
#include"config.h"
#include"DS3231.h"
#include"SSD.h"
#include"fonts.h"
#include"touch.h"
#include "nvs_flash.h"
#include "esp_bt.h"
#include "esp_gap_ble_api.h"
#include "esp_gatts_api.h"
#include "esp_bt_main.h"
#include "gatts_table_creat_demo.h"
#include"ble_application.h"
#include"ui.h"


void send_data();
int time_display(int touch);
i2c_cmd_handle_t SSD_stat_comm();
void set_GDRAM();
int compare_arr(uint32_t *arr1 , uint32_t *arr2, int len);
void configure_gpio(int arr[],int len_arr);

void configure_BLE();
void print_alerts();


TaskHandle_t xHandle;
QueueHandle_t touch ;


char *opt_msg = "\r\n\r\n****SSD1306 Testing ****\r\n1.Initialize Display\r\n2.Turn ON the Display ??\r\n3.Turn  OFF the Display \r\n4.Send Data '1'\r\n5.Send Data '0'\r\n7.Send a char to Display \r\n";

int a = 0 ;
#define HIGH 1
#define LOW 0



// The value of the Pin No correspoinding to Touch_PAD No has been taken from Library itself , here these are used for providing user friendly names ( reffereable through Pin No )
#define TOUCH_PIN12 TOUCH_PAD_NUM5
#define TOUCH_PIN13 TOUCH_PAD_NUM4
#define TOUCH_PIN27 TOUCH_PAD_NUM7
#define TOUCH_PIN33 TOUCH_PAD_NUM8



 /* Now receiving the string containing the current time , here is the description about the contents of the string : 

            Every field is of 2 chracters  ( means Seconds , Min , Hours each will be represented by two-two characters each  )

            First 2 Characters : Seconds 
            Next 2 Characters : Minuets 
            Next 2 Characters : Hour 
            Next 2 Chracters : Day 
            Next 2 Characters : Date 
            Next 2 Characters : Month 
            Next 2 Characters : Year 



            Note : There needs to applied extreme level of error handling on the I2C side plus pointer handling side so that segmentation fault doesn't occur more over 
            any I2C based errors are also reported . 

        */

void update_time(void *args)
{

    uart_config();
    configure_I2C();

    while(1)
    {

       char *Time = DS3231_get_time();

       time.seconds[0]  = Time[0];
       time.seconds[1] = Time[1];

       time.min[0]  = Time[2];
       time.min[1] = Time[3];

       time.hour[0]  = Time[4];
       time.hour[1] = Time[5];

       time.day[0]  = Time[6];
       time.day[1] = Time[7];

       time.date[0]  = Time[8];
       time.date[1] = Time[9];

       time.month[0] = Time[10];
       time.month[1] = Time[11];

       time.year[0] = Time[12];
       time.year[1] = Time[13];

       time.century[0] = '2';
       time.century[1] = '0';
       
     //  printf(" TIme is : %c%c",time.hour[0],time.hour[1]);

    free(Time);
       vTaskDelay(300/portTICK_RATE_MS);

    }

}


void display(void *args)
{
    SSD_initialize();
    int * p = (int *) malloc(sizeof(int)) ;

    while(1)
    {


         //printf("\n\nTIme is :  %s",time_msg);
        // printf("\n\nTIme is :  %c%c",Time_msg[0],Time_msg[1]);
       //  printf("\nDate is : %14c",Date_msg);
        
        *p =-1 ;

        if (xQueueReceive(touch,p,10/portTICK_RATE_MS) !=0)
        {
            printf("\nValue received inside the Queue is : %d",(*p));

        }

        (*func_ptr[status])(*p);
         SSD_push_mat();
  
   vTaskDelay(40/portTICK_RATE_MS);



    }

}


   /* Task should be eliminated , uptill finger is taken off the Touch Pad 
         Further Optimizations : IncludeLeft SLide also  , if there is any zero in the middle dataset then Task should be exited 
         More Features : Selection Pin , ( TOuch Start at Pin is the Touch Left at that Pin ) 
                         Left Slide Detection as well . 
*/


void slide_task(int *args)
{
    
    configure_gpio((int *)args,4);
    // vTaskSuspend(NULL);                     // For suspending this own task 
    int prev = 0,current = 0,index = 0;
    uint32_t touched_pad[8] ;
    uint32_t check_pad[4] = {1<<(int)args[0] ,1<<(int)args[1],1<<(int)args[2],1<<(int)args[3]};
    uint32_t right_slide[2*4] = {check_pad[0],check_pad[0] | check_pad[1] , check_pad[1] , check_pad[1] | check_pad[2], check_pad[2],check_pad[2] | check_pad[3],check_pad[3] , 0};
    uint32_t left_slide[2*4] = {check_pad[3],check_pad[3] | check_pad[2],check_pad[2],check_pad[2] | check_pad[1],check_pad[1],check_pad[1] | check_pad[0],check_pad[0],0};
    int *status = 0;


    while(1)
    {

         ESP_ERROR_CHECK(touch_pad_intr_disable());
        current= touch_pad_get_status();
        touch_pad_clear_status();
          
        if (current != prev ) 
        {
            touched_pad[index] = current;
            prev = current ; 
            index ++ ;
            printf("Pin Touched :%d\n",current);

             if ( index != 7 && current == 0)
             {   
                   if ( index == 2 || index == 3)
                   {   printf("Select Detected");
                        status = SELECT;
                        xQueueSend(touch,&(status),100/portTICK_RATE_MS);

                    }

                index = 8;
            
             }

        }


        vTaskDelay(75/portTICK_RATE_MS);                      // To accomodate the filter period , if reading are taken during the filter period ,then it gives 0's 

    if( index == 8) 
        {


            index = 0 ;
            current = 0; 
          printf("\nValue of the array : %d,%d,%d,%d,%d,%d,%d,%d",touched_pad[0],touched_pad[1],touched_pad[2],touched_pad[3],touched_pad[4],touched_pad[5],touched_pad[6],touched_pad[7]);
           if(compare_arr(right_slide,touched_pad,8))
           {
               status = RIGHT_SLIDE;
               xQueueSend(touch,&(status),100/portTICK_RATE_MS);
           }
            if(compare_arr(left_slide,touched_pad,8))
             {  
                   status = LEFT_SLIDE ;
                   xQueueSend(touch,&(status),100/portTICK_RATE_MS);
                   printf("\nLEFT SLide Detected");
             }

            vTaskDelay(100/portTICK_RATE_MS);               // Giving a one second delay , so as to prevent the task from re-running after one slide has occured 
           
            ESP_ERROR_CHECK(touch_pad_intr_enable());       // Now enabling back the interrupts
             vTaskSuspend(NULL);                          // WHen the 7 readings are taken then we suspend the task 


        }
     


    }

}


 void app_main(void)
{
    int arr[4] = {TOUCH_PIN12,TOUCH_PIN13,TOUCH_PIN27,TOUCH_PIN33};
  xTaskCreate(update_time,"Receiving Time from DS3231",2048,NULL,10,NULL);
 xTaskCreate(display,"Displaying Task",2048,NULL,8,NULL);
  xTaskCreate(slide_task,"Touch Interface",2048,arr,5,&task_handle);
  //symbol_task();
 // xTaskCreate(symbol_task,"Symbol Testing",2048,NULL,5,NULL);
 touch = xQueueCreate(5,sizeof(int));  
     configure_BLE();


}






/*

To change the vlaue fo the Attribute localy , we need to set the attribute value according to the handle , 
To disable the notification , indication .


Inside the New Alert Service  : 

Format : Category( 1 Byte ) , No_Notofication , Last_Name


In the Defining of the Structure for the Alerts , ther could have been two approaches : 
1.Creating array of Objects , each object has Properties : ID , No_Alert , Name 
  User Layer would access that API by deferencing the array 

2. Creating array of categories & Alerts inside the Structure 
    & Defrencing the value of array inside that Structure 




*/




/*

Already Tested : 
void symbol_task()
{
    SSD_initialize();
    uart_config();
    uint8_t * ch = ( uint8_t *) malloc(sizeof(uint8_t));
    while(1)
    {

     uart_write_bytes(UART_NUM_1,"\r\nEnter the Charcter you want to display on screen ",strlen("Enter the Charcter you want to display on screen "));
     uart_read_bytes(UART_NUM_1,ch,1,portMAX_DELAY);
     clear_mat();
     create_symbol(*ch,10,10);
     SSD_push_mat();


    }

}

////////////////////


NOTES : 

1. In the ESP-32 microcontroller , Pull Resistor have been found to be sufficient for the comm. purposes .
2. ALso there is serious need to create & Delete the handle otherwise many times it has lead to the bugs.

DS3231 Reading fucnition is compelete & now for the writing function , proto is compelete 
, final yet needs to be written . 


Further Updates :


1. Getting the value of Status Register or all register & display it via UART 
2. Making it more User friendly  ( improvement s in current menu ) 
3. Error Reporting : Debugging Errors ( wheere each errors like : Wire not connected , Pull- Ups missising should be given by the system ) 
4.Updating the current variable names ( especially of the Acknowledgment which is curently called with the help of 0 or 1 ) 

Error Reporting to be Priority 1 ( as the Segmentation fault error would be occuring & more errors to occur ) , so error reporting is must for designing a 
robust system . 


For the purpose of Structure bsed design of the State machine , the Structure can be used to store the function pointer easily  ( inspite the fact that 
it can't store the function inside them ) .z



*/


/*

 For the purpose of the state machine design : 
 Follow the Game State , Enum video 
 & also refer to the follwing link for more clear explanation : https://stackoverflow.com/questions/1371460/state-machines-tutorials

 Things Learned so far : 
 1. There needs to be two array : One for Storing the current State
                                  Another for storing the pointer to the function ( which needs to be executed for that state ) 
2. There may be furhter support of the structure in the current system , to support the backward tracking of the states ( if reqd .)

                    
A good tutorial , relating the State Machine Design with the reference to the micro controllers ( GPIO INterface )
http://blog.mbedded.ninja/programming/general/control-methodology/a-function-pointer-based-state-machine

Learned from the above Page : 

1.THere is structuer made for the State , Event , Function pointer . 
    Based upon the matching of the State , Event . ( Function pointer is called ) 
    For Example : Current State ( LED OFF , Event : Switch is Pressed for OFF ) then the LED OFF function would be called 
                  Current State (LED ON , Event : Swithc is Pressed for LED ON ) then no function would be called . 


Size of the enum : https://stackoverflow.com/questions/366017/what-is-the-size-of-an-enum-in-c?utm_medium=organic&utm_source=google_rich_qa&utm_campaign=google_rich_qa


Now , Adding up the Flash Light Feature : 
1. TURN ON the LED 
2. TURN OFF the LED 

Delays Inside the Task should be minimum , as it makes the UI sluggish as the Task is put into blocking mode 

For GUI design of the Flash Light : 


Refer to this link for learning about the defination of constants : http://www.cplusplus.com/forum/beginner/56491/

*/