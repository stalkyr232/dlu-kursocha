#ifndef DMA_H
#define DMA_H
#include "dma2registers.hpp"         // ��� ����������� ���
#include "dma1registers.hpp"         // ��� ����������� ���
#include "adc1registers.hpp"         // ���������� ��� ���
#include "tim3registers.hpp"         // ���������� ��� ������� TIM3

//template<typename TDmaConfig, typename Channel, typename Steam> 
class DMA
{
public:

  static void ConfigureADC(std::uint32_t variableAddress)
  {
      Disable();
      DMA2::S0CR::CHSEL::Channel0::Set();          // ����� 0 ������ ��� ������ ������ � ���, ��� S0CR - steam 0
      DMA2::S0CR::CT::AddressedDMA_SxM0AR::Set();  // ��������������� ������ ,���������� ���������� DMA_SxM0AR
      DMA2::S0CR::DBM::Off::Set();                 // 
      DMA2::S0CR::MSIZE::bit_32::Set();            // ��������� ������ ��� �������� ������
      DMA2::S0CR::PSIZE::bit_32::Set();
      DMA2::S0CR::CIRC::Enabled::Set();            // ����������� ����� ������ ���
      DMA2::S0CR::DIR::PeripheralToMemory::Set();  // ��������� ������ �� ������������� ���������� � ������ 
      DMA2::S0CR::PFCTRL::DMAController::Set();
      DMA2::S0PAR::Write(ADC1::DR::Address);       // �������� ������ �� ���������
      DMA2::S0M0AR::Write(variableAddress);        // ���������� ������ � ���� ������
      DMA2::S0NDTR::Write(1);
      DMA2::S0CR::EN::Enabled::Set();             // ��������� ������
  };


  static void Disable()
  {
                  // ���������� ������
      DMA2::S0CR::EN::Disabled::Set();             // ���������� ������
  };
};

#endif
