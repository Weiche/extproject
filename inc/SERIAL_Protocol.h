/*
 * SERIAL_Protocol.h
 *
 *  Created on: 2015”N7ŒŽ16“ú
 *      Author: First Version Tetsu Gi 2015/07/16
 */
#ifndef SERIAL_PROTOCOL_H_
#define SERIAL_PROTOCOL_H_

/* Include					*/

/* Export Constant			*/

/* Export Macro				*/
#define	SERIAL_STATE_CONNONLINE		(0)
#define SERIAL_STATE_CONNOFFLINE	(1)

#define SERIAL_STATE_PACKETIDLE		(0)
#define SERIAL_STATE_PACKETRECV		(1)
/* Export Typedef			*/
struct s_data {
	uint8_t data_ascii[10];
	uint8_t length;
	uint8_t type;
};
typedef struct s_data data_t;
/* Public Function Prototype */

void	Serial_ProtocolInit(void);
void	Serial_ProtocolReset(void);
int32_t Serial_ProtocolGetConnectionState(void);
int32_t Serial_ProtocolGetPacketState(void);
int32_t Serial_ProtocolRecv(data_t *buff);/* return receive packet number */
int32_t Serial_ProtocolSend(const data_t *buff);

#endif /* SERIAL_PROTOCOL_H_ */
