/* ESP32 procurar e conectar ao seu Arduino */

#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEScan.h>
#include <BLEAdvertisedDevice.h>

// --- Configuração ---
// O nome do seu Arduino (definido no código dele)
#define ARDUINO_NAME "Gabriel-JoaoR"
// O UUID do serviço que o Arduino está anunciando
static BLEUUID serviceUUID("180C");
// --------------------

static BLEAdvertisedDevice* myDevice; // Ponteiro para guardar o dispositivo encontrado
static bool deviceFound = false;      // Flag para avisar que encontramos o dispositivo
static bool connecting = false;       // Flag para evitar múltiplas tentativas de conexão

// Esta classe é chamada automaticamente quando o scan encontra um dispositivo
class MyAdvertisedDeviceCallbacks : public BLEAdvertisedDeviceCallbacks {
    
    // Esta função roda para CADA dispositivo encontrado no scan
    void onResult(BLEAdvertisedDevice advertisedDevice) {
        Serial.print("Dispositivo BLE encontrado: ");
        Serial.println(advertisedDevice.getName().c_str());

        // Verifica se é o dispositivo que queremos (pelo nome)
        if (advertisedDevice.getName() == ARDUINO_NAME) {
            Serial.println("!!! ENCONTREI O ARDUINO 'Gabriel-JoaoR' !!!");
            advertisedDevice.getScan()->stop(); // Para o scan, pois já achamos
            
            // Precisamos copiar os dados do dispositivo, pois o 'advertisedDevice'
            // é local e será destruído após esta função.
            myDevice = new BLEAdvertisedDevice(advertisedDevice); 
            deviceFound = true; // Avisa ao loop() que encontramos
        }
    }
};

void setup() {
  Serial.begin(115200);
  Serial.println("ESP32 - Cliente BLE");
  
  BLEDevice::init("Meu ESP32"); // Inicializa o BLE com um nome para o ESP32
  
  BLEScan* pBLEScan = BLEDevice::getScan(); // Pega o objeto scanner
  pBLEScan->setAdvertisedDeviceCallbacks(new MyAdvertisedDeviceCallbacks()); // Define o callback
  pBLEScan->setActiveScan(true); // Scan ativo
  pBLEScan->setInterval(100);
  pBLEScan->setWindow(99); // Configurações de scan

  Serial.println("Iniciando scan (5 segundos)...");
  pBLEScan->start(5, false); // Inicia o scan por 5 segundos
}

// Função separada para conectar (para organizar o código)
void connectToServer() {
    connecting = true; // Marca que estamos tentando conectar
    Serial.print("Conectando ao ");
    Serial.println(myDevice->getAddress().toString().c_str());

    BLEClient* pClient = BLEDevice::createClient(); // Cria o cliente
    
    // Tenta conectar
    if (pClient->connect(myDevice)) {
        Serial.println("Conectado com sucesso ao Arduino!");

        // Tenta obter o serviço que o Arduino está anunciando
        BLERemoteService* pRemoteService = pClient->getService(serviceUUID);
        if (pRemoteService == nullptr) {
            Serial.print("Falha ao encontrar o serviço UUID: ");
            Serial.println(serviceUUID.toString().c_str());
            pClient->disconnect();
            return;
        }

        Serial.println("Serviço '180C' encontrado!");


        // pClient->disconnect();
        // Serial.println("Desconectado.");
        // Comente a linha acima para ficar conectado!

    } else {
        Serial.println("Falha ao conectar.");
    }
    
    // delete pClient; // Não deletar o cliente se quiser ficar conectado
}


void loop() {
  // Se encontramos o dispositivo E não estamos já conectados/conectando...
  if (deviceFound && !connecting) {
    
    connectToServer(); // Tenta conectar
  
  } else if (!deviceFound) {
    // Se não encontramos, escaneia novamente
    Serial.println("Arduino não encontrado, iniciando novo scan...");
    BLEScan* pBLEScan = BLEDevice::getScan();
    pBLEScan->start(5, false); // Scan por 5 segundos
    delay(5000); // Espera o scan terminar
  }
  
  delay(2000); // delay no loop 
}
