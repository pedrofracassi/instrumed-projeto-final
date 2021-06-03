#include <LiquidCrystal_I2C.h>
#include <Adafruit_BMP280.h>
#include <DHT.h>

// Configurações DHT 22

#define PINO_DHT 2
#define TIPO_DHT DHT22
DHT dht(PINO_DHT, TIPO_DHT);
float umidade_dht;
float temperatura_dht;

float calibracaoDHT (float leitura) {
  return leitura * 1.05570549 + 6.690405197;
}

// Configurações BMP280

#define ADDR_BMP 0x76
Adafruit_BMP280 bmp;
float pressao_bmp;

// Configurações LM35

#define PINO_LM35 A2
float leitura_lm35;
float temperatura_lm35;

float calibracaoLM35 (float leitura) {
  float voltagem = leitura * (1.1/1023.0);
  return voltagem * 99.62571869 + 0.057542347;
}

// Configurações LDR

#define PINO_LDR A3
float leitura_ldr;

// Configurações LCD
LiquidCrystal_I2C lcd(0x27,16,2);

void imprimeLcd(String linha1, String linha2) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(linha1);
  lcd.setCursor(0, 1);
  lcd.print(linha2);
}

void setup() {
  analogReference(INTERNAL);
  Serial.begin(9600);
  dht.begin();
  bmp.begin(ADDR_BMP);
  lcd.init();
  lcd.setBacklight(HIGH);
}

void loop() {
  int count = 0;
  while (count < 5) {
    leitura_lm35 = analogRead(PINO_LM35);
    temperatura_lm35 = calibracaoLM35(leitura_lm35);
    imprimeLcd("Temperatura:", String(temperatura_lm35));
    delay(1000);
    count = count + 1;
  }
  
  count = 0;
  while (count < 5) {
    umidade_dht = calibracaoDHT(dht.readHumidity());
    imprimeLcd("Humidade:", String(umidade_dht));
    delay(1000);
    count = count + 1;
  }

  count = 0;
  while (count < 5) {
    pressao_bmp = bmp.readPressure();
    imprimeLcd("Pressao:", String(pressao_bmp/1000));
    delay(1000);
    count = count + 1;
  }

  count = 0;
  while (count < 5) {
    pressao_bmp = bmp.readPressure();
    imprimeLcd("Pressao:", String(pressao_bmp/1000));
    delay(1000);
    count = count + 1;
  }

  count = 0;
  while (count < 5) {
    leitura_ldr = analogRead(PINO_LDR);
    imprimeLcd("Luminosidade:", String(umidade_dht));
    delay(1000);
    count = count + 1;
  }
}
