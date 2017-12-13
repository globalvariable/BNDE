#ifndef HANDLE_DIO_CTRL_2_DIO_CTRL_DUR_HAND_MSGS_H
#define HANDLE_DIO_CTRL_2_DIO_CTRL_DUR_HAND_MSGS_H

#include "../../../Library/Status/DioCtrlDurStatus.h"
#include "../../../Library/Messages/DioCtrl2DioCtrlDurHand.h"
#include "../../../Library/Misc/Misc.h"
#include "../../../Library/System/TimeStamp/TimeStamp.h"
#include "ConfigDioCtrlComponentNums.h"

bool handle_dio_control_to_dio_ctrl_dur_handler_msg(DioCtrlDurationStatus *dio_ctrl_inputs_min_dur_status, DioCtrlDurationStatus *dio_ctrl_inputs_max_dur_status, TimeStamp current_time, DioCtrl2DioCtrlDurHandMsg *msgs_dio_ctrl_2_dio_ctrl_dur_hand, TimeStamp *inputs_handling_end_time_min, TimeStamp *inputs_handling_end_time_max, DioCtrlDurationStatus *dio_ctrl_outputs_dur_status, TimeStamp *outputs_handling_end_time);











#endif
