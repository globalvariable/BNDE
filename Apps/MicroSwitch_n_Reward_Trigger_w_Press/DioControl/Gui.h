#ifndef GUI_H
#define GUI_H


#include <gtk/gtk.h>
#include <stdbool.h>
#include <stdlib.h>
#include "GuiDioControl.h"
#include "../../../Library/Messages/Gui2DioCtrl.h"

// Functions
void create_gui_handler(RtTasksData *rt_tasks_data, Gui2DioCtrlMsg *msgs_gui_2_dio_ctrl, DioCtrl2GuiMsg *msgs_dio_ctrl_2_gui, DioCtrlInputStatusHistory *dio_ctrl_input_status_history, DioCtrlOutputStatusHistory *dio_ctrl_output_status_history, DioCtrlData *dio_ctrl_data, DioCtrlParadigmRobotReach *dio_ctrl_paradigm);



#endif
