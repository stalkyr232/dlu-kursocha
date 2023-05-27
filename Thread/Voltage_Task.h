#ifndef VOLTAGETASK_H
#define VOLTAGETASK_H

#include "Thread.hpp"
#include "IMeasureParameter.h"

class Voltage_Task: public OsWrapper::Thread<128> 
{
public:

  Voltage_Task(IMeasureParameter& parameter); 
  void Execute() override; 
    
private: // ��������� �������, ������� ������ ������ �� ��������� (��� ������������� ��������� � Voltage_Task.cpp)
   IMeasureParameter& _parameter; 

    
};

#endif
