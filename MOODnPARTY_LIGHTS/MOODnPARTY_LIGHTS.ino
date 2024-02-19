#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <EEPROM.h>

//#include <WS2812FX.h> // You can use this original lib
#include <WS2812FX_MnP_edition.h> // but this one is better )

#include "defs.h"

WS2812FX lamp = WS2812FX(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);


void setup() { 

  WiFi.mode(WIFI_OFF);
  Serial.begin(115200);
  EEPROM.begin(512);
  delay(100);


  //  -= = = = = =  SETUP LAMP  = = = = = =-
  DEBUGN("WS2812FX setup");
  lamp.init();
//  initParameters(); // uncomment for manual init all parameters during development
  loadParameters();

  if (param.MAGIC ==  ESP.getChipId()) { // First start, need init ?
    applyParameters(); DEBUGN("ApplyParameters");
  } else {
    initParameters(); DEBUGN("Init");
  }

  lamp.start(); DEBUGN("Lamp Start");
  lamp.service(); DEBUGN("First Lamp Service");

  //  -= = = = = =  SETUP WIFI  = = = = = =-
  loadCredentials();

  if (String(wifidata.wifiSSID) == "") {
    setLampState(STATE_START_AP_ONLY);
  } else {
    setLampState(STATE_START_AP_STA);
  }
}

void loop() {
  runLEDs();
  runWiFi();
}
