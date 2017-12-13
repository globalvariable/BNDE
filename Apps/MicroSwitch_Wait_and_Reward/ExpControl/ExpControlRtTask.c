#include "ExpControlRtTask.h"

static RtTasksData *static_rt_tasks_data = NULL;

static ExpStatus trial_status = TRIAL_STATUS_NULL;   // Only trial handler can change trial status. 

static ExpDurationStatus trial_duration_status = TRIAL_DUR_STATUS_NULL;   // Only trial duration handler can change trial status. 
static TimeStamp handling_end_time = 0;

static ExpCtrlParadigmRobotReach *static_paradigm = NULL;

static ClassifiedExpHistory *classified_history = NULL;

static ExpStatusHistory *static_trial_status_history = NULL;

static Gui2ExpCtrlMsg *static_msgs_gui_2_exp_ctrl = NULL;  
static ExpCtrl2GuiMsg *static_msgs_exp_ctrl_2_gui = NULL;  

static DioCtrl2ExpCtrlMsg *msgs_dio_ctrl_2_exp_ctrl = NULL;
static ProstheticCtrl2ExpCtrlMsg *msgs_prosthetic_ctrl_2_exp_ctrl = NULL;

static ExpCtrl2DioCtrlMsg *msgs_exp_ctrl_2_dio_ctrl = NULL;
static ExpCtrl2ProstheticCtrlMsg *msgs_exp_ctrl_2_prosthetic_ctrl = NULL;

static ExpCtrlDur2ExpCtrlMsg *msgs_trial_dur_hand_2_exp_ctrl = NULL;    // Exp Handler only read it, cannot write
static ExpCtrl2ExpCtrlDurMsg *msgs_exp_ctrl_2_trial_dur_hand = NULL;     // Exp Handler can write here, cannot read it, trial duration handler will read it

static ExpCtrl2NeuralNetMsg *msgs_exp_ctrl_2_neural_net = NULL;
static NeuralNet2ExpCtrlMsg *msgs_neural_net_2_exp_ctrl = NULL;


static int exp_control_rt_thread = 0;
static bool rt_exp_control_stay_alive = 1;

static void *rt_exp_control(void *args);

static bool connect_to_dio_ctrl(void);
static bool connect_to_prosthetic_ctrl(void);
static bool connect_to_neural_net(void);



bool create_exp_control_rt_thread(RtTasksData *rt_tasks_data, Gui2ExpCtrlMsg *msgs_gui_2_exp_ctrl, ExpCtrlParadigmRobotReach *paradigm, ClassifiedExpHistory* classified_trial_history, ExpCtrl2GuiMsg *msgs_exp_ctrl_2_gui, ExpStatusHistory *trial_status_history)
{
	static_rt_tasks_data = rt_tasks_data;

	trial_status = TRIAL_STATUS_TRIALS_DISABLED;

	trial_duration_status = TRIAL_DUR_STATUS_HANDLING_DISABLED;

	static_paradigm = paradigm;

	classified_history = classified_trial_history;

	static_trial_status_history = trial_status_history;

	static_msgs_gui_2_exp_ctrl = msgs_gui_2_exp_ctrl;	
	static_msgs_exp_ctrl_2_gui = msgs_exp_ctrl_2_gui;	

	msgs_dio_ctrl_2_exp_ctrl = allocate_shm_server_dio_ctrl_2_exp_ctrl_msg_buffer(msgs_dio_ctrl_2_exp_ctrl);
	msgs_prosthetic_ctrl_2_exp_ctrl = allocate_shm_server_prosthetic_ctrl_2_exp_ctrl_msg_buffer(msgs_prosthetic_ctrl_2_exp_ctrl);
	msgs_neural_net_2_exp_ctrl = allocate_shm_server_neural_net_2_exp_ctrl_msg_buffer(msgs_neural_net_2_exp_ctrl);

/*	if (!connect_to_neural_net())
		return print_message(ERROR_MSG ,"ExpControl", "ExpControlRtTask", "create_exp_control_rt_thread", "connect_to_neural_net().");	
*/

	if (! connect_to_prosthetic_ctrl())		// connect to mov obj hand before exp envi so that mov obj hand initializes semaphore and shm shared with exp envi hand.
		return print_message(ERROR_MSG ,"ExpControl", "ExpControlRtTask", "create_exp_control_rt_thread", "connect_to_dio_ctrl().");	
	sleep(1);
	if (! connect_to_dio_ctrl())
		return print_message(ERROR_MSG ,"ExpControl", "ExpControlRtTask", "create_exp_control_rt_thread", "connect_to_dio_ctrl().");	


	msgs_trial_dur_hand_2_exp_ctrl = allocate_trial_dur_hand_2_exp_ctrl_msg_buffer(msgs_trial_dur_hand_2_exp_ctrl);
	msgs_exp_ctrl_2_trial_dur_hand = allocate_exp_ctrl_2_trial_dur_hand_msg_buffer(msgs_exp_ctrl_2_trial_dur_hand);

/*	if(! create_trial_duration_handler_rt_thread(rt_tasks_data, msgs_trial_dur_hand_2_exp_ctrl, msgs_exp_ctrl_2_trial_dur_hand))
		return print_message(ERROR_MSG ,"ExpControl", "ExpControlRtTask", "create_exp_control_rt_thread", "create_exp_control_rt_thread().");	
*/
	if (exp_control_rt_thread !=0)
		return print_message(BUG_MSG ,"ExpControl", "ExpControlRtTask", "create_exp_control_rt_thread", "CANNOT create rt_thread again.");	
	exp_control_rt_thread =  rt_thread_create(rt_exp_control, NULL, 10000);
	if (exp_control_rt_thread ==0)
		return print_message(BUG_MSG ,"ExpControl", "ExpControlRtTask", "create_exp_control_rt_thread", "Couldn' t create rt_thread.");	
	return TRUE;
}

bool kill_exp_control_rt_thread(void)
{
	return TRUE;
}

static void *rt_exp_control(void *args)
{
	RT_TASK *handler;
        RTIME period;
	RTIME prev_time, curr_time, execution_end;
	RTIME expected;
	RTIME exp_ctrl_time_ns;
	unsigned int timer_cpuid, task_cpuid;

	timer_cpuid = (SYSTIME_PERIODIC_CPU_ID*MAX_NUM_OF_CPU_THREADS_PER_CPU);
	task_cpuid = (EXP_CONTROL_CPU_ID*MAX_NUM_OF_CPU_THREADS_PER_CPU);

	if (! check_rt_task_specs_to_init(static_rt_tasks_data, EXP_CONTROL_CPU_ID, EXP_CONTROL_CPU_TASK_ID, EXP_CONTROL_PERIOD))  {
		print_message(ERROR_MSG ,"ExpControl", "ExpControlRtTask", "rt_exp_control", "! check_rt_task_specs_to_init()."); exit(1); }	
        if (! (handler = rt_task_init_schmod(EXP_CONTROL_TASK_NAME, EXP_CONTROL_TASK_PRIORITY, EXP_CONTROL_STACK_SIZE, EXP_CONTROL_MSG_SIZE,EXP_CONTROL_POLICY, 1 << task_cpuid))) {
		print_message(ERROR_MSG ,"ExpControl", "ExpControlRtTask", "rt_exp_control", "handler = rt_task_init_schmod()."); exit(1); }
	if (! write_rt_task_specs_to_rt_tasks_data(static_rt_tasks_data, EXP_CONTROL_CPU_ID, EXP_CONTROL_CPU_TASK_ID, EXP_CONTROL_PERIOD, "ExpControl"))  {
		print_message(ERROR_MSG ,"ExpControl", "ExpControlRtTask", "rt_exp_control", "! write_rt_task_specs_to_rt_tasks_data()."); exit(1); }	

	curr_time = rt_get_time_cpuid(task_cpuid);	
	exp_ctrl_time_ns = rt_get_time_ns_cpuid(timer_cpuid);	// use system time

        period = nano2count(EXP_CONTROL_PERIOD);
        rt_task_make_periodic(handler, curr_time + period, period);

	prev_time = curr_time ;
	expected = curr_time + period;


        mlockall(MCL_CURRENT | MCL_FUTURE);
	rt_make_hard_real_time();		// do not forget this // check the task by nano /proc/rtai/scheduler (HD/SF) 

	initialize_gui_to_exp_control_msg_params(&trial_status, static_msgs_gui_2_exp_ctrl, msgs_exp_ctrl_2_trial_dur_hand, msgs_exp_ctrl_2_dio_ctrl, msgs_exp_ctrl_2_prosthetic_ctrl, msgs_exp_ctrl_2_neural_net, static_paradigm, classified_history, static_msgs_exp_ctrl_2_gui, static_trial_status_history);
	initialize_trial_dur_handler_to_exp_control_msg_params(&trial_status, msgs_trial_dur_hand_2_exp_ctrl, msgs_exp_ctrl_2_trial_dur_hand, msgs_exp_ctrl_2_dio_ctrl, msgs_exp_ctrl_2_prosthetic_ctrl, msgs_exp_ctrl_2_neural_net, classified_history, static_paradigm, static_msgs_exp_ctrl_2_gui, static_trial_status_history);
	initialize_dio_control_to_exp_control_msg_params(&trial_status, msgs_dio_ctrl_2_exp_ctrl, msgs_exp_ctrl_2_trial_dur_hand, msgs_exp_ctrl_2_dio_ctrl, msgs_exp_ctrl_2_prosthetic_ctrl, msgs_exp_ctrl_2_neural_net, static_paradigm, classified_history, static_msgs_exp_ctrl_2_gui, static_trial_status_history);
	initialize_prosthetic_control_to_exp_control_msg_params(&trial_status, msgs_prosthetic_ctrl_2_exp_ctrl, msgs_exp_ctrl_2_trial_dur_hand, msgs_exp_ctrl_2_dio_ctrl, msgs_exp_ctrl_2_prosthetic_ctrl, msgs_exp_ctrl_2_neural_net, static_paradigm, classified_history, static_msgs_exp_ctrl_2_gui, static_trial_status_history);


	msgs_exp_ctrl_2_trial_dur_hand->buff_read_idx = msgs_exp_ctrl_2_trial_dur_hand->buff_write_idx; // to reset message buffer. previously written messages and reading of them now might lead to inconvenience.,
	msgs_trial_dur_hand_2_exp_ctrl->buff_read_idx = msgs_trial_dur_hand_2_exp_ctrl->buff_write_idx; // to reset message buffer. previously written messages and reading of them now might lead to inconvenience.,
	msgs_dio_ctrl_2_exp_ctrl->buff_read_idx = msgs_dio_ctrl_2_exp_ctrl->buff_write_idx; // to reset message buffer. previously written messages and reading of them now might lead to inconvenience.,
	msgs_prosthetic_ctrl_2_exp_ctrl->buff_read_idx = msgs_prosthetic_ctrl_2_exp_ctrl->buff_write_idx; // to reset message buffer. previously written messages and reading of them now might lead to inconvenience.,
	msgs_neural_net_2_exp_ctrl->buff_read_idx = msgs_neural_net_2_exp_ctrl->buff_write_idx; // to reset message buffer. previously written messages and reading of them now might lead to inconvenience.,

	static_msgs_gui_2_exp_ctrl->buff_read_idx = static_msgs_gui_2_exp_ctrl->buff_write_idx; // to reset message buffer. previously written messages and reading of them now might lead to inconvenience.,


        while (rt_exp_control_stay_alive) 
	{
        	rt_task_wait_period();

		curr_time = rt_get_time_cpuid(task_cpuid);	
		exp_ctrl_time_ns = rt_get_time_ns_cpuid(timer_cpuid);	// use system time

		expected += period;
		save_jitter(static_rt_tasks_data, EXP_CONTROL_CPU_ID, EXP_CONTROL_CPU_TASK_ID, prev_time, curr_time, period);
		prev_time = curr_time;

		// routines
		if (!handle_gui_to_exp_control_msg(exp_ctrl_time_ns)) {
			print_message(ERROR_MSG ,"ExpControl", "ExpControlRtTask", "rt_exp_control", "! handle_gui_to_exp_control_msg()."); break; }
		if (!handle_dio_control_to_exp_control_msg(exp_ctrl_time_ns))  {
			print_message(ERROR_MSG ,"ExpControl", "ExpControlRtTask", "rt_exp_control", "! handle_dio_control_to_exp_control_msg()."); break; }
		if (!handle_prosthetic_control_to_exp_control_msg(exp_ctrl_time_ns))  {
			print_message(ERROR_MSG ,"ExpControl", "ExpControlRtTask", "rt_exp_control", "! handle_prosthetic_control_to_exp_control_msg()."); break; }
		// handle_exp_control_to_trial_dur_handler  --> handle_exp_control_duration --> handle_trial_dur_handler_to_exp_control_msg is important  === so that messages from exp envi and mov obj handler have priority over trial  duratiion handler.  e.g. nose poke event from exp envi handler extends refractory period (BEFORE trial_dur_handler_to_exp_control makes trials available due to refractory timeout). 
		if (! handle_exp_control_to_trial_dur_handler_msg(&trial_duration_status, exp_ctrl_time_ns, msgs_exp_ctrl_2_trial_dur_hand, &handling_end_time)) {
			print_message(ERROR_MSG ,"BMIExpController", "ExpControlRtTask", "rt_trial_duration_handler", "! handle_exp_control_to_trial_duration_handler_msg()."); break; }
		if (! handle_exp_control_duration(&trial_duration_status, exp_ctrl_time_ns, handling_end_time, msgs_trial_dur_hand_2_exp_ctrl)) {
			print_message(ERROR_MSG ,"BMIExpController", "ExpControlRtTask", "rt_trial_duration_handler", "! handle_exp_control_to_trial_duration_handler_msg()."); break; }
		if (!handle_trial_dur_handler_to_exp_control_msg(exp_ctrl_time_ns))  {
			print_message(ERROR_MSG ,"ExpControl", "ExpControlRtTask", "rt_exp_control", "! handle_trial_dur_handler_to_exp_control_msg()."); break; }
		// routines	
		execution_end = rt_get_time_cpuid(timer_cpuid);
		save_run_time(static_rt_tasks_data, EXP_CONTROL_CPU_ID, EXP_CONTROL_CPU_TASK_ID, curr_time, execution_end);		
        }
	rt_make_soft_real_time();
        rt_task_delete(handler);
	print_message(INFO_MSG ,"ExpControl", "ExpControlRtTask", "rt_exp_control", "rt_task_delete().");	

        return 0; 
}


static bool connect_to_dio_ctrl(void)
{
	DioCtrl2ExpCtrlMsgItem msg_item;
	char str_dio_ctrl_2_exp_ctrl_msg[DIO_CTRL_2_EXP_CTRL_MSG_STRING_LENGTH];

	msgs_exp_ctrl_2_dio_ctrl = allocate_shm_client_exp_ctrl_2_dio_ctrl_msg_buffer(msgs_exp_ctrl_2_dio_ctrl);	
	if (msgs_exp_ctrl_2_dio_ctrl == NULL)
		return print_message(ERROR_MSG ,"ExpControl", "ExpControlRtTask", "connect_to_dio_ctrl", "msgs_exp_ctrl_2_dio_ctrl == NULL.");
	sleep(1);	
	if (!write_to_exp_ctrl_2_dio_ctrl_msg_buffer(msgs_exp_ctrl_2_dio_ctrl, static_rt_tasks_data->current_system_time, EXP_CTRL_2_DIO_CTRL_MSG_ARE_YOU_ALIVE, 0))
		return print_message(ERROR_MSG ,"ExpControl", "ExpControlRtTask", "connect_to_dio_ctrl", "write_to_exp_ctrl_2_dio_ctrl_msg_bufferr().");

	while(1)
	{
		while (get_next_dio_ctrl_2_exp_ctrl_msg_buffer_item(msgs_dio_ctrl_2_exp_ctrl, &msg_item))
		{
			get_dio_ctrl_2_exp_ctrl_msg_type_string(msg_item.msg_type, str_dio_ctrl_2_exp_ctrl_msg);
			print_message(INFO_MSG ,"ExpControl", "ExpControlRtTask", "connect_to_dio_ctrl", str_dio_ctrl_2_exp_ctrl_msg);	
			switch (msg_item.msg_type)
			{
				case DIO_CTRL_2_EXP_CTRL_MSG_I_AM_ALIVE:
					print_message(INFO_MSG ,"ExpControl", "ExpControlRtTask", "connect_to_dio_ctrl", "Connection to DIO_CONTROL is successful!!!");	
					sleep(1);	
					return TRUE;			
				default:
					print_message(BUG_MSG ,"ExpControl", "ExpControlRtTask", "connect_to_dio_ctrl", str_dio_ctrl_2_exp_ctrl_msg);	
					return (void*)print_message(BUG_MSG ,"ExpControl", "ExpControlRtTask", "connect_to_dio_ctrl", "default - switch.");
			}
		}
		sleep(1);
	}
	return print_message(BUG_MSG ,"ExpControl", "ExpControlRtTask", "connect_to_dio_ctrl", "Wrong hit in the code.");
}

static bool connect_to_prosthetic_ctrl(void)
{
	ProstheticCtrl2ExpCtrlMsgItem msg_item;
	char str_prosthetic_ctrl_2_exp_ctrl_msg[PROSTHETIC_CTRL_2_EXP_CTRL_MSG_STRING_LENGTH];
	ExpCtrl2ProstheticCtrlMsgAdditional exp_ctrl_2_prosthetic_ctrl_add;

	msgs_exp_ctrl_2_prosthetic_ctrl = allocate_shm_client_exp_ctrl_2_prosthetic_ctrl_msg_buffer(msgs_exp_ctrl_2_prosthetic_ctrl);	
	if (msgs_exp_ctrl_2_prosthetic_ctrl == NULL)
		return print_message(ERROR_MSG ,"ExpControl", "ExpControlRtTask", "connect_to_prosthetic_ctrl", "msgs_exp_ctrl_2_prosthetic_ctrl == NULL.");
	sleep(1);	

	exp_ctrl_2_prosthetic_ctrl_add.dummy = 0;
	if (!write_to_exp_ctrl_2_prosthetic_ctrl_msg_buffer(msgs_exp_ctrl_2_prosthetic_ctrl, static_rt_tasks_data->current_system_time, EXP_CTRL_2_PROSTHETIC_CTRL_MSG_ARE_YOU_ALIVE, exp_ctrl_2_prosthetic_ctrl_add))
		return print_message(ERROR_MSG ,"ExpControl", "ExpControlRtTask", "connect_to_prosthetic_ctrl", "write_to_exp_ctrl_2_prosthetic_ctrl_msg_bufferr().");

	while(1)
	{
		while (get_next_prosthetic_ctrl_2_exp_ctrl_msg_buffer_item(msgs_prosthetic_ctrl_2_exp_ctrl, &msg_item))
		{
			get_prosthetic_ctrl_2_exp_ctrl_msg_type_string(msg_item.msg_type, str_prosthetic_ctrl_2_exp_ctrl_msg);
			print_message(INFO_MSG ,"ExpControl", "ExpControlRtTask", "connect_to_prosthetic_ctrl", str_prosthetic_ctrl_2_exp_ctrl_msg);	
			switch (msg_item.msg_type)
			{
				case PROSTHETIC_CTRL_2_EXP_CTRL_MSG_I_AM_ALIVE:
					print_message(INFO_MSG ,"ExpControl", "ExpControlRtTask", "connect_to_prosthetic_ctrl", "Connection to PROSTHETIC_CONTROL is successful!!!");
					sleep(1);		
					return TRUE;			
				default:
					print_message(BUG_MSG ,"ExpControl", "ExpControlRtTask", "connect_to_prosthetic_ctrl", str_prosthetic_ctrl_2_exp_ctrl_msg);	
					return (void*)print_message(BUG_MSG ,"ExpControl", "ExpControlRtTask", "connect_to_prosthetic_ctrl", "default - switch.");
			}
		}
		sleep(1);
	}
	return print_message(BUG_MSG ,"ExpControl", "ExpControlRtTask", "connect_to_prosthetic_ctrl", "Wrong hit in the code.");
}

static bool connect_to_neural_net(void)
{
	NeuralNet2ExpCtrlMsgItem msg_item;
	char str_neural_net_2_exp_ctrl_msg[NEURAL_NET_2_EXP_CTRL_MSG_STRING_LENGTH];
	ExpCtrl2NeuralNetMsgAdditional exp_ctrl_to_neural_net_msg_add;
	msgs_exp_ctrl_2_neural_net = allocate_shm_client_exp_ctrl_2_neural_net_msg_buffer(msgs_exp_ctrl_2_neural_net);
	if (msgs_exp_ctrl_2_neural_net == NULL)
		return print_message(ERROR_MSG ,"ExpControl", "ExpControlRtTask", "connect_to_neural_net", "msgs_exp_ctrl_2_neural_net == NULL.");
	exp_ctrl_to_neural_net_msg_add.dummy = 0;
	if (!write_to_exp_ctrl_2_neural_net_msg_buffer(msgs_exp_ctrl_2_neural_net, static_rt_tasks_data->current_system_time, EXP_CTRL_2_NEURAL_NET_MSG_ARE_YOU_ALIVE, exp_ctrl_to_neural_net_msg_add))
		return print_message(ERROR_MSG ,"ExpControl", "ExpControlRtTask", "connect_to_neural_net", "write_to_exp_ctrl_2_neural_net_msg_buffer().");

	while (1) 
	{ 
		while (get_next_neural_net_2_exp_ctrl_msg_buffer_item(msgs_neural_net_2_exp_ctrl, &msg_item))
		{
			get_neural_net_2_exp_ctrl_msg_type_string(msg_item.msg_type, str_neural_net_2_exp_ctrl_msg);
			print_message(INFO_MSG ,"ExpControl", "ExpControlRtTask", "connect_to_neural_net", str_neural_net_2_exp_ctrl_msg);	
			switch (msg_item.msg_type)
			{
				case NEURAL_NET_2_EXP_CTRL_MSG_I_AM_ALIVE:
					print_message(INFO_MSG ,"ExpControl", "ExpControlRtTask", "connect_to_neural_net", "Connection to NEURAL_NET is successful!!!");
					exp_ctrl_to_neural_net_msg_add.dummy = 0;
					if (!write_to_exp_ctrl_2_neural_net_msg_buffer(msgs_exp_ctrl_2_neural_net, static_rt_tasks_data->current_system_time, EXP_CTRL_2_SPIKE_GEN_MSG_TRIAL_STATUS_CHANGED, exp_ctrl_to_neural_net_msg_add))
						return print_message(ERROR_MSG ,"ExpControl", "ExpControlRtTask", "connect_to_neural_net", "write_to_exp_ctrl_2_neural_net_msg_buffer().");	
					return TRUE;			
				default:
					return print_message(BUG_MSG ,"ExpControl", "ExpControlRtTask", "connect_to_neural_net", str_neural_net_2_exp_ctrl_msg);	
			}
		}
		sleep(1); 
	}
	return print_message(BUG_MSG ,"ExpControl", "ProstheticControlRtTask", "connect_to_neural_net", "Wrong hit in the code.");
}


