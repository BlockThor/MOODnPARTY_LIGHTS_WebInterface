//#include <TimeLib.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <EEPROM.h>
#include <RTClib.h>

//#include <WS2812FX.h> // You can use this original lib
#include <WS2812FX_MnP_edition.h>  // but this one is better )

#include "defs.h"

WS2812FX lamp = WS2812FX(LED_COUNT, LED_PIN, LED_TYPE);
RTC_Millis rtc;

void setup() {

  Serial.begin(115200);
  WiFi.mode(WIFI_OFF);
  EEPROM.begin(512);
  rtc.begin(DateTime(F(__DATE__), F(__TIME__)));

#ifndef ESP8266
  while (!Serial)
    ;  // wait for serial port to connect. Needed for native USB
#endif

  DEBUGN("\n\n - = = = -");
  DEBUG2N("ver: ", MNPL_VERSION);
  //  -= = = = = =  SETUP LAMP  = = = = = =-
  DEBUGN("WS2812FX setup");
  lampInit();
  loadParameters();

  if (param.MAGIC == ESP.getChipId()) {
    applyParameters();
    DEBUGN("ApplyParameters");
  } else {
    DEBUG2XN("Init: no ChipID:", ESP.getChipId());
    DEBUG2XN("MAGIC: ", param.MAGIC);
    initParameters();
  }
  loadTime();

  lampStart();

  //  -= = = = = =  SETUP WIFI  = = = = = =-
  loadCredentials();

  if (wifidata.wifiSSID[0] == '\0') {
    setLampState(STATE_START_AP_ONLY);
  } else {
    setLampState(STATE_START_AP_STA);
  }

  lastHeartbeat = now;
}

void loop() {
  yield();
  runTime();
  runLEDs();
  runWiFi();
}
