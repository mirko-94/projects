#include <p30fxxxx.h>
#include <outcompare.h>
#include "timer2.h"

_FOSC(CSW_FSCM_OFF & XT_PLL4);//instruction takt je isti kao i kristal
_FWDT(WDT_OFF);

unsigned char tempRX;
unsigned char ul_niz[];
unsigned int brojac=0, napred=0, rikverc=0, levo=0, desno=0, turbo=0, nista = 0, i;
unsigned int det_pravo = 0, det_levo = 0, det_desno = 0, det_rikverc = 0, det_turbo = 0, det_nista;

void __attribute__((__interrupt__)) _T2Interrupt(void)
{
   	TMR2 =0;
    IFS0bits.T2IF = 0;
}

void __attribute__ ((__interrupt__)) _T3Interrupt(void)
{
    TMR3 = 0;
    IFS0bits.T3IF = 0;
}

void initUART1(void){
    
    U1MODEbits.ALTIO = 0;
    U1BRG = 0x0207;
    U1STA &= 0xFFFC;
    U1MODEbits.UARTEN = 1;
    U1STAbits.UTXEN = 1;
    IEC0bits.U1RXIE = 1;
}

void provera( void ){ //ako je stiglo 3 od 5 korisnih karaktera, postavi flag za dato
//stanje
    if(det_pravo >= 3){
        napred = 1;
        det_pravo = 0;
    }else{
        napred = 0;
    }
 
    if(det_levo >= 3){
        levo = 1;
        det_levo = 0;
    }else{
        levo = 0;
    }
    
    if(det_desno >= 3){
        desno = 1;
        det_desno = 0;
    }else{
        desno = 0;
    }
    
    if(det_rikverc >= 3){
        rikverc = 1;
        det_rikverc = 0;
    }else{
        rikverc = 0;
    }
 
    if(det_turbo >= 3){
        turbo = 1;
        det_turbo = 0;
    }else{
        turbo = 0;
    }
 
    if(det_nista >= 3){
        nista = 1;
        det_nista = 0;
    }else{
        nista = 0;
    }
}


void __attribute__((__interrupt__)) _U1RXInterrupt(void) {
 
 tempRX=U1RXREG;
 ul_niz[brojac] = tempRX;
 
 //Write_UART1(ulazni_niz[brojac]);
 brojac++; //u ulazni_niz smestamo po 10 karaktera
 if(brojac >= 10){ //u sekvencama od po 10 karaktera trazimo koliko od njih su korisni
    for(i = 0; i < brojac; i++){
     if(ul_niz[i] == 'p' ){ //proveravamo da li je stigao koristan simbol
            det_pravo++;
            ul_niz[i] = 0;
     } 
     
     if(ul_niz[i] == 'r' ){
            det_rikverc++;
            ul_niz[i] = 0;
     } 
     
     if(ul_niz[i] == 'l' ){
            det_levo++;
            ul_niz[i] = 0;
     } 
     
     if(ul_niz[i] == 'd' ){
            det_desno++;
            ul_niz[i] = 0;
     }

     if(ul_niz[i] == 't' ){
            det_turbo++;
            ul_niz[i] = 0;
     }
     
     if(ul_niz[i] == 'n' ){
            det_nista++;
            ul_niz[i] = 0;
     }     

  } // od for-a
    
 provera();
 brojac = 0;
 
 } //od if(brojac == 8);*/
 
 IFS0bits.U1RXIF = 0;

}// od prekida

void PWM_init(void){
    
    PR2=49;
    OC1RS=0;
    OC1R=1000;
    OC1CON = OC_IDLE_CON & OC_TIMER2_SRC & OC_PWM_FAULT_PIN_DISABLE & T2_PS_1_8;
   
    PR3=49;
    OC2RS=0;
    OC2R=1000;
    OC2CON = OC_IDLE_CON & OC_TIMER2_SRC & OC_PWM_FAULT_PIN_DISABLE & T3_PS_1_8;

    // UKLJUCUJEMO TAJMERE KOJE KORISTIMO
    T2CONbits.TON = 1;
    T3CONbits.TON = 1;
    
    //INICIJALIZACIJA PWM pinova
    TRISDbits.TRISD0 = 0; //enable A
    TRISDbits.TRISD1 = 0; //enable B   
}

void napred_f(void){
// Brzina kretanja motora    
    OC1RS=23;
    OC2RS=23;

// Kombinacija za napred    
    LATBbits.LATB9  = 1;
    LATBbits.LATB10 = 0;
    LATBbits.LATB11 = 1;
    LATBbits.LATB12 = 0;
}

void rikverc_f(void){
// Brzina kretanja motora    
    OC1RS=23;
    OC2RS=23;

// Kombinacija za rikverc    
    LATBbits.LATB9  = 0;
    LATBbits.LATB10 = 1;
    LATBbits.LATB11 = 0;
    LATBbits.LATB12 = 1;
}

void levo_f(void){
// Brzina kretanja motora    
    OC1RS=23;
    OC2RS=23;

// Kombinacija za levo    
    LATBbits.LATB9  = 0;
    LATBbits.LATB10 = 1;
    LATBbits.LATB11 = 1;
    LATBbits.LATB12 = 0;
}

void desno_f(void){
// Brzina kretanja motora    
    OC1RS=23;
    OC2RS=23;

// Kombinacija za desno
    LATBbits.LATB9  = 1;
    LATBbits.LATB10 = 0;
    LATBbits.LATB11 = 0;
    LATBbits.LATB12 = 1;
}

void turbo_f(void){
// Brzina kretanja motora    
    OC1RS=23;
    OC2RS=23;

// Kombinacija za napred    
    LATBbits.LATB9  = 1;
    LATBbits.LATB10 = 0;
    LATBbits.LATB11 = 1;
    LATBbits.LATB12 = 0;
}

void nista_f(void){
// Brzina kretanja motora    
    OC1RS=35;
    OC2RS=35;

// Kombinacija za nista    
    LATBbits.LATB9  = 0;
    LATBbits.LATB10 = 0;
    LATBbits.LATB11 = 0;
    LATBbits.LATB12 = 0;
}

int main(void){
    
   //POSTAVLJAMO ODREDJENE PINOVE NA PORTB DA BUDU DIGITALNI
   ADPCFGbits.PCFG9 = 1;
   ADPCFGbits.PCFG10 = 1;
   ADPCFGbits.PCFG11 = 1;
   ADPCFGbits.PCFG12 = 1; 
    
   //POSTAVLJAMO PINOVE DA BUDU IZLAZNI
   TRISBbits.TRISB9 = 0;
   TRISBbits.TRISB10 = 0;
   TRISBbits.TRISB11 = 0;
   TRISBbits.TRISB12 = 0;
    
   initUART1();
   PWM_init();
    
while(1){
 
    if( napred == 1 ){
        napred_f(); 
    } else if( rikverc == 1 ){
        rikverc_f(); 
    } else if( desno == 1 ){
        desno_f(); 
    } else if( levo == 1 ){
        levo_f(); 
    } else if( turbo_f == 1 ){
        napred_f(); 
    } else if( nista == 1){
        nista_f();
    }
 }

 return (1);
}

