#ifndef HANDLE_DIO_CTRL_DUR_HAND_2_DIO_CTRL_MSGS_H
#define HANDLE_DIO_CTRL_DUR_HAND_2_DIO_CTRL_MSGS_H


#include <gtk/gtk.h>
#include <stdbool.h>
#include "../../../Library/Status/DioCtrlStatus.h"
#include "../../../Library/DioCtrlData/DioCtrlData.h"
#include "../../../Library/DioCtrlData/DioCtrlEvaluate.h"
#include "../../../Library/Messages/DioCtrlDurHand2DioCtrl.h"
#include "../../../Library/Messages/DioCtrl2ExpCtrl.h"
#include "ConfigDioCtrlComponentNums.h"
#include "HandleRS232Buffers.h"
#include "DioCtrlParadigm.h"

bool handle_dio_ctrl_dur_handler_to_dio_control_msg(DioCtrlData *dio_ctrl_data, TimeStamp current_time, DioCtrlDurHand2DioCtrlMsg *msgs_dio_ctrl_dur_hand_2_dio_ctrl, DioCtrl2ExpCtrlMsg *msgs_dio_ctrl_2_exp_ctrl, DioCtrlParadigmRobotReach *dio_ctrl_paradigm);



#endif
