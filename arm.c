/*
     ____ __     ____   ___    ____ __         (((((()
    | |_  \ \  /   ) ) | |  ) | |_  \ \  /  \(@)- /
    |_|__  \_\/  __)_) |_|_/  |_|__  \_\/   /(@)- \
                                               ((())))
 *//**
 *  \file  
 *  \brief  
 *  \author  
 *  \copyright  
 */
#include <string.h>
#include <stdio.h>
#include "ev3.h"
#include "ev3_port.h"
#include "ev3_sensor.h"
#include "ev3_tacho.h"
#include "balls.h"
#include "sensors.h"
#include "movements.h"

// WIN32 /////////////////////////////////////////
#ifdef __WIN32__

#include <windows.h>

// UNIX //////////////////////////////////////////
#else

#include <unistd.h>
#define Sleep( msec ) usleep(( msec ) * 1000 )

//////////////////////////////////////////////////
#endif

#define ARM_MOTOR_PORT      OUTPUT_D
#define ARM_MOTOR_EXT_PORT  EXT_PORT__NONE_
#define FLAG_MOTOR_PORT      OUTPUT_A
#define FLAG_MOTOR_EXT_PORT  EXT_PORT__NONE_
int max_speed_arm;  /* Motor maximal speed */
int max_speed_flag;
enum { A, F };
uint8_t motor_arm[ 3 ] = { DESC_LIMIT, DESC_LIMIT };

void run_forever_arm( int speed)
{
	set_tacho_speed_sp( motor_arm[ A ], speed );
	set_tacho_command_inx( motor_arm[A], TACHO_RUN_FOREVER );
}

void run_forever_flag( int speed)
{
	set_tacho_speed_sp( motor_arm[ F ], speed );
	set_tacho_command_inx( motor_arm[F], TACHO_RUN_FOREVER );
}


void arm_to_rel_pos( int arm_speed, int arm_pos)
{
	set_tacho_speed_sp( motor_arm[ A ], arm_speed );
	set_tacho_position_sp( motor_arm[ A ], arm_pos );
	set_tacho_command_inx( motor_arm[ A ], TACHO_RUN_TO_REL_POS );
}

void stop_arm( void )
{
	set_tacho_command_inx( motor_arm[A], TACHO_STOP );
}

void stop_flag( void )
{
	set_tacho_command_inx( motor_arm[F], TACHO_STOP );
}

int arm_motor_init( void )
{
	char s[ 16 ];

	if ( ev3_search_tacho_plugged_in( ARM_MOTOR_PORT, ARM_MOTOR_EXT_PORT, motor_arm + A, 0 )) {
		get_tacho_max_speed( motor_arm[ A ], &max_speed_arm );
		/* Reset the motor */
		set_tacho_command_inx( motor_arm[ A ], TACHO_RESET );
	} else {
		printf( "ARM motor (%s) is NOT found.\n", ev3_port_name( ARM_MOTOR_PORT, ARM_MOTOR_EXT_PORT, 0, s ));
		/* Inoperative without left motor */
		return ( 0 );
	}
        
        if ( ev3_search_tacho_plugged_in( FLAG_MOTOR_PORT,FLAG_MOTOR_EXT_PORT, motor_arm + F, 0 )) {
		get_tacho_max_speed( motor_arm[ F ], &max_speed_flag );
		/* Reset the motor */
		set_tacho_command_inx( motor_arm[ F ], TACHO_RESET );
	} else {
		printf( "FLAG motor (%s) is NOT found.\n", ev3_port_name( FLAG_MOTOR_PORT, FLAG_MOTOR_EXT_PORT, 0, s ));
		/* Inoperative without left motor */
		return ( 0 );
	}
	return ( 1 );
}

