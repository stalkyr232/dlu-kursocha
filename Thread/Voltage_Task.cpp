#include "FlowTask.h"
#include <iostream> // ����������� ����������� ���������� �++
#include "tim3registers.hpp"         // ���������� ��� TIM3


// �����������
FlowTask::FlowTask(IMeasureParameter& parameter): _parameter(parameter)
{
  
}

void FlowTask::Execute() 
{

  for(;;)
  {
   TIM3::CR1::CEN::Value1::Set();                              // ��������� ��������
   volatile auto flowRare = _parameter.Calculate();
   std::cout << flowRare << std::endl;
   TIM3::CR1::CEN::Value0::Set();                              // ���������� ��������
   Sleep(1000ms); 
  }
}