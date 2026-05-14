
uint32_t storeColors[3];  // = {BLUE, BLACK, RED};

void applyColors() {
  setColorMode(param.COLORMODE);
  lampSetColors(storeColors);
}

void setColorMode(uint8_t colorMode) {
  if (colorMode == COLORMODE_MONO) {
    storeColors[0] = rgb_to_rgbw(param.COLOR0);
    storeColors[1] = rgb_to_rgbw(param.COLOR1);
    storeColors[2] = storeColors[1];
  } else if (colorMode == COLORMODE_DUO) {
    storeColors[0] = rgb_to_rgbw(param.COLOR0);
    storeColors[1] = rgb_to_rgbw(param.COLOR1);
    storeColors[2] = rgb_to_rgbw(param.COLOR2);
  } else if (colorMode == COLORMODE_RGB) {
    storeColors[0] = rgb_to_rgbw(param.COLOR1);
    storeColors[1] = storeColors[0];
    storeColors[2] = storeColors[0];
    // } else {
    // future modes?
  }
  lampSetColors(storeColors);
}

void checkAutoPlay() {
  unsigned long now = millis();

  if (now < auto_last_change) auto_last_change = now;
  if (param.PLAYMODE > 0 && (now - auto_last_change > (param.PLAYTIME * 1000))) {  // cycle effect mode every 'param.PLAYTIME' seconds
    uint8_t num_modes;
    uint8_t prevMode = lamp.getMode();
    switch (param.PLAYMODE) {
      case P_ALL:
        playMode++;
        num_modes = sizeof(monoModes) + sizeof(duoModes) + sizeof(rgbModes);
        playMode %= num_modes;
        if (playMode > (sizeof(monoModes) + sizeof(duoModes))) {  // random All is RGBMode
          lampSetMode(rgbModes[playMode - (sizeof(monoModes) + sizeof(duoModes))]);
          setColorMode(COLORMODE_RGB);
        } else if (playMode > sizeof(monoModes)) {  // random All is DuoMode
          lampSetMode(duoModes[playMode - sizeof(monoModes)]);
          setColorMode(COLORMODE_DUO);
        } else {  // random All is MonoMode
          lampSetMode(monoModes[playMode]);
          setColorMode(COLORMODE_MONO);
        }
        DEBUG2("AllPlayMode: #", playMode);
        DEBUG2N(" - ", lamp.getModeName(lamp.getMode()));
        break;

      case P_MONO:
        num_modes = sizeof(monoModes);
        lampSetMode(monoModes[0]);
        for (uint8_t i = 0; i < num_modes - 1; i++) {
          if (prevMode == monoModes[i]) {
            lampSetMode(monoModes[i + 1]);
          }
        }
        setColorMode(COLORMODE_MONO);
        DEBUG2N("Auto MONOMode: ", lamp.getModeName(lamp.getMode()));
        break;

      case P_DUO:
        num_modes = sizeof(duoModes);
        lampSetMode(duoModes[0]);
        for (uint8_t i = 0; i < num_modes - 1; i++) {
          if (prevMode == duoModes[i]) {
            lampSetMode(duoModes[i + 1]);
          }
        }
        setColorMode(COLORMODE_DUO);
        DEBUG2N("Auto DUOMode: ", lamp.getModeName(lamp.getMode()));
        break;

      case P_RGB:
        num_modes = sizeof(rgbModes);
        lampSetMode(rgbModes[0]);
        for (uint8_t i = 0; i < num_modes - 1; i++) {
          if (prevMode == rgbModes[i]) {
            lampSetMode(rgbModes[i + 1]);
          }
        }
        setColorMode(COLORMODE_RGB);
        DEBUG2N("Auto RGBMode: ", lamp.getModeName(lamp.getMode()));
        break;

      case P_ALL_RANDOM:
        num_modes = sizeof(monoModes) + sizeof(duoModes) + sizeof(rgbModes);
        playMode = random(num_modes);  //lamp.random8(num_modes);
        DEBUG2("RandPlayMode: #", playMode);
        //        DEBUG2("ms: #", sizeof(monoModes)); DEBUG2(" | ds: #", sizeof(monoModes)); DEBUG2(" | rs: #", sizeof(rgbModes)); DEBUG2N(" | Ttl: #", num_modes);
        num_modes = sizeof(monoModes) + sizeof(duoModes) + sizeof(rgbModes);
        if (playMode > (sizeof(monoModes) + sizeof(duoModes))) {  // random All is RGBMode
          lampSetMode(rgbModes[playMode - (sizeof(monoModes) + sizeof(duoModes))]);
          DEBUG2(" RGB: #", playMode - (sizeof(monoModes) + sizeof(duoModes)));
          DEBUG2N(" - mode: ", lamp.getModeName(lamp.getMode()));
          setColorMode(COLORMODE_RGB);
        } else if (playMode > sizeof(monoModes)) {  // random All is DuoMode
          lampSetMode(duoModes[playMode - sizeof(monoModes)]);
          setColorMode(COLORMODE_DUO);
          DEBUG2(" DUO: #", playMode - sizeof(monoModes));
          DEBUG2N(" - mode: ", lamp.getModeName(lamp.getMode()));
        } else {  // random All is MonoMode
          lampSetMode(monoModes[playMode]);
          setColorMode(COLORMODE_MONO);
          DEBUG2(" MONO: #", playMode);
          DEBUG2N(" - mode: ", lamp.getModeName(lamp.getMode()));
        }
        break;

      case P_MONO_RANDOM:
        num_modes = sizeof(monoModes);
        lampSetMode(monoModes[lamp.random8(num_modes)]);
        setColorMode(COLORMODE_MONO);
        DEBUG2N("Auto R MONOMode: ", lamp.getModeName(lamp.getMode()));
        break;

      case P_DUO_RANDOM:
        num_modes = sizeof(duoModes);
        lampSetMode(duoModes[lamp.random8(num_modes)]);
        setColorMode(COLORMODE_DUO);
        DEBUG2N("Auto R DUOMode: ", lamp.getModeName(lamp.getMode()));
        break;

      case P_RGB_RANDOM:
        num_modes = sizeof(rgbModes);
        lampSetMode(rgbModes[lamp.random8(num_modes)]);
        setColorMode(COLORMODE_RGB);
        DEBUG2N("Auto R RGBMode: ", lamp.getModeName(lamp.getMode()));
        break;

        //      default:
    }
    auto_last_change = now;
  }
}

uint32_t rgb_to_rgbw(uint32_t color) {
  uint8_t r = (color >> 16) & 0xFF;
  uint8_t g = (color >> 8) & 0xFF;
  uint8_t b = color & 0xFF;

  uint8_t w = r;
  if (g < w) w = g;
  if (b < w) w = b;

  if (isRGBW(param.LEDTYPE)) {
    r -= w;
    g -= w;
    b -= w;
  }

  return ((uint32_t)w << 24) | ((uint32_t)r << 16) | ((uint32_t)g << 8) | (uint32_t)b;
}

inline bool isRGBW(uint8_t value) {
  switch (value) {
    case 6:
    case 9:
    case 82:
    case 161:
    case 88:
    case 164:
      return false;  // belongs to group ONE
    default:
      return true;  // not in group ONE
  }
}