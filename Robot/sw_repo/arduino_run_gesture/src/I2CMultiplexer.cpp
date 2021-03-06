#include "I2CMultiplexer.h"


I2CMultiplexer::I2CMultiplexer(uint8_t addr){
	I2CMulti = addr;
}

uint8_t *I2CMultiplexer::scan(uint8_t port){
	static uint8_t dev[127] = {0};
//	uint8_t dev;
	memset(dev,0,sizeof(dev));
	uint8_t i = 0;
	selectPort(port);

	uint8_t error, address, temp = 0x00;
	int nDevices;
	nDevices = 0;
	for(address = 1; address < 127; address++ ) {
		if (address == I2CMulti){ continue;}
		error = i2c_write(I2CMulti_device, address, &temp, 1);
		if (error == 1){
			dev[i] = address;
			i++;
		}
	}
	return dev;
}

void I2CMultiplexer::selectPort(uint8_t port){
	if (port > 7) return;
	uint8_t temp = 1 << port;
	i2c_write(I2CMulti_device, I2CMulti, &temp, 1);
}

uint8_t I2CMultiplexer::write(uint8_t port,uint8_t addr, uint8_t reg,uint8_t* buf, uint8_t len){
	int i;
	int len_total = (int)len+1;
	uint8_t temp[len_total];
	selectPort(port);

	temp[0] = reg;
	for (i=1;i<len_total;i++){
		temp[i]=buf[i-1];
	}
	return i2c_write(I2CMulti_device, addr, temp, len_total);
}


uint8_t I2CMultiplexer::read(uint8_t port,uint8_t addr,uint8_t reg,uint8_t* data, uint8_t len){
	selectPort(port);
	int i = 0;
	if (i2c_write(I2CMulti_device, addr, &reg, 1)==0)
		return 0;
	 i = i2c_read(I2CMulti_device, addr, data, len);
//	Serial.println(result[0]);
	return i;
}
