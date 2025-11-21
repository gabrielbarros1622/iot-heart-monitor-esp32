# iot-heart-monitor-esp32
# Projeto final de Objetos Inteligentes Conectados: Sistema de Monitoramento de Batimentos Cardíacos baseado em ESP32 e MQTT.

Este projeto apresenta o desenvolvimento de um sistema de monitoramento de batimentos cardíacos utilizando a plataforma ESP32, comunicação sem fio e protocolo MQTT. A solução se baseia nos conceitos de Internet das Coisas (IoT) e tem como objetivo auxiliar aplicações de saúde preventiva, permitindo a leitura contínua da frequência cardíaca, envio de dados para um servidor e acionamento automático e remoto de alertas sonoros.

## Objetivos

- Monitorar o batimento cardíaco em tempo real.
- Enviar os valores de BPM (Batimentos por Minuto) para a nuvem via MQTT.
- Detectar batimentos elevados e acionar automaticamente um buzzer de alerta.
- Permitir o controle remoto do alerta sonoro via mensagens MQTT.

---

## Funcionamento do Sistema

O sistema utiliza um sinal analógico (simulado via potenciômetro no Wokwi) representando variações cardíacas. O ESP32 identifica picos que caracterizam batimentos, calcula o BPM e envia para um broker MQTT. Caso o valor ultrapasse o limite configurado, um buzzer é acionado automaticamente. O alerta também pode ser ativado manualmente via MQTT.

**Principais tópicos MQTT:**
| Tópico | Função |
|--------|--------|
| `monitor/heartRate` | Publica os valores de BPM |
| `monitor/buzzer` | Recebe comandos para ativar/desativar o buzzer |

📌 **Comandos aceitos pelo buzzer via MQTT:**
- `ON` → liga o buzzer
- `OFF` → desliga o buzzer

---

## Tecnologias e Componentes

- **ESP32 DevKit V1**
- **Potenciômetro (simulação do sensor cardíaco)**
- **Buzzer ativo 5V**
- **Simulador Wokwi**
- **Client MQTT HiveMQ WebSocket**
- **Arduino IDE**
- Bibliotecas utilizadas:
  - `WiFi.h`
  - `PubSubClient.h`

---

## Diagrama de Funcionamento (Fluxograma)
📌 O fluxograma completo está disponível na pasta `/docs`.

---

## Diagrama do Circuito
O esquema eletrônico final está disponível em `/docs`.

---

## Conexão com o HiveMQ Web Client

| Campo | Valor |
|-------|------|
| **Broker Address** | `broker.hivemq.com` |
| **Port** | `8000` (WebSocket) |
| **Client ID** | Qualquer identificador |
| **Tópicos** | `monitor/heartRate`, `monitor/buzzer` |

---

## Como Executar o Projeto

### **1) Clonar o repositório**
https://github.com/gabrielbarros1622/iot-heart-monitor-esp32

### **2) Abrir o código na Arduino IDE**
- Abrir `src/firmware.ino`.
- Instalar bibliotecas necessárias se solicitado.

### **3) Executar o projeto no Wokwi**
- Abrir o link incluído no artigo (projeto no Wokwi).
- Rodar a simulação.

### **4) Monitorar via MQTT**
- Acessar https://www.hivemq.com/demos/websocket-client/
- Conectar e assinar os tópicos.

---

## Prints e Demonstrações

- Prints do funcionamento estão em `/docs/mqtt_prints`.
- **Link do vídeo (a ser inserido):** *(colocar após gravação)*
- **Repositório faz parte do artigo final da disciplina e será citado como referência.**

---

## 👨‍💻 Autor
**Gabriel da Silva Barros**  
Projeto desenvolvido como requisito da disciplina sobre Internet das Coisas (IoT).  
Mackenzie — 2025.

---

## 📜 Licença
Este projeto pode ser utilizado para fins educacionais e acadêmicos. Para uso comercial, consulte o autor.
