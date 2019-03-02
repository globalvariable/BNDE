#ifndef DIO_CTRL_DURATION_HANDLER_RT_TASK_H
#define DIO_CTRL_DURATION_HANDLER_RT_TASK_H

#include <gtk/gtk.h>
#include <stdbool.h>
#include <rtai_shm.h>
#include <rtai_nam2num.h>
#include "../../../Library/Misc/Misc.h"
#include "../../../Library/Messages/DioCtrlDurHand2DioCtrl.h"
#include "../../../Library/Messages/DioCtrl2DioCtrlDurHand.h"
#include "../../../Library/Status/DioCtrlDurStatus.h"
#include "../../../Library/System/RtTasksData/RtTasksData.h"
#include "../../../Library/RtTaskStats/RtTaskStats.h"
#include "HandleDioCtrl2DioCtrlDurHandMsgs.h"
#include "HandleDioCtrlDur.h"
#include "DioControlRtTask.h"

bool create_dio_ctrl_duration_handler_rt_thread(RtTasksData *rt_tasks_data, DioCtrlDurHand2DioCtrlMsg *msgs_dio_ctrl_dur_hand_2_dio_ctrl, DioCtrl2DioCtrlDurHandMsg *msgs_dio_ctrl_2_dio_ctrl_dur_hand, unsigned int num_of_inp_comps, unsigned int num_of_outp_comps);
bool kill_dio_ctrl_duration_handler_rt_thread(void);









#endif
