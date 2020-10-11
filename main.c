/*
     ____ __     ____   ___    ____ __         (((((()
    | |_  \ \  /   ) ) | |  ) | |_  \ \  /  \(@)- /
    |_|__  \_\/  __)_) |_|_/  |_|__  \_\/   /(@)- \
                                               ((())))
 *//**
 *  \file  main.c
 *  \brief  
 *  \author 
 */

#include <stdio.h>
#include "coroutine.h"
#include "ev3.h"
#include "ev3_port.h"
#include "ev3_sensor.h"
#include "ev3_tacho.h"
#include "movements.h"
#include "messages.h"
#include "sensors.h"
#include "balls.h"
#include "arm.h"
// WIN32 /////////////////////////////////////////
#ifdef __WIN32__

#include <windows.h>

// UNIX //////////////////////////////////////////
#else

#include <unistd.h>
#define Sleep( msec ) usleep(( msec ) * 1000 )

//////////////////////////////////////////////////
#endif

int ball_scored;

void fire(void);
void fire_beginning(void);


int main( void )
{
	printf( "Waiting the EV3 brick online...\n" );
	if ( ev3_init() < 1 ) return ( 1 );

	printf( "*** ( EV3 ) Hello! ***\n" );
	ev3_sensor_init();
	ev3_tacho_init();

	if (base_motors_init()==0) {
            printf( "base_motors_init error \n" );
            return(0);
	}
        
        if (arm_motor_init()==0) {
            printf( "arm_motor_init error \n" );
            return(0);
        }
        
        if (sensors_init()==0) { //never happen
            printf("sensors_init error \n");
            return(0);
        }
       
        /*run_forever_flag(max_speed_flag*0.05);
        
        ball_scored=0;
      
        fire_beginning();   
        forwardCm(18);
        while(ball_scored<4) {
            while(hasBall==false) {
                scan_ball();
                go_catch_ball();
                reset_gyro();
            }
            backwardCm(20);
            fire();
            forwardCm(20);
        }
      
     
        stop_flag();
        */
       
        scan_ball();
        
        
        
	ev3_uninit();
	printf( "*** ( EV3 ) Bye! ***\n" );

	return ( 0 );
}

void fire_beginning(void)
{
    forwardCm(15);
    Sleep(2000);
    fire(); //fire the first ball
    catch_ball();
    if (hasBall==true) {
        fire(); //fire the second ball
    }
    //forwardCm(10); //go to scan zone
}

void fire(void) {
    arm_to_rel_pos(max_speed_arm, -60*870/1000);  // -60*870/1000
    Sleep(500); //need to implement it in a thread but for now we let the time for the fire
    ball_scored+=1;
    hasBall=false;
}



