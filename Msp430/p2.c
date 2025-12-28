#include "/home/gabriel/IOT/include/msp430g2231.h"
  
  int contador_de_interrupcoes = 0; // precisa ser volatile


  int main(void) { 
  WDTCTL = WDTPW + WDTHOLD;   // Desliga Watchdog timer


  P1DIR = 0b01000001;         // P1.0 e P1.6 como saída
  P1REN = 0b00001000;         // Habilita resistor no P1.3
  P1OUT = 0b00001000;         // Pull-up em P1.3
  P1IE  = 0b00001000;         // Habilita interrupção no P1.3
  P1IES = 0b00001000;         // Borda de descida (quando botão é pressionado)
  P1IFG &= ~0b00001000;       // Zera flags do P1.3


  __bis_SR_register(CPUOFF + GIE);  // Modo LPM0 + habilita interrupções


  while (1);  // Loop infinito de segurança (caso saia do LPM)
  }


  // Rotina de Interrupção
  __attribute__((interrupt(PORT1_VECTOR)))
  void Port_1(void) {

    contador_de_interrupcoes++;// Conta botão pressionado

    
    __delay_cycles(10000);// Debounce

    //a cada 5 vezes que o botão for pressionado um led fica aceso
    if (contador_de_interrupcoes % 5 == 0) {
        //a cada 5 apertos inverte a cor do led
        P1OUT ^= 0b01000000;        // Alterna LED em P1.6
        P1OUT ^= 0b00000001;        // Alterna LED em P1.1
    }

  P1IFG &= ~0b00001000;       // Limpa flag do P1.3
  }


