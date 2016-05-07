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

accel_data_t get_raw_accData_IMU(void)
{
	accel_data_t rcvd;
	Wire.beginTransmission(MPU);
	Wire.write(ACCEL_XOUT_H); //Pedir el registro 0x3B - corresponde al AcX
	Wire.endTransmission(false);
	Wire.requestFrom(MPU,6,true); //A partir del 0x3B, se piden 6 registros
	rcvd.a_x = Wire.read()<<8|Wire.read(); //Cada valor ocupa 2 registros
	rcvd.a_y = Wire.read()<<8|Wire.read();
	rcvd.a_z = Wire.read()<<8|Wire.read();
	return rcvd;
}

gyro_data_t get_raw_gyroData_IMU(void)
{
	gyro_data_t rcvd;
	Wire.beginTransmission(MPU);
	Wire.write(GYRO_XOUT_H);
	Wire.endTransmission(false);
	Wire.requestFrom(MPU,6,true); //A diferencia del Acelerometro, solo se piden 4 registros
	rcvd.g_x = Wire.read()<<8|Wire.read();
	rcvd.g_y = Wire.read()<<8|Wire.read();
	rcvd.g_z = Wire.read()<<8|Wire.read();
	return rcvd;
}

IMU_6050_t get_allData_IMU(void)
{
	IMU_6050_t rcvd;
	Wire.beginTransmission(MPU);
	Wire.write(ACCEL_XOUT_H); //Pedir el registro 0x3B - corresponde al AcX
	Wire.endTransmission(false);
	Wire.requestFrom(MPU,6,false); //A partir del 0x3B, se piden 6 registros
	rcvd.accel.a_x = Wire.read()<<8|Wire.read(); //Cada valor ocupa 2 registros
	rcvd.accel.a_y = Wire.read()<<8|Wire.read();
	rcvd.accel.a_z = Wire.read()<<8|Wire.read();
	Wire.beginTransmission(MPU);
	Wire.write(GYRO_XOUT_H);
	Wire.requestFrom(MPU,6,true); //A diferencia del Acelerometro, solo se piden 4 registros
	rcvd.gyro.g_x = Wire.read()<<8|Wire.read();
	rcvd.gyro.g_y = Wire.read()<<8|Wire.read();
	rcvd.gyro.g_z = Wire.read()<<8|Wire.read();
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