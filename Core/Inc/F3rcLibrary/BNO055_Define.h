/*
 * BNO055_Define.h
 *
 *  Created on: Aug 31, 2022
 *      Author: reiii
 */

#ifndef INC_F3RCLIBRARY_BNO055_DEFINE_H_
#define INC_F3RCLIBRARY_BNO055_DEFINE_H_

#define BNO055_ACC_SCALE							(100.f)								// 1 m/ss = 100LSB
#define BNO055_MAG_SCALE							(16.f)								// 1 mT = 16LSB
#define BNO055_GYR_SCALE							(16.f)								// 1 Deg/S = 16LSB
#define BNO055_EULER_SCALE						(16.f)								// Unit = Degrees
#define BNO055_QUA_SCALE							((float)(1<<14))

#define BNO055_OPERATING_CONFIG				(0x0)									// Config Mode
#define BNO055_OPERATING_ACCGYRO			(0x5)									// Non-Fusion Mode
#define BNO055_OPERATING_MAGGYRO			(0x6)									// Non-Fusion Mode
#define BNO055_OPERATING_AMG					(0x7)									// Non-Fusion Mode
#define BNO055_OPERATING_COMPASS			(0x9)									// Fusion Mode
#define BNO055_OPERATING_NDOF_FMC_OFF	(0xB)									// Fusion Mode
#define BNO055_OPERATING_NDOF					(0xC)									// Fusion Mode

#define BNO055_A_RANGE_2G						(0x0)
#define BNO055_A_RANGE_4G						(0x1)										// Default
#define BNO055_A_RANGE_8G						(0x2)
#define BNO055_A_RANGE_16G					(0x3)
#define BNO055_A_BANDWIDTH_7_81HZ		(0x0)
#define BNO055_A_BANDWIDTH_15_63HZ	(0x1)
#define BNO055_A_BANDWIDTH_31_25HZ	(0x2)
#define BNO055_A_BANDWIDTH_62_5HZ		(0x3)										// Default
#define BNO055_A_BANDWIDTH_125HZ		(0x4)
#define BNO055_A_BANDWIDTH_250HZ		(0x5)
#define BNO055_A_BANDWIDTH_500HZ		(0x6)
#define BNO055_A_BANDWIDTH_1000HZ		(0x7)

#define BNO055_G_RANGE_2000DPS			(0x0)										// Default
#define BNO055_G_RANGE_1000DPS			(0x1)
#define BNO055_G_RANGE_500DPS				(0x2)
#define BNO055_G_RANGE_250DPS				(0x3)
#define BNO055_G_RANGE_125DPS				(0x4)
#define BNO055_G_BANDWIDTH_523HZ		(0x0)
#define BNO055_G_BANDWIDTH_230HZ		(0x1)
#define BNO055_G_BANDWIDTH_116HZ		(0x2)
#define BNO055_G_BANDWIDTH_47HZ			(0x3)
#define BNO055_G_BANDWIDTH_23HZ			(0x4)
#define BNO055_G_BANDWIDTH_12HZ			(0x5)
#define BNO055_G_BANDWIDTH_64HZ			(0x6)
#define BNO055_G_BANDWIDTH_32HZ			(0x7)										// Default

#define BNO055_M_DOR_2HZ						(0x0)
#define BNO055_M_DOR_6HZ						(0x1)
#define BNO055_M_DOR_8HZ						(0x2)
#define BNO055_M_DOR_10HZ						(0x3)										// Default
#define BNO055_M_DOR_15HZ						(0x4)
#define BNO055_M_DOR_20HZ						(0x5)
#define BNO055_M_DOR_25HZ						(0x6)
#define BNO055_M_DOR_30HZ						(0x7)

#define BNO055_ADDR					(0x28 << 1)
#define BNO055_CHIP_ID			(0xA0)

// Page 0/1 Same
#define BNO055_REG_PAGE_ID			(0x7)

// Page 0
#define BNO055_REG_CHIP_ID			(0x0)
#define BNO055_REG_ACC_X				(0x8)
#define BNO055_REG_MAG_X				(0xE)
#define BNO055_REG_GYR_X				(0x14)
#define BNO055_REG_EUL_HEADING	(0x1A)											// Heading Roll Pitch
#define BNO055_REG_QUA_W				(0x20)											// W X Y Z
#define BNO055_REG_LIA_X				(0x28)
#define BNO055_REG_GRV_X				(0x2E)
#define BNO055_REG_OPR_MODE			(0x3D)
#define BNO055_REG_ACC_OFFSET_X	(0x55)
#define BNO055_REG_MAG_OFFSET_X	(0x5B)
#define BNO055_REG_GYR_OFFSET_X	(0x61)
#define BNO055_REG_ACC_RADIUS		(0x67)
#define BNO055_REG_MAG_RADIUS		(0x69)

// page 1
#define BNO055_REG_ACC_CONFIG		(0x8)
#define BNO055_REG_MAG_CONFIG		(0x9)
#define BNO055_REG_GYR_CONFIG		(0xA)

#endif /* INC_F3RCLIBRARY_BNO055_DEFINE_H_ */
