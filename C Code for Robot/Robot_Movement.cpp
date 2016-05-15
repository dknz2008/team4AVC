# include <stdio.h>
# include <time.h>
extern "C" int init();
extern "C" int write_digital( int chan , char level );
extern "C" int set_motor(int motor,int speed);
extern "C" int Sleep( int sec , int usec );
extern "C" int read_analog(int ch_adc);
extern "C" char get_pixel(int row,int col,int color);

int main (){
      // This sets up the RPi hardware and ensures
      // everything is working correctly
      init();

	
	int arrayOfPixels[64]; //For every 5 pixels (340/5 = 64)
	int total = 0;
		
	float kp = 0.5;
	float ki = 0.5;
	float kd = 0.5;

	int total_error = 0;
	int current_error = 0;
	int previous_error = 0;
 	int error_diff = 0;
	int error_period = 0; //need to change

	int i, w, s;

	double proportional_signal;	
	int integral_signal = 0;
	int derivative_signal = 0;



        while (1) {

		int adc_reading = 0;

		//take_picture();
		 

	
		for(i = 0; i < 64; i++){
			//need to check if 120 is the middle or not
			arrayOfPixels[i] = get_pixel(i*5, 120, 3);
			//Getting total of the pixels along the pane
			total = total + arrayOfPixels[i];

		}	
	
		for(i=0; i<320; i++){
			w = get_pixel(i,120,3);
			//printf("%f\n",w);	
			if(w>127){
				s = 1;
				//Calculating error, if to the left, will give negative number, 
				//if to right, positive
				current_error = (current_error + (i-160)*s);
			}	
		}
		
		
		//Random error checking code, most of which isn't implemented yet
		total_error = total_error + current_error;
		integral_signal = total*ki;
		
		error_diff = current_error-previous_error;
		derivative_signal = (error_diff/error_period)*kd;
		previous_error = current_error;
		

		//Getting the robot to move
		proportional_signal = current_error*kp;	
	
		set_motor(1, proportional_signal);
		set_motor(2, -1*proportional_signal);	     		

      }

return 0;
}
