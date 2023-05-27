#ifndef WATERCONSUMTION_H
#define WATERCONSUMTION_H

#include "IMeasureParameter.h" // дл€ IMeasureParameter
#include "IDataSource.h"       // дл€ IDataSource
#include <cstdint>             // дл€ int16_t s

class WaterConsumtion: public IMeasureParameter
{
public: 
  explicit WaterConsumtion(IDataSource& numberTopsFronts);  
  float Calculate() override;

  
private:
  // посто€нные из даташита на датчик
  static constexpr int16_t s = 60; // сек 
  static constexpr float R = 5.5;  // ќм
  IDataSource& _numberTopsFronts;
};

#endif