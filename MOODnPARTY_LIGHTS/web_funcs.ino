//  -= = = = = =  Webserver Functions  = = = = = =-

// - - - - - - SRV HANDLE - - - - - -

void srv_handle_sendwifi() {
  DEBUG("Handle WiFi: ");
  DEBUG2N("Counted args:", webServer.args());

  for (uint8_t i = 0; i < webServer.args(); i++) {
    DEBUG2("Arg: ", webServer.argName(i));
    DEBUG2N("\t= ", webServer.arg(i));
    webServer.arg("n").toCharArray(wifidata.wifiSSID, sizeof(wifidata.wifiSSID) - 1);
    webServer.arg("p").toCharArray(wifidata.wifiPass, sizeof(wifidata.wifiPass) - 1);
  }
  webServer.send(200, "text/plain", "Ok");

  saveCredentials();
  loadCredentials();

  if (wifidata.wifiSSID[0] == '\0') {
    setLampState(STATE_START_AP_ONLY);
  } else {
    setLampState(STATE_START_AP_STA);
  }
}

// void srv_handle_sendapwifi() {
//   DEBUG("Handle ApWiFi\n");
//   for (uint8_t i = 0; i < webServer.args(); i++) {
//     DEBUG2("Arg: ", webServer.argName(i));
//     DEBUG2N("\t= ", webServer.arg(i));
//     webServer.arg("an").toCharArray(wifidata.wifiSSID_Ap, sizeof(wifidata.wifiSSID) - 1);
//     webServer.arg("ap").toCharArray(wifidata.wifiPass_Ap, sizeof(wifidata.wifiPass) - 1);
//   }
//   webServer.send(200, "text/plain", "Ok");
//   //  webServer.client().stop(); // Stop is needed because we sent no content length

//   if (String(wifidata.wifiSSID_Ap) == "") {  // AP WiFi name can't be empty - set default
//     String(WIFI_AP_SSID).toCharArray(wifidata.wifiSSID_Ap, 20);
//     String(WIFI_AP_PASS).toCharArray(wifidata.wifiPass_Ap, 20);
//   }
//   saveCredentials();
//   loadCredentials();
// }
void srv_handle_sendapwifi() {
  DEBUG("Handle ApWiFi\n");

  if (webServer.hasArg("an")) {
    strncpy(wifidata.wifiSSID_Ap, webServer.arg("an").c_str(), sizeof(wifidata.wifiSSID_Ap) - 1);
    wifidata.wifiSSID_Ap[sizeof(wifidata.wifiSSID_Ap) - 1] = '\0';
  }

  if (webServer.hasArg("ap")) {
    strncpy(wifidata.wifiPass_Ap, webServer.arg("ap").c_str(), sizeof(wifidata.wifiPass_Ap) - 1);
    wifidata.wifiPass_Ap[sizeof(wifidata.wifiPass_Ap) - 1] = '\0';
  }

  webServer.send(200, "text/plain", "Ok");

  if (wifidata.wifiSSID_Ap[0] == '\0') {
    strncpy(wifidata.wifiSSID_Ap, WIFI_AP_SSID, sizeof(wifidata.wifiSSID_Ap) - 1);
    wifidata.wifiSSID_Ap[sizeof(wifidata.wifiSSID_Ap) - 1] = '\0';

    strncpy(wifidata.wifiPass_Ap, WIFI_AP_PASS, sizeof(wifidata.wifiPass_Ap) - 1);
    wifidata.wifiPass_Ap[sizeof(wifidata.wifiPass_Ap) - 1] = '\0';
  }
  saveCredentials();
  loadCredentials();
}

void srv_handle_wifiscan() {
  DEBUGN("Scan start");
  WiFi.scanNetworks(true);  // async scan
  unsigned long startTimer = millis();
  int8_t scanResult = 0;
  // wait for scan to complete or timeout
  while (scanResult == 0 && millis() - startTimer < TTC) {
    scanResult = WiFi.scanComplete();
    delay(100);
    DEBUG(".");
  }
  DEBUG("\n");

  webServer.setContentLength(CONTENT_LENGTH_UNKNOWN);
  webServer.send(200, "text/html", "");
  webServer.sendContent_P(PSTR("<table>"));

  if (scanResult > 0) {
    for (int i = 0; i < scanResult; i++) {
      if (i > 0 && WiFi.SSID(i) == WiFi.SSID(i - 1)) continue;  // skip duplicates
      // encryption icon
      if (WiFi.encryptionType(i) == ENC_TYPE_NONE) {
        webServer.sendContent_P(PSTR("\r\n<tr><td> </td><td><a name='O' href='#n' onclick='f(this)'>"));
      } else {
        webServer.sendContent_P(PSTR("\r\n<tr><td>&#x1F512</td><td><a name='L' href='#n' onclick='f(this)'>"));
      }
      // SSID
      webServer.sendContent(WiFi.SSID(i).c_str());
      webServer.sendContent_P(PSTR("</a></td></tr>"));
    }
  } else {
    webServer.sendContent_P(PSTR("\r\n<tr><td></td><td>No WiFi found</td></tr>"));
  }
  webServer.sendContent_P(PSTR("<tr><td></td><td><small>(rescan if any missing)</small></td></tr></table>"));
  webServer.client().stop();
  DEBUG2N("Scan done: ", scanResult);
}

void srv_handle_cmd() {
  if (webServer.hasArg("command")) {
    const char* cmd = webServer.arg("command").c_str();
    DEBUG2N("Received command: ", cmd);
    // if (cmd == "sst") {  // save settings
    if (strcmp(cmd, "sst") == 0) {  // save settings
      param.LEDCOUNT = lamp.getLength();
      param.LEDPIN = lamp.getPin();
      saveParameters();
      DEBUGN("Settings saved");
    } else if (strcmp(cmd, "reset") == 0) {  // reset all parameters to default
      initParameters();
      DEBUGN("Reset to Factory");
    } else if (strcmp(cmd, "restart") == 0) {  // restart lamp
      DEBUGN("Restart");
      setLampState(STATE_RESET);
    }
    webServer.send(200, "text/plain", "Ok");
  } else {
    webServer.send(400, "text/plain", "Missing command");
  }
}

void srv_handle_time() {
  if (webServer.hasArg("timestamp")) {
    const char* arg = webServer.arg("timestamp").c_str();  // safe C-string
    uint32_t webTime = strtoul(arg, nullptr, 10);
    setTime(webTime);
    saveTime();
    yield();
    webServer.send(200, "text/plain", "Ok");
  } else {
    webServer.send(400, "text/plain", "Missing timestamp");
  }
}
void srv_handle_timer() {
  DEBUG2N("Rcv srv_handle_timer: ", webServer.args());
  if (webServer.hasArg("on") && webServer.hasArg("off") && webServer.hasArg("won") && webServer.hasArg("woff")) {

    uint32_t onSec = strtoul(webServer.arg("on").c_str(), nullptr, 10);
    uint32_t offSec = strtoul(webServer.arg("off").c_str(), nullptr, 10);
    uint32_t wonSec = strtoul(webServer.arg("won").c_str(), nullptr, 10);
    uint32_t woffMin = strtoul(webServer.arg("woff").c_str(), nullptr, 10);
    DEBUGX("Auto on: %lu  off: %lu\n won: %lu  woff: %lu\n", onSec, offSec, wonSec, woffMin);

    param.TIMEON = onSec;
    param.TIMEOFF = offSec;
    param.WIFION = wonSec;
    param.WIFIOFF = woffMin;
    DEBUG2N("TimeOn:\t", DateTime(param.TIMEON).timestamp(DateTime::TIMESTAMP_FULL));
    DEBUG2N("TimeOff:\t", DateTime(param.TIMEOFF).timestamp(DateTime::TIMESTAMP_TIME));
    DEBUG2N("WiFiOn:\t", DateTime(param.TIMEOFF).timestamp(DateTime::TIMESTAMP_TIME));
    saveParameters();
    webServer.send(200, "text/plain", "Ok");
  } else {
    webServer.send(400, "text/plain", "Missing timers");
  }
}

void srv_handle_not_found() {
  if (captivePortal()) return;
  DEBUG2N("404 header:", webServer.hostHeader());
  webServer.send(404, "text/plain", "");
  webServer.client().stop();
}


void srv_handle_index_html() {
  // DEBUG2N("header:", webServer.header());
  // DEBUG2N("Name:", webServer.headerName());
  if (captivePortal()) {  // If caprive portal redirect instead of displaying the page.
    return;
  }
  webServer.sendHeader("Cache-Control", "no-cache, no-store, must-revalidate");
  webServer.sendHeader("Pragma", "no-cache");
  webServer.sendHeader("Expires", "-1");
  webServer.send_P(200, "text/html", index_html);
}

void srv_handle_main_js() {
  DEBUG(" main.js ");
  webServer.sendHeader("Cache-Control", "no-cache");
  webServer.send_P(200, "application/javascript", main_js);
}

void srv_handle_vars_js() {
  DEBUG(" vars.js ");
  webServer.setContentLength(CONTENT_LENGTH_UNKNOWN);
  webServer.send(200, "application/javascript", "");
  webServer.sendContent_P(PSTR("const param="));
  DEBUGN("const param=");
  webServer.sendContent(vars_setup());
  DEBUG2N(": ", vars_setup());

  webServer.sendContent_P(PSTR("TT:"));
  webServer.sendContent_P(PSTR("\""));
  webServer.sendContent_P(MNP_TITLE);
  webServer.sendContent_P(PSTR("\","));
  DEBUGN(MNP_TITLE);

  webServer.sendContent_P(PSTR("HD:"));
  webServer.sendContent_P(PSTR("\""));
  webServer.sendContent_P(MNP_HEADER);
  webServer.sendContent_P(PSTR("\","));
  DEBUGN(MNP_HEADER);

  webServer.sendContent_P(PSTR("FT:"));
  webServer.sendContent_P(PSTR("\""));
  webServer.sendContent_P(MNP_FOOTER);
  webServer.sendContent_P(PSTR("\","));
  DEBUGN(MNP_FOOTER);

  webServer.sendContent_P(PSTR("AB:"));
  webServer.sendContent_P(PSTR("\""));
  webServer.sendContent_P(MNP_ABOUTCONTENT);
  webServer.sendContent_P(PSTR("<br>Current mode: \'"));
  webServer.sendContent(lamp.getModeName(lamp.getMode()));
  webServer.sendContent_P(PSTR("\'<br>Current ver.: \'"));
  char buffer[16];  // enough space for "0x" + 8 hex digits + null terminator
  sprintf(buffer, "0x%X", MNPL_VERSION);
  webServer.sendContent(buffer);
  webServer.sendContent_P(PSTR("\'<br>\","));
  DEBUGN(MNP_ABOUTCONTENT);

  webServer.sendContent_P(PSTR("WR:"));
  webServer.sendContent_P(PSTR("\""));
  // webServer.sendContent_P(PSTR("<p>through the wifi network:<br>Oinoussian_3</p><br><table><tbody><tr><th>WLAN config</th></tr><tr><td>SSID OinoussianCrew</td></tr><tr><td>IP 1.2.3.4</td></tr></tbody></table>"));
  // Connection type
  // if (webServer.client().localIP() == WIFI_AP_IP) {
  //   webServer.sendContent_P(PSTR("connection:\'softAP\',<br>"));
  //   webServer.sendContent_P(PSTR("ssid:\'"));
  //   webServer.sendContent(wifidata.wifiSSID_Ap);
  //   webServer.sendContent_P(PSTR("\'<br>"));
  // } else {
  //   webServer.sendContent_P(PSTR("connection:\'station\'<br>"));
  //   webServer.sendContent_P(PSTR("ssid:\'"));
  //   webServer.sendContent(wifidata.wifiSSID);
  //   webServer.sendContent_P(PSTR("\'<br>"));
  // }

  // // SoftAP config if not running STA
  // if (lampState != STATE_RUNNING_STA) {
  //   webServer.sendContent_P(PSTR("ssid:\'"));
  //   webServer.sendContent(wifidata.wifiSSID_Ap);
  //   webServer.sendContent_P(PSTR("\', ip:\'"));
  //   webServer.sendContent(WiFi.softAPIP().toString());
  //   webServer.sendContent_P(PSTR("\'"));
  // }

  webServer.sendContent_P(PSTR("\"}"));
  webServer.sendContent("");
  Delay(100);
  webServer.client().stop();
}

// char urlBuf[32];
// IPAddress ip = webServer.client().localIP();
// snprintf(urlBuf, sizeof(urlBuf), "http://%u.%u.%u.%u", ip[0], ip[1], ip[2], ip[3]);


void srv_handle_modes_js() {
  DEBUG(" modes.js ");
  webServer.setContentLength(CONTENT_LENGTH_UNKNOWN);
  webServer.send(200, "application/javascript", "");

  webServer.sendContent_P(PSTR("const modes={"));

  // monoModes array
  webServer.sendContent_P(PSTR("monoModes:["));
  uint8_t num = sizeof(monoModes);
  for (uint8_t i = 0; i < num; i++) {
    webServer.sendContent("\"");
    webServer.sendContent(lamp.getModeName(monoModes[i]));
    webServer.sendContent("\"");
    if (i < num - 1) {
      webServer.sendContent(",");
    }
  }
  webServer.sendContent_P(PSTR("],"));
  // duoModes array
  webServer.sendContent_P(PSTR("duoModes:["));
  num = sizeof(duoModes);
  for (uint8_t i = 0; i < num; i++) {
    webServer.sendContent("\"");
    webServer.sendContent(lamp.getModeName(duoModes[i]));
    webServer.sendContent("\"");
    if (i < num - 1) {
      webServer.sendContent(",");
    }
  }
  webServer.sendContent_P(PSTR("],"));
  // rgbModes array
  webServer.sendContent_P(PSTR("rgbModes:["));
  num = sizeof(rgbModes);
  for (uint8_t i = 0; i < num; i++) {
    webServer.sendContent("\"");
    webServer.sendContent(lamp.getModeName(rgbModes[i]));
    webServer.sendContent("\"");
    if (i < num - 1) {
      webServer.sendContent(",");
    }
  }
  webServer.sendContent_P(PSTR("],"));
  // specModes array
  webServer.sendContent_P(PSTR("specModes:["));
  num = sizeof(specModes);
  for (uint8_t i = 0; i < num; i++) {
    webServer.sendContent("\"");
    webServer.sendContent(lamp.getModeName(specModes[i]));
    webServer.sendContent("\"");
    if (i < num - 1) {
      webServer.sendContent(",");
    }
  }
  webServer.sendContent("],");
  // allModes array
  webServer.sendContent_P(PSTR("allModes:["));
  num = lamp.getModeCount();
  for (uint8_t i = 0; i < num; i++) {
    webServer.sendContent("\"");
    webServer.sendContent(lamp.getModeName(i));
    webServer.sendContent("\"");
    if (i < num - 1) {
      webServer.sendContent(",");
    }
  }
  webServer.sendContent("],");

  webServer.sendContent("};");
  webServer.sendContent("");
  // Delay(100);
  webServer.client().stop();
}




void srv_handle_style_css() {
  webServer.sendHeader("Cache-Control", "no-cache");
  webServer.send_P(200, "text/css", style_css);
}

void srv_handle_set() {

  for (uint8_t i = 0; i < webServer.args(); i++) {
    const char* sName = webServer.argName(i).c_str();
    const char* sArg = webServer.arg(i).c_str();

    DEBUG2("Arg: ", sName);
    DEBUG2N(" = ", sArg);

    if (strcmp(sName, "rst") == 0) {
      initParameters();
    }
    yield();

    if (strcmp(sName, "c0") == 0) {
      uint32_t rcvdColor = strtoul(sArg, nullptr, 10);
      if (rcvdColor <= 0xFFFFFF) {
        param.COLOR0 = rcvdColor;
        applyColors();
      }
    } else if (strcmp(sName, "c1") == 0) {
      uint32_t rcvdColor = strtoul(sArg, nullptr, 10);
      if (rcvdColor <= 0xFFFFFF) {
        param.COLOR1 = rcvdColor;
        applyColors();
      }
    } else if (strcmp(sName, "c2") == 0) {
      uint32_t rcvdColor = strtoul(sArg, nullptr, 10);
      if (rcvdColor <= 0xFFFFFF) {
        param.COLOR2 = rcvdColor;
        applyColors();
      }
    }
    yield();
    // modes
    if (strcmp(sName, "mn") == 0) {
      uint8_t tmp = atoi(sArg);
      lamp.setMode(tmp);
      setColorMode(COLORMODE_DUO);
      param.MODE = lamp.getMode();
      param.COLORMODE = COLORMODE_DUO;
      param.PLAYMODE = P_NONE;
    } else if (strcmp(sName, "mm") == 0) {
      uint8_t tmp = atoi(sArg);
      lamp.setMode(monoModes[tmp]);
      setColorMode(COLORMODE_MONO);
      param.MODE = lamp.getMode();
      param.COLORMODE = COLORMODE_MONO;
      param.PLAYMODE = P_NONE;
    } else if (strcmp(sName, "md") == 0) {
      uint8_t tmp = atoi(sArg);
      lamp.setMode(duoModes[tmp]);
      setColorMode(COLORMODE_DUO);
      param.MODE = lamp.getMode();
      param.COLORMODE = COLORMODE_DUO;
      param.PLAYMODE = P_NONE;
    } else if (strcmp(sName, "mr") == 0) {
      uint8_t tmp = atoi(sArg);
      lamp.setMode(rgbModes[tmp]);
      setColorMode(COLORMODE_RGB);
      param.MODE = lamp.getMode();
      param.COLORMODE = COLORMODE_RGB;
      param.PLAYMODE = P_NONE;
    } else if (strcmp(sName, "ms") == 0) {
      uint8_t tmp = atoi(sArg);
      lamp.setMode(specModes[tmp]);
      setColorMode(COLORMODE_DUO);
      param.MODE = lamp.getMode();
      param.COLORMODE = COLORMODE_DUO;
      param.PLAYMODE = P_NONE;
    }
    yield();
    // on/off
    if (strcmp(sName, "of") == 0) {
      if (sArg[0] == '0') lamp.stop();
      else lamp.start();
    }
    // brightness
    else if (strcmp(sName, "br") == 0) {
      if (sArg[0] == '-') lamp.setBrightness(lamp.getBrightness() * 0.8);
      else if (sArg[0] == ' ') lamp.setBrightness(min(max(lamp.getBrightness(), 5) * 1.2, 255));
      else lamp.setBrightness(atoi(sArg));
      param.BRI = lamp.getBrightness();
    }
    // speed
    else if (strcmp(sName, "ds") == 0) {
      if (sArg[0] == '-') lamp.setSpeed(max(lamp.getSpeed(), 5) * 1.2);
      else if (sArg[0] == ' ') lamp.setSpeed(lamp.getSpeed() * 0.8);
      else lamp.setSpeed(atoi(sArg));
      param.SPEED = lamp.getSpeed();
    }
    yield();
    // autoplay
    if (strcmp(sName, "ap") == 0) {
      param.PLAYMODE = atoi(sArg);
      auto_last_change = 0;
    } else if (strcmp(sName, "at") == 0) {
      param.PLAYTIME = atoi(sArg);
      auto_last_change = 0;
    }
    // options
    else if (strcmp(sName, "dr") == 0) {
      uint8_t opts = lamp.getOptions(0);
      if (sArg[0] == 'r') lamp.setOptions(0, opts | REVERSE);
      else lamp.setOptions(0, opts & ~REVERSE);
    } else if (strcmp(sName, "sz") == 0) {
      uint8_t opts = lamp.getOptions(0);
      uint16_t p = atoi(sArg);
      opts &= ~SIZE_XLARGE;
      opts |= p;
      lamp.setOptions(0, opts);
      lamp.resetSegmentRuntime(0);
    } else if (strcmp(sName, "fd") == 0) {
      uint8_t opts = lamp.getOptions(0);
      uint16_t p = atoi(sArg);
      opts &= ~FADE_GLACIAL;
      opts |= p;
      lamp.setOptions(0, opts);
    }
    yield();
    // hardware
    if (strcmp(sName, "sn") == 0) {
      uint16_t p = atoi(sArg);
      lamp.stop();
      lamp.strip_off();
      lamp.setLength(p);
      lamp.stop();
      lamp.setBrightness(param.BRI);
      lamp.start();
    } else if (strcmp(sName, "sp") == 0) {
      lamp.setPin(atoi(sArg));
    } else if (strcmp(sName, "st") == 0) {
      param.LEDTYPE = atoi(sArg);
      lamp.updateType(param.LEDTYPE);
    } else if (strcmp(sName, "sb") == 0) {
      DEBUG("SET BUTTON RESET!");
    }
    yield();
  }
  yield();
  param.OPTION = lamp.getOptions(0);
  saveParameters();
  webServer.send(200, "text/plain", "Ok");
  // webServer.client().stop();  // Stop is needed because we sent no content length
  //SOME WHERE HERE MOST PROBABLY SHOULD BE THE REASON FOR FREEZE WIFI MODULE AFTER SEVERAL CALLS
}


// - - - - - - PAGE SETUPS - - - - - -
const char* vars_setup() {
  static char buf[400];  // static so it persists after function returns
  DateTime tOn = DateTime(param.TIMEON);
  DateTime tOff = DateTime(param.TIMEOFF);
  DateTime tWOn = DateTime(param.WIFION);
  char bufT0[6] = "hh:mm";
  now.toString(bufT0);
  char bufT1[6] = "hh:mm";
  tOn.toString(bufT1);
  char bufT2[6] = "hh:mm";
  tOff.toString(bufT2);
  char bufW1[6] = "hh:mm";
  tWOn.toString(bufW1);
  char hexcol0[7];
  sprintf(hexcol0, "%06x", param.COLOR0);
  char hexcol1[7];
  sprintf(hexcol1, "%06x", param.COLOR1);
  char hexcol2[7];
  sprintf(hexcol2, "%06x", param.COLOR2);
  snprintf(buf, sizeof(buf),
           "{of:%d, br:%u, ds:%u, ap:%u, at:%u, dr:'%c', sz:%u, fd:%u, SN:%u, SP:%u, "
           "Tm:\"%s\", T1:\"%s\", T2:\"%s\", W1:\"%s\", W2:%u, C0:\"#%s\", C1:\"#%s\", C2:\"#%s\", AN:\"%s\",",
           lamp.isRunning() ? 1 : 0,
           param.BRI,
           param.SPEED,
           param.PLAYMODE,
           param.PLAYTIME,
           ((param.OPTION & REVERSE) == REVERSE) ? 'r' : 'd',
           (param.OPTION & SIZE_XLARGE),
           (param.OPTION & FADE_GLACIAL),
           lamp.getLength(),
           lamp.getPin(),
           bufT0,
           bufT1,
           bufT2,
           bufW1,
           param.WIFIOFF,
           hexcol0,
           hexcol1,
           hexcol2,
           wifidata.wifiSSID_Ap);
  return buf;
}
//
bool captivePortal() {
  const char* host = webServer.hostHeader().c_str();
  if (!isIp(host)) {
    // ignore noisy domains
    if (strstr(host, "msftconnecttest.com") || strstr(host, "digicert.com") || strstr(host, "google.com") || strstr(host, "windowsupdate.com")) {
      webServer.client().stop();
      return true;
    }
    // otherwise redirect
    char urlBuf[32];
    IPAddress ip = webServer.client().localIP();
    snprintf(urlBuf, sizeof(urlBuf), "http://%u.%u.%u.%u", ip[0], ip[1], ip[2], ip[3]);
    webServer.sendHeader("Location", urlBuf, true);
    webServer.send(302, "text/plain", "");
    webServer.client().stop();
    return true;
  }
  return false;
}

/** Is this an IP? */
bool isIp(const char* str) {
  for (size_t i = 0; str[i] != '\0'; i++) {
    char c = str[i];
    if (c != '.' && (c < '0' || c > '9')) {
      return false;
    }
  }
  return true;
}