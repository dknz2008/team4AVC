#include <stdio.h>
#include <time.h>
extern "C" int InitHardware();
extern "C" int ReadAnalog(int ch_adc);
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

  while(true){

      InitHardware();

      int adc_reading = 0;

      open_screen_stream(); // Puts the video output on desktop screen

		take_picture();
		int sum = 0;
		int i, w, s;
		for(i=0, i<320, i++){
			w = get_pixel(i,120,3);
			if(w>127){
				s=1;
			};
			else{
				s=0;
			};
			sum = sum + (i-160)*s;
		}

		if(sum < 0){
			//turn_right();
			set_motor(1, 255);
  			set_motor(2, -255);

		}

		if(sum > 0){
			//turn_left();

  			set_motor(1, -255);
  			set_motor(2, 255);
		}
		if(sum == 0){
			//drive_forward();
			set_motor(1, 255);
  			set_motor(2, 255);
		}

      update_screen(); //  - updates video output area of the screen.
  }

  close_screen_stream()

  return 0;
}
