/* Includes ------------------------------------------------------------------*/
#include "user_handler.h"

//all handler
void CAN1_RX_Handler(uint32_t rxId, uint8_t *rxBuf)
{
	if(rxId==0){
		for(int i=0;i<8;i++){
			CAN1_Msg[i]=rxBuf[i];
		}
	}
}
void CAN2_RX_Handler(uint32_t rxId, uint8_t *rxBuf)
{
	if(rxId==0){
		for(int i=0;i<8;i++){
			CAN2_Msg[i]=rxBuf[i];
		}
	}
}
void UART1_IDLE_Handler(uint8_t* buf)
{

}
void UART2_IDLE_Handler(uint8_t* buf)
{
	
}
void UART3_IDLE_Handler(uint8_t* buf)
{
	
}
void UART4_IDLE_Handler(uint8_t* buf)
{
	
}
void UART5_IDLE_Handler(uint8_t* buf)
{
	
}
void UART6_IDLE_Handler(uint8_t* buf)
{
	
}
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	
}
