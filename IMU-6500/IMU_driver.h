#ifndef IMU_DRIVER_H_
#define IMU_DRIVER_H_

#include "IMU_6500.h"

#ifdef __Arduino
#include "Arduino/IMU_driver.h"
#endif

#ifdef _SAME70
#include "SAME70/IMU_driver.h"
#endif

#endif /* IMU_DRIVER_H_ */