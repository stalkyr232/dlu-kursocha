#include "rccregisters.hpp"                       // Для модуля тактирования RCC
#include "dma1registers.hpp"                       // Для подключения ДМА
#include "dma2registers.hpp"                      // Для подключения ДМА

#include "nvicregisters.hpp"                      // для объявления глобальных прерываний
#include "interrupthandler.hpp"                   // библиотека векторов прерываний
//#include "StartUp.cpp"                            // для прерываний  
//----------------------------Стандартные библиотеки С++------------------------
#include <iostream> // подключение стандартной библиотеки С++
 

//----------------------------Порты---------------------------------------------
#include "gpioaregisters.hpp"       // регистр для порта a
#include "gpiobregisters.hpp"       // регистр для порта b
//=================================Температура==================================
#include "Temperature.h" 
#include "IMeasureParameter.h" 
#include "adc1registers.hpp"         // библиотека для АЦП
#include "Resistor.h"               // для класса Resistor 
#include "ADC.h"
#include "adccommonregisters.hpp"
//=================================Расход=======================================
#include "Front.h"
#include "Flowmeter.h"   
#include "WaterConsumtion.h"  
#include "tim3registers.hpp"         // библиотека для TIM3
//=================================ШИМ==========================================
#include "CurrentControler.h"   
#include "PWM.h"  
//=================================ModBus=======================================
#include "Modbus.h"
#include "IDataSource.h"
 //================================-ОСРВ========================================
#include "rtos.hpp"
#include "TemperatureTask.h" 
//#include "DataTransferTask.h"   
//#include "CurrentPowerRegulationTask.h"   
#include "FlowTask.h"   

std::uint32_t SystemCoreClock = 16'000'000U;    // тактирование внутреннего генератора, 1 такт = 8 000 000 Гц = 1 сек
std::uint32_t OneMillisecondRation = 1000U; // коэффициент деления
std::uint32_t Timer3Prescaller = SystemCoreClock / OneMillisecondRation; // 1 млсек


//----------------------------Создание объектов---------------------------------  
  ADC adc;
  Resistor resistor(static_cast<IDataSource&>(adc));
  Temperature temperature(static_cast<IDataSource&>(resistor)); // создание обекта для расчёта температуры
  TemperatureTask temperatureTask(temperature);                 // создание задачи по измерению температуры
  
  Flowmeter flow;
  WaterConsumtion waterConsumption(static_cast<IDataSource&>(flow));
  FlowTask flowTask(waterConsumption);
//------------------------------------------------------------------------------  
 

//------------------------------------------------------------------------------    
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
  
  //-----------------------------Таймер в режиме захвата------------------------
  GPIOB::MODER::MODER4::Alternate::Set();
  RCC::APB1RSTR::TIM3RST::Reset::Set();   // сброс таймера
  RCC::APB1ENR::TIM3EN::Enable::Set();       // подали тактирование на таймер TIM3
  RCC::AHB1ENR::DMA1EN::Enable::Set();       // подали тактирование на ДМА
  flow.Start();

  TIM3::CCMR1_Input::CC1S::Value1::Set();                 // определяет направление канала
  TIM3::CCMR1_Input::IC1F::Value1::Set();                 // фильтрация входа
  
  // захват по переднему фронту
  TIM3::CCER::CC1P::Value0::Set();
  TIM3::CCER::CC1NP::Value0::Set();
  
  TIM3::CCER::CC1E::Value1::Set();                          // захват включён
  
  TIM3::ARR::Write(10);// 10 милисекунд                  // Максимальное значние таймера до которого он считает
  TIM3::CNT::Write(0);
  TIM3::SR::UIF::NoInterruptPending::Set();             // скинули флаг
  TIM3::CR1::CEN::Value1::Set();                        // включение счётчика
  TIM3::PSC::Write(Timer3Prescaller);                   // делитель частоты
 
  TIM3::DIER::CC1IE::Value1::Set();                         // прерывание разрешено
  TIM3::DIER::CC1DE::Value1::Set();                         // ДМА включён
  NVIC::ISER1::Write(1U << 29U);  // разрешить глобальное прерывание, где 29 - позиция таймера TIM3, ISER1 хранит только 32 значения, затем идёт ISER2, который хранит следующие 32 значения и т.д.
  
  //---------------------------Создание задач-----------------------------------
  OsWrapper::Rtos::CreateThread(temperatureTask, "TemperatureTask"); 
  OsWrapper::Rtos::CreateThread(flowTask, "flowTask"); 
  OsWrapper::Rtos::Start();
  
  for(;;)  
  { 
    
    float temperatureWithADC = temperature.Calculate();
    float ConsumptionWithFlowmeter = waterConsumption.Calculate();
    
  }
  
  

  
}
