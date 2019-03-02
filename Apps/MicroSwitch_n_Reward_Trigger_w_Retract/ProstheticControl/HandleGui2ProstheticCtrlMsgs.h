#ifndef HAND_GUI_2_PROSTHETIC_CTRL_MSGS_H
#define HAND_GUI_2_PROSTHETIC_CTRL_MSGS_H

#include <gtk/gtk.h>
#include <stdbool.h>
#include "../../../Library/Status/ProstheticCtrlStatus.h"
#include "../../../Library/ProstheticCtrlData/ProstheticCtrlData.h"
#include "../../../Library/Messages/Gui2ProstheticCtrl.h"
#include "../../../Library/Robot/ThreeDofRobot.h"

bool handle_gui_to_prosthetic_control_msg(ThreeDofRobot *robot_arm, ProstheticCtrlStatus *prosthetic_ctrl_status, TimeStamp current_time, Gui2ProstheticCtrlMsg *msgs_gui_2_prosthetic_ctrl);









#endif
