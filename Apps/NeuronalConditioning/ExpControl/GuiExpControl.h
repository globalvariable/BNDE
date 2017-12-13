#ifndef GUI_EXP_CONTROL_H
#define GUI_EXP_CONTROL_H

#include "../../../Library/Messages/Gui2ExpCtrl.h"
#include "../../../Library/Messages/ExpCtrl2Gui.h"
#include "../../../Library/Misc/Misc.h"
#include "../../../Library/System/RtTasksData/RtTasksData.h"
#include "ExpControlRtTask.h"
#include "ExpHistory.h"
#include "DataHandling/DataHandling.h"
#include "../../../Library/Status/ExpStatusHistory.h"

bool create_exp_control_tab(GtkWidget *tabs, RtTasksData *rt_tasks_data, Gui2ExpCtrlMsg *msgs_gui_2_exp_ctrl, ExpCtrlParadigmRobotReach *exp_ctrl_paradigm, ClassifiedExpHistory* classified_trial_history, ExpCtrl2GuiMsg *msgs_exp_ctrl_2_gui, ExpStatusHistory *trial_status_history);


#endif
