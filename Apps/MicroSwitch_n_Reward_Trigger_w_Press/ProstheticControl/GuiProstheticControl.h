#ifndef GUI_PROSTHETIC_CONTROL_H
#define GUI_PROSTHETIC_CONTROL_H


#include <stdlib.h>
#include "../../../Library/Messages/Gui2ProstheticCtrl.h"
#include "../../../Library/Messages/ProstheticCtrl2Gui.h"
#include "../../../Library/Misc/Misc.h"
#include "../../../Library/System/RtTasksData/RtTasksData.h"
#include "../../../Library/Robot/ThreeDofRobot.h"
#include "ProstheticCtrlParadigm.h"
#include "../../../Library/Thresholding/Thresholding.h"
#include "DataHandling/DataHandling.h"
#include "../../../Library/Status/ProstheticCtrlStatusHistory.h"
#include "../../../Library/Robot/ThreeDofRobotHistory.h"
#include "ProstheticControlRtTask.h"

bool create_prosthetic_control_tab(GtkWidget *tabs, RtTasksData *rt_tasks_data, Gui2ProstheticCtrlMsg *msgs_gui_2_prosthetic_ctrl, ProstheticCtrl2GuiMsg *msgs_prosthetic_ctrl_2_gui, ThreeDofRobot *robot_arm, ProstheticCtrlParadigmRobotReach *prosthetic_ctrl_paradigm, ProstheticCtrlStatusHistory* prosthetic_ctrl_status_history, ThreeDofRobotAngleHistory *robot_angle_history, ThreeDofRobotPulseHistory *robot_pulse_history);


#endif
