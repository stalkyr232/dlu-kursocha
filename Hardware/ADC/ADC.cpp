#include "ADC.h"
#include <cstdint>
#include "DMA.h"

ADC::ADC(): code(0)
 {
 
 }
 
float ADC::GetData()
{
  
  return static_cast<float>(code);
  
} 
void ADC::Start()
{
   DMA::ConfigureADC(reinterpret_cast<std::uint32_t>(&code)); // взяли адрес code и преобразовали в число
  // DMA::Start();
}