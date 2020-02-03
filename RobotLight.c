/*
 * File:   RobotLight.c
 * Author: user
 *
 * Created on September 4, 2019, 11:12 PM
 */

//includes
#include "p24FJ64GA002.h"
#include "ezbl.h"
//definitions
#define RED LATBbits.LATB6
#define GREEN LATBbits.LATB8
#define ORANGE LATBbits.LATB7
#define WALK LATBbits.LATB13
#define WAIT LATBbits.LATB12


//main program
int main(void)
{
    enum state{INIT}PROGstate;
    
    
        //set up i/o
    PROGstate= INIT;
    switch(PROGstate)
    {
        
        case INIT: RED = 1;
                        GREEN = 0;
                        ORANGE = 0;
                        WALK = 1; 
                        WAIT = 0;
        
                        TRISBbits.TRISB6=0;
                        TRISBbits.TRISB7=0;
                        TRISBbits.TRISB8=0;
                        TRISBbits.TRISB12=0;
                        TRISBbits.TRISB13=0;
                        
                        
                        
        //set up interrupts for timer 3 and notification change
        
                        IPC2bits.T3IP=4;
                        IFS0bits.T3IF=0;
                        IEC0bits.T3IE=1;
                       
        
        
        //configure timer 2
        
                        TMR2=0;
                        PR2=0x8967;
                        PR3=0x9;
                        T2CON=0x8020;
                        T2CONbits.T32=1;
                        
        
        //change notification setup
                               
                        IFS1bits.CNIF=0;
                        IEC1bits.CNIE=1;
                        IPC4bits.CNIP=5;
                        CNEN2bits.CN27IE=1;
                        break;
                        
        
                        
    } 
        
    while(1)
    {
    }
    
      
       
        
    
    return 0;
}

void _ISR _T3Interrupt()
{
   enum states{ORANGEstate,REDstate,GREENstate}LEDstate;
   
   LEDstate=ORANGEstate;
   switch(LEDstate)
    {
       case ORANGEstate:if(GREEN==1)   //Orange state
                        {
                            TMR2=0;
                            GREEN=0;
                            ORANGE=1;
         
                            PR2=0xDC6B;
                            PR3=0x2;
                            LEDstate=REDstate;
                        
                            break;
         
                        }
       else case REDstate: if(ORANGE==1)     //Red state
                        {
                            TMR2=0;
                            ORANGE=0;
                            RED=1;
                            PR2=0x8967;
                            PR3=0x9;
         
                            WAIT=0;
                            WALK=1;
                            LEDstate=GREENstate;
                            break;
                        }
       else case GREENstate: if(RED==1)    //Green state
                        {
                            TMR2=0;
                            RED=0;
                            GREEN=1;
                            WALK=0;
                            WAIT=1;
                            PR2=0x9C37;
                            PR3=0x1C;
                            LEDstate=ORANGEstate;
                            break;
         
                        }
    }
    
     

    IFS0bits.T3IF=0;
    
}

void _ISR _CNInterrupt()
{
  
   
    if(GREEN==1)
    {
        TMR2=0;
        PR2=0x003E;
        PR3=0x0000;
       
    }
    
    IFS1bits.CNIF=0;

}
//java -jar ezbl_tools.jar --communicator -com=COM3 -baud=9600 -artifact=FLASHING