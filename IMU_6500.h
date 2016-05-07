/* there is all of the registers of the IMU
 * IMU_6050.h
 *
 * Created: 23/04/2016 03:40:26 p. m.
 *  Author: aleja_000
 */ 


#ifndef IMU_6050_H_
#define IMU_6050_H_


#define SELF_TEST_X_GYRO	00
#define SELF_TEST_Y_GYRO	01
#define SELF_TEST_Z_GYRO	02
#define SELF_TEST_X_ACCEL	13
#define SELF_TEST_Y_ACCEL	14
#define SELF_TEST_Z_ACCEL	15
#define XG_OFFSET_H			19
#define XG_OFFSET_L			20
#define YG_OFFSET_H			21
#define YG_OFFSET_L			22
#define ZG_OFFSET_H			23
#define ZG_OFFSET_L			24
#define SMPLRT_DIV			25
#define CONFIG				26
#define GYRO_CONFIG			27
#define ACCEL_CONFIG		28
#define ACCEL_CONFIG_2		29
#define LP_ACCEL_ODR		30
#define WOM_THR				31
#define FIFO_EN				35
#define I2C_MST_CTRL		36
#define I2C_SLV0_ADDR		37
#define I2C_SLV0_REG		38
#define I2C_SLV0_CTRL		39
#define I2C_SLV1_ADDR		40
#define I2C_SLV1_REG		41
#define I2C_SLV1_CTRL		42
#define I2C_SLV2_ADDR		43
#define I2C_SLV2_REG		44
#define I2C_SLV2_CTRL		45
#define I2C_SLV3_ADDR		46
#define I2C_SLV3_REG		47
#define I2C_SLV3_CTRL		48
#define I2C_SLV4_ADDR		49
#define I2C_SLV4_REG		50
#define I2C_SLV4_DO			51
#define I2C_SLV4_CTRL		52
#define I2C_SLV4_DI			53
#define I2C_MST_STATUS		54
#define INT_PIN_CFG			55
#define INT_ENABLE			56
#define INT_STATUS			58
#define ACCEL_XOUT_H		59
#define ACCEL_XOUT_L		60
#define ACCEL_YOUT_H		61
#define ACCEL_YOUT_L		62
#define ACCEL_ZOUT_H		63
#define ACCEL_ZOUT_L		64
#define TEMP_OUT_H			65
#define TEMP_OUT_L			66
#define GYRO_XOUT_H			67
#define GYRO_XOUT_L			68
#define GYRO_YOUT_H			69
#define GYRO_YOUT_L			70
#define GYRO_ZOUT_H			71
#define GYRO_ZOUT_L			72
#define EXT_SENS_DATA_00	73
...
..
.			//..DATA_23	    96
#define I2C_SLV0_DO			99
#define I2C_SLV1_DO			100
#define I2C_SLV2_DO			101
#define I2C_SLV3_DO			102
#define I2C_MST_DELAY_CTRL	103
#define SIGNAL_PATH_RESET	104
#define ACCEL_INTEL_CTRL	105
#define USER_CTRL			106
#define PWR_MGMT_1			107
#define PWR_MGMT_2			108
#define FIFO_COUNT_H		114
#define FIFO_COUNT_L		115
#define FIFO_R_W			116
#define WHO_AM_I			117
#define XA_OFFSET_H			119
#define XA_OFFSET_L			120
#define YA_OFFSET_H			122
#define YA_OFFSET_L			123
#define ZA_OFFSET_H			125
#define ZA_OFFSET_L			126

//factores para convertir
//te dara un rango de 2*LSB_xg al ser de -xg hasta +xg se usara la funcion map()
//un ejemplo seria degres = map(dataRaw/LSB_2g, 0, 4, -2, 2); depende del rango en el que se este trabajando
#define LSB_2g	16384.0f
#define LSB_4g	8192.0f
#define LSB_8g	4096.0f
#define LSB_16g	2048.0f

#define LSB_250dg	131.0f
#define LSB_500dg	65.5f
#define LSB_1000dg	32.8f
#define LSB_2000dg	16.4f

#endif /* MPU_6050_H_ */