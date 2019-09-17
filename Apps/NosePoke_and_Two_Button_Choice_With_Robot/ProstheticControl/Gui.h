#ifndef GUI_H
#define GUI_H


#include <gtk/gtk.h>
#include <stdbool.h>
#include <stdlib.h>
#include "GuiProstheticControl.h"
#include "../../../Library/Messages/Gui2ProstheticCtrl.h"

// Functions
void create_gui_handler(RtTasksData *rt_tasks_data, Gui2ProstheticCtrlMsg *msgs_gui_2_prosthetic_ctrl, ProstheticCtrl2GuiMsg *msgs_prosthetic_ctrl_2_gui, ThreeDofRobot *robot_arm, ProstheticCtrlParadigmRobotReach *prosthetic_ctrl_paradigm, ProstheticCtrlStatusHistory* prosthetic_ctrl_status_history, ThreeDofRobotAngleHistory *robot_angle_history, ThreeDofRobotPulseHistory *robot_pulse_history);



#endif
