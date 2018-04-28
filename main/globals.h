#ifndef __GLOBALS_H_
#define __GLOBALS_H_


 typedef struct 
 {

     char seconds[2];
     char min[2];
     char hour[2];
     char day[2];
     char date[2];
     char month[2];
     char year[2];
     char century[2];

 }Time;


typedef struct 
{
int category;                                                   // Categories are : Email , Call , Message , Missed Call , SMS , 
int no_notify ; 
char text[18];             // Maximum Length of the string inside the Alert is 18 

}Alert;


Alert trial[10];
extern char alert_categories[6][15] ;
Time time;



 #endif