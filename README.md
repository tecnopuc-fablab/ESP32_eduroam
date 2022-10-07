# ESP32_eduroam
Este guia mostrará como conectar rede eduroam usando ESP32

* Instalar IDE Arduino 2.0
  * https://www.arduino.cc/en/software
  * ![image](https://user-images.githubusercontent.com/89941162/194555221-16933f51-ba2c-40ac-8774-4cd8fbb66659.png)



* Instalar o Arduino-ESP32 diretamente do Arduino IDE.
  * Para obter uma visão geral do suporte do SoC, dê uma olhada em https://docs.espressif.com/projects/arduino-esp32/en/latest/installing.html, onde você pode descobrir     se o chip específico está em versão estável ou de       desenvolvimento.

    Link de lançamento estável:
  *https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
    
  *![image](https://user-images.githubusercontent.com/89941162/194555819-d0ebd85e-0921-4787-8e46-b3165bcba5be.png)
  
  
* Instalando gerenciado de placas ESP32
   * Para iniciar o processo de instalação usando o Boards Manager, siga estes passos:
   * Inicie o Arduino e abra a janela Preferências.
   * ![image](https://user-images.githubusercontent.com/89941162/194556948-959ea464-03e0-4b77-8814-ef96708160ba.png)
   * Insira o link de liberação (https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json)  no campo URLs adicionais 
     do Gerenciado de Placas.

   ![image](https://user-images.githubusercontent.com/89941162/194557415-c4c7dbbe-ee8f-4dde-8075-d3ebf9581ae2.png)


     


* Gerenciador de bibliotecas 
  * WiFiClientSecure.h
  * esp_wpa2.h
  * esp_wifi.h
  * WiFi.h
