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


#include "4WD_MOTO.h"

typedef enum motor {
MOTOR_A = 1, //right front
MOTOR_B = 2, //right rear
MOTOR_C = 3, //left front
MOTOR_D = 4, //left rear
}motor_e;

//car is intialize to go straight forward with speed 50

static unsigned int pol_a = 0, pol_b = 0,pol_c = 0, pol_d = 0;
static unsigned int dir_a = 0, dir_b = 0,dir_c = 1, dir_d = 1;
static unsigned int speed_a = 50, speed_b = 50,speed_c = 50, speed_d = 50;

static timer timer_a;
static timer timer_b;
static timer timer_c;
static timer timer_d;

static gpio counter_a;
static gpio counter_b;
static gpio counter_c;
static gpio counter_d;

static gpio gpio_a;
static gpio gpio_b;
static gpio gpio_c;
static gpio gpio_d;


unsigned int init_ardumoto(){
	//initialize the timer module 2,3,4,5
    timer_a = timer_open_device(2);
    timer_b = timer_open_device(3);
	timer_c = timer_open_device(4);
	timer_d = timer_open_device(5);
	//link the pwm to output
    set_pin(PWM_A_PIN, PWM2);
    set_pin(PWM_B_PIN, PWM3);
	set_pin(PWM_C_PIN, PWM4);
	set_pin(PWM_D_PIN, PWM5);
	//link the FG of automoto to input
    set_pin(FG_A_PIN, TIMER_IC2);
    set_pin(FG_B_PIN, TIMER_IC3);
	set_pin(FG_C_PIN, TIMER_IC4);
	set_pin(FG_D_PIN, TIMER_IC5);

    gpio_a = gpio_open(DIR_A_PIN);
    gpio_b = gpio_open(DIR_B_PIN);
	gpio_c = gpio_open(DIR_C_PIN);
	gpio_d = gpio_open(DIR_D_PIN);

    counter_a = gpio_open(FG_A_PIN);
    counter_b = gpio_open(FG_B_PIN);
	counter_c = gpio_open(FG_C_PIN);
	counter_d = gpio_open(FG_D_PIN);

    gpio_set_direction(gpio_a, GPIO_OUT);
    gpio_set_direction(gpio_b, GPIO_OUT);
	gpio_set_direction(gpio_c, GPIO_OUT);
	gpio_set_direction(gpio_d, GPIO_OUT);

    gpio_set_direction(counter_a, GPIO_IN);
    gpio_set_direction(counter_b, GPIO_IN);
    gpio_set_direction(counter_c, GPIO_IN);
    gpio_set_direction(counter_d, GPIO_IN);

    stop_all();

    return 0;
}

float distance(){
	//reduction ratio is 45:1
	//one round output 45*6 pulse
	//diameter of tyre is 65mm
	u32 distance_a, distance_b, distance_c, distance_d;
	float distance;
	distance_a = get_count(MOTOR_A);
	distance_b = get_count(MOTOR_B);
	distance_c = get_count(MOTOR_C);
	distance_d = get_count(MOTOR_D);
	distance = (distance_a/(45*45*6) + distance_b/(45*45*6) + \
			distance_c/(45*45*6) + distance_d/(45*45*6)) * 6.5;
	xil_printf("Car has moved %f cm.", distance);
	return distance;
}

void configure_polar(unsigned int motor, unsigned int polarity){
    if (motor == MOTOR_A) {
        pol_a = polarity;
    }else if (motor == MOTOR_B) {
        pol_b = polarity;
	}else if (motor == MOTOR_C) {
        pol_c = polarity;
    }else if (motor == MOTOR_D) {
        pol_d = polarity;
    }
}

void set_direction(unsigned int motor, unsigned int direction){
    if (motor == MOTOR_A){
        dir_a = direction;
    }
    else if (motor == MOTOR_B){
        dir_b = direction;
    }
	else if (motor == MOTOR_C){
        dir_c = direction;
    }
    else if (motor == MOTOR_D){
        dir_d = direction;
    }
}

void set_speed(unsigned int motor, unsigned int speed){
    if (motor == MOTOR_A) {
        speed_a = speed;
    }else if (motor == MOTOR_B) {
        speed_b = speed;
    }else if (motor == MOTOR_C) {
        speed_c = speed;
    }else if (motor == MOTOR_D) {
        speed_d = speed;
    }
}

void run(unsigned int motor){
    if (motor == MOTOR_A) {
        gpio_write(gpio_a, dir_a);
        timer_pwm_generate(timer_a, DEFAULT_PERIOD, 
                           speed_a*DEFAULT_PERIOD/100);
    }else if(motor == MOTOR_B) {
        gpio_write(gpio_b, dir_b);
        timer_pwm_generate(timer_b, DEFAULT_PERIOD, 
                           speed_b*DEFAULT_PERIOD/100);
    }else if(motor == MOTOR_C) {
        gpio_write(gpio_c, dir_c);
        timer_pwm_generate(timer_c, DEFAULT_PERIOD, 
                           speed_c*DEFAULT_PERIOD/100);
    }else if(motor == MOTOR_D) {
        gpio_write(gpio_d, dir_d);
        timer_pwm_generate(timer_d, DEFAULT_PERIOD, 
                           speed_d*DEFAULT_PERIOD/100);
    }
}

void run_all(){
	run(1);
	run(2);
	run(3);
	run(4);
}

void stop(unsigned int motor){
    if (motor == MOTOR_A) {
        timer_pwm_generate(timer_a, DEFAULT_PERIOD, DEFAULT_PERIOD-1);
    }else if(motor == MOTOR_B) {
        timer_pwm_generate(timer_b, DEFAULT_PERIOD, DEFAULT_PERIOD-1);
    }else if(motor == MOTOR_C) {
        timer_pwm_generate(timer_c, DEFAULT_PERIOD, DEFAULT_PERIOD-1);
    }else if(motor == MOTOR_D) {
        timer_pwm_generate(timer_d, DEFAULT_PERIOD, DEFAULT_PERIOD-1);
    }
}

void stop_all(){
	stop(1);
	stop(2);
	stop(3);
	stop(4);
}

void move_forward(unsigned int speed){
	set_direction(1,0);
	set_direction(2,0);
	set_direction(3,1);
	set_direction(4,1);
	set_speed(1,speed);
	set_speed(2,speed);
	set_speed(3,speed);
	set_speed(4,speed);
	run_all();
}

void move_backward(unsigned int speed){
	set_direction(1,1);
	set_direction(2,1);
	set_direction(3,0);
	set_direction(4,0);
	set_speed(1,speed);
	set_speed(2,speed);
	set_speed(3,speed);
	set_speed(4,speed);
	run_all();
}

void move_left(int status){
	if (status == STATUS_A){
		set_direction(1,1);
		set_direction(2,1);
		set_direction(3,0);
		set_direction(4,0);
		run(1);
		run(2);
		stop(3);
		stop(4);
	}
	else if(status == STATUS_B){
		set_direction(1,1);
		set_direction(2,1);
		set_direction(3,1);
		set_direction(4,1);
		run_all();
	}
}

void move_right(int status){
	if (status == STATUS_A){
		set_direction(1,1);
		set_direction(2,1);
		set_direction(3,0);
		set_direction(4,0);
		stop(1);
		stop(2);
		run(3);
		run(4);
	}
	else if(status == STATUS_B){
		set_direction(1,0);
		set_direction(2,0);
		set_direction(3,0);
		set_direction(4,0);
		run_all();
	}
}




