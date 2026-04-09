void runTime() {
  now = rtc.now();
  static bool done = false;
  if (now.second() % 30 == 0) {
    if (!done) {
//      Serial.print(now.unixtime(), DEC);
//      Serial.print(" | ");
      Serial.print(now.hour(), DEC);
      Serial.print(':');
      Serial.print(now.minute(), DEC);
      Serial.print(':');
      Serial.print(now.second(), DEC);
      Serial.println();
      done = true;
    }
  } else {
    done = false;
  }
}

void setTime(uint32_t t) {
  DEBUG2N("Time Set to:", t);
  rtc.adjust(DateTime(t));
  //saveParameters();
  //DEBUGN("Time Set to:");
}