#include "Generator_Task.h"
#include <iostream> // подключение стандартной библиотеки С++
#include "tim3registers.hpp"         // библиотека для TIM3


// конструктор
GeneratorTask::GeneratorTask(IDataSource& freq): _freq(freq)
{

}
// Задача, которая записывает новое ARR и половину от него CCR, другими словами выдаёт сигнал
void GeneratorTask::Execute() 
{
  for(;;)
  {
   volatile auto  ARR = _freq.GetData();
   if (ARR == 0)
   {
     TIM3::CCER::CC3E::Value0::Set();
   }
   else
   {
    TIM3::ARR::Write(static_cast<int32_t>(ARR));
    TIM3::CCR3::Write(static_cast<int32_t>(ARR/2U));
    TIM3::CCER::CC3E::Value1::Set();
   }

   std::cout << ARR << std::endl;
   Sleep(50ms); 
  }
}