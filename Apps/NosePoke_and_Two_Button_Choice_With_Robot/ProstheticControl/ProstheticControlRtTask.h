#ifndef PROSTHETIC_CONTROL_RT_TASK_H
#define PROSTHETIC_CTRL__HANDLER_RT_TASK_H


#include <gtk/gtk.h>
#include <stdbool.h>
#include <rtai_shm.h>
#include <rtai_nam2num.h>
#include "../../../Library/Messages/Gui2ProstheticCtrl.h"
#include "../../../Library/Messages/ProstheticCtrl2Gui.h"
#include "../../../Library/Messages/ExpCtrl2ProstheticCtrl.h"
#include "../../../Library/Messages/ProstheticCtrl2ExpCtrl.h"
#include "../../../Library/Messages/ProstheticCtrlDurHand2ProstheticCtrl.h"
#include "../../../Library/Messages/ProstheticCtrl2ProstheticCtrlDurHand.h"
#include "../../../Library/Messages/ProstheticCtrl2NeuralNet.h"
#include "../../../Library/Messages/NeuralNet2ProstheticCtrl.h"
#include "../../../Library/System/RtTasksData/RtTasksData.h"
#include "../../../Library/RtTaskStats/RtTaskStats.h"
#include "../../../Library/ProstheticCtrlData/ProstheticCtrlData.h"
#include "ProstheticCtrlParadigm.h"
#include "../../../Library/Robot/ThreeDofRobot.h"
#include "../../../Library/Thresholding/Thresholding.h"
#include "../../../Library/LogBuffer/MessageLogBuffer.h"
#include "../../../Library/RS232/RS232Handler.h"
#include "HandleGui2ProstheticCtrlMsgs.h"
#include "HandleProstheticCtrlDurHand2ProstheticCtrlMsgs.h"
#include "HandleProstheticCtrl2ProstheticCtrlDurHandMsgs.h"
#include "HandleExpCtrl2ProstheticCtrlMsgs.h"
#include "HandleNeuralNet2ProstheticCtrlMsgs.h"
#include "HandleSpikeDataBuff.h"
#include "../TaskConfig.h"
#include "../InterProcessMsgConfig.h"

bool create_prosthetic_control_rt_thread(RtTasksData *rt_tasks_data, ThreeDofRobot *robot_arm, Gui2ProstheticCtrlMsg *msgs_gui_2_prosthetic_ctrl, ProstheticCtrl2GuiMsg *msgs_prosthetic_ctrl_2_gui, ProstheticCtrlParadigmRobotReach *prosthetic_ctrl_paradigm, MessageLogBuffer *message_log, ProstheticCtrlStatusHistory* prosthetic_ctrl_status_history, ThreeDofRobotAngleHistory *robot_angle_history, ThreeDofRobotPulseHistory *robot_pulse_history);
bool kill_prosthetic_control_rt_thread(void);



#endif
