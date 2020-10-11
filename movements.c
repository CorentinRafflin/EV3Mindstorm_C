/*
     ____ __     ____   ___    ____ __         (((((()
    | |_  \ \  /   ) ) | |  ) | |_  \ \  /  \(@)- /
    |_|__  \_\/  __)_) |_|_/  |_|__  \_\/   /(@)- \
                                               ((())))
 *//**
 *  \file  movements.c
 *  \brief  
 *  \author  
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "ev3.h"
#include "ev3_port.h"
#include "ev3_sensor.h"
#include "ev3_tacho.h"
#include "movements.h"
#include "sensors.h"

// WIN32 /////////////////////////////////////////
#ifdef __WIN32__

#include <windows.h>

// UNIX //////////////////////////////////////////
#else

#include <unistd.h>
#define Sleep( msec ) usleep(( msec ) * 1000 )

//////////////////////////////////////////////////
#endif

#define L_MOTOR_PORT      OUTPUT_B
#define L_MOTOR_EXT_PORT  EXT_PORT__NONE_
#define R_MOTOR_PORT      OUTPUT_C
#define R_MOTOR_EXT_PORT  EXT_PORT__NONE_


int max_speed_base;  /* Motor maximal speed */

enum { L, R };
uint8_t motor[ 3 ] = { DESC_LIMIT, DESC_LIMIT, DESC_LIMIT };  /* Sequence numbers of motors */


void run_forever( int l_speed, int r_speed )
{
	set_tacho_speed_sp( motor[ L ], l_speed );
	set_tacho_speed_sp( motor[ R ], r_speed );
	multi_set_tacho_command_inx( motor, TACHO_RUN_FOREVER );
}

void run_to_rel_pos( int l_speed, int l_pos, int r_speed, int r_pos )
{
	set_tacho_speed_sp( motor[ L ], l_speed );
	set_tacho_speed_sp( motor[ R ], r_speed );
	set_tacho_position_sp( motor[ L ], l_pos );
	set_tacho_position_sp( motor[ R ], r_pos );
	multi_set_tacho_command_inx( motor, TACHO_RUN_TO_REL_POS );
}

void run_timed( int l_speed, int r_speed, int ms )
{
	set_tacho_speed_sp( motor[ L ], l_speed );
	set_tacho_speed_sp( motor[ R ], r_speed );
	multi_set_tacho_time_sp( motor, ms );
	multi_set_tacho_command_inx( motor, TACHO_RUN_TIMED );
}

int is_running( void )
{
	FLAGS_T state = TACHO_STATE__NONE_;

	get_tacho_state_flags( motor[ L ], &state );
	if ( state != TACHO_STATE__NONE_ ) return ( 1 );
	get_tacho_state_flags( motor[ R ], &state );
	if ( state != TACHO_STATE__NONE_ ) return ( 1 );

	return ( 0 );
}

void stop( void )
{
	multi_set_tacho_command_inx( motor, TACHO_STOP );
}

int base_motors_init( void )
{
	char s[ 16 ];

	if ( ev3_search_tacho_plugged_in( L_MOTOR_PORT, L_MOTOR_EXT_PORT, motor + L, 0 )) {
		get_tacho_max_speed( motor[ L ], &max_speed_base );
		/* Reset the motor */
		set_tacho_command_inx( motor[ L ], TACHO_RESET );
	} else {
		printf( "LEFT motor (%s) is NOT found.\n", ev3_port_name( L_MOTOR_PORT, L_MOTOR_EXT_PORT, 0, s ));
		/* Inoperative without left motor */
		return ( 0 );
	}
	if ( ev3_search_tacho_plugged_in( R_MOTOR_PORT, R_MOTOR_EXT_PORT, motor + R, 0 )) {
		/* Reset the motor */
		set_tacho_command_inx( motor[ R ], TACHO_RESET );
	} else {
		printf( "RIGHT motor (%s) is NOT found.\n", ev3_port_name( R_MOTOR_PORT, R_MOTOR_EXT_PORT, 0, s ));
		/* Inoperative without right motor */
		return ( 0 );
	}
	return ( 1 );
}

void turn(float angle) {
    stop();
    //printf("I turn by (%f)", degree);
    float current_angle = read_gyro();
   
    if(angle > 0) { //turn right
        run_forever(-max_speed_base*0.1, max_speed_base*0.1);
        while (read_gyro()<=current_angle+angle) {
            
        }
    }
    else { //turn left
        run_forever(max_speed_base*0.1, -max_speed_base*0.1);
        while (read_gyro()>=current_angle+angle) {
            
        }
    }
    stop();
    
}

void forwardCm(float cm) {
    float ms = cm*166.4;
    run_timed(-max_speed_base*0.1, -max_speed_base*0.1, ms); //6 s = 55 cm
    Sleep(ms+1000);
}

void backwardCm(float cm) {
    float ms = cm*166.4;
    run_timed(max_speed_base*0.1, max_speed_base*0.1, ms); //6 s = 55 cm
    Sleep(ms+1000);
}

/*void forwardCm(float cm) {
    float last_angle = read_gyro();
    int i=0;
    int cmInt = floor(cm);
    
    for(i=0; i<=cmInt;i++) {
        run_timed(-max_speed_base*0.1, -max_speed_base*0.1, 2*83.2);
        Sleep(200);
        if(abs(read_gyro()-last_angle)>1) {
            turn(last_angle-read_gyro());
            Sleep(200);
        }
        
    }
    run_timed(-max_speed_base*0.2, -max_speed_base*0.2, 132*(cm-cmInt));
}

void backwardCm(float cm) {
    float last_angle = read_gyro();
    int i=0;
    int cmInt = floor(cm);
    
    for(i=0; i<=cmInt;i++) {
        run_timed(max_speed_base*0.2, max_speed_base*0.2, 132);
        Sleep(100);
        if(abs(read_gyro()-last_angle)>1) {
            turn(last_angle-read_gyro());
            Sleep(200);
        }      
    }
    run_timed(max_speed_base*0.2, max_speed_base*0.2, 132*(cm-cmInt));
}

*/
