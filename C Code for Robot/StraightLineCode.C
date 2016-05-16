#include <stdio.h>
#include <time.h>
extern "C" int InitHardware();
extern "C" int Sleep(int sec, int usec);
extern "C" int set_motor(int motor,int speed);


int main()
{

  set_motor(0, 100);
  set_motor(1, 100);

  return 0;
}
//test
