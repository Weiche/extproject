/*
 * SERIAL_Protocol.h
 *
 *  Created on: 2015”N7ŒŽ16“ú
 *      Author: First Version Tetsu Gi 2015/07/16
 */
#ifndef SERIAL_PROTOCOL_H_
#define SERIAL_PROTOCOL_H_

/* Include					*/
#include "SERIAL_Driver.h"
#include <stdint.h>

/* Export Constant			*/
#define	SERIAL_STATE_CONNONLINE		(0)
#define SERIAL_STATE_CONNOFFLINE	(1)

#define SERIAL_STATE_PACKETIDLE		(0)
#define SERIAL_STATE_PACKETRECV		(1)

/* Export Macro				*/
/* Export Typedef			*/
typedef int32_t state_t;

struct s_data {
	uint8_t data_ascii[10];
	uint8_t length;
	uint8_t type;
};
typedef struct s_data data_t;

struct s_SERIAL_protocol {
	SERIAL_Driver_t Driver;
	int32_t CONN_State;
	int32_t PACKET_State;
	int32_t ERROR_State;
	uint32_t PACKET_Timeout;
	uint32_t CONN_Timeout;
	uint8_t TXPacketBuffer[SERIAL_PROTOCOL_TXBUFFERSIZE];
	uint8_t TempRXBuffer[64];
	int32_t TempRXBufferIndex;
};
typedef struct s_SERIAL_protocol SERIAL_Protocol_t;

/* Public Function Prototype */

void SERIAL_ProtocolInit(SERIAL_Protocol_t *this);
void SERIAL_ProtocolReset(SERIAL_Protocol_t *this);
int32_t SERIAL_ProtocolRecv(SERIAL_Protocol_t *this, data_t *buff,
		uint32_t max_num);/* return receive packet number */
int32_t SERIAL_ProtocolSend(SERIAL_Protocol_t *this, const data_t *pdata,
		uint32_t num);
void SERIAL_ProtocolBackground(SERIAL_Protocol_t *this);
state_t SERIAL_ProtocolGetConnectionState(SERIAL_Protocol_t *this);
state_t SERIAL_ProtocolGetPacketState(SERIAL_Protocol_t *this);


#endif /* SERIAL_PROTOCOL_H_ */
