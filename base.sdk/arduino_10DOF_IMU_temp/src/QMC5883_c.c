/*!
 * @file DFRobot_QMC5883.cpp
 * @brief Compatible with QMC5883 and QMC5883
 * @n 3-Axis Digital Compass IC
 *
 * @copyright	[DFRobot](http://www.dfrobot.com), 2017
 * @copyright	GNU Lesser General Public License
 *
 * @author [dexian.huang](952838602@qq.com)
 * @version	V1.0
 * @date	2017-7-3
 */

#include "QMC5883_c.h"

#include <i2c.h>
#include <stdlib.h>
#include <sleep.h>

#define delay(x) usleep(x*1000)

i2c QMC5883_device;

bool isHMC_;
bool isQMC_;

float mgPerDigit;
Vector v;


float minX, maxX;
float minY, maxY;
float minZ, maxZ;
bool firstRun;

float map(float val, float I_Min, float I_Max, float O_Min, float O_Max){
	return(val/(I_Max-I_Min)*(O_Max-O_Min) + O_Min);
}

bool QMC5883_begin()
{
	int retry;
	uint8_t temp = 0;
	retry = 5;

	while(retry--){
		isHMC_ = i2c_write(QMC5883_device, HMC5883L_ADDRESS, &temp, 1);
		if(isHMC_){
			break;
		}
		delay(20);
	}

	if(isHMC_){
		if ((QMC5883_fastRegister8(HMC5883L_REG_IDENT_A) != 0x48)
		|| (QMC5883_fastRegister8(HMC5883L_REG_IDENT_B) != 0x34)
		|| (QMC5883_fastRegister8(HMC5883L_REG_IDENT_C) != 0x33)){
			return false;
		}

		QMC5883_setRange(HMC5883L_RANGE_1_3GA);
		QMC5883_setMeasurementMode(HMC5883L_CONTINOUS);
		QMC5883_setDataRate(HMC5883L_DATARATE_15HZ);
		QMC5883_setSamples(HMC5883L_SAMPLES_1);
		mgPerDigit = 0.92f;
		return true;
	}else{
		retry = 5;
		while(retry--){
			isQMC_ = i2c_write(QMC5883_device, QMC5883_ADDRESS, &temp, 1);
			if(isQMC_){
				break;
			}
			delay(20);
		}

		if(isQMC_){
			QMC5883_writeRegister8(QMC5883_REG_IDENT_B,0X01);
			QMC5883_writeRegister8(QMC5883_REG_IDENT_C,0X40);
			QMC5883_writeRegister8(QMC5883_REG_IDENT_D,0X01);
			QMC5883_writeRegister8(QMC5883_REG_CONFIG_1,0X1D);
			if ((QMC5883_fastRegister8(QMC5883_REG_IDENT_B) != 0x01)
			|| (QMC5883_fastRegister8(QMC5883_REG_IDENT_C) != 0x40)
			|| (QMC5883_fastRegister8(QMC5883_REG_IDENT_D) != 0x01)){
				return false;
			}
			QMC5883_setRange(QMC5883_RANGE_8GA);
			QMC5883_setMeasurementMode(QMC5883_CONTINOUS);
			QMC5883_setDataRate(QMC5883_DATARATE_50HZ);
			QMC5883_setSamples(QMC5883_SAMPLES_8);
			mgPerDigit = 4.35f;
			return true;
		}
	}
	return false;
}

Vector QMC5883_readRaw(void)
{
	int range = 10;
	float Xsum = 0.0;
	float Ysum = 0.0;
	float Zsum = 0.0;
	if(isHMC_){
		while(range--){
			v.XAxis = QMC5883_readRegister16(HMC5883L_REG_OUT_X_M);
			v.YAxis = QMC5883_readRegister16(HMC5883L_REG_OUT_Y_M);
			v.ZAxis = QMC5883_readRegister16(HMC5883L_REG_OUT_Z_M);
			QMC5883_calibrate();
			Xsum += v.XAxis;
			Ysum += v.YAxis;
			Zsum += v.ZAxis;
		}
		v.XAxis = Xsum/range;
		v.YAxis = Ysum/range;
		v.ZAxis = Zsum/range;
		if(firstRun){
			QMC5883_initMinMax();
			firstRun = false;
		}
	}else if(isQMC_){
		while (range--){
			v.XAxis = QMC5883_readRegister16(QMC5883_REG_OUT_X_M);
			v.YAxis = QMC5883_readRegister16(QMC5883_REG_OUT_Y_M);
			v.ZAxis = QMC5883_readRegister16(QMC5883_REG_OUT_Z_M);
			QMC5883_calibrate();
			Xsum += v.XAxis;
			Ysum += v.YAxis;
			Zsum += v.ZAxis;
		}
		v.XAxis = Xsum/range;
		v.YAxis = Ysum/range;
		v.ZAxis = Zsum/range;
		if(firstRun){
			QMC5883_initMinMax();
			firstRun = false;
		}
	}
	return v;
}
void QMC5883_calibrate()
{
	if(v.XAxis < minX ) minX = v.XAxis;
	if(v.XAxis > maxX ) maxX = v.XAxis;
	if(v.YAxis < minY ) minY = v.YAxis;
	if(v.YAxis > maxY ) maxY = v.YAxis;
	if(v.ZAxis < minZ ) minZ = v.ZAxis;
	if(v.ZAxis > maxZ ) maxZ = v.ZAxis;
}
void QMC5883_initMinMax()
{
	minX = v.XAxis;
	maxX = v.XAxis;
	minY = v.YAxis;
	maxY = v.YAxis;
	minZ = v.ZAxis;
	maxZ = v.ZAxis;
}
Vector QMC5883_readNormalize(void)
{
	int range = 10;
	float Xsum = 0.0;
	float Ysum = 0.0;
	float Zsum = 0.0;
	if(isHMC_){
		while (range--){
			v.XAxis = ((float)QMC5883_readRegister16(HMC5883L_REG_OUT_X_M )) * mgPerDigit;
			v.YAxis = ((float)QMC5883_readRegister16(HMC5883L_REG_OUT_Y_M )) * mgPerDigit;
			v.ZAxis = (float)QMC5883_readRegister16(HMC5883L_REG_OUT_Z_M) * mgPerDigit;
			Xsum += v.XAxis;
			Ysum += v.YAxis;
			Zsum += v.ZAxis;
		}
		v.XAxis = Xsum/range;
		v.YAxis = Ysum/range;
		v.ZAxis = Zsum/range;
		if(firstRun){
			QMC5883_initMinMax();
			firstRun = false;
		}
		QMC5883_calibrate();
		v.XAxis= map(v.XAxis,minX,maxX,-360,360);
		v.YAxis= map(v.YAxis,minY,maxY,-360,360);
		v.ZAxis= map(v.ZAxis,minZ,maxZ,-360,360);
		return v;
	}else if(isQMC_){
		while (range--){
			v.XAxis = ((float)QMC5883_readRegister16(QMC5883_REG_OUT_X_M)) * mgPerDigit;
			v.YAxis = ((float)QMC5883_readRegister16(QMC5883_REG_OUT_Y_M)) * mgPerDigit;
			v.ZAxis = (float)QMC5883_readRegister16(QMC5883_REG_OUT_Z_M) * mgPerDigit;
			Xsum += v.XAxis;
			Ysum += v.YAxis;
			Zsum += v.ZAxis;
		}
		v.XAxis = Xsum/range;
		v.YAxis = Ysum/range;
		v.ZAxis = Zsum/range;
		if(firstRun){
			QMC5883_initMinMax();
			firstRun = false;
		}

		QMC5883_calibrate();
		v.XAxis= map(v.XAxis,minX,maxX,-360,360);
		v.YAxis= map(v.YAxis,minY,maxY,-360,360);
		v.ZAxis= map(v.ZAxis,minZ,maxZ,-360,360);
	}
	return v;
}

void QMC5883_setRange(QMC5883_range_t range)
{
	if(isHMC_){
		switch(range){
		case HMC5883L_RANGE_0_88GA:
			mgPerDigit = 0.073f;
			break;

		case HMC5883L_RANGE_1_3GA:
			mgPerDigit = 0.92f;
			break;

		case HMC5883L_RANGE_1_9GA:
			mgPerDigit = 1.22f;
			break;

		case HMC5883L_RANGE_2_5GA:
			mgPerDigit = 1.52f;
			break;

		case HMC5883L_RANGE_4GA:
			mgPerDigit = 2.27f;
			break;

		case HMC5883L_RANGE_4_7GA:
			mgPerDigit = 2.56f;
			break;

		case HMC5883L_RANGE_5_6GA:
			mgPerDigit = 3.03f;
			break;

		case HMC5883L_RANGE_8_1GA:
			mgPerDigit = 4.35f;
			break;

		default:
			break;
		}

		QMC5883_writeRegister8(HMC5883L_REG_CONFIG_B, range << 5);
	}else if(isQMC_){
		switch(range)
		{
		case QMC5883_RANGE_2GA:
			mgPerDigit = 1.22f;
			break;
		case QMC5883_RANGE_8GA:
			mgPerDigit = 4.35f;
			break;
		default:
			break;
		}

		QMC5883_writeRegister8(QMC5883_REG_CONFIG_2, range << 4);
	}
}

QMC5883_range_t QMC5883_getRange(void)
{
	if(isHMC_){
		return (QMC5883_range_t)((QMC5883_readRegister8(HMC5883L_REG_CONFIG_B) >> 5));
	}else if(isQMC_){
		return (QMC5883_range_t)((QMC5883_readRegister8(QMC5883_REG_CONFIG_2) >> 4));
	}
	return QMC5883_RANGE_8GA;
}

void QMC5883_setMeasurementMode(QMC5883_mode_t mode)
{
	uint8_t value;
	if(isHMC_){
		value = QMC5883_readRegister8(HMC5883L_REG_MODE);
		value &= 0b11111100;
		value |= mode;

		QMC5883_writeRegister8(HMC5883L_REG_MODE, value);
	}else if(isQMC_){
		value = QMC5883_readRegister8(QMC5883_REG_CONFIG_1);
		value &= 0xfc;
		value |= mode;

		QMC5883_writeRegister8(QMC5883_REG_CONFIG_1, value);
	}
}

QMC5883_mode_t QMC5883_getMeasurementMode(void)
{
	uint8_t value=0;
	if(isHMC_){
		value = QMC5883_readRegister8(HMC5883L_REG_MODE);
	}else if(isQMC_){
		value = QMC5883_readRegister8(QMC5883_REG_CONFIG_1);
	}
	value &= 0b00000011;
	return (QMC5883_mode_t)value;
}

void QMC5883_setDataRate(QMC5883_dataRate_t dataRate)
{
	uint8_t value;
	if(isHMC_){
		value = QMC5883_readRegister8(HMC5883L_REG_CONFIG_A);
		value &= 0b11100011;
		value |= (dataRate << 2);

		QMC5883_writeRegister8(HMC5883L_REG_CONFIG_A, value);
	}else if(isQMC_){
		value = QMC5883_readRegister8(QMC5883_REG_CONFIG_1);
		value &= 0xf3;
		value |= (dataRate << 2);

		QMC5883_writeRegister8(QMC5883_REG_CONFIG_1, value);
	}
}

QMC5883_dataRate_t QMC5883_getDataRate(void)
{
	uint8_t value=0;
	if(isHMC_){
		value = QMC5883_readRegister8(HMC5883L_REG_CONFIG_A);
		value &= 0b00011100;
		value >>= 2;
	}else if(isQMC_){
		value = QMC5883_readRegister8(QMC5883_REG_CONFIG_1);
		value &= 0b00001100;
		value >>= 2;
	}
	return (QMC5883_dataRate_t)value;
}

void QMC5883_setSamples(QMC5883_samples_t samples)
{
	uint8_t value;
	if(isHMC_){
		value = QMC5883_readRegister8(HMC5883L_REG_CONFIG_A);
		value &= 0b10011111;
		value |= (samples << 5);
		QMC5883_writeRegister8(HMC5883L_REG_CONFIG_A, value);
	}else if(isQMC_){
		value = QMC5883_readRegister8(QMC5883_REG_CONFIG_1);
		value &= 0x3f;
		value |= (samples << 6);
		QMC5883_writeRegister8(QMC5883_REG_CONFIG_1, value);
	}
}

QMC5883_samples_t QMC5883_getSamples(void)
{
	uint8_t value=0;
	if(isHMC_){
		value = QMC5883_readRegister8(HMC5883L_REG_CONFIG_A);
		value &= 0b01100000;
		value >>= 5;
	}else if(isQMC_){
		value = QMC5883_readRegister8(QMC5883_REG_CONFIG_1);
		value &= 0x3f;
		value >>= 6;
	}
	return (QMC5883_samples_t)value;
}

bool QMC5883_isHMC(){return isHMC_;}
bool QMC5883_isQMC(){return isQMC_;}

// Write byte to register
void QMC5883_writeRegister8(uint8_t reg, uint8_t value)
{
	uint8_t temp[2];
	temp[0] = reg;
	temp[1] = value;
	if(isHMC_){
		i2c_write(QMC5883_device, HMC5883L_ADDRESS, temp, 2);
	}else if(isQMC_){
		i2c_write(QMC5883_device, QMC5883_ADDRESS, temp, 2);
	}
}
// Read byte to register
uint8_t QMC5883_fastRegister8(uint8_t reg)
{
	uint8_t value=0;
	if(isHMC_){
		i2c_write(QMC5883_device, HMC5883L_ADDRESS, &reg, 1);
		i2c_read(QMC5883_device, HMC5883L_ADDRESS, &value, 1);
	}else if(isQMC_){
		i2c_write(QMC5883_device, QMC5883_ADDRESS, &reg, 1);
		i2c_read(QMC5883_device, QMC5883_ADDRESS, &value, 1);
	}
	return value;
}

// Read byte from register
uint8_t QMC5883_readRegister8(uint8_t reg)
{
	uint8_t value=0;
	if(isHMC_){
		i2c_write(QMC5883_device, HMC5883L_ADDRESS, &reg, 1);
		i2c_read(QMC5883_device, HMC5883L_ADDRESS, &value, 1);
	}else if(isQMC_){
		i2c_write(QMC5883_device, QMC5883_ADDRESS, &reg, 1);
		i2c_read(QMC5883_device, QMC5883_ADDRESS, &value, 1);
	}
	return value;
}
// Read word from register
int16_t QMC5883_readRegister16(uint8_t reg)
{
	uint8_t temp[2] = {0};
	int16_t value=0;
	if(isHMC_){
		i2c_write(QMC5883_device, HMC5883L_ADDRESS, &reg, 1);
		i2c_read(QMC5883_device, HMC5883L_ADDRESS, temp, 2);
		value = temp[0] << 8 | temp[1];
	}else if(isQMC_){
		i2c_write(QMC5883_device, QMC5883_ADDRESS, &reg, 1);
		i2c_read(QMC5883_device, QMC5883_ADDRESS, temp, 2);
		value = temp[0] << 8 | temp[1];
	}
	return value;
}

int QMC5883_getICType(void)
{
	if(isHMC_){
		return IC_HMC5883L;
	}else if(isQMC_){
		return IC_QMC5883;
	}else{
		return IC_NONE;
	}
}

