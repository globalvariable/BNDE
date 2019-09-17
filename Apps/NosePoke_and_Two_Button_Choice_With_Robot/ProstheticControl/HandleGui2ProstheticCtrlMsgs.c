#include "HandleGui2ProstheticCtrlMsgs.h"



bool handle_gui_to_prosthetic_control_msg(ThreeDofRobot *robot_arm, ProstheticCtrlStatus *prosthetic_ctrl_status, TimeStamp current_time, Gui2ProstheticCtrlMsg *msgs_gui_2_prosthetic_ctrl)
{
	Gui2ProstheticCtrlMsgItem msg_item;
	char str_gui_msg[GUI_2_PROSTHETIC_CTRL_MSG_STRING_LENGTH];

	while (get_next_gui_2_prosthetic_ctrl_msg_buffer_item(msgs_gui_2_prosthetic_ctrl, &msg_item))
	{
		get_gui_2_prosthetic_ctrl_msg_type_string(msg_item.msg_type, str_gui_msg);
		print_message(INFO_MSG ,"ProstheticControl", "HandleGui2ProstheticCtrlMsgs", "handle_gui_to_prosthetic_control_msg", str_gui_msg);
		switch (msg_item.msg_type)
		{
			case GUI_2_PROSTHETIC_CTRL_MSG_SET_THRESHOLD:	
/*
				prosthetic_ctrl_data->glo_constraints.current_threshold = msg_item.additional_data;
*/
				break;
			default:
				return print_message(BUG_MSG ,"ProstheticControl", "HandleGui2ProstheticCtrlMsgs", "handle_gui_to_prosthetic_control_msg", str_gui_msg);
		}
	}

	return TRUE;
}
