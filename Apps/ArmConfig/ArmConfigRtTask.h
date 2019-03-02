#ifndef ARM_CONFIG_RT_TASK_H
#define ARM_CONFIG_RT_TASK_H


#include <gtk/gtk.h>
#include <stdbool.h>
#include <rtai_shm.h>
#include <rtai_nam2num.h>
#include "ArmConfig.h"
#include "../../../BlueSpike/System/RtTasksData/RtTasksData.h"
#include "../../../BlueSpike/Library/RtTaskStats/RtTaskStats.h"
#include "../../Library/RS232/RS232Handler.h"
#include "../../Library/Robot/ThreeDofRobot.h"

bool create_servo_control_rt_thread(ThreeDofRobot *robot_arm);

#endif
