#ifndef FILTER_H
#define FILTER_H

#include "IDataSource.h"       // ��� IDataSource
#include <cmath>

class Filter: public IDataSource
{
public:
  explicit Filter(IDataSource& voltage): _voltage(voltage) 
 {
   
 } 
  
  float GetData() // ������� ����� � �������� � ���� �������� ����������
  {
   // float U = _voltage.GetData();
    //std::cout << U << std::endl;
    float FilteredValue = OldValue + ( _voltage.GetData() - OldValue) * tau; // ������� ��� ����������
    OldValue = FilteredValue;
    return FilteredValue;
  }
  
  
private:
  IDataSource& _voltage;
  float OldValue = 0.0f; // ��������� ����������
  static constexpr float dt = 100.0f;
  static constexpr float RC = 100.0f;
  inline static const float tau = 1.0f - exp(-dt/RC);
  
};
#endif