#include <WiFiClientSecure.h>     

#include "esp_wpa2.h"
#include "esp_wifi.h"
#include <WiFi.h>

#include <Wire.h>
#include "SparkFunHTU21D.h"

#define EXAMPLE_EAP_METHOD 1
#define EXAMPLE_EAP_ID "100XXXXX@pucrs.br"           //Usuário
#define EXAMPLE_EAP_USERNAME "100XXXXX@pucrs.br"     //Usuário
#define EXAMPLE_EAP_PASSWORD  "XXXXXXX"              //Senha             
#define EXAMPLE_WIFI_SSID "eduroam"                  //Rede

#define SDA 21
#define SCL 22


/**********************************Variáveis Globais**************************************************/
HTU21D myHumidity;
TwoWire wireSensor = TwoWire(1);
boolean Liga_Led = false;
unsigned long int Timer = 0;

const char*  server = "google.com";  // URL Servidor
WiFiClientSecure client;      

/***********************************Setup*************************************************************/
void setup() {
    
  Serial.begin(115200);
  Serial.println("INIT");
  WiFi.disconnect(true);
  WiFi.mode(WIFI_STA);
  Serial.print("Mac>> ");
  Serial.println(WiFi.macAddress());
  
  esp_wifi_sta_wpa2_ent_set_identity((uint8_t *)EXAMPLE_EAP_ID, strlen(EXAMPLE_EAP_ID) );
  esp_wifi_sta_wpa2_ent_set_username((uint8_t *)EXAMPLE_EAP_USERNAME, strlen(EXAMPLE_EAP_USERNAME) );
  esp_wifi_sta_wpa2_ent_set_password((uint8_t *)EXAMPLE_EAP_PASSWORD, strlen(EXAMPLE_EAP_PASSWORD) );
  esp_wifi_sta_wpa2_ent_enable() ;
  WiFi.begin(EXAMPLE_WIFI_SSID);
  
  while (WiFi.status() != WL_CONNECTED) {
    switch(WiFi.status()){
       case 0:Serial.println("Wi-Fi está em processo de mudança de status");
       break;
       case 1:Serial.println("SSID configurado não pode ser alcançado");
       break;
       case 3:Serial.println("Conexão estabelecida ");
       break;
       case 4:Serial.println("Conexão falhou");
       break;
       case 6:Serial.println("Senha incorreta");
       break;
       case 7:Serial.println("ESP32 não está configurado em modo Estação");      
       break;     
       default:
       Serial.println(WiFi.status());
    }
    Serial.println("Aguarde...");
    delay(500);
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  myHumidity.begin();
  pinMode(2, OUTPUT);

  client.setInsecure();          
  Liga_Led ^= true;
}


/*******************************Programa Principal**********************************************/
void loop() {

  if( millis() > Timer){         //Temporizador de 1 segundo
    Timer = millis() + 1000; 
    digitalWrite(2, Liga_Led);
    float humd = myHumidity.readHumidity();
    float temp = myHumidity.readTemperature();

    Serial.print("Time:");
    Serial.print(millis());
    Serial.print(" Temperature:");
    Serial.print(temp, 1);
    Serial.print("C");
    Serial.print(" Humidity:");
    Serial.print(humd, 1);
    Serial.print("%");

    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
    Serial.println();
  

   switch(WiFi.status()){
       case 0:Serial.println("Wi-Fi está em processo de mudança de status");
       break;
       case 1:Serial.println("SSID configurado não possa ser alcançado");
       break;
       case 3:Serial.println("Conexão WiFi estabelecida ");
       break;
       case 4:Serial.println("Conexão falhou");
       break;
       case 6:Serial.println("Senha incorreta");
       break;
       case 7:Serial.println("ESP32 não está configurado em modo Estação");      
       break;     
       default:
       Serial.println(WiFi.status());
    }

    //Inicio acesso banco de dados
    if (!client.connect(server, 443)) {
      Serial.println("Falha de conexão no Servidor!");
    }
    else {
      Serial.println("Conectado ao Servidor!");
      client.println("GET https://google.com HTTP/1.1");     //poder ser url do google sheet
      client.println("Host: grande.ideia.pucrs.br");
      client.println("Connection: close");
      client.println();

      while (client.connected()) {
        String line = client.readStringUntil('\n');  
        if (line == "\r") {
          Serial.println("cabeçalhos recebidos");
          break;
        }
      }
     
      while (client.available()) {
        char c = client.read();
        Serial.write(c);
      }
      Liga_Led ^= true;
      client.stop();
    
    }//Fim acesso banco de dados  
     
  }   

}
