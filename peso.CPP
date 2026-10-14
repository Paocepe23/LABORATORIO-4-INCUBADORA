#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2); // RS, E, D4-D7
const int pinGalga = A1;

// Constantes de calibración (ajustar con pesos patrón conocidos)
const float PENDIENTE = 0.0215; // kg por unidad ADC, obtenida por calibración
const float OFFSET = -1.3;

void setup() {
  lcd.begin(16, 2);
  lcd.print("Peso neonato:");
}

void loop() {
  int lectura = analogRead(pinGalga);
  float pesoKg = lectura * PENDIENTE + OFFSET;

  lcd.setCursor(0, 1);
  lcd.print(pesoKg, 2);
  lcd.print(" kg   ");
  delay(300);
}
