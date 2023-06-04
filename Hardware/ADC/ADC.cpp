#include "ADC.h"
#include <cstdint>
#include "DMA.h"

// кнструктор с начальным значением code=0
ADC::ADC(): code(0)
{
 
}
 
// Метод, который возвращает значение АЦП
float ADC::GetData()
{
  return static_cast<float>(code);
} 

void ADC::Start()
{
   DMA::ConfigureADC(reinterpret_cast<std::uint32_t>(&code)); // взяли адрес code и преобразовали в число
}