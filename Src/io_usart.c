#include "io_usart.h"
#include "tim.h"

typedef enum {
	IO_UART_STATE_RESET = 0x00, /*!< Peripheral is not initialized                      */
	IO_UART_STATE_READY = 0x01, /*!< Peripheral Initialized and ready for use           */
	IO_UART_STATE_BUSY = 0x02, /*!< an internal process is ongoing                     */
	IO_UART_STATE_BUSY_TX = 0x12, /*!< Data Transmission process is ongoing               */
	IO_UART_STATE_BUSY_RX = 0x22, /*!< Data Reception process is ongoing                  */
	IO_UART_STATE_BUSY_TX_RX = 0x32, /*!< Data Transmission and Reception process is ongoing */
	IO_UART_STATE_TIMEOUT = 0x03, /*!< Timeout state                                      */
	IO_UART_STATE_ERROR = 0x04 /*!< Error                                              */
} IO_UART_StateTypeDef;

RX_BUF rxbuf; //���ͻ�����ȫ�ֱ���
IO_UART_StateTypeDef State;
uint16_t read_index;

void IO_Usart_Init() {

	rxbuf.num = 0;
	rxbuf.SBUF = 0x00;
	rxbuf.rxbit = 0;
	State = IO_UART_STATE_READY;
	HAL_TIM_Base_Start_IT(&htim2);
}

void io_usart_real_main() {
	if (read_index != rxbuf.num) {
		int tmp_data=rxbuf.data[read_index];
		printf("%s", (uint8_t*)&tmp_data);
		read_index++;
		if (read_index >= MAX_BUF_LEN)
			read_index = 0;
	}
}

/**
 * ���� ��ʱ���жϴ���
 */
void TIM_RX_Callback() {
	if ((State == IO_UART_STATE_BUSY_RX)
			|| (State == IO_UART_STATE_BUSY_TX_RX)) {
		if (rxbuf.rxbit % 2 == 0) {
			if (rxbuf.rxbit / 2 == 9) { //ֹͣλ
				if (RX_BIT_DATA) {
					HAL_TIM_Base_Stop_IT(&htim2);
					rxbuf.data[rxbuf.num] = rxbuf.SBUF;
					rxbuf.num++;
					if (rxbuf.num >= MAX_BUF_LEN) {
						rxbuf.num = 0;
					}
					if (State == IO_UART_STATE_BUSY_TX_RX) {
						State = IO_UART_STATE_BUSY_TX;
					} else {
						State = IO_UART_STATE_READY;
					}
					rxbuf.rxbit = 0;
				}

				return;
			}

			if (rxbuf.rxbit / 2 > 0) {
				if (RX_BIT_DATA)
					rxbuf.SBUF |= (1 << (rxbuf.rxbit / 2 - 1));
			}
		}

		rxbuf.rxbit++;
	}
}
/**
 * �ⲿ�жϴ���ӿڣ����ڼ����յ��½���  ����
 */
void EXT_RX_Callback() {
	if (((State == HAL_UART_STATE_READY) || (State == HAL_UART_STATE_BUSY_TX))
			&& !RX_BIT_DATA) {
		if (State == IO_UART_STATE_BUSY_TX) {
			State = IO_UART_STATE_BUSY_TX_RX;
		} else {
			State = IO_UART_STATE_BUSY_RX;
		}
		rxbuf.rxbit = 0; //����λ��0
		rxbuf.SBUF = 0;
		HAL_TIM_Base_Start_IT(&htim2); //������ʱ��
	}

}
