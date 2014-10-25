#ifndef SHM_NUM_H
#define SHM_NUM_H

#include "../RtTasksData/RtTasksData.h"

// NOTE:    SEMAPHORE AND SHARED MEMORY CANNOT USE THE SAME OBJECT NUMBER 

///////////////  SEMAPHORE /////////////////////////////////
#define SEM_NUM_DIO_CTRL_RX_BUFFER			101
#define SEM_NUM_DIO_CTRL_TX_BUFFER			102







///////////////  SHARED MEMORY /////////////////////////////////

#define SHM_NUM_RT_TASKS_DATA							200

#define SHM_NUM_BLUESPIKE_RECORDING_DATA				201
#define SHM_NUM_BLUESPIKE_SORTED_SPIKES				202


#define SHM_NUM_DIO_CTRL_RX_BUFFER			251   // should be shorter than or equal to 6 for correct shm numbering
#define SHM_NUM_DIO_CTRL_TX_BUFFER			252

#define SHM_NUM_DAQ_CONFIG_2_KERNEL_SPIKE			401
#define SHM_NUM_FILTER_CTRL_2_KERNEL_SPIKE			402
#define SHM_NUM_SPIKE_THRES_2_KERNEL_SPIKE			403	
#define SHM_NUM_TEMPLATE_MATCHING_2_KERNEL_SPIKE	404

#define SHM_NUM_EXP_CTRL_2_DIO_CTRL			501			
#define SHM_NUM_EXP_CTRL_2_PROSTHETIC_CTRL			502
#define SHM_NUM_EXP_CTRL_2_NEURAL_NET			503
#define SHM_NUM_EXP_CTRL_2_SPIKE_GEN				504
#define SHM_NUM_EXP_CTRL_2_NEU_REC_HAND			505

#define SHM_NUM_DIO_CTRL_2_EXP_CTRL			520


#define SHM_NUM_PROSTHETIC_CTRL_2_NEURAL_NET			540		// take care of multi threaded messaging btw mov obj hand and neural net
#define SHM_NUM_PROSTHETIC_CTRL_2_EXP_CTRL			550			


#define SHM_NUM_NEURAL_NET_2_PROSTHETIC_CTRL			560		// take care of multi threaded messaging btw mov obj hand and neural net
#define SHM_NUM_NEURAL_NET_2_EXP_CTRL			570

#define SHM_NUM_SPIKE_GEN_2_EXP_CTRL				581

#define SHM_NUM_NEU_REC_HAND_2_EXP_CTRL			591

#endif
