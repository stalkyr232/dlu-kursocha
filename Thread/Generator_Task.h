#ifndef GENERATORTASK_H
#define GENERATORTASK_H

#include "Thread.hpp"
#include "IMeasureParameter.h"
#include "IDataSource.h"

class GeneratorTask: public OsWrapper::Thread<512> 
{
 public:

  GeneratorTask(IDataSource& freq); 
  void Execute() override; 

private: // приватный атрибут, который хранит ссылку на интерфейс (его инициализация находится в TemperatureTask.cpp)
   IDataSource& _freq;
};

#endif
