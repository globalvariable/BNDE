#include "ProstheticControlRtTask.h"

static RtTasksData *static_rt_tasks_data = NULL;

static ProstheticCtrlStatus prosthetic_ctrl_status = PROSTHETIC_CTRL_STATUS_DISABLED;   // Only prosthetic_ctrl handler can change status. 

static int prosthetic_control_rt_thread = 0;
static bool rt_prosthetic_control_stay_alive = 1;

static void *rt_prosthetic_control(void *args);

static ThreeDofRobot *static_robot_arm = NULL;
static ProstheticCtrlParadigmRobotReach *static_prosthetic_ctrl_paradigm = NULL;

static Gui2ProstheticCtrlMsg *static_msgs_gui_2_prosthetic_ctrl = NULL;
static ProstheticCtrl2GuiMsg *static_msgs_prosthetic_ctrl_2_gui = NULL;

static ExpCtrl2ProstheticCtrlMsg *msgs_exp_ctrl_2_prosthetic_ctrl = NULL;
static ProstheticCtrl2ExpCtrlMsg *msgs_prosthetic_ctrl_2_exp_ctrl = NULL;

static ProstheticCtrlDurHand2ProstheticCtrlMsg *msgs_prosthetic_ctrl_dur_hand_2_prosthetic_ctrl = NULL;
static ProstheticCtrl2ProstheticCtrlDurHandMsg *msgs_prosthetic_ctrl_2_prosthetic_ctrl_dur_hand = NULL;   

static ProstheticCtrl2NeuralNetMsg **msgs_prosthetic_ctrl_2_neural_net_multi_thread = NULL;
static NeuralNet2ProstheticCtrlMsg **msgs_neural_net_2_prosthetic_ctrl_multi_thread = NULL;

static ProstheticCtrlStatusHistory* static_prosthetic_ctrl_status_history = NULL;
static ThreeDofRobotAngleHistory *static_robot_angle_history = NULL;
static ThreeDofRobotPulseHistory *static_robot_pulse_history = NULL;

static MessageLogBuffer *static_message_log = NULL;

static SpikeData *scheduled_spike_data = NULL;

static bool connect_to_exp_ctrl(void);
static bool connect_to_neural_net(void);

/*
static bool connect_to_prosthetic_ctrl_interf(void );
*/


bool create_prosthetic_control_rt_thread(RtTasksData *rt_tasks_data, ThreeDofRobot *robot_arm, Gui2ProstheticCtrlMsg *msgs_gui_2_prosthetic_ctrl, ProstheticCtrl2GuiMsg *msgs_prosthetic_ctrl_2_gui, ProstheticCtrlParadigmRobotReach *prosthetic_ctrl_paradigm, MessageLogBuffer *message_log, ProstheticCtrlStatusHistory* prosthetic_ctrl_status_history, ThreeDofRobotAngleHistory *robot_angle_history, ThreeDofRobotPulseHistory *robot_pulse_history)
{
	static_rt_tasks_data = rt_tasks_data;

	static_robot_arm = robot_arm;
	static_prosthetic_ctrl_paradigm = prosthetic_ctrl_paradigm;

	static_msgs_gui_2_prosthetic_ctrl = msgs_gui_2_prosthetic_ctrl;
	static_msgs_prosthetic_ctrl_2_gui = msgs_prosthetic_ctrl_2_gui;

	static_prosthetic_ctrl_status_history = prosthetic_ctrl_status_history;
	static_robot_angle_history = robot_angle_history;
	static_robot_pulse_history = robot_pulse_history;

	static_message_log = message_log;

	msgs_exp_ctrl_2_prosthetic_ctrl = allocate_shm_server_exp_ctrl_2_prosthetic_ctrl_msg_buffer(msgs_exp_ctrl_2_prosthetic_ctrl);
	msgs_neural_net_2_prosthetic_ctrl_multi_thread = allocate_shm_server_neural_net_2_prosthetic_ctrl_multi_thread_msg_buffer(msgs_neural_net_2_prosthetic_ctrl_multi_thread, SNN_SIM_NUM_OF_DEDICATED_CPUS);
	msgs_prosthetic_ctrl_2_neural_net_multi_thread = g_new0(ProstheticCtrl2NeuralNetMsg*, SNN_SIM_NUM_OF_DEDICATED_CPUS); 

	init_prosthetic_ctrl_duration_handler();

	if (!connect_to_neural_net())
		return print_message(ERROR_MSG ,"ProstheticControl", "ProstheticControlRtTask", "create_prosthetic_control_rt_thread", "connect_to_neural_net().");	

	if (! connect_to_exp_ctrl())
		return print_message(ERROR_MSG ,"ProstheticControl", "ProstheticControlRtTask", "create_prosthetic_control_rt_thread", "connect_to_exp_ctrl().");	

	msgs_prosthetic_ctrl_dur_hand_2_prosthetic_ctrl = allocate_prosthetic_ctrl_dur_hand_2_prosthetic_ctrl_msg_buffer(msgs_prosthetic_ctrl_dur_hand_2_prosthetic_ctrl);
	msgs_prosthetic_ctrl_2_prosthetic_ctrl_dur_hand = allocate_prosthetic_ctrl_2_prosthetic_ctrl_dur_hand_msg_buffer(msgs_prosthetic_ctrl_2_prosthetic_ctrl_dur_hand);

	scheduled_spike_data = allocate_spike_data(scheduled_spike_data, NEURAL_NET_2_PROSTHETIC_CTRL_MSG_BUFF_SIZE);

	if (prosthetic_control_rt_thread !=0)
		return print_message(BUG_MSG ,"ProstheticControl", "ProstheticControlRtTask", "create_prosthetic_control_rt_thread", "CANNOT create rt_thread again.");	
	prosthetic_control_rt_thread =  rt_thread_create(rt_prosthetic_control, NULL, 10000);
	if (prosthetic_control_rt_thread ==0)
		return print_message(BUG_MSG ,"ProstheticControl", "ProstheticControlRtTask", "create_prosthetic_control_rt_thread", "Couldn' t create rt_thread.");	
	return TRUE;
}

bool kill_prosthetic_control_rt_thread(void)
{
	return TRUE;
}

static void *rt_prosthetic_control(void *args)
{
	RT_TASK *handler;
        RTIME period;
	RTIME prev_time, curr_time, execution_end;
	RTIME expected;
	unsigned int i, timer_cpuid, task_cpuid;
	RTIME prosthetic_ctrl_time_ns;
	ProstheticCtrl2ProstheticCtrlDurHandMsgAdditional prosthetic_ctrl_2_prosthetic_ctrl_dur_hand_additional_data;



	SEM *dio_ctrl_rx_buff_sem = NULL;
	SEM *dio_ctrl_tx_buff_sem = NULL;
	DioCtrlRxShm *dio_ctrl_rx_buff_shm = NULL;
	DioCtrlTxShm *dio_ctrl_tx_buff_shm = NULL;

	timer_cpuid = (SYSTIME_PERIODIC_CPU_ID*MAX_NUM_OF_CPU_THREADS_PER_CPU);
	task_cpuid = (PROSTHETIC_CONTROL_CPU_ID*MAX_NUM_OF_CPU_THREADS_PER_CPU);

	if (! check_rt_task_specs_to_init(static_rt_tasks_data, PROSTHETIC_CONTROL_CPU_ID, PROSTHETIC_CONTROL_CPU_TASK_ID, PROSTHETIC_CONTROL_PERIOD))  {
		print_message(ERROR_MSG ,"ProstheticControl", "ProstheticControlRtTask", "rt_prosthetic_control", "! check_rt_task_specs_to_init()."); exit(1); }	
        if (! (handler = rt_task_init_schmod(PROSTHETIC_CONTROL_TASK_NAME, PROSTHETIC_CONTROL_TASK_PRIORITY, PROSTHETIC_CONTROL_STACK_SIZE, PROSTHETIC_CONTROL_MSG_SIZE,PROSTHETIC_CONTROL_POLICY, 1 << task_cpuid))) {
		print_message(ERROR_MSG ,"ProstheticControl", "ProstheticControlRtTask", "rt_prosthetic_control", "handler = rt_task_init_schmod()."); exit(1); }
	if (! write_rt_task_specs_to_rt_tasks_data(static_rt_tasks_data, PROSTHETIC_CONTROL_CPU_ID, PROSTHETIC_CONTROL_CPU_TASK_ID, PROSTHETIC_CONTROL_PERIOD, "ProstheticControl"))  {
		print_message(ERROR_MSG ,"ProstheticControl", "ProstheticControlRtTask", "rt_prosthetic_control", "! write_rt_task_specs_to_rt_tasks_data()."); exit(1); }	

	curr_time = rt_get_time_cpuid(task_cpuid);	
	prosthetic_ctrl_time_ns = rt_get_time_ns_cpuid(timer_cpuid);	// use system time

        period = nano2count(PROSTHETIC_CONTROL_PERIOD);
        rt_task_make_periodic(handler, curr_time + period, period);

	prev_time = curr_time;
	expected = curr_time + period;

	// Initialization of semaphores should be done after initializing the rt task !!!!
	if (! init_rs232_buffers(static_robot_arm, &dio_ctrl_rx_buff_sem, &dio_ctrl_tx_buff_sem, &dio_ctrl_rx_buff_shm, &dio_ctrl_tx_buff_shm,  prosthetic_ctrl_time_ns))  {
		print_message(ERROR_MSG ,"ProstheticControl", "ProstheticControlRtTask", "rt_prosthetic_control", "! init_rs232_buffers()."); exit(1); }	

        mlockall(MCL_CURRENT | MCL_FUTURE);
	rt_make_hard_real_time();		// do not forget this // check the task by nano /proc/rtai/scheduler (HD/SF) 

	msgs_exp_ctrl_2_prosthetic_ctrl->buff_read_idx = msgs_exp_ctrl_2_prosthetic_ctrl->buff_write_idx; // to reset message buffer. previously written messages and reading of them now might lead to inconvenience.,
	msgs_prosthetic_ctrl_dur_hand_2_prosthetic_ctrl->buff_read_idx = msgs_prosthetic_ctrl_dur_hand_2_prosthetic_ctrl->buff_write_idx; // to reset message buffer. previously written messages and reading of them now might lead to inconvenience.,
	msgs_prosthetic_ctrl_2_prosthetic_ctrl_dur_hand->buff_read_idx = msgs_prosthetic_ctrl_2_prosthetic_ctrl_dur_hand->buff_write_idx; // to reset message buffer. previously written messages and reading of them now might lead to inconvenience.,
	static_msgs_gui_2_prosthetic_ctrl->buff_read_idx = static_msgs_gui_2_prosthetic_ctrl->buff_write_idx;
	static_msgs_prosthetic_ctrl_2_gui->buff_read_idx = static_msgs_prosthetic_ctrl_2_gui->buff_write_idx;
	for (i = 0; i < SNN_SIM_NUM_OF_DEDICATED_CPUS; i++)
	{
		(msgs_neural_net_2_prosthetic_ctrl_multi_thread[i])->buff_read_idx = (msgs_neural_net_2_prosthetic_ctrl_multi_thread[i])->buff_write_idx; // to reset message buffer. previously written messages and reading of them now might lead to inconvenience.,
	}

	prosthetic_ctrl_2_prosthetic_ctrl_dur_hand_additional_data.schedule.schedule = prosthetic_ctrl_time_ns;  // send this command now
	prosthetic_ctrl_2_prosthetic_ctrl_dur_hand_additional_data.schedule.item_idx = PROSTHETIC_CTRL_DUR_STATUS_ITEM_SEND_AD_CONVERSION;
	if (! write_to_prosthetic_ctrl_2_prosthetic_ctrl_dur_hand_msg_buffer(msgs_prosthetic_ctrl_2_prosthetic_ctrl_dur_hand, prosthetic_ctrl_time_ns,  PROSTHETIC_CTRL_2_PROSTHETIC_CTRL_DUR_HAND_MSG_SET_SCHEDULE, prosthetic_ctrl_2_prosthetic_ctrl_dur_hand_additional_data)) {
		print_message(BUG_MSG ,"ProstheticControl", "ProstheticControlRtTask", "rt_prosthetic_control", "write_to_prosthetic_ctrl_2_prosthetic_ctrl_dur_hand_msg_buffer()."); exit(1); }	

        while (rt_prosthetic_control_stay_alive) 
	{
        	rt_task_wait_period();

		curr_time = rt_get_time_cpuid(task_cpuid);	
		prosthetic_ctrl_time_ns = rt_get_time_ns_cpuid(timer_cpuid);	// use system time

		expected += period;
		save_jitter(static_rt_tasks_data, PROSTHETIC_CONTROL_CPU_ID, PROSTHETIC_CONTROL_CPU_TASK_ID, prev_time, curr_time, period);
		prev_time = curr_time;
		// routines
		if (! handle_gui_to_prosthetic_control_msg(static_robot_arm, &prosthetic_ctrl_status, prosthetic_ctrl_time_ns, static_msgs_gui_2_prosthetic_ctrl)) {
			print_message(ERROR_MSG ,"ProstheticControl", "ProstheticControlRtTask", "rt_prosthetic_control", "! handle_gui_to_prosthetic_control_msg()."); break; }
		if (! handle_exp_control_to_prosthetic_control_msg(static_robot_arm, &prosthetic_ctrl_status, prosthetic_ctrl_time_ns, msgs_exp_ctrl_2_prosthetic_ctrl, msgs_prosthetic_ctrl_2_prosthetic_ctrl_dur_hand, msgs_prosthetic_ctrl_2_exp_ctrl, static_prosthetic_ctrl_paradigm, static_message_log, static_prosthetic_ctrl_status_history, static_msgs_prosthetic_ctrl_2_gui, msgs_prosthetic_ctrl_2_neural_net_multi_thread))  {
			print_message(ERROR_MSG ,"ProstheticControl", "ProstheticControlRtTask", "rt_prosthetic_control", "! handle_exp_control_to_prosthetic_control_msg()."); break; }
		if (! handle_prosthetic_control_to_prosthetic_ctrl_dur_handler_msg(prosthetic_ctrl_time_ns, msgs_prosthetic_ctrl_2_prosthetic_ctrl_dur_hand)) {
			print_message(ERROR_MSG ,"ProstheticControl", "ProstheticCtrlDurationHandlerRtTask", "rt_prosthetic_ctrl_duration_handler", "! handle_prosthetic_control_to_prosthetic_ctrl_duration_handler_msg()."); break; }
		if (! handle_prosthetic_control_duration(prosthetic_ctrl_time_ns, msgs_prosthetic_ctrl_dur_hand_2_prosthetic_ctrl))  {
			print_message(ERROR_MSG ,"ProstheticControl", "ProstheticCtrlDurationHandlerRtTask", "rt_prosthetic_ctrl_duration_handler", "! handle_prosthetic_control_duration()."); break; }
		if (! handle_prosthetic_ctrl_dur_handler_to_prosthetic_control_msg(static_robot_arm, prosthetic_ctrl_time_ns, &prosthetic_ctrl_status, msgs_prosthetic_ctrl_dur_hand_2_prosthetic_ctrl, msgs_prosthetic_ctrl_2_exp_ctrl, msgs_prosthetic_ctrl_2_prosthetic_ctrl_dur_hand, msgs_prosthetic_ctrl_2_neural_net_multi_thread, scheduled_spike_data, static_message_log, static_prosthetic_ctrl_paradigm, static_robot_pulse_history, static_robot_angle_history, static_prosthetic_ctrl_status_history))  {
			print_message(ERROR_MSG ,"ProstheticControl", "ProstheticControlRtTask", "rt_prosthetic_control", "! handle_prosthetic_ctrl_dur_handler_to_prosthetic_control_msg()."); break; }
		// first handle duration status and robot position which determine prosthetic_ctrl_status. Later on hanle spike outputs of neural net.  it changes the target pulse width value to reset the position to target led during reseting status. 
		if (! handle_neural_net_to_prosthetic_control_msg(static_robot_arm, prosthetic_ctrl_time_ns, msgs_neural_net_2_prosthetic_ctrl_multi_thread, scheduled_spike_data))  {
			print_message(ERROR_MSG ,"ProstheticControl", "ProstheticControlRtTask", "rt_prosthetic_control", "! handle_neural_net_to_prosthetic_control_msg()."); break; }
		if (! handle_spike_data_buff(prosthetic_ctrl_status, prosthetic_ctrl_time_ns, scheduled_spike_data, static_robot_arm, static_prosthetic_ctrl_paradigm))  {
			print_message(ERROR_MSG ,"ProstheticControl", "ProstheticControlRtTask", "rt_prosthetic_control", "! handle_spike_data_buff()."); break; }
		// routines	
		execution_end = rt_get_time_cpuid(timer_cpuid);
		save_run_time(static_rt_tasks_data, PROSTHETIC_CONTROL_CPU_ID, PROSTHETIC_CONTROL_CPU_TASK_ID, curr_time, execution_end);		
        }
	rt_make_soft_real_time();
        rt_task_delete(handler);
	print_message(INFO_MSG ,"ProstheticControl", "ProstheticControlRtTask", "rt_prosthetic_control", "rt_task_delete().");	

        return 0; 
}

static bool connect_to_exp_ctrl(void )
{
	ExpCtrl2ProstheticCtrlMsgItem msg_item;
	char str_exp_ctrl_2_prosthetic_ctrl_msg[EXP_CTRL_2_PROSTHETIC_CTRL_MSG_STRING_LENGTH];

	while (1) 
	{ 
		while (get_next_exp_ctrl_2_prosthetic_ctrl_msg_buffer_item(msgs_exp_ctrl_2_prosthetic_ctrl, &msg_item))
		{
			get_exp_ctrl_2_prosthetic_ctrl_msg_type_string(msg_item.msg_type, str_exp_ctrl_2_prosthetic_ctrl_msg);
			print_message(INFO_MSG ,"ProstheticControl", "ProstheticControlRtTask", "connect_to_exp_ctrl", str_exp_ctrl_2_prosthetic_ctrl_msg);	
			switch (msg_item.msg_type)
			{
				case EXP_CTRL_2_PROSTHETIC_CTRL_MSG_ARE_YOU_ALIVE:
					msgs_prosthetic_ctrl_2_exp_ctrl = allocate_shm_client_prosthetic_ctrl_2_exp_ctrl_msg_buffer(msgs_prosthetic_ctrl_2_exp_ctrl);
					sleep(1);
					if (msgs_prosthetic_ctrl_2_exp_ctrl == NULL)
						return print_message(ERROR_MSG ,"ProstheticControl", "ProstheticControlRtTask", "connect_to_exp_ctrl", "msgs_prosthetic_ctrl_2_exp_ctrl == NULL.");	
					if (!write_to_prosthetic_ctrl_2_exp_ctrl_msg_buffer(msgs_prosthetic_ctrl_2_exp_ctrl, static_rt_tasks_data->current_system_time, PROSTHETIC_CTRL_2_EXP_CTRL_MSG_I_AM_ALIVE, 0))
						return print_message(ERROR_MSG ,"ProstheticControl", "ProstheticControlRtTask", "connect_to_exp_ctrl", "write_to_prosthetic_ctrl_2_exp_ctrl_msg_buffer().");	
					print_message(INFO_MSG ,"ProstheticControl", "ProstheticControlRtTask", "connect_to_exp_ctrl", "Connection to EXP_CONTROL is successful!!!");	
					return TRUE;		
				default:
					return print_message(BUG_MSG ,"ProstheticControl", "ProstheticControlRtTask", "connect_to_exp_ctrl", str_exp_ctrl_2_prosthetic_ctrl_msg);	
			}
		}
		print_message(INFO_MSG ,"ProstheticControl", "ProstheticControlRtTask", "connect_to_exp_ctrl", "Waiting for EXP_CONTROL to connect.");	
		sleep(1);
	}
	return print_message(BUG_MSG ,"ProstheticControl", "ProstheticControlRtTask", "connect_to_exp_ctrl", "Wrong hit in the code.");
}

static bool connect_to_neural_net(void)
{
	NeuralNet2ProstheticCtrlMsgItem msg_item;
	char str_neural_net_2_prosthetic_ctrl_msg[NEURAL_NET_2_PROSTHETIC_CTRL_MSG_STRING_LENGTH];
	unsigned int i, num_of_alive_responses = 0;
	ProstheticCtrl2NeuralNetMsgAdditional	prosthetic_ctrl_2_neural_net_msg_add;
	for (i = 0; i <SNN_SIM_NUM_OF_DEDICATED_CPUS; i++)
	{
		msgs_prosthetic_ctrl_2_neural_net_multi_thread[i] = allocate_shm_client_prosthetic_ctrl_2_neural_net_multi_thread_msg_buffer_item(msgs_prosthetic_ctrl_2_neural_net_multi_thread, i, MIN_PROSTHETIC_CTRL_2_NEURAL_NET_EVENT_SCHEDULING_DELAY, MIN_PROSTHETIC_CTRL_2_NEURAL_NET_EVENT_SCHEDULING_DELAY);
		if (msgs_prosthetic_ctrl_2_neural_net_multi_thread[i] == NULL)
			return print_message(ERROR_MSG ,"ProstheticControl", "ProstheticControlRtTask", "connect_to_neural_net", "msgs_prosthetic_ctrl_2_neural_net == NULL.");
		prosthetic_ctrl_2_neural_net_msg_add.dummy = 0;
		if (!write_to_prosthetic_ctrl_2_neural_net_msg_buffer(msgs_prosthetic_ctrl_2_neural_net_multi_thread[i], static_rt_tasks_data->current_system_time, PROSTHETIC_CTRL_2_NEURAL_NET_MSG_ARE_YOU_ALIVE, prosthetic_ctrl_2_neural_net_msg_add))
			return print_message(ERROR_MSG ,"ProstheticControl", "ProstheticControlRtTask", "connect_to_neural_net", "write_to_prosthetic_ctrl_2_neural_net_msg_buffer().");
	}
	while (1) 
	{
		for (i = 0; i < SNN_SIM_NUM_OF_DEDICATED_CPUS; i++)
		{ 
			while (get_next_neural_net_2_prosthetic_ctrl_msg_buffer_item(msgs_neural_net_2_prosthetic_ctrl_multi_thread[i], &msg_item))
			{
				get_neural_net_2_prosthetic_ctrl_msg_type_string(msg_item.msg_type, str_neural_net_2_prosthetic_ctrl_msg);
				print_message(INFO_MSG ,"ProstheticControl", "ProstheticControlRtTask", "connect_to_neural_net", str_neural_net_2_prosthetic_ctrl_msg);	
				switch (msg_item.msg_type)
				{
					case NEURAL_NET_2_PROSTHETIC_CTRL_MSG_I_AM_ALIVE:
						print_message(INFO_MSG ,"ProstheticControl", "ProstheticControlRtTask", "connect_to_neural_net", "Connection to NEURAL_NET is successful!!!");	
						static_prosthetic_ctrl_paradigm->num_of_output_neurons = msg_item.neuron_num;
						num_of_alive_responses++;
						if (num_of_alive_responses == SNN_SIM_NUM_OF_DEDICATED_CPUS)
							goto SEND_JOINT_MIN_MAX;
						break;			
					default:
						return print_message(BUG_MSG ,"ProstheticControl", "ProstheticControlRtTask", "connect_to_neural_net", str_neural_net_2_prosthetic_ctrl_msg);	
				}
			}
		}
		sleep(1); 
	}
	SEND_JOINT_MIN_MAX: 
/*	prosthetic_ctrl_2_neural_net_msg_add.three_dof_robot_min_joint_angles[BASE_SERVO] = static_prosthetic_ctrl_paradigm->polar_space_limits[BASE_SERVO].min;
	prosthetic_ctrl_2_neural_net_msg_add.three_dof_robot_min_joint_angles[SHOULDER_SERVO] = static_prosthetic_ctrl_paradigm->polar_space_limits[SHOULDER_SERVO].min;
	prosthetic_ctrl_2_neural_net_msg_add.three_dof_robot_min_joint_angles[ELBOW_SERVO] = static_prosthetic_ctrl_paradigm->polar_space_limits[ELBOW_SERVO].min;
	if (!write_to_prosthetic_ctrl_2_neural_net_msg_buffer((*msgs_prosthetic_ctrl_2_neural_net_multi_thread)[0], *sys_time_ptr, PROSTHETIC_CTRL_2_NEURAL_NET_MSG_JOINT_ANGLE_MIN, prosthetic_ctrl_2_neural_net_msg_add))	
		return print_message(ERROR_MSG ,"ProstheticControl", "ProstheticControlRtTask", "connect_to_neural_net", "write_to_prosthetic_ctrl_2_neural_net_msg_buffer().");

	prosthetic_ctrl_2_neural_net_msg_add.three_dof_robot_max_joint_angles[BASE_SERVO] = static_prosthetic_ctrl_paradigm->polar_space_limits[BASE_SERVO].max;
	prosthetic_ctrl_2_neural_net_msg_add.three_dof_robot_max_joint_angles[SHOULDER_SERVO] = static_prosthetic_ctrl_paradigm->polar_space_limits[SHOULDER_SERVO].max;
	prosthetic_ctrl_2_neural_net_msg_add.three_dof_robot_max_joint_angles[ELBOW_SERVO] = static_prosthetic_ctrl_paradigm->polar_space_limits[ELBOW_SERVO].max;
	if (!write_to_prosthetic_ctrl_2_neural_net_msg_buffer((*msgs_prosthetic_ctrl_2_neural_net_multi_thread)[0], *sys_time_ptr, PROSTHETIC_CTRL_2_NEURAL_NET_MSG_JOINT_ANGLE_MAX, prosthetic_ctrl_2_neural_net_msg_add))	
		return print_message(ERROR_MSG ,"ProstheticControl", "ProstheticControlRtTask", "connect_to_neural_net", "write_to_prosthetic_ctrl_2_neural_net_msg_buffer().");
*/

	return print_message(INFO_MSG ,"ProstheticControl", "ProstheticControlRtTask", "connect_to_neural_net", "Successfull !!!.");
}
