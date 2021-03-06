#include "RtTaskStatsViewer.h"

static RtTasksData 			*rt_tasks_data = NULL; 

int main( int argc, char *argv[])
{
	unsigned int i, j, k;
	unsigned int sink;
	unsigned int cpu_num, task_num;
	unsigned int stay_alive = 1;
	char arg_str[50];
	RTIME sum, max;
	unsigned int cntr;
	CpuTasksRtData *cpu_tasks_rt_data; 

	rt_tasks_data = (RtTasksData*)rtai_malloc(SHM_NUM_RT_TASKS_DATA, 0);
	if (rt_tasks_data == NULL) 
		return print_message(ERROR_MSG ,"RtTaskStatsViewer", "RtTaskStatsViewer", "main", "rt_tasks_data == NULL.");

	while (stay_alive)
	{
		printf("Enter command(list / clear_all / kill / task / clear_cpu / clear_cpus_023 / clear_cpu_thread/ clear_task_stats) :\n");		
		sink = scanf("%s", arg_str);
		if ((strcmp(arg_str, "list" ) == 0))
		{
			printf("-----------------------------------------  RT_TASK_STATS ----------------------------------------\n");
			printf("SYSTEM_TIME:		 	%llu\n", (long long unsigned int)rt_tasks_data->current_system_time);
			printf("MAX_NUM_OF_CPUS: 		%u\n", MAX_NUM_OF_CPUS);	
			printf("MAX_NUM_OF_CPU_THREADS_PER_CPU: 	%u\n", MAX_NUM_OF_CPU_THREADS_PER_CPU);	
			printf("MAX_NUM_OF_RT_TASKS_PER_CPU: 		%u\n", MAX_NUM_OF_RT_TASKS_PER_CPU);	
			printf("TOTAL_NUM_OF_RT_TASKS: 		%u\n", rt_tasks_data->num_of_total_rt_tasks);	

			for (i = 0; i < MAX_NUM_OF_CPUS; i ++)
			{
				printf("===============================================\n");
				printf("------------------------------------ CPU %u ------------------------------------\n", i);
				printf("CPU_RT_TASK_PERIOD:		%lu\n", (long unsigned int) rt_tasks_data->cpus_rt_task_data[i].rt_task_period);
				printf("NUM_OF_RT_TASKS_AT_CPU:	%u\n", rt_tasks_data->cpus_rt_task_data[i].num_of_rt_tasks_at_cpu);		
				for(k = 0; k < MAX_NUM_OF_RT_TASKS_PER_CPU; k++)
				{
					printf("---------------------  CPU %u  THREAD %u TASK %u -----------------\n", i, j, k);
		       		 	printf("TASK_NAME: 			%s\n", rt_tasks_data->cpus_rt_task_data[i].task_rt_data[k].task_name);		
				}		
			}
			printf("---------------------------------------------------------------------------------------------------------------\n");
		}
		else if (strcmp(arg_str, "clear_all" ) == 0)
		{
			for (i = 0; i < MAX_NUM_OF_CPUS; i ++)
			{
				for(k = 0; k < MAX_NUM_OF_RT_TASKS_PER_CPU; k++)
				{
					cpu_tasks_rt_data = &(rt_tasks_data->cpus_rt_task_data[i].task_rt_data[k]) ; 
					for (cntr = 0; cntr < TASK_STAT_HIST_BUFFER_SIZE; cntr++)
					{
						cpu_tasks_rt_data->run_time_buff[cntr] = 0;
						cpu_tasks_rt_data->jitter_buff[cntr] = 0;
					}
				}			
			}			
		}
		else if (strcmp(arg_str, "task" ) == 0)
		{
			printf("Enter task name:\n");
			sink = scanf("%s", arg_str);
			for (i = 0; i < MAX_NUM_OF_CPUS; i ++)
			{
				for(k = 0; k < MAX_NUM_OF_RT_TASKS_PER_CPU; k++)
				{
					if ((strcmp(arg_str, rt_tasks_data->cpus_rt_task_data[i].task_rt_data[k].task_name) != 0))
						continue;
					printf("---------------------  CPU %u  THREAD %u TASK %u -----------------\n", i, j, k);
					printf("TASK_NAME: 			%s\n", rt_tasks_data->cpus_rt_task_data[i].task_rt_data[k].task_name);		
					cpu_tasks_rt_data = &(rt_tasks_data->cpus_rt_task_data[i].task_rt_data[k]) ; 
					sum = 0;
					for (cntr = 0; cntr < TASK_STAT_HIST_BUFFER_SIZE; cntr++)
						sum += cpu_tasks_rt_data->run_time_buff[cntr];
					printf("TASK_RUN_TIME - MEAN:		%lld\n", count2nano(sum/TASK_STAT_HIST_BUFFER_SIZE));
					max = 0;
					for (cntr = 0; cntr < TASK_STAT_HIST_BUFFER_SIZE; cntr++)
					{
						if (cpu_tasks_rt_data->run_time_buff[cntr] > max)
							max = cpu_tasks_rt_data->run_time_buff[cntr];
					}
				       	printf("TASK_RUN_TIME - MAX: 		%lld\n", count2nano(max));	
					sum = 0;
					for (cntr = 0; cntr < TASK_STAT_HIST_BUFFER_SIZE; cntr++)
						sum += cpu_tasks_rt_data->jitter_buff[cntr];
					printf("JITTER - MEAN:			%lld\n", count2nano(sum/TASK_STAT_HIST_BUFFER_SIZE));
					max = 0;
					for (cntr = 0; cntr < TASK_STAT_HIST_BUFFER_SIZE; cntr++)
					{
						if (cpu_tasks_rt_data->jitter_buff[cntr] > max)
							max = cpu_tasks_rt_data->jitter_buff[cntr];
					}
				       	printf("JITTER - MAX: 			%lld\n", count2nano(max));		
				}
			}
		}		
/*		else if  (strcmp(arg_str, "clear_cpu" ) == 0)
		{
			printf("Enter CPU number:\n");
			sink = scanf("%s", arg_str);
			cpu_num = atoi(arg_str);
			if ((cpu_num < MAX_NUM_OF_CPUS) && (cpu_num >= 0))
			{
				for (j = 0; j < MAX_NUM_OF_CPU_THREADS_PER_CPU; j++)
				{	
					for(k = 0; k < MAX_NUM_OF_RT_TASKS_PER_CPU_THREAD; k++)
					{
						rt_tasks_data->cpus_rt_task_data[cpu_num].cpu_threads_rt_data[j].cpu_thread_tasks_rt_data[k].task_name[0] = 0;	
			       		 	rt_tasks_data->cpus_rt_task_data[cpu_num].cpu_threads_rt_data[j].cpu_thread_tasks_rt_data[k].max_task_run_time = 0;		
			       		 	rt_tasks_data->cpus_rt_task_data[cpu_num].cpu_threads_rt_data[j].cpu_thread_tasks_rt_data[k].max_positive_jitter = 0;		
				 		rt_tasks_data->cpus_rt_task_data[cpu_num].cpu_threads_rt_data[j].cpu_thread_tasks_rt_data[k].max_negative_jitter = 0;	
			       		 	rt_tasks_data->cpus_rt_task_data[cpu_num].cpu_threads_rt_data[j].cpu_thread_tasks_rt_data[k].positive_jitter_threshold = 0;		
				 		rt_tasks_data->cpus_rt_task_data[cpu_num].cpu_threads_rt_data[j].cpu_thread_tasks_rt_data[k].negative_jitter_threshold = 0;	
			       		 	rt_tasks_data->cpus_rt_task_data[cpu_num].cpu_threads_rt_data[j].cpu_thread_tasks_rt_data[k].num_of_positive_jitter_exceeding_threshold = 0;		
				 		rt_tasks_data->cpus_rt_task_data[cpu_num].cpu_threads_rt_data[j].cpu_thread_tasks_rt_data[k].num_of_negative_jitter_exceeding_threshold = 0;
					}			
				}				
			}
			else
			{
				print_message(ERROR_MSG ,"RtTaskStatsViewer", "RtTaskStatsViewer", "main", "Inconvenient cpu num.\n");			
			}	
		}
		else if  (strcmp(arg_str, "clear_cpus_023" ) == 0)
		{
			for (j = 0; j < MAX_NUM_OF_CPU_THREADS_PER_CPU; j++)
			{	
				for(k = 0; k < MAX_NUM_OF_RT_TASKS_PER_CPU_THREAD; k++)
				{
					rt_tasks_data->cpus_rt_task_data[0].cpu_threads_rt_data[j].cpu_thread_tasks_rt_data[k].task_name[0] = 0;	
		       		 	rt_tasks_data->cpus_rt_task_data[0].cpu_threads_rt_data[j].cpu_thread_tasks_rt_data[k].max_task_run_time = 0;		
		       		 	rt_tasks_data->cpus_rt_task_data[0].cpu_threads_rt_data[j].cpu_thread_tasks_rt_data[k].max_positive_jitter = 0;		
			 		rt_tasks_data->cpus_rt_task_data[0].cpu_threads_rt_data[j].cpu_thread_tasks_rt_data[k].max_negative_jitter = 0;	
		       		 	rt_tasks_data->cpus_rt_task_data[0].cpu_threads_rt_data[j].cpu_thread_tasks_rt_data[k].positive_jitter_threshold = 0;		
			 		rt_tasks_data->cpus_rt_task_data[0].cpu_threads_rt_data[j].cpu_thread_tasks_rt_data[k].negative_jitter_threshold = 0;	
		       		 	rt_tasks_data->cpus_rt_task_data[0].cpu_threads_rt_data[j].cpu_thread_tasks_rt_data[k].num_of_positive_jitter_exceeding_threshold = 0;		
			 		rt_tasks_data->cpus_rt_task_data[0].cpu_threads_rt_data[j].cpu_thread_tasks_rt_data[k].num_of_negative_jitter_exceeding_threshold = 0;
					rt_tasks_data->cpus_rt_task_data[2].cpu_threads_rt_data[j].cpu_thread_tasks_rt_data[k].task_name[0] = 0;	
		       		 	rt_tasks_data->cpus_rt_task_data[2].cpu_threads_rt_data[j].cpu_thread_tasks_rt_data[k].max_task_run_time = 0;		
		       		 	rt_tasks_data->cpus_rt_task_data[2].cpu_threads_rt_data[j].cpu_thread_tasks_rt_data[k].max_positive_jitter = 0;		
			 		rt_tasks_data->cpus_rt_task_data[2].cpu_threads_rt_data[j].cpu_thread_tasks_rt_data[k].max_negative_jitter = 0;	
		       		 	rt_tasks_data->cpus_rt_task_data[2].cpu_threads_rt_data[j].cpu_thread_tasks_rt_data[k].positive_jitter_threshold = 0;		
			 		rt_tasks_data->cpus_rt_task_data[2].cpu_threads_rt_data[j].cpu_thread_tasks_rt_data[k].negative_jitter_threshold = 0;	
		       		 	rt_tasks_data->cpus_rt_task_data[2].cpu_threads_rt_data[j].cpu_thread_tasks_rt_data[k].num_of_positive_jitter_exceeding_threshold = 0;		
			 		rt_tasks_data->cpus_rt_task_data[2].cpu_threads_rt_data[j].cpu_thread_tasks_rt_data[k].num_of_negative_jitter_exceeding_threshold = 0;
					rt_tasks_data->cpus_rt_task_data[3].cpu_threads_rt_data[j].cpu_thread_tasks_rt_data[k].task_name[0] = 0;	
		       		 	rt_tasks_data->cpus_rt_task_data[3].cpu_threads_rt_data[j].cpu_thread_tasks_rt_data[k].max_task_run_time = 0;		
		       		 	rt_tasks_data->cpus_rt_task_data[3].cpu_threads_rt_data[j].cpu_thread_tasks_rt_data[k].max_positive_jitter = 0;		
			 		rt_tasks_data->cpus_rt_task_data[3].cpu_threads_rt_data[j].cpu_thread_tasks_rt_data[k].max_negative_jitter = 0;	
		       		 	rt_tasks_data->cpus_rt_task_data[3].cpu_threads_rt_data[j].cpu_thread_tasks_rt_data[k].positive_jitter_threshold = 0;		
			 		rt_tasks_data->cpus_rt_task_data[3].cpu_threads_rt_data[j].cpu_thread_tasks_rt_data[k].negative_jitter_threshold = 0;	
		       		 	rt_tasks_data->cpus_rt_task_data[3].cpu_threads_rt_data[j].cpu_thread_tasks_rt_data[k].num_of_positive_jitter_exceeding_threshold = 0;		
			 		rt_tasks_data->cpus_rt_task_data[3].cpu_threads_rt_data[j].cpu_thread_tasks_rt_data[k].num_of_negative_jitter_exceeding_threshold = 0;
				}			
			}				
		}
		else if  (strcmp(arg_str, "clear_cpu_thread" ) == 0)
		{			
			printf("Enter CPU number:\n");
			sink = scanf("%s", arg_str);
			cpu_num = atoi(arg_str);
			printf("Enter CPU thread:\n");
			sink = scanf("%s", arg_str);
			cpu_thread = atoi(arg_str);
			if ((cpu_num < MAX_NUM_OF_CPUS) && (cpu_num >= 0))
			{
				if ((cpu_thread < MAX_NUM_OF_CPU_THREADS_PER_CPU) && (cpu_thread >= 0) )
				{	
					for(k = 0; k < MAX_NUM_OF_RT_TASKS_PER_CPU_THREAD; k++)
					{
			       		 	rt_tasks_data->cpus_rt_task_data[cpu_num].cpu_threads_rt_data[cpu_thread].cpu_thread_tasks_rt_data[k].task_name[0] = 0;
			       		 	rt_tasks_data->cpus_rt_task_data[cpu_num].cpu_threads_rt_data[cpu_thread].cpu_thread_tasks_rt_data[k].max_task_run_time = 0;		
			       		 	rt_tasks_data->cpus_rt_task_data[cpu_num].cpu_threads_rt_data[cpu_thread].cpu_thread_tasks_rt_data[k].max_positive_jitter = 0;		
				 		rt_tasks_data->cpus_rt_task_data[cpu_num].cpu_threads_rt_data[cpu_thread].cpu_thread_tasks_rt_data[k].max_negative_jitter = 0;	
			       		 	rt_tasks_data->cpus_rt_task_data[cpu_num].cpu_threads_rt_data[cpu_thread].cpu_thread_tasks_rt_data[k].positive_jitter_threshold = 0;		
				 		rt_tasks_data->cpus_rt_task_data[cpu_num].cpu_threads_rt_data[cpu_thread].cpu_thread_tasks_rt_data[k].negative_jitter_threshold = 0;	
			       		 	rt_tasks_data->cpus_rt_task_data[cpu_num].cpu_threads_rt_data[cpu_thread].cpu_thread_tasks_rt_data[k].num_of_positive_jitter_exceeding_threshold = 0;		
				 		rt_tasks_data->cpus_rt_task_data[cpu_num].cpu_threads_rt_data[cpu_thread].cpu_thread_tasks_rt_data[k].num_of_negative_jitter_exceeding_threshold = 0;
					}			
				}
				else
				{
					print_message(ERROR_MSG ,"RtTaskStatsViewer", "RtTaskStatsViewer", "main", "Inconvenient cpu thread num.\n");					
				}				
			}
			else
			{
				print_message(ERROR_MSG ,"RtTaskStatsViewer", "RtTaskStatsViewer", "main", "Inconvenient cpu num.\n");					
			}			
		}
*/		else if  (strcmp(arg_str, "clear_task_stats" ) == 0)
		{
			printf("Enter CPU number:\n");
			sink = scanf("%s", arg_str);
			cpu_num = atoi(arg_str);
			printf("Enter task number:\n");
			sink = scanf("%s", arg_str);
			task_num = atoi(arg_str);
			if ((cpu_num >= MAX_NUM_OF_CPUS) || (cpu_num < 0))
			{
				print_message(ERROR_MSG ,"RtTaskStatsViewer", "RtTaskStatsViewer", "main", "Invalid CPU num.\n");
			}
			else if ((task_num >= MAX_NUM_OF_RT_TASKS_PER_CPU) || (task_num < 0))
			{
				print_message(ERROR_MSG ,"RtTaskStatsViewer", "RtTaskStatsViewer", "main", "Invalid task num.\n");
			}
			else
			{
				cpu_tasks_rt_data = &(rt_tasks_data->cpus_rt_task_data[cpu_num].task_rt_data[task_num]) ; 
				for (cntr = 0; cntr < TASK_STAT_HIST_BUFFER_SIZE; cntr++)
				{
					cpu_tasks_rt_data->run_time_buff[cntr] = 0;
					cpu_tasks_rt_data->jitter_buff[cntr] = 0;
				}
			}
		}
		else
		{
			print_message(ERROR_MSG ,"RtTaskStatsViewer", "RtTaskStatsViewer", "main", "Unknown argument.\n");
			printf ("The command given is %s\n", arg_str);			
		}

	}
	rtai_free(SHM_NUM_RT_TASKS_DATA, rt_tasks_data);	
	return 0;
}
