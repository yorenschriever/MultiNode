#include "Value.h"

Value::Value(const Value& v)
{
  dataptr = malloc(v.len);
  memcpy(dataptr, v.dataptr,v.len);
  len=v.len;
  type=v.type;
}

Value::Value()
{
  type=ValueNull;
  dataptr=0;
}

Value::Value(bool value)
{
  SetValue(value);
}

void Value::SetValue(bool val){  
  type = ValueBoolean;
  store((void*)&val,sizeof(val)); 
}

Value::Value(int val){  
  SetValue(val);
}

void Value::SetValue(int val){  
  type = ValueIndex;
  store((void*)&val,sizeof(val)); 
}

Value::Value(float val){ 
  SetValue(val);
}

void Value::SetValue(float val){ 
  type = ValueNumber; 
  store((void*)&val, sizeof(val)); 
}

void Value::SetValue(std::string val){  
  type=ValueString;
  store((void*)val.c_str(),val.length()+1); 
}

Value::Value(std::string val){  
  SetValue(val);
}

Value::Value(char* val, int len){  
  SetValue(val,len);
}

void Value::SetValue(char* val, int len)
{
  type=ValueString;
  store((void*)val,len+1);   
}

Value::Value(char* val){  
  SetValue(val);
}

void Value::SetValue(char* val)
{
  type=ValueString;
  store((void*)val,strlen(val)+1);   
}

Value::~Value()
{
  if (dataptr!=0)
    free(dataptr);
}

void Value::store(void* val, unsigned int len)
{ 
  dataptr = realloc(dataptr, len);
  memcpy(dataptr,val, len);
  this->len=len;
}


std::string Value::AsString()
{
  if (type==ValueNull)
    return "Null";
  if (type==ValueBoolean)
    return *((bool*) dataptr) ? "True":"False";
  if (type==ValueString)
    return std::string((char*) dataptr);
  else if (type==ValueIndex)
    return std::to_string(*((int*) dataptr));
  else if (type==ValueNumber)
    return std::to_string(*((float*) dataptr));
  return "";
}

bool Value::AsBoolean()
{
  if (type==ValueNull)
    return false;
  if (type==ValueBoolean)
    return *((bool*) dataptr);
  if (type==ValueIndex)
    return *((int*) dataptr);
  else if (type==ValueNumber)
    return *((float*) dataptr) != 0;
  else if (type==ValueString)
    return (!strcmp("1", (char*) dataptr) || !strcmp("True",(char*) dataptr)  || !strcmp("true",(char*) dataptr)); 
  return false;
}

int Value::AsIndex()
{
  if (type==ValueNull)
    return 0;
  if (type==ValueBoolean)
    return *((bool*) dataptr);
  if (type==ValueIndex)
    return *((int*) dataptr);
  else if (type==ValueNumber)
    return *((float*) dataptr);
  else if (type==ValueString)
    return atoi((const char*) dataptr);
  return 0;
}

float Value::AsNumber()
{
  if (type==ValueNull)
    return 0;
  if (type==ValueBoolean)
    return *((bool*) dataptr);
  if (type==ValueIndex)
    return *((int*) dataptr);
  else if (type==ValueNumber)
    return *((float*) dataptr);
  else if (type==ValueString)
    return atof((const char*) dataptr);
  return 0;
}
