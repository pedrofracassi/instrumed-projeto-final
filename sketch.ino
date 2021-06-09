#include <LiquidCrystal_I2C.h>
#include <Adafruit_BMP280.h>
#include <DHT.h>

// Configurações DHT 22
#define PINO_DHT 2
#define TIPO_DHT DHT22
DHT dht(PINO_DHT, TIPO_DHT);
float umidade_dht;
float temperatura_dht;

/*
  Função que recebe a leitura do DHT e retorna
  o valor calibrado
*/
float calibracaoDHT (float leitura) {
  return leitura * 1.05570549 + 6.690405197;
}

// Configurações BMP280
#define ADDR_BMP 0x76
Adafruit_BMP280 bmp;
float pressao_bmp;
float altitude_bmp;

// Configurações LM35
#define PINO_LM35 A2
float leitura_lm35;
float temperatura_lm35;

/*
  Função que recebe a leitura de 10 bits (0-1023) do LM35
  e retorna a medição de temperatura calibrada
*/
float calibracaoLM35 (float leitura) {
  float voltagem = leitura * (1.1/1023.0);
  return voltagem * 99.62571869 + 0.057542347;
}

// Configurações LDR
#define PINO_LDR A3
float leitura_ldr;

// Configurações LCD
LiquidCrystal_I2C lcd(0x27,16,2);

/*
  Função que recebe uma string e a largura máxima do display,
  retornando uma nova string com espaços na frente pra que
  o texto fique centralizado no LCD
*/
String center(String texto, int maxW) {
  int spacesBefore = (maxW - texto.length()) / 2;
  String str = "";
  int count = 0;
  while (count != spacesBefore) {
    str += " ";
    count++;
  }
  return str + texto;
}

/*
  Função que recebe duas strings, limpa a tela e
  imprime uma string em cada linha do LCD.
*/
void imprimeLcd(String linha1, String linha2) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(center(linha1, 16));
  lcd.setCursor(0, 1);
  lcd.print(center(linha2, 16));
}

void setup() {
  // Ajustando a referência de voltagem do ADC
  analogReference(INTERNAL);

  // Inicializando bibliotecas dos sensores que precisam
  dht.begin();
  bmp.begin(ADDR_BMP);

  // Inicializando o LCD e ligando a luz de fundo
  lcd.init();
  lcd.setBacklight(HIGH);

  // Tela inicial
  imprimeLcd("InstruMed", "Insper 2021.1");
  delay(2000);
  imprimeLcd("Camila", "Bernardi");
  delay(2000);
  imprimeLcd("Gabriela", "Albuquerque");
  delay(2000);
  imprimeLcd("Pedro", "Fracassi");
  delay(2000);
  lcd.clear();
  delay(1000);
}

void loop() {
  /*
    Utilizamos whiles pra exibir a medição durante 5 segundos,
    atualizando-a a cada segundo (delay de 1000 milissegundos * 5 vezes).
    
    Essa estrutura é repetida várias vezes, uma para cada medição
    diferente que exibimos no LCD.
  */

  int count = 0;

  // Temperatura do LM35
  while (count < 5) {
    leitura_lm35 = analogRead(PINO_LM35);
    temperatura_lm35 = calibracaoLM35(leitura_lm35);
    imprimeLcd("Temperatura", String(temperatura_lm35) + " " + (char)223 + "C");
    delay(1000);
    count = count + 1;
  }
  
  count = 0; // Zeramos o contador do loop pra utilizá-lo novamente no próximo while

  // Humidade do DHT22
  while (count < 5) {
    umidade_dht = calibracaoDHT(dht.readHumidity());
    imprimeLcd("Umidade", String(umidade_dht) + "%");
    delay(1000);
    count = count + 1;
  }

  count = 0;

  // Pressão do BMP280
  while (count < 5) {
    pressao_bmp = bmp.readPressure();
    imprimeLcd("Pressao", String(pressao_bmp/1000) + "kPa");
    delay(1000);
    count = count + 1;
  }

  count = 0;

  // Altitude do BMP280
  while (count < 5) {
    altitude_bmp = bmp.readAltitude();
    imprimeLcd("Altitude", String(altitude_bmp) + "m");
    delay(1000);
    count = count + 1;
  }

  count = 0;

  // Luminosidade do LDR
  while (count < 5) {
    leitura_ldr = analogRead(PINO_LDR);
    float luminosidade = pow(10, 7.934 - 1.523*log10(10000*((3.3-(leitura_ldr*1.1/1023.0)))/(leitura_ldr*1.1/1023.0)));
    imprimeLcd("Luminosidade:", String(luminosidade) + "lux");
    delay(1000);
    count = count + 1;
  }
}
