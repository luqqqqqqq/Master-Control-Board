
#ifndef __CAN_DRV_H
#define __CAN_DRV_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

//can rx data frame struct
typedef struct {
	CAN_RxHeaderTypeDef header;
	uint8_t 			data[8];
} CAN_RxFrameTypeDef;

//can rx data frame
static CAN_RxFrameTypeDef can_rx_frame;

//user rx msg from can 
static uint8_t CAN1_Msg[8];
static uint8_t CAN2_Msg[8];

//can tx header(StdId=ID ExtId=0 IDE=0 RTR=0 DLC=8)
static CAN_TxHeaderTypeDef pheader={0,0,0,0,8};

//can for Enable 
extern CAN_HandleTypeDef hcan1;
extern CAN_HandleTypeDef hcan2;

//can Enable func
void CAN_Enable(CAN_HandleTypeDef* hcan);

//set tx id
void Set_tx_ID(uint32_t txId);

//handle need to rewrite
__WEAK void CAN1_RX_Handler(uint32_t rxId, uint8_t *rxBuf);
__WEAK void CAN2_RX_Handler(uint32_t rxId, uint8_t *rxBuf);

//can tx func in hal_can.c, use this func to tx
//HAL_StatusTypeDef HAL_CAN_AddTxMessage(CAN_HandleTypeDef *hcan, CAN_TxHeaderTypeDef *pHeader, uint8_t aData[], uint32_t *pTxMailbox);

#endif
