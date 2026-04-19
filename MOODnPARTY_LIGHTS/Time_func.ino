void runTime() {
  now = rtc.now();
  runAutoOnOff();
  runWiFiTimout();

  TimeSpan elapsed = now - lastHeartbeat;

  static bool done = false;
  if (now.second() % 5 == 0) {
    if (!done) {
      Serial.print(now.timestamp(DateTime::TIMESTAMP_TIME));
      Serial.print(" | ");
      Serial.print(ESP.getFreeHeap());
      // DEBUG2N(" | WiFi status:", getWiFiState(WiFi.status()));
      DEBUG2(" | Lamp status:", getNameLampState(getLampState()));
      // Compare with timeout value
      DEBUG2N(" |  elapsed:", elapsed.totalseconds() / 60);

      saveTime();

      if (ESP.getFreeHeap() < 30000) {
        DEBUG2N("Restart by LowHeap", ESP.getFreeHeap());
        ESP.restart();
      }
      done = true;
    }
  } else {
    done = false;
  }
}

void setTime(uint32_t t) {
  DateTime _time = DateTime(t);
  DEBUG2N("Time Set to:", _time.timestamp(DateTime::TIMESTAMP_FULL));
  rtc.adjust(_time);
  lastHeartbeat = rtc.now();
}

void runAutoOnOff() {
  DateTime tOn = DateTime(param.TIMEON);
  DateTime tOff = DateTime(param.TIMEOFF);

  if (now.hour() == tOn.hour() && now.minute() == tOn.minute() && now.second() == 0) {
    if (!lamp.isRunning()) {
      lamp.resume();
      isStandby = false;
      DEBUG("-= Auto On =-");
    }
  }
  if (now.hour() == tOff.hour() && now.minute() == tOff.minute() && now.second() == 0) {
    if (lamp.isRunning()) {
      lamp.stop();
      isStandby = true;
      DEBUG("-= Auto Off =-");
    }
  }
}

void runWiFiTimout() {
  DateTime tWOut = DateTime(param.WIFION);

  if (getLampState() == STATE_RUNNING_NOWIFI) {
    if (now.hour() == tWOut.hour() && now.minute() == tWOut.minute()) {
      setLampState(STATE_START_AP_ONLY);
      DEBUG("-= WiFi On =-");
    }
  } else if (isTimeout(param.WIFIOFF)) {
    setLampState(STATE_STOP_WIFI);
    DEBUG("-= WiFi Off =-");
  }
}

bool isRange() {
  DateTime tOn = DateTime(param.TIMEON);
  DateTime tOff = DateTime(param.TIMEOFF);
  uint16_t t = now.hour() * 60 + now.minute();
  uint16_t t_on = tOn.hour() * 60 + tOn.minute();
  uint16_t t_off = tOff.hour() * 60 + tOff.minute();

  return ((t >= t_on) && (t < t_off));
}

bool isTimeout(uint16_t timeoutmins) {
  // Calculate elapsed seconds since last heartbeat
  TimeSpan elapsed = now - lastHeartbeat;

  // Compare with timeout value
  if (elapsed.totalseconds() / 60 >= timeoutmins) {
    return true;  // timeout occurred
  }
  return false;  // still within allowed time
}