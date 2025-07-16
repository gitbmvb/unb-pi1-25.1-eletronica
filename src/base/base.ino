#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

// Login e senha da rede wifi
const char* ssid = "G1_Ajax_Base";
const char* password = "botafogo24";

// Pino do motor
// const int ENA    = 5;  // GPIO 5 ou seja, D1
// const int IN1    = 4;  // GPIO 4, ou seja, D2
// const int IN2    = 0;  // GPIO 0, ou seja, D3
//const int ENA    = 5;  // GPIO 5 ou seja, D1
const int IN1    = 5;  // GPIO 4, ou seja, D2
const int IN2    = 4;  // GPIO 0, ou seja, D3 
const int LED    = 2;  // GPIO 2, ou seja, D4
const int BUZZER = 14; // GPIO 14, ou seja, D5

// Servidor HTTP
ESP8266WebServer server(80);

// htmlzin cachorro
const char* htmlPage = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
  <title>Controle ESP8266</title>
  <meta charset="UTF-8">
</head>
<body>
  <h1>Controle o Pino D2</h1>
  <form action="/ligar" method="POST">
    <button type="submit">Decolar</button>
  </form>
</body>
</html>
)rawliteral";

void setup() {
  Serial.begin(115200);
  //pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(LED, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  digitalWrite(IN1, LOW); // Garante que o motor vai começar desligado
  digitalWrite(IN2, LOW); // Garante que o motor vai começar desligado
  digitalWrite(LED, HIGH);

  // Cria a rede wifi
  WiFi.softAP(ssid, password);
  Serial.println("Rede WiFi criada");
  Serial.print("IP address: ");
  Serial.println(WiFi.softAPIP()); // 192.168.4.1 (pode nao ser kkkkk)

  // Pagina principal
  server.on("/", HTTP_GET, []() {
    server.send(200, "text/html", htmlPage);
  });

  // Liga o motor
  server.on("/ligar", HTTP_POST, []() {
    ligaMotor();
    server.sendHeader("Location", "/");
    server.send(303); // Volta pra pagina principal
  });


  server.begin();
  Serial.println("Servidor HTTP iniciado"); // printa que iniciou pra gente nao ficar perdido
  digitalWrite(LED, HIGH);
}

void loop() {
  server.handleClient();
}

void ligaMotor(){
  r2d2();
  //piscaLed(LED, 5);
  // for(int relampagoMarquinhos = 0; relampagoMarquinhos < 255; relampagoMarquinhos++){
  //   analogWrite(ENA, relampagoMarquinhos);
  // }
  digitalWrite(IN1, HIGH); // Garante que o motor vai terminar desligado
  digitalWrite(IN2, LOW); // Garante que o motor vai terminar desligado
}

void piscaLed(int pino, int vezes){
  for(int i = 0; i < vezes; i++){
    digitalWrite(pino, LOW);
    delay(500);
    digitalWrite(pino, HIGH);
    delay(500);
  }
}

void r2d2() {
  bool estadoLed = true;
  for (int i = 0; i < 10; i++) {
    int freq = random(500, 3000);     // Frequência entre 500Hz e 3000Hz
    int dur = random(50, 200);        // Duração entre 50ms e 200ms
    tone(BUZZER, freq, dur);       // Emite o som
    digitalWrite(LED, estadoLed);
    estadoLed = !estadoLed;
    delay(dur + random(20, 100));     // Pausa entre os sons
  }
  noTone(BUZZER); // Para o som
}
