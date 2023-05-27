#include "rccregisters.hpp"                       // ��� ������ ������������ RCC
#include "dma1registers.hpp"                       // ��� ����������� ���
#include "dma2registers.hpp"                      // ��� ����������� ���

#include "nvicregisters.hpp"                      // ��� ���������� ���������� ����������
#include "interrupthandler.hpp"                   // ���������� �������� ����������
//#include "StartUp.cpp"                            // ��� ����������  
//----------------------------����������� ���������� �++------------------------
#include <iostream> // ����������� ����������� ���������� �++
 

//----------------------------�����---------------------------------------------
#include "gpioaregisters.hpp"       // ������� ��� ����� a
#include "gpiobregisters.hpp"       // ������� ��� ����� b
//=================================�����������==================================
#include "Temperature.h" 
#include "IMeasureParameter.h" 
#include "adc1registers.hpp"         // ���������� ��� ���
#include "Resistor.h"               // ��� ������ Resistor 
#include "ADC.h"
#include "adccommonregisters.hpp"
//=================================������=======================================
#include "Front.h"
#include "Flowmeter.h"   
#include "WaterConsumtion.h"  
#include "tim3registers.hpp"         // ���������� ��� TIM3
//=================================���==========================================
#include "CurrentControler.h"   
#include "PWM.h"  
//=================================ModBus=======================================
#include "Modbus.h"
#include "IDataSource.h"
 //================================-����========================================
#include "rtos.hpp"
#include "TemperatureTask.h" 
//#include "DataTransferTask.h"   
//#include "CurrentPowerRegulationTask.h"   
#include "FlowTask.h"   

std::uint32_t SystemCoreClock = 16'000'000U;    // ������������ ����������� ����������, 1 ���� = 8 000 000 �� = 1 ���
std::uint32_t OneMillisecondRation = 1000U; // ����������� �������
std::uint32_t Timer3Prescaller = SystemCoreClock / OneMillisecondRation; // 1 �����


//----------------------------�������� ��������---------------------------------  
  ADC adc;
  Resistor resistor(static_cast<IDataSource&>(adc));
  Temperature temperature(static_cast<IDataSource&>(resistor)); // �������� ������ ��� ������� �����������
  TemperatureTask temperatureTask(temperature);                 // �������� ������ �� ��������� �����������
  
  Flowmeter flow;
  WaterConsumtion waterConsumption(static_cast<IDataSource&>(flow));
  FlowTask flowTask(waterConsumption);
//------------------------------------------------------------------------------  
 

//------------------------------------------------------------------------------    
int main()
{
 
  RCC::AHB1ENR::GPIOAEN::Enable::Set();         // ������ ������������ �� ���� A
  RCC::AHB1ENR::GPIOBEN::Enable::Set();         // ������ ������������ �� ���� B
  
  //------------------------------------���-------------------------------------
  GPIOA::MODER::MODER0::Analog::Set();
  RCC::APB2ENR::ADC1EN::Enable::Set();       // ������ ������������ �� ���
  RCC::AHB1ENR::DMA2EN::Enable::Set();       // ������ ������������ �� ���
  adc.Start();

  ADC1::CR1::RES::Bits12::Set();             // ����������� ���   
  ADC1::CR1::SCAN::Enable::Set();            // ����� ������������

  ADC1::CR2::CONT::ContinuousConversion::Set();
  ADC1::CR2::DMA::Enable::Set();
  ADC1::CR2::DDS::DMARequest::Set();
  ADC1::CR2::ADON::Enable::Set();
  ADC1::CR2::SWSTART::On::Set();
  
  //-----------------------------������ � ������ �������------------------------
  GPIOB::MODER::MODER4::Alternate::Set();
  RCC::APB1RSTR::TIM3RST::Reset::Set();   // ����� �������
  RCC::APB1ENR::TIM3EN::Enable::Set();       // ������ ������������ �� ������ TIM3
  RCC::AHB1ENR::DMA1EN::Enable::Set();       // ������ ������������ �� ���
  flow.Start();

  TIM3::CCMR1_Input::CC1S::Value1::Set();                 // ���������� ����������� ������
  TIM3::CCMR1_Input::IC1F::Value1::Set();                 // ���������� �����
  
  // ������ �� ��������� ������
  TIM3::CCER::CC1P::Value0::Set();
  TIM3::CCER::CC1NP::Value0::Set();
  
  TIM3::CCER::CC1E::Value1::Set();                          // ������ �������
  
  TIM3::ARR::Write(10);// 10 ����������                  // ������������ ������� ������� �� �������� �� �������
  TIM3::CNT::Write(0);
  TIM3::SR::UIF::NoInterruptPending::Set();             // ������� ����
  TIM3::CR1::CEN::Value1::Set();                        // ��������� ��������
  TIM3::PSC::Write(Timer3Prescaller);                   // �������� �������
 
  TIM3::DIER::CC1IE::Value1::Set();                         // ���������� ���������
  TIM3::DIER::CC1DE::Value1::Set();                         // ��� �������
  NVIC::ISER1::Write(1U << 29U);  // ��������� ���������� ����������, ��� 29 - ������� ������� TIM3, ISER1 ������ ������ 32 ��������, ����� ��� ISER2, ������� ������ ��������� 32 �������� � �.�.
  
  //---------------------------�������� �����-----------------------------------
  OsWrapper::Rtos::CreateThread(temperatureTask, "TemperatureTask"); 
  OsWrapper::Rtos::CreateThread(flowTask, "flowTask"); 
  OsWrapper::Rtos::Start();
  
  for(;;)  
  { 
    
    float temperatureWithADC = temperature.Calculate();
    float ConsumptionWithFlowmeter = waterConsumption.Calculate();
    
  }
  
  

  
}
