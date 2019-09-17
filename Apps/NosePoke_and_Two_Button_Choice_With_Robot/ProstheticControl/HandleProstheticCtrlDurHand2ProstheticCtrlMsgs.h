#ifndef HANDLE_PROSTHETIC_CTRL_DUR_HAND_2_PROSTHETIC_CTRL_MSGS_H
#define HANDLE_PROSTHETIC_CTRL_DUR_HAND_2_PROSTHETIC_CTRL_MSGS_H


#include <gtk/gtk.h>
#include <stdbool.h>
#include "HandleSpikeDataBuff.h"
#include "HandleRobotPosition.h"
#include "../../../Library/Status/ProstheticCtrlStatus.h"
#include "../../../Library/Status/ProstheticCtrlDurStatus.h"
#include "../../../Library/ProstheticCtrlData/ProstheticCtrlData.h"
#include "../../../Library/Messages/ProstheticCtrlDurHand2ProstheticCtrl.h"
#include "../../../Library/Messages/ProstheticCtrl2ProstheticCtrlDurHand.h"
#include "../../../Library/Messages/ProstheticCtrl2ExpCtrl.h"
#include "../../../Library/Messages/ProstheticCtrl2NeuralNet.h"
#include "../../../Library/Robot/ThreeDofRobot.h"
#include "../../../Library/LogBuffer/MessageLogBuffer.h"
#include "../../../Library/Misc/Randn.h"
#include "HandleRS232Buffers.h"
#include "ProstheticCtrlParadigm.h"
#include "../TaskConfig.h"

bool handle_prosthetic_ctrl_dur_handler_to_prosthetic_control_msg(ThreeDofRobot *robot_arm, TimeStamp current_time, ProstheticCtrlStatus *prosthetic_ctrl_status, ProstheticCtrlDurHand2ProstheticCtrlMsg *msgs_prosthetic_ctrl_dur_hand_2_prosthetic_ctrl, ProstheticCtrl2ExpCtrlMsg *msgs_prosthetic_ctrl_2_exp_ctrl, ProstheticCtrl2ProstheticCtrlDurHandMsg *msgs_prosthetic_ctrl_2_prosthetic_ctrl_dur_hand, ProstheticCtrl2NeuralNetMsg **msgs_prosthetic_ctrl_2_neural_net_multi_thread, SpikeData *scheduled_spike_data, MessageLogBuffer *message_log, ProstheticCtrlParadigmRobotReach *prosthetic_ctrl_paradigm, ThreeDofRobotPulseHistory *robot_pulse_history, ThreeDofRobotAngleHistory *robot_angle_history, ProstheticCtrlStatusHistory* prosthetic_ctrl_status_history);



#endif
