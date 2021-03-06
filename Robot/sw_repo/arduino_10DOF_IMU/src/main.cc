/*
 * Empty C++ Application
 */

#include "BNO055.h"
#include "BMP280.h"
#include "I2CMultiplexer.h"
#include "circular_buffer.h"
#include <sleep.h>

#define delay(x) usleep(x*1000)
#define SEA_LEVEL_PRESSURE    1015.0f   // sea level pressure

typedef BMP280_IIC BMP;
typedef BNO055_IIC BNO;

// Mailbox commands
#define CONFIG_IOP_SWITCH       0x1
#define GET_AXIS_DATA           0x3
#define GET_EUL_DATA            0x5
#define GET_QUA_DATA            0x7
#define GET_TEMPERATURE         0xB
#define GET_PRESSURE            0xD
#define RESET                   0xF

I2CMultiplexer I2CMulti(0x70);
BMP bmp(BMP::eSdo_low);
BNO bno(0x28);
int main()
{
	//float   alti = bmp.calAltitude(SEA_LEVEL_PRESSURE, press);

	//sLiaAnalog = bno.getAxis(BNO::eAxisLia);    // read linear acceleration
	//sGrvAnalog = bno.getAxis(BNO::eAxisGrv);    // read gravity vector

	int cmd;
	uint8_t channel, flag;
	int16_t ax, ay, az;
	int16_t gx, gy, gz;
	int16_t mx, my, mz;
	BNO::sAxisAnalog_t   sAccAnalog, sMagAnalog, sGyrAnalog, sLiaAnalog, sGrvAnalog;
	BNO::sEulAnalog_t    sEulAnalog;
	BNO::sQuaAnalog_t    sQuaAnalog;

	// Initialization
	I2CMulti.I2CMulti_device = bmp.BMP280_device = bno.BNO055_device = i2c_open_device(0);

//	I2CMulti.selectPort(1);
//
//	bno.reset();
//	delay(500);
//	flag = 0;
//	while (bno.begin() != BNO::eStatusOK && flag<5) {
//		flag++;
//		delay(1000);
//	}
//	if (flag == 5)
//		MAILBOX_DATA(0) = 0;
//	else
//		MAILBOX_DATA(0) = 1;
//
//	bmp.reset();
//	flag = 0;
//	while (bmp.begin() != BMP::eStatusOK && flag<5) {
//		flag++;
//	}

	// Run application
	while(1){
	 // wait and store valid command
	  while((MAILBOX_CMD_ADDR & 0x01)==0);
	  cmd = MAILBOX_CMD_ADDR;

	  switch(cmd){
		  case CONFIG_IOP_SWITCH:
			// use dedicated I2C - no operation needed
			flag = 0;
			channel = MAILBOX_DATA(0);
			while (I2CMulti.selectPort(channel)!=1 && flag<5) {
				flag++;
			}
			if (flag == 5)
				MAILBOX_DATA(0) = 0;
			else
				MAILBOX_DATA(0) = 1;

			bno.reset();
			delay(500);
			flag = 0;
			while (bno.begin() != BNO::eStatusOK && flag<5) {
				flag++;
				delay(500);
			}
			if (flag == 5)
				MAILBOX_DATA(1) = 0;
			else
				MAILBOX_DATA(1) = 1;

			bmp.reset();
			flag = 0;
			while (bmp.begin() != BMP::eStatusOK && flag<5) {
				flag++;
				delay(500);
			}
			if (flag == 5)
				MAILBOX_DATA(2) = 0;
			else
				MAILBOX_DATA(2) = 1;
			MAILBOX_CMD_ADDR = 0x0;
			break;

		 case GET_AXIS_DATA:
			sAccAnalog = bno.getAxis(BNO::eAxisAcc);    // read acceleration
			sGyrAnalog = bno.getAxis(BNO::eAxisGyr);    // read gyroscope
			sMagAnalog = bno.getAxis(BNO::eAxisMag);    // read geomagnetic
			MAILBOX_DATA_FLOAT(0) = sAccAnalog.x;
			MAILBOX_DATA_FLOAT(1) = sAccAnalog.y;
			MAILBOX_DATA_FLOAT(2) = sAccAnalog.z;
			MAILBOX_DATA_FLOAT(3) = sGyrAnalog.x;
			MAILBOX_DATA_FLOAT(4) = sGyrAnalog.y;
			MAILBOX_DATA_FLOAT(5) = sGyrAnalog.z;
			MAILBOX_DATA_FLOAT(6) = sMagAnalog.x;
			MAILBOX_DATA_FLOAT(7) = sMagAnalog.y;
			MAILBOX_DATA_FLOAT(8) = sMagAnalog.z;
			MAILBOX_CMD_ADDR = 0x0;
			break;

		 case GET_EUL_DATA:
			sEulAnalog = bno.getEul();                  // read euler angle
			MAILBOX_DATA_FLOAT(0) = sEulAnalog.head;
			MAILBOX_DATA_FLOAT(1) = sEulAnalog.roll;
			MAILBOX_DATA_FLOAT(2) = sEulAnalog.pitch;
			MAILBOX_CMD_ADDR = 0x0;
			break;

		 case GET_QUA_DATA:
			sQuaAnalog = bno.getQua();                  // read quaternion
			MAILBOX_DATA_FLOAT(0) = sQuaAnalog.w;
			MAILBOX_DATA_FLOAT(1) = sQuaAnalog.x;
			MAILBOX_DATA_FLOAT(2) = sQuaAnalog.y;
			MAILBOX_DATA_FLOAT(3) = sQuaAnalog.z;
			MAILBOX_CMD_ADDR = 0x0;
			break;

		 case GET_TEMPERATURE:
			MAILBOX_DATA_FLOAT(0) = bmp.getTemperature();
			MAILBOX_CMD_ADDR = 0x0;
			break;

		 case GET_PRESSURE:
			MAILBOX_DATA(0) = bmp.getPressure();
			MAILBOX_CMD_ADDR = 0x0;
			break;

		 case RESET:
			bno.reset();
			MAILBOX_CMD_ADDR = 0x0;
			break;

		 default:
			MAILBOX_CMD_ADDR = 0x0;
			break;
	  }
	}
	return 0;
}

//int main()
//{
//	BNO::sQuaAnalog_t    sQuaAnalog;
//	// Initialization
//	I2CMulti.I2CMulti_device = bmp.BMP280_device = bno.BNO055_device = i2c_open_device(0);
//
//	I2CMulti.selectPort(1);
//	bno.reset();
//	while (bno.begin() != BNO::eStatusOK) {
//		xil_printf("Initialization failed");
//	}
//
//	bmp.reset();
//	if (bmp.begin() != BMP::eStatusOK) {
//		xil_printf("Initialization failed");
//	}
//
//	sQuaAnalog = bno.getQua();                  // read quaternion
//	return 0;
//}
