#include <Wire.h>
#include <Adafruit_ADXL345_U.h>
#include <Adafruit_BMP280.h>
#include <Adafruit_Sensor.h>
#include <BluetoothSerial.h>
#include <ArduinoJson.h>

// Sensores
Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified(12345);
Adafruit_BMP280 bmp;

// Bluetooth
BluetoothSerial SerialBT;

// Enum para saber o estado do foggeute
enum Estado { AGUARDANDO_LANCAMENTO, EM_VOO, POUSO_DETECTADO };
Estado estado = AGUARDANDO_LANCAMENTO;

// Parâmetros de detecção (ajustados com base nos testes reais)
const float ACEL_LANCAMENTO = 15.0;    // 1.5G para detectar lançamento com a força da explosao inicial
const float ACEL_QUEDA = 7.0;          // Valor para ver se o foguete está em queda livre (talvez nem use)
const float ACEL_IMPACTO = 25.0;       // Valor para saber se pousou (de acordo com a força da queda)
const unsigned long TEMPO_QUEDA_MINIMO = 300; // Tempo mínimo em queda (ms) (talvez nem use)

// Armazenamento de dados
const int MAX_DADOS = 1000;            // Capacidade máxima de armazenamento
String dadosVoo[MAX_DADOS];            // Array de dados dos sensores durante o voo
int totalDados = 0;                    // Contador de dados armazenados

// Variáveis de tempo e controle (talvez nem seja necessário)
unsigned long tempoDecolagem = 0;
unsigned long inicioQueda = 0;
bool emQuedaLivre = false;

// Struct para a calibração
struct {
  float ax, ay, az;
} calibracao;

void setup() {
  Serial.begin(115200);
  SerialBT.begin("ESP32_Foguete");

  Wire.begin(21, 22); // I2C (SDA=21, SCL=22)

  // Inicializa acelerômetro
  if (!accel.begin()) {
    Serial.println("❌ ADXL345 não encontrado!");
    while (1);
  }
  accel.setRange(ADXL345_RANGE_16_G);

  // Inicializa a altitude
  if (!bmp.begin(0x76)) {
    Serial.println("❌ BMP280 não encontrado!");
    while (1);
  }

  // Calibração inicial (nao movimentar os sensores)
  calibrarSensor();
  
  Serial.println("✅ Sistema pronto. Detectando lançamento...");
}

void loop() {
  // Lê dados do sensor
  sensors_event_t evento;
  accel.getEvent(&evento);
  
  // Calcula aceleração total
  float ax = evento.acceleration.x - calibracao.ax;
  float ay = evento.acceleration.y - calibracao.ay;
  float az = evento.acceleration.z - calibracao.az;
  float aTotal = sqrt(ax*ax + ay*ay + az*az);

  switch (estado) {
    case AGUARDANDO_LANCAMENTO:
      if (aTotal > ACEL_LANCAMENTO) {
        iniciarVoo();
      }
      break;

    case EM_VOO:
      monitorarVoo(aTotal);
      break;

    case POUSO_DETECTADO:
      aguardarConexaoBluetooth();
      break;
  }

  delay(20); // Tempo para não bugar as leituras
}

// Calibrar o acelerometro de acordo com a posição do bixin
void calibrarSensor() {
  sensors_event_t evento;
  accel.getEvent(&evento);
  
  // Média de 10 leituras para calibração do acelerometro
  calibracao.ax = calibracao.ay = calibracao.az = 0;
  for (int i = 0; i < 10; i++) {
    accel.getEvent(&evento);
    calibracao.ax += evento.acceleration.x;
    calibracao.ay += evento.acceleration.y;
    calibracao.az += evento.acceleration.z;
    delay(10);
  }
  
  calibracao.ax /= 10;
  calibracao.ay /= 10;
  calibracao.az /= 10;
  
  Serial.println("📊 Calibração concluída:");
  Serial.print("Gravidade: X="); Serial.print(calibracao.ax);
  Serial.print(" Y="); Serial.print(calibracao.ay);
  Serial.print(" Z="); Serial.println(calibracao.az);
}

void iniciarVoo() {
  estado = EM_VOO;
  tempoDecolagem = millis();
  SerialBT.end(); // Desliga Bluetooth durante o voo
  Serial.println("LANÇAMENTO DETECTADO! Iniciando coleta de dados...");
  
  // Armazena o primeiro ponto de dados
  if (totalDados < MAX_DADOS) {
    dadosVoo[totalDados++] = gerarJsonDados();
  }
}

void monitorarVoo(float aTotal) {
  // Armazena dados continuamente
  if (totalDados < MAX_DADOS) {
    dadosVoo[totalDados++] = gerarJsonDados();
  }
  Serial.println(dadosVoo[totalDados - 1]);

  if (aTotal > ACEL_IMPACTO) {
    estado = POUSO_DETECTADO;
    SerialBT.begin("ESP32_Foguete"); // Detectou o pouso e ativa o bluetooth
    Serial.println("POUSO DETECTADO! Aguardando conexão para envio de dados.");
  }
  delay(100);
}

void aguardarConexaoBluetooth() {
  if (SerialBT.available() && SerialBT.read() == 'a') {
    enviarDadosArmazenados();
  }
}

String gerarJsonDados() {
  sensors_event_t evento;
  accel.getEvent(&evento);
  
  StaticJsonDocument<200> doc;
  doc["t"] = millis() - tempoDecolagem;
  doc["ax"] = evento.acceleration.x - calibracao.ax;
  doc["ay"] = evento.acceleration.y - calibracao.ay;
  doc["az"] = evento.acceleration.z - calibracao.az;
  doc["alt"] = bmp.readAltitude(1013.25);
  doc["a"] = sqrt(
    doc["ax"].as<float>() * doc["ax"].as<float>() +
    doc["ay"].as<float>() * doc["ay"].as<float>() +
    doc["az"].as<float>() * doc["az"].as<float>()
  );
  
  String json;
  serializeJson(doc, json);
  return json;
}

void enviarDadosArmazenados() {
  Serial.println("Enviando dados armazenados...");
  for (int i = 0; i < totalDados; i++) {
    SerialBT.println(dadosVoo[i]);
    delay(5); // Espaço entre envios
  }
  SerialBT.println("{\"fim\":true}"); // Finaliza o envio
  Serial.println("Dados enviados! Total: " + String(totalDados) + " registros.");
  totalDados = 0; // Reseta o contador
}