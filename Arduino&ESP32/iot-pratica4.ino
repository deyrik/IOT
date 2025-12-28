//ESP 32
#include <WiFi.h>
const char* ssid = "Seliana"; // Nome da rede WiFi
const char* password = "12345678"; // Senha da rede
void setup() {
Serial.begin(115200); // Inicializa o monitor serial
delay(1000);
Serial.println();
Serial.println("Conectando ao WiFi...");
WiFi.begin(ssid, password); 

// Aguarda conexão
while (WiFi.status() != WL_CONNECTED) {
delay(500);
Serial.print(".");
}
Serial.println();
Serial.println("WiFi conectado!");
Serial.print("Endereço IP: ");
Serial.println(WiFi.localIP());
}

void loop() {
  // put your main code here, to run repeatedly:

}
