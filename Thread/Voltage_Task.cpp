#include "FlowTask.h"
#include <iostream> // подключение стандартной библиотеки С++
#include "tim3registers.hpp"         // библиотека для TIM3


// конструктор
FlowTask::FlowTask(IMeasureParameter& parameter): _parameter(parameter)
{
  
}

void FlowTask::Execute() 
{

  for(;;)
  {
   TIM3::CR1::CEN::Value1::Set();                              // включение счётчика
   volatile auto flowRare = _parameter.Calculate();
   std::cout << flowRare << std::endl;
   TIM3::CR1::CEN::Value0::Set();                              // выключение счётчика
   Sleep(1000ms); 
  }
}