//  -= = = = = =  Webserver Functions  = = = = = =-

// - - - - - - SRV HANDLE - - - - - -

void srv_handle_sendwifi() {
  DEBUG("Handle WiFi: ");
  DEBUG2N("Counted args:", webServer.args());

  for (uint8_t i = 0; i < webServer.args(); i++) {
    DEBUG2("Arg: ", webServer.argName(i)); DEBUG2N("\t= ", webServer.arg(i));
    webServer.arg("n").toCharArray(wifidata.wifiSSID, sizeof(wifidata.wifiSSID) - 1);
    webServer.arg("p").toCharArray(wifidata.wifiPass, sizeof(wifidata.wifiPass) - 1);
  }
  webServer.send(200, "text/plain", "Ok");
  //  webServer.client().stop(); // Stop is needed because we sent no content length

  saveCredentials();
  loadCredentials();
  if (String(wifidata.wifiSSID) == "") {
    setLampState(STATE_START_AP_ONLY);
  } else {
    setLampState(STATE_START_AP_STA);
  }
}

void srv_handle_sendapwifi() {
  DEBUG("Handle ApWiFi\n");
  for (uint8_t i = 0; i < webServer.args(); i++) {
    DEBUG2("Arg: ", webServer.argName(i)); DEBUG2N("\t= ", webServer.arg(i));
    webServer.arg("an").toCharArray(wifidata.wifiSSID_Ap, sizeof(wifidata.wifiSSID) - 1);
    webServer.arg("ap").toCharArray(wifidata.wifiPass_Ap, sizeof(wifidata.wifiPass) - 1);
  }
  webServer.send(200, "text/plain", "Ok");
  //  webServer.client().stop(); // Stop is needed because we sent no content length

  if (String(wifidata.wifiSSID_Ap) == "") { // AP WiFi name can't be empty - set default
    String(WIFI_AP_SSID).toCharArray(wifidata.wifiSSID_Ap, 20);
    String(WIFI_AP_PASS).toCharArray(wifidata.wifiPass_Ap, 20);
  }
  saveCredentials();
  loadCredentials();
}
void srv_handle_wifiscan() {
  int8_t scanResult = 0;
  String Page;
  DEBUGN("Scan start");
  WiFi.scanNetworks(true);
  unsigned long startTimer = millis();
  while (scanResult = 0 && millis() - startTimer < TTC) {
    scanResult = WiFi.scanComplete();
    Delay(100);
    DEBUG(".");
  }
  DEBUG("\n");

  Page = String(F("<table>"));
  if (scanResult > 0) {
    for (int i = 0; i < scanResult; i++) {
      if (i > 0 && WiFi.SSID(i) == WiFi.SSID(i - 1)) continue; // if two WiFi are same name ignore
      Page += String(F("\r\n<tr><td>")) + ((WiFi.encryptionType(i) == ENC_TYPE_NONE) ? " " : String(F("&#x1F512")));
      Page += String(F("</td><td><a name='")) + ((WiFi.encryptionType(i) == ENC_TYPE_NONE) ? 'O' : 'L');
      Page += String("' href='#n' onclick='f(this)'>") + WiFi.SSID(i) + F("</a></td></tr>");
    }
  } else {
    Page += F("\r\n<tr><td></td> <td>No WiFi found</td></tr>");
  }
  Page += F("<tr><td></td><td><small>(rescan if any missing)</small></td></tr></table>");

  DEBUG2N("Scan done: ", scanResult);
  webServer.send(200, "text/plain", Page);
}

void srv_handle_cmd() {
  String sName = webServer.argName(0);
  if (sName == "sst") {  // save settings
    param.LEDCOUNT = lamp.getLength();
    param.LEDPIN = lamp.getPin();
    //      param.LEDTYPE = p;
    saveParameters();
    DEBUGN("Settings saved");
  }
  if (sName == "reset") {  // reset all parameters to default
    initParameters();
    DEBUGN("Reset to Factory");
  }
  if (sName == "restart") {  // reset all parameters to default
    DEBUGN("Restart");
    setLampState(STATE_RESET);
    //    ESP.reset();
  }
  webServer.send(200, "text/plain", "Ok");
}
void srv_handle_not_found() {
  if (captivePortal()) { // If caprive portal redirect instead of displaying the error page.
    return;
  }
  webServer.send(404, "text/plain", "File Not Found");
}

void srv_handle_index_html() {
  DEBUG2N("Server header:", webServer.hostHeader());
  if (captivePortal()) { // If caprive portal redirect instead of displaying the page.
    return;
  }
  String stringHTML = index_html;
  String page;
  char hexcol[6];

  // - - - txt processor - - -
  stringHTML.replace("{TT}", String(F(MNP_TITLE)));
  stringHTML.replace("{HD}", String(F(MNP_HEADER)));
  stringHTML.replace("{FT}", String(F(MNP_FOOTER)));

  sprintf(hexcol, "%06x", param.COLOR0);
  stringHTML.replace("{C0}", String(hexcol));
  sprintf(hexcol, "%06x", param.COLOR1);
  stringHTML.replace("{C1}", String(hexcol));
  sprintf(hexcol, "%06x", param.COLOR2);
  stringHTML.replace("{C2}", String(hexcol));

  page = param_Page_setup();
  stringHTML.replace("{PM}", page);

  page = allModes_Page_setup();
  stringHTML.replace("{M0}", page);
  page = monoModes_Page_setup();
  stringHTML.replace("{M1}", page);
  page = duoModes_Page_setup();
  stringHTML.replace("{M2}", page);
  page = rgbModes_Page_setup();
  stringHTML.replace("{M3}", page);
  page = specModes_Page_setup();
  stringHTML.replace("{M4}", page);

  page = wifiInfo_Page_setup();
  stringHTML.replace("{WR}", page);

  page = about_Page_setup();
  stringHTML.replace("{AB}", page);

  page = String(lamp.getLength());
  stringHTML.replace("{SN}", page);
  page = String(lamp.getPin());
  stringHTML.replace("{SP}", page);
  page = String(wifidata.wifiSSID_Ap);
  stringHTML.replace("{AN}", page);



  // - - - - - - - - - - -

  webServer.sendHeader("Cache-Control", "no-cache, no-store, must-revalidate");
  webServer.sendHeader("Pragma", "no-cache");
  webServer.sendHeader("Expires", "-1");
  webServer.send(200, "text/html", stringHTML);
  stringHTML = "";
  page = "";
}

void srv_handle_main_js() {
  webServer.send_P(200, "application/javascript", main_js);
}
void srv_handle_style_css() {
  webServer.send_P(200, "text/css", style_css);
}

void srv_handle_set() {
  String sName = "";
  String sArg = "";
  for (uint8_t i = 0; i < webServer.args(); i++) {
    DEBUG2("Arg: ", webServer.argName(i)); DEBUG2N(" = ", webServer.arg(i));
    sName = webServer.argName(i);
    sArg = webServer.arg(i);
    if (sName == "rst") {  // reset all parameters to default
      initParameters();
    }
    if (sName == "c0") {
      uint32_t rcvdColor = sArg.toInt();
      if (rcvdColor <= 0xFFFFFF) {
        param.COLOR0 = rcvdColor;
        applyColors();
        //        DEBUG2XN(" R:",rcvdColor>>16 & 0xFF);DEBUG2XN(" G:",rcvdColor>>8 & 0xFF);DEBUG2XN(" B:",rcvdColor & 0xFF);
      }
    }
    if (sName == "c1") {
      uint32_t rcvdColor = sArg.toInt();
      if (rcvdColor <= 0xFFFFFF) {
        param.COLOR1 = rcvdColor;
        applyColors();
      }
    }
    if (sName == "c2") {
      uint32_t rcvdColor = sArg.toInt();
      if (rcvdColor <= 0xFFFFFF) {
        param.COLOR2 = rcvdColor;
        applyColors();
      }
    }

    if (sName == "nm") {
      uint8_t tmp = (uint8_t)sArg.toInt();
      lamp.setMode(tmp);
      setColorMode(COLORMODE_DUO);
      param.MODE = lamp.getMode();
      param.COLORMODE = COLORMODE_DUO;
      param.PLAYMODE = P_NONE;
      DEBUG2N("normMode is ", lamp.getModeName(lamp.getMode()));
    }
    if (sName == "mm") {
      uint8_t tmp = (uint8_t)sArg.toInt();
      lamp.setMode(monoModes[tmp]);
      setColorMode(COLORMODE_MONO);
      param.MODE = lamp.getMode();
      param.COLORMODE = COLORMODE_MONO;
      param.PLAYMODE = P_NONE;
      DEBUG2N("monoModes is ", lamp.getModeName(lamp.getMode()));
    }
    if (sName == "md") {
      uint8_t tmp = (uint8_t)sArg.toInt();
      lamp.setMode(duoModes[tmp]);
      setColorMode(COLORMODE_DUO);
      param.MODE = lamp.getMode();
      param.COLORMODE = COLORMODE_DUO;
      param.PLAYMODE = P_NONE;
      DEBUG2N("duoModes is ", lamp.getModeName(lamp.getMode()));
    }
    if (sName == "mr") {
      uint8_t tmp = (uint8_t)sArg.toInt();
      lamp.setMode(rgbModes[tmp]);
      setColorMode(COLORMODE_RGB);
      param.MODE = lamp.getMode();
      param.COLORMODE = COLORMODE_RGB;
      param.PLAYMODE = P_NONE;
      DEBUG2N("rgbModes is ", lamp.getModeName(lamp.getMode()));
    }
    if (sName == "ms") {
      uint8_t tmp = (uint8_t)sArg.toInt();
      lamp.setMode(specModes[tmp]);
      setColorMode(COLORMODE_DUO);
      param.MODE = lamp.getMode();
      param.COLORMODE = COLORMODE_DUO;
      param.PLAYMODE = P_NONE;
      DEBUG2N("specModes is ", lamp.getModeName(lamp.getMode()));
    }

    if (sName == "of") {
      if (webServer.arg(i)[0] == '0') {
        lamp.stop();  //      lamp.pause();
      } else {
        lamp.start(); //      lamp.resume();
      }
    }
    if (sName == "br") { // brightness
      if (webServer.arg(i)[0] == '-') {
        lamp.setBrightness(lamp.getBrightness() * 0.8);
      } else if (webServer.arg(i)[0] == ' ') {
        lamp.setBrightness(min(max(lamp.getBrightness(), 5) * 1.2, 255));
      } else { // set brightness directly
        uint8_t tmp = (uint8_t)sArg.toInt();
        lamp.setBrightness(tmp);
      }
      param.BRI = lamp.getBrightness();
      //      DEBUG2N("brightness is ", lamp.getBrightness());
    }

    if (sName == "ds") { //speed
      if (webServer.arg(i)[0] == '-') {
        lamp.setSpeed(max(lamp.getSpeed(), 5) * 1.2);
      } else if (webServer.arg(i)[0] == ' ') {
        lamp.setSpeed(lamp.getSpeed() * 0.8);
      } else {
        uint16_t tmp = sArg.toInt();
        lamp.setSpeed(tmp);
      }
      param.SPEED = lamp.getSpeed();
      //      DEBUG2N("speed is ", lamp.getSpeed());
    }
    if (sName == "ap") { // playmode - autoplay
      uint16_t p = (uint16_t)sArg.toInt();
      param.PLAYMODE = p;
      //      DEBUG2N("playMode:", param.PLAYMODE);
      auto_last_change = 0;
    }
    if (sName == "at") { // playtime - autotime
      uint16_t p = (uint16_t)sArg.toInt();
      param.PLAYTIME = p;
      //      DEBUG2N("playTime:", param.PLAYTIME);
      auto_last_change = 0;
    }

    if (sName == "dr") { // direct / reverse
      uint8_t opts = lamp.getOptions(0);
      if (webServer.arg(i)[0] == 'r') {
        lamp.setOptions(0, opts | REVERSE);
      } else {
        lamp.setOptions(0, opts & ~REVERSE);
      }
      //      DEBUG2BN("Options:", lamp.getOptions(0));
    }
    if (sName == "sz") { // size
      uint8_t opts = lamp.getOptions(0);
      uint16_t p = (uint16_t)sArg.toInt();
      opts &= ~SIZE_XLARGE;
      opts |= p;
      lamp.setOptions(0, opts);
      lamp.resetSegmentRuntime(0);
    }
    if (sName == "fd") {
      uint8_t opts = lamp.getOptions(0);
      uint16_t p = (uint16_t)sArg.toInt();
      opts &= ~FADE_GLACIAL;
      opts |= p;
      lamp.setOptions(0, opts);
      //      DEBUG2BN("Options:", lamp.getOptions(0));
      //      DEBUG2N("Rate set to:", lamp.getOptions(0)));
    }

    // LED HARDWARE
    if (sName == "sn") {
      uint16_t p = (uint16_t)sArg.toInt();
      //      param.LEDCOUNT = p;
      lamp.fill(0, 0, lamp.getLength());
      lamp.setLength(p);
      DEBUG2N("LEDCOUNT:", p);
    }
    if (sName == "sp") {
      uint16_t p = (uint16_t)sArg.toInt();
      //      param.LEDPIN = p;
      lamp.setPin(p);
      DEBUG2N("LEDPIN:", p);
    }
    if (sName == "st") {
      uint16_t p = (uint16_t)sArg.toInt();
      param.LEDTYPE = p;
      lamp.updateType(p);
      DEBUG2N("LEDTYPE:", p);
    }
    if (sName == "sb") {
      DEBUG("SET BUTTON RESET!");
    }
  }
  param.OPTION = lamp.getOptions(0);
  saveParameters();
  webServer.send(200, "text/plain", "Ok");
  webServer.client().stop(); // Stop is needed because we sent no content length
  //SOME WHERE HERE MOST PROBABLY SHOULD BE THE REASON FOR FREEZE WIFI MODULE AFTER SEVERAL CALLS
}


// - - - - - - PAGE SETUPS - - - - - -

String wifiInfo_Page_setup() {
  String page;
  if (webServer.client().localIP() == WIFI_AP_IP) {
    page += String(F("<p>through the soft AP:<br/>")) + wifidata.wifiSSID_Ap + F("</p>");
  } else {
    page += String(F("<p>through the wifi network:<br/>")) + wifidata.wifiSSID + F("</p>\r\n<br/>");
  }
  if (lampState != STATE_RUNNING_STA) {
    page += String(F("<table><tr><th>SoftAP config</th></tr><tr><td><i>SSID</i> ")) +
            String(wifidata.wifiSSID_Ap) +
            F("</td></tr><tr><td><i>IP</i> ") +
            WiFi.softAPIP().toString() +
            F("</td></tr></table>\r\n<br />");
  }
  page += String(F("<table><tr><th>WLAN config</th></tr><tr><td>SSID ")) +
          String(wifidata.wifiSSID) +
          F("</td></tr><tr><td>") +
          ((WiFi.status() != WL_CONNECTED) ? getWiFiStateString(lastWiFiStatus) : F("IP ") + WiFi.localIP().toString()) +
          F("</td></tr></table>");
  return page;
}

String allModes_Page_setup() {
  String page;
  uint8_t num_modes = lamp.getModeCount();
  for (uint8_t i = 0; i < num_modes - MAX_CUSTOM_MODES; i++) {
    page += "\n<li>";
    page += lamp.getModeName(i);
    page += "</li>";
  }
  return page;
}
String monoModes_Page_setup() {
  String page;
  uint8_t num_modes = sizeof(monoModes);
  for (uint8_t i = 0; i < num_modes; i++) {
    page += "\n<li>";
    page += lamp.getModeName(monoModes[i]);
    page += "</li>";
  }
  return page;
}
String duoModes_Page_setup() {
  String page;
  uint8_t num_modes = sizeof(duoModes);
  for (uint8_t i = 0; i < num_modes; i++) {
    page += "\n<li>";
    page += lamp.getModeName(duoModes[i]);
    page += "</li>";
  }
  return page;
}
String rgbModes_Page_setup() {
  String page;
  uint8_t num_modes = sizeof(rgbModes);
  for (uint8_t i = 0; i < num_modes; i++) {
    page += "\n<li>";
    page += lamp.getModeName(rgbModes[i]);
    page += "</li>";
  }
  return page;
}
String specModes_Page_setup() {
  String page;
  uint8_t num_modes = sizeof(specModes);
  for (uint8_t i = 0; i < num_modes; i++) {
    page += "\n<li>";
    page += lamp.getModeName(specModes[i]);
    page += "</li>";
  }
  return page;
}

String param_Page_setup() {
  //{'of':1, 'br':64, 'ds':1000, 'ap':0, 'pt':60, 'dr':'r', 'sz':6, 'fd':48 }
  String page;
  page +=  "{of:";
  page +=  lamp.isRunning() ? "1" : "0";
  page += ", br:" + String(param.BRI);
  page += ", ds:" + String(param.SPEED);
  page += ", ap:" + String(param.PLAYMODE);
  page += ", at:" + String(param.PLAYTIME);
  page += ", dr:" + String((((param.OPTION & REVERSE) == REVERSE) ? "'r'" : "'d'"));
  page += ", sz:" + String(param.OPTION & SIZE_XLARGE);
  page += ", fd:" + String(param.OPTION & FADE_GLACIAL);
  page += "}";
  return page;
}

String about_Page_setup() {
  String page;
  //  page += String(F("<p> Let's talk about!</p><p>Thank for using my lovely MoodLineLamp!</p><p>Thank for using my lovely MoodLineLamp!</p>"));
  page = String(F(MNP_ABOUTCONTENT));

#if !defined(WS2812FX_MNP_EDITION_h)
  page += String(F("<p>!!! Designed for WS2812FX_MNP_EDITION lib !!!</p><p>Please download <a href='https://github.com/BlockThor/WS2812FX_MOODnPARTY_Edition'>Mood&Party Lights WS2812FX Lib</a></p>"));
#endif

  return page;
}

boolean captivePortal() {
  IPAddress hAddr, cAddr;
  cAddr = webServer.client().localIP();
  if (!cAddr.isSet()) {
    return true;
  }
  if (hAddr.fromString(webServer.hostHeader()) && hAddr == cAddr) {
    return false;
  }
  return false;
}
