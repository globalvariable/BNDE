#ifndef DIO_CTRL_COMPONENT_STATUS_HISTORY_H
#define DIO_CTRL_COMPONENT_STATUS_HISTORY_H


typedef struct __DioCtrlInputStatusHistoryItem DioCtrlInputStatusHistoryItem;
typedef struct __DioCtrlOutputStatusHistoryItem DioCtrlOutputStatusHistoryItem;
typedef struct __DioCtrlInputStatusHistory DioCtrlInputStatusHistory;
typedef struct __DioCtrlOutputStatusHistory DioCtrlOutputStatusHistory;

#include "../DioCtrlData/DioCtrlComponentTypes.h"
#include "DioCtrlComponentStatus.h"
#include "../System/TimeStamp/TimeStamp.h"
#include "../Misc/Misc.h"

struct __DioCtrlInputStatusHistoryItem
{
	TimeStamp			time;
	DioCtrlInputCompNum	comp_num;
	DioCtrlCompStatus	new_status;
};

struct __DioCtrlOutputStatusHistoryItem
{
	TimeStamp				time;
	DioCtrlOutputCompNum	comp_num;
	DioCtrlCompStatus		new_status;
};


struct __DioCtrlInputStatusHistory
{
	DioCtrlInputStatusHistoryItem 	*history;
	unsigned int 					buff_write_idx;  
	unsigned int 					buff_read_idx;  
	unsigned int 					buffer_size;
};

struct __DioCtrlOutputStatusHistory
{
	DioCtrlOutputStatusHistoryItem	 	*history;
	unsigned int 					buff_write_idx;
  	unsigned int 					buff_read_idx;
	unsigned int 					buffer_size;
};

DioCtrlInputStatusHistory* allocate_dio_ctrl_input_status_history(DioCtrlInputStatusHistory* hist, unsigned int buffer_size); 
DioCtrlInputStatusHistory* deallocate_dio_ctrl_input_status_history(DioCtrlInputStatusHistory* hist); 
bool write_to_dio_ctrl_input_status_history(DioCtrlInputStatusHistory* hist, TimeStamp time, DioCtrlInputCompNum comp_num, DioCtrlCompStatus new_status);
bool get_next_dio_ctrl_input_status_history_item(DioCtrlInputStatusHistory* hist, DioCtrlInputStatusHistoryItem *item);	

DioCtrlOutputStatusHistory* allocate_dio_ctrl_output_status_history(DioCtrlOutputStatusHistory* hist, unsigned int buffer_size); 
DioCtrlOutputStatusHistory* deallocate_dio_ctrl_output_status_history(DioCtrlOutputStatusHistory* hist); 
bool write_to_dio_ctrl_output_status_history(DioCtrlOutputStatusHistory* hist, TimeStamp time, DioCtrlOutputCompNum comp_num, DioCtrlCompStatus new_status);
bool get_next_dio_ctrl_output_status_history_item(DioCtrlOutputStatusHistory* hist, DioCtrlOutputStatusHistoryItem *item);	

#endif
