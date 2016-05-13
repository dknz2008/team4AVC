#include <stdio.h>
#include <time.h>
extern "C" int init(int);
extern "C" int read_analog(int ch_adc);
extern "C" int Sleep(int sec, int usec);
extern "C" int set_motor(int motor,int speed);
extern "C" int take_picture();
extern "C" char get_pixel(int row,int col,int colour);
extern "C" int update_screen();
extern "C" int open_screen_stream();
extern "C" int close_screen_stream();


int main()
{

  while(true){

      init(0);

      int adc_reading = 0;
      
      

  take_picture();

                float kp = 0.5;
                int sum = 0;
                int i, w, s;

                for(i=0, i<320, i++){
                        w = get_pixel(i,120,3);
                        if(w>127){
                                s=1;
                        }
                        else{
                                s=0;
                        }
                        sum = sum + (i-160)*s;
                }

                double proportional_signal = sum*kp;

                if(proportional_signal > 255){
                        set_motor(1, 255);
                        set_motor(2, -1*255);
                }
                else if(proportional_signal < -255){
                        set_motor(1, -255);
                        set_motor(2, -1*255); //unsure if this is going to work
                }else{
                        set_motor(1, proportional_signal);
                        set_motor(2, -1*proportional_signal);
                }





