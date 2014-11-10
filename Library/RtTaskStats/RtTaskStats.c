#include "RtTaskStats.h"

bool check_rt_task_specs_to_init(RtTasksData *rt_tasks_data, unsigned int cpu_id, unsigned int cpu_task_id, TimeStamp period)
{
	if (rt_tasks_data == NULL)
		return print_message(ERROR_MSG ,"RtTaskStats", "RtTaskStats", "check_rt_task_specs_to_init", "rt_tasks_data == NULL.");		
	if ((rt_tasks_data->cpus_rt_task_data[cpu_id].rt_task_period != 0) && (rt_tasks_data->cpus_rt_task_data[cpu_id].rt_task_period != period)) 
		return print_message(ERROR_MSG ,"RtTaskStats", "RtTaskStats", "check_rt_task_specs_to_init", "Inconvenient period submitted for rt_task.");
	if (rt_tasks_data->cpus_rt_task_data[cpu_id].task_rt_data[cpu_task_id].task_name[0] != 0)
		return print_message(ERROR_MSG ,"RtTaskStats", "RtTaskStats", "check_rt_task_specs_to_init", "There is a task at this cpu/task id == 0.");
	return TRUE;
}

bool write_rt_task_specs_to_rt_tasks_data(RtTasksData *rt_tasks_data, unsigned int cpu_id, unsigned int cpu_task_id, TimeStamp period, char *task_name)
{
	if (!check_rt_task_specs_to_init(rt_tasks_data, cpu_id, cpu_task_id, period))
		return print_message(ERROR_MSG ,"RtTaskStats", "RtTaskStats", "write_rt_task_specs_to_rt_tasks_data", "! check_rt_task_specs_to_init().");
	rt_tasks_data->cpus_rt_task_data[cpu_id].rt_task_period = period;			
	rt_tasks_data->num_of_total_rt_tasks++;
	rt_tasks_data->cpus_rt_task_data[cpu_id].num_of_rt_tasks_at_cpu++;
	strcpy(rt_tasks_data->cpus_rt_task_data[cpu_id].task_rt_data[cpu_task_id].task_name, task_name);
	return TRUE;
}

bool delete_rt_task_from_rt_tasks_data(RtTasksData *rt_tasks_data, unsigned int cpu_id, unsigned int cpu_task_id)
{
	rt_tasks_data->num_of_total_rt_tasks--;
	rt_tasks_data->cpus_rt_task_data[cpu_id].num_of_rt_tasks_at_cpu--;
	if (rt_tasks_data->cpus_rt_task_data[cpu_id].num_of_rt_tasks_at_cpu == 0)		// no task remained at cpu
		rt_tasks_data->cpus_rt_task_data[cpu_id].rt_task_period = 0;

	rt_tasks_data->cpus_rt_task_data[cpu_id].task_rt_data[cpu_task_id].task_name[0] = 0;		

	return TRUE;
}

void save_jitter(RtTasksData *rt_tasks_data, unsigned int cpu_id, unsigned int cpu_task_id, RTIME prev_time_count, RTIME curr_time_count, RTIME period)
{
	int jitter;

	CpuTasksRtData *cpu_tasks_rt_data = &(rt_tasks_data->cpus_rt_task_data[cpu_id].task_rt_data[cpu_task_id]) ; 
	jitter = curr_time_count - prev_time_count - period;
	if (jitter < 0)
		jitter = -jitter;

	cpu_tasks_rt_data->jitter_buff[cpu_tasks_rt_data->jitter_buff_cntr] = jitter;
	cpu_tasks_rt_data->jitter_buff_cntr ++;
	if (cpu_tasks_rt_data->jitter_buff_cntr == TASK_STAT_HIST_BUFFER_SIZE) 
		cpu_tasks_rt_data->jitter_buff_cntr = 0;
	return;
}

void save_run_time(RtTasksData *rt_tasks_data, unsigned int cpu_id, unsigned int cpu_task_id, RTIME task_start_time, RTIME task_end_time)
{
	unsigned int task_run_time;
	CpuTasksRtData *cpu_tasks_rt_data = &(rt_tasks_data->cpus_rt_task_data[cpu_id].task_rt_data[cpu_task_id]) ; 

	task_run_time = task_end_time - task_start_time;

	cpu_tasks_rt_data->run_time_buff[cpu_tasks_rt_data->run_time_buff_cntr] = task_run_time;
	cpu_tasks_rt_data->run_time_buff_cntr ++;
	if (cpu_tasks_rt_data->run_time_buff_cntr == TASK_STAT_HIST_BUFFER_SIZE) 
		cpu_tasks_rt_data->run_time_buff_cntr = 0;
	return;
}



