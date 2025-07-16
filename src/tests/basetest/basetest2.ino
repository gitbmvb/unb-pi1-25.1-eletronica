#define PINO_IN1 5    // Motor horário
#define PINO_IN2 6    // Motor anti-horário
#define BOTAO_PIN 2   // Botão (comum ao GND, pull-up interno)
#define LED_PIN   4   // LED -> resistor -> D4
#define BUZZER    8   // Buzzer

unsigned long tempoInicio = 0;
bool sistemaAtivo = false;
bool esperandoSoltarBotao = false;

void setup() {
  pinMode(PINO_IN1, OUTPUT);
  pinMode(PINO_IN2, OUTPUT);
  pinMode(BOTAO_PIN, INPUT_PULLUP);
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZER, OUTPUT);
}

void loop() {
  bool botaoPressionado = (digitalRead(BOTAO_PIN) == LOW);

  if (botaoPressionado && !sistemaAtivo && !esperandoSoltarBotao) {
    sistemaAtivo = true;
    tempoInicio = millis();

    digitalWrite(LED_PIN, HIGH);
    tone(BUZZER, 440);
    analogWrite(PINO_IN1, 255);
    digitalWrite(PINO_IN2, LOW);

    esperandoSoltarBotao = true; // Aguarda botão ser solto
  }

  if (!botaoPressionado) {
    esperandoSoltarBotao = false; // Botão foi solto, pode aceitar novo clique
  }

  if (sistemaAtivo && (millis() - tempoInicio >= 5000)) {
    sistemaAtivo = false;
    digitalWrite(LED_PIN, LOW);
    noTone(BUZZER);
    digitalWrite(PINO_IN1, LOW);
    digitalWrite(PINO_IN2, LOW);
  }
}

