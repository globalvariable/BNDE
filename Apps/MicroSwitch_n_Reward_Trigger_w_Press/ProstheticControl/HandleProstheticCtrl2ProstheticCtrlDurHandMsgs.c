#include "HandleProstheticCtrl2ProstheticCtrlDurHandMsgs.h"

static ProstheticCtrlSchedule *prosthetic_ctrl_schedule = NULL;

void init_prosthetic_ctrl_duration_handler(void)
{
	prosthetic_ctrl_schedule = g_new0(ProstheticCtrlSchedule,1);
}

bool handle_prosthetic_control_duration(TimeStamp current_time, ProstheticCtrlDurHand2ProstheticCtrlMsg *msgs_prosthetic_ctrl_dur_hand_2_prosthetic_ctrl)
{
	unsigned int i;

	for (i = 0; i < PROSTHETIC_CTRL_DUR_STATUS_NUM_OF_ITEMS; i++)
	{
		if (prosthetic_ctrl_schedule->items[i].active)
		{
			if (current_time >= prosthetic_ctrl_schedule->items[i].schedule)
			{
				prosthetic_ctrl_schedule->items[i].active = FALSE;	
				if (! write_to_prosthetic_ctrl_dur_hand_2_prosthetic_ctrl_msg_buffer(msgs_prosthetic_ctrl_dur_hand_2_prosthetic_ctrl, current_time, PROSTHETIC_CTRL_DUR_HAND_2_PROSTHETIC_CTRL_MSG_TIMEOUT, i))
					return print_message(ERROR_MSG ,"ProstheticControl", "HandleProstheticCtrlDur", "handle_prosthetic_control_duration", "! write_to_prosthetic_ctrl_dur_hand_2_prosthetic_ctrl_msg_buffer()."); 
			}	
		}
	}
	return TRUE;
}


bool handle_prosthetic_control_to_prosthetic_ctrl_dur_handler_msg(TimeStamp current_time, ProstheticCtrl2ProstheticCtrlDurHandMsg *msgs_prosthetic_ctrl_2_prosthetic_ctrl_dur_hand)
{
	ProstheticCtrl2ProstheticCtrlDurHandMsgItem msg_item;
	while (get_next_prosthetic_ctrl_2_prosthetic_ctrl_dur_hand_msg_buffer_item(msgs_prosthetic_ctrl_2_prosthetic_ctrl_dur_hand, &msg_item))
	{
		switch (msg_item.msg_type)
		{
			case PROSTHETIC_CTRL_2_PROSTHETIC_CTRL_DUR_HAND_MSG_SET_SCHEDULE:	
				switch (msg_item.additional_data.schedule.item_idx)
				{
					case PROSTHETIC_CTRL_DUR_STATUS_ITEM_STAY_AT_CURRENT_POSITION:
						if (prosthetic_ctrl_schedule->items[PROSTHETIC_CTRL_DUR_STATUS_ITEM_STAY_AT_CURRENT_POSITION].active)
							return print_message(ERROR_MSG ,"ProstheticControl", "HandleProstheticCtrl2ProstheticCtrlDurHandMsgs", "handle_prosthetic_control_to_prosthetic_ctrl_dur_handler_msg", "PROSTHETIC_CTRL_2_PROSTHETIC_CTRL_DUR_HAND_MSG_SET_SCHEDULE & PROSTHETIC_CTRL_DUR_STATUS_ITEM_STAY_AT_CURRENT_POSITION");
						prosthetic_ctrl_schedule->items[PROSTHETIC_CTRL_DUR_STATUS_ITEM_STAY_AT_CURRENT_POSITION].schedule = msg_item.additional_data.schedule.schedule;
						prosthetic_ctrl_schedule->items[PROSTHETIC_CTRL_DUR_STATUS_ITEM_STAY_AT_CURRENT_POSITION].active = TRUE;
						break;
					case PROSTHETIC_CTRL_DUR_STATUS_ITEM_SEND_PULSE_WIDTH:
						if (prosthetic_ctrl_schedule->items[PROSTHETIC_CTRL_DUR_STATUS_ITEM_SEND_PULSE_WIDTH].active)
							return print_message(ERROR_MSG ,"ProstheticControl", "HandleProstheticCtrl2ProstheticCtrlDurHandMsgs", "handle_prosthetic_control_to_prosthetic_ctrl_dur_handler_msg", "PROSTHETIC_CTRL_2_PROSTHETIC_CTRL_DUR_HAND_MSG_SET_SCHEDULE &PROSTHETIC_CTRL_DUR_STATUS_ITEM_SEND_PULSE_WIDTH");
						prosthetic_ctrl_schedule->items[PROSTHETIC_CTRL_DUR_STATUS_ITEM_SEND_PULSE_WIDTH].schedule = msg_item.additional_data.schedule.schedule;
						prosthetic_ctrl_schedule->items[PROSTHETIC_CTRL_DUR_STATUS_ITEM_SEND_PULSE_WIDTH].active = TRUE;
						break;	
					case PROSTHETIC_CTRL_DUR_STATUS_ITEM_SEND_AD_CONVERSION:
						if (prosthetic_ctrl_schedule->items[PROSTHETIC_CTRL_DUR_STATUS_ITEM_SEND_AD_CONVERSION].active)
							return print_message(ERROR_MSG ,"ProstheticControl", "HandleProstheticCtrl2ProstheticCtrlDurHandMsgs", "handle_prosthetic_control_to_prosthetic_ctrl_dur_handler_msg", "PROSTHETIC_CTRL_2_PROSTHETIC_CTRL_DUR_HAND_MSG_SET_SCHEDULE &PROSTHETIC_CTRL_DUR_STATUS_ITEM_SEND_AD_CONVERSION");
						prosthetic_ctrl_schedule->items[PROSTHETIC_CTRL_DUR_STATUS_ITEM_SEND_AD_CONVERSION].schedule = msg_item.additional_data.schedule.schedule;
						prosthetic_ctrl_schedule->items[PROSTHETIC_CTRL_DUR_STATUS_ITEM_SEND_AD_CONVERSION].active = TRUE;
						break;	
					case PROSTHETIC_CTRL_DUR_STATUS_ITEM_READ_POSITION:
						if (prosthetic_ctrl_schedule->items[PROSTHETIC_CTRL_DUR_STATUS_ITEM_READ_POSITION].active)
							return print_message(ERROR_MSG ,"ProstheticControl", "HandleProstheticCtrl2ProstheticCtrlDurHandMsgs", "handle_prosthetic_control_to_prosthetic_ctrl_dur_handler_msg", "PROSTHETIC_CTRL_2_PROSTHETIC_CTRL_DUR_HAND_MSG_SET_SCHEDULE & PROSTHETIC_CTRL_DUR_STATUS_ITEM_READ_POSITION");
						prosthetic_ctrl_schedule->items[PROSTHETIC_CTRL_DUR_STATUS_ITEM_READ_POSITION].schedule = msg_item.additional_data.schedule.schedule;
						prosthetic_ctrl_schedule->items[PROSTHETIC_CTRL_DUR_STATUS_ITEM_READ_POSITION].active = TRUE;
						break;	
					default:
						return print_message(BUG_MSG ,"ProstheticControl", "HandleProstheticCtrl2ProstheticCtrlDurHandMsgs", "handle_prosthetic_control_to_prosthetic_ctrl_dur_handler_msg", "PROSTHETIC_CTRL_2_PROSTHETIC_CTRL_DUR_HAND_MSG_SET_SCHEDULE - switch (msg_item.additional_data.schedule.schedule_item) - default");
				}
				break;	
			case PROSTHETIC_CTRL_2_PROSTHETIC_CTRL_DUR_HAND_MSG_CANCEL_SCHEDULE:	
				switch (msg_item.additional_data.schedule.item_idx)
				{
					case PROSTHETIC_CTRL_DUR_STATUS_ITEM_STAY_AT_CURRENT_POSITION:
						prosthetic_ctrl_schedule->items[PROSTHETIC_CTRL_DUR_STATUS_ITEM_STAY_AT_CURRENT_POSITION].active = FALSE;
						break;
					case PROSTHETIC_CTRL_DUR_STATUS_ITEM_SEND_PULSE_WIDTH:
						prosthetic_ctrl_schedule->items[PROSTHETIC_CTRL_DUR_STATUS_ITEM_SEND_PULSE_WIDTH].active = FALSE;
						break;	
					case PROSTHETIC_CTRL_DUR_STATUS_ITEM_SEND_AD_CONVERSION:
						prosthetic_ctrl_schedule->items[PROSTHETIC_CTRL_DUR_STATUS_ITEM_SEND_AD_CONVERSION].active = FALSE;
						break;	
					case PROSTHETIC_CTRL_DUR_STATUS_ITEM_READ_POSITION:
						prosthetic_ctrl_schedule->items[PROSTHETIC_CTRL_DUR_STATUS_ITEM_READ_POSITION].active = FALSE;
						break;	
					default:
						return print_message(BUG_MSG ,"ProstheticControl", "HandleProstheticCtrl2ProstheticCtrlDurHandMsgs", "handle_prosthetic_control_to_prosthetic_ctrl_dur_handler_msg", "PROSTHETIC_CTRL_2_PROSTHETIC_CTRL_DUR_HAND_MSG_CANCEL_SCHEDULE - switch (msg_item.additional_data.schedule.schedule_item) - default");
				}
				break;	
			default:
				return print_message(BUG_MSG ,"ProstheticControl", "HandleProstheticCtrl2ProstheticCtrlDurHandMsgs", "handle_prosthetic_control_to_prosthetic_ctrl_dur_handler_msg", "switch(msg_item.msg_type) - default");
		}
	}
	return TRUE;
}
