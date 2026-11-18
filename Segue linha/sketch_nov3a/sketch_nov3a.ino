// ===================================================
// PROJETO ROBÔ SEGUE-LINHA (ARDUINO UNO + L9110S + 2x TCRT5000)
// ===================================================

// --- Mapeamento dos Pinos dos Sensores de Linha ---
const int SENSOR_ESQ = 2; // Sensor Esquerdo (D0)
const int SENSOR_DIR = 3; // Sensor Direito (D0)

// --- Mapeamento dos Pinos da Ponte H L9110S ---
const int IN1 = 5;  // Motor Esquerdo (Sentido A / PWM)
const int IN2 = 6;  // Motor Esquerdo (Sentido B / PWM)
const int IN3 = 9;  // Motor Direito (Sentido A / PWM)
const int IN4 = 10; // Motor Direito (Sentido B / PWM)

// --- Ajuste de Velocidade (0 a 255) ---
// Motores DC com 4 pilhas costumam responder bem entre 120 e 180
int velocidade = 150;

// Protótipos das funções
void frente();
void esquerda();
void direita();
void parar();

void setup() {
  // Configuração dos pinos dos sensores como Entrada
  pinMode(SENSOR_ESQ, INPUT);
  pinMode(SENSOR_DIR, INPUT);

  // Configuração dos pinos dos motores como Saída
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  // Inicializa com motores parados
  parar();
}

void loop() {
  // Leitura dos sensores (0 = Branco / 1 = Preto na maioria dos módulos)
  int leituraEsq = digitalRead(SENSOR_ESQ);
  int leituraDir = digitalRead(SENSOR_DIR);

  // Lógica de Movimentação do Segue-Linha:
  if (leituraEsq == LOW && leituraDir == LOW) {
    // Ambos na pista branca -> Anda para FRENTE
    frente();
  } else if (leituraEsq == HIGH && leituraDir == LOW) {
    // Sensor Esquerdo detectou a linha preta -> Vira para a ESQUERDA
    esquerda();
  } else if (leituraEsq == LOW && leituraDir == HIGH) {
    // Sensor Direito detectou a linha preta -> Vira para a DIREITA
    direita();
  } else if (leituraEsq == HIGH && leituraDir == HIGH) {
    // Ambos na linha preta ou cruzamento -> PARAR
    parar();
  }
}

// ===================================================
// FUNÇÕES DE CONTROLE DOS MOTORES (L9110S)
// ===================================================

void frente() {
  // Motor Esquerdo FRENTE
  analogWrite(IN1, velocidade);
  analogWrite(IN2, 0);

  // Motor Direito FRENTE
  analogWrite(IN3, velocidade);
  analogWrite(IN4, 0);
}

void esquerda() {
  // Motor Esquerdo PARADO / REVERSO
  analogWrite(IN1, 0);
  analogWrite(IN2, 0);

  // Motor Direito FRENTE (gira o robô para a esquerda)
  analogWrite(IN3, velocidade);
  analogWrite(IN4, 0);
}

void direita() {
  // Motor Esquerdo FRENTE (gira o robô para a direita)
  analogWrite(IN1, velocidade);
  analogWrite(IN2, 0);

  // Motor Direito PARADO / REVERSO
  analogWrite(IN3, 0);
  analogWrite(IN4, 0);
}

void parar() {
  analogWrite(IN1, 0);
  analogWrite(IN2, 0);
  analogWrite(IN3, 0);
  analogWrite(IN4, 0);
}