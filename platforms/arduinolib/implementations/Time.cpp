#include "Arduino.h"
#include "../../../src/Time.h"

inline unsigned long Time::Millis()
{
    return millis();
}