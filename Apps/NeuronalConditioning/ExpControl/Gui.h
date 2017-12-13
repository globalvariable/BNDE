#ifndef GUI_H
#define GUI_H


#include <gtk/gtk.h>
#include <stdbool.h>
#include <stdlib.h>
#include "GuiExpControl.h"
#include "../../../Library/Messages/Gui2ExpCtrl.h"

// Functions
void create_gui_handler(RtTasksData *rt_tasks_data, Gui2ExpCtrlMsg *msgs_gui_2_exp_ctrl, ExpCtrlParadigmRobotReach *exp_ctrl_paradigm, ClassifiedExpHistory* classified_trial_history, ExpCtrl2GuiMsg *msgs_exp_ctrl_2_gui, ExpStatusHistory *trial_status_history);



#endif
