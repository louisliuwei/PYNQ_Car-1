/******************************************************************************
 *  Copyright (c) 2016, Xilinx, Inc.
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
 * Ver   Who  Date     Changes
 * ----- --- ------- -----------------------------------------------
 * 1.00a ljh 04/25/16 release
 *
 * </pre>
 *
 *****************************************************************************/

#include "SparkFun_APDS9960.h"
#include "circular_buffer.h"
#include "timer.h"
#include "i2c.h"

int main()
{
	extern i2c device;
	// Initialization
	device = i2c_open_device(0);

	xil_printf("Gesture Test\r\n");
	if ( init() ) {
		xil_printf("APDS-9960 initialization complete");
	} else {
		xil_printf("Something went wrong during APDS-9960 init!");
	}

	if ( enableGestureSensor(true) ) {
		xil_printf("Gesture sensor is now running");
	} else {
		xil_printf("Something went wrong during gesture sensor init!");
	}

	while (1) {
		if ( isGestureAvailable() ) {
			switch ( readGesture() ) {
			case DIR_UP:
				xil_printf("UP");
				break;
			case DIR_DOWN:
				xil_printf("DOWN");
				break;
			case DIR_LEFT:
				xil_printf("LEFT");
				break;
			case DIR_RIGHT:
				xil_printf("RIGHT");
				break;
			case DIR_NEAR:
				xil_printf("NEAR");
				break;
			case DIR_FAR:
				xil_printf("FAR");
				break;
			default:
				xil_printf("NONE");
			}
		}
	}
	return 0;
}
