#ifndef TEMPERATURE_H
#define TEMPERATURE_H

#include "IMeasureParameter.h" // для IMeasureParameter
#include "IDataSource.h"       // для IDataSource

class Temperature: public IMeasureParameter
{
public: 
  explicit Temperature(IDataSource& resistor);  
  float Calculate() override;

  
private:
  // Градуировочные характеристики
  static constexpr float At = -246.584F;  
  static constexpr float Bt = 2.37383F;
  static constexpr float Ct = 0.000921853F;  
  IDataSource& _resistor;
};

#endif