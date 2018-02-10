#ifndef ICOMMUNICATION_H
#define ICOMMUNICATION_H

#include <string>
#include <functional>

typedef std::function<void (uint8_t num, uint8_t * payload, size_t length)> MessageEvent;

class ICommunication
{
    public:

        virtual void begin()=0;
        virtual void onMessage(MessageEvent msgevent)=0;

        virtual bool sendMessage(std::string txt)=0;
        virtual bool sendMessage(const char* msg, int len)=0;

        //virtual void disconnect(uint8_t id);
        virtual void loop()=0;

};

#endif