#include "rccregisters.hpp"                       // Для модуля тактирования RCC
//#include "dma1registers.hpp"                       // Для подключения ДМА
//#include "dma2registers.hpp"                      // Для подключения ДМА
#include "adc1registers.hpp"         // библиотека для АЦП
#include "adccommonregisters.hpp"
#include "tim3registers.hpp"         // библиотека для TIM3

#include "nvicregisters.hpp"                      // для объявления глобальных прерываний
#include "interrupthandler.hpp"                   // библиотека векторов прерываний
//#include "StartUp.cpp"                            // для прерываний  
//----------------------------Стандартные библиотеки С++------------------------
#include <iostream> // подключение стандартной библиотеки С++
 

//----------------------------Порты---------------------------------------------
#include "gpioaregisters.hpp"       // регистр для порта a
#include "gpiobregisters.hpp"       // регистр для порта b
//=================================Классы==================================
//#include "Voltage.h" 
//#include "IMeasureParameter.h" 
#include "ADC.h"
#include "IDataSource.h"


 //================================-ОСРВ========================================
#include "rtos.hpp"

std::uint32_t SystemCoreClock = 16'000'000U;    // тактирование внутреннего генератора, 1 такт = 8 000 000 Гц = 1 сек
std::uint32_t OneMillisecondRation = 1000U; // коэффициент деления
std::uint32_t Timer3Prescaller = SystemCoreClock / OneMillisecondRation; // 1 млсек


//----------------------------Создание объектов---------------------------------  
  ADC adc;
 // Resistor resistor(static_cast<IDataSource&>(adc));
 // Temperature temperature(static_cast<IDataSource&>(resistor)); // создание обекта для расчёта температуры
 // TemperatureTask temperatureTask(temperature);                 // создание задачи по измерению температуры
  
 
 
int main()
{
 
  RCC::AHB1ENR::GPIOAEN::Enable::Set();         // Подать тактирование на порт A
  RCC::AHB1ENR::GPIOBEN::Enable::Set();         // Подать тактирование на порт B
  
  //------------------------------------АЦП-------------------------------------
  GPIOA::MODER::MODER0::Analog::Set();
  RCC::APB2ENR::ADC1EN::Enable::Set();       // подали тактирование на АЦП
  RCC::AHB1ENR::DMA2EN::Enable::Set();       // подали тактирование на ДМА
  adc.Start();

  ADC1::CR1::RES::Bits12::Set();             // разрядность АЦП   
  ADC1::CR1::SCAN::Enable::Set();            // режим сканирования

  ADC1::CR2::CONT::ContinuousConversion::Set();
  ADC1::CR2::DMA::Enable::Set();
  ADC1::CR2::DDS::DMARequest::Set();
  ADC1::CR2::ADON::Enable::Set();
  ADC1::CR2::SWSTART::On::Set();
  
  
  //---------------------------Создание задач-----------------------------------
  //OsWrapper::Rtos::CreateThread(temperatureTask, "TemperatureTask"); 
 // OsWrapper::Rtos::CreateThread(flowTask, "flowTask"); 
  //OsWrapper::Rtos::Start();
  
  for(;;)  
  { 
    
  //  float temperatureWithADC = temperature.Calculate();
    //float ConsumptionWithFlowmeter = waterConsumption.Calculate();
    
  }
  
  

  
}
