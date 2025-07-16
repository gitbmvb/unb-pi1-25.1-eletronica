#define PINO_IN1 5    // Motor horário
#define PINO_IN2 6    // Motor anti‑horário
#define BOTAO_PIN 2   // Botão (comum ao GND, pull‑up interno)
#define LED_PIN   4   // LED -> resistor -> D4
#define BUZZER    8   // Buzzer

void setup() {
  pinMode(PINO_IN1, OUTPUT);
  pinMode(PINO_IN2, OUTPUT);
  pinMode(BOTAO_PIN, INPUT_PULLUP); // evita resistor externo no botão
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZER, OUTPUT);
}

void loop() {
  bool botaoPressionado = (digitalRead(BOTAO_PIN) == LOW); // LOW = apertado

  if (botaoPressionado) {
    // Acende LED e aciona motor + buzzer
    digitalWrite(LED_PIN, HIGH);
    tone(BUZZER, 440);          // soa enquanto o botão estiver pressionado
    analogWrite(PINO_IN1, 255); // motor sentido horário
    digitalWrite(PINO_IN2, LOW);
  } else {
    // Desliga tudo
    digitalWrite(LED_PIN, LOW);
    noTone(BUZZER);
    digitalWrite(PINO_IN1, LOW);
    digitalWrite(PINO_IN2, LOW);
  }
}
