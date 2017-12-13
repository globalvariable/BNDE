#ifndef HANDLE_SPIKE_DATA_BUFF_H
#define HANDLE_SPIKE_DATA_BUFF_H


#include "../../../Library/Status/ProstheticCtrlStatus.h"
#include "../../../Library/ProstheticCtrlData/ProstheticCtrlData.h"
#include "../../../Library/Izlib/SpikeData/SpikeData.h"
#include "../../../Library/Robot/ThreeDofRobot.h"
#include "ProstheticCtrlParadigm.h"
#include "../NetworkConfig.h"

bool handle_spike_data_buff(ProstheticCtrlStatus prosthetic_ctrl_status, TimeStamp current_time, SpikeData *scheduled_spike_data, ThreeDofRobot *robot, ProstheticCtrlParadigmRobotReach *prosthetic_ctrl_paradigm);


#endif
