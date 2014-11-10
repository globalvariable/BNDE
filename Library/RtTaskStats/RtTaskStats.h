#ifndef RT_TASK_STATS_H
#define RT_TASK_STATS_H

#include <gtk/gtk.h>
#include <stdbool.h>
#include <rtai_sched.h>
#include <rtai_shm.h>
#include "../System/RtTasksData/RtTasksData.h"
#include "../Misc/Misc.h"

bool check_rt_task_specs_to_init(RtTasksData *rt_tasks_data, unsigned int cpu_id, unsigned int cpu_task_id, TimeStamp period);
bool write_rt_task_specs_to_rt_tasks_data(RtTasksData *rt_tasks_data, unsigned int cpu_id, unsigned int cpu_task_id, TimeStamp period, char *task_name);
bool delete_rt_task_from_rt_tasks_data(RtTasksData *rt_tasks_data, unsigned int cpu_id, unsigned int cpu_task_id);
void save_jitter(RtTasksData *rt_tasks_data, unsigned int cpu_id, unsigned int cpu_task_id, RTIME prev_time_count, RTIME curr_time_count, RTIME period);
void save_run_time(RtTasksData *rt_tasks_data, unsigned int cpu_id, unsigned int cpu_task_id, RTIME task_start_time, RTIME task_end_time);

#endif
