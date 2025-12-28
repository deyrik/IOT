#include "/home/gabriel/IOT/include/msp430g2231.h"

// #define LIGHT_THRESHOLD 400 // Valor mínimo do ADC para acender LED7
//#define LIGHT_THRESHOLD 50 // Valor mínimo do ADC para acender LED7


void initADC(void) {
 ADC10CTL1 = INCH_0; // Canal A0 (P1.0)
 ADC10CTL0 = SREF_0 | ADC10SHT_3 | ADC10ON; // V+ = Vcc, V- = GND, ADC ligado
 ADC10AE0 |= 0b00000001; // Habilita P1.0 como entrada analógica
}
unsigned int readADC(void) {
 ADC10CTL0 |= ENC | ADC10SC; // Inicia conversão
 while (ADC10CTL1 & ADC10BUSY); // Espera terminar
 return ADC10MEM; // Retorna valor (0–1023)
}
void initLED(void) {
 P1DIR |= 0b01000000; // LED verde como saída
 P1OUT &= ~0b01000000; // Inicialmente desligado
}

int main(void) {
 WDTCTL = WDTPW | WDTHOLD; // Para watchdog
 BCSCTL1 = CALBC1_1MHZ; // Seleciona fonte de clock
 DCOCTL = CALDCO_1MHZ; // Configura fonte de clock

 P1OUT |= 0b00000001; // Coloca o pino P1.0 em nível alto→LED em reverso acumula carga
 __delay_cycles(1000);
 P1DIR &= ~0b00000001; // Configura o pino P1.0 como entrada (0000 0001)
 initADC(); 
 initLED();
while (1) {
 unsigned int valorADC = readADC(); // 3. Ler ADC
 int piscadas = valorADC / 50; // Número de piscadas do LED
 int i;
 for (i = 0; i < piscadas; i++)
 {
  P1OUT |= 0b01000000; // LED verde aceso
  __delay_cycles(200000); // Delay (~ 1s)
  P1OUT &= ~0b01000000; // LED verde apagado 
  __delay_cycles(200000);
 }

    __delay_cycles(500000); // Delay (~ 5s)
 }
}

//  // 4. Comparar com limiar
//  if (valor < LIGHT_THRESHOLD) P1OUT |= 0b01000000; // Claro → LED verde aceso
//  else P1OUT &= ~0b01000000; // Escuro → LED verde apagado
//  __delay_cycles(50000); // Delay (~50 ms)