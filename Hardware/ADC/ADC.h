#ifndef ADC_H
#define ADC_H

#include <cstdint>
#include "IDataSource.h"  

class ADC: public IDataSource
{
public:
  ADC();
  float GetData() override;
  void Start();
  
private:
  std::uint32_t code;

};

#endif