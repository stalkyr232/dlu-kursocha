#include "WaterConsumtion.h"


WaterConsumtion::WaterConsumtion(IDataSource& numberTopsFronts): _numberTopsFronts(numberTopsFronts) 
 {
   
 }

float WaterConsumtion::Calculate()
{
 float flowRate = (_numberTopsFronts.GetData() * s) / R ;
 return flowRate;
}