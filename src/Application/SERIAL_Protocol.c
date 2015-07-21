/*""FILE COMMENT""*********************************************************************************
 *  System Name : このプログラムは教育用です。(転用不可)
 *  File Name   : SERIAL.c
 *  Contents    : デバイスドライバ設計コース 総合演習 プログラム作成
 *              : 課題C:パソコンからのコマンド指示に応じたパルスモータの制御
 *  Model       : 
 *  CPU         : RXファミリ/RX600シリーズ/RX62Nグループ
 *  Compiler    : RXファミリ C/C++コンパイラ
 *  OS          : 使用せず
 *  Programmer  : ルネサス半導体トレーニングセンター
 *  Note        : コンパイラオブジェクトオプション-nostuff指定
 *              : コンパイラオブジェクトオプション-section=L=C指定
 *              : コンパイラ最適化オプション-noschedule指定
 *              : コンパイラ最適化オプション-case=ifthen指定
 **************************************************************************************************
 * Copyright (C) 2011(2012) Renesas Electronics Corporation
 *  and Renesas Solutions Corp. All rights reserved.
 **************************************************************************************************
 *  History     : 
 *""FILE COMMENT END""****************************************************************************/
#include "CONFIG.h"
#include <stdint.h>
#include "SERIAL_Driver.h"
#include "SERIAL_Protocol.h"
/* Private Macro */
#define NUM2ASCII(num)		((num)   + 0x30)
#define ASCII2NUM(ascii)	((ascii) - 0x30)

/* Private Functions */
static int32_t SERIAL_ProtocolAssemblePacket(uint8_t *buff, uint32_t buffersize,
		const data_t *pdata) {
	uint32_t length, type, i;
	length = pdata->length;
	type = pdata->type;
	ASSERT( length <= 10 );
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
	if (length > 10) {
		return ERROR_SERIAL_PACKET;
	}

	/* Check End code */
	if (buff[length + 5] != SERIAL_PROTOCOL_END_CODE) {
		return ERROR_SERIAL_PACKET;
	}

	/* Copy data */
	buff += 5;
	pdata->length = length;
	pdata->type = type;
	while (length--) {
		pdata->data_ascii[pdata->length - length] = *buff++;
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
	while (max_num--) {

		/* 2 Call driver receiver to check if any packet received
		 * 3 Disassemble packet with protocol format
		 * 4 Copy to data_t *buff
		 */
		/* return receive packet number */
	}
	return ret;
}

int32_t SERIAL_ProtocolSend(SERIAL_Protocol_t *this, const data_t *pdata,
		uint32_t num) {
	int32_t ret, i, size, packet_count = 0;
	uint8_t *p;
	ASSERT(buff);ASSERT(pdata);
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
	ASSERT(this);
	ASSERT(num);
	ASSERT(buff);
	*num = 0;
	do {
		ret = SERIAL_DriverRecv(&this->Driver, buff, 1);
		if (ret == 1) {
			if (*buff == char_expect) {
				return ERROR_OK;
			}
			buff++;
			(*num)++;
		}
	} while (ret > 0);
	return ERROR_Empty;
}

static int32_t __CONNStateMaching(SERIAL_Protocol_t *this,
		uint32_t event) {
	int32_t ret = 0;
	ASSERT(this);
	if( this->CONN_State == SERIAL_STATE_CONNONLINE ){

	}else if(this->CONN_State == SERIAL_STATE_CONNOFFLINE){

	}else{
		ASSERT(0);
	}
	return ret;
}

void SERIAL_ProtocolBackground(SERIAL_Protocol_t *this) {
	int32_t ret;

	SERIAL_DriverBackground(&this->Driver);
	/* Check UART hardware errors */
	if (this->Driver.Error_State == 1) {
		this->Driver.Error_State = 0;
		/* transfer the error_state to upper layer */
		this->ERROR_State |= 1;
	} else {
		/* STATE IDLE */
		if (this->PACKET_State == SERIAL_STATE_PACKETIDLE) {

			/* try to receive START_CODE*/
			ret = __SERIAL_ProtocolDropUntilChar(this,
			SERIAL_PROTOCOL_START_CODE);
			if (ret == ERROR_OK) {
				this->TempRXBuffer[0] = SERIAL_PROTOCOL_START_CODE;
				this->TempRXBufferIndex = 1;
				this->PACKET_State = SERIAL_STATE_PACKETRECV;
			} else {
				/* No Start code found */
				nop();
			}
		}
		/* STATE RECEIVING */
		else if (this->PACKET_State == SERIAL_STATE_PACKETRECV) {
			ret = __SERIAL_ProtocolGetUntilChar(this, SERIAL_PROTOCOL_END_CODE,
					&this->TempRXBuffer[this->TempRXBufferIndex]);
			if( ret == ERROR_Empty ){

			}else{

			}
		}
	}
	this->CONN_State = SERIAL_STATE_CONNOFFLINE;
	this->CONN_State = SERIAL_STATE_CONNONLINE;
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
