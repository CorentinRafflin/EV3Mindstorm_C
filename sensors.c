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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ev3.h"
#include "ev3_port.h"
#include "ev3_tacho.h"
#include "ev3_sensor.h"
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
const char const *color[] = { "?", "BLACK", "BLUE", "GREEN", "YELLOW", "RED", "WHITE", "BROWN" };
#define COLOR_COUNT  (( int )( sizeof( color ) / sizeof( color[ 0 ])))

int i;
uint8_t sn;
FLAGS_T state;
uint8_t sn_touch;
uint8_t sn_gyro;
uint8_t sn_color;
uint8_t sn_sonar;

char s[ 256 ];
int val;
float value;

  
static bool _check_pressed( uint8_t sn )
{
  int val;

  if ( sn == SENSOR__NONE_ ) {
    return ( ev3_read_keys(( uint8_t *) &val ) && ( val & EV3_KEY_UP ));
  }
  return ( get_sensor_value( 0, sn, &val ) && ( val != 0 ));
}

int sensors_init( void )
{
	
        uint32_t n, ii;
        ev3_sensor_init();
        
        printf( "Found sensors:\n" );
        for ( i = 0; i < DESC_LIMIT; i++ ) {
          if ( ev3_sensor[ i ].type_inx != SENSOR_TYPE__NONE_ ) {
            printf( "  type = %s\n", ev3_sensor_type( ev3_sensor[ i ].type_inx ));
            printf( "  port = %s\n", ev3_sensor_port_name( i, s ));
            if ( get_sensor_mode( i, s, sizeof( s ))) {
              printf( "  mode = %s\n", s );
            }
            if ( get_sensor_num_values( i, &n )) {
              for ( ii = 0; ii < n; ii++ ) {
                if ( get_sensor_value( ii, i, &val )) {
                  printf( "  value%d = %d\n", ii, val );
                }
              }
            }
          }
        }       
        
        //Set gyro to mode GYRO-ANG
        reset_gyro();
        
        //set color to mode COL-COLOR
        if ( ev3_search_sensor( LEGO_EV3_COLOR, &sn_color, 0 )) {
            printf( "COLOR sensor is found, changing mode...\n" );
            if (set_sensor_mode( sn_color, "COL-COLOR" )==0) {
                printf("unable to set color sensor mode to COL_COLOR");
            }
        }
        
        //set sonar to mode US-DIST-CM
        if ( ev3_search_sensor( LEGO_EV3_COLOR, &sn_sonar, 0 )) {
            printf( "SONAR sensor is found, changing mode...\n" );
            if (set_sensor_mode( sn_sonar, "US-DIST-CM" )==0) {
                printf("unable to set sonar sensor mode to US-DIST-CM");
            }
        }
        
	return ( 1 );
        
       
}



char* read_color( void ) 
{
    
    if ( ev3_search_sensor( LEGO_EV3_COLOR, &sn_color, 0 )) {
        //printf( "COLOR sensor is found, reading COLOR...\n" );
                
        if ( !get_sensor_value( 0, sn_color, &val ) || ( val < 0 ) || ( val >= COLOR_COUNT )) {
          val = 0;
        }
        //printf( "\r(%s) \n", color[ val ]);
        fflush( stdout );
        return (char*) color[ val ];
    }
    return (0);
}


float read_gyro( void ) 
{
    
    if ( ev3_search_sensor( LEGO_EV3_GYRO, &sn_gyro, 0 )) {
        //printf( "GYRO sensor is found, reading value...\n" );
                
        if ( !get_sensor_value( 0, sn_gyro, &val ) ) {
          val = 0;
        }
        
        //printf( "\r(%d) \n", val);
        fflush( stdout );
        return (float) val;
    }
    return (0);
}

float read_sonar(void) 
{
    if (ev3_search_sensor(LEGO_EV3_US, &sn_sonar,0)){
      //printf("SONAR found, reading sonar...\n");
      if ( !get_sensor_value0(sn_sonar, &value )) {
        value = 0;
      }
      //printf( "\r(%f) \n", value);
      fflush( stdout );
    }
    
    return value;
}

float get_average_distance(void)
{
    int i;
    float average_dist=0;
    for(i=0; i<100;i++) {
        average_dist=average_dist+read_sonar();
    }
    return average_dist/100;
}


void reset_gyro(void) {
    if ( ev3_search_sensor( LEGO_EV3_GYRO, &sn_gyro, 0 )) {
        printf( "GYRO sensor is found, changing mode...\n" );
        set_sensor_mode( sn_gyro, "GYRO-CAL");
        if (set_sensor_mode( sn_gyro, "GYRO-ANG" )==0) {
            printf("unable to set mode to GYRO-ANG \n");
        }
    }
    Sleep(100);
}