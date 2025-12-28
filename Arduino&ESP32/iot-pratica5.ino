#include <WiFi.h>
#include <HTTPClient.h>
const char* ssid = "NOME DA REDE";
const char* password = "SENHA";
// Exemplo de URL (troque por qualquer site ou API)
//const char* url = "http://worldtimeapi.org/api/timezone/America/Sao_Paulo";
const char* url = "https://www.google.com";

void setup() {
 Serial.begin(115200);
 // Conecta ao WiFi
 Serial.print("Conectando ao WiFi");
 WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
 Serial.print(".");
 delay(500);
 }
 Serial.println("\nWiFi conectado!");
}
void loop() {
 if (WiFi.status() == WL_CONNECTED) {
 HTTPClient http;
 http.begin(url); // Inicia requisição
 int httpCode = http.GET(); // Faz GET
 if (httpCode > 0) {
 Serial.printf("Código HTTP: %d\n", httpCode);
 String payload = http.getString(); // Conteúdo retornado
 Serial.println("Resposta do servidor:");
 Serial.println(payload);
 } else {
 Serial.printf("Erro na requisição: %s\n", http.errorToString(httpCode).c_str());
 }
 http.end(); // Fecha conexão
 }
 delay(5000); // faz novamente a cada 5s
}
