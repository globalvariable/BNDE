#ifndef HAND_NEURAL_NET_2_PROSTHETIC_CTRL_MSGS_H
#define HAND_NEURAL_NET_2_PROSTHETIC_CTRL_MSGS_H



#include <gtk/gtk.h>
#include <stdbool.h>
#include "../../../Library/Status/ProstheticCtrlStatus.h"
#include "../../../Library/ProstheticCtrlData/ProstheticCtrlData.h"
#include "../../../Library/Messages/NeuralNet2ProstheticCtrl.h"
#include "../../../Library/Messages/NeuralNet2ProstheticCtrl.h"
#include "../../../Library/Robot/ThreeDofRobot.h"
#include "../../../Library/Izlib/SpikeData/SpikeData.h"
#include "../TaskConfig.h"
bool handle_neural_net_to_prosthetic_control_msg(ThreeDofRobot *robot_arm, TimeStamp current_time, NeuralNet2ProstheticCtrlMsg **msgs_neural_net_2_prosthetic_ctrl_multi_thread, SpikeData *scheduled_spike_data);





#endif
