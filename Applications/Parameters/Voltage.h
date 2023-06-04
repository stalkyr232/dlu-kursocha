#ifndef VOLTAGE_H
#define VOLTAGE_H

#include "IDataSource.h"       // ??? IDataSource

class Voltage: public IDataSource
{
public: 
  explicit Voltage(IDataSource& code): _code(code) 
{

} 
  float GetData() override
  {
    float voltage =  _code.GetData() * 3.3f / 4096.0f; // 
    return voltage;
  }

private:
   IDataSource& _code;
};

#endif