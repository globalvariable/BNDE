#include "DioCtrlComponentStatusHistory.h"


DioCtrlInputStatusHistory* allocate_dio_ctrl_input_status_history(DioCtrlInputStatusHistory* hist, unsigned int buffer_size)
{
	if (hist != NULL)
	{
		hist = deallocate_dio_ctrl_input_status_history(hist);
		hist = allocate_dio_ctrl_input_status_history(hist, buffer_size);
		return hist;
	}  
	hist = g_new0(DioCtrlInputStatusHistory,1);
	hist->history = g_new0(DioCtrlInputStatusHistoryItem, buffer_size);
	hist->buffer_size = buffer_size;	
	print_message(INFO_MSG ,"ExperimentHandler", "DioCtrlHistory", "allocate_dio_ctrl_input_status_history", "Created DioCtrlInputStatusHistory.");
	return hist;
}
DioCtrlInputStatusHistory* deallocate_dio_ctrl_input_status_history(DioCtrlInputStatusHistory* hist)
{
	if (hist == NULL)
		return (DioCtrlInputStatusHistory*)print_message(BUG_MSG ,"ExperimentHandler", "DioCtrlHistory", "deallocate_dio_ctrl_input_status_history", "DioCtrlInputStatusHistory == NULL.");    
	g_free(hist->history);
	g_free(hist);
	print_message(INFO_MSG ,"ExperimentHandler", "DioCtrlHistory", "deallocate_dio_ctrl_input_status_history", "Destroyed DioCtrlInputStatusHistory.");
	return NULL;
}

bool write_to_dio_ctrl_input_status_history(DioCtrlInputStatusHistory* hist, TimeStamp time, DioCtrlInputCompNum comp_num, DioCtrlCompStatus new_status)
{
	unsigned int *idx = &(hist->buff_write_idx);
	DioCtrlInputStatusHistoryItem *item = &(hist->history[hist->buff_write_idx]);
	item->time = time;
	item->comp_num = comp_num;
	item->new_status = new_status;
	if ((*idx + 1) == hist->buffer_size)
		*idx = 0;
	else
		(*idx)++;
	if ((*idx) == hist->buff_read_idx)
		return print_message(BUG_MSG ,"ExperimentHandlers", "DioCtrlHistory", "write_to_dio_ctrl_input_status_history", "BUFFER IS FULL!!!.");    		
	return TRUE;
}

bool get_next_dio_ctrl_input_status_history_item(DioCtrlInputStatusHistory* hist, DioCtrlInputStatusHistoryItem *item)
{
	unsigned int *idx;
	if (hist->buff_read_idx == hist->buff_write_idx)
		return FALSE;
	idx = &(hist->buff_read_idx);
	memcpy(item, &(hist->history[*idx]), sizeof(DioCtrlInputStatusHistoryItem));
	if ((*idx + 1) == hist->buffer_size)
		*idx = 0;
	else
		(*idx)++;	
	return TRUE;	
}

DioCtrlOutputStatusHistory* allocate_dio_ctrl_output_status_history(DioCtrlOutputStatusHistory* hist, unsigned int buffer_size)
{
	if (hist != NULL)
	{
		hist = deallocate_dio_ctrl_output_status_history(hist);
		hist = allocate_dio_ctrl_output_status_history(hist, buffer_size);
		return hist;
	}  
	hist = g_new0(DioCtrlOutputStatusHistory,1);
	hist->history = g_new0(DioCtrlOutputStatusHistoryItem, buffer_size);
	hist->buffer_size = buffer_size;	
	print_message(INFO_MSG ,"ExperimentHandler", "DioCtrlHistory", "allocate_dio_ctrl_output_status_history", "Created DioCtrlOutputStatusHistory.");
	return hist;
}
DioCtrlOutputStatusHistory* deallocate_dio_ctrl_output_status_history(DioCtrlOutputStatusHistory* hist)
{
	if (hist == NULL)
		return (DioCtrlOutputStatusHistory*)print_message(BUG_MSG ,"ExperimentHandler", "DioCtrlHistory", "deallocate_dio_ctrl_input_status_history", "DioCtrlOutputStatusHistory == NULL.");    
	g_free(hist->history);
	g_free(hist);
	print_message(INFO_MSG ,"ExperimentHandler", "DioCtrlHistory", "deallocate_dio_ctrl_input_status_history", "Destroyed DioCtrlOutputStatusHistory.");
	return NULL;
}
bool write_to_dio_ctrl_output_status_history(DioCtrlOutputStatusHistory* hist, TimeStamp time, DioCtrlOutputCompNum comp_num, DioCtrlCompStatus new_status)
{
	unsigned int *idx = &(hist->buff_write_idx);
	DioCtrlOutputStatusHistoryItem *item = &(hist->history[hist->buff_write_idx]);
	item->time = time;
	item->comp_num = comp_num;
	item->new_status = new_status;
	if ((*idx + 1) == hist->buffer_size)
		*idx = 0;
	else
		(*idx)++;
	if ((*idx) == hist->buff_read_idx)
		return print_message(BUG_MSG ,"ExperimentHandlers", "DioCtrlHistory", "write_to_dio_ctrl_output_status_history", "BUFFER IS FULL!!!.");    		
	return TRUE;
}
bool get_next_dio_ctrl_output_status_history_item(DioCtrlOutputStatusHistory* hist, DioCtrlOutputStatusHistoryItem *item)
{
	unsigned int *idx;
	if (hist->buff_read_idx == hist->buff_write_idx)
		return FALSE;
	idx = &(hist->buff_read_idx);
	memcpy(item, &(hist->history[*idx]), sizeof(DioCtrlOutputStatusHistoryItem));
	if ((*idx + 1) == hist->buffer_size)
		*idx = 0;
	else
		(*idx)++;	
	return TRUE;
}
