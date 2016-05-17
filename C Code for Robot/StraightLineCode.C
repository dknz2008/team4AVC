#include <stdio.h>
#include <time.h>
extern "C" int init(int);
extern "C" int sleep(int sec, int usec);
extern "C" int set_motor(int motor,int speed);

int main()
{
  init(0);
  set_motor(1, -100);
  set_motor(2, -100);
  sleep(3,0);
  set_motor(1, 0);
  set_motor(2, 0);
  return 0;
}
