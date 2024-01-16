#define LED_PIN 2 // D4 on 
#define LED_COUNT 60

#define MNP_TITLE "MOOD'n'PARTY LIGHTS"
#define MNP_HEADER "<h1>MOOD'n'PARTY LIGHTS</h1>" //<h4> Some more text in header </h4>
#define MNP_ABOUTCONTENT "<h2>&#x1F7E1;&#x1F7E3;&#x1F7E4; MOOD'n'PARTY &#x1F534;&#x1F7E2;&#x1F535;<br> \
  LIGHTS</h2><p>Let's talk about!</p><p>Thank you for using my lovely Mood & Party Lights! &#x1F525 </p> \
  <p>PM Me and Follow Me on IG: @<a rel='nofollow me' href='https://instagram.com/vasylyudin/'>VasylYudin</a></p>"
#define MNP_FOOTER "Vasyl Yudin 2023-2024"

#if defined(WS2812FX_MNP_EDITION_h)
const uint8_t monoModes[] = {
  FX_MODE_STATIC,
  FX_MODE_BREATH,
  FX_MODE_SCAN,
  FX_MODE_MOOD_SWING,
  FX_MODE_THEATER_CHASE,
  FX_MODE_WAVES,
  FX_MODE_TWINKLE_FADE,
  FX_MODE_SPARKLE,
  FX_MODE_LARSON_SCANNER,
  FX_MODE_FIREWORKS,
  FX_MODE_XMAS_TWINKLE,
  FX_MODE_RAIN,
  FX_MODE_DISSOLVE,
  FX_MODE_COMETS,
  FX_MODE_POPCORN,
  FX_MODE_FIREFLY,
  FX_MODE_OCEAN,
  FX_MODE_FIRE2012,
  FX_MODE_ORBITA,
  FX_MODE_PARTYSKY,
  FX_MODE_DISCO,
  FX_MODE_METEOR,
  FX_MODE_FLYING_SPIRIT
};
const uint8_t duoModes[] =  {
  FX_MODE_STATIC,
  FX_MODE_MOOD_CLICK,
  FX_MODE_BREATH,
  FX_MODE_SCAN,
  FX_MODE_DUAL_SCAN,
  FX_MODE_MOOD_SWING,
  FX_MODE_WAVES,
  FX_MODE_TWINKLE_FADE,
  FX_MODE_SPARKLE,
  FX_MODE_RUNNING_COLOR,
  FX_MODE_LARSON_SCANNER,
  FX_MODE_FIREWORKS,
  FX_MODE_XMAS_TWINKLE,
  FX_MODE_RAIN,
  FX_MODE_DISSOLVE,
  FX_MODE_DUAL_LARSON,
  FX_MODE_COMETS,
  FX_MODE_POPCORN,
  FX_MODE_PARTYSKY,
  FX_MODE_DISCO,
  FX_MODE_METEOR,
  FX_MODE_FLYING_SPIRIT
};
const uint8_t rgbModes[] =  {
  FX_MODE_STATIC,
  FX_MODE_MOOD_CLICK,  
  FX_MODE_MOOD_TRAIN,
  FX_MODE_MOOD_SHIFT,
  FX_MODE_MOOD_FLOW,
  FX_MODE_XMAS_GLANCE,
  FX_MODE_XMAS_TICK,
  FX_MODE_XMAS_TWINKLE,
  FX_MODE_XMAS_GLITTER,
  FX_MODE_TWINKLE_FADE,
  FX_MODE_SCAN,
  FX_MODE_DUAL_SCAN,
  FX_MODE_MOOD_SWING,
  FX_MODE_THEATER_CHASE,
  FX_MODE_WAVES,
  FX_MODE_SPARKLE,
  FX_MODE_LARSON_SCANNER,
  FX_MODE_DUAL_LARSON,
  FX_MODE_FIREWORKS,
  FX_MODE_RAIN,
  FX_MODE_DISSOLVE,
  FX_MODE_RUNNING_TAILS,
  FX_MODE_COMETS,
  FX_MODE_POPCORN,
  FX_MODE_FIREFLY,
  FX_MODE_FIRE2012,
  FX_MODE_ORBITA,
  FX_MODE_PARTYSKY,
  FX_MODE_OCEAN,
  FX_MODE_MACHINA,
  FX_MODE_DISCO,
  FX_MODE_METEOR,
  FX_MODE_COLORFALL,
  FX_MODE_SPLIT,
  FX_MODE_FLYING_SPIRIT
};
const uint8_t specModes[] =  {
  FX_MODE_STROBE,
  FX_MODE_MULTI_STROBE,
  FX_MODE_PARTY_STROBE,
  FX_MODE_ICU, 
  FX_MODE_RAINBOW_FIREWORKS,
  FX_MODE_FILLER_UP,
  FX_MODE_VU_METER,
  FX_MODE_VU_METER_PEAK,
  FX_MODE_HEARTBEAT,
  FX_MODE_FIREFLY,
  FX_MODE_FIRE2012,
  FX_MODE_OCEAN,
  FX_MODE_ORBITA,
  FX_MODE_MACHINA
};

#else
#pragma message("Designed for WS2812FX_MNP_EDITION lib")
const uint8_t monoModes[] = {0, 1, 2, 3, 4, 5, 6, 13, 14, 15, 16, 18, 19, 21, 23, 24, 25, 26, 28, 30, 31, 34, 36, 37, 40, 43, 44, 48, 49, 50, 65, 66, 68, 70, 71 };
const uint8_t duoModes[] =  {45, 53, 54, 55, 56, 57, 64 };
const uint8_t rgbModes[] =  {7, 8, 9, 10, 11, 12, 17, 20, 22, 27, 29, 32, 33, 35, 38, 39, 42, 46, 56, 60, 62, 63, 67, 70 };
const uint8_t specModes[] =  {41, 47, 51, 52, 58, 59, 61,  };
#endif




// - = No  user adjustment beyond this point = -

#define MNP_LIGHTS_VERSION_VAL(major, minor, patch) ((major << 16) | (minor << 8) | (patch))
#define MNP_LIGHTS_VERSION MNP_LIGHTS_VERSION_VAL(0, 1, 0)

#define MNPL_VERSION_VAL(major, minor, patch) ((major << 16) | (minor << 8) | (patch))
#define MNPL_VERSION MNPL_VERSION_VAL(0, 1, 0)

#define DEBUGING 1 // Switch debug output on and off by 1 or 0
#if DEBUGING
#define DEBUG(s)     { Serial.print(F(s)); }
#define DEBUG2(s,v)  { Serial.print(F(s)); Serial.print(v); }
#define DEBUG2X(s,v) { Serial.print(F(s)); Serial.print(v, HEX); }
#define DEBUGN(s)     { Serial.println(F(s)); }
#define DEBUG2N(s,v)  { Serial.print(F(s)); Serial.println(v); }
#define DEBUG2XN(s,v) { Serial.print(F(s)); Serial.println(v, HEX); }
#else
#define DEBUG(s)
#define DEBUG2(s,v)
#define DEBUG2X(s,v)
#define DEBUGN(s)
#define DEBUG2N(s,v)
#define DEBUG2XN(s,v)
#endif

enum State {
  STATE_START_AP_ONLY,
  STATE_START_AP_STA,
  STATE_SWITCH_TO_STA,
  STATE_RUNNING_AP,
  STATE_RUNNING_AP_STA,
  STATE_RUNNING_STA,
  STATE_RESET,
  STATE_ERROR,
  STATE_MAX_VALUE
} lampState;

struct WiFiData {
  char wifiSSID[34];
  char wifiPass[64];
} wifidata;

typedef enum {
  P_NONE,
  P_ALL,
  P_MONO,
  P_DUO,
  P_RGB,
  P_ALL_RANDOM,
  P_MONO_RANDOM,
  P_DUO_RANDOM,
  P_RGB_RANDOM,
} MODES;

struct LampParameters {
  uint32_t  MAGIC;
  uint32_t  COLOR0;
  uint32_t  COLOR1;
  uint32_t  COLOR2;
  uint8_t   MODE;
  uint8_t   COLORMODE;
  uint16_t  SPEED;
  uint8_t   OPTION;
  uint8_t   BRI;
  uint8_t   PLAYMODE;
  uint16_t  PLAYTIME;
  uint8_t   FLAGS;
} param;

#define COLORMODE_MONO 1
#define COLORMODE_DUO 2
#define COLORMODE_RGB 3
#define COLORMODE_PALETTE 4 // todo

extern const char index_html[];
extern const char main_js[];
extern const char style_css[];

// QUICKFIX...See https://github.com/esp8266/Arduino/issues/263
#define min(a,b) ((a)<(b)?(a):(b))
#define max(a,b) ((a)>(b)?(a):(b))

boolean auto_cycle = false;
uint8_t playMode = 0;
unsigned long auto_last_change = 0;
