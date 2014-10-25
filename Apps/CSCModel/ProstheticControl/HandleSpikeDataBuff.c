#include "HandleSpikeDataBuff.h"

static TimeStamp previous_system_time = 0;

bool handle_spike_data_buff(ProstheticCtrlStatus prosthetic_ctrl_status, TimeStamp current_time, SpikeData *scheduled_spike_data, ThreeDofRobot *robot, ProstheticCtrlParadigmRobotReach *prosthetic_ctrl_paradigm)
{
	SpikeTimeStampItem *item;
	char str_prosthetic_ctrl_status[PROSTHETIC_CTRL_STATUS_MAX_STRING_LENGTH];
	unsigned int			*read_idx, write_idx, buffer_size;

	unsigned int base_servo_extensor_spike_counter;
	unsigned int base_servo_flexor_spike_counter;
	unsigned int shoulder_servo_extensor_spike_counter;
	unsigned int shoulder_servo_flexor_spike_counter;
	unsigned int elbow_servo_extensor_spike_counter;
	unsigned int elbow_servo_flexor_spike_counter;


	read_idx = &(scheduled_spike_data->buff_idx_read);
	write_idx = scheduled_spike_data->buff_idx_write;	
	buffer_size = scheduled_spike_data->buffer_size;

	switch (prosthetic_ctrl_status)
	{
		case PROSTHETIC_CTRL_STATUS_OUT_OF_TRIAL:
			while ((*read_idx) != write_idx)		
			{
				item = &(scheduled_spike_data->buff[*read_idx]);
				if (item->peak_time < previous_system_time)
				{
					print_message(BUG_MSG ,"ProstheticControl", "HandleSpikeDataBuff", "handle_spike_data_buff", "item->peak_time < previous_system_time.");    
					if ((*read_idx + 1) == buffer_size)
						*read_idx = 0;
					else
						(*read_idx)++;
					continue;
				}	
				if (item->peak_time >= current_time)	
					break;
				if ((*read_idx + 1) == buffer_size)
					*read_idx = 0;
				else
					(*read_idx)++;
			}    

			clear_spike_count_memo_of_servo(&(robot->servos[BASE_SERVO]));

			previous_system_time = current_time;
			break;
		case PROSTHETIC_CTRL_STATUS_STAYING_AT_START_POINT:
			while ((*read_idx) != write_idx)		
			{
				item = &(scheduled_spike_data->buff[*read_idx]);
				if (item->peak_time < previous_system_time)
				{
					print_message(BUG_MSG ,"ProstheticControl", "HandleSpikeDataBuff", "handle_spike_data_buff", "item->peak_time < previous_system_time.");    
					if ((*read_idx + 1) == buffer_size)
						*read_idx = 0;
					else
						(*read_idx)++;
					continue;
				}		
				if (item->peak_time >= current_time)	
					break;
				if ((*read_idx + 1) == buffer_size)
					*read_idx = 0;
				else
					(*read_idx)++;
			}    
			previous_system_time = current_time;
			break;
		case PROSTHETIC_CTRL_STATUS_AVAILABLE_TO_CONTROL:
			base_servo_extensor_spike_counter = 0;
			base_servo_flexor_spike_counter = 0;
			shoulder_servo_extensor_spike_counter = 0;
			shoulder_servo_flexor_spike_counter = 0;
			elbow_servo_extensor_spike_counter = 0;
			elbow_servo_flexor_spike_counter = 0;
			while ((*read_idx) != write_idx)		
			{
				item = &(scheduled_spike_data->buff[*read_idx]);
				if (item->peak_time < previous_system_time)
				{
					print_message(BUG_MSG ,"ProstheticControl", "HandleSpikeDataBuff", "handle_spike_data_buff", "item->peak_time < previous_system_time.");    
					if ((*read_idx + 1) == buffer_size)
						*read_idx = 0;
					else
						(*read_idx)++;
					continue;
				}	  	
				if (item->peak_time >= current_time)	
					break;
				if ((*read_idx + 1) == buffer_size)
					*read_idx = 0;
				else
					(*read_idx)++;
				switch (item->layer)
				{
					case LAYER_BASE_SERVO_EXTENSOR_SPINY:
						base_servo_extensor_spike_counter++;
						break;
					case LAYER_BASE_SERVO_FLEXOR_SPINY:
						base_servo_flexor_spike_counter++;	
						break;
					default:		
						return print_message(BUG_MSG ,"ProstheticControl", "HandleSpikeDataBuff", "handle_spike_data_buff", "Invalid Output Layer Number.");
				}
			}

			submit_servo_direction_and_speed_via_spike_count(&(robot->servos[BASE_SERVO]),  base_servo_extensor_spike_counter, base_servo_flexor_spike_counter);

			previous_system_time = current_time;    ///  IMPORTANT
			break;
		case PROSTHETIC_CTRL_STATUS_RESETTING_TO_TARGET_POINT:
			while ((*read_idx) != write_idx)		
			{
				item = &(scheduled_spike_data->buff[*read_idx]);
				if (item->peak_time < previous_system_time)
				{
					print_message(BUG_MSG ,"ProstheticControl", "HandleSpikeDataBuff", "handle_spike_data_buff", "item->peak_time < previous_system_time.");    
					if ((*read_idx + 1) == buffer_size)
						*read_idx = 0;
					else
						(*read_idx)++;
					continue;
				}		
				if (item->peak_time >= current_time)	
					break;
				if ((*read_idx + 1) == buffer_size)
					*read_idx = 0;
				else
					(*read_idx)++;
			}   
			previous_system_time = current_time; 
			break; 
		case PROSTHETIC_CTRL_STATUS_REACHED_TARGET_POINT:
			while ((*read_idx) != write_idx)		
			{
				item = &(scheduled_spike_data->buff[*read_idx]);
				if (item->peak_time < previous_system_time)
				{
					print_message(BUG_MSG ,"ProstheticControl", "HandleSpikeDataBuff", "handle_spike_data_buff", "item->peak_time < previous_system_time.");    
					if ((*read_idx + 1) == buffer_size)
						*read_idx = 0;
					else
						(*read_idx)++;
					continue;
				}		
				if (item->peak_time >= current_time)	
					break;
				if ((*read_idx + 1) == buffer_size)
					*read_idx = 0;
				else
					(*read_idx)++;
			}    
			previous_system_time = current_time;
			break; 
		case PROSTHETIC_CTRL_STATUS_RESETTING_TO_START_POINT:
			while ((*read_idx) != write_idx)		
			{
				item = &(scheduled_spike_data->buff[*read_idx]);
				if (item->peak_time < previous_system_time)
				{
					print_message(BUG_MSG ,"ProstheticControl", "HandleSpikeDataBuff", "handle_spike_data_buff", "item->peak_time < previous_system_time.");    
					if ((*read_idx + 1) == buffer_size)
						*read_idx = 0;
					else
						(*read_idx)++;
					continue;
				}	
				if (item->peak_time >= current_time)	
					break;
				if ((*read_idx + 1) == buffer_size)
					*read_idx = 0;
				else
					(*read_idx)++;
			} 
			previous_system_time = current_time;
			break; 
		case PROSTHETIC_CTRL_STATUS_DISABLED:
			while ((*read_idx) != write_idx)		
			{
				item = &(scheduled_spike_data->buff[*read_idx]);
				if (item->peak_time < previous_system_time)
				{
					print_message(BUG_MSG ,"ProstheticControl", "HandleSpikeDataBuff", "handle_spike_data_buff", "item->peak_time < previous_system_time.");    
					if ((*read_idx + 1) == buffer_size)
						*read_idx = 0;
					else
						(*read_idx)++;
					continue;
				}		
				if (item->peak_time >= current_time)	
					break;
				if ((*read_idx + 1) == buffer_size)
					*read_idx = 0;
				else
					(*read_idx)++;
			}    
			previous_system_time = current_time;
			break; 
		default:
			get_prosthetic_ctrl_status_type_string(prosthetic_ctrl_status, str_prosthetic_ctrl_status);
			return print_message(BUG_MSG ,"ProstheticControl", "HandleSpikeDataBuff", "handle_spike_data_buff", str_prosthetic_ctrl_status);
	}



	return TRUE;
}



