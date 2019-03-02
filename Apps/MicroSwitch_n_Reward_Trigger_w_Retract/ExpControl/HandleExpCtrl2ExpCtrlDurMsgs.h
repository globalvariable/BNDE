#ifndef HANDLE_EXP_CTRL_2_TRIAL_DUR_HAND_MSGS_H
#define HANDLE_EXP_CTRL_2_TRIAL_DUR_HAND_MSGS_H




#include <gtk/gtk.h>
#include <stdbool.h>
#include "../../../Library/Messages/ExpCtrl2ExpCtrlDur.h"
#include "../../../Library/Status/ExpDurStatus.h"


bool handle_exp_control_to_trial_dur_handler_msg(ExpDurationStatus *trial_duration_status, TimeStamp current_time, ExpCtrl2ExpCtrlDurMsg *msgs_exp_ctrl_2_trial_dur_hand, TimeStamp *handling_end_time);




#endif
