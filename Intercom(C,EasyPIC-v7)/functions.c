#include<p30fxxxx.h>
#include <stdlib.h>
#include <stdio.h> 
#include "driver.h"
#include "adc.h" 
#include <libpic30.h>
#include <string.h>
#include "timer.h"

//_FOSC(CSW_FSCM_OFF & XT_PLL4); instruction tact is same as crystal//
_FOSC(CSW_ON_FSCM_OFF & HS3_PLL4);
_FWDT(WDT_OFF);
_FGS(CODE_PROT_OFF);


unsigned int X, Y, x_value, y_value, n=0, j=10;
unsigned int counter_ms,stopwatch,ms,second;
int w=1;
int j1;
unsigned int  state3, state4, state5, state6, state7, num=0;
unsigned int state11= 0;
unsigned int button11=0;
unsigned char password[]={"1111"};
unsigned char a[4][2]={"1","2","3","4"};
unsigned char b[5]="";
 

//const unsigned int ADC_THRESHOLD = 900; 
const unsigned int AD_Xmin =220;
const unsigned int AD_Xmax =3642;
const unsigned int AD_Ymin =520;
const unsigned int AD_Ymax =3450;

unsigned int raw0,raw1,raw2,raw3;
unsigned int number,number1,number2,temp0,temp1; 
unsigned char tempRX;
#define DRIVE_A PORTCbits.RC13
#define DRIVE_B PORTCbits.RC14

void ConfigureTSPins(void)
{
	//ADPCFGbits.PCFG10=1;
	//ADPCFGbits.PCFG7=digital;

	//TRISBbits.TRISB10=0;
	TRISCbits.TRISC13=0;
    TRISCbits.TRISC14=0;
	
	//LATCbits.LATC14=0;
	//LATCbits.LATC13=0;
}

void initUART1(void)
{
    U1BRG=0x0015;//setting baudrate

    U1MODEbits.ALTIO = 0;//pin selection, primary or alternative

    IEC0bits.U1RXIE=1;//enable rx1 interrupt

    U1STA&=0xfffc;

    U1MODEbits.UARTEN=1;//turn on this module

    U1STAbits.UTXEN=1;//turn on transmitting
}

void __attribute__((__interrupt__)) _U1RXInterrupt(void) 
{
    IFS0bits.U1RXIF = 0;
    
    tempRX = U1RXREG;
   
    password[n] = tempRX;
    GoToXY(10,3);
    GLCD_Printf ("           ");
    GoToXY(10,3);
    GLCD_Printf ("NEW PASSWORD:");
    GoToXY(80,3);
        GLCD_Printf (password);
        n++;
    if ( n >= 4 )
    {                //restriction, no more than 5 locations
        n = 0;
   }
  
}


void WriteUART1(unsigned int data)
{
	  while(!U1STAbits.TRMT);

    if(U1MODEbits.PDSEL == 3)
        U1TXREG = data;
    else
        U1TXREG = data & 0xFF;
}

                    		   
//Function sends 4-digit numbers(digit by digit)
void WriteUART1dec2string(unsigned int data)
{
	unsigned char temp;

	temp=data/1000;
	WriteUART1(temp+'0');
	data=data-temp*1000;
	temp=data/100;
	WriteUART1(temp+'0');
	data=data-temp*100;
	temp=data/10;
	WriteUART1(temp+'0');
	data=data-temp*10;
	WriteUART1(data+'0');
}



void Delay(unsigned int N)
{
	unsigned int i;
	for(i=0;i<N;i++);
}

void Touch_Panel (void)
{
// horisontal transistors conducting
	DRIVE_A = 1;  
	DRIVE_B = 0;
    
     LATCbits.LATC13=1;
     LATCbits.LATC14=0;

	Delay(500); //waiting for AD conversion to be done
				
	// read x	
	x_value = temp0;//temp0 - value given by AD converter on bottom pin		

	// vertical transistors conducting
     LATCbits.LATC13=0;
     LATCbits.LATC14=1;
	DRIVE_A = 0;  
	DRIVE_B = 1;

	Delay(500); //waiting for AD conversion
	
	// read y	
	y_value = temp1;// temp1 is value given by AD convertor left pin	
	
//to make coordinates match screen resolution(128x64),x and y need to be scaled(0-128,0-64)
//scaling x
X=(x_value-161)*0.03629;



//X= ((x_value-AD_Xmin)/(AD_Xmax-AD_Xmin))*128;	

//scaling y
	Y= ((y_value-500)*0.020725);

//	Y= ((y_value-AD_Ymin)/(AD_Ymax-AD_Ymin))*64;
}


	
void __attribute__((__interrupt__)) _ADCInterrupt(void) 
{
	raw2 = ADCBUF0; // RB7 photo resistor					
	raw0 = ADCBUF1;//0
	raw1 = ADCBUF2;//1
    raw3 = ADCBUF3;
    
	temp0=raw0;
	temp1=raw1;

    IFS0bits.ADIF = 0;
} 

void Write_GLCD(unsigned int data)
{
unsigned char temp;

temp=data/1000;
Glcd_PutChar(temp+'0');
data=data-temp*1000;
temp=data/100;
Glcd_PutChar(temp+'0');
data=data-temp*100;
temp=data/10;
Glcd_PutChar(temp+'0');
data=data-temp*10;
Glcd_PutChar(data+'0');
}
//

void __attribute__ ((__interrupt__)) _T2Interrupt(void) // every 1ms
{

     TMR2 = 0 ; // clearing timer to make possible another interrupt
     ms=1;//ms flag

	counter_ms++;//ms counter
    stopwatch++;//Delay_ms counter

   if (counter_ms==1000)//sec
        {
          counter_ms=0;
          second=1;//sec flag

		 } 
	IFS0bits.T2IF = 0; 
       
}

void Delay_ms (int time)
	{
		stopwatch = 0;
		while(stopwatch < time);
	}



void alarm(int k)
{
    int i;
    for(i=0;i<k;i++){
            LATAbits.LATA11 = 1;
            Delay_ms(10);
            LATAbits.LATA11 =0;
            Delay_ms(6);
    }}

   
int servoMotor(int tmp){
    
    if(tmp==0){
        
            LATFbits.LATF6=1;
            Delay_ms(8);     
            LATFbits.LATF6=0;
            Delay_ms(192);    
            LATFbits.LATF6=1;
    }else{
       
            LATFbits.LATF6=1;
            Delay_ms(4);   
            LATFbits.LATF6=0;
            Delay_ms(196);   
            LATFbits.LATF6=1;
        
    }}
    






void main(void)
{    
    int i;
    unsigned int p=10,q=1;
    
    //configuring pins
    ADPCFGbits.PCFG7 = 0;  //photo resistor
	TRISBbits.TRISB7 = 0;  
    
    TRISDbits.TRISD8 = 0; //
    LATDbits.LATD8 = 0;
   
    
    TRISFbits.TRISF6 = 0; //servo
    TRISAbits.TRISA11 = 0;
    //TRISDbits.TRISD9=1;
    
    ADPCFGbits.PCFG11 =0; //mq3 
    TRISBbits.TRISB11 =0;
    
    
    TRISDbits.TRISD9=1;
    
    
    
  
    
    //configuring pins and GLCD
	ConfigureLCDPins();
	ConfigureTSPins();

	GLCD_LcdInit();

	GLCD_ClrScr();
    initUART1();
	
    Init_T2();
	ADCinit();
	ConfigureADCPins();
	ADCON1bits.ADON=1;
    
    
    
        // Initial screen
        GoToXY(4,1);
        GLCD_Printf (" Enter the password:");

		GLCD_Rectangle(3,3,120,40);
		GLCD_Rectangle(3,40,30,60);
        GLCD_Rectangle(30,40,60,60);
        GLCD_Rectangle(60,40,90,60);
        GLCD_Rectangle(60,40,120,60);
        
        
	    GoToXY(15,6);
        GLCD_Printf ("1");
        
        GoToXY(42,6);
        GLCD_Printf ("2");
    
        GoToXY(71,6);
        GLCD_Printf ("3");
        
        GoToXY(100,6);
        GLCD_Printf ("4");
        
    while(1)
		{ 
            
        Touch_Panel ();
       
  //photo resitor
    if(PORTDbits.RD9 == 1){
           if(raw2 < 0010){
                LATDbits.LATD8=1;
                Delay_ms(10000);
                LATDbits.LATD8=0;
           }else{  
                 LATDbits.LATD8=0;
           }}
      
     
     //mq3 sensor   
     if (raw3 > 0100){
            Delay_ms(1000);
            alarm(70);
           }            
        
      //Writing entered digits
        
        if ((1<X)&&(X<30)&& (1<Y)&&(Y<20))
				{
					if(state4<21)//state-taster must be pushed for some time
      					state4++;
				}
			else
      				state4=0;//not enough time pushed

			if(state4==20)
        {GoToXY(p,2);
        GLCD_Printf (a[0]);
        
        q++;
        p=(q%5)*10; num++; strcat(b,a[0]);}
        
         if ((30<X)&&(X<60)&& (1<Y)&&(Y<20))
				{
					if(state5<21)//state-taster must be pushed for some time
      					state5++;
				}
			else
      				state5=0;//not enough time pushed

			if(state5==20) 
        {GoToXY(p,2);
        GLCD_Printf (a[1]);
        q++;
        p=(q%5)*10; num++; strcat(b,a[1]);}
        
        if ((60<X)&&(X<90)&& (1<Y)&&(Y<20))
				{
					if(state6<21)//state-taster must be pushed for some time
      					state6++;
				}
			else
      				state6=0;//not enough time pushed

			if(state6==20) 
        {GoToXY(p,2);
        GLCD_Printf (a[2]);
        q++;
        p=(q%5)*10; num++; strcat(b,a[2]);}
        
        if ((90<X)&&(X<120)&& (1<Y)&&(Y<20))
				{
					if(state7<21)//state-taster must be pushed for some time
      					state7++;
				}
			else
      				state7=0;//not enough time pushed

			if(state7==20) 
        {GoToXY(p,2);
        GLCD_Printf (a[3]);
        q++;
        p=(q%5)*10; num++; strcat(b,a[3]);}
        
        
        
      //Checking the password
        
        if(num==4) {  
            
            if(!strcmp(b,password)) 
            {
              
              Delay(5000);
            GoToXY(80,2);
        GLCD_Printf ("OPEN");
            for( i=7; i >0; i--){
             servoMotor(0);
            }
        
            WriteUART1('O');
            WriteUART1('N');
            Delay_ms(5000);
             for( i=7; i >0; i--){
             servoMotor(90);}
            alarm(20);
          }else{
            
       Delay(5000);
     GoToXY(80,2);
     GLCD_Printf("ERROR");
        
        alarm(150);}
        num=0;
            
        GoToXY(4,2);
        GLCD_Printf ("                   ");
        p=10;
        q=1;
        
        strcpy(b,"");
        
        GoToXY(10,3);
        GLCD_Printf ("                  ");
        
        }

                
    
        
        
        }//while
}//main

