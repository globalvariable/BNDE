#include "HandleRS232Buffers.h"


typedef union 			
{
	struct 
	{
		unsigned guide_led:1;  
		unsigned left_led:1;  
		unsigned right_led:1;  
		unsigned levers_available:1;  
		unsigned valve:1;  
		unsigned buzzer:1;
		unsigned dio_ctrl_switch:1;
		unsigned get_ready_led:1;
	} ;
	unsigned char all_cmd;  /// one byte (unsigned char, see it via Watch in debug mode)
} DioCtrlRS232Cmd;


typedef union  			
{
	struct 
	{
		unsigned ir_beam:1;  
		unsigned left_lever:1;  
		unsigned right_lever:1;  
		unsigned ir_beam_2:1;
		unsigned none1:1;
		unsigned none2:1;
		unsigned none3:1;
		unsigned none4:1;
	} ;
	unsigned char all_status;  /// one byte (unsigned char, see it via Watch in debug mode)
} DioCtrlRS232Status;



#define DIO_CTRL_STATUS_MSG_LEN			1
#define DIO_CTRL_STATUS_MSG_START_IDX	1
#define DIO_CTRL_CMD_MSG_LEN				1
#define DIO_CTRL_CMD_MSG_START_IDX		1

static SEM *static_dio_ctrl_rx_buff_sem = NULL;
static SEM *static_dio_ctrl_tx_buff_sem = NULL;
static DioCtrlRxShm *static_dio_ctrl_rx_buff_shm = NULL;
static DioCtrlTxShm *static_dio_ctrl_tx_buff_shm = NULL;

static DioCtrlRS232Cmd *dio_ctrl_rs232_cmd = NULL;
static DioCtrlRS232Status *dio_ctrl_rs232_status = NULL;

bool init_rs232_buffers(SEM **dio_ctrl_rx_buff_sem, SEM **dio_ctrl_tx_buff_sem, DioCtrlRxShm **dio_ctrl_rx_buff_shm, DioCtrlTxShm **dio_ctrl_tx_buff_shm)
{

	dio_ctrl_rs232_cmd = g_new0(DioCtrlRS232Cmd, 1);
 	dio_ctrl_rs232_status = g_new0(DioCtrlRS232Status, 1);

	if (! bind_to_dio_ctrl_rx_buffer_semaphore(dio_ctrl_rx_buff_sem))
		return print_message(ERROR_MSG ,"BMIExpController", "HandleRxTxBuffer", "init_rx_tx_buffer", "! bind_to_dio_ctrl_rx_buffer_semaphore().");	
	if (! bind_to_dio_ctrl_tx_buffer_semaphore(dio_ctrl_tx_buff_sem))
		return print_message(ERROR_MSG ,"BMIExpController", "HandleRxTxBuffer", "init_rx_tx_buffer", "! bind_to_dio_ctrl_tx_buffer_semaphore().");	
	if (! bind_to_dio_ctrl_tx_buffer_shm(dio_ctrl_tx_buff_shm) )
		return print_message(ERROR_MSG ,"BMIExpController", "HandleRxTxBuffer", "init_rx_tx_buffer", "! bind_to_dio_ctrl_tx_buffer_shm().");	
	if (! bind_to_dio_ctrl_rx_buffer_shm(dio_ctrl_rx_buff_shm) )
		return print_message(ERROR_MSG ,"BMIExpController", "HandleRxTxBuffer", "init_rx_tx_buffer", "! bind_to_dio_ctrl_rx_buffer_shm().");	

	static_dio_ctrl_rx_buff_sem = *dio_ctrl_rx_buff_sem; 
	static_dio_ctrl_tx_buff_sem = *dio_ctrl_tx_buff_sem;
	static_dio_ctrl_rx_buff_shm = *dio_ctrl_rx_buff_shm;
	static_dio_ctrl_tx_buff_shm = *dio_ctrl_tx_buff_shm;

	return TRUE;
}

bool handle_dio_ctrl_tx_shm(DioCtrlData *dio_ctrl_data, TimeStamp current_time, DioCtrlOutputStatusHistory *dio_ctrl_output_status_history)
{
	DioCtrlTxShm dio_ctrl_tx_buffer;
	static DioCtrlCompStatus output_components_status_prev[NUM_OF_OUTPUT_COMPONENTS] = {0,0,0,0,0,0};

	if (dio_ctrl_data->outp_comp_types[VALVE_IDX_IN_DIO_CTRL_DATA].status != output_components_status_prev[VALVE_IDX_IN_DIO_CTRL_DATA])
	{
		switch(dio_ctrl_data->outp_comp_types[VALVE_IDX_IN_DIO_CTRL_DATA].status)
		{
			case DIO_CTRL_COMP_STATUS_LOW:
				dio_ctrl_rs232_cmd->valve = 0;
				break;
			case DIO_CTRL_COMP_STATUS_HIGH:
				dio_ctrl_rs232_cmd->valve = 1;
				break;
			default:
				return print_message(BUG_MSG ,"DioControl", "HandleRS232Buffer", "hhandle_dio_ctrl_tx_shm", "switch(dio_ctrl_data->outp_comps[VALVE_IDX_IN_DIO_CTRL_DATA].status) - default");
		}
		output_components_status_prev[VALVE_IDX_IN_DIO_CTRL_DATA] = dio_ctrl_data->outp_comp_types[VALVE_IDX_IN_DIO_CTRL_DATA].status;
		if (! write_to_dio_ctrl_output_status_history(dio_ctrl_output_status_history, current_time, DIO_CTRL_OUTPUT_COMPONENT_VALVE_CENTER, dio_ctrl_data->outp_comp_types[VALVE_IDX_IN_DIO_CTRL_DATA].status))
			return print_message(BUG_MSG ,"BMIExpController", "HandleRS232Buffers", "handle_dio_ctrl_rx_shm", "write_to_dio_ctrl_output_status_history().");
	}

	if (dio_ctrl_data->outp_comp_types[BUZZER_IDX_IN_DIO_CTRL_DATA].status != output_components_status_prev[BUZZER_IDX_IN_DIO_CTRL_DATA])
	{			
		switch(dio_ctrl_data->outp_comp_types[BUZZER_IDX_IN_DIO_CTRL_DATA].status)
		{
			case DIO_CTRL_COMP_STATUS_LOW:
				dio_ctrl_rs232_cmd->buzzer = 0;
				break;
			case DIO_CTRL_COMP_STATUS_HIGH:
				dio_ctrl_rs232_cmd->buzzer = 1;
				break;
			default:
				return print_message(BUG_MSG ,"DioControl", "HandleRS232Buffer", "hhandle_dio_ctrl_tx_shm", "switch(dio_ctrl_data->outp_comps[BUZZER_IDX_IN_DIO_CTRL_DATA].status) - default");
		}
		output_components_status_prev[BUZZER_IDX_IN_DIO_CTRL_DATA] = dio_ctrl_data->outp_comp_types[BUZZER_IDX_IN_DIO_CTRL_DATA].status;
		if (! write_to_dio_ctrl_output_status_history(dio_ctrl_output_status_history, current_time, DIO_CTRL_OUTPUT_COMPONENT_BUZZER, dio_ctrl_data->outp_comp_types[BUZZER_IDX_IN_DIO_CTRL_DATA].status))
			return print_message(BUG_MSG ,"BMIExpController", "HandleRS232Buffers", "handle_dio_ctrl_rx_shm", "write_to_dio_ctrl_output_status_history().");
	}
	
	if (dio_ctrl_data->outp_comp_types[LEFT_LED_IDX_IN_DIO_CTRL_DATA].status != output_components_status_prev[LEFT_LED_IDX_IN_DIO_CTRL_DATA])
	{	
		switch(dio_ctrl_data->outp_comp_types[LEFT_LED_IDX_IN_DIO_CTRL_DATA].status)
		{
			case DIO_CTRL_COMP_STATUS_LOW:
				dio_ctrl_rs232_cmd->left_led = 0;
				break;
			case DIO_CTRL_COMP_STATUS_HIGH:
				dio_ctrl_rs232_cmd->left_led = 1;
				break;
			default:
				return print_message(BUG_MSG ,"DioControl", "HandleRS232Buffer", "hhandle_dio_ctrl_tx_shm", "switch(dio_ctrl_data->outp_comps[LEFT_LED_IDX_IN_DIO_CTRL_DATA].status) - default");
		}		
		output_components_status_prev[LEFT_LED_IDX_IN_DIO_CTRL_DATA] = dio_ctrl_data->outp_comp_types[LEFT_LED_IDX_IN_DIO_CTRL_DATA].status;
		if (! write_to_dio_ctrl_output_status_history(dio_ctrl_output_status_history, current_time, DIO_CTRL_OUTPUT_COMPONENT_LEFT_TARGET_LED, dio_ctrl_data->outp_comp_types[LEFT_LED_IDX_IN_DIO_CTRL_DATA].status))
			return print_message(BUG_MSG ,"BMIExpController", "HandleRS232Buffers", "handle_dio_ctrl_rx_shm", "write_to_dio_ctrl_output_status_history().");
	}

	if (dio_ctrl_data->outp_comp_types[RIGHT_LED_IDX_IN_DIO_CTRL_DATA].status != output_components_status_prev[RIGHT_LED_IDX_IN_DIO_CTRL_DATA])
	{	
		switch(dio_ctrl_data->outp_comp_types[RIGHT_LED_IDX_IN_DIO_CTRL_DATA].status)
		{
			case DIO_CTRL_COMP_STATUS_LOW:
				dio_ctrl_rs232_cmd->right_led = 0;
				break;
			case DIO_CTRL_COMP_STATUS_HIGH:
				dio_ctrl_rs232_cmd->right_led = 1;
				break;
			default:
				return print_message(BUG_MSG ,"DioControl", "HandleRS232Buffer", "hhandle_dio_ctrl_tx_shm", "switch(dio_ctrl_data->outp_comps[RIGHT_LED_IDX_IN_DIO_CTRL_DATA].status) - default");
		}		
		output_components_status_prev[RIGHT_LED_IDX_IN_DIO_CTRL_DATA] = dio_ctrl_data->outp_comp_types[RIGHT_LED_IDX_IN_DIO_CTRL_DATA].status;
		if (! write_to_dio_ctrl_output_status_history(dio_ctrl_output_status_history, current_time, DIO_CTRL_OUTPUT_COMPONENT_RIGHT_TARGET_LED, dio_ctrl_data->outp_comp_types[RIGHT_LED_IDX_IN_DIO_CTRL_DATA].status))
			return print_message(BUG_MSG ,"BMIExpController", "HandleRS232Buffers", "handle_dio_ctrl_rx_shm", "write_to_dio_ctrl_output_status_history().");
	}

	if (dio_ctrl_data->outp_comp_types[GUIDE_LED_IDX_IN_DIO_CTRL_DATA].status != output_components_status_prev[GUIDE_LED_IDX_IN_DIO_CTRL_DATA])
	{	
		switch(dio_ctrl_data->outp_comp_types[GUIDE_LED_IDX_IN_DIO_CTRL_DATA].status)
		{
			case DIO_CTRL_COMP_STATUS_LOW:
				dio_ctrl_rs232_cmd->guide_led = 0;
				break;
			case DIO_CTRL_COMP_STATUS_HIGH:
				dio_ctrl_rs232_cmd->guide_led = 1;
				break;
			default:
				return print_message(BUG_MSG ,"DioControl", "HandleRS232Buffer", "handle_dio_ctrl_tx_shm", "switch(dio_ctrl_data->outp_comps[GUIDE_LED_IDX_IN_DIO_CTRL_DATA].status) - default");
		}		
		output_components_status_prev[GUIDE_LED_IDX_IN_DIO_CTRL_DATA] = dio_ctrl_data->outp_comp_types[GUIDE_LED_IDX_IN_DIO_CTRL_DATA].status;
		if (! write_to_dio_ctrl_output_status_history(dio_ctrl_output_status_history, current_time, DIO_CTRL_OUTPUT_COMPONENT_GUIDE_LED, dio_ctrl_data->outp_comp_types[GUIDE_LED_IDX_IN_DIO_CTRL_DATA].status))
			return print_message(BUG_MSG ,"BMIExpController", "HandleRS232Buffers", "handle_dio_ctrl_rx_shm", "write_to_dio_ctrl_output_status_history().");
	}
	
	if (dio_ctrl_data->outp_comp_types[LEVER_SOLENOID_IDX_IN_DIO_CTRL_DATA].status != output_components_status_prev[LEVER_SOLENOID_IDX_IN_DIO_CTRL_DATA])
	{	
		switch(dio_ctrl_data->outp_comp_types[LEVER_SOLENOID_IDX_IN_DIO_CTRL_DATA].status)
		{
			case DIO_CTRL_COMP_STATUS_LOW:
				dio_ctrl_rs232_cmd->levers_available = 0;
				break;
			case DIO_CTRL_COMP_STATUS_HIGH:
				dio_ctrl_rs232_cmd->levers_available = 1;
				break;
			default:
				return print_message(BUG_MSG ,"DioControl", "HandleRS232Buffer", "handle_dio_ctrl_tx_shm", "switch(dio_ctrl_data->outp_comps[LEVER_SOLENOID_IDX_IN_DIO_CTRL_DATA].status) - default");
		}		
		output_components_status_prev[LEVER_SOLENOID_IDX_IN_DIO_CTRL_DATA] = dio_ctrl_data->outp_comp_types[LEVER_SOLENOID_IDX_IN_DIO_CTRL_DATA].status;
		if (! write_to_dio_ctrl_output_status_history(dio_ctrl_output_status_history, current_time, DIO_CTRL_OUTPUT_COMPONENT_LEVER_SOLENOID, dio_ctrl_data->outp_comp_types[LEVER_SOLENOID_IDX_IN_DIO_CTRL_DATA].status))
			return print_message(BUG_MSG ,"BMIExpController", "HandleRS232Buffers", "handle_dio_ctrl_rx_shm", "write_to_dio_ctrl_output_status_history().");
	}

	if (dio_ctrl_data->outp_comp_types[GET_READY_LED_IDX_IN_DIO_CTRL_DATA].status != output_components_status_prev[GET_READY_LED_IDX_IN_DIO_CTRL_DATA])
	{	
		switch(dio_ctrl_data->outp_comp_types[GET_READY_LED_IDX_IN_DIO_CTRL_DATA].status)
		{
			case DIO_CTRL_COMP_STATUS_LOW:
				dio_ctrl_rs232_cmd->get_ready_led = 0;
				break;
			case DIO_CTRL_COMP_STATUS_HIGH:
				dio_ctrl_rs232_cmd->get_ready_led = 1;
				break;
			default:
				return print_message(BUG_MSG ,"DioControl", "HandleRS232Buffer", "hhandle_dio_ctrl_tx_shm", "switch(dio_ctrl_data->outp_comps[GET_READY_LED_IDX_IN_DIO_CTRL_DATA].status) - default");
		}		
		output_components_status_prev[GET_READY_LED_IDX_IN_DIO_CTRL_DATA] = dio_ctrl_data->outp_comp_types[GET_READY_LED_IDX_IN_DIO_CTRL_DATA].status;
		if (! write_to_dio_ctrl_output_status_history(dio_ctrl_output_status_history, current_time, DIO_CTRL_OUTPUT_COMPONENT_GET_READY_LED, dio_ctrl_data->outp_comp_types[GET_READY_LED_IDX_IN_DIO_CTRL_DATA].status))
			return print_message(BUG_MSG ,"BMIExpController", "HandleRS232Buffers", "handle_dio_ctrl_rx_shm", "write_to_dio_ctrl_output_status_history().");
	}

	dio_ctrl_tx_buffer.last_write_time = current_time;
	dio_ctrl_tx_buffer.dio_ctrl_tx_buff[0] = dio_ctrl_rs232_cmd->all_cmd;
	if (! write_to_dio_ctrl_tx_buff_shm(&dio_ctrl_tx_buffer, static_dio_ctrl_tx_buff_shm, DIO_CTRL_CMD_MSG_LEN, static_dio_ctrl_tx_buff_sem))  //  Exp Envi Handler writes its command to static_dio_ctrl_tx_buff for delivery by this process
		print_message(ERROR_MSG ,"BMIExpController", "HandleRxTxBuffer", "handle_dio_ctrl_tx_shm", "! read_dio_ctrl_tx_buff_shm()."); 

	return TRUE;
}

bool handle_dio_ctrl_rx_shm(DioCtrlData *dio_ctrl_data, TimeStamp current_time, DioCtrl2DioCtrlDurHandMsg *msgs_dio_ctrl_2_dio_ctrl_dur_hand, DioCtrl2ExpCtrlMsg* msgs_dio_ctrl_2_exp_ctrl, DioCtrlInputStatusHistory *dio_ctrl_input_status_history)
{
	static DioCtrlRS232Status dio_ctrl_rs232_status_prev = { .all_status = 0 };
	DioCtrlRxShm dio_ctrl_rx_buffer;
	bool cancellation_reqiured_for_low_status_timer, setting_required_for_high_status_timer;
	bool cancellation_reqiured_for_high_status_timer, setting_required_for_low_status_timer;

	if (! read_dio_ctrl_rx_buff_shm(&dio_ctrl_rx_buffer, static_dio_ctrl_rx_buff_shm, DIO_CTRL_STATUS_MSG_LEN, static_dio_ctrl_rx_buff_sem)) 
		print_message(ERROR_MSG ,"BMIExpController", "HandleRxTxBuffer", "handle_dio_ctrl_rx_shm", "! read_dio_ctrl_tx_buff_shm()."); 
	dio_ctrl_rs232_status->all_status = dio_ctrl_rx_buffer.dio_ctrl_rx_buff[0];
//	printf ("%u\n", dio_ctrl_rs232_status->all_status);

	if (dio_ctrl_rs232_status_prev.ir_beam != dio_ctrl_rs232_status->ir_beam)
	{
//		printf ("CHANGE IR_BEAM\n");
		dio_ctrl_rs232_status_prev.ir_beam = dio_ctrl_rs232_status->ir_beam;

		if (dio_ctrl_rs232_status->ir_beam)
		{
			if (! dio_ctrl_input_low_2_high_event(&(dio_ctrl_data->inp_comp_types[RESTRAIN_SWITCH_IDX_IN_DIO_CTRL_DATA]), &cancellation_reqiured_for_low_status_timer, &setting_required_for_high_status_timer))
				return print_message(BUG_MSG ,"BMIExpController", "HandleRS232Buffers", "handle_dio_ctrl_rx_shm", "dio_ctrl_input_low_2_high_event().");
			if (cancellation_reqiured_for_low_status_timer)	 
			{
				if (! write_to_dio_ctrl_2_dio_ctrl_dur_hand_msg_buffer(msgs_dio_ctrl_2_dio_ctrl_dur_hand, current_time,  DIO_CTRL_2_DIO_CTRL_DUR_HAND_MSG_CANCEL_INPUT_MIN_TIMER, RESTRAIN_SWITCH_IDX_IN_DIO_CTRL_DATA, 0))
					return print_message(BUG_MSG ,"BMIExpController", "HandleRS232Buffers", "handle_dio_ctrl_rx_shm", "write_to_dio_ctrl_2_dio_ctrl_dur_hand_msg_buffer().");	
				if (! write_to_dio_ctrl_2_dio_ctrl_dur_hand_msg_buffer(msgs_dio_ctrl_2_dio_ctrl_dur_hand, current_time,  DIO_CTRL_2_DIO_CTRL_DUR_HAND_MSG_CANCEL_INPUT_MAX_TIMER, RESTRAIN_SWITCH_IDX_IN_DIO_CTRL_DATA, 0))
					return print_message(BUG_MSG ,"BMIExpController", "HandleRS232Buffers", "handle_dio_ctrl_rx_shm", "write_to_dio_ctrl_2_dio_ctrl_dur_hand_msg_buffer().");	
			}
			if (setting_required_for_high_status_timer)
			{	
				if (! write_to_dio_ctrl_2_dio_ctrl_dur_hand_msg_buffer(msgs_dio_ctrl_2_dio_ctrl_dur_hand, current_time,  DIO_CTRL_2_DIO_CTRL_DUR_HAND_MSG_START_INPUT_MIN_TIMER, RESTRAIN_SWITCH_IDX_IN_DIO_CTRL_DATA, dio_ctrl_data->inp_comp_types[RESTRAIN_SWITCH_IDX_IN_DIO_CTRL_DATA].constraints.min_high_status_duration + current_time))
					return print_message(BUG_MSG ,"BMIExpController", "HandleRS232Buffers", "handle_dio_ctrl_rx_shm", "write_to_dio_ctrl_2_dio_ctrl_dur_hand_msg_buffer().");
				if (! write_to_dio_ctrl_2_dio_ctrl_dur_hand_msg_buffer(msgs_dio_ctrl_2_dio_ctrl_dur_hand, current_time,  DIO_CTRL_2_DIO_CTRL_DUR_HAND_MSG_START_INPUT_MAX_TIMER, RESTRAIN_SWITCH_IDX_IN_DIO_CTRL_DATA, dio_ctrl_data->inp_comp_types[RESTRAIN_SWITCH_IDX_IN_DIO_CTRL_DATA].constraints.max_high_status_duration + current_time))
					return print_message(BUG_MSG ,"BMIExpController", "HandleRS232Buffers", "handle_dio_ctrl_rx_shm", "write_to_dio_ctrl_2_dio_ctrl_dur_hand_msg_buffer().");
			}
			if (! write_to_dio_ctrl_input_status_history(dio_ctrl_input_status_history, current_time, DIO_CTRL_INPUT_COMPONENT_IR_BEAM_NOSE_POKE, DIO_CTRL_COMP_STATUS_HIGH))
				return print_message(BUG_MSG ,"BMIExpController", "HandleRS232Buffers", "handle_dio_ctrl_rx_shm", "write_to_dio_ctrl_input_status_history().");
		}
		else
		{
			if (! dio_ctrl_input_high_2_low_event(&(dio_ctrl_data->inp_comp_types[RESTRAIN_SWITCH_IDX_IN_DIO_CTRL_DATA]), &cancellation_reqiured_for_high_status_timer, &setting_required_for_low_status_timer))
				return print_message(BUG_MSG ,"DioControl", "HandleRS232Buffers", "handle_dio_ctrl_rx_shm", "dio_ctrl_input_high_2_low_event().");
			if (cancellation_reqiured_for_high_status_timer)	 
			{
				if (! write_to_dio_ctrl_2_dio_ctrl_dur_hand_msg_buffer(msgs_dio_ctrl_2_dio_ctrl_dur_hand, current_time,  DIO_CTRL_2_DIO_CTRL_DUR_HAND_MSG_CANCEL_INPUT_MIN_TIMER, RESTRAIN_SWITCH_IDX_IN_DIO_CTRL_DATA, 0))
					return print_message(BUG_MSG ,"BMIExpController", "HandleRS232Buffers", "handle_dio_ctrl_rx_shm", "write_to_dio_ctrl_2_dio_ctrl_dur_hand_msg_buffer().");	
				if (! write_to_dio_ctrl_2_dio_ctrl_dur_hand_msg_buffer(msgs_dio_ctrl_2_dio_ctrl_dur_hand, current_time,  DIO_CTRL_2_DIO_CTRL_DUR_HAND_MSG_CANCEL_INPUT_MAX_TIMER, RESTRAIN_SWITCH_IDX_IN_DIO_CTRL_DATA, 0))
					return print_message(BUG_MSG ,"BMIExpController", "HandleRS232Buffers", "handle_dio_ctrl_rx_shm", "write_to_dio_ctrl_2_dio_ctrl_dur_hand_msg_buffer().");		
			}
			if (setting_required_for_low_status_timer)
			{	
				if (! write_to_dio_ctrl_2_dio_ctrl_dur_hand_msg_buffer(msgs_dio_ctrl_2_dio_ctrl_dur_hand, current_time,  DIO_CTRL_2_DIO_CTRL_DUR_HAND_MSG_START_INPUT_MIN_TIMER, RESTRAIN_SWITCH_IDX_IN_DIO_CTRL_DATA, dio_ctrl_data->inp_comp_types[RESTRAIN_SWITCH_IDX_IN_DIO_CTRL_DATA].constraints.min_low_status_duration + current_time))
					return print_message(BUG_MSG ,"BMIExpController", "HandleRS232Buffers", "handle_dio_ctrl_rx_shm", "write_to_dio_ctrl_2_dio_ctrl_dur_hand_msg_buffer().");	
				if (! write_to_dio_ctrl_2_dio_ctrl_dur_hand_msg_buffer(msgs_dio_ctrl_2_dio_ctrl_dur_hand, current_time,  DIO_CTRL_2_DIO_CTRL_DUR_HAND_MSG_START_INPUT_MAX_TIMER, RESTRAIN_SWITCH_IDX_IN_DIO_CTRL_DATA, dio_ctrl_data->inp_comp_types[RESTRAIN_SWITCH_IDX_IN_DIO_CTRL_DATA].constraints.max_low_status_duration + current_time))
					return print_message(BUG_MSG ,"BMIExpController", "HandleRS232Buffers", "handle_dio_ctrl_rx_shm", "write_to_dio_ctrl_2_dio_ctrl_dur_hand_msg_buffer().");	
			}	
			if (! write_to_dio_ctrl_input_status_history(dio_ctrl_input_status_history, current_time, DIO_CTRL_INPUT_COMPONENT_IR_BEAM_NOSE_POKE, DIO_CTRL_COMP_STATUS_LOW))
				return print_message(BUG_MSG ,"BMIExpController", "HandleRS232Buffers", "handle_dio_ctrl_rx_shm", "write_to_dio_ctrl_input_status_history().");
		}
	}



	if (dio_ctrl_rs232_status_prev.left_lever != dio_ctrl_rs232_status->left_lever)
	{
//		printf ("CHANGE LEFT_LEVER\n");
		dio_ctrl_rs232_status_prev.left_lever = dio_ctrl_rs232_status->left_lever;

		if (dio_ctrl_rs232_status->left_lever)
		{
			if (! dio_ctrl_input_low_2_high_event(&(dio_ctrl_data->inp_comp_types[LEFT_LEVER_IDX_IN_DIO_CTRL_DATA]), &cancellation_reqiured_for_low_status_timer, &setting_required_for_high_status_timer))
				return print_message(BUG_MSG ,"BMIExpController", "HandleRS232Buffers", "handle_dio_ctrl_rx_shm", "dio_ctrl_input_low_2_high_event().");
			if (cancellation_reqiured_for_low_status_timer)	 
			{
				if (! write_to_dio_ctrl_2_dio_ctrl_dur_hand_msg_buffer(msgs_dio_ctrl_2_dio_ctrl_dur_hand, current_time,  DIO_CTRL_2_DIO_CTRL_DUR_HAND_MSG_CANCEL_INPUT_MIN_TIMER, LEFT_LEVER_IDX_IN_DIO_CTRL_DATA, 0))
					return print_message(BUG_MSG ,"BMIExpController", "HandleRS232Buffers", "handle_dio_ctrl_rx_shm", "write_to_dio_ctrl_2_dio_ctrl_dur_hand_msg_buffer().");	
				if (! write_to_dio_ctrl_2_dio_ctrl_dur_hand_msg_buffer(msgs_dio_ctrl_2_dio_ctrl_dur_hand, current_time,  DIO_CTRL_2_DIO_CTRL_DUR_HAND_MSG_CANCEL_INPUT_MAX_TIMER, LEFT_LEVER_IDX_IN_DIO_CTRL_DATA, 0))
					return print_message(BUG_MSG ,"BMIExpController", "HandleRS232Buffers", "handle_dio_ctrl_rx_shm", "write_to_dio_ctrl_2_dio_ctrl_dur_hand_msg_buffer().");	
			}
			if (setting_required_for_high_status_timer)
			{	
				if (! write_to_dio_ctrl_2_dio_ctrl_dur_hand_msg_buffer(msgs_dio_ctrl_2_dio_ctrl_dur_hand, current_time,  DIO_CTRL_2_DIO_CTRL_DUR_HAND_MSG_START_INPUT_MIN_TIMER, LEFT_LEVER_IDX_IN_DIO_CTRL_DATA, dio_ctrl_data->inp_comp_types[LEFT_LEVER_IDX_IN_DIO_CTRL_DATA].constraints.min_high_status_duration + current_time))
					return print_message(BUG_MSG ,"BMIExpController", "HandleRS232Buffers", "handle_dio_ctrl_rx_shm", "write_to_dio_ctrl_2_dio_ctrl_dur_hand_msg_buffer().");
				if (! write_to_dio_ctrl_2_dio_ctrl_dur_hand_msg_buffer(msgs_dio_ctrl_2_dio_ctrl_dur_hand, current_time,  DIO_CTRL_2_DIO_CTRL_DUR_HAND_MSG_START_INPUT_MAX_TIMER, LEFT_LEVER_IDX_IN_DIO_CTRL_DATA, dio_ctrl_data->inp_comp_types[LEFT_LEVER_IDX_IN_DIO_CTRL_DATA].constraints.max_high_status_duration + current_time))
					return print_message(BUG_MSG ,"BMIExpController", "HandleRS232Buffers", "handle_dio_ctrl_rx_shm", "write_to_dio_ctrl_2_dio_ctrl_dur_hand_msg_buffer().");
			}
			if (! write_to_dio_ctrl_input_status_history(dio_ctrl_input_status_history, current_time, DIO_CTRL_INPUT_COMPONENT_LEFT_LEVER, DIO_CTRL_COMP_STATUS_HIGH))
				return print_message(BUG_MSG ,"BMIExpController", "HandleRS232Buffers", "handle_dio_ctrl_rx_shm", "write_to_dio_ctrl_input_status_history().");
		}
		else
		{
			if (! dio_ctrl_input_high_2_low_event(&(dio_ctrl_data->inp_comp_types[LEFT_LEVER_IDX_IN_DIO_CTRL_DATA]), &cancellation_reqiured_for_high_status_timer, &setting_required_for_low_status_timer))
				return print_message(BUG_MSG ,"DioControl", "HandleRS232Buffers", "handle_dio_ctrl_rx_shm", "dio_ctrl_input_high_2_low_event().");
			if (cancellation_reqiured_for_high_status_timer)	 
			{
				if (! write_to_dio_ctrl_2_dio_ctrl_dur_hand_msg_buffer(msgs_dio_ctrl_2_dio_ctrl_dur_hand, current_time,  DIO_CTRL_2_DIO_CTRL_DUR_HAND_MSG_CANCEL_INPUT_MIN_TIMER, LEFT_LEVER_IDX_IN_DIO_CTRL_DATA, 0))
					return print_message(BUG_MSG ,"BMIExpController", "HandleRS232Buffers", "handle_dio_ctrl_rx_shm", "write_to_dio_ctrl_2_dio_ctrl_dur_hand_msg_buffer().");	
				if (! write_to_dio_ctrl_2_dio_ctrl_dur_hand_msg_buffer(msgs_dio_ctrl_2_dio_ctrl_dur_hand, current_time,  DIO_CTRL_2_DIO_CTRL_DUR_HAND_MSG_CANCEL_INPUT_MAX_TIMER, LEFT_LEVER_IDX_IN_DIO_CTRL_DATA, 0))
					return print_message(BUG_MSG ,"BMIExpController", "HandleRS232Buffers", "handle_dio_ctrl_rx_shm", "write_to_dio_ctrl_2_dio_ctrl_dur_hand_msg_buffer().");		
			}
			if (setting_required_for_low_status_timer)
			{	
				if (! write_to_dio_ctrl_2_dio_ctrl_dur_hand_msg_buffer(msgs_dio_ctrl_2_dio_ctrl_dur_hand, current_time,  DIO_CTRL_2_DIO_CTRL_DUR_HAND_MSG_START_INPUT_MIN_TIMER, LEFT_LEVER_IDX_IN_DIO_CTRL_DATA, dio_ctrl_data->inp_comp_types[LEFT_LEVER_IDX_IN_DIO_CTRL_DATA].constraints.min_low_status_duration + current_time))
					return print_message(BUG_MSG ,"BMIExpController", "HandleRS232Buffers", "handle_dio_ctrl_rx_shm", "write_to_dio_ctrl_2_dio_ctrl_dur_hand_msg_buffer().");	
				if (! write_to_dio_ctrl_2_dio_ctrl_dur_hand_msg_buffer(msgs_dio_ctrl_2_dio_ctrl_dur_hand, current_time,  DIO_CTRL_2_DIO_CTRL_DUR_HAND_MSG_START_INPUT_MAX_TIMER, LEFT_LEVER_IDX_IN_DIO_CTRL_DATA, dio_ctrl_data->inp_comp_types[LEFT_LEVER_IDX_IN_DIO_CTRL_DATA].constraints.max_low_status_duration + current_time))
					return print_message(BUG_MSG ,"BMIExpController", "HandleRS232Buffers", "handle_dio_ctrl_rx_shm", "write_to_dio_ctrl_2_dio_ctrl_dur_hand_msg_buffer().");	
			}	
			if (! write_to_dio_ctrl_input_status_history(dio_ctrl_input_status_history, current_time, DIO_CTRL_INPUT_COMPONENT_LEFT_LEVER, DIO_CTRL_COMP_STATUS_LOW))
				return print_message(BUG_MSG ,"BMIExpController", "HandleRS232Buffers", "handle_dio_ctrl_rx_shm", "write_to_dio_ctrl_input_status_history().");
		}



	}
	if (dio_ctrl_rs232_status_prev.right_lever != dio_ctrl_rs232_status->right_lever)
	{
//		printf ("CHANGE RIGHT_LEVER\n");
		dio_ctrl_rs232_status_prev.right_lever = dio_ctrl_rs232_status->right_lever;

		if (dio_ctrl_rs232_status->right_lever)
		{
			if (! dio_ctrl_input_low_2_high_event(&(dio_ctrl_data->inp_comp_types[RIGHT_LEVER_IDX_IN_DIO_CTRL_DATA]), &cancellation_reqiured_for_low_status_timer, &setting_required_for_high_status_timer))
				return print_message(BUG_MSG ,"BMIExpController", "HandleRS232Buffers", "handle_dio_ctrl_rx_shm", "dio_ctrl_input_low_2_high_event().");
			if (cancellation_reqiured_for_low_status_timer)	 
			{
				if (! write_to_dio_ctrl_2_dio_ctrl_dur_hand_msg_buffer(msgs_dio_ctrl_2_dio_ctrl_dur_hand, current_time,  DIO_CTRL_2_DIO_CTRL_DUR_HAND_MSG_CANCEL_INPUT_MIN_TIMER, RIGHT_LEVER_IDX_IN_DIO_CTRL_DATA, 0))
					return print_message(BUG_MSG ,"BMIExpController", "HandleRS232Buffers", "handle_dio_ctrl_rx_shm", "write_to_dio_ctrl_2_dio_ctrl_dur_hand_msg_buffer().");	
				if (! write_to_dio_ctrl_2_dio_ctrl_dur_hand_msg_buffer(msgs_dio_ctrl_2_dio_ctrl_dur_hand, current_time,  DIO_CTRL_2_DIO_CTRL_DUR_HAND_MSG_CANCEL_INPUT_MAX_TIMER, RIGHT_LEVER_IDX_IN_DIO_CTRL_DATA, 0))
					return print_message(BUG_MSG ,"BMIExpController", "HandleRS232Buffers", "handle_dio_ctrl_rx_shm", "write_to_dio_ctrl_2_dio_ctrl_dur_hand_msg_buffer().");	
			}
			if (setting_required_for_high_status_timer)
			{	
				if (! write_to_dio_ctrl_2_dio_ctrl_dur_hand_msg_buffer(msgs_dio_ctrl_2_dio_ctrl_dur_hand, current_time,  DIO_CTRL_2_DIO_CTRL_DUR_HAND_MSG_START_INPUT_MIN_TIMER, RIGHT_LEVER_IDX_IN_DIO_CTRL_DATA, dio_ctrl_data->inp_comp_types[RIGHT_LEVER_IDX_IN_DIO_CTRL_DATA].constraints.min_high_status_duration + current_time))
					return print_message(BUG_MSG ,"BMIExpController", "HandleRS232Buffers", "handle_dio_ctrl_rx_shm", "write_to_dio_ctrl_2_dio_ctrl_dur_hand_msg_buffer().");
				if (! write_to_dio_ctrl_2_dio_ctrl_dur_hand_msg_buffer(msgs_dio_ctrl_2_dio_ctrl_dur_hand, current_time,  DIO_CTRL_2_DIO_CTRL_DUR_HAND_MSG_START_INPUT_MAX_TIMER, RIGHT_LEVER_IDX_IN_DIO_CTRL_DATA, dio_ctrl_data->inp_comp_types[RIGHT_LEVER_IDX_IN_DIO_CTRL_DATA].constraints.max_high_status_duration + current_time))
					return print_message(BUG_MSG ,"BMIExpController", "HandleRS232Buffers", "handle_dio_ctrl_rx_shm", "write_to_dio_ctrl_2_dio_ctrl_dur_hand_msg_buffer().");
			}
			if (! write_to_dio_ctrl_input_status_history(dio_ctrl_input_status_history, current_time, DIO_CTRL_INPUT_COMPONENT_RIGHT_LEVER, DIO_CTRL_COMP_STATUS_HIGH))
				return print_message(BUG_MSG ,"BMIExpController", "HandleRS232Buffers", "handle_dio_ctrl_rx_shm", "write_to_dio_ctrl_input_status_history().");
		}
		else
		{
			if (! dio_ctrl_input_high_2_low_event(&(dio_ctrl_data->inp_comp_types[RIGHT_LEVER_IDX_IN_DIO_CTRL_DATA]), &cancellation_reqiured_for_high_status_timer, &setting_required_for_low_status_timer))
				return print_message(BUG_MSG ,"DioControl", "HandleRS232Buffers", "handle_dio_ctrl_rx_shm", "dio_ctrl_input_high_2_low_event().");
			if (cancellation_reqiured_for_high_status_timer)	 
			{
				if (! write_to_dio_ctrl_2_dio_ctrl_dur_hand_msg_buffer(msgs_dio_ctrl_2_dio_ctrl_dur_hand, current_time,  DIO_CTRL_2_DIO_CTRL_DUR_HAND_MSG_CANCEL_INPUT_MIN_TIMER, RIGHT_LEVER_IDX_IN_DIO_CTRL_DATA, 0))
					return print_message(BUG_MSG ,"BMIExpController", "HandleRS232Buffers", "handle_dio_ctrl_rx_shm", "write_to_dio_ctrl_2_dio_ctrl_dur_hand_msg_buffer().");	
				if (! write_to_dio_ctrl_2_dio_ctrl_dur_hand_msg_buffer(msgs_dio_ctrl_2_dio_ctrl_dur_hand, current_time,  DIO_CTRL_2_DIO_CTRL_DUR_HAND_MSG_CANCEL_INPUT_MAX_TIMER, RIGHT_LEVER_IDX_IN_DIO_CTRL_DATA, 0))
					return print_message(BUG_MSG ,"BMIExpController", "HandleRS232Buffers", "handle_dio_ctrl_rx_shm", "write_to_dio_ctrl_2_dio_ctrl_dur_hand_msg_buffer().");		
			}
			if (setting_required_for_low_status_timer)
			{	
				if (! write_to_dio_ctrl_2_dio_ctrl_dur_hand_msg_buffer(msgs_dio_ctrl_2_dio_ctrl_dur_hand, current_time,  DIO_CTRL_2_DIO_CTRL_DUR_HAND_MSG_START_INPUT_MIN_TIMER, RIGHT_LEVER_IDX_IN_DIO_CTRL_DATA, dio_ctrl_data->inp_comp_types[RIGHT_LEVER_IDX_IN_DIO_CTRL_DATA].constraints.min_low_status_duration + current_time))
					return print_message(BUG_MSG ,"BMIExpController", "HandleRS232Buffers", "handle_dio_ctrl_rx_shm", "write_to_dio_ctrl_2_dio_ctrl_dur_hand_msg_buffer().");	
				if (! write_to_dio_ctrl_2_dio_ctrl_dur_hand_msg_buffer(msgs_dio_ctrl_2_dio_ctrl_dur_hand, current_time,  DIO_CTRL_2_DIO_CTRL_DUR_HAND_MSG_START_INPUT_MAX_TIMER, RIGHT_LEVER_IDX_IN_DIO_CTRL_DATA, dio_ctrl_data->inp_comp_types[RIGHT_LEVER_IDX_IN_DIO_CTRL_DATA].constraints.max_low_status_duration + current_time))
					return print_message(BUG_MSG ,"BMIExpController", "HandleRS232Buffers", "handle_dio_ctrl_rx_shm", "write_to_dio_ctrl_2_dio_ctrl_dur_hand_msg_buffer().");	
			}	
			if (! write_to_dio_ctrl_input_status_history(dio_ctrl_input_status_history, current_time, DIO_CTRL_INPUT_COMPONENT_RIGHT_LEVER, DIO_CTRL_COMP_STATUS_LOW))
				return print_message(BUG_MSG ,"BMIExpController", "HandleRS232Buffers", "handle_dio_ctrl_rx_shm", "write_to_dio_ctrl_input_status_history().");
		}





	}

	if (dio_ctrl_rs232_status_prev.ir_beam_2 != dio_ctrl_rs232_status->ir_beam_2)
	{
//		printf ("CHANGE IR_BEAM_2\n");

		dio_ctrl_rs232_status_prev.ir_beam_2 = dio_ctrl_rs232_status->ir_beam_2;

		if (dio_ctrl_rs232_status->ir_beam_2)
		{
			if (! dio_ctrl_input_low_2_high_event(&(dio_ctrl_data->inp_comp_types[IR_BEAM_IDX_IN_DIO_CTRL_DATA]), &cancellation_reqiured_for_low_status_timer, &setting_required_for_high_status_timer))
				return print_message(BUG_MSG ,"BMIExpController", "HandleRS232Buffers", "handle_dio_ctrl_rx_shm", "dio_ctrl_input_low_2_high_event().");
			if (cancellation_reqiured_for_low_status_timer)	 
			{
				if (! write_to_dio_ctrl_2_dio_ctrl_dur_hand_msg_buffer(msgs_dio_ctrl_2_dio_ctrl_dur_hand, current_time,  DIO_CTRL_2_DIO_CTRL_DUR_HAND_MSG_CANCEL_INPUT_MIN_TIMER, IR_BEAM_IDX_IN_DIO_CTRL_DATA, 0))
					return print_message(BUG_MSG ,"BMIExpController", "HandleRS232Buffers", "handle_dio_ctrl_rx_shm", "write_to_dio_ctrl_2_dio_ctrl_dur_hand_msg_buffer().");	
				if (! write_to_dio_ctrl_2_dio_ctrl_dur_hand_msg_buffer(msgs_dio_ctrl_2_dio_ctrl_dur_hand, current_time,  DIO_CTRL_2_DIO_CTRL_DUR_HAND_MSG_CANCEL_INPUT_MAX_TIMER, IR_BEAM_IDX_IN_DIO_CTRL_DATA, 0))
					return print_message(BUG_MSG ,"BMIExpController", "HandleRS232Buffers", "handle_dio_ctrl_rx_shm", "write_to_dio_ctrl_2_dio_ctrl_dur_hand_msg_buffer().");	
			}
			if (setting_required_for_high_status_timer)
			{	
				if (! write_to_dio_ctrl_2_dio_ctrl_dur_hand_msg_buffer(msgs_dio_ctrl_2_dio_ctrl_dur_hand, current_time,  DIO_CTRL_2_DIO_CTRL_DUR_HAND_MSG_START_INPUT_MIN_TIMER, IR_BEAM_IDX_IN_DIO_CTRL_DATA, dio_ctrl_data->inp_comp_types[IR_BEAM_IDX_IN_DIO_CTRL_DATA].constraints.min_high_status_duration + current_time))
					return print_message(BUG_MSG ,"BMIExpController", "HandleRS232Buffers", "handle_dio_ctrl_rx_shm", "write_to_dio_ctrl_2_dio_ctrl_dur_hand_msg_buffer().");
				if (! write_to_dio_ctrl_2_dio_ctrl_dur_hand_msg_buffer(msgs_dio_ctrl_2_dio_ctrl_dur_hand, current_time,  DIO_CTRL_2_DIO_CTRL_DUR_HAND_MSG_START_INPUT_MAX_TIMER, IR_BEAM_IDX_IN_DIO_CTRL_DATA, dio_ctrl_data->inp_comp_types[IR_BEAM_IDX_IN_DIO_CTRL_DATA].constraints.max_high_status_duration + current_time))
					return print_message(BUG_MSG ,"BMIExpController", "HandleRS232Buffers", "handle_dio_ctrl_rx_shm", "write_to_dio_ctrl_2_dio_ctrl_dur_hand_msg_buffer().");
			}
			if (! write_to_dio_ctrl_input_status_history(dio_ctrl_input_status_history, current_time, DIO_CTRL_INPUT_COMPONENT_IR_BEAM_NOSE_POKE, DIO_CTRL_COMP_STATUS_HIGH))
				return print_message(BUG_MSG ,"BMIExpController", "HandleRS232Buffers", "handle_dio_ctrl_rx_shm", "write_to_dio_ctrl_input_status_history().");
		}
		else
		{
			if (! dio_ctrl_input_high_2_low_event(&(dio_ctrl_data->inp_comp_types[IR_BEAM_IDX_IN_DIO_CTRL_DATA]), &cancellation_reqiured_for_high_status_timer, &setting_required_for_low_status_timer))
				return print_message(BUG_MSG ,"DioControl", "HandleRS232Buffers", "handle_dio_ctrl_rx_shm", "dio_ctrl_input_high_2_low_event().");
			if (cancellation_reqiured_for_high_status_timer)	 
			{
				if (! write_to_dio_ctrl_2_dio_ctrl_dur_hand_msg_buffer(msgs_dio_ctrl_2_dio_ctrl_dur_hand, current_time,  DIO_CTRL_2_DIO_CTRL_DUR_HAND_MSG_CANCEL_INPUT_MIN_TIMER, IR_BEAM_IDX_IN_DIO_CTRL_DATA, 0))
					return print_message(BUG_MSG ,"BMIExpController", "HandleRS232Buffers", "handle_dio_ctrl_rx_shm", "write_to_dio_ctrl_2_dio_ctrl_dur_hand_msg_buffer().");	
				if (! write_to_dio_ctrl_2_dio_ctrl_dur_hand_msg_buffer(msgs_dio_ctrl_2_dio_ctrl_dur_hand, current_time,  DIO_CTRL_2_DIO_CTRL_DUR_HAND_MSG_CANCEL_INPUT_MAX_TIMER, IR_BEAM_IDX_IN_DIO_CTRL_DATA, 0))
					return print_message(BUG_MSG ,"BMIExpController", "HandleRS232Buffers", "handle_dio_ctrl_rx_shm", "write_to_dio_ctrl_2_dio_ctrl_dur_hand_msg_buffer().");		
			}
			if (setting_required_for_low_status_timer)
			{	
				if (! write_to_dio_ctrl_2_dio_ctrl_dur_hand_msg_buffer(msgs_dio_ctrl_2_dio_ctrl_dur_hand, current_time,  DIO_CTRL_2_DIO_CTRL_DUR_HAND_MSG_START_INPUT_MIN_TIMER, IR_BEAM_IDX_IN_DIO_CTRL_DATA, dio_ctrl_data->inp_comp_types[IR_BEAM_IDX_IN_DIO_CTRL_DATA].constraints.min_low_status_duration + current_time))
					return print_message(BUG_MSG ,"BMIExpController", "HandleRS232Buffers", "handle_dio_ctrl_rx_shm", "write_to_dio_ctrl_2_dio_ctrl_dur_hand_msg_buffer().");	
				if (! write_to_dio_ctrl_2_dio_ctrl_dur_hand_msg_buffer(msgs_dio_ctrl_2_dio_ctrl_dur_hand, current_time,  DIO_CTRL_2_DIO_CTRL_DUR_HAND_MSG_START_INPUT_MAX_TIMER, IR_BEAM_IDX_IN_DIO_CTRL_DATA, dio_ctrl_data->inp_comp_types[IR_BEAM_IDX_IN_DIO_CTRL_DATA].constraints.max_low_status_duration + current_time))
					return print_message(BUG_MSG ,"BMIExpController", "HandleRS232Buffers", "handle_dio_ctrl_rx_shm", "write_to_dio_ctrl_2_dio_ctrl_dur_hand_msg_buffer().");	
			}	
			if (! write_to_dio_ctrl_input_status_history(dio_ctrl_input_status_history, current_time, DIO_CTRL_INPUT_COMPONENT_IR_BEAM_NOSE_POKE, DIO_CTRL_COMP_STATUS_LOW))
				return print_message(BUG_MSG ,"BMIExpController", "HandleRS232Buffers", "handle_dio_ctrl_rx_shm", "write_to_dio_ctrl_input_status_history().");
		}
	}
	return TRUE;
}
