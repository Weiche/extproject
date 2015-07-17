/*
 * SERIAL_Driver.h
 *
 *  Created on: 2015”N7ŒŽ16“ú
 *      Author: First Version Tetsu Gi 2015/07/16
 */

#ifndef SERIAL_DRIVER_H_
#define SERIAL_DRIVER_H_
void	Serial_DriverInit	(void);
void	Serial_DriverReset	(void);
void	Serial_DriverSend	(const uint8_t *buff, uint8_t num);
int		Serial_DriverRecv	(uint8_t *buff, uint8_t max_num);


#endif /* SERIAL_DRIVER_H_ */
