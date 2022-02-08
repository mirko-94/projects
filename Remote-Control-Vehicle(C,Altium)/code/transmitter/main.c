#include <p30fxxxx.h>
#include "timer2.h"

_FOSC(CSW_FSCM_OFF & XT_PLL4);//instruction takt je isti kao i kristal
_FWDT(WDT_OFF);

unsigned char tempRX;
unsigned int naredba, i;

void initUART1(void){
    
    U1MODEbits.ALTIO = 0;
    U1BRG = 0x0207;
    U1STA &= 0xFFFC;
    U1MODEbits.UARTEN = 1;
    U1STAbits.UTXEN = 1;
    IEC0bits.U1RXIE = 1;
}

void __attribute__((__interrupt__)) _U1RXInterrupt(void) 
{
    IFS0bits.U1RXIF = 0;
tempRX=U1RXREG;

}

void writeUART1( unsigned int data )
{
    while ( !U1STAbits.TRMT );
    
    if ( U1MODEbits.PDSEL == 3 )
    {
        U1TXREG = data;
    }
    else
    {
        U1TXREG = data&0xFF;
    }    
}

int main(void){
    
   initUART1();
   
//POSTAVLJAMO ODREDJENE PINOVE NA PORTB DA BUDU DIGITALNI
   ADPCFGbits.PCFG0 = 1;
   ADPCFGbits.PCFG1 = 1;
   ADPCFGbits.PCFG2 = 1;
   ADPCFGbits.PCFG3 = 1;
   ADPCFGbits.PCFG4 = 1;
   ADPCFGbits.PCFG10 = 1;
   ADPCFGbits.PCFG11 = 1;
   ADPCFGbits.PCFG12 = 1;
   
//POSTAVLJAMO PINOVE DA BUDU IZLAZNI
   TRISBbits.TRISB10 = 0;
   TRISBbits.TRISB11 = 0;
   TRISBbits.TRISB12 = 0;
   
   TRISCbits.TRISC13 = 0;
   TRISCbits.TRISC14 = 0;
   
//POSTAVLJAMO TASTERE DA BUDU ULAZNI
   TRISBbits.TRISB0 = 1;
   TRISBbits.TRISB1 = 1;
   TRISBbits.TRISB2 = 1;
   TRISBbits.TRISB3 = 1;
   TRISBbits.TRISB4 = 1;
   
   while(1){

    //NISTA
    if( PORTBbits.RB0 == 1 && PORTBbits.RB1 == 1 && PORTBbits.RB2 == 1 && PORTBbits.RB3 == 1 && PORTBbits.RB4 == 1 ){
        naredba = 0;
    } 
       
    //NAPRED
    if( PORTBbits.RB0 == 0 ){
        LATBbits.LATB10 = 1;
        naredba = 1;
    } else{
        LATBbits.LATB10 = 0;
    } 

    //RIKVERC
    if( PORTBbits.RB1 == 0 ){
        LATBbits.LATB11 = 1;
        naredba = 2;
    } else{
        LATBbits.LATB11 = 0;
    } 

    //DESNO
    if( PORTBbits.RB2 == 0 ){
        LATBbits.LATB12 = 1;
        naredba = 3;
    } else{
        LATBbits.LATB12 = 0;
    } 
    
    //LEVO
    if( PORTBbits.RB3 == 0 ){
        LATCbits.LATC13 = 1;
        naredba = 4;
    } else{
        LATCbits.LATC13 = 0;
    } 
    
    //TURBO
    if( PORTBbits.RB4 == 0 ){
        LATCbits.LATC14 = 1;
        naredba = 5;
    } else{
        LATCbits.LATC14 = 0;
    } 
 
    
    if( naredba == 0 ){
            writeUART1('0');
            writeUART1('0');
            writeUART1('0');
            writeUART1('0');
            writeUART1('0');
            for(i=0; i<1000; i++);
            writeUART1('n');
            writeUART1('n');
            writeUART1('n');
            writeUART1('n');
            writeUART1('n');
            for(i=0; i<1000; i++);
    } else if( naredba == 1 ){
            writeUART1('0');
            writeUART1('0');
            writeUART1('0');
            writeUART1('0');
            writeUART1('0');
            for(i=0; i<1000; i++);
            writeUART1('p');
            writeUART1('p');
            writeUART1('p');
            writeUART1('p');
            writeUART1('p');
            for(i=0; i<1000; i++);    
    } else if( naredba == 2 ){
            writeUART1('0');
            writeUART1('0');
            writeUART1('0');
            writeUART1('0');
            writeUART1('0');
            for(i=0; i<1000; i++);
            writeUART1('r');
            writeUART1('r');
            writeUART1('r');
            writeUART1('r');
            writeUART1('r');
            for(i=0; i<1000; i++);    
    } else if( naredba == 3 ){
            writeUART1('0');
            writeUART1('0');
            writeUART1('0');
            writeUART1('0');
            writeUART1('0');
            for(i=0; i<1000; i++);
            writeUART1('d');
            writeUART1('d');
            writeUART1('d');
            writeUART1('d');
            writeUART1('d');
            for(i=0; i<1000; i++);    
    } else if( naredba == 4 ){
            writeUART1('0');
            writeUART1('0');
            writeUART1('0');
            writeUART1('0');
            writeUART1('0');
            for(i=0; i<1000; i++);
            writeUART1('l');
            writeUART1('l');
            writeUART1('l');
            writeUART1('l');
            writeUART1('l');
            for(i=0; i<1000; i++);    
    } else if( naredba == 5 ){
            writeUART1('0');
            writeUART1('0');
            writeUART1('0');
            writeUART1('0');
            writeUART1('0');
            for(i=0; i<1000; i++);
            writeUART1('t');
            writeUART1('t');
            writeUART1('t');
            writeUART1('t');
            writeUART1('t');
            for(i=0; i<1000; i++);    
    }
    
    /*
    
    switch( naredba ){
        case 0:
            writeUART1('0');
            writeUART1('0');
            writeUART1('0');
            writeUART1('0');
            writeUART1('0');
            for(i=0; i<1000; i++);
            writeUART1('n');
            writeUART1('n');
            writeUART1('n');
            writeUART1('n');
            writeUART1('n');
            for(i=0; i<1000; i++);
        case 1:
            writeUART1('0');
            writeUART1('0');
            writeUART1('0');
            writeUART1('0');
            writeUART1('0');
            for(i=0; i<1000; i++);
            writeUART1('p');
            writeUART1('p');
            writeUART1('p');
            writeUART1('p');
            writeUART1('p');
            for(i=0; i<1000; i++);
        case 2:
            writeUART1('0');
            writeUART1('0');
            writeUART1('0');
            writeUART1('0');
            writeUART1('0');
            for(i=0; i<1000; i++);
            writeUART1('r');
            writeUART1('r');
            writeUART1('r');
            writeUART1('r');
            writeUART1('r');
            for(i=0; i<1000; i++);
        case 3:
            writeUART1('0');
            writeUART1('0');
            writeUART1('0');
            writeUART1('0');
            writeUART1('0');
            for(i=0; i<1000; i++);
            writeUART1('d');
            writeUART1('d');
            writeUART1('d');
            writeUART1('d');
            writeUART1('d');
            for(i=0; i<1000; i++);
        case 4:
            writeUART1('0');
            writeUART1('0');
            writeUART1('0');
            writeUART1('0');
            writeUART1('0');
            for(i=0; i<1000; i++);
            writeUART1('l');
            writeUART1('l');
            writeUART1('l');
            writeUART1('l');
            writeUART1('l');
            for(i=0; i<1000; i++);
        case 5:
            writeUART1('0');
            writeUART1('0');
            writeUART1('0');
            writeUART1('0');
            writeUART1('0');
            for(i=0; i<1000; i++);
            writeUART1('t');
            writeUART1('t');
            writeUART1('t');
            writeUART1('t');
            writeUART1('t');
            for(i=0; i<1000; i++);
    }*/
    
 }  
 return (1);
}


