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

	
//	int arrayOfPixels[64]; //For every 5 pixels (340/5 = 64)
//	int total = 0;
	float kd = 1.2;
//	float ki = 0.5;
//	float kd = 0.2;

//	float total_error = 0;
	float current_error = 0;
//	int previous_error = 0;
// 	int  error_diff = 0;
//	int  error_period = 0; //need to change
	float  pid;

	int w, s;

	double proportional_signal;	
//	int integral_signal = 0;
//	int derivative_signal = 0;
	

//	for(i = 0;  i < 8; i++){

//	select_IO(i, 0);
//	write_digital(i, 1);
//	}


        while (1) {

	
	take_picture();
	int color = get_pixel(102, 55, 3);
//	printf("Color=%d\n", color);
//	int adc_reading = 0;

		
		current_error = 0;
		proportional_signal = 0;
	
//		for(i = 0; i < 64; i++){
			//need to check if 120 is the middle or not
//			arrayOfPixels[i] = get_pixel(120,i*5, 3);
			//Getting total of the pixels along the pane
//			total = total + arrayOfPixels[i];

//		}	
	
		for(int i=0; i<320; i++){
			w = get_pixel(i,120,3);
//			printf("%d\n",w);
			if(w>120){
				s = 1;
			}else{

				s = 0;
			}				

//if to right, positive
				current_error = (current_error + (i-160)*s);

			//	printf("current_error is  %f \n", current_error);

			}




	              //  printf("PID: %f \n", pid);
		
		
		
		//Random error checking code, most of which isn't implemented yet
//		total_error = total_error + current_error;
//		integral_signal = total*ki;
		
//		error_diff = current_error-previous_error;
//		derivative_signal = (error_diff/error_period)*kd;
//		previous_error = current_error;
		

		//Getting the robot to move
		proportional_signal = current_error*kd;	
	//	printf("Current Error: %f \n", current_error);
	//	printf("Proportional Signal %f \n", proportional_signal);
	
		
	/**	int abc;
		if(proportional_signal > 0){
			abc = 1;
		}else if(proportional_signal < 0){
			abc = -1;
		}else{
			abc = 1;
		}*/
    		pid =( proportional_signal );	
		

		
	

		
		printf("PID: %f \n", pid);

		if(pid > 255){				
			set_motor(1,-1*255);
			set_motor(2, 255);	     		
		}else if(pid < -255){
			set_motor(1, 255);
                       set_motor(2,- 1*255);
		}else{
			set_motor(1, -pid);
			set_motor(2, -pid);
		}
      }

return 0;
}

