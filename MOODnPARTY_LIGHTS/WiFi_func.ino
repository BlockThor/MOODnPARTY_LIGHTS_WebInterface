#define WIFI_AP_TIMEOUT    60000
#define WIFI_AP_IP         IPAddress(172, 217, 28, 1)
#define WIFI_AP_SUBNET     IPAddress(255, 255, 255, 0)
//#define WIFI_DNS_PORT      (byte)53

#define WIFI_AP_SSID "MOODLAMP"
#define WIFI_AP_PASS  "MOODLAMP"
#define HOSTNAME "moodlamp"

const char *softAP_ssid = WIFI_AP_SSID;
const char *softAP_pass = WIFI_AP_PASS;

const byte DNS_PORT = 53;
IPAddress apIP(172, 217, 28, 1);
DNSServer dnsServer;
ESP8266WebServer webServer(80);

void runWiFi() {
  switch (lampState) {
    case   STATE_START_AP_ONLY:  startAP();      break;
    case   STATE_START_AP_STA:   startAPSTA();   break;
    case   STATE_SWITCH_TO_STA:  switchToSTA();  break;
    case   STATE_RUNNING_AP:     runningAP();    break;
    case   STATE_RUNNING_AP_STA: runningAPSTA(); break;
    case   STATE_RUNNING_STA:    runningSTA(); break;
    default: enterError();   break;
  }
}

bool startAP() {
  WiFi.mode(WIFI_OFF);
  Delay(100);
  WiFi.mode(WIFI_AP);

  WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
  WiFi.softAP(softAP_ssid, softAP_pass);
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
  WiFi.softAP(softAP_ssid, softAP_pass);

  dnsServer.setErrorReplyCode(DNSReplyCode::NoError);
  dnsServer.start(DNS_PORT, "*", apIP);
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
    while (WiFi.status() != WL_CONNECTED && millis() - startTimer < 120000) {
      Delay(500);
      DEBUG("|");
    }
    // Check connection
    if (WiFi.status() == WL_CONNECTED) {
      DEBUG2N(" Connected: ", WiFi.localIP());
      return true;
    } else {
      DEBUG2N("WiFi.NotConnected: ", WiFi.status());
      setLampState(STATE_ERROR);
      return false;
    }
  } else {
    DEBUG2N("WiFi.NotBegin: ", WiFi.status());
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
  webServer.on("/generate_204", srv_handle_index_html);  //Android captive portal. Maybe not needed. Might be handled by notFound handler.
  webServer.on("/fwlink", srv_handle_index_html);  //Microsoft captive portal. Maybe not needed. Might be handled by notFound handler.
  webServer.on("/scan", srv_handle_wifiscan);
  webServer.on("/sendWiFi", srv_handle_sendwifi);
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
  ESP.reset();
}
