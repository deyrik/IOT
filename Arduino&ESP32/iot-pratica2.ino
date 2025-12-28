
#include <Arduino_LSM9DS1.h>

void setup() {
if (!IMU.begin()) while (1); // Inicializa o sensor IMU e para o programa caso o sensor não seja encontrado
pinMode(LED_BUILTIN, OUTPUT); // Inicializa o LED_BUILTIN como output
}


void loop(){
float ax, ay, az; // Variáveis dos eixos X, Y e Z
if(IMU.accelerationAvailable()){
  IMU.readAcceleration(ax, ay, az); // Atribui as acelerações aplicadas em cada eixo as variáveis
  int delayPadrao = 250;
  int delayTimeX = 250; // Define um intervalo de tempo
  int delayTimeY = 250;
  int delayTimeZ = 250;

  //cada vez que ele verifica e esta menor que, ele pisca mais (ou seja, o delay da verificação é menor)

  //numero em cima sobre um denominador que varia 


    if(az != 0){
      int valor = abs(1000*az);
      digitalWrite(LED_BUILTIN, HIGH); //Ativa o LED
      delay(valor);
      digitalWrite(LED_BUILTIN, LOW); // Desativa o LED
      //delay(delayPadrao);
      delay(valor);
    }
    

  }
}
