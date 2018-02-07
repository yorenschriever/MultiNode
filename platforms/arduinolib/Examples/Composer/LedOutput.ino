
const float gammaValue = 2.1;
uint8_t gammaTable[256];

strand_t STRANDS[] = { // Avoid using any of the strapping pins on the ESP32
  {.rmtChannel = 0, .gpioNum = 16, .ledType = LED_WS2813_V2, .brightLimit = 255, .numPixels = 256,  .pixels = nullptr, ._stateVars = nullptr},
};

int STRANDCNT = sizeof(STRANDS)/sizeof(STRANDS[0]);

void LedOutputSetup()
{
  gpioSetup(16, OUTPUT, LOW);

  if (digitalLeds_initStrands(STRANDS, STRANDCNT)) {
    Serial.println("Init FAILURE: halting");
    while (true) {};
  }
  Serial.println("Init leds complete");

  for (int i=0;i<256;i++){
    gammaTable[i] = pow((float)i/255.0,gammaValue)*255;
  }
}

void UpdateLeds()
{
  strand_t* pStrand = &STRANDS[0];
  for (int i=0;i<256; i++){ 
    pStrand->pixels[i] = getColorAt(i);
  }
  digitalLeds_updatePixels(pStrand);
}



void gpioSetup(int gpioNum, int gpioMode, int gpioVal) {
    pinMode (gpioNum, gpioMode);
    digitalWrite (gpioNum, gpioVal);
}

pixelColor_t getColorAt(int i)
{
  Position p = getLedPos(i);
  return mkColor( topNode->GetStackedColor(p) );
}

pixelColor_t mkColor(RGBA cin)
{
  return pixelFromRGBW(
    gammaTable[(int)(cin.r * cin.a)],
    gammaTable[(int)(cin.g * cin.a)],
    gammaTable[(int)(cin.b * cin.a)],
    0);
}
