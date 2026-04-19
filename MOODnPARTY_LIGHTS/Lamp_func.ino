// Default parameters for Initiation after reset
const LampParameters paramsDefault = {
  0,               // magic number
  MAGENTA,         // main color
  BLACK,           // background
  BLUE,            // second color
  FX_MODE_STATIC,  //static
  3,               // color mode 1-MONO; 2-DUO 3-RGB
  1000,            // speed
  0b00110010,      // options: X00000000 - rev?; 0XXX0000 - FADE_RATE; 0000X000 - GAMMA; 00000XX0 - SIZE_OPTION
  128,             // med bri
  5,               // play mode: random all
  60,              // play time: 1 min
  LED_PIN,         // LED Pin
  LED_COUNT,       // LED Count
  LED_TYPE,        // LED Type
  0,               // additional flags
  192844800,       // TimeOn 18:00
  192861000,       // TimeOff 22:30
  192844800,       // WiFiOn 18:00
  10,              // WiFiOff 10 min
};



void runLEDs() {
  checkAutoPlay();
  // lamp.service();
  static unsigned long lastUpdate = 0;  //Throttle LED updates
  if (millis() - lastUpdate > 20) {     // 20 ms = 50 Hz
    lamp.service();
    lastUpdate = millis();
  }
}

// - - - - - - Lamp State - - - - - -
void setLampState(State s) {
  DEBUG2("Status was:", getNameLampState(getLampState()));
  lampState = s;
  DEBUG2N(" set:", getNameLampState(getLampState()));
}
State getLampState() {
  return lampState;
}

const char* const LAMP_STATE[] PROGMEM{
  "S_START_AP_ONLY",
  "S_START_AP_STA",
  "S_SWITCH_TO_STA",
  "S_RUNNING_AP",
  "S_RUNNING_AP_STA",
  "S_RUNNING_STA",
  "S_STOP_WIFI",
  "S_RUNNING_NOWIFI",
  "S_RESET",
  "S_ERROR",
  "S_MAX_VALUE"
};

const char* getNameLampState(State s) {
#ifdef DEBUGING
  if (s <= 9) {
    return LAMP_STATE[s];
  }
  return LAMP_STATE[STATE_MAX_VALUE];  // fallback
#else
  (void)(s);
  return "";
#endif
}


// - - - - - - D E L A Y - - - - - -
boolean Delay(int interval) {
  unsigned long prevMillis = millis();
  long currMillis = millis();
  //  updateBorder();
  do {
    currMillis = millis();
    runLEDs();
    if (lampState == STATE_START_AP_STA || lampState == STATE_RUNNING_AP || lampState == STATE_RUNNING_AP_STA) {
      runningAP();
    }
    delay(10);
    yield();
  } while (currMillis - prevMillis < interval);
  return false;
}
