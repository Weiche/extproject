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
#define SERIAL_PROTOCOL_TXBUFFERSIZE	(128)
/* Export Macro				*/
#define SERIAL_ProtocolGetConnectionState(p)	(p->CONN_State)
#define SERIAL_ProtocolGetPacketState(p)		(p->PACKET_State)

/* Export Typedef			*/
typedef int32_t state_t;

struct s_data {
	uint8_t data_ascii[10];
	uint8_t length;
	uint8_t type;
};
typedef struct s_data data_t;

struct s_SERIAL_protocol {
	int32_t CONN_State;
	int32_t PACKET_State;
	SERIAL_Driver_t Driver;
	uint8_t TXPacketBuffer[SERIAL_PROTOCOL_TXBUFFERSIZE];
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

#ifndef SERIAL_ProtocolGetConnectionState
state_t SERIAL_ProtocolGetConnectionState(void);
state_t SERIAL_ProtocolGetPacketState(void);
#endif

#endif /* SERIAL_PROTOCOL_H_ */
