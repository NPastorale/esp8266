#include <ESP8266WiFi.h>
#include <PubSubClient.h>

const char* ssid = "ssid";
const char* password = "password";
const char* mqtt_server = "server";
const char pinLuz = D0;
const char* topicLuz = "topic";
const char* clientID = "mqttclientid";
const char* mqttUsername = "mqttusername";
const char* mqttPassword = "mqttpassword";

WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
  pinMode(pinLuz, OUTPUT);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void setup_wifi() {
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1);
  }
}

void callback(char* topic, byte* payload, unsigned int length) {
  if ((char)payload[0] == '1') {
    digitalWrite(pinLuz, HIGH);
  } else {
    digitalWrite(pinLuz, LOW);
  }
}

void reconnect() {
  while (!client.connected()) {
    if (client.connect(clientID,mqttUsername,mqttPassword)) {
      client.subscribe(topicLuz,1);
    } else {
      delay(1000);
    }
  }
}

void loop() {

  if (!client.connected()) {
    reconnect();
  }
  client.loop();
}
