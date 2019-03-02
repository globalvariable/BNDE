#ifndef HAND_GUI_2_DIO_CTRL_MSGS_H
#define HAND_GUI_2_DIO_CTRL_MSGS_H

#include <gtk/gtk.h>
#include <stdbool.h>
#include "../../../Library/Status/DioCtrlStatus.h"
#include "../../../Library/DioCtrlData/DioCtrlData.h"
#include "../../../Library/Messages/Gui2DioCtrl.h"

bool handle_gui_to_dio_control_msg(DioCtrlData *dio_ctrl_data, TimeStamp current_time, Gui2DioCtrlMsg *msgs_gui_2_dio_ctrl);









#endif
