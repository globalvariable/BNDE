#include "ProstheticCtrlStatusHistory.h"

ProstheticCtrlStatusHistory* allocate_prosthetic_ctrl_status_history(ProstheticCtrlStatusHistory* hist, unsigned int buffer_size)
{
	if (hist != NULL)
	{
		hist = deallocate_prosthetic_ctrl_status_history(hist);
		hist = allocate_prosthetic_ctrl_status_history(hist, buffer_size);
		return hist;
	}  
	hist = g_new0(ProstheticCtrlStatusHistory,1);
	hist->history = g_new0(ProstheticCtrlStatusHistoryItem, buffer_size);
	hist->buffer_size = buffer_size;	
	print_message(INFO_MSG ,"ExperimentHandler", "ProstheticCtrlStatusHistory", "allocate_prosthetic_ctrl_status_history", "Created ProstheticCtrlStatusHistory.");
	return hist;
}
ProstheticCtrlStatusHistory* deallocate_prosthetic_ctrl_status_history(ProstheticCtrlStatusHistory* hist)
{
	if (hist == NULL)
		return (ProstheticCtrlStatusHistory*)print_message(BUG_MSG ,"ExperimentHandler", "ProstheticCtrlStatusHistory", "deallocate_prosthetic_ctrl_status_history", "ProstheticCtrlStatusHistory == NULL.");    
	g_free(hist->history);
	g_free(hist);
	print_message(INFO_MSG ,"ExperimentHandler", "ProstheticCtrlStatusHistory", "deallocate_prosthetic_ctrl_status_history", "Destroyed ProstheticCtrlStatusHistory.");
	return NULL;
}

bool write_to_prosthetic_ctrl_status_history(ProstheticCtrlStatusHistory* hist, TimeStamp time, ProstheticCtrlStatus new_status)
{
	unsigned int *idx = &(hist->buff_write_idx);
	ProstheticCtrlStatusHistoryItem *item = &(hist->history[hist->buff_write_idx]);
	item->time = time;
	item->new_status = new_status;
	if ((*idx + 1) == hist->buffer_size)
		*idx = 0;
	else
		(*idx)++;
	if ((*idx) == hist->buff_read_idx)
		return print_message(BUG_MSG ,"ExperimentHandlers", "ProstheticCtrlStatusHistory", "write_to_prosthetic_ctrl_status_history", "BUFFER IS FULL!!!.");    		
	return TRUE;
}

bool get_next_prosthetic_ctrl_status_history_item(ProstheticCtrlStatusHistory* hist, ProstheticCtrlStatusHistoryItem *item)
{
	unsigned int *idx;
	if (hist->buff_read_idx == hist->buff_write_idx)
		return FALSE;
	idx = &(hist->buff_read_idx);
	memcpy(item, &(hist->history[*idx]), sizeof(ProstheticCtrlStatusHistoryItem));
	if (((*idx) + 1) == hist->buffer_size)
		*idx = 0;
	else
		(*idx)++;	
	return TRUE;	
}
