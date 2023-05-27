#ifndef DMA_H
#define DMA_H
#include "dma2registers.hpp"         // Для подключения ДМА
#include "dma1registers.hpp"         // Для подключения ДМА
#include "adc1registers.hpp"         // библиотека для АЦП
#include "tim3registers.hpp"         // библиотека для таймера TIM3

//template<typename TDmaConfig, typename Channel, typename Steam> 
class DMA
{
public:
  
  static void ConfigureADC(std::uint32_t variableAddress)
  {
      Disable();
      DMA2::S0CR::CHSEL::Channel0::Set();          // Выбор 0 канала под запись данных с АЦП, где S0CR - steam 0
      DMA2::S0CR::CT::AddressedDMA_SxM0AR::Set();  // устанавливается память ,адресуется указателем DMA_SxM0AR  
      DMA2::S0CR::DBM::Off::Set();                 // 
      DMA2::S0CR::MSIZE::bit_32::Set();            // выделение памяти под хранение данных
      DMA2::S0CR::PSIZE::bit_32::Set();    
      DMA2::S0CR::CIRC::Enabled::Set();            // циклический режим работы ДМА
      DMA2::S0CR::DIR::PeripheralToMemory::Set();  // размещает данные из периферийного устройства в память 
      DMA2::S0CR::PFCTRL::DMAController::Set();  
      DMA2::S0PAR::Write(ADC1::DR::Address);       // забирает данные из периферии
      DMA2::S0M0AR::Write(variableAddress);        // записывает данные в этот адресс
      DMA2::S0NDTR::Write(1);
      DMA2::S0CR::EN::Enabled::Set();             // включение потока
  };
  
    static void ConfigureFlow(std::uint32_t variableAddress)
  {
      Disable();
      DMA1::S4CR::CHSEL::Channel5::Set();          // Выбор 0 канала под запись данных с АЦП, где S0CR - steam 0
      DMA1::S4CR::CT::AddressedDMA_SxM0AR::Set();  // устанавливается память ,адресуется указателем DMA_SxM0AR  
      DMA1::S4CR::DBM::Off::Set();                 // 
      DMA1::S4CR::MSIZE::bit_32::Set();            // выделение памяти под хранение данных
      DMA1::S4CR::PSIZE::bit_32::Set();    
      DMA1::S4CR::CIRC::Enabled::Set();            // циклический режим работы ДМА
      DMA1::S4CR::DIR::PeripheralToMemory::Set();  // размещает данные из периферийного устройства в память 
      DMA1::S4CR::PFCTRL::DMAController::Set();  
      DMA1::S4PAR::Write(TIM3::CCR1::Address);     // забирает данные из периферии
      DMA1::S4M0AR::Write(variableAddress);        // записывает данные в этот адресс
      DMA1::S4NDTR::Write(1);
      DMA1::S4CR::EN::Enabled::Set();             // включение потока
  };
  
  static void Start()
  {
      // DMA2::S0CR::EN::Enabled::Set();             // включение потока
  };
  static void Disable()
  {
      DMA1::S4CR::EN::Disabled::Set();             // выключение потока
      DMA2::S0CR::EN::Disabled::Set();             // выключение потока
  };
};

#endif
