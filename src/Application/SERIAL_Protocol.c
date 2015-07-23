#include "CONFIG.h"
#include <stdint.h>
#include "SERIAL_Driver.h"
#include "SERIAL_Protocol.h"
/* Private Macro */
#define NUM2ASCII(num)		((num)   + 0x30)
#define ASCII2NUM(ascii)	((ascii) - 0x30)
#define __PACKET_TIMEOUT		(2000)
#define __CONNECTION_TIMEOUT	(1000)
struct s_packet_buffer {
	data_t buffer[2];
	int16_t index;
	int16_t flag;
};
typedef struct s_packet_buffer DATA_PacketBuffer_t;
static DATA_PacketBuffer_t __PacketBuffer;

/* Private Functions */
static int32_t SERIAL_ProtocolAssemblePacket(uint8_t *buff, uint32_t buffersize,
		const data_t *pdata) {
	uint32_t length, type, i;
	ASSERT( buff );
	ASSERT( pdata );
	length = pdata->length;
	type = pdata->type;
	ASSERT( length <= 10 );
	ASSERT( type <= 99 );
	if (buffersize >= (pdata->length + 6)) {
		/* Assemble Packet */
		*buff++ = SERIAL_PROTOCOL_START_CODE;
		*buff++ = NUM2ASCII((type / 10) % 10);
		*buff++ = NUM2ASCII(type % 10);
		*buff++ = NUM2ASCII((length / 10) % 10);
		*buff++ = NUM2ASCII(length % 10);
		i = 0;
		while (length--) {
			*buff++ = pdata->data_ascii[i++];
		}
		*buff++ = SERIAL_PROTOCOL_END_CODE;
		return (pdata->length + 6);
	} else {
		return ERROR_NotEnoughSize;
	}
}

static int32_t SERIAL_ProtocolDisassemblePacket(const uint8_t *buff,
		data_t *pdata) {
	uint32_t length, type, i;
	ASSERT( buff );
	(void) SERIAL_ProtocolDisassemblePacket;
	ASSERT( pdata );
	if (buff[0] != SERIAL_PROTOCOL_START_CODE) {
		return ERROR_SERIAL_PACKET;
	}
	/* Check if type and length is a number */
	for (i = 1; i <= 4; i++) {
		if ( ASCII2NUM(buff[i]) > 9) {
			return ERROR_SERIAL_PACKET;
		}
	}
	/* convert ASCII to decimal */
	type = ASCII2NUM(buff[1]) * 10;
	type += ASCII2NUM(buff[2]);
	length = ASCII2NUM(buff[3]) * 10;
	length += ASCII2NUM(buff[4]);

	/* Check length */
#ifndef GENERAL
	if ( (type == 1 && length == 3) || (type == 0 && length == 6)) {

	}else{
		return ERROR_SERIAL_PACKET;
	}
#else
	if (length > 10) {
		return ERROR_SERIAL_PACKET;
	}
#endif
	/* Check End code */
	if (buff[length + 5] != SERIAL_PROTOCOL_END_CODE) {
		return ERROR_SERIAL_PACKET;
	}

	/* Copy data */
	buff += 5;
	pdata->length = length;
	pdata->type = type;
	while (length) {
		pdata->data_ascii[pdata->length - length] = *buff++;
		length--;
	}
	return ERROR_OK;
}
/* Public Functions */
void SERIAL_ProtocolInit(SERIAL_Protocol_t *this) {
	SERIAL_DriverInit(&this->Driver);
}
void SERIAL_ProtocolReset(SERIAL_Protocol_t *this) {
	SERIAL_DriverReset(&this->Driver);
}

int32_t SERIAL_ProtocolRecv(SERIAL_Protocol_t *this, data_t *buff,
		uint32_t max_num) {
	int32_t ret = 0;
	/* 1 Check input */
	ASSERT(this);ASSERT(buff);
	if(this->ERROR_State){
		this->ERROR_State = 0;
		return ERROR_SERIAL_FAIL;
	}else{
		while (max_num--) {
			if( __PacketBuffer.flag & (1<<0) )
			{
				*buff++ = __PacketBuffer.buffer[0];
				__PacketBuffer.flag &= ~(1<<0);
				ret ++;
			}else if(__PacketBuffer.flag & (1<<1)){
				*buff++ = __PacketBuffer.buffer[1];
				__PacketBuffer.flag &= ~(1<<1);
				ret ++;
			}
			/* return receive packet number */
		}
		return ret;
	}

}

int32_t SERIAL_ProtocolSend(SERIAL_Protocol_t *this, const data_t *pdata,
		uint32_t num) {
	int32_t ret, i, size, packet_count = 0;
	uint8_t *p;
	ASSERT(this);ASSERT(pdata);
	p = this->TXPacketBuffer;
	size = SERIAL_PROTOCOL_TXBUFFERSIZE;
	/* Assemble Packet */
	for (i = 0; num > 0; num--) {
		ret = SERIAL_ProtocolAssemblePacket(p, size, &(pdata[i]));
		/* Error */
		if (ret < 0) {
			break;
		} else {
			/* Success assemble the packet */
			/* Set start pointer for next packet */
			p += ret;
			/* Calculate space remain */
			size -= ret;
			/* Count one */
			packet_count++;
		}
		i++;
	}
	size = SERIAL_PROTOCOL_TXBUFFERSIZE - size;
	/* Send Packet */
	ret = SERIAL_DriverSend(&(this->Driver), this->TXPacketBuffer, size);
	if (ret == size) {
		/* success */
		return packet_count;
	} else {
		/* failed, return error code */
		return ret;
	}
}
static int32_t __SERIAL_ProtocolDropUntilChar(SERIAL_Protocol_t *this,
		uint8_t char_expect) {
	int32_t ret;
	uint8_t temp = 0;
	do {
		ret = SERIAL_DriverRecv(&this->Driver, &(temp), 1);
		if (temp == char_expect) {
			return ERROR_OK;
		} else {
			nop();
		}
	} while (ret > 0);
	return ERROR_Empty;
}
/*
 *
 * @return number of char get from driver
 */
static int32_t __SERIAL_ProtocolGetUntilChar(SERIAL_Protocol_t *this,
		uint8_t char_expect, uint8_t *buff, uint8_t *num) {
	int32_t ret;
	ASSERT(this);ASSERT(num);ASSERT(buff);
	*num = 0;
	do {
		ret = SERIAL_DriverRecv(&this->Driver, buff, 1);
		ASSERT( ret <= 1 );
		if (ret == 1) {
			(*num) += ret;
			if ((*buff) == char_expect) {
				return ERROR_OK;
			}
			buff += ret;
		}
	} while (ret > 0);
	return ERROR_Empty;
}
/* Connection Machine:Actions */
static void __ActionGoOnline(SERIAL_Protocol_t *this) {
	this->CONN_State = SERIAL_STATE_CONNONLINE;
	this->CONN_Timeout = 2000;
}

static void __ActionGoOffline(SERIAL_Protocol_t *this) {
	this->CONN_State = SERIAL_STATE_CONNOFFLINE;
}

static void __StateActionOnline(SERIAL_Protocol_t *this) {
	if (this->CONN_Timeout == 0) {
		__ActionGoOffline(this);
	}
	this->CONN_Timeout--;
}

/* Packet State Machine:Actions */
static void __ActionGoPacketRECV(SERIAL_Protocol_t *this) {
	this->PACKET_Timeout = __PACKET_TIMEOUT;
	this->PACKET_State = SERIAL_STATE_PACKETRECV;
}
static void __ActionGoPacketIDLE(SERIAL_Protocol_t *this) {
	this->PACKET_State = SERIAL_STATE_PACKETIDLE;
	this->TempRXBufferIndex = 0;
	this->TempRXBuffer[0] = '\0';
}
static void __ActionEndCodeRecv(SERIAL_Protocol_t *this) {

	int32_t ret;
	data_t temp;
	/* disassemble the packet and check packet format */
	ret = SERIAL_ProtocolDisassemblePacket(this->TempRXBuffer, &temp);

	/* if format is right put into buffer */
	if (ret == ERROR_OK) {
		{
			__PacketBuffer.buffer[__PacketBuffer.index] = temp;
			__PacketBuffer.flag |= (1<<__PacketBuffer.index);
			__PacketBuffer.index ++;
			__PacketBuffer.index &= 0x01;
		}
		__ActionGoOnline(this);
	}else if(ret == ERROR_SERIAL_PACKET){
		this->ERROR_State |= (1<<3);
	}
	__ActionGoPacketIDLE(this);
}

static void __ActionStartCodeRecv(SERIAL_Protocol_t *this) {
	/* store start code */
	this->TempRXBuffer[0] = SERIAL_PROTOCOL_START_CODE;
	this->TempRXBufferIndex = 1;
	__ActionGoPacketRECV(this);
}

static void __StateActionIDLE(SERIAL_Protocol_t *this) {
	int32_t ret;
	/* try to receive START_CODE*/
	ret = __SERIAL_ProtocolDropUntilChar(this,
	SERIAL_PROTOCOL_START_CODE);
	/* start code received */
	if (ret == ERROR_OK) {
		__ActionStartCodeRecv(this);
	} else {
		/* No Start code found */
	}
}

static void __StateActionRECV(SERIAL_Protocol_t *this) {
	int32_t ret;
	uint8_t num;
	/* try to fetch received data from driver until end code */
	num = 0;
	ret = __SERIAL_ProtocolGetUntilChar(this, SERIAL_PROTOCOL_END_CODE,
			&this->TempRXBuffer[this->TempRXBufferIndex], &num);
	this->TempRXBufferIndex += num;
	/* if no data received */
	if (ret == ERROR_Empty) {
		this->PACKET_Timeout--;
	}
	/* if end code received */
	else if (ret == ERROR_OK) {
		__ActionEndCodeRecv(this);
	} else {
		this->PACKET_Timeout = __PACKET_TIMEOUT;
	}
	/* timeout event */
	if (this->PACKET_Timeout == 0) {
		__ActionGoPacketIDLE(this);
	}
}
void SERIAL_ProtocolBackground(SERIAL_Protocol_t *this) {
	SERIAL_DriverBackground(&this->Driver);
	/* Check UART hardware errors */
	if (this->Driver.Error_State & 0x03) {
		this->ERROR_State = this->Driver.Error_State;
		this->Driver.Error_State = 0;
		/* transfer the error_state to upper layer */
	} else {
		/* Packet receive State machine*/
		if (this->PACKET_State == SERIAL_STATE_PACKETIDLE) {
			/* STATE IDLE */
			__StateActionIDLE(this);
		}

		else if (this->PACKET_State == SERIAL_STATE_PACKETRECV) {
			/* STATE RECEIVING */
			__StateActionRECV(this);
		}

		/* Connection State machine*/
		if (this->CONN_State == SERIAL_STATE_CONNONLINE) {
			/* STATE ONLINE */
			__StateActionOnline(this);
		}
	}
}

state_t SERIAL_ProtocolGetConnectionState(SERIAL_Protocol_t *this) {
	ASSERT(this);
	return this->CONN_State;
}
state_t SERIAL_ProtocolGetPacketState(SERIAL_Protocol_t *this) {
	ASSERT(this);
	return this->PACKET_State;
}
/**************************************************************************************************
 end of file
 **************************************************************************************************/
