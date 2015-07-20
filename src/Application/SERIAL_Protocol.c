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
void	SERIAL_ProtocolInit(SERIAL_Protocol_t *this){
	SERIAL_DriverInit(&this->Driver);
}
void	SERIAL_ProtocolReset(SERIAL_Protocol_t *this){

}

#ifndef SERIAL_ProtocolGetConnectionState
int32_t SERIAL_ProtocolGetConnectionState(void){
	return SERIAL_STATE_CONNONLINE;
}
int32_t SERIAL_ProtocolGetPacketState(void){
	return SERIAL_STATE_CONNOFFLINE;
}
#endif

static int32_t SERIAL_ProtocolAssemblePacket(uint8_t *buff , uint32_t buffersize,const data_t *pdata){
	uint32_t length,type,i;
	length = pdata->length;
	type = pdata->type;
	ASSERT( length <= 10 );
	if( buffersize >=  (pdata->length + 6) ){
		/* Assemble Packet */
		*buff++ = SERIAL_PROTOCOL_START_CODE;
		*buff++ = (type / 10) % 10 + 0x30;
		*buff++ = type % 10 + 0x30;
		*buff++ = (length / 10) % 10 + 0x30;
		*buff++ = length % 10 + 0x30;
		i = 0;
		while(length--){
			*buff++ = pdata->data_ascii[i++];
		}
		*buff++ = SERIAL_PROTOCOL_END_CODE;
		return (pdata->length + 6);
	}
	else{
		return ERROR_NotEnoughSize;
	}
}

int32_t SERIAL_ProtocolRecv(SERIAL_Protocol_t *this, data_t *buff, uint32_t max_num){
	/* 1 Check input
	 * 2 Call driver receiver to check if any packet received
	 * 3 Disassemble packet with protocol format
	 * 4 Copy to data_t *buff
	 */
	return 0;
}/* return receive packet number */

int32_t SERIAL_ProtocolSend(SERIAL_Protocol_t *this, const data_t *pdata, uint32_t num){
	int32_t ret,i,size,packet_count = 0;
	uint8_t *p;
	ASSERT(buff);
	ASSERT(pdata);
	p = this->TXPacketBuffer;
	size = SERIAL_PROTOCOL_TXBUFFERSIZE;
	/* Assemble Packet */
	for(i = 0; num > 0; num--){
		ret = SERIAL_ProtocolAssemblePacket(p , size ,&(pdata[i]) );
		/* Error */
		if( ret < 0 ){
			break;
		}else{
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
	ret = SERIAL_DriverSend( &(this->Driver), this->TXPacketBuffer, size);
	if( ret == size){
		/* success */
		return packet_count;
	}else{
		/* failed, return error code */
		return ret;
	}
}

void SERIAL_ProtocolBackground(SERIAL_Protocol_t *this){
	SERIAL_DriverBackground(&this->Driver);
	this->CONN_State = SERIAL_STATE_CONNOFFLINE;
	this->CONN_State = SERIAL_STATE_CONNONLINE;
	this->PACKET_State = SERIAL_STATE_PACKETIDLE;
	this->PACKET_State = SERIAL_STATE_PACKETRECV;

}
/**************************************************************************************************
    end of file
**************************************************************************************************/
