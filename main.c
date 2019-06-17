/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/

#if defined(__XC)
    #include <xc.h>        /* XC8 General Include File */
#elif defined(HI_TECH_C)
    #include <htc.h>       /* HiTech General Include File */
#elif defined(__18CXX)
    #include <p18cxxx.h>   /* C18 General Include File */
#endif

#if defined(__XC) || defined(HI_TECH_C)

#include <stdint.h>        /* For uint8_t definition */
#include <stdbool.h>       /* For true/false definition */

#endif

#include "system.h"        /* System funct/params, like osc/peripheral config */
#include "user.h"          /* User funct/params, such as InitApp */
#define _XTAL_FREQ 20000000

/******************************************************************************/
/* User Global Variable Declaration                                           */
/******************************************************************************/
unsigned int duty=1;
unsigned int per=200;
unsigned int t_on;
unsigned int t_off;
bool inc_duty=false;
bool dec_duty=false;
unsigned int count_up=0;
unsigned int count_duty=0;


/* i.e. uint8_t <variable_name>; */

/******************************************************************************/
/* Main Program                                                               */
/******************************************************************************/
/* Function prototype */
void delay_100us(unsigned int us);

void main(void)
{
    /* Configure the oscillator for the device */
    ConfigureOscillator();

    /* Initialize I/O and Peripherals for application */
    InitApp();

    /* TODO <INSERT USER APPLICATION CODE HERE> */
    unsigned int max_cont_up=20000/per; /* tiempo para que empiece a bajar */
    unsigned int max_count_duty=100000/(per*per);
    t_on=duty;
    t_off=per-duty;
    while(1)
    {
        LATAbits.LA0=1;
        delay_100us(t_on);
        LATAbits.LA0=0;
        delay_100us(t_off);
        if(PORTAbits.RA1==1){
            count_up+=1;
        }
        else if (count_up!=0) { /* si la cuenta =/=0, deje de incrementar o decrementar duty */
            if(inc_duty || dec_duty){
                inc_duty=false;
                dec_duty=false;
            }
            else if(count_up>max_cont_up) {
                dec_duty=true;
            }
            else {
                inc_duty=true;
            }
            count_up=0;
        }
        if(inc_duty){
            count_duty+=1;
            
            if(count_duty==max_count_duty){
                if(duty<per){
                    duty+=1;    
                }
                else{
                    inc_duty=false;
                }            
                count_duty=0;
                t_on=duty;
                t_off=per-duty;
            }
        }
        else if(dec_duty){
            count_duty+=1;
            if(count_duty==max_count_duty){
                if(duty>0){
                    duty-=1;  
                }
                else{
                    dec_duty=false;
                }  
                count_duty=0;
                t_on=duty;
                t_off=per-duty;
            }
        }
    }
}

/* Function definitions */

void delay_100us(unsigned int us){
    unsigned int i;
    for(i=0;i<us;i++){
        __delay_us(100);
    }
}
