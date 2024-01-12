// Default parameters for Initiation after reset
const LampParameters paramsDefault = {
  0,              // magic number
  MAGENTA,        // main color
  BLACK,          // background
  BLUE,           // second color
  FX_MODE_STATIC, //static
  3,              // color mode 1-MONO; 2-DUO 3-RGB
  1000,           // speed
  0b00110010,     // options: X00000000 - rev?; 0XXX0000 - FADE_RATE; 0000X000 - GAMMA; 00000XX0 - SIZE_OPTION
  128,            // med bri
  5,              // play mode: random all
  60,             // play time: 1 min
  0               // additional flags
};



void runLEDs(){
  checkAutoPlay();
  lamp.service();
}

// - - - - - - Lamp State - - - - - - 
void setLampState(State s) {
  lampState = s;
  DEBUG2N("Status set:", getLampStateString(s));
}
State getLampState() {
  return lampState;
}

const char * const LAMP_STATE[] PROGMEM
{
  "STATE_START_AP_ONLY",
  "STATE_START_AP_STA",
  "STATE_SWITCH_TO_STA",
  "STATE_RUNNING_AP",
  "STATE_RUNNING_AP_STA",
  "STATE_RUNNING_STA",
  "STATE_RESET",
  "STATE_ERROR"
};

String getLampStateString(State s){
  if(s <= 7) return LAMP_STATE[s];
  return LAMP_STATE[STATE_MAX_VALUE];
}

// - - - - - - D E L A Y - - - - - -
boolean Delay(int interval) {
  unsigned long prevMillis = millis();
  long currMillis = millis();
  //  updateBorder();
  do {
    currMillis = millis();
    runLEDs();
    yield();
  } while (currMillis - prevMillis < interval);
  return false;
}
