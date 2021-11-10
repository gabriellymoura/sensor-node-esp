void mqtt_callback(char* topic, byte* payload, unsigned int length){
    String msg;
          //obtem a string do payload recebido
    for(int i = 0; i < length; i++) {
       char c = (char)payload[i];
       msg += c;
    } 

    Serial.println("Mensagem Recebida: "); 
  
}

void reconnect() {
  // Loop until we're reconnected
  while (!MQTT.connected()) {
    Serial.print("* Tentando se conectar ao Broker MQTT: ");
    // Attempt to connect
    if (MQTT.connect("ESP32Client")) {
      Serial.println("connected");  
    } else {
      Serial.print("failed, rc=");
      Serial.println(MQTT.state());
      Serial.println("Havera nova tentatica de conexao em 2s");
      delay(2000);
    }
  }
}
void initMQTT() 
{
  MQTT.setServer(mqtt_server, 1883);
  MQTT.setCallback(mqtt_callback);

}

void reconnectMQTT(){

    //  String clientName = WiFi.macAddress();
  while(!MQTT.connected()){
    Serial.print("* Tentando se conectar ao Broker MQTT: ");
    Serial.println(mqtt_server);
    if (MQTT.connect("mqtt_server")) {
            Serial.println("Conectado com sucesso ao broker MQTT!");
//            MQTT.subscribe(TOPICO_SUB);
            //MQTT.publish(TOPICO_PUB); 
        } 
    else{
            Serial.println("Falha ao reconectar no broker.");
            Serial.println("Havera nova tentatica de conexao em 2s");
            delay(2000);
        }
  }
}
