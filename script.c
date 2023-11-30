#include <LiquidCrystal.h>

LiquidCrystal lcd (12,11,7,6,5,4);// Endereço do LCD e suas dimensões (16 colunas, 2 linhas)

const int pulsePin = 2; // Pino digital para o transistor PNP
const int tempPin = A0; // Pino analógico para o sensor de temperatura TMP36
const int buzzerPin = 8; // Pino digital para o buzzer

void setup() {
  pinMode(pulsePin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  Serial.begin(9600);

  // Inicializa o LCD com as dimensões
  lcd.begin(16,2); // Liga o backlight do LCD

  // Ajusta o contraste do LCD com o potenciômetro
  analogWrite(9, 100); // Define o contraste 

  // Exibe mensagem inicial no LCD
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");

  lcd.setCursor(0, 1);
  lcd.print("BPM: ");
}

void loop() {

  // Leitura da temperatura
  int tempReading = analogRead(tempPin);
  float tempC = (tempReading * 5.0 * 100.0) / 1024.0; // Converte o valor lido para temperatura em Celsius
  // Exibe a temperatura no LCD
  lcd.setCursor(6, 0);
  lcd.print(tempC);
  lcd.print(" C ");
  
  // Simula a frequência cardíaca usando o transistor PNP
  int bpm = random(230); // Gera um valor aleatório entre 0 e 255
  digitalWrite(pulsePin, bpm); // Escreve o valor no pino PWM

  // Verifica se a frequência simulada passa de 220 e ativa o buzzer
  if (digitalWrite(pulsePin) > 220) {
    digitalWrite(buzzerPin, HIGH); // Ativa o buzzer
  } else {
    digitalWrite(buzzerPin, LOW);
  }

  lcd.setCursor(6, 1); // Posiciona o cursor na segunda linha, primeira coluna
  lcd.print(bpm);

  delay(1000); // Aguarda um segundo antes da próxima leitura/simulação
}
