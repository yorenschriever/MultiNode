/*
#ifndef UDPWRAPPERFACTORY_H
#define UDPWRAPPERFACTORY_H

#if defined(ESP8266) || defined(ESP31B) || defined(ESP32)
	#include "UDPWrapperESP32.h"
#endif

class UDPWrapperFactory {
  public:

	#if defined(ESP8266) || defined(ESP31B) || defined(ESP32)
	
		static UDPWrapper* getWrapper(){ return new UDPWrapperESP32(); }

	#else

		#error "no UDP wrapper implemented for this platform"

	#endif
};

#endif
*/