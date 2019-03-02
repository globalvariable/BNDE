#ifndef HANDLE_EXP_CTRL_DUR_H
#define HANDLE_EXP_CTRL_DUR_H

#include <gtk/gtk.h>
#include <stdbool.h>
#include "../../../Library/Messages/ExpCtrlDur2ExpCtrl.h"
#include "../../../Library/Status/ExpDurStatus.h"

bool handle_exp_control_duration(ExpDurationStatus *trial_duration_status, TimeStamp current_time, TimeStamp handling_end_time, ExpCtrlDur2ExpCtrlMsg *msgs_trial_dur_hand_2_exp_ctrl);









#endif
