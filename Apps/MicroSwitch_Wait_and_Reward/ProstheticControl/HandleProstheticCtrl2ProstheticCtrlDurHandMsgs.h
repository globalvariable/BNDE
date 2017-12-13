#ifndef HANDLE_PROSTHETIC_CTRL_2_PROSTHETIC_CTRL_DUR_HAND_MSGS_H
#define HANDLE_PROSTHETIC_CTRL_2_PROSTHETIC_CTRL_DUR_HAND_MSGS_H

#include "../../../Library/Status/ProstheticCtrlDurStatus.h"
#include "../../../Library/Messages/ProstheticCtrl2ProstheticCtrlDurHand.h"
#include "../../../Library/Messages/ProstheticCtrlDurHand2ProstheticCtrl.h"
#include "../../../Library/Misc/Misc.h"
#include "../../../Library/System/TimeStamp/TimeStamp.h"

void init_prosthetic_ctrl_duration_handler(void);
bool handle_prosthetic_control_duration(TimeStamp current_time, ProstheticCtrlDurHand2ProstheticCtrlMsg *msgs_prosthetic_ctrl_dur_hand_2_prosthetic_ctrl);
bool handle_prosthetic_control_to_prosthetic_ctrl_dur_handler_msg(TimeStamp current_time, ProstheticCtrl2ProstheticCtrlDurHandMsg *msgs_prosthetic_ctrl_2_prosthetic_ctrl_dur_hand);











#endif
