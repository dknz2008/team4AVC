#include <iostream>
#include <stdio.h>
#include <time.h>

//Extern C

//Initilise Hardware
extern "C" int init(int d_lev);

/* Camera Feed */
extern "C" int update_screen();
extern "C" int open_screen_stream();
extern "C" int close_screen_stream();
extern "C" int take_picture();
extern "C" char get_pixel(int row,int col,int colour);

/* Motor */
extern "C" int set_motor(int motor, int speed);
extern "C" int Sleep(int sec, int usec);

/* Server */
extern "C" int connect_to_server( char server_addr[15],int port);
extern "C" int send_to_server(char message[24]);
extern "C" int receive_from_server(char message[24]);
 
/* Char */
char internetProtocol[] = "130.195.6.196";

/* Integer*/
int port = 1024;

/* Double */
double pixelTotal;
double pixelAverage;
double Kp = 0;		//Proportional Value (Keep values in the tens)
double Kd = 0;		//Derivative Value
double Ki = 0;		//Integral Value
double left, right;

/* Floats */
float kpEv;          //Error Value for proportional
float kdEv;          //Error Value for derivative
float kiEv;          //Error Value for integral

//Calls
int networking();
int lineFollow();

//Methods
int main(){
	init(0);               //Initialise Rpi Hardware
	networking();          //Runs Networking Code
}

int networking(){
	char message[24];                // It can accept up to 24 chars in its array
	
	connect_to_server(internetProtocol, port);   //Connect to the server passing in variables
    send_to_server("Please");                        //Sends "Please" to the server
    
    receive_from_server(message);        //Recieves a message & stores in message(Char)
    send_to_server(message);             //Sends recieved message to the server
    
    //printf("%s", message);             //Debugging purpose: Prints out message(Char)
	return 0;
	lineFollow();	
}

int lineFollow(){
	int pixelArray[32];
	int sample = sizeOf(pixelArray)/sizeOf(int);//Finds the size of the array then divides by the size of an int
	
	while(true){                                //Forever True until certain event is met
		kpEv = 0;                           //Proportional ErrorValue = 0
		pixelTotal = 0;                     //Pixel Totel = 0
		pixelAverage = 0;                   //PixelAverage = 0
		take_picture();                     //Takes a picture with the camera
		
		for(int i = 0; i < sample; i++){                     //This proccess
			pixelArray[i] = get_pixel(i*10, 120, 3);nnnn //Finds the brightness
			pixelTotal += pixelArray[i];	             //Of pixels in the array
		}
		
		pixelAverage = pixelTotal/sample;//Finds the average brightest pixel
		
		for(int i = 0; i < sample; i++){             //Finds if pixel is brighter
			if(pixelArray[i]>pixelAverage){      //Then the average, a negitive number means turn left
				kpEv += 10*(i-sample/2);     //Positive number means turn right
			}
		}
		
		//printf("%f\n", kpEv);            //Debugging Purpose: Prints float(%f) proportional error value
		
		left = 40 + (kpEv * kp);           // Determines the new motor speeds to alter direction
		right = 40 - (kpEv * kp);          // Determines the new motor speeds to alter direction
		
		set_motor(1, left);                // Changes the motor speeds to the predetermined values
		set_motor(2, right);               // Changes the motor speeds to the predetermined values
		
		//printf("%d, %d\n", left, right); //Debugging Purpose: Prints double(%d) left, right values
		update_screen();
	}
	
	close_screen_stream();
	return 0;
	
	
}
