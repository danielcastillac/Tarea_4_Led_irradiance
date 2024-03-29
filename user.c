/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/

#if defined(__XC)
    #include <xc.h>         /* XC8 General Include File */
#elif defined(HI_TECH_C)
    #include <htc.h>        /* HiTech General Include File */
#elif defined(__18CXX)
    #include <p18cxxx.h>    /* C18 General Include File */
#endif

#if defined(__XC) || defined(HI_TECH_C)

#include <stdint.h>         /* For uint8_t definition */
#include <stdbool.h>        /* For true/false definition */

#endif

#include "user.h"

/******************************************************************************/
/* User Functions                                                             */
/******************************************************************************/

/* <Initialize variables in user.h and insert code for user algorithms.> */

void InitApp(void)
{
    /* TODO Initialize User Ports/Peripherals/Project here */
    PORTA=0; /* cero en decimal, estoy limpiando */
    /* PORTAbits.RA1=0; para un bit en especifico*/
    LATA=0;
    /* Setup analog functionality and port direction */
    ADCON1=0x0F;
    /* ADCON1bits.PCFG=0b1111; si quiero cambiar  */
    /* Initialize peripherals */
    TRISAbits.RA0=0; /* LED */
    TRISAbits.RA1=1; /* Switch */
    /* Configure the IPEN bit (1=on) in RCON to turn on/off int priorities */

    /* Enable interrupts */
}

