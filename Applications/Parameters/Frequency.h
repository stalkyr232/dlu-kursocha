#ifndef FREQUENSY_H
#define FREQUENSY_H

#include "IDataSource.h"       // ��� IDataSource

class Frequency: public IDataSource
{
public: 
  explicit Frequency(IDataSource& voltge): _voltge(voltge) 
 {

 }
 
 float GetData() override
  {
    float Ufilter = _voltge.GetData();
    float ARR = 0.0f;
    if (Ufilter < 0.9f) 
    {
      ARR = 0;
    }
    else
    {
      float F = Af + Bf * Ufilter; // ������� � ������
      ARR = fSistem / F;
    }
    return ARR;
  }

private:
  float fSistem = 16000000; // ������� ���� = 16���
  // ������������
  float Af = - 12.5f;
  float Bf = 22.5f;

  IDataSource& _voltge;
};

#endif