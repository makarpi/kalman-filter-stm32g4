/*
 * mems.h
 *
 *  Created on: 26 sty 2020
 *      Author: Mateusz
 */

#ifndef SRC_HARDWARE_MEMS_DRIVER_MEMS_H_
#define SRC_HARDWARE_MEMS_DRIVER_MEMS_H_

void Mems_Init(void);
int32_t LSM6DSO_I2C_Write(void *handle, uint8_t reg, uint8_t *bufp, uint16_t len);
int32_t LSM6DSO_I2C_Read(void *handle, uint8_t reg, uint8_t *bufp, uint16_t len);

#endif /* SRC_HARDWARE_MEMS_DRIVER_MEMS_H_ */
