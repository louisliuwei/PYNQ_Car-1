/******************************************************************************
 *  Copyright (c) 2019, Xilinx, Inc.
 *  All rights reserved.
 * 
 *  Redistribution and use in source and binary forms, with or without 
 *  modification, are permitted provided that the following conditions are met:
 *
 *  1.  Redistributions of source code must retain the above copyright notice, 
 *     this list of conditions and the following disclaimer.
 *
 *  2.  Redistributions in binary form must reproduce the above copyright 
 *      notice, this list of conditions and the following disclaimer in the 
 *      documentation and/or other materials provided with the distribution.
 *
 *  3.  Neither the name of the copyright holder nor the names of its 
 *      contributors may be used to endorse or promote products derived from 
 *      this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 *  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, 
 *  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR 
 *  PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR 
 *  CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, 
 *  EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, 
 *  PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 *  OR BUSINESS INTERRUPTION). HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, 
 *  WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR 
 *  OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF 
 *  ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *****************************************************************************/
/******************************************************************************
 *
 *
 * @file arduino_automoto.c
 *
 * IOP code (MicroBlaze) for automoto SEN:FIT0441.
 * www.dfrobot.com.cn/goods-1270.html
 *
 * FIT0441 is controlled by both GPIO and PWM
 *
 * There are four automotos under control to drive a car
 * auotmoto a: right front
 * auotmoto b: right rear
 * automoto c: left sacro-anterior / left front
 * auotmoto d: left rear
 *
 * Hardware version 2.2.
 * 
 *
 *
 * <pre>
 * MODIFICATION HISTORY:
 *
 * Ver   Who  Date     Changes
 * ----- --- ------- -----------------------------------------------
 * 1.00a zc  1/21/19 release
 * 
 *
 * </pre>
 *
 *****************************************************************************/


#include "xio_switch.h"
#include "gpio.h"
#include "timer.h"
#include "xtmrctr.h"
#include "4WD_MOTO.h"

#define DEFAULT_PERIOD 625998
#define DEFAULT_DUTY 312998

//#define PWM_A_PIN 6
//#define PWM_B_PIN 9
//#define PWM_C_PIN 10
//#define PWM_D_PIN 11
//
//#define DIR_A_PIN 7
//#define DIR_B_PIN 8
//#define DIR_C_PIN 12
//#define DIR_D_PIN 13
//
//#define FG_A_PIN 4
//#define FG_B_PIN 5
//#define FG_C_PIN 18
//#define FG_D_PIN 19
unsigned char PWM_LEFT_PIN=6, PWM_RIGHT_PIN=5;
unsigned char DIR_LEFT_PIN=7, DIR_RIGHT_PIN=4;
unsigned char A_CHA_PIN=3, A_CHB_PIN=2, B_CHA_PIN=9, B_CHB_PIN=8;
unsigned char C_CHA_PIN=11, C_CHB_PIN=10, D_CHA_PIN=13, D_CHB_PIN=12;

#define RATIO (45*45*6)

typedef enum motor {
MOTOR_LEFT = 1, //Left motor
MOTOR_RIGHT = 2, //Right motor
}motor_e;

//car is intialize to go straight forward with speed 50

static unsigned int dir_left = 0, dir_right = 0;
static unsigned int speed_left = 50, speed_right = 50;

static timer timer_left;
static timer timer_right;
static timer timer_e;
static timer timer_f;

static gpio gpio_left;
static gpio gpio_right;


float distance();
void stop_all();
unsigned int init_ardumoto(){
	//initialize the timer module 0,1,2,3,4,5

    timer_left  = timer_open_device(0);
    timer_right = timer_open_device(1);
//	timer_e = timer_open_device(2);
//	timer_f = timer_open_device(3);
//	timer_open_capture(timer_e);
//	timer_open_capture(timer_f);
	//link the pwm to output
    set_pin(PWM_LEFT_PIN,  PWM0);
    set_pin(PWM_RIGHT_PIN, PWM1);
	//link the FG of automoto to input
//    set_pin(FG_A_PIN, TIMER_IC1);
//    set_pin(FG_B_PIN, TIMER_IC6);
//	set_pin(FG_C_PIN, TIMER_IC2);
//	set_pin(FG_D_PIN, TIMER_IC7);

    gpio_left = gpio_open(DIR_LEFT_PIN);
    gpio_right = gpio_open(DIR_RIGHT_PIN);

    gpio_set_direction(gpio_left, GPIO_OUT);
    gpio_set_direction(gpio_right, GPIO_OUT);

    stop_all();

    return 0;
}

float get_velocity(){
	//reduction ratio is 45:1
	//one round output 45*6 pulse
	//diameter of tyre is 65mm
	u32 v_a, v_b, v_c, v_d;
	float v;
	v_a = timer_get_pulsewidth(timer_e,0);
	v_b = timer_get_pulsewidth(timer_e,1);
	v_c = timer_get_pulsewidth(timer_f,0);
	v_d = timer_get_pulsewidth(timer_f,1);
	v = (v_a/RATIO + v_b/RATIO + v_c/RATIO + v_d/RATIO) * (6.5*3.14/4);
	//xil_printf("Car has moved %f cm.", distance);
	return v;
}

static void set_direction(unsigned int motor, unsigned int direction){
    if (motor == MOTOR_LEFT){
        dir_left = direction;
    }
    else if (motor == MOTOR_RIGHT){
        dir_right = direction;
    }
}

void set_speed(unsigned int motor, unsigned int speed){
    if (motor == MOTOR_LEFT) {
        speed_left = speed;
    }else if (motor == MOTOR_RIGHT) {
        speed_right = speed;
    }
}

void run(unsigned int motor){
    if (motor == MOTOR_LEFT) {
        gpio_write(gpio_left, dir_left);
        timer_pwm_generate(timer_left, DEFAULT_PERIOD,
                           speed_left*DEFAULT_PERIOD/100);
    }else if(motor == MOTOR_RIGHT) {
        gpio_write(gpio_right, dir_right);
        timer_pwm_generate(timer_right, DEFAULT_PERIOD,
                           speed_right*DEFAULT_PERIOD/100);
    }
}

void run_all(){
	run(MOTOR_LEFT);
	run(MOTOR_RIGHT);
}

void stop(unsigned int motor){
    if (motor == MOTOR_LEFT) {
        timer_pwm_generate(timer_left, DEFAULT_PERIOD, DEFAULT_PERIOD-1);
    }else if(motor == MOTOR_RIGHT) {
        timer_pwm_generate(timer_right, DEFAULT_PERIOD, DEFAULT_PERIOD-1);
    }
}

void stop_all(){
	stop(MOTOR_LEFT);
	stop(MOTOR_RIGHT);
}

void move_forward(unsigned int speed){
	set_direction(MOTOR_LEFT,1);
	set_direction(MOTOR_RIGHT,1);
	set_speed(MOTOR_LEFT,speed);
	set_speed(MOTOR_RIGHT,speed);
	run_all();
}

void move_backward(unsigned int speed){
	set_direction(MOTOR_LEFT,0);
	set_direction(MOTOR_RIGHT,0);
	set_speed(MOTOR_LEFT,speed);
	set_speed(MOTOR_RIGHT,speed);
	run_all();
}

void move_left(int status, unsigned int speed){
	if (status == STATUS_A){
		set_direction(MOTOR_LEFT,1);
		set_direction(MOTOR_RIGHT,1);

		set_speed(MOTOR_LEFT,speed);
		set_speed(MOTOR_RIGHT,speed);

		run(MOTOR_RIGHT);
		stop(MOTOR_LEFT);
	}
	else if(status == STATUS_B){
		set_direction(MOTOR_LEFT,1);
		set_direction(MOTOR_RIGHT,0);

		set_speed(MOTOR_LEFT,speed);
		set_speed(MOTOR_RIGHT,speed);

		run_all();
	}
}

void move_right(int status, unsigned int speed){
	if (status == STATUS_A){
		set_direction(MOTOR_LEFT,1);
		set_direction(MOTOR_RIGHT,1);

		set_speed(MOTOR_LEFT,speed);
		set_speed(MOTOR_RIGHT,speed);

		stop(MOTOR_RIGHT);
		run(MOTOR_LEFT);
	}
	else if(status == STATUS_B){
		set_direction(MOTOR_LEFT,0);
		set_direction(MOTOR_RIGHT,1);

		set_speed(MOTOR_LEFT,speed);
		set_speed(MOTOR_RIGHT,speed);

		run_all();
	}
}
