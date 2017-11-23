#include "RS232Handler.h"

#define NUMBITS		8
#define STOPBITS		1

bool init_rs232_com1(unsigned int baud_rate)   // rs 232 is enabled by mov obj handler
{
	int sp_open_return;
	rt_spclose(COM1);  // it might be left open since the previous program.
	sp_open_return = rt_spopen(COM1, baud_rate, NUMBITS, STOPBITS, RT_SP_PARITY_NONE, RT_SP_NO_HAND_SHAKE, RT_SP_FIFO_DISABLE);
	if (sp_open_return)
	{
      		switch(sp_open_return)
		{
	 		case -ENODEV:
		 		return print_message(ERROR_MSG ,"DioControls", "RS232Handler", "enable_rs232_com1", "No Device.");
	 		case -EINVAL:
	  	 		return print_message(ERROR_MSG ,"DioControls", "RS232Handler", "enable_rs232_com1", "Invalid Value.");       		
	 		case -EADDRINUSE:
	  	 		return print_message(ERROR_MSG ,"DioControls", "RS232Handler", "enable_rs232_com1", "Address in Use.");     
	 		default:
	  	 		return print_message(ERROR_MSG ,"DioControls", "RS232Handler", "enable_rs232_com1", "Unknown Error.");       		
		}
	}
	rt_spclear_rx(COM1);
	rt_spclear_tx(COM1);
	print_message(INFO_MSG ,"DioControls", "RS232Handler", "enable_rs232_com1", "RS-232 COM1 - Enabled.");  
	return TRUE;
}

bool init_dio_ctrl_rx_buffer_semaphore(SEM **dio_ctrl_rx_buff_sem)
{
	if (*dio_ctrl_rx_buff_sem != NULL)
        	return print_message(ERROR_MSG ,"DioControls", "RS232Handler", "init_dio_ctrl_rx_buffer_semaphore", "dio_ctrl_rx_buff_sem != NULL.");
	*dio_ctrl_rx_buff_sem = rt_get_adr(SEM_NUM_DIO_CTRL_RX_BUFFER);
	if (*dio_ctrl_rx_buff_sem == NULL)  // semaphore had not been created before.
	{
		*dio_ctrl_rx_buff_sem = rt_typed_sem_init(SEM_NUM_DIO_CTRL_RX_BUFFER, 1, BIN_SEM | FIFO_Q );
		print_message(INFO_MSG ,"DioControls", "RS232Handler", "init_dio_ctrl_rx_buffer_semaphore", "Initialized dio_ctrl_rx_buff semaphore.");  
	}
	else // a semaphore created before, delete and init it again.
	{
		rt_sem_delete(*dio_ctrl_rx_buff_sem);
		*dio_ctrl_rx_buff_sem = rt_typed_sem_init(SEM_NUM_DIO_CTRL_RX_BUFFER, 1, BIN_SEM | FIFO_Q );
		print_message(INFO_MSG ,"DioControls", "RS232Handler", "init_dio_ctrl_rx_buffer_semaphore", "Re-initialized dio_ctrl_rx_buff semaphore.");  
	}
	return TRUE;
}

bool bind_to_dio_ctrl_rx_buffer_semaphore(SEM **dio_ctrl_rx_buff_sem) // init_dio_ctrl_rx_buffer_semaphore is used by mov obj handler process Other processes(programs) using COM1 via semaphore are binded to the (static value)semaphore created by mov obj handler. 
{
	*dio_ctrl_rx_buff_sem = rt_get_adr(SEM_NUM_DIO_CTRL_RX_BUFFER);
	if (*dio_ctrl_rx_buff_sem  == NULL)
         	return print_message(ERROR_MSG ,"DioControls", "RS232Handler", "bind_to_dio_ctrl_rx_buffer_semaphore", "No dio_ctrl_rx_buff semaphore created. Create it with mov obj handler.");
	print_message(INFO_MSG ,"DioControls", "RS232Handler", "bind_to_dio_ctrl_rx_buffer_semaphore", "Binded to dio_ctrl_rx_buffer_semaphore.");  
	return TRUE;
}

bool init_dio_ctrl_tx_buffer_semaphore(SEM **dio_ctrl_tx_buff_sem)
{
	if (*dio_ctrl_tx_buff_sem != NULL)
        	return print_message(ERROR_MSG ,"DioControls", "RS232Handler", "init_dio_ctrl_tx_buffer_semaphore", "dio_ctrl_tx_buff_sem != NULL.");
	*dio_ctrl_tx_buff_sem = rt_get_adr(SEM_NUM_DIO_CTRL_TX_BUFFER);
	if (*dio_ctrl_tx_buff_sem == NULL)  // semaphore had not been created before.
	{
		*dio_ctrl_tx_buff_sem = rt_typed_sem_init(SEM_NUM_DIO_CTRL_TX_BUFFER, 1, BIN_SEM | FIFO_Q );
		print_message(INFO_MSG ,"DioControls", "RS232Handler", "init_dio_ctrl_tx_buffer_semaphore", "Initialized dio_ctrl_tx_buff semaphore.");  
	}
	else // a semaphore created before, delete and init it again.
	{
		rt_sem_delete(*dio_ctrl_tx_buff_sem);
		*dio_ctrl_tx_buff_sem = rt_typed_sem_init(SEM_NUM_DIO_CTRL_TX_BUFFER, 1, BIN_SEM | FIFO_Q );
		print_message(INFO_MSG ,"DioControls", "RS232Handler", "init_dio_ctrl_tx_buffer_semaphore", "Re-initialized dio_ctrl_tx_buff semaphore.");  
	}
	return TRUE;
}

bool bind_to_dio_ctrl_tx_buffer_semaphore(SEM **dio_ctrl_tx_buff_sem) // init_dio_ctrl_tx_buffer_semaphore is used by mov obj handler process Other processes(programs) using COM1 via semaphore are binded to the (static value)semaphore created by mov obj handler. 
{
	*dio_ctrl_tx_buff_sem = rt_get_adr(SEM_NUM_DIO_CTRL_TX_BUFFER);
	if (*dio_ctrl_tx_buff_sem  == NULL)
         	return print_message(ERROR_MSG ,"DioControls", "RS232Handler", "bind_to_dio_ctrl_tx_buffer_semaphore", "No dio_ctrl_tx_buff semaphore created. Create it with mov obj handler.");
	print_message(INFO_MSG ,"DioControls", "RS232Handler", "bind_to_dio_ctrl_tx_buffer_semaphore", "Binded to dio_ctrl_tx_buffer_semaphore.");  
	return TRUE;
}

bool init_dio_ctrl_rx_buffer_shm(DioCtrlRxShm **dio_ctrl_rx_buff_shm, unsigned int buff_size_to_use) // This proc is used by mov obj handler program to enable RS232 and clear shared memory buffer. 
{
	if (buff_size_to_use > DIO_CTRL_RX_BUFFER_SIZE) 
         	return print_message(ERROR_MSG ,"DioControls", "RS232Handler", "init_dio_ctrl_rx_buffer_shm", "buff_size_to_use > DIO_CTRL_RX_BUFFER_SIZE.");
	if (*dio_ctrl_rx_buff_shm != NULL)
         	return print_message(ERROR_MSG ,"DioControls", "RS232Handler", "init_dio_ctrl_rx_buffer_shm", "dio_ctrl_rx_buff was allocated before.");
	*dio_ctrl_rx_buff_shm = rt_get_adr(SHM_NUM_DIO_CTRL_RX_BUFFER);
	if (*dio_ctrl_rx_buff_shm == NULL)
	{
		*dio_ctrl_rx_buff_shm = rtai_malloc(SHM_NUM_DIO_CTRL_RX_BUFFER, sizeof(DioCtrlRxShm));
		memset(*dio_ctrl_rx_buff_shm, 0, sizeof(DioCtrlRxShm));
		print_message(INFO_MSG ,"DioControls", "RS232Handler", "init_dio_ctrl_rx_buffer_shm", "Initialized dio_ctrl_rx_buff shm object.");  
	}
	else
	{
		rtai_free(SHM_NUM_DIO_CTRL_RX_BUFFER, *dio_ctrl_rx_buff_shm);
		*dio_ctrl_rx_buff_shm = rtai_malloc(SHM_NUM_DIO_CTRL_RX_BUFFER, sizeof(DioCtrlRxShm));
		memset(*dio_ctrl_rx_buff_shm, 0, sizeof(DioCtrlRxShm));
		print_message(INFO_MSG ,"DioControls", "RS232Handler", "init_dio_ctrl_rx_buffer_shm", "Re-initialized dio_ctrl_rx_buff shm object..");  		
	}
	return TRUE;
} 

bool bind_to_dio_ctrl_rx_buffer_shm(DioCtrlRxShm **dio_ctrl_rx_buff_shm) // init_dio_ctrl_prosthetic_ctrl_rs232_com1_shm is used by mov obj handler program. Other processes(i.e exp envi handler) using COM1 via semaphore are binded to the (static value) shm buffer created by mov obj handler. 
{
	if (*dio_ctrl_rx_buff_shm != NULL)
         	return print_message(ERROR_MSG ,"DioControls", "RS232Handler", "bind_to_dio_ctrl_rx_buffer_shm", "This program binded to shared memory previously.");
	*dio_ctrl_rx_buff_shm = rt_get_adr(SHM_NUM_DIO_CTRL_RX_BUFFER);
	if (*dio_ctrl_rx_buff_shm == NULL)
         	return print_message(ERROR_MSG ,"DioControls", "RS232Handler", "bind_to_dio_ctrl_rx_buffer_shm", "No dio_ctrl_rx_buff shared memory created. Initialize it with Mov Obj Handler.");
	*dio_ctrl_rx_buff_shm = rtai_malloc(SHM_NUM_DIO_CTRL_RX_BUFFER, 0);
	if (*dio_ctrl_rx_buff_shm == NULL)
         	return print_message(ERROR_MSG ,"DioControls", "RS232Handler", "bind_to_dio_ctrl_rx_buffer_shm", "Couldn't bind to dio_ctrl_rx_buffer_shm shared memory.");
	print_message(INFO_MSG ,"DioControls", "RS232Handler", "bind_to_dio_ctrl_rx_buffer_shm", "Binded to dio_ctrl_rx_buffer_shm shared memory.");  
	return TRUE;
}

bool init_dio_ctrl_tx_buffer_shm(DioCtrlTxShm **dio_ctrl_tx_buff_shm, unsigned int buff_size_to_use, TimeStamp current_time) // This proc is used by mov obj handler program to enable RS232 and clear shared memory buffer. 
{
	if (buff_size_to_use > DIO_CTRL_TX_BUFFER_SIZE) 
         	return print_message(ERROR_MSG ,"DioControls", "RS232Handler", "init_dio_ctrl_rx_buffer_shm", "buff_size_to_use > DIO_CTRL_RX_BUFFER_SIZE.");
	if (*dio_ctrl_tx_buff_shm != NULL)
         	return print_message(ERROR_MSG ,"DioControls", "RS232Handler", "init_dio_ctrl_tx_buffer_shm", "dio_ctrl_tx_buff was allocated before.");
	*dio_ctrl_tx_buff_shm = rt_get_adr(SHM_NUM_DIO_CTRL_TX_BUFFER);
	if (*dio_ctrl_tx_buff_shm == NULL)
	{
		*dio_ctrl_tx_buff_shm = rtai_malloc(SHM_NUM_DIO_CTRL_TX_BUFFER, sizeof(DioCtrlTxShm));
		memset(*dio_ctrl_tx_buff_shm, 0, sizeof(DioCtrlTxShm));
		(*dio_ctrl_tx_buff_shm)->last_write_time = current_time;
		print_message(INFO_MSG ,"DioControls", "RS232Handler", "init_dio_ctrl_tx_buffer_shm", "Initialized dio_ctrl_tx_buff shm object.");  
	}
	else
	{
		rtai_free(SHM_NUM_DIO_CTRL_TX_BUFFER, dio_ctrl_tx_buff_shm);
		*dio_ctrl_tx_buff_shm = rtai_malloc(SHM_NUM_DIO_CTRL_TX_BUFFER, sizeof(DioCtrlTxShm));
		memset(*dio_ctrl_tx_buff_shm, 0, sizeof(DioCtrlTxShm));
		(*dio_ctrl_tx_buff_shm)->last_write_time = current_time;
		print_message(INFO_MSG ,"DioControls", "RS232Handler", "init_dio_ctrl_tx_buffer_shm", "Re-initialized dio_ctrl_tx_buff shm object..");  		
	}
	return TRUE;
} 

bool bind_to_dio_ctrl_tx_buffer_shm(DioCtrlTxShm **dio_ctrl_tx_buff_shm) // init_dio_ctrl_prosthetic_ctrl_rs232_com1_shm is used by mov obj handler program. Other processes(i.e exp envi handler) using COM1 via semaphore are binded to the (static value) shm buffer created by mov obj handler. 
{
	if (*dio_ctrl_tx_buff_shm != NULL)
         	return print_message(ERROR_MSG ,"DioControls", "RS232Handler", "bind_to_dio_ctrl_tx_buffer_shm", "This program binded to shared memory previously.");
	*dio_ctrl_tx_buff_shm = rt_get_adr(SHM_NUM_DIO_CTRL_TX_BUFFER);
	if (*dio_ctrl_tx_buff_shm == NULL)
         	return print_message(ERROR_MSG ,"DioControls", "RS232Handler", "bind_to_dio_ctrl_tx_buffer_shm", "No dio_ctrl_tx_buff shared memory created. Initialize it with Mov Obj Handler.");
	*dio_ctrl_tx_buff_shm = rtai_malloc(SHM_NUM_DIO_CTRL_TX_BUFFER, 0);
	if (*dio_ctrl_tx_buff_shm == NULL)
         	return print_message(ERROR_MSG ,"DioControls", "RS232Handler", "bind_to_dio_ctrl_tx_buffer_shm", "Couldn't bind to dio_ctrl_tx_buffer_shm shared memory.");
	print_message(INFO_MSG ,"DioControls", "RS232Handler", "bind_to_dio_ctrl_tx_buffer_shm", "Binded to dio_ctrl_tx_buffer_shm shared memory.");  
	return TRUE;
}


bool write_to_dio_ctrl_rx_buff_shm(unsigned char *msg, DioCtrlRxShm *dio_ctrl_rx_buff_shm, unsigned int buff_size, SEM *dio_ctrl_rx_buff_sem) // mov obj handler writes here after handling rs232 rx buffer.
{
	unsigned int i;
        rt_sem_wait(dio_ctrl_rx_buff_sem);
	for (i = 0; i < buff_size; i++)
	{
		dio_ctrl_rx_buff_shm->dio_ctrl_rx_buff[i] = msg[i];
	}
        rt_sem_signal(dio_ctrl_rx_buff_sem);
	return TRUE;
}

bool read_dio_ctrl_rx_buff_shm(DioCtrlRxShm *msg, DioCtrlRxShm *dio_ctrl_rx_buff_shm, unsigned int buff_size, SEM *dio_ctrl_rx_buff_sem) // exp envi handler reads here.
{
	unsigned int i;
        rt_sem_wait(dio_ctrl_rx_buff_sem);
	for (i = 0; i < buff_size; i++)
	{
		msg->dio_ctrl_rx_buff[i] = dio_ctrl_rx_buff_shm->dio_ctrl_rx_buff[i];
	}
        rt_sem_signal(dio_ctrl_rx_buff_sem);
	return TRUE;
}

bool write_to_dio_ctrl_tx_buff_shm(DioCtrlTxShm *msg, DioCtrlTxShm *dio_ctrl_tx_buff_shm, unsigned int buff_size, SEM *dio_ctrl_tx_buff_sem) // dio_ctrl handler writes here to send command via mov obj handler.
{
	unsigned int i;
        rt_sem_wait(dio_ctrl_tx_buff_sem);

	dio_ctrl_tx_buff_shm->last_write_time = msg->last_write_time;
	for (i = 0; i < buff_size; i++)
	{
		dio_ctrl_tx_buff_shm->dio_ctrl_tx_buff[i] = msg->dio_ctrl_tx_buff[i];
	}
        rt_sem_signal(dio_ctrl_tx_buff_sem);
	return TRUE;
}

bool read_dio_ctrl_tx_buff_shm(DioCtrlTxShm *msg, DioCtrlTxShm *dio_ctrl_tx_buff_shm, unsigned int buff_size, SEM *dio_ctrl_tx_buff_sem) // mov obj handler reads here to tx via rs232.
{
	unsigned int i;
        rt_sem_wait(dio_ctrl_tx_buff_sem);
	msg->last_write_time = dio_ctrl_tx_buff_shm->last_write_time;
	for (i = 0; i < buff_size; i++)
	{
		msg->dio_ctrl_tx_buff[i] = dio_ctrl_tx_buff_shm->dio_ctrl_tx_buff[i];
	}
        rt_sem_signal(dio_ctrl_tx_buff_sem);
	return TRUE;
}

bool read_from_rs232_com1(unsigned char *msg, unsigned int msg_size)  // mov obj handler uses to read all rx buffer of rs232
{
	int rx_num_of_chars_remaining;
	rx_num_of_chars_remaining = rt_spread(COM1, (char*) msg, (int)msg_size);
	if (rx_num_of_chars_remaining != 0)
		return print_message(ERROR_MSG ,"DioControls", "RS232Handler", "read_from_rs232_com1", "rx_num_of_chars_remaining != 0.");
	return TRUE;	
}


bool write_to_rs232_com1(unsigned char *msg, unsigned int msg_size)
{
	if (rt_spwrite(COM1, (char*) msg, (int)msg_size))
		return print_message(ERROR_MSG ,"DioControls", "RS232Handler", "write_to_rs232_com1", "rt_spwrite().");
	return TRUE;
}

void disable_rs232_com1(void)
{
	rt_spclose(COM1); 
	print_message(INFO_MSG ,"DioControls", "RS232Handler", "disable_rs232_com1", "RS-232 COM1 - Disabled.");       		
}

void clear_rx_buffer(unsigned char *rx_buffer, unsigned int buff_size) 
{
	unsigned int i;
	for (i = 0; i < buff_size; i++)
		rx_buffer[i] = 0;
}
