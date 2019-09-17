#ifndef DIO_CTRL_DUR_H
#define DIO_CTRL_DUR_H


#include <gtk/gtk.h>
#include <stdbool.h>
#include "../../../Library/Messages/DioCtrlDurHand2DioCtrl.h"
#include "../../../Library/Status/DioCtrlDurStatus.h"

bool handle_dio_control_duration(DioCtrlDurationStatus *dio_ctrl_inputs_min_dur_status, DioCtrlDurationStatus *dio_ctrl_inputs_max_dur_status, TimeStamp current_time, TimeStamp *inputs_handling_end_time_min, TimeStamp *inputs_handling_end_time_max, unsigned int num_of_input_components, DioCtrlDurHand2DioCtrlMsg *msgs_dio_ctrl_dur_hand_2_dio_ctrl, unsigned int num_of_output_components, DioCtrlDurationStatus *dio_ctrl_outputs_dur_status, TimeStamp *outputs_handling_end_time);



#endif
