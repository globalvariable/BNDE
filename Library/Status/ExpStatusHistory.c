#include "ExpStatusHistory.h"

ExpStatusHistory* allocate_trial_status_history(ExpStatusHistory* hist, unsigned int buffer_size)
{
	if (hist != NULL)
	{
		hist = deallocate_trial_status_history(hist);
		hist = allocate_trial_status_history(hist, buffer_size);
		return hist;
	}  
	hist = g_new0(ExpStatusHistory,1);
	hist->history = g_new0(ExpStatusHistoryItem, buffer_size);
	hist->buffer_size = buffer_size;	
	print_message(INFO_MSG ,"ExperimentHandler", "ExpStatusHistory", "allocate_trial_status_history", "Created ExpStatusHistory.");
	return hist;
}
ExpStatusHistory* deallocate_trial_status_history(ExpStatusHistory* hist)
{
	if (hist == NULL)
		return (ExpStatusHistory*)print_message(BUG_MSG ,"ExperimentHandler", "ExpStatusHistory", "deallocate_trial_status_history", "ExpStatusHistory == NULL.");    
	g_free(hist->history);
	g_free(hist);
	print_message(INFO_MSG ,"ExperimentHandler", "ExpStatusHistory", "deallocate_trial_status_history", "Destroyed ExpStatusHistory.");
	return NULL;
}

bool write_to_trial_status_history(ExpStatusHistory* hist, TimeStamp time, ExpStatus new_status)
{
	unsigned int *idx = &(hist->buff_write_idx);
	ExpStatusHistoryItem *item = &(hist->history[hist->buff_write_idx]);
	item->time = time;
	item->new_status = new_status;
	if ((*idx + 1) == hist->buffer_size)
		*idx = 0;
	else
		(*idx)++;
	if ((*idx) == hist->buff_read_idx)
		return print_message(BUG_MSG ,"ExperimentHandlers", "ExpStatusHistory", "write_to_trial_status_history", "BUFFER IS FULL!!!.");    		
	return TRUE;
}

bool get_next_trial_status_history_item(ExpStatusHistory* hist, ExpStatusHistoryItem *item)
{
	unsigned int *idx;
	if (hist->buff_read_idx == hist->buff_write_idx)
		return FALSE;
	idx = &(hist->buff_read_idx);
	memcpy(item, &(hist->history[*idx]), sizeof(ExpStatusHistoryItem));
	if (((*idx) + 1) == hist->buffer_size)
		*idx = 0;
	else
		(*idx)++;	
	return TRUE;	
}
