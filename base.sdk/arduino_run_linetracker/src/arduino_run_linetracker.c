/*
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
 * @file arduino_getsture.c
 *
 * IOP code (MicroBlaze) for DFRotbot Gesture module.
 * The module has to be connected to an arduino interface
 * via a shield socket.
 *
 * <pre>
 * MODIFICATION HISTORY:
 *
 * Ver   Who    Date     Changes
 * ----- ---    ------- -----------------------------------------------
 * 1.00a zc/ljh 01/22/19 release
 *
 * </pre>
 *
 *****************************************************************************/

#include "4WD_MOTO.h"
#include "SEN0147.h"
#include <circular_buffer.h>
#include "sleep.h"

// Work on 8-bit mode
#define CONFIG_IOP_SWITCH           0x1
#define STOP                        0x3
#define MOVE                        0x5
#define VELOCITY                    0x7
#define SET_PWM						0x9
#define SEND_DATA                   0XB

int channel_left;
int channel_right;


extern unsigned int PWM_A_PIN, PWM_B_PIN, PWM_C_PIN, PWM_D_PIN;
extern unsigned int DIR_A_PIN, DIR_B_PIN, DIR_C_PIN, DIR_D_PIN;
extern unsigned int FG_A_PIN, FG_B_PIN, FG_C_PIN, FG_D_PIN;

void initialize(){
// SysMon Initialize
	SysMonConfigPtr = XSysMon_LookupConfig(SYSMON_DEVICE_ID);
	if(SysMonConfigPtr == NULL)
		xil_printf("SysMon LookupConfig failed.\n\r");
	xStatus = XSysMon_CfgInitialize(SysMonInstPtr, SysMonConfigPtr,
                                    SysMonConfigPtr->BaseAddress);
	if(XST_SUCCESS != xStatus)
		xil_printf("SysMon CfgInitialize failed\r\n");
	// Clear the old status
	XSysMon_GetStatus(SysMonInstPtr);
}

u32 read_adc(int channel){
	while ((XSysMon_GetStatus(SysMonInstPtr) &
                        XSM_SR_EOS_MASK) != XSM_SR_EOS_MASK);
	xadc_raw_value = XSysMon_GetAdcData(SysMonInstPtr, channel);
	return xadc_raw_value;
}

float read_analog(int channel){
	while ((XSysMon_GetStatus(SysMonInstPtr) &
                        XSM_SR_EOS_MASK) != XSM_SR_EOS_MASK);
	xadc_voltage = (float)(XSysMon_GetAdcData(SysMonInstPtr, channel)*V_Conv);
	return xadc_voltage;
}

void reset(){
// SysMon Initialize
	SysMonConfigPtr = XSysMon_LookupConfig(SYSMON_DEVICE_ID);
	if(SysMonConfigPtr == NULL)
		xil_printf("SysMon LookupConfig failed.\n\r");
	xStatus = XSysMon_CfgInitialize(SysMonInstPtr,
					SysMonConfigPtr, SysMonConfigPtr->BaseAddress);
	if(XST_SUCCESS != xStatus)
		xil_printf("SysMon CfgInitialize failed.\r\n");
	// Clear the old status
	XSysMon_GetStatus(SysMonInstPtr);
}

int set_LTpins(int pin){
	//set the pins of sensor
	if (pin == 0) return CHANNEL_A0;
	else if (pin == 1) return CHANNEL_A1;
	else if (pin == 2) return CHANNEL_A2;
	else if (pin == 3) return CHANNEL_A3;
	else if (pin == 4) return CHANNEL_A4;
	else if (pin == 5) return CHANNEL_A5;
	return 0;
}

int main()
{
	int cmd, direction, speed;
	int which, period, duty;
	float v;

	initialize();

	while(1){
		// wait and store valid command
		while((MAILBOX_CMD_ADDR & 0x01)==0);
		cmd = MAILBOX_CMD_ADDR;

		switch(cmd){
			  case CONFIG_IOP_SWITCH:
				  // read new pin configuration
				  PWM_A_PIN = MAILBOX_DATA(0);
				  PWM_B_PIN = MAILBOX_DATA(1);
				  PWM_C_PIN = MAILBOX_DATA(2);
				  PWM_D_PIN = MAILBOX_DATA(3);
				  DIR_A_PIN = MAILBOX_DATA(4);
				  DIR_B_PIN = MAILBOX_DATA(5);
				  DIR_C_PIN = MAILBOX_DATA(6);
				  DIR_D_PIN = MAILBOX_DATA(7);
				  FG_A_PIN  = MAILBOX_DATA(8);
				  FG_B_PIN  = MAILBOX_DATA(9);
				  FG_C_PIN  = MAILBOX_DATA(10);
				  FG_D_PIN  = MAILBOX_DATA(11);
				  channel_left = set_LTpins(MAILBOX_DATA(12));
				  channel_right = set_LTpins(MAILBOX_DATA(13));
				  init_ardumoto();
				  MAILBOX_CMD_ADDR = 0x0;
				  break;

			  case STOP:
				  stop_all();
				  MAILBOX_CMD_ADDR = 0x0;
				  break;

			  case MOVE:
				  direction = MAILBOX_DATA(0);
				  speed = MAILBOX_DATA(1);
				  switch (direction) {
				  	  case 0://move forward
				  		  move_forward(speed);
				  		  break;
				  	  case 1://move back
				  		  move_backward(speed);
				  		  break;
				  	  case 2://move left stop
				  		  move_left(STATUS_A, speed);
				  		  break;
				  	  case 3://move right stop
				  		  move_right(STATUS_A, speed);
				  		  break;
				  	  case 4://left reverse
				  		  move_left(STATUS_B, speed);
				  		  break;
				  	  case 5://right reverse
				  		  move_right(STATUS_B, speed);
				  		  break;
				  }
				  MAILBOX_CMD_ADDR = 0x0;
				  break;
			  case VELOCITY:
				  v = get_velocity();
				  MAILBOX_DATA(0) = (signed int)(4*v);
				  MAILBOX_CMD_ADDR = 0x0;
				  break;
			  case SET_PWM:
				  which  = MAILBOX_DATA(0);
				  period = MAILBOX_DATA(1);
				  duty   = MAILBOX_DATA(2);
				  timer_pwm_generate(which, period, duty);
				  MAILBOX_CMD_ADDR = 0x0;
				  break;

			  case SEND_DATA:
				  // write out adc_value, reset mailbox
				  MAILBOX_DATA(0) = read_adc(channel_left);
				  MAILBOX_DATA(1) = read_adc(channel_right);
				  MAILBOX_DATA_FLOAT(2) = read_analog(channel_left);
				  MAILBOX_DATA_FLOAT(3) = read_analog(channel_right);
				  MAILBOX_CMD_ADDR = 0x0;
				  break;

			  default:
				  MAILBOX_CMD_ADDR = 0x0; // reset command
				  break;
		   }
		 }
   return(0);
}

//int main()
//{
//	float dist;
//	init_ardumoto();
//	dist = get_velocity();
//	run_all();
//	sleep(1);
//	stop_all();
//	sleep(1);
//	dist = get_velocity();
//	move_forward(50);
//	sleep(1);
//	move_backward(50);
//	sleep(1);
//	move_left(STATUS_A);
//	sleep(1);
//	move_right(STATUS_B);
//	sleep(1);
//	stop_all();
//	return 0;
//}
