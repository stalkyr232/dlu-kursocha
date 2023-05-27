#include "rccregisters.hpp"                       // ��� ������ ������������ RCC
//#include "dma1registers.hpp"                       // ��� ����������� ���
//#include "dma2registers.hpp"                      // ��� ����������� ���
#include "adc1registers.hpp"         // ���������� ��� ���
#include "adccommonregisters.hpp"
#include "tim3registers.hpp"         // ���������� ��� TIM3

#include "nvicregisters.hpp"                      // ��� ���������� ���������� ����������
#include "interrupthandler.hpp"                   // ���������� �������� ����������
//#include "StartUp.cpp"                            // ��� ����������  
//----------------------------����������� ���������� �++------------------------
#include <iostream> // ����������� ����������� ���������� �++
 

//----------------------------�����---------------------------------------------
#include "gpioaregisters.hpp"       // ������� ��� ����� a
#include "gpiobregisters.hpp"       // ������� ��� ����� b
//=================================������==================================
//#include "Voltage.h" 
//#include "IMeasureParameter.h" 
#include "ADC.h"
#include "IDataSource.h"


 //================================-����========================================
#include "rtos.hpp"

std::uint32_t SystemCoreClock = 16'000'000U;    // ������������ ����������� ����������, 1 ���� = 8 000 000 �� = 1 ���
std::uint32_t OneMillisecondRation = 1000U; // ����������� �������
std::uint32_t Timer3Prescaller = SystemCoreClock / OneMillisecondRation; // 1 �����


//----------------------------�������� ��������---------------------------------  
  ADC adc;
 // Resistor resistor(static_cast<IDataSource&>(adc));
 // Temperature temperature(static_cast<IDataSource&>(resistor)); // �������� ������ ��� ������� �����������
 // TemperatureTask temperatureTask(temperature);                 // �������� ������ �� ��������� �����������
  
 
 
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
  
  
  //---------------------------�������� �����-----------------------------------
  //OsWrapper::Rtos::CreateThread(temperatureTask, "TemperatureTask"); 
 // OsWrapper::Rtos::CreateThread(flowTask, "flowTask"); 
  //OsWrapper::Rtos::Start();
  
  for(;;)  
  { 
    
  //  float temperatureWithADC = temperature.Calculate();
    //float ConsumptionWithFlowmeter = waterConsumption.Calculate();
    
  }
  
  

  
}
