#include <IMU_driver.h>

#define range_acc
#define range_gyro

void setup()
{
	Serial.begin(9600);
	enable_IMU(range_acc, range_gyro);
}

void loop()
{
	IMU_6050_t imu_data;

	imu_data = get_allData_IMU();
	Serial.println("acc x: %f",imu_data.accel.a_x);
	Serial.println("acc y: %f",imu_data.accel.a_y);
	Serial.println("acc z: %f",imu_data.accel.a_z);

	Serial.println("gyro x: %f",imu_data.gyro.g_x);
	Serial.println("gyro y: %f",imu_data.gyro.g_y);
	Serial.println("gyro z: %f",imu_data.gyro.g_z);
	delay(1000);
}