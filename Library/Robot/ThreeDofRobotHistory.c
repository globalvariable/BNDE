#include "ThreeDofRobotHistory.h"


ThreeDofRobotAngleHistory* allocate_three_dof_robot_angle_history(ThreeDofRobotAngleHistory* hist, unsigned int buffer_size)
{
	if (hist != NULL)
	{
		hist = deallocate_three_dof_robot_angle_history(hist);
		hist = allocate_three_dof_robot_angle_history(hist, buffer_size);
		return hist;
	}  
	hist = g_new0(ThreeDofRobotAngleHistory,1);
	hist->history = g_new0(ThreeDofRobotAngleHistoryItem, buffer_size);
	hist->buffer_size = buffer_size;	
	print_message(INFO_MSG ,"ExperimentHandler", "ThreeDofRobotHistory", "allocate_three_dof_robot_angle_history", "Created ThreeDofRobotAngleHistory.");
	return hist;

}
ThreeDofRobotAngleHistory* deallocate_three_dof_robot_angle_history(ThreeDofRobotAngleHistory* hist)
{
	if (hist == NULL)
		return (ThreeDofRobotAngleHistory*)print_message(BUG_MSG ,"ExperimentHandler", "ThreeDofRobotAngleHistory", "deallocate_three_dof_robot_angle_history", "ThreeDofRobotAngleHistory == NULL.");    
	g_free(hist->history);
	g_free(hist);
	print_message(INFO_MSG ,"ExperimentHandler", "ThreeDofRobotHistory", "deallocate_three_dof_robot_angle_history", "Destroyed ThreeDofRobotAngleHistory.");
	return NULL;
}

bool write_to_three_dof_robot_angle_history(ThreeDofRobotAngleHistory* hist, TimeStamp time, ServoAngle base, ServoAngle shoulder, ServoAngle elbow)
{
	unsigned int *idx = &(hist->buff_write_idx);
	ThreeDofRobotAngleHistoryItem *item = &(hist->history[hist->buff_write_idx]);
	item->time = time;
	item->servo_angles[BASE_SERVO] = base;
	item->servo_angles[SHOULDER_SERVO] = shoulder;
	item->servo_angles[ELBOW_SERVO] = elbow;
	if ((*idx + 1) == hist->buffer_size)
		*idx = 0;
	else
		(*idx)++;
	if ((*idx) == hist->buff_read_idx)
		return print_message(BUG_MSG ,"ExperimentHandlers", "ThreeDofRobotHistory", "write_to_three_dof_robot_angle_history", "BUFFER IS FULL!!!.");    		
	return TRUE;
}
bool get_next_three_dof_robot_angle_history_item(ThreeDofRobotAngleHistory* hist, ThreeDofRobotAngleHistoryItem *item)
{
	unsigned int *idx;
	if (hist->buff_read_idx == hist->buff_write_idx)
		return FALSE;
	idx = &(hist->buff_read_idx);
	memcpy(item, &(hist->history[*idx]), sizeof(ThreeDofRobotAngleHistoryItem));
	if (((*idx) + 1) == hist->buffer_size)
		*idx = 0;
	else
		(*idx)++;	
	return TRUE;	
}	

ThreeDofRobotPulseHistory* allocate_three_dof_robot_pulse_history(ThreeDofRobotPulseHistory* hist, unsigned int buffer_size)
{
	if (hist != NULL)
	{
		hist = deallocate_three_dof_robot_pulse_history(hist);
		hist = allocate_three_dof_robot_pulse_history(hist, buffer_size);
		return hist;
	}  
	hist = g_new0(ThreeDofRobotPulseHistory,1);
	hist->history = g_new0(ThreeDofRobotPulseHistoryItem, buffer_size);
	hist->buffer_size = buffer_size;	
	print_message(INFO_MSG ,"ExperimentHandler", "ThreeDofRobotHistory", "allocate_three_dof_robot_pulse_history", "Created ThreeDofRobotPulseHistory.");
	return hist;

}
ThreeDofRobotPulseHistory* deallocate_three_dof_robot_pulse_history(ThreeDofRobotPulseHistory* hist)
{
	if (hist == NULL)
		return (ThreeDofRobotPulseHistory*)print_message(BUG_MSG ,"ExperimentHandler", "ThreeDofRobotHistory", "deallocate_three_dof_robot_pulse_history", "ThreeDofRobotPulseHistory == NULL.");    
	g_free(hist->history);
	g_free(hist);
	print_message(INFO_MSG ,"ExperimentHandler", "ThreeDofRobotHistory", "deallocate_three_dof_robot_pulse_history", "Destroyed ThreeDofRobotPulseHistory.");
	return NULL;

}
bool write_to_three_dof_robot_pulse_history(ThreeDofRobotPulseHistory* hist, TimeStamp time, ServoPulse base, ServoPulse shoulder, ServoPulse elbow)
{
	unsigned int *idx = &(hist->buff_write_idx);
	ThreeDofRobotPulseHistoryItem *item = &(hist->history[hist->buff_write_idx]);
	item->time = time;
	item->servo_pulses[BASE_SERVO] = base;
	item->servo_pulses[SHOULDER_SERVO] = shoulder;
	item->servo_pulses[ELBOW_SERVO] = elbow;
	if ((*idx + 1) == hist->buffer_size)
		*idx = 0;
	else
		(*idx)++;
	if ((*idx) == hist->buff_read_idx)
		return print_message(BUG_MSG ,"ExperimentHandlers", "ThreeDofRobotHistory", "write_to_three_dof_robot_pulse_history", "BUFFER IS FULL!!!.");    		
	return TRUE;	
}
bool get_next_three_dof_robot_pulse_history_item(ThreeDofRobotPulseHistory* hist, ThreeDofRobotPulseHistoryItem *item)
{
	unsigned int *idx;
	if (hist->buff_read_idx == hist->buff_write_idx)
		return FALSE;
	idx = &(hist->buff_read_idx);
	memcpy(item, &(hist->history[*idx]), sizeof(ThreeDofRobotPulseHistoryItem));
	if (((*idx) + 1) == hist->buffer_size)
		*idx = 0;
	else
		(*idx)++;	
	return TRUE;	
}	
