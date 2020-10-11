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
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "ev3.h"
#include "ev3_port.h"
#include "ev3_sensor.h"
#include "ev3_tacho.h"
#include "balls.h"
#include "sensors.h"
#include "movements.h"
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

bool hasBall = false;

/*void scan_ball( void ) 
{
    float max_range[] = {496.0, 496.0, 496.0, 496.0, 496.0, 498.0, 498.0, 498.9, 498.9, 499.2, 499.2, 504.0, 504.0, 509.0, 506.0, 506.0, 506.0, 511.0, 511.0, 511.0, 517.0, 517.0, 517.0, 526.7, 526.7, 523.6, 523.6, 523.6, 518.0, 518.0, 518.0, 531.0, 531.0, 538.0, 538.0, 538.0, 553.8, 553.8, 553.8, 598.0, 598.0, 598.0, 607.0, 607.0, 607.0, 607.0, 603.0, 603.0, 603.0, 586.0, 586.0, 586.0, 586.0, 594.5, 594.5, 603.0, 596.2, 596.2, 585.2, 585.2, 586.0, 576.4, 576.4, 572.7, 562.2, 562.2, 554.0, 554.0, 553.8, 553.0, 553.0, 553.0, 553.0, 546.0, 546.0, 546.0, 546.0, 546.0, 546.0, 546.0, 546.0, 546.0, 551.0, 551.0, 548.5, 548.5, 548.5, 546.0, 546.0, 546.0, 546.0, 547.4, 547.4, 547.4, 551.0, 551.0, 551.0, 553.0, 553.0, 553.0, 554.0, 554.0, 554.0, 559.0, 559.0, 559.0, 561.0, 561.0, 561.0, 564.6, 564.6, 564.6, 570.0, 570.0, 570.0, 573.0, 573.0, 573.0, 578.0, 578.0, 578.0, 581.0, 581.0, 581.0, 597.0, 597.0, 597.0, 607.0, 704.8, 697.8, 652.4, 652.4, 705.0, 705.0, 712.0, 706.0, 706.0, 706.0, 705.0, 705.0, 705.0, 705.0, 713.3, 713.3, 713.3, 721.0, 721.0, 721.0, 728.0, 728.0, 728.0, 733.2, 733.2, 443.0, 443.0, 443.0, 435.0, 435.0, 435.0, 427.6, 427.6, 427.6, 425.0, 425.0, 425.0, 425.0, 426.2, 426.2, 416.0, 416.0, 416.0, 416.0, 419.2, 419.2, 415.2, 415.2, 415.2, 403.0, 403.0, 403.0, 403.0, 405.7, 405.7, 404.0, 404.0, 404.0, 404.0, 408.0, 408.0, 408.0, 412.0, 412.0, 411.0, 411.0, 411.0, 411.0, 418.0, 418.0, 418.0, 420.0, 420.0, 420.0, 427.0, 427.0, 427.0, 437.0, 437.0, 437.0, 452.8, 452.8, 452.8, 705.5, 705.5, 697.2, 697.2, 697.2, 697.2, 698.0, 698.0, 687.0, 687.0, 687.0, 687.0, 690.6, 687.4, 687.4, 680.0, 680.0, 689.0, 679.0, 679.0, 679.0, 692.2, 573.7, 573.7, 559.0, 559.0, 553.0, 553.0, 546.0, 542.0, 542.0, 542.0, 537.0, 537.0, 537.0, 535.2, 535.2, 535.2, 527.0, 527.0, 527.0, 526.4, 526.4, 526.4, 524.6, 524.6, 524.6, 523.0, 523.0, 523.0, 523.0, 523.0, 523.0, 523.0, 523.0, 523.0, 523.0, 523.0, 523.0, 523.0, 523.0, 523.0, 523.0, 524.6, 524.6, 524.6, 525.0, 525.0, 525.0, 525.0, 525.0, 525.0, 525.0, 525.0, 525.0, 530.0, 530.0, 530.0, 534.0, 534.0, 534.0, 536.0, 537.6, 537.6, 539.2, 539.2, 546.0, 546.0, 553.0, 555.0, 555.0, 563.0, 563.0, 572.0, 572.0, 574.0, 574.0, 564.4, 564.4, 564.4, 563.0, 563.0, 563.0, 563.0, 563.0, 563.0, 580.0, 580.0, 580.0, 523.0, 523.0, 523.0, 510.0, 510.0, 510.0, 502.5, 502.5, 502.5, 495.2, 495.2, 495.2, 492.0, 492.0, 492.0, 488.4, 488.4, 488.4, 483.0, 483.0, 483.0, 483.0, 483.0, 483.0, 483.0, 483.0, 483.0, 483.0, 483.0, 483.0, 483.0, 483.0, 483.0, 484.5, 483.0, 483.0, 483.0, 483.0, 483.0, 483.0, 483.0, 483.0, 483.0};
    float average_dist = 2000;
    int angle = floor(read_gyro());
    int thresold=0;
    while(average_dist>thresold && angle<359) { 
        turn(2);
        angle = floor(read_gyro());     
        average_dist=get_average_distance();
        
        if (max_range[angle]>650) {
            max_range[angle]=650;
        }
        if (angle>=143 && angle<153) {
            thresold = max_range[angle]-250; 
        }
        else if (angle>=153 && angle<=210) {
            thresold = max_range[angle]-100;
        }
        else if (angle>210 && angle<=220) {
            thresold = max_range[angle]-250;
        }
        else if (angle > 120 && angle<=142) {
            thresold = max_range[angle]-115;
        }
        else if (angle>220 && angle<240) {
            thresold = max_range[angle]-90;
        }
        else {
            thresold = max_range[angle]-90;
        }
        
        
     
        printf("-- At angle (%d), I measure (%f) and the threshold is (%d) \n", angle, average_dist, thresold);    
    }  
    
    if (angle>359) {
        reset_gyro();
        scan_ball();
    }
    
    turn(3);
    Sleep(200);
}
*/

/*
void scan_ball(void) 
{
    float currentDist = read_sonar();
    run_forever(max_speed_base, max_speed_base);
    while ( read_sonar() > currentDist-30 ) { //TODO add a timing 
        
    }
    float final_dist_cm = read_sonar()/10;
    stop();
    forwardCm(final_dist);
    catch_ball();
    turn(-90);
    
}*/
/*
bool not_a_ball(void) {
    int fov = 45;
    int dist_min = 500;
    int ecart_max = 20;
    int angle = floor(read_gyro());
    if ((angle%180 > 90-fov)&&(angle%180 < 90+fov)) {
        printf("perpendiculaire:   ");
        float dist = get_average_distance();
        printf("%f\n", dist);
        if (dist < dist_min) {
            return false;
        }
        else {
            return true;
        }
    }
    else if ((angle%180 > -fov)&&(angle%180 < fov)) {
        printf("perpendiculaire:   ");
        float dist = get_average_distance();
        printf("%f\n", dist);
        if (dist < dist_min) {
            return false;
        }
        else {
            return true;
        }
    }
    else {
        printf("diagonale:    ");
        int i;
        float ecart=0;
        float previous_dist = read_sonar();
        for (i=0; i<100; i++) {
            float dist = read_sonar();
            if (abs(dist - previous_dist) > ecart) {
                ecart = abs(dist-previous_dist);
            }
            previous_dist = dist;
        }
        printf("%f\n", ecart);
        if (ecart > ecart_max) {
            return true;
        }
        else {
            return false;
        }
    }
}

void scan_ball(void) 
{
    while (not_a_ball()) {
        turn(1);
        Sleep(500);
    }
    printf("ball found");
}*/



void test_scan(void) {
    int angle = floor(read_gyro());
    while(angle<360) {      
        angle = floor(read_gyro());     
        
        printf("\n %d %f", angle, get_average_distance());
        Sleep(200);
        turn(1);
        Sleep(200);
    }   
}

bool got_ball(void) {
    char * color = read_color();
    
    if (strcmp(color,"BLACK")==0) {
        Sleep(20);
        if (strcmp(color, "BLACK")==0) {
            Sleep(20);
            return false;
        }
    }

    if(strcmp(color,"?")!=0) {
        Sleep(3);
        if(strcmp(read_color(), color)==0) {
           Sleep(3);
           if(strcmp(read_color(), color)==0) {
               Sleep(2);
               if(strcmp(read_color(), color)==0) {                                         
                        printf("Find something with color (%s) \n", color);
                        return true;                                                       
               }
           }
       }     
   }
   return false; 
}

bool got_something(void)
{
    char * color = read_color();
    if(strcmp(color,"?")!=0) {
        return true;
    }
    return false;
}



void catch_ball(void) 
{
    run_forever_arm(-max_speed_arm*0.05);
    int debut_catch=time(NULL);
    int now_catch;
    hasBall = false;
    while( hasBall==false && (now_catch-debut_catch<5) ) {
        now_catch=time(NULL);
        hasBall=got_ball();
    }
    while ( hasBall==false && got_something()==false) {
    }
    
    if (hasBall==true) {
        hasBall=got_ball();
    }
    printf("hasBall =%d \n", hasBall );
    stop_arm();
    if (hasBall==false) {
        arm_to_rel_pos(max_speed_arm, -20*870/1000);
    }
    Sleep(200);
}

void go_catch_ball(void) //after scan_ball
{
    printf("Let's go_catch_ball \n");
    float average_dist = get_average_distance();
    int angle = floor(read_gyro());
 
    turn(180);
    Sleep(2000);
   
    float max_range[] = {496.0, 496.0, 496.0, 496.0, 496.0, 498.0, 498.0, 498.9, 498.9, 499.2, 499.2, 504.0, 504.0, 509.0, 506.0, 506.0, 506.0, 511.0, 511.0, 511.0, 517.0, 517.0, 517.0, 526.7, 526.7, 523.6, 523.6, 523.6, 518.0, 518.0, 518.0, 531.0, 531.0, 538.0, 538.0, 538.0, 553.8, 553.8, 553.8, 598.0, 598.0, 598.0, 607.0, 607.0, 607.0, 607.0, 603.0, 603.0, 603.0, 586.0, 586.0, 586.0, 586.0, 594.5, 594.5, 603.0, 596.2, 596.2, 585.2, 585.2, 586.0, 576.4, 576.4, 572.7, 562.2, 562.2, 554.0, 554.0, 553.8, 553.0, 553.0, 553.0, 553.0, 546.0, 546.0, 546.0, 546.0, 546.0, 546.0, 546.0, 546.0, 546.0, 551.0, 551.0, 548.5, 548.5, 548.5, 546.0, 546.0, 546.0, 546.0, 547.4, 547.4, 547.4, 551.0, 551.0, 551.0, 553.0, 553.0, 553.0, 554.0, 554.0, 554.0, 559.0, 559.0, 559.0, 561.0, 561.0, 561.0, 564.6, 564.6, 564.6, 570.0, 570.0, 570.0, 573.0, 573.0, 573.0, 578.0, 578.0, 578.0, 581.0, 581.0, 581.0, 597.0, 597.0, 597.0, 607.0, 704.8, 697.8, 652.4, 652.4, 705.0, 705.0, 712.0, 706.0, 706.0, 706.0, 705.0, 705.0, 705.0, 705.0, 713.3, 713.3, 713.3, 721.0, 721.0, 721.0, 728.0, 728.0, 728.0, 733.2, 733.2, 443.0, 443.0, 443.0, 435.0, 435.0, 435.0, 427.6, 427.6, 427.6, 425.0, 425.0, 425.0, 425.0, 426.2, 426.2, 416.0, 416.0, 416.0, 416.0, 419.2, 419.2, 415.2, 415.2, 415.2, 403.0, 403.0, 403.0, 403.0, 405.7, 405.7, 404.0, 404.0, 404.0, 404.0, 408.0, 408.0, 408.0, 412.0, 412.0, 411.0, 411.0, 411.0, 411.0, 418.0, 418.0, 418.0, 420.0, 420.0, 420.0, 427.0, 427.0, 427.0, 437.0, 437.0, 437.0, 452.8, 452.8, 452.8, 705.5, 705.5, 697.2, 697.2, 697.2, 697.2, 698.0, 698.0, 687.0, 687.0, 687.0, 687.0, 690.6, 687.4, 687.4, 680.0, 680.0, 689.0, 679.0, 679.0, 679.0, 692.2, 573.7, 573.7, 559.0, 559.0, 553.0, 553.0, 546.0, 542.0, 542.0, 542.0, 537.0, 537.0, 537.0, 535.2, 535.2, 535.2, 527.0, 527.0, 527.0, 526.4, 526.4, 526.4, 524.6, 524.6, 524.6, 523.0, 523.0, 523.0, 523.0, 523.0, 523.0, 523.0, 523.0, 523.0, 523.0, 523.0, 523.0, 523.0, 523.0, 523.0, 523.0, 524.6, 524.6, 524.6, 525.0, 525.0, 525.0, 525.0, 525.0, 525.0, 525.0, 525.0, 525.0, 530.0, 530.0, 530.0, 534.0, 534.0, 534.0, 536.0, 537.6, 537.6, 539.2, 539.2, 546.0, 546.0, 553.0, 555.0, 555.0, 563.0, 563.0, 572.0, 572.0, 574.0, 574.0, 564.4, 564.4, 564.4, 563.0, 563.0, 563.0, 563.0, 563.0, 563.0, 580.0, 580.0, 580.0, 523.0, 523.0, 523.0, 510.0, 510.0, 510.0, 502.5, 502.5, 502.5, 495.2, 495.2, 495.2, 492.0, 492.0, 492.0, 488.4, 488.4, 488.4, 483.0, 483.0, 483.0, 483.0, 483.0, 483.0, 483.0, 483.0, 483.0, 483.0, 483.0, 483.0, 483.0, 483.0, 483.0, 484.5, 483.0, 483.0, 483.0, 483.0, 483.0, 483.0};
    
    float actual_max_range = max_range[angle];    
    
    float cm = (average_dist/10);
        
    if(cm>5 && angle>130 && angle<230) {
        cm=5;
    } 
    else if (cm>15) {
        cm=15;
    }

    forwardCm(cm);
    catch_ball();
    
    backwardCm(cm);
    
    if (angle>0) {
        while(read_gyro()>0) {
            run_forever(max_speed_base*0.05, -max_speed_base*0.05);
        }
    }
    else {
        while(read_gyro()<0) {
            run_forever(-max_speed_base*0.05, max_speed_base*0.05);
        }
    }
    stop();
    //turn(180-angle);
    Sleep(1000);   
}

void test_catch_ball(void) {
    run_forever_arm(-max_speed_arm*0.05);
    while( got_ball()==false) {
    }
    stop_arm();
}

    
