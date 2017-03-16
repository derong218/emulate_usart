
#ifndef __io_usart_H
#define __io_usart_H
#ifdef __cplusplus
 extern "C" {
#endif
#include "main.h"
#include "stm32f1xx_hal.h"

#define TX_MODE 1 
#define RX_MODE 0 

#define MAX_BUF_LEN 512

typedef struct{ 
	uint8_t data[MAX_BUF_LEN];//发送数据缓冲队列
	uint16_t num; //缓冲队列有效数据个数
	uint8_t txbit; //记录当前数据发送数据位 
	uint8_t txcnt; //记录当前已发送数据个数 
	}TX_BUF;//发送缓冲区数据结构 

typedef struct{ 
	uint8_t data[MAX_BUF_LEN]; //接收数据缓冲队列
	uint16_t num; //记录当前接收到数据的个数
	uint8_t rxbit; //记录当前接收数据的数据位 
	uint8_t SBUF; //记录最近一次接收到的有效字节 
	}RX_BUF;//接收缓冲区

 void IO_Usart_Init(void);
 void io_usart_real_main(void);
 void TIM_RX_Callback(void);
 void EXT_RX_Callback(void);

#ifdef __cplusplus
}


#endif
#endif /*__ usart_H */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
