
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
	uint8_t data[MAX_BUF_LEN];//�������ݻ������
	uint16_t num; //���������Ч���ݸ���
	uint8_t txbit; //��¼��ǰ���ݷ�������λ 
	uint8_t txcnt; //��¼��ǰ�ѷ������ݸ��� 
	}TX_BUF;//���ͻ��������ݽṹ 

typedef struct{ 
	uint8_t data[MAX_BUF_LEN]; //�������ݻ������
	uint16_t num; //��¼��ǰ���յ����ݵĸ���
	uint8_t rxbit; //��¼��ǰ�������ݵ�����λ 
	uint8_t SBUF; //��¼���һ�ν��յ�����Ч�ֽ� 
	}RX_BUF;//���ջ�����

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
