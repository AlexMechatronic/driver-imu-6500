/*
 * IMU_driver.c
 *
 * Created: 25/04/2016 07:40:06 p. m.
 *  Author: aleja_000
 */ 
#include "IMU_driver.h"

void enable_IMU(void)
{
	//aqui puede ir la inicializacion del modulo
	//tambien podria ser optimizarlo para usar los canales XDMA
	//y se este actualizando
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