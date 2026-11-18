# Robô Segue Linha

Robô seguidor de linha com Arduino e sensores infravermelhos TCRT5000. O robô detecta uma linha preta sobre fundo branco e ajusta os motores para se manter sobre ela.

## Conteúdo da pasta

| Arquivo | Descrição |
|---|---|
| `sketch_nov3a/sketch_nov3a.ino` | Código básico (lógica liga/desliga) com Arduino UNO, ponte H L9110S e 2 sensores TCRT5000 |
| `Robô Segue Linha.docx` | Plano de ensino, lista de componentes, esquema de ligação e código avançado com controle PID (sensor de 5 canais e driver TB6612FNG) |

## Versões do projeto

### 1. Versão básica (`sketch_nov3a.ino`)

- **Placa:** Arduino UNO
- **Sensores:** 2x TCRT5000 (esquerdo e direito)
- **Driver dos motores:** Ponte H L9110S
- **Velocidade:** PWM de 0 a 255 (padrão `150`, indicado para 4 pilhas)

**Pinagem**

| Componente | Pino |
|---|---|
| Sensor esquerdo (D0) | 2 |
| Sensor direito (D0) | 3 |
| Motor esquerdo (IN1 / IN2) | 5 / 6 |
| Motor direito (IN3 / IN4) | 9 / 10 |

**Lógica de funcionamento**

| Sensor esq. | Sensor dir. | Ação |
|---|---|---|
| Branco | Branco | Frente |
| Preto | Branco | Vira à esquerda |
| Branco | Preto | Vira à direita |
| Preto | Preto | Para (cruzamento ou fim de percurso) |

> Na maioria dos módulos, `LOW` = superfície branca e `HIGH` = linha preta. Se o seu módulo for invertido, troque a lógica no código.

### 2. Versão avançada com PID (descrita no `.docx`)

Focada em velocidade e estabilidade, usa um sensor de 5 canais e controle PID (Proporcional, Integral e Derivativo), que faz correções suaves e evita que o robô perca a linha em alta velocidade.

**Ligação do sensor de 5 canais**

| Sensor | Arduino |
|---|---|
| VCC / GND | 5V / GND |
| OUT1 a OUT5 | Pinos digitais 2, 3, 4, 5 e 6 |

**Ligação do driver TB6612FNG**

| Driver | Ligação |
|---|---|
| VM | Positivo da bateria (7,4 V) |
| VCC / STBY | 5V do Arduino |
| GND | GND comum (bateria e Arduino) |
| PWMA / AIN1 / AIN2 | Pinos 9 / 7 / 8 (motor esquerdo) |
| PWMB / BIN1 / BIN2 | Pinos 10 / 11 / 12 (motor direito) |
| MOTOR A / MOTOR B | Motores esquerdo e direito |

**Constantes do PID (valores iniciais, ajuste na pista)**

```cpp
float Kp = 40.0;
float Ki = 0.01;
float Kd = 15.0;
```

## Lista de componentes (versão do plano de ensino)

| Produto | Qtd. |
|---|---|
| Suporte para 2 baterias 18650 com chave ON/OFF | 1 |
| Módulo seguidor de linha 1 canal TCRT5000 | 2 |
| Ponte H dupla com driver TB6612FNG | 1 |
| Shield de expansão para Arduino Nano 3.0 | 1 |
| Placa Nano V3.0 com conector USB Tipo C | 1 |
| Motor com redução 3-6 V | 2 |
| Roda plástica 65x26 mm | 2 |
| Baterias Li-Ion 18650 (7,4 V) ou LiPo 2S | 2 |
| Rodízio giratório 24x13 mm (roda boba) | 1 |
| Chassi acrílico de 2 rodas + 1 roda boba | 1 |
| Jumpers macho-fêmea (40 peças) | 1 |

**Custo estimado:** R$ 273,70

## Como usar

1. Monte o chassi, os motores, as rodas e a bateria.
2. Ligue sensores e driver conforme a pinagem da versão escolhida.
3. Abra o código na [IDE do Arduino](https://www.arduino.cc/en/software), selecione a placa e a porta e faça o upload.
4. Posicione o robô sobre a linha preta e ligue a bateria.

## Dicas para ganhar velocidade

- **Ajuste do PID:** comece com Ki e Kd zerados. Aumente o Kp aos poucos até o robô seguir a linha (mesmo trepidando nas retas). Depois aumente o Kd para suavizar e deixe o Ki zerado ou muito baixo (ex.: 0,01).
- **Aderência das rodas:** rodas de plástico duro derrapam. Prefira pneus de borracha macia ou silicone.
- **Centro de gravidade:** fixe as baterias (parte mais pesada) o mais baixo e centralizado possível no chassi, para evitar capotamentos e derrapagens nas curvas.

## Referências

- [Robô seguidor de linha, Vida de Silício](https://portal.vidadesilicio.com.br/robo-seguidor-de-linha/)