void initWiFi(){
  delay(10);
  Serial.println("------Conexao WI-FI------");
  Serial.print("Conectando-se na rede: ");
  Serial.println(ssid);
  Serial.println("Aguarde");

  reconectWiFi();
}


void reconectWiFi(){
  // Teste se ja esta conectado;
  if (WiFi.status() == WL_CONNECTED) return;
   WiFi.begin(ssid, password);  // Conectar a rede Wifi
   while (WiFi.status() != WL_CONNECTED){
    delay(100);
    Serial.print(".");
   }

   Serial.println();
   Serial.print("Conectado com sucesso na rede ");
   Serial.println(ssid);
   Serial.print("Meu IP: ");
   Serial.println(WiFi.localIP());
   
}

void verificaConexaoWIFIMQTT(){
  reconectWiFi();
  reconnectMQTT(); // verifica conexão Mqtt
  
}
