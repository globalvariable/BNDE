#ifndef HANDLE_PROSTHETIC_CTRL_2_EXP_CTRL_MSGS_H
#define HANDLE_PROSTHETIC_CTRL_2_EXP_CTRL_MSGS_H


#include <gtk/gtk.h>
#include <stdbool.h>
#include "../../../Library/Messages/ProstheticCtrl2ExpCtrl.h"
#include "../../../Library/Messages/ExpCtrl2ExpCtrlDur.h"
#include "../../../Library/Messages/ExpCtrl2DioCtrl.h"
#include "../../../Library/Messages/ExpCtrl2ProstheticCtrl.h"
#include "../../../Library/Messages/ExpCtrl2NeuralNet.h"
#include "../../../Library/Messages/ExpCtrl2SpikeGen.h"
#include "../../../Library/Messages/ExpCtrl2Gui.h"
#include "../../../Library/Status/ExpStatus.h"
#include "ExpCtrlParadigm.h"
#include "../../../Library/Misc/Randn.h"
#include "ExpHistory.h"
#include "../../../Library/Status/ExpStatusHistory.h"


void initialize_prosthetic_control_to_exp_control_msg_params(ExpStatus *arg_trial_status, ProstheticCtrl2ExpCtrlMsg *arg_msgs_prosthetic_ctrl_2_exp_ctrl, ExpCtrl2ExpCtrlDurMsg *arg_msgs_exp_ctrl_2_trial_dur_hand, ExpCtrl2DioCtrlMsg *arg_msgs_exp_ctrl_2_dio_ctrl, ExpCtrl2ProstheticCtrlMsg *arg_msgs_exp_ctrl_2_prosthetic_ctrl, ExpCtrl2NeuralNetMsg *arg_msgs_exp_ctrl_2_neural_net, ExpCtrlParadigmRobotReach *arg_paradigm, ClassifiedExpHistory *arg_classified_history, ExpCtrl2GuiMsg *arg_msgs_exp_ctrl_2_gui, ExpStatusHistory *arg_trial_status_history);

bool handle_prosthetic_control_to_exp_control_msg(TimeStamp current_time);





#endif
