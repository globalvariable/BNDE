#ifndef DIO_CONTROL_RT_TASK_H
#define DIO_CONTROL_RT_TASK_H


#include <gtk/gtk.h>
#include <stdbool.h>
#include <rtai_shm.h>
#include <rtai_nam2num.h>
#include "../../../Library/Messages/Gui2DioCtrl.h"
#include "../../../Library/Messages/DioCtrl2Gui.h"
#include "../../../Library/Messages/ExpCtrl2DioCtrl.h"
#include "../../../Library/Messages/DioCtrl2ExpCtrl.h"
#include "../../../Library/Messages/DioCtrlDurHand2DioCtrl.h"
#include "../../../Library/Messages/DioCtrl2DioCtrlDurHand.h"
#include "../../../Library/Status/DioCtrlStatus.h"
#include "../../../Library/System/RtTasksData/RtTasksData.h"
#include "../../../Library/RtTaskStats/RtTaskStats.h"
#include "DioCtrlDurationHandlerRtTask.h"
#include "../../../Library/DioCtrlData/DioCtrlData.h"
#include "../../../Library/Status/DioCtrlComponentStatusHistory.h"
#include "HandleGui2DioCtrlMsgs.h"
#include "HandleDioCtrlDurHand2DioCtrlMsgs.h"
#include "HandleExpCtrl2DioCtrlMsgs.h"
#include "HandleRS232Buffers.h"
#include "../TaskConfig.h"


bool create_dio_control_rt_thread(RtTasksData *rt_tasks_data, DioCtrlData *dio_ctrl_data, Gui2DioCtrlMsg *msgs_gui_2_dio_ctrl, DioCtrl2GuiMsg *msgs_dio_ctrl_2_gui, DioCtrlInputStatusHistory *dio_ctrl_input_status_history, DioCtrlOutputStatusHistory *dio_ctrl_output_status_history, DioCtrlParadigmRobotReach *dio_ctrl_paradigm);
bool kill_dio_control_rt_thread(void);



#endif
