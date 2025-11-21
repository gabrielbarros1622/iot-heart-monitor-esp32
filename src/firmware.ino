/*
 * Sistema de Monitoramento de Batimentos Cardíacos via IoT
 * Autor: Gabriel da Silva Barros
 * Hardware: ESP32 DevKit V1 + Potenciômetro (simulando AD8232) + Buzzer ativo
 * Comunicação: Wi-Fi + Protocolo MQTT (broker público HiveMQ)
 * Objetivo: Transmitir o valor de BPM em tempo real e acionar alerta sonoro local/remoto
 */

#include <WiFi.h>
#include <PubSubClient.h>

// -------------------- CONFIGURAÇÕES DE HARDWARE --------------------
#define SENSOR_PIN 34       // Entrada analógica (AD8232 simulado via potenciômetro no Wokwi)
#define BUZZER_PIN 12       // Buzzer ativo
#define BPM_LIMIT 110       // Limite para alerta sonoro

// -------------------- CONFIGURAÇÕES DE REDE E MQTT --------------------
const char* ssid = "Wokwi-GUEST";   // Rede padrão da simulação
const char* password = "";          // Sem senha

// Broker MQTT público HiveMQ
const char* mqtt_server = "broker.hivemq.com";

WiFiClient espClient;
PubSubClient client(espClient);

// -------------------- VARIÁVEIS DO CÁLCULO DE BPM --------------------
unsigned long lastBeatTime = 0;
int lastValue = 0;
int BPM = 0;

// -------------------- FUNÇÃO DE RECONEXÃO MQTT --------------------
void reconnect() {
  while (!client.connected()) {
    Serial.print("Conectando ao MQTT...");
    
    if (client.connect("esp32-heart-monitor")) {
      Serial.println("Conectado!");

      // Inscrição para receber comandos remotos
      client.subscribe("monitor/buzzer");
    } 
    else {
      Serial.print("Falhou, rc=");
      Serial.print(client.state());
      Serial.println(" tentando novamente em 2s");
      delay(2000);
    }
  }
}

// -------------------- CONFIGURAÇÃO INICIAL --------------------
void setup() {
  Serial.begin(115200);

  pinMode(SENSOR_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(BUZZER_PIN, LOW);

  // Conexão Wi-Fi
  WiFi.begin(ssid, password);
  Serial.print("Conectando ao WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(250);
    Serial.print(".");
  }
  Serial.println("\nWiFi conectado!");

  // Configuração MQTT
  client.setServer(mqtt_server, 1883);

  // Callback: ações ao receber mensagens MQTT
  client.setCallback([](char* topic, byte* payload, unsigned int length) {
    String message;
    for (int i = 0; i < length; i++) message += (char)payload[i];
    
    Serial.println("Mensagem recebida: " + message);

    if (message == "ON") digitalWrite(BUZZER_PIN, HIGH);
    if (message == "OFF") digitalWrite(BUZZER_PIN, LOW);
  });
}

// -------------------- LOOP PRINCIPAL --------------------
void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();  // Mantém a conexão viva

  int value = analogRead(SENSOR_PIN);

  // Detecção de pico simulando batimento cardíaco
  if (value > 1600 && lastValue <= 1600) {
    unsigned long now = millis();
    BPM = 60000 / (now - lastBeatTime);
    lastBeatTime = now;

    Serial.print("BPM Calculado: ");
    Serial.println(BPM);

    // Envio do BPM para o MQTT em JSON
    String payload = "{ \"bpm\": " + String(BPM) + " }";
    client.publish("monitor/heartRate", payload.c_str());
  }

  lastValue = value;

  // Alerta automático local via buzzer
  if (BPM > BPM_LIMIT) {
    digitalWrite(BUZZER_PIN, HIGH);
  } else {
    digitalWrite(BUZZER_PIN, LOW);
  }

  delay(10);
}
