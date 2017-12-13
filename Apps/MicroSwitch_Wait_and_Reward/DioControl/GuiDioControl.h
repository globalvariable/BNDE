#ifndef GUI_DIO_CONTROL_H
#define GUI_DIO_CONTROL_H

#include "../../../Library/Messages/Gui2DioCtrl.h"
#include "../../../Library/Messages/DioCtrl2Gui.h"
#include "../../../Library/Misc/Misc.h"
#include "../../../Library/System/RtTasksData/RtTasksData.h"
#include "DataHandling/DataHandling.h"
#include "../../../Library/Status/DioCtrlComponentStatusHistory.h"
#include "../../../Library/DioCtrlData/DioCtrlData.h"
#include "DioCtrlParadigm.h"
#include "DioControlRtTask.h"

bool create_dio_control_tab(GtkWidget *tabs, RtTasksData *rt_tasks_data, Gui2DioCtrlMsg *msgs_gui_2_dio_ctrl, DioCtrl2GuiMsg *msgs_dio_ctrl_2_gui, DioCtrlInputStatusHistory *dio_ctrl_input_status_history, DioCtrlOutputStatusHistory *dio_ctrl_output_status_history, DioCtrlData *dio_ctrl_data, DioCtrlParadigmRobotReach *dio_ctrl_paradigm);


#endif
