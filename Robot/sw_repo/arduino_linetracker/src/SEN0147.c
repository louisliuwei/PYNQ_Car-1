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
 * IOP code (MicroBlaze) for SEN0147.
 * http://www.dfrobot.com.cn/goods-784.html
 *
 * SEN0147 is controlled by xadc module
 * SEN0147 has both digital and analog model
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
 * 1.00a zc  1/27/19 release
 * 
 *
 * </pre>
 *
 *****************************************************************************/

#include "SEN0147.h"
#include <circular_buffer.h>

#define CONFIG_IOP_SWITCH 0x1
#define SEND_DATA 0X3

int channel_left;
int channel_right;

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
}


int main(){
	
	int cmd;
	u32 adc = 0;
	float analog = 0;
	initialize();
	
	while(1){
		while((MAILBOX_CMD_ADDR)==0);
		cmd = MAILBOX_CMD_ADDR;
		switch(cmd){
			
         case CONFIG_IOP_SWITCH:
            // set pins
            channel_left = set_LTpins(MAILBOX_DATA(0));
			channel_right = set_LTpins(MAILBOX_DATA(1));
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
            MAILBOX_CMD_ADDR = 0x0;
            break;
            
      }
	}
	return 0;
}
