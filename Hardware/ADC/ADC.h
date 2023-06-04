#ifndef ADC_H
#define ADC_H

#include <cstdint>
#include "IDataSource.h"

// Класс, который получает значение с АЦП
class ADC: public IDataSource
{
public:
  ADC();
  float GetData() override;
  void Start();

private:
    volatile const std::uint32_t code;

};

#endif