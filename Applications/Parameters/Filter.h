#ifndef FILTER_H
#define FILTER_H

#include "IDataSource.h"       // дл€ IDataSource
#include <cmath>

class Filter: public IDataSource
{
public:
  explicit Filter(IDataSource& voltage): _voltage(voltage) 
 {
   
 } 
  
  float GetData() // —оздаем класс и передаем в него значение напр€жени€
  {
   // float U = _voltage.GetData();
    //std::cout << U << std::endl;
    float FilteredValue = OldValue + ( _voltage.GetData() - OldValue) * tau; // ‘ормула дл€ фильтрации
    OldValue = FilteredValue;
    return FilteredValue;
  }
  
  
private:
  IDataSource& _voltage;
  float OldValue = 0.0f; // ќбъ€вл€ем переменную
  static constexpr float dt = 100.0f;
  static constexpr float RC = 100.0f;
  inline static const float tau = 1.0f - exp(-dt/RC);
  
};
#endif