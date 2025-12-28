// the setup function runs once when you press reset or power the board
void setup() {
  pinMode(LED_BUILTIN, OUTPUT); // Inicializa o LED_BUILTIN como output
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(LED_BUILTIN, HIGH);  // Ativa o LED
  delay(1000);
  digitalWrite(LED_BUILTIN, LOW);   // Desativa o LED
  delay(1000);
}
