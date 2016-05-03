#include <stdio.h>
#include <time.h>
extern "C" int InitHardware();
extern "C" int ReadAnalog(int ch_adc);
extern "C" int Sleep(int sec, int usec);
extern "C" int SetMotor(int motor ,int dir,int speed);
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
      White = get_pixel(120,160,3); // test camera case

      int sum = 0;
      int i;
      for(i = 0, i < 320, i++){

        b = 0;
        arrayOfPixels[i] = get_pixel(120, i, 3);
        w = get_pixel(120, i, 3);
        sum = sum + i*w;
      
      }

      //finding the average of every group of 20 pixels
      int GroupOfPixels = [16];  // 320/20 = 16
      int AverageGroupOfPixels = [16];
      
      for(int n = 1; n <= 16; n++){
         for(int i = 0; i < 20; i++){
              GroupOfPixels[n] = GroupOfPixels[n] + arrayOfPixels[i*n]; 
         }

         i = 0;
         AverageGroupOfPixels[n-1] = GroupOfPixels[n-1]/20; 
     }


        //Finding max value
        int max = 0;
        for(int i = 0; i < 16; i++)
        {
          if(AverageGroupOfPixels[i] > max){
            max = AverageGroupOfPixels[i];
          }
        }

        //Finding min value
        int min = 0;

        for(int i = 0; i < 16; i++)
        {
          if(AverageGroupOfPixels[i] < min){
            min = AverageGroupOfPixels[i];
          }
        }


     if(){


     }

      update_screen(); //  - updates video output area of the screen. 
  }

  close_screen_stream()
  
  return 0;
}
