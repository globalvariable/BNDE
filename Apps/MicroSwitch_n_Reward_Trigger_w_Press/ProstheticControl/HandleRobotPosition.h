#ifndef HANDLE_ROBOT_POSITION_THRESHOLD_H
#define HANDLE_ROBOT_POSITION_THRESHOLD_H


#include <gtk/gtk.h>
#include <stdbool.h>
#include "../../../Library/Status/ProstheticCtrlStatus.h"
#include "../../../Library/Status/ProstheticCtrlDurStatus.h"
#include "../../../Library/Robot/ThreeDofRobot.h"
#include "ProstheticCtrlParadigm.h"
#include "../../../Library/Messages/ProstheticCtrl2ProstheticCtrlDurHand.h"
#include "../../../Library/Messages/ProstheticCtrl2ExpCtrl.h"
#include "ConfigProstheticControl.h"
#include "../../../Library/Status/ProstheticCtrlStatusHistory.h"
#include "../../../Library/Messages/ProstheticCtrl2NeuralNet.h"

bool handle_robot_arm_position_threshold(ThreeDofRobot *robot, ProstheticCtrlParadigmRobotReach *paradigm, ProstheticCtrlStatus *prosthetic_ctrl_status, TimeStamp current_time, ProstheticCtrl2ProstheticCtrlDurHandMsg *msgs_prosthetic_ctrl_2_prosthetic_ctrl_dur_hand, ProstheticCtrl2ExpCtrlMsg *msgs_prosthetic_ctrl_2_exp_ctrl, ProstheticCtrlStatusHistory* prosthetic_ctrl_status_history, ProstheticCtrl2NeuralNetMsg **msgs_prosthetic_ctrl_2_neural_net_multi_thread);






#endif

