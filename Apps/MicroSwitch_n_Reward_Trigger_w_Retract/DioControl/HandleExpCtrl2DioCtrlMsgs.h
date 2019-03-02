#ifndef HANDLE_EXP_CTRL_2_DIO_CTRL_MSGS_H
#define HANDLE_EXP_CTRL_2_DIO_CTRL_MSGS_H

#include <gtk/gtk.h>
#include <stdbool.h>
#include "../../../Library/Status/DioCtrlStatus.h"
#include "../../../Library/DioCtrlData/DioCtrlData.h"
#include "../../../Library/DioCtrlData/DioCtrlEvaluate.h"
#include "../../../Library/Messages/ExpCtrl2DioCtrl.h"
#include "../../../Library/Messages/DioCtrl2DioCtrlDurHand.h"
#include "../../../Library/Messages/DioCtrl2Gui.h"
#include "DioCtrlParadigm.h"
#include "ConfigDioCtrlComponentNums.h"
#include "HandleRS232Buffers.h"

bool handle_exp_control_to_dio_control_msg(DioCtrlData *dio_ctrl_data, TimeStamp current_time, ExpCtrl2DioCtrlMsg *msgs_exp_ctrl_2_dio_ctrl, DioCtrl2DioCtrlDurHandMsg *msgs_dio_ctrl_2_dio_ctrl_dur_hand, DioCtrlParadigmRobotReach *dio_ctrl_paradigm, DioCtrl2GuiMsg *msgs_dio_ctrl_2_gui);












#endif
