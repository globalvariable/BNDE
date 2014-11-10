#ifndef RT_TASKS_DATA_H
#define RT_TASKS_DATA_H

#include "../Cpu/CpuInfo.h"
#include "../KernelTaskCtrl/KernelTaskCtrl.h"
#include "../TimeStamp/TimeStamp.h"
#include <rtai_shm.h>

#define MAX_NUM_OF_RT_TASKS_PER_CPU			10
#define MAX_NUM_OF_RT_TASKS_NAME_LENGTH		40

#define TASK_STAT_HIST_BUFFER_SIZE		100000

typedef struct __CpuThreadTasksRtData
{
	char		task_name[MAX_NUM_OF_RT_TASKS_NAME_LENGTH];
	unsigned int	jitter_buff[TASK_STAT_HIST_BUFFER_SIZE];	// determine a threshold and writes threshold-exceeding jitters here.  
	unsigned int	run_time_buff[TASK_STAT_HIST_BUFFER_SIZE];	// determine a threshold and writes threshold-exceeding jitters here.  
	unsigned int	jitter_buff_cntr;
	unsigned int	run_time_buff_cntr;
} CpuTasksRtData;

typedef struct __CpusRtData
{
	unsigned int			num_of_rt_tasks_at_cpu;
	CpuTasksRtData		task_rt_data[MAX_NUM_OF_RT_TASKS_PER_CPU];		
	TimeStamp			rt_task_period;
} CpusRtData;

typedef struct __RtTasksData
{
	RTIME			current_system_time;	// periodic task of HybridNetwork determines it. 	
	unsigned int		num_of_total_rt_tasks;	
	CpusRtData 		cpus_rt_task_data[MAX_NUM_OF_CPUS];
} RtTasksData;


#endif
