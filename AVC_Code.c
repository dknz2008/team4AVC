#include <iostream>
#include <stdio.h>
#include <time.h>
extern "C" int InitHardware();
extern "C" int ReadAnalog(int ch_adc);
extern "C" int Sleep(int sec, int usec);
extern "C" int SetMotor(int motor ,int dir,int speed);

int main()
{
  
}
