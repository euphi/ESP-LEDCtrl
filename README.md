# ESP-LEDCtrl
LED Strip Controller (2x RGB, 1 White) with ESP8266 Homie (MQTT)


## How to Build
  * If not already installed, install Platformio
    * See http://docs.platformio.org/en/latest/installation.html for instructions
    
  * Clone LEDCtrl + necessary libraries into a directory
    * `git clone https://github.com/euphi/ESP-LEDCtrl.git`
    * `git clone https://github.com/marvinroger/homie-esp8266.git`
    * `git clone https://github.com/euphi/HomieNodeCollection.git`
    * `git clone https://github.com/euphi/esp8266-oled-ssd1306.git`
    
  * Link libs into the ESP-LEDCtrl lib directory:
    * `cd ESP-LEDCtrl/lib`
    * `ln -s ../../homie-esp8266 .`
    * `ln -s ../../HomieNodeCollection .`
    * `ln -s ../../esp8266-oled-ssd1306 .`
    * `cd ..`
  
  * Run platformio
    * Ensure working directory is ESP-LEDCtrl and run `pio run` 
    * To upload, use `pio run --target upload`
    
