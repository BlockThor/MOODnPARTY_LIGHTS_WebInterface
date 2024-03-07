#define WIFI_AP_TIMEOUT    60000
#define WIFI_AP_IP         IPAddress(1, 2, 3, 4)
#define WIFI_AP_SUBNET     IPAddress(255, 255, 255, 0)
//#define WIFI_DNS_PORT      (byte)53


const byte DNS_PORT = 53;
IPAddress apIP(1, 2, 3, 4);
DNSServer dnsServer;
ESP8266WebServer webServer(80);
uint8_t lastWiFiStatus;

void runWiFi() {
  switch (lampState) {
    case   STATE_START_AP_ONLY:  startAP();      break;
    case   STATE_START_AP_STA:   startAPSTA();   break;
    case   STATE_SWITCH_TO_STA:  switchToSTA();  break;
    case   STATE_RUNNING_AP:     runningAP();    break;
    case   STATE_RUNNING_AP_STA: runningAPSTA(); break;
    case   STATE_RUNNING_STA:    runningSTA(); break;
    case   STATE_RESET:          ESP.reset(); break;
    default: enterError();   break;
  }
}

bool startAP() {
  WiFi.mode(WIFI_OFF);
  Delay(100);
  WiFi.mode(WIFI_AP);

  WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
  WiFi.softAP(wifidata.wifiSSID_Ap, wifidata.wifiPass_Ap);
  Delay(250);

  dnsServer.setTTL(0);
  dnsServer.start(DNS_PORT, "*", apIP);
  dnsServer.setErrorReplyCode(DNSReplyCode::NoError);
  startServer();

  setLampState(STATE_RUNNING_AP);
  return true;
}

bool startAPSTA() {
  WiFi.mode(WIFI_AP_STA);
  WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
  WiFi.softAP(wifidata.wifiSSID_Ap, wifidata.wifiPass_Ap);

  dnsServer.setTTL(0);
  dnsServer.start(DNS_PORT, "*", apIP);
  dnsServer.setErrorReplyCode(DNSReplyCode::NoError);
  startServer();
  
  if (connectWiFi()) startServer();
  else return false;

  setLampState(STATE_RUNNING_AP_STA);
  return true;
}


bool switchToSTA() {
  WiFi.mode(WIFI_OFF);
  Delay(100);
  WiFi.mode(WIFI_STA);
  Delay(100);
  if (connectWiFi()) startServer();
  else return false;

  setLampState(STATE_RUNNING_STA);
  return true;
}

void runningAP() {
  dnsServer.processNextRequest();
  webServer.handleClient();
}

void runningAPSTA() {
  checkWiFiConnection();
  dnsServer.processNextRequest();
  webServer.handleClient();
  checkAPTimeout();
}

void runningSTA() {
  checkWiFiConnection();
  webServer.handleClient();
}

bool connectWiFi() {
  DEBUG("Connect WiFi: ");
  if (WiFi.begin(wifidata.wifiSSID, wifidata.wifiPass)) {
    DEBUGN("WiFi.begin");
    unsigned long startTimer = millis();
    while (WiFi.status() != WL_CONNECTED && WiFi.status() != WL_WRONG_PASSWORD && millis() - startTimer < TTC) {
      Delay(500);
      DEBUG("|");
    }
    DEBUGVN(getWiFiStateString(WiFi.status()));
    // Check connection
    if (WiFi.status() == WL_CONNECTED) {
      DEBUG2N(" Connected: ", WiFi.localIP());
      lastWiFiStatus = WL_CONNECTED;
      return true;
    } else if (WiFi.status() == WL_NO_SSID_AVAIL) {
      DEBUG2N("\nWiFi.NotFound: ", wifidata.wifiSSID);
      lastWiFiStatus = WL_NO_SSID_AVAIL;
      setLampState(STATE_START_AP_ONLY);
      return false;
    } else if (WiFi.status() == WL_WRONG_PASSWORD) {
      DEBUG2N("\nWiFi.WrongPass: ", wifidata.wifiPass);
      lastWiFiStatus = WL_WRONG_PASSWORD;
      setLampState(STATE_START_AP_ONLY);
      return false;
    } else {
      DEBUG2N("\nWiFi.NotConnected: ", WiFi.status());
      lastWiFiStatus = WiFi.status();
      //      setLampState(STATE_ERROR);
      return false;
    }
  } else {
    DEBUG2N("WiFi.NotBegin: ", WiFi.status());
    DEBUGVN(getWiFiStateString(WiFi.status()));
    setLampState(STATE_RUNNING_AP);
    return false;
  }
}

void startServer() {
  DEBUGN("HTTP server setup");
  webServer.on("/", srv_handle_index_html);
  webServer.on("/main.js", srv_handle_main_js);
  webServer.on("/style.css", srv_handle_style_css);
  webServer.on("/set", srv_handle_set);
  webServer.on("/scan", srv_handle_wifiscan);
  webServer.on("/sendWiFi", srv_handle_sendwifi);
  webServer.on("/sendApWiFi", srv_handle_sendapwifi);
  webServer.on("/cmd", srv_handle_cmd);

  webServer.on("/generate_204", srv_handle_index_html);  //Android captive portal. Maybe not needed. Might be handled by notFound handler.
  webServer.on("/fwlink", srv_handle_index_html);  //Microsoft captive portal. Maybe not needed. Might be handled by notFound handler.
  webServer.onNotFound(srv_handle_not_found);

  webServer.begin();
  DEBUGN("HTTP server starting.");
}

void checkWiFiConnection() {
  if (WiFi.status() != WL_CONNECTED) {
    DEBUGN("WiFi lost");
    WiFi.disconnect();
    Delay(250);
    connectWiFi();
  }
}

void checkAPTimeout() {
  unsigned long now = millis();
  if (now > WIFI_AP_TIMEOUT && WiFi.softAPgetStationNum() == 0) {
    setLampState(STATE_SWITCH_TO_STA);
    DEBUGN("AP is Timeout!!!");
  }
}

void enterError() {
  DEBUGN("-> ERROR <-");
  Delay(1000);
  setLampState(STATE_RESET);
}

const char * const WIFI_STATE[] PROGMEM
{
  "IDLE_STATUS",
  "NO_SSID_AVAIL",
  "SCAN_COMPLETED",
  "CONNECTED",
  "CONNECT_FAILED",
  "CONNECTION_LOST",
  "WRONG_PASSWORD",
  "DISCONNECTED",
  "FAILED",
};

String getWiFiStateString(uint8_t s) {
#ifdef DEBUGING
  if (s <= 7) return WIFI_STATE[s];
  return WIFI_STATE[8];
#else
  (void)(s);
#endif
}