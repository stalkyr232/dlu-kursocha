#include "Temperature.h"

Temperature::Temperature(IDataSource& resistor): _resistor(resistor) 
 {
   
 }

float Temperature::Calculate()
{
  
 float T = At + _resistor.GetData() * Bt + _resistor.GetData()*_resistor.GetData() * Ct ;
 return T;
}