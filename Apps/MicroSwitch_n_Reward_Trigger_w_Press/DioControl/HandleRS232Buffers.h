#ifndef HANDLE_RS232_BUFFERS_H
#define HANDLE_RS232_BUFFERS_H



#include <gtk/gtk.h>
#include <stdbool.h>
#include <rtai_shm.h>
#include "ConfigDioCtrlComponentNums.h"
#include "../../../Library/RS232/RS232Handler.h"
#include "../../../Library/DioCtrlData/DioCtrlData.h"
#include "../../../Library/DioCtrlData/DioCtrlEvaluate.h"
#include "../../../Library/Messages/DioCtrl2DioCtrlDurHand.h"
#include "../../../Library/System/TimeStamp/TimeStamp.h"
#include "../../../Library/Status/DioCtrlComponentStatusHistory.h"
#include "../../../Library/Messages/DioCtrl2ExpCtrl.h"

bool init_rs232_buffers(SEM **dio_ctrl_rx_buff_sem, SEM **dio_ctrl_tx_buff_sem, DioCtrlRxShm **dio_ctrl_rx_buff_shm, DioCtrlTxShm **dio_ctrl_tx_buff_shm);
bool handle_dio_ctrl_tx_shm(DioCtrlData *dio_ctrl_data, TimeStamp current_time, DioCtrlOutputStatusHistory *dio_ctrl_output_status_history);
bool handle_dio_ctrl_rx_shm(DioCtrlData *dio_ctrl_data, TimeStamp current_time, DioCtrl2DioCtrlDurHandMsg *msgs_dio_ctrl_2_dio_ctrl_dur_hand, DioCtrl2ExpCtrlMsg* msgs_dio_ctrl_2_exp_ctrl, DioCtrlInputStatusHistory *dio_ctrl_input_status_history);






#endif
