#include "/home/gabriel/IOT/include/msp430g2231.h"

 int contador_de_interrupcoes = 0; // precisa ser volatile

void main(void) {
    WDTCTL = WDTPW + WDTHOLD;   // Desliga Watchdog timer
    
    P1DIR = 0b01000001;         // P1.0 e P1.6 como saída
    P1REN = 0b00001000;         // Habilita resistor no P1.3
    P1OUT = 0b00001000;         // Pull-up em P1.3
    P1IE  = 0b00001000;         // Habilita interrupção no P1.3
    P1IES = 0b00001000;         // Borda de descida (quando botão é pressionado)
    P1IFG &= ~0b00001000;       // Zera flags do P1.3
    
    P1OUT |= 01000000;              // Liga LED verde no início

    __bis_SR_register(CPUOFF + GIE);  // Modo LPM0 + habilita interrupções
    // _BIS_SR(CPUOFF + GIE);      // Baixo consumo + habilita interrupções globais >>>>>>>>>>// se der ruim tira CPUOFF

    while(1);                   // loop infinito
}

#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void){
    contador_de_interrupcoes++;// Conta botão pressionado

    
    __delay_cycles(10000);// Debounce

    //a cada 5 vezes que o botão for pressionado um led fica aceso
    if (contador_de_interrupcoes % 5 == 0) {
        //a cada 5 apertos inverte a cor do led
        P1OUT ^= 0b01000000;        // Alterna LED em P1.6
    }
    P1IFG &= ~0b00001000;                   // Limpa flag do P1.3
}
