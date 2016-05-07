/*
 * IMU_driver.c
 *
 * Created: 25/04/2016 07:40:06 p. m.
 *  Author: Alejandro M
 */ 
#include "IMU_driver.h"

void enable_IMU(float range_acc, float range_gyro)
{
	//aqui puede ir la inicializacion del modulo
	Wire.begin();
	Wire.beginTransmission(MPU);
	Wire.write(0x6B);
	Wire.write(0);
	Wire.endTransmission(true);

	change_range_gyro(range_gyro);
	change_range_acc(range_acc);
}

void change_range_gyro(float range)
{
	Wire.beginTransmission(MPU);
	Wire.write(GYRO_CONFIG);
	switch (range)
	{
		case LSB_250dg:
			Wire.write(0);
		case LSB_500dg:
			Wire.write(01<<3);
		case LSB_1000dg:
			Wire.write(10<<3);
		case LSB_2000dg:
			Wire.write(11<<3);
	}
	Wire.endTransmission(true);
	range_gyro_actualy = range;
}
void change_range_acc(float range)
{
	Wire.beginTransmission(MPU);
	Wire.write(ACCEL_CONFIG);
	switch (range)
	{
		case LSB_2g:
			Wire.write(0);
		case LSB_4g:
			Wire.write(01<<3);
		case LSB_8g:
			Wire.write(10<<3);
		case LSB_16g:
			Wire.write(11<<3);
	}
	Wire.endTransmission(true);
	range_acc_actualy = range;
}

accel_data_t get_accData_IMU(void)
{
	accel_data_t rcvd;
	Wire.beginTransmission(MPU);
	Wire.write(ACCEL_XOUT_H); //Pedir el registro 0x3B - corresponde al AcX
	Wire.endTransmission(false);
	Wire.requestFrom(MPU,6,true); //A partir del 0x3B, se piden 6 registros
	rcvd.a_x = process_data_IMU(Wire.read()<<8|Wire.read(), range_acc_actualy);
	rcvd.a_y = process_data_IMU(Wire.read()<<8|Wire.read(), range_acc_actualy);
	rcvd.a_z = process_data_IMU(Wire.read()<<8|Wire.read(), range_acc_actualy);
	return rcvd;
}

gyro_data_t get_gyroData_IMU(void)
{
	gyro_data_t rcvd;
	Wire.beginTransmission(MPU);
	Wire.write(GYRO_XOUT_H);
	Wire.endTransmission(false);
	Wire.requestFrom(MPU,6,true); //A diferencia del Acelerometro, solo se piden 4 registros
	rcvd.g_x = process_data_IMU(Wire.read()<<8|Wire.read(), range_gyro_actualy);
	rcvd.g_y = process_data_IMU(Wire.read()<<8|Wire.read(), range_gyro_actualy);
	rcvd.g_z = process_data_IMU(Wire.read()<<8|Wire.read(), range_gyro_actualy);
	return rcvd;
}

IMU_6050_t get_allData_IMU(void)
{
	IMU_6050_t rcvd;

	Wire.beginTransmission(MPU);
	Wire.write(ACCEL_XOUT_H); //Pedir el registro 0x3B - corresponde al AcX
	Wire.endTransmission(false);
	Wire.requestFrom(MPU,6,false); //A partir del 0x3B, se piden 6 registros
	rcvd.accel.a_x = process_data_IMU(Wire.read()<<8|Wire.read(), range_acc_actualy); //Cada valor ocupa 2 registros
	rcvd.accel.a_y = process_data_IMU(Wire.read()<<8|Wire.read(), range_acc_actualy);
	rcvd.accel.a_z = process_data_IMU(Wire.read()<<8|Wire.read(), range_acc_actualy);
	Wire.beginTransmission(MPU);
	Wire.write(GYRO_XOUT_H);
	Wire.requestFrom(MPU,6,true); //A diferencia del Acelerometro, solo se piden 4 registros
	rcvd.gyro.g_x = process_data_IMU(Wire.read()<<8|Wire.read(), range_gyro_actualy);
	rcvd.gyro.g_y = process_data_IMU(Wire.read()<<8|Wire.read(), range_gyro_actualy);
	rcvd.gyro.g_z = process_data_IMU(Wire.read()<<8|Wire.read(), range_gyro_actualy);

	return rcvd;
}

float process_data_IMU(float data_raw,float t_data)
{
	switch (t_data)
	{
		case LSB_2g:
			return map(data_raw / LSB_2g, 0, 4, -2, 2);			
		case LSB_4g:
			return map(data_raw / LSB_4g, 0, 8, -4, 4);
		case LSB_8g:
			return map(data_raw / LSB_8g, 0, 16, -8, 8);
		case LSB_16g:
			return map(data_raw / LSB_16g, 0, 32, -16, 16);
		case LSB_250dg:
			return map(data_raw / LSB_250dg, 0, 500, -250, 250);
		case LSB_500dg:
			return map(data_raw / LSB_500dg, 0, 1000, -500, 500);
		case LSB_1000dg:
			return map(data_raw / LSB_1000dg, 0, 2000, -1000, 1000);
		case LSB_2000dg:
			return map(data_raw / LSB_500dg, 0, 4000, -2000, 2000);
	}
	return 1.0;
}