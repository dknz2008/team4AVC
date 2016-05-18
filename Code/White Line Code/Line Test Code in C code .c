##include <stdio.h>
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

  int arrayOfPixels[320]; // making array of pixels to store values in

        init(0);
  while(true){


      int adc_reading = 0;

//      open_screen_stream(); // Puts the video output on desktop screen

                take_picture();
                int sum = 0;
                int i, w, s;    
                for(i=0; i<320; i++){
                        w = get_pixel(120,i,3); //the variable was in the wrong column so the code was reading a column instead of a row and the column never gets to 320 because the height of the camera resolution is 240.
                        if(w>180){
                          s=1;
                        }    
                        else{   
                                s=0;
                        };
                        sum = (sum + (i-160)*s);
                }

                printf("sum = %d", sum);
                if(sum > 0){  
                //turn_left();  
                        set_motor(1, 105);
                        set_motor(2, 105);
        		Sleep(1,0);
                }

                if(sum <  0){
                        //turn_right();

                        set_motor(1, -105);
                        set_motor(2, -105);
                	printf("drive right");
                	Sleep(1,0);             
}
                if(sum == 0){
                        //drive_forward();
                        set_motor(1, -70);
                        set_motor(2, 70);
                        printf("drive forward");
                        Sleep(1,0);
                }

  //    update_screen(); //  - updates video output area of the screen.
  }

 // close_screen_stream();
 
  return 0;
}






