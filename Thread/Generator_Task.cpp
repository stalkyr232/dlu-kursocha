#include "TemperatureTask.h"
#include <iostream> // подключение стандартной библиотеки С++
// конструктор
TemperatureTask::TemperatureTask(IMeasureParameter& parameter): _parameter(parameter)
{
  
}

void TemperatureTask::Execute() 
{

  for(;;)
  {
   volatile auto temperature = _parameter.Calculate();
   std::cout << temperature << std::endl;
   Sleep(1000ms); 
  }
}