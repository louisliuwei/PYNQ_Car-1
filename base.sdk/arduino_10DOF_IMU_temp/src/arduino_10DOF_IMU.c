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
 * @file arduino_10DOF_IMU.c
 *
 * IOP code (MicroBlaze) for DFRotbot 10DOF IMU module.
 * The module has to be connected to an arduino interface
 * via a shield socket.
 *
 * <pre>
 * MODIFICATION HISTORY:
 *
 * Ver   Who  Date     Changes
 * ----- --- ------- -----------------------------------------------
 * 1.00a ljh 01/28/19 release
 *
 * </pre>
 *
 *****************************************************************************/

#include "circular_buffer.h"
#include "i2c.h"
#include <sleep.h>
#include "QMC5883_c.h"

#define delay(x) usleep(x*1000)

int main()
{
	extern i2c QMC5883_device;
	// Initialization
	QMC5883_device = i2c_open_device(0);
	// Initialize Initialize QMC5883
	while (!QMC5883_begin()){
		xil_printf("Could not find a valid QMC5883 sensor, check wiring!");

	}
	if(QMC5883_isHMC() ){
		xil_printf("Initialize HMC5883");
		QMC5883_setRange(HMC5883L_RANGE_1_3GA);
		QMC5883_setMeasurementMode(HMC5883L_CONTINOUS);
		QMC5883_setDataRate(HMC5883L_DATARATE_15HZ);
		QMC5883_setSamples(HMC5883L_SAMPLES_8);
	}else if(QMC5883_isQMC()){
		xil_printf("Initialize QMC5883");
		QMC5883_setRange(QMC5883_RANGE_2GA);
		QMC5883_setMeasurementMode(QMC5883_CONTINOUS);
		QMC5883_setDataRate(QMC5883_DATARATE_50HZ);
		QMC5883_setSamples(QMC5883_SAMPLES_8);
	}

	while (1) {
		Vector mag = QMC5883_readRaw();
	}
}
