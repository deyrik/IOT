#include <ArduinoBLE.h>
BLEService myService("180C"); // Identificador do serviço (pode ser qualquer UUID)
int controleConexao = 0;
void setup() {
Serial.begin(9600);


while (!Serial);

// Espere pela Serial, mas no máximo por 5 segundos (5000ms)
//while (!Serial && millis() < 5000);


if (!BLE.begin()) {
Serial.println("Erro ao iniciar BLE!");
while (1);
}
BLE.setLocalName("Gabriel-JoaoR"); // Nome que aparecerá no celular
BLE.setAdvertisedService(myService);BLE.addService(myService);
BLE.advertise();
Serial.println("Aguardando conexão do celular...");
}
void loop() {
BLEDevice central = BLE.central();
if (central && controleConexao == 0) {
controleConexao = 1;
Serial.print("Conectado a: ");
Serial.println(central.address());
}
}
