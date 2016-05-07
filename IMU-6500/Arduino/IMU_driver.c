/*
 * IMU_driver.c
 *
 * Created: 25/04/2016 07:40:06 p. m.
 *  Author: Alejandro M
 */ 
#include "IMU_driver.h"

void enable_IMU(void)
{
	//aqui puede ir la inicializacion del modulo
	Wire.begin();
	Wire.beginTransmission(MPU);
	Wire.write(0x6B);
	Wire.write(0);
	Wire.endTransmission(true);
}

accel_data_t get_raw_accData_IMU(range_data_t t_data)
{
	accel_data_t rcvd;
	Wire.beginTransmission(MPU);
	Wire.write(ACCEL_XOUT_H); //Pedir el registro 0x3B - corresponde al AcX
	Wire.endTransmission(false);
	Wire.requestFrom(MPU,6,true); //A partir del 0x3B, se piden 6 registros
	rcvd.a_x = process_data_IMU(Wire.read()<<8|Wire.read(), t_data);
	rcvd.a_y = process_data_IMU(Wire.read()<<8|Wire.read(), t_data);
	rcvd.a_z = process_data_IMU(Wire.read()<<8|Wire.read(), t_data);
	return rcvd;
}

gyro_data_t get_raw_gyroData_IMU(range_data_t t_data)
{
	gyro_data_t rcvd;
	Wire.beginTransmission(MPU);
	Wire.write(GYRO_XOUT_H);
	Wire.endTransmission(false);
	Wire.requestFrom(MPU,6,true); //A diferencia del Acelerometro, solo se piden 4 registros
	rcvd.g_x = process_data_IMU(Wire.read()<<8|Wire.read(), t_data);
	rcvd.g_y = process_data_IMU(Wire.read()<<8|Wire.read(), t_data);
	rcvd.g_z = process_data_IMU(Wire.read()<<8|Wire.read(), t_data);
	return rcvd;
}

IMU_6050_t get_allData_IMU(range_data_t t_data_acc, range_data_t t_data_gyro)
{
	IMU_6050_t rcvd;
	
	Wire.beginTransmission(MPU);
	Wire.write(ACCEL_XOUT_H); //Pedir el registro 0x3B - corresponde al AcX
	Wire.endTransmission(false);
	Wire.requestFrom(MPU,6,false); //A partir del 0x3B, se piden 6 registros
	rcvd.accel.a_x = process_data_IMU(Wire.read()<<8|Wire.read(), t_data_acc); //Cada valor ocupa 2 registros
	rcvd.accel.a_y = process_data_IMU(Wire.read()<<8|Wire.read(), t_data_acc);
	rcvd.accel.a_z = process_data_IMU(Wire.read()<<8|Wire.read(), t_data_acc);
	Wire.beginTransmission(MPU);
	Wire.write(GYRO_XOUT_H);
	Wire.requestFrom(MPU,6,true); //A diferencia del Acelerometro, solo se piden 4 registros
	rcvd.gyro.g_x = process_data_IMU(Wire.read()<<8|Wire.read(), t_data_gyro);
	rcvd.gyro.g_y = process_data_IMU(Wire.read()<<8|Wire.read(), t_data_gyro);
	rcvd.gyro.g_z = process_data_IMU(Wire.read()<<8|Wire.read(), t_data_gyro);

	return rcvd;
}

uint32_t update_and_get_Data_IMU(void)
{
	gyro_data_t gyro;
	accel_data_t accel;
	
	
	//obtener por comunicacion spi los datos
	
	//				= getTime()
	uint32_t timeNow;
	float deltat = timeNow - lastUpdate;//es el diferencial del tiempo transcurrido entre cada actualizacion de los datos
	lastUpdate = timeNow;
	QuaternionStruct quaternion = filterUpdate(deltat, gyro.g_x, gyro.g_y, gyro.g_z, accel.a_x, accel.a_y, accel.a_z);
}

float process_data_IMU(float data_raw,range_data_t t_data)
{
	switch (t_data)
	{
		case LSB_2g_dat:
			return map(data_raw / LSB_2g, 0, 4, -2, 2);			
		case LSB_4g_dat:
			return map(data_raw / LSB_4g, 0, 8, -4, 4);
		case LSB_8g_dat:
			return map(data_raw / LSB_8g, 0, 16, -8, 8);
		case LSB_16g_dat:
			return map(data_raw / LSB_16g, 0, 32, -16, 16);
		case LSB_250dg_dat:
			return map(data_raw / LSB_250dg, 0, 500, -250, 250);
		case LSB_500dg_dat:
			return map(data_raw / LSB_500dg, 0, 1000, -500, 500);
		case LSB_1000dg_dat:
			return map(data_raw / LSB_1000dg, 0, 2000, -1000, 1000);
		case LSB_2000dg_dat:
			return map(data_raw / LSB_500dg, 0, 4000, -2000, 2000);
	}
	return 1.0;
}