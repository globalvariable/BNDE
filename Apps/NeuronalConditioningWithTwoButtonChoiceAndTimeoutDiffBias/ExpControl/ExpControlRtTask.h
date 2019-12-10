#ifndef EXP_CONTROL_RT_TASK_H
#define EXP_CONTROL_RT_TASK_H

#include <gtk/gtk.h>
#include <stdbool.h>
#include <rtai_shm.h>
#include <rtai_nam2num.h>
#include "../../../Library/Status/ExpStatus.h"
#include "../../../Library/Messages/Gui2ExpCtrl.h"
#include "../../../Library/Messages/ExpCtrl2Gui.h"
#include "../../../Library/Messages/ExpCtrlDur2ExpCtrl.h"
#include "../../../Library/Messages/ExpCtrl2ExpCtrlDur.h"
#include "../../../Library/Messages/DioCtrl2ExpCtrl.h"
#include "../../../Library/Messages/ProstheticCtrl2ExpCtrl.h"
#include "../../../Library/Messages/ExpCtrl2DioCtrl.h"
#include "../../../Library/Messages/ExpCtrl2ProstheticCtrl.h"
#include "../../../Library/Messages/ExpCtrl2NeuralNet.h"
#include "../../../Library/Messages/NeuralNet2ExpCtrl.h"
#include "../../../Library/Messages/ExpCtrl2SpikeGen.h"
#include "../../../Library/Messages/SpikeGen2ExpCtrl.h"
#include "../../../Library/Messages/NeuRecHand2ExpCtrl.h"
#include "../../../Library/Messages/ExpCtrl2NeuRecHand.h"
#include "../../../Library/Misc/Misc.h"
#include "../../../Library/System/RtTasksData/RtTasksData.h"
#include "../../../Library/RtTaskStats/RtTaskStats.h"
#include "HandleGui2ExpCtrlMsgs.h"
#include "HandleExpCtrlDur2ExpCtrlMsgs.h"
#include "HandleDioCtrl2ExpCtrlMsgs.h"
#include "HandleProstheticCtrl2ExpCtrlMsgs.h"
#include "../../../Library/Status/ExpStatusHistory.h"
#include "HandleExpCtrl2ExpCtrlDurMsgs.h"
#include "HandleExpCtrlDur.h"
#include "../TaskConfig.h"

bool create_exp_control_rt_thread(RtTasksData *rt_tasks_data, Gui2ExpCtrlMsg *msgs_gui_2_exp_ctrl, ExpCtrlParadigmRobotReach *paradigm, ClassifiedExpHistory* classified_trial_history, ExpCtrl2GuiMsg *msgs_exp_ctrl_2_gui, ExpStatusHistory *trial_status_history);
bool kill_exp_control_rt_thread(void);









#endif
