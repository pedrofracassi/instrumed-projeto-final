#include <Adafruit_BMP280.h>
#include <DHT.h>

#define PINO_DHT 2
#define TIPO_DHT DHT22
DHT dht(PINO_DHT, TIPO_DHT);
float humidade_dht;
float temperatura_dht;

float calibracaoDHT (float leitura) {
  return leitura * 1.05570549 + 6.690405197;
}

#define ADDR_BMP 0x76
Adafruit_BMP280 bmp;
float pressao_bmp;

#define PINO_LM35 A2
float leitura_lm35;
float temperatura_lm35;

float calibracaoLM35 (float leitura) {
  float voltagem = leitura * (1.1/1023.0);
  return voltagem * 99.62571869 + 0.057542347;
}

#define PINO_LDR A3
float leitura_ldr;

void setup() {
  analogReference(INTERNAL);
  Serial.begin(9600);
  dht.begin();
  bmp.begin(ADDR_BMP);
}

void loop() {
  humidade_dht = calibracaoDHT(dht.readHumidity());
  pressao_bmp = bmp.readPressure();
  leitura_lm35 = analogRead(PINO_LM35);
  temperatura_lm35 = calibracaoLM35(leitura_lm35);
  leitura_ldr = analogRead(PINO_LDR);
  Serial.print(humidade_dht);
  Serial.print(",");
  Serial.print(pressao_bmp);
  Serial.print(",");
  Serial.print(leitura_ldr);
  Serial.print(",");
  Serial.println(temperatura_lm35);
  delay(1000);
}
