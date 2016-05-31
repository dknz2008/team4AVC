include <stdio.h>
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


int cameraRead(){
        int w = 0;
        int dark = 0;
        int w1 = 0;     
        int dark1 = 0;
        int current_error = 0;
        int s = 0;
        int num = 0;


                        take_picture();
                        for(int i=0; i<320; i++){
                                w = get_pixel(i,120,3);
//                                w1 = get_pixel(i, 0, 3);
                                if(w>100){   
                                        s = 1;
                                        num++;
                                }else{
                                        dark++;
                                        s = 0;
                                }

                                if(w1 < 50){ 
                                        dark1++;
                                }

                                        current_error = (current_error + (i-160)*s);

                                }
        return dark;  

}



int main (){
      // This sets up the RPi hardware and ensures
      // everything is working correctly
      init(0);


        bool center = false;
      int msec =0;
        int trigger = 10;
        clock_t before = clock();

        float kp = 7.5;
        float kd = 0.5; 
        float current_error = 0;
        float previous_error = 0;
        float  pid_left;
        float pid_right;
        int w, s;
        int w1; //second line
        double proportional_signal;
        int derivative_signal;
        float dir = 0;
int changeTurn = 0;
        time_t sec;
        time_t sec1;
        sec = time(NULL);
        sec1 = time(NULL);
        int seconds_passed = 0;
        int abcd = 0;
        int quad3 = 0;

        int turnNum = 1;
        network();


//      set_motor(1, 220);
//      set_motor(2, -55);

        int t_junction = 0;
        int missFirst = 0;
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
                                if(w>100){
                                        s = 1;
                                        num++;
                                }else{
                                        dark++;
                                        s = 0;
                                }
 if(w1 < 50){
                                        dark1++;
                                }
        
                                        current_error = (current_error + (i-160)*s);
        
                                }
  




             
                //printf("current error %f", current_error);
                //Getting the robot to move

                proportional_signal = current_error*kp;

                        pid_left = 150 + proportional_signal/(320);
                        pid_right = 150 - proportional_signal/(320);


        //      printf("num: %d\n", num);
        //      printf("dark: %d\n", dark1);
                if(dark >= 320 && t_junction == 0){
                        printf("backward\n");
                        pid_left = -190;
                        pid_right = -190;
                        //Sleep(0, 20000);
                }



                if(turnNum ==3 && dark >=300){
                        set_motor(1, 180);
                        set_motor(2, -180);
                        Sleep(0, 300000);
                        set_motor(1, -210);
                        set_motor(2, -210);
                        turnNum++;
                }
                
                if(t_junction == 2 && dark >=320 && turnNum !=3){
                        //right turn
                        set_motor(1, 180);
set_motor(2, -180);
                        Sleep(0, 500000);
                        set_motor(1, 220);
                        set_motor(2, 220);
                        Sleep(1, 600000);
                        while(dark >=300){
                                dark = cameraRead();
                                set_motor(1, -210);
                                set_motor(2, -210);
                                //Sleep(2, 600000);
                        }
                        turnNum++;


                }



                if(num >=300 & turnNum !=3){
                        //missFirst++;
                        //if(missFirst > 1){
                                //pid_left = -140;
                                //pid_right = 140;
                                //Sleep(1,300000);
                                printf("largenum\n");
                                t_junction = 1;
                //      }

                }


                if(dark >=320 && t_junction == 1 && turnNum !=3){

                        printf("Turn\n");

                        set_motor(1, 180);
                        set_motor(2, -180);
                        Sleep(0,300000);
                        set_motor(1 ,-210);
                        set_motor(2, -210);
                        Sleep(1, 500000);
                        t_junction = 2;
                        turnNum++;
                }
 //printf("pid right: %f\n", pid_left);
                //printf("pid left: %f\n", pid_right);
                if(pid_left >= 220){
                        pid_left = 220;
                }
                if(pid_right >= 220){
                        pid_right = 220;
                }
                if(pid_left <= -220){
                        pid_left = -220;
                }
                  if(pid_right <= -220){
                        pid_right = -220;
                }

                /*
                if(pid_left <= 100){
                        pid_left = 120;
                }
                if(pid_right <= 100){
                        pid_right = 120;
                }
                if(pid_left <= -100){
                        pid_left = -120;
                }
                if(pid_right <= -100){
                        pid_right = -120;
                }*/

//              printf("pidLeft: %f\n", pid_left);
//              printf("pidRIght: %f\n", pid_right);
                set_motor(1, (int)pid_left);
                set_motor(2, -(int)pid_right);

 }

        set_motor(1, 0);
        set_motor(2, 0);
return 0;
}
