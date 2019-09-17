#ifndef HANDLE_EXP_CTRL_2_PROSTHETIC_CTRL_MSGS_H
#define HANDLE_EXP_CTRL_2_PROSTHETIC_CTRL_MSGS_H

#include <gtk/gtk.h>
#include <stdbool.h>
#include "ConfigProstheticControl.h"
#include "../../../Library/Status/ProstheticCtrlStatus.h"
#include "../../../Library/Status/ProstheticCtrlDurStatus.h"
#include "../../../Library/ProstheticCtrlData/ProstheticCtrlData.h"
#include "../../../Library/Messages/ExpCtrl2ProstheticCtrl.h"
#include "../../../Library/Messages/ProstheticCtrl2ProstheticCtrlDurHand.h"
#include "../../../Library/Messages/ProstheticCtrl2ExpCtrl.h"
#include "../../../Library/Messages/ProstheticCtrl2Gui.h"
#include "../../../Library/Robot/ThreeDofRobot.h"
#include "../../../Library/Coordinate/Cartesian.h"
#include "ProstheticCtrlParadigm.h"
#include "../../../Library/LogBuffer/MessageLogBuffer.h"
#include "../../../Library/Status/ProstheticCtrlStatusHistory.h"
#include "../../../Library/Messages/ProstheticCtrl2NeuralNet.h"
#include "../../../Library/Misc/Randn.h"
#include "../TaskConfig.h"

bool handle_exp_control_to_prosthetic_control_msg(ThreeDofRobot *robot_arm, ProstheticCtrlStatus *prosthetic_ctrl_status, TimeStamp current_time, ExpCtrl2ProstheticCtrlMsg *msgs_exp_ctrl_2_prosthetic_ctrl, ProstheticCtrl2ProstheticCtrlDurHandMsg *msgs_prosthetic_ctrl_2_prosthetic_ctrl_dur_hand, ProstheticCtrl2ExpCtrlMsg *msgs_prosthetic_ctrl_2_exp_ctrl, ProstheticCtrlParadigmRobotReach *prosthetic_ctrl_paradigm, MessageLogBuffer *message_log, ProstheticCtrlStatusHistory* prosthetic_ctrl_status_history, ProstheticCtrl2GuiMsg *msgs_prosthetic_ctrl_2_gui, ProstheticCtrl2NeuralNetMsg **msgs_prosthetic_ctrl_2_neural_net_multi_thread);












#endif
