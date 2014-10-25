#ifndef RS232_HANDLER_H
#define RS232_HANDLER_H
 
#include <rtai_serial.h>
#include <rtai_sem.h>  
#include <rtai_registry.h>  
#include <rtai_shm.h>
#include <rtai_nam2num.h>
#include <stdbool.h>
#include <gtk/gtk.h>
#include "../Misc/Misc.h"
#include "../System/ShmSemNum/ShmSemNum.h"
#include "../System/TimeStamp/TimeStamp.h"

#define DIO_CTRL_TX_BUFFER_SIZE 10
#define DIO_CTRL_RX_BUFFER_SIZE 10

typedef struct
{
	TimeStamp		last_write_time;		
	unsigned char	dio_ctrl_tx_buff[DIO_CTRL_RX_BUFFER_SIZE];
} DioCtrlTxShm;

typedef struct
{
	unsigned char	dio_ctrl_rx_buff[DIO_CTRL_TX_BUFFER_SIZE];
} DioCtrlRxShm;

bool init_rs232_com1(unsigned int baud_rate);
bool init_dio_ctrl_rx_buffer_semaphore(SEM **dio_ctrl_rx_buff_sem);
bool bind_to_dio_ctrl_rx_buffer_semaphore(SEM **dio_ctrl_rx_buff_sem);
bool init_dio_ctrl_tx_buffer_semaphore(SEM **dio_ctrl_tx_buff_sem);
bool bind_to_dio_ctrl_tx_buffer_semaphore(SEM **dio_ctrl_tx_buff_sem) ;
bool init_dio_ctrl_rx_buffer_shm(DioCtrlRxShm **dio_ctrl_rx_buff_shm, unsigned int buff_size_to_use);
bool bind_to_dio_ctrl_rx_buffer_shm(DioCtrlRxShm **dio_ctrl_rx_buff_shm);
bool init_dio_ctrl_tx_buffer_shm(DioCtrlTxShm **dio_ctrl_tx_buff_shm, unsigned int buff_size_to_use, TimeStamp current_time);
bool bind_to_dio_ctrl_tx_buffer_shm(DioCtrlTxShm **dio_ctrl_tx_buff_shm);
bool write_to_dio_ctrl_rx_buff_shm(unsigned char *msg, DioCtrlRxShm *dio_ctrl_rx_buff_shm, unsigned int buff_size, SEM *dio_ctrl_rx_buff_sem);
bool read_dio_ctrl_rx_buff_shm(DioCtrlRxShm *msg, DioCtrlRxShm *dio_ctrl_rx_buff_shm, unsigned int buff_size, SEM *dio_ctrl_rx_buff_sem);
bool write_to_dio_ctrl_tx_buff_shm(DioCtrlTxShm *msg, DioCtrlTxShm *dio_ctrl_tx_buff_shm, unsigned int buff_size, SEM *dio_ctrl_tx_buff_sem);
bool read_dio_ctrl_tx_buff_shm(DioCtrlTxShm *msg, DioCtrlTxShm *dio_ctrl_tx_buff_shm, unsigned int buff_size, SEM *dio_ctrl_tx_buff_sem);
bool read_from_rs232_com1(unsigned char *msg, unsigned int msg_size);
bool write_to_rs232_com1(unsigned char *msg, unsigned int msg_size);
void disable_rs232_com1(void);
void clear_rx_buffer(unsigned char *rx_buffer, unsigned int buff_size) ;




#endif
