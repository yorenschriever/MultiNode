#include "../../../src/Time.h"

#include <chrono>

inline unsigned long Time::Millis()
{
    using namespace std::chrono;
    milliseconds ms = duration_cast< milliseconds >(
        system_clock::now().time_since_epoch()
    );
    return ms;
}