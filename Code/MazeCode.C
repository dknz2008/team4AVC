# include <stdio.h>
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
	//Variables
	int tooClose = 500;
	int tooFar = 200;
	int detected = 80;
	//variable 'detected' used to detect if the robot is entering the maze 
	
	init(0);
	int adc_Front;
	int adc_Left;
	int adc_Right;
	while(1)
	{
		adc_Front = ReadAnalog(1);
		adc_Left = ReadAnalog(2);
		adc_Right = ReadAnalog(3);
		
		//printf("%d\n", adc_readingFront);
		
		if(adc_Front > tooClose)
		{
			if(adc_Left > tooFar && adc_Right > tooFar)
			{
				//180 Degree turn
				set_motor(1,-100);
				set_motor(2,-100);
				Sleep(1,500000);
			}
			else if(adc_Left > tooFar)
			{
				//90 Degree turn right
				set_motor(1,-100);
				set_motor(2,-100);
				Sleep(1,500000);
			}
			else
			{
				//90 Degree turn left
				set_motor(1,-100);
				set_motor(2,-100);
				Sleep(1,500000);
			}
		}
	}
	
	return 0;
}
