#ifndef VALUE_H
#define VALUE_H

#include <string>

enum VALUETYPE { ValueNull, ValueBoolean, ValueIndex, ValueNumber, ValueString, ValueColour };

class Value {

  public:
    Value(); 
    Value(const Value& v);
    Value(int val);
    Value(float val);
    Value(std::string val);
    Value(char* val);
    Value(char* val, int len);
    Value(bool val);  
    ~Value();

    void SetValue(int val);
    void SetValue(float val);
    void SetValue(std::string val);
    void SetValue(char* val);
    void SetValue(char* val, int len);
    void SetValue(bool val);

    bool AsBoolean();
    int AsIndex();
    float AsNumber();
    std::string AsString();

  private:
    void store(void* ptr, unsigned int len);
    void* retrieve();

    void* dataptr=0;
    VALUETYPE type;
    int len=0;
};

#endif