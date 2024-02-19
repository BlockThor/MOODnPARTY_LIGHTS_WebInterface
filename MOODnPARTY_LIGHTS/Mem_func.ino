/** Store WLAN credentials to EEPROM */
void saveCredentials() {
  EEPROM.put(0, wifidata);
  EEPROM.commit();
}
/** Load WLAN credentials from EEPROM */
void loadCredentials() {
  EEPROM.get(0, wifidata);
  if (String(wifidata.wifiSSID) == "") {
    DEBUGN("No WiFi data stored");
  } else {
    DEBUG2("Recovered SSID:", wifidata.wifiSSID);
    DEBUG2N(" Pass:", strlen(wifidata.wifiPass) > 0 ? F("********") : F("<no password>"));
  }
  if (String(wifidata.wifiSSID_Ap) == "") {
    DEBUGN("No ApWiFi data stored");
  } else {
    DEBUG2("Recovered SSID_Ap:", wifidata.wifiSSID_Ap);
    DEBUG2N(" Ap Pass:", strlen(wifidata.wifiPass_Ap) > 0 ? F("********") : F("<no password>"));
  }
}
/** Save Parameters from EEPROM */
void saveParameters() {
  uint8_t addr = sizeof(wifidata) + 2;
  EEPROM.put(addr, param);
  if (EEPROM.commit()) {
    Delay(10);
    //    DEBUGN("Settings saved");;
  } else {
    DEBUGN("EEPROM error");;
  }
}
/** Load Parameters from EEPROM */
void loadParameters() {
  DEBUGN("Load parameters");
  uint8_t addr = sizeof(wifidata) + 2;
  EEPROM.get(addr, param);
  DEBUG2N("Loaded.  Last addr:", addr);
  DEBUG2N("MAGIC:\tHx",   param.MAGIC);
  DEBUG2XN("COLOR0:\tHx", param.COLOR0);
  DEBUG2XN("COLOR1:\tHx", param.COLOR1);
  DEBUG2XN("COLOR2:\tHx", param.COLOR2);
  DEBUG2N("Mode:\t",      param.MODE);
  DEBUG2N("C_md:\t",      param.COLORMODE);
  DEBUG2N("Speed:\t",     param.SPEED);
  DEBUG2N("Bri:\t",       param.BRI);
  DEBUG2XN("Option:\tBx", param.OPTION);
  DEBUG2N("pMode:\t",     param.PLAYMODE);
  DEBUG2N("pTime:\t",     param.PLAYTIME);
  DEBUG2N("pL_Pin:\t",    param.LEDPIN);
  DEBUG2N("pL_Count:\t",  param.LEDCOUNT);
  DEBUG2N("pL_Type:\t",   param.LEDTYPE);
  DEBUG2N("FADE:\t",   ((param.OPTION) & FADE_GLACIAL));
  DEBUG2N("SIZE:\t",   ((param.OPTION) & SIZE_XLARGE));
}

/** INIT Parameters */
void initParameters() {
  memset(wifidata.wifiSSID, 0, sizeof(wifidata.wifiSSID) - 1);
  memset(wifidata.wifiPass, 0, sizeof(wifidata.wifiPass) - 1);
  String(WIFI_AP_SSID).toCharArray(wifidata.wifiSSID_Ap, 20);
  String(WIFI_AP_PASS).toCharArray(wifidata.wifiPass_Ap, 20);
  param = paramsDefault;
  param.MAGIC =  ESP.getChipId();
  DEBUGN("Set to default");
  saveCredentials();
  saveParameters();
}
