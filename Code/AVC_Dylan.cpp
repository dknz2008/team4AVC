 include <stdio.h>
# include <time.h>
extern "C" int init(int);
extern "C" int write_digital( int chan , char level );
extern "C" int set_motor(int motor,int speed);
extern "C" int Sleep( int sec , int usec );
extern "C" int read_analog(int ch_adc);
extern "C" char get_pixel(int row,int col,int color);
extern "C" int take_picture();
extern "C" int select_IO(int chan, int direct);

int main (){
      // This sets up the RPi hardware and ensures
      // everything is working correctly
      init(0);
        float kd = 5;
        float current_error = 0;
        float  pid_left;
        float pid_right;
        int w, s;
        double proportional_signal;

        while (1) {

        take_picture();
        float current_error_average = 0;
                pid_left = 0;
                pid_right = 0;

                current_error = 0;
                proportional_signal = 0;

                int num = 0;
                int dark = 0;
                for(int i=0; i<320; i++){
                        w = get_pixel(i,120,3);

                        if(w>127){
                                s = 1;
                                num++;
                        }else{
                                dark++;
                                s = 0;
                        }
 current_error = (current_error + (i-160)*s);

                        }
                        current_error_average = current_error/num;

                //Getting the robot to move
                proportional_signal = current_error*kd;

                int abc;
//              if(dark >= 320){
//                      printf("dark");
//                      pid_left =  -100;
//                      pid_right = - 100;
//                      Sleep(0, 5000);
//                      dark = 0;
//              }else{
                        pid_left =( 80 +  proportional_signal/(160*2) );
                        pid_right = (80 - proportional_signal/(160*2) );
//              }

                set_motor(1, -pid_left);
                set_motor(2, -pid_right);

/**             if(pid > 255){
                        set_motor(1,-1*255);
                        set_motor(2, 255);
                }else if(pid < -255){
                        set_motor(1, 255);
                       set_motor(2,- 1*255);
                }else{
                        set_motor(1, -pid);
                        set_motor(2, pid);
                }
        */
 }

        set_motor(1,0);
        set_motor(2, 0);
return 0;
}

