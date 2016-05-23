# include <stdio.h>
# include <time.h>
extern "C" int init(int);
//extern "C" int write_digital( int chan , char level );
//extern "C" int Sleep( int sec , int usec );
extern "C" int read_analog(int ch_adc);
extern "C" int select_IO(int chan, int direct);

int main (){
	//Variables
	int adc_Front = 0;
	int adc_Left = 0;
	int adc_Right = 0;
	
	init(0);
	while(1)
	{
		adc_Front = ReadAnalog(1);
		adc_Left = ReadAnalog(2);
		adc_Right = ReadAnalog(3);
		
		printf("%d\n", adc_Front);
		printf("%d\n", adc_Left);
		printf("%d\n", adc_Right);
	}
