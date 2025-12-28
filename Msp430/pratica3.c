#include "/home/gabriel/IOT/include/msp430g2231.h"

int segundos = 0; 


void main(void) {
  WDTCTL = WDTPW + WDTHOLD;   // Desliga Watchdog timer
 P1DIR = 0b01000001;         // Define pinos 1.0 e 1.6 como saída (0100 0001)
 P1REN = 0b00001000;         // Habilita pullup/pulldown do pino 1.3 (0000 1000)
 P1OUT = 0b00001000;         // Define pullup para o pino 1.3 (0000 1000)


 CCTL0 = CCIE;               // Habilita interrupção de comparação do timer A          
 TACTL = TASSEL_2+MC_3+ID_3; // SMCLK = 1 MHz, SMCLK/8 = 125 KHz (8 us)     
 CCR0 =  62500;              // Modo up/down: chega no valor e depois volta
                             // para zero, portanto cada interrupção acontece
                             // 2 * 62500 * 8 us = 1 segundo   
 _BIS_SR(CPUOFF + GIE);                   
 while(1); 
 
 

}


__attribute__((interrupt(TIMER0_A0_VECTOR)))
void Timer_A(void) {

    if (segundos == 0){
        P1OUT |= 0b00000001;       // Acende LED do pino 1.0
    }


    if (segundos == 20)
    {
        P1OUT &= 0b11111110;       // Apaga LED do pino 1.0
        P1OUT |= 0b01000000;       // Acende LED do pino 1.6
    }
    

    if (segundos >=35)
    {
     P1OUT &= 0b10111111;       // Apaga LED do pino 1.6
    }
    
    if (segundos > 35 && segundos <= 40){
        P1OUT ^= 0b00000001;       // Apaga LED do pino 1.0
    }

    if (segundos > 40)
    {
        //zera 
        segundos = 0;
    }
    
    
  segundos++;
  //P1OUT = P1OUT ^ 0b00000001;       // Limpa flag do P1.3
}


