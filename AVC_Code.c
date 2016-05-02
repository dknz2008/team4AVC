#include <iostream>
#include <stdio.h>
#include <time.h>
extern "C" int InitHardware();
extern "C" int ReadAnalog(int ch_adc);
extern "C" int Sleep(int sec, int usec);
extern "C" int SetMotor(int motor ,int dir,int speed);

int main()
{
  InitHardware();
  int adc_reading = 0;
  
  //Drives forward and stops abruptly if something is in front of it
  while (adc_reading < 600)
  {
    adc_reading = ReadAnalog(0);
    SetMotor(1, 1, 255);
    SetMotor(2, 1, 255);
    //Sleep(0,500000);
  }
  
  //Turns left
  SetMotor(1, 0, 255);
  SetMotor(2, ,1 255);
  
  //Turns left
  SetMotor(1, 0, 255);
  SetMotor(2, ,1 255);
  
  //Turns left until there are no obstructions
  while (adc_reading >= 600)
  {
    adc_reading = ReadAnalog(0);
    SetMotor(1, 0, 255);
    SetMotor(2, ,1 255);
    //Sleep(0,500000);
  }
  
  //Turns right until there are no obstructions
  while (adc_reading >= 600)
  {
    adc_reading = ReadAnalog(0);
    SetMotor(1, 1, 255);
    SetMotor(2, ,0 255);
    //Sleep(0,500000);
  }
  
  //Drives forward and slows down when it gets close to a wall
   while (adc_reading >= 600)
  {
    adc_reading = ReadAnalog(0);
    SetMotor(1,1,adc_reading/700*255);
    //Sleep(0,500000);
  }
  
  //Gentle stop
  int count = 255;
  while (count > 0)
  {
    SetMotor(1, 0, count);
    SetMotor(2, ,1 count);
    count = count -10;
    //sleep(0,500000)''
  }
  
  return 0;
}
