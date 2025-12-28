#include "/home/gabriel/IOT/include/msp430g2231.h"


void main(void) {
    WDTCTL = WDTPW + WDTHOLD; // Desliga Watchdog timer
    P1DIR = 0x01 + 0x40;      // Define pinos 1.0 (LED Vermelho) e 1.6 (LED Verde) como saída
    P1REN = 0x08;             // Habilita pullup/pulldown do pino 1.3 (Botão)
    P1OUT = 0x08;             // Define pullup para o pino 1.3
    int contador = 0;

    while(1) {
        if( (P1IN & 0x08) == 0 ){ // Verifica se o botão no pino 1.3 foi pressionado
            contador++;
        }

        if (contador % 2 == 0) {
            P1OUT = P1OUT | 0x01;   // Acende  Vermelho 
            P1OUT = P1OUT & ~0x40;  // Apaga Verde 
        }
        else {
            P1OUT = P1OUT & ~0x01;  // Apaga Vermelho 
            P1OUT = P1OUT | 0x40;   // Acende Verde 
        }
    }
}