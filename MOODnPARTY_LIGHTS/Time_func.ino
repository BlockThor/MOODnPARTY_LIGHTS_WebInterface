void runTime() {
  now = rtc.now();

  if (isDay) {
    if (isStandby) {
      lamp.resume();
      isStandby = false;
    }
  } else {
    if (lamp.isRunning()) {
      lamp.stop();
      isStandby = true;
    }
  }

  static bool done = false;
  if (now.second() % 5 == 0) {
    if (!done) {
      Serial.print(now.timestamp(DateTime::TIMESTAMP_TIME));
      Serial.print(" | ");
      Serial.println(ESP.getFreeHeap());
      
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
}

void runAutoOnOff() {
  DateTime tOn = DateTime(param.TIMEON);
  DateTime tOff = DateTime(param.TIMEOFF);

  if (now.hour() == tOn.hour() && now.minute() == tOn.minute() && now.second() == 0) {
    if (!lamp.isRunning()) {
      lamp.resume();
      isStandby = false;
    }
    DEBUG("-= Auto On =-");
  }
  if (now.hour() == tOff.hour() && now.minute() == tOff.minute() && now.second() == 0) {
    if (lamp.isRunning()) {
      lamp.stop();
      isStandby = true;
    }
    DEBUG("-= Auto Off =-");
  }
}

bool isDay() {
  DateTime tOn = DateTime(param.TIMEON);
  DateTime tOff = DateTime(param.TIMEOFF);
  uint16_t t = now.hour() * 60 + now.minute();
  uint16_t t_on = tOn.hour() * 60 + tOn.minute();
  uint16_t t_off = tOff.hour() * 60 + tOff.minute();

  boolean isDay = ((t >= t_on) && (t < t_off));
  return isDay;
}