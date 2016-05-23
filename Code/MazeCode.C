# include <stdio.h>
# include <time.h>
extern "C" int init(int);
extern "C" int write_digital( int chan , char level );
extern "C" int set_motor(int motor,int speed);
extern "C" int Sleep( int sec , int usec );
extern "C" int read_analog(int ch_adc);
extern "C" int select_IO(int chan, int direct);

int main (){
	//Variables
	int tooClose = 500;
	int wallDistance = 200;
	int speed = 100;
	int adc_Front = 0;
	int adc_Left = 0;
	int adc_Right = 0;
	int sectorTime = 1;
	int usectorTime = 0;
	int turnTime = 1;
	int uturnTime = 0;
	String state = "line";
	
	init(0);
	if(state == maze) //State will be changed from "line" to "maze" when the camera detects an amount of red pixels
	{
		while(1)
		{
			adc_Front = ReadAnalog(1);
			adc_Left = ReadAnalog(2);
			adc_Right = ReadAnalog(3);
			
			//printf("%d\n", adc_readingFront);
			
			//Through testing i have found that the way to complete any maze
			if(adc_Front < wallDistance)
			{
				if(adc_Left < wallDist)
				{
					//90 Degree turn left
					set_motor(1,-1 *speed);
					set_motor(2,speed);
					Sleep(turnTime,uturnTime);
					//Then drive forward one sector
					set_motor(1,speed);
					set_motor(2,speed);
					Sleep(sectorTime,usectorTime);
				}
				else
				{
					if(adc_Left < wallDist)
					{
						//Drive forward one sector
						set_motor(1,speed);
						set_motor(2,speed);
						Sleep(sectorTime,usectorTime);
					}
				
			}
			else if(adc_Front > tooClose) //If there is a wall infront of the robot
			{
				if(adc_Left >= wallDistance && adc_Right >= wallDistance) //If the robot comes to a dead end
				{
					//180 Degree turn
					set_motor(1,-1* speed);
					set_motor(2,100);
					Sleep(turnTime,uturnTime);
				}
				else if(adc_Left >= wallDistance) //If the robot comes to a place where there is walls infront and to the left but not to the right
				//Note at a T intersection 
				{
					//90 Degree turn right
					set_motor(1,speed);
					set_motor(2,-1 * speed);
					Sleep(turnTime,uturnTime);
				}
				else //If the robot comes to a place where there is walls infront but no wall to the left, it will turn left
				//Note it will make the robot turn left at a T intersection
				{
					//90 Degree turn left
					set_motor(1,-1 * speed);
					set_motor(2,speed);
					Sleep(turnTime,uturnTime);
				}
			}
			
			Sleep(1,0);
		}
	}
	
	return 0;
}
