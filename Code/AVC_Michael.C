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
      // This sets up the RPi hardware and ensures
      // everything is working correctly
	init(0);
	float kd = 20;
	float current_error = 0;
	float  pid_left;
	float pid_right;
	int w, s;
	double proportional_signal;
	int quarterTurnTime = 1;
	int halfTurnTime = 1;
	int onLineMin = 30;
	int onLineMax = 50;
	int halfLineValue = 180;

        while (1) {
		take_picture();
		float current_error_average = 0;
		pid_left = 0;
		pid_right = 0;
		
		//int color = get_pixel(102, 55, 3);
	
		current_error = 0;
		proportional_signal = 0;
		
		int num = 0;
		int dark = 0;
	
		for(int i=0; i<320; i++){
			w = get_pixel(120,i,3);
			if(w>127){
				s = 1;
				num ++;
			}else{
				dark ++;
				s = 0;
			}				

			//if to right, positive
			current_error = (current_error + (i-160)*s);
			}
			current_error_average = current_error/num;

		//Getting the robot to move
		//numbers here need to be thoroughly tested
		if(s >= onLineMin && s < onLineMax)//if number of white pixels detected is between onLineMin and onLineMax pixels (on white line)
		{
			proportional_signal = current_error*kd;	
	    		pid =( proportional_signal );	
			printf("PID: %f \n", pid);
	
			//if(pid > 255){				
			//	set_motor(1,-1*255);
			//	set_motor(2, 255);	     		
			//}else if(pid < -255){
			//	set_motor(1, 255);
	                //      set_motor(2,- 1*255);
			//}else{
				pid_left = (80 + proportional_signal / (160*2));
				pid_right = (80 - proportional_signal / (160*2));
				set_motor(1, -pid_left);
				set_motor(2, -pid_right);
			//}
		}
		else if(s >= onLineMax && s < halfLineValue)//if number of white pixels detected is between onLineMax and halfLineValue pixels (roughly half of line is white - 90 degree turn)
		{
			//turn 90 degrees in that direction
			if(pid > 255){				
				set_motor(1,-1*255);
				set_motor(2, 255);
				sleep(quarterTurnTime,0);
			}else if(pid < -255){
				set_motor(1, 255);
	                        set_motor(2,- 1*255);
	                        sleep(quarterTurnTime,0);
		}
		else if(s >= halfLineValue) //if number of white pixels detected is greater than halfLineValue pixels (over half of the reading is white - T intersection - turn 90 in a direction)
		{
			//turn 90 degrees left or right
			set_motor(1,-1*255);
			set_motor(2, 255);
			sleep(quarterTurnTime,0);
		}
		else //anything less than onLineMin pixels of white detected (must be dead end - turn 180)
		{
			//turn 180 degrees
			set_motor(1,-1*255);
			set_motor(2, 255);
			sleep(halfTurnTime,0);
		}
      }

return 0;
}
