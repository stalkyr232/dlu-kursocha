#include "rccregisters.hpp"           // ��� ������ ������������ RCC

#include "adc1registers.hpp"         // ���������� ��� ���
#include "tim3registers.hpp"         // ���������� ��� TIM3

//----------------------------����������� ���������� �++------------------------
#include <iostream> // ����������� ����������� ���������� �++
 

//----------------------------�����---------------------------------------------
#include "gpioaregisters.hpp"       // ������� ��� ����� a
#include "gpiocregisters.hpp"       // ������� ��� ����� c

//====================================����������================================
#include "IMeasureParameter.h" 
#include "IDataSource.h"

//====================================������====================================
#include "ADC.h"
#include "Voltage.h" 
#include "Frequency.h"
#include "Filter.h"
 //================================-���� � ������===============================
#include "rtos.hpp"
#include "Generator_Task.h"

std::uint32_t SystemCoreClock = 16'000'000U;    // ������������ ����������� ����������, 1 ���� = 8 000 000 �� = 1 ���
std::uint32_t OneMillisecondRation = 1000U;     // ����������� �������
std::uint32_t Timer3Prescaller = SystemCoreClock / OneMillisecondRation; // 1 �����


//----------------------------�������� ��������---------------------------------  
  ADC adc;                                           // ������ ��� ��� ��������� ���� � �������������
  Voltage volt(static_cast<IDataSource&>(adc));      // ������ ��� �������� ���� � ����������
  Filter fiter (static_cast<IDataSource&>(volt));
  Frequency freq(static_cast<IDataSource&>(fiter));  // �������� ������ ��� ������� ������� � ����������� �� �������� �������������
  GeneratorTask generator(freq);                    // �������� ������ �� ������ ������ �������� � ARR � � CCR
 
 
int main()
{
 
  RCC::AHB1ENR::GPIOAEN::Enable::Set();         // ������ ������������ �� ���� A
  RCC::AHB1ENR::GPIOCEN::Enable::Set();         // ������ ������������ �� ���� C
  
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
  
  //----------------------------------���---------------------------------------
  
  GPIOC::MODER::MODER8::Alternate::Set();
  GPIOC::AFRH::AFRH8::Af2::Set();

   RCC::APB1ENR::TIM3EN::Enable::Set();       // ������ ������������ �� ������ TIM3

  TIM3::CNT::Write(0);
  TIM3::SR::UIF::NoInterruptPending::Set();             // ������� ����
  // ��������� ��� ��� 4 ������
  TIM3::CCMR2_Output::OC3M::Value6::Set();   
  TIM3::CCMR2_Output::OC3PE::Value1::Set(); 
  
  TIM3::PSC::Write(Timer3Prescaller);                   // �������� �������
  TIM3::ARR::Write(100);
  TIM3::CCR3::Write(10);  
  
  TIM3::CCER::CC3E::Value1::Set();          // ��������� ������ �������

  TIM3::CR1::CEN::Value1::Set();           // ��������� ��������      
  
  //---------------------------�������� �����-----------------------------------
  OsWrapper::Rtos::CreateThread(generator, "GeneratorTask"); 
  OsWrapper::Rtos::Start();
  
  // ������ assert ������������ ��� ��������� ������ ������ �� ����� ���������� ���������. 
  // �������� assert(expression) ��������� �������� false ������ � ��� ������, ���� ��������� �������� �����������.
  // ������� �������, ��������� ������ ���� �� ������ ������� �����������, ���� ��������� ������ �� assert, �� ��������� �������� �����������.
  assert(false); 
  return 0;
  
  }