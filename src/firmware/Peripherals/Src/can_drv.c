/* Includes ------------------------------------------------------------------*/
#include "can_drv.h"

//can Enable
void CAN_Enable(CAN_HandleTypeDef* hcan)
{
	//Config can rx filter
	CAN_FilterTypeDef* sFilterConfig;
	sFilterConfig->FilterBank = 0;							//choose filter 0 to config for can 1
	sFilterConfig->FilterMode = CAN_FILTERMODE_IDMASK;		//flag mask mode(just can flag in mask == filter flag in mask will be rx)
	sFilterConfig->FilterScale = CAN_FILTERSCALE_32BIT;		//filter scale(mask lenth)
	sFilterConfig->FilterIdHigh = 0;						//flag high 16 bit
	sFilterConfig->FilterIdLow = 0;							//flag low 16 bit
	sFilterConfig->FilterMaskIdHigh = 0;					//mask bit
	sFilterConfig->FilterMaskIdLow = 0;						//mask bit
	sFilterConfig->FilterFIFOAssignment = CAN_FILTER_FIFO0;	//associated to FIFO 0
	sFilterConfig->FilterActivation = ENABLE;				//enable filter
	sFilterConfig->SlaveStartFilterBank = 14;				//if config can 2 filter, FilterBank+=SlaveStartFilterBank
	HAL_CAN_ConfigFilter(hcan, sFilterConfig);				//blind filter with can
	
	//Enable FIFO0
	HAL_CAN_ActivateNotification(hcan, CAN_IT_RX_FIFO0_MSG_PENDING);
	
	//Enable can module
	if(HAL_CAN_Start(hcan)!=HAL_OK)while(1);
} 

//this func define weakly for it £¨when can rx new msg will triggle£©(this func define by hal)  
void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
	//get rx data frame
	HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &can_rx_frame.header, can_rx_frame.data);
	if(hcan == &hcan1){CAN1_RX_Handler(can_rx_frame.header.StdId, can_rx_frame.data);}
	if(hcan == &hcan2){CAN2_RX_Handler(can_rx_frame.header.StdId, can_rx_frame.data);}
}
                                                                      
//set tx id
void Set_tx_ID(uint32_t txId)
{
	pheader.StdId=txId;
}
