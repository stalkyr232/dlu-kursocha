#ifndef WATERCONSUMTION_H
#define WATERCONSUMTION_H

#include "IMeasureParameter.h" // ��� IMeasureParameter
#include "IDataSource.h"       // ��� IDataSource
#include <cstdint>             // ��� int16_t s

class WaterConsumtion: public IMeasureParameter
{
public: 
  explicit WaterConsumtion(IDataSource& numberTopsFronts);  
  float Calculate() override;

  
private:
  // ���������� �� �������� �� ������
  static constexpr int16_t s = 60; // ��� 
  static constexpr float R = 5.5;  // ��
  IDataSource& _numberTopsFronts;
};

#endif