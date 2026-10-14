// Lectura de termistor NTC 10k B3950 y control de LEDs/actuador
const int pinTermistor = A0;
const int pinLedVerde = 2;
const int pinLedAzul  = 3;
const int pinLedRojo  = 4;
const int pinCalefactor = 5;

const float R_FIJA = 6200.0;
const float R25 = 10000.0;
const float BETA = 3950.0;
const float T25K = 298.15;

float leerTemperaturaC() {
  int lectura = analogRead(pinTermistor);
  float vOut = lectura * (5.0 / 1023.0);
  float rTermistor = R_FIJA * (5.0 / vOut - 1.0);
  float tempK = 1.0 / (1.0/T25K + log(rTermistor / R25) / BETA);
  return tempK - 273.15;
}

void setup() {
  pinMode(pinLedVerde, OUTPUT);
  pinMode(pinLedAzul, OUTPUT);
  pinMode(pinLedRojo, OUTPUT);
  pinMode(pinCalefactor, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  float temp = leerTemperaturaC();

  bool muyFrio = temp < 36.0;
  bool muyCaliente = temp > 37.5;
  bool enRango = !muyFrio && !muyCaliente;

  digitalWrite(pinLedVerde, enRango);
  digitalWrite(pinLedAzul, muyFrio);
  digitalWrite(pinLedRojo, muyCaliente);
  digitalWrite(pinCalefactor, muyFrio ? HIGH : LOW);

  Serial.print("Temp: "); Serial.println(temp);
  delay(500);
}
