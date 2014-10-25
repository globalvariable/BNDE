#ifndef THREE_DOF_ROBOT_HISTORY_H
#define THREE_DOF_ROBOT_HISTORY_H


typedef struct __ThreeDofRobotAngleHistoryItem ThreeDofRobotAngleHistoryItem;
typedef struct __ThreeDofRobotAngleHistory ThreeDofRobotAngleHistory;

typedef struct __ThreeDofRobotPulseHistoryItem ThreeDofRobotPulseHistoryItem;
typedef struct __ThreeDofRobotPulseHistory ThreeDofRobotPulseHistory;

#include "ThreeDofRobot.h"
#include "../System/TimeStamp/TimeStamp.h"
#include "../Misc/Misc.h"

struct __ThreeDofRobotAngleHistoryItem
{
	TimeStamp			time;
	ServoAngle			servo_angles[THREE_DOF_ROBOT_NUM_OF_SERVOS];
};

struct __ThreeDofRobotAngleHistory
{
	ThreeDofRobotAngleHistoryItem 	*history;
	unsigned int 			buff_write_idx;  
	unsigned int 			buff_read_idx;  
	unsigned int 			buffer_size;
};

struct __ThreeDofRobotPulseHistoryItem
{
	TimeStamp			time;
	ServoPulse			servo_pulses[THREE_DOF_ROBOT_NUM_OF_SERVOS];
};

struct __ThreeDofRobotPulseHistory
{
	ThreeDofRobotPulseHistoryItem 	*history;
	unsigned int 			buff_write_idx;  
	unsigned int 			buff_read_idx;  
	unsigned int 			buffer_size;
};


ThreeDofRobotAngleHistory* allocate_three_dof_robot_angle_history(ThreeDofRobotAngleHistory* hist, unsigned int buffer_size); 
ThreeDofRobotAngleHistory* deallocate_three_dof_robot_angle_history(ThreeDofRobotAngleHistory* hist); 
bool write_to_three_dof_robot_angle_history(ThreeDofRobotAngleHistory* hist, TimeStamp time, ServoAngle base, ServoAngle shoulder, ServoAngle elbow);
bool get_next_three_dof_robot_angle_history_item(ThreeDofRobotAngleHistory* hist, ThreeDofRobotAngleHistoryItem *item);	

ThreeDofRobotPulseHistory* allocate_three_dof_robot_pulse_history(ThreeDofRobotPulseHistory* hist, unsigned int buffer_size); 
ThreeDofRobotPulseHistory* deallocate_three_dof_robot_pulse_history(ThreeDofRobotPulseHistory* hist); 
bool write_to_three_dof_robot_pulse_history(ThreeDofRobotPulseHistory* hist, TimeStamp time, ServoPulse base, ServoPulse shoulder, ServoPulse elbow);
bool get_next_three_dof_robot_pulse_history_item(ThreeDofRobotPulseHistory* hist, ThreeDofRobotPulseHistoryItem *item);	

#endif
