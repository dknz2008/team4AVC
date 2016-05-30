#include <stdio.h>
#include <time.h>
extern "C" int init(int);
extern "C" int write_digital( int chan , char level );
extern "C" int set_motor(int motor,int speed);
extern "C" int Sleep( int sec , int usec );
extern "C" int read_analog(int ch_adc);
extern "C" char get_pixel(int row,int col,int color);
extern "C" int take_picture();
extern "C" int select_IO(int chan, int direct);

extern "C" int connect_to_server(char server_addr[15],int port);
extern "C" int send_to_server(char message[24]);
extern "C" int receive_from_server(char message[24]);

 

int network(){
        //network code
        char ip[20] = "130.195.6.196\0";

        connect_to_server(ip, 1024);
        printf("Connecting");
        char msg[20] = "Please\0";
        send_to_server(msg);
        printf("something happened 1");
        char message[24];
        receive_from_server(message);
        printf("something happened");
        send_to_server(message);
        printf("%s", message);
        return 0;
}


int main (){
      // This sets up the RPi hardware and ensures
      // everything is working correctly
      init(0);


        bool center = false;
      int msec =0;
        int trigger = 10;
        clock_t before = clock();

        float kd = 5;
        float current_error = 0;
        float  pid_left;
        float pid_right;
        int w, s;
        int w1; //second line
        double proportional_signal;
        float dir = 0;
        int changeTurn = 0;
        time_t sec;
        time_t sec1;
        sec = time(NULL);
        sec1 = time(NULL);
        int seconds_passed = 0;
        int abcd = 0;
        int quad3 = 0;

 
//      network();
 


while (1) {
 


        float current_error_average = 0;
                pid_left = 0;
                pid_right = 0;
 
                current_error = 0;
                proportional_signal = 0;
                w1 = 0;
                w  = 0;
                int num = 0;
                int dark = 0;
                int dark1 = 0;
                take_picture();
                        for(int i=0; i<320; i++){
                                w = get_pixel(i,120,3);
                                w1 = get_pixel(i, 0, 3); 
                                if(w>127){
                                        s = 1;
                                        num++;
                                }else{
                                        dark++;
                                        s = 0;
                                }

                                if(w1 < 127){
                                        dark1++;
                                }

                                        current_error = (current_error + (i-160)*s);

                                }

                printf("current error %f", current_error);
                //Getting the robot to move
                proportional_signal = current_error*kd;


                        pid_left = 140 + proportional_signal/(320);
                        pid_right = 140 - proportional_signal/(320);



                printf("pid right: %f", pid_left);
                printf("pid left: %f", pid_right);
                if(pid_left >= 255){
                        pid_left = -255;
                }
                if(pid_right >= 255){
                        pid_right = -255;
                }
                if(pid_left <= -255){
                        pid_left = 255;
                }
                  if(pid_right <= -255){
                        pid_right = 255;
                }
 
                set_motor(1, pid_left);
                set_motor(2, -pid_right);
                
                }

        set_motor(1,0);
        set_motor(2, 0);
return 0;
}

 
