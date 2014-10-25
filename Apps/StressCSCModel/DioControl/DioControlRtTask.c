#include "DioControlRtTask.h"

static RtTasksData *static_rt_tasks_data = NULL;

static int dio_control_rt_thread = 0;
static bool rt_dio_control_stay_alive = 1;

static void *rt_dio_control(void *args);

static DioCtrlData *static_dio_ctrl_data = NULL;

static Gui2DioCtrlMsg *static_msgs_gui_2_dio_ctrl = NULL;
static DioCtrl2GuiMsg *static_msgs_dio_ctrl_2_gui = NULL;  
/*
static DioCtrlInterf2DioCtrlMsg *msgs_dio_ctrl_interf_2_dio_ctrl = NULL;
static DioCtrl2DioCtrlInterfMsg *msgs_dio_ctrl_2_dio_ctrl_interf = NULL;
*/

static ExpCtrl2DioCtrlMsg *msgs_exp_ctrl_2_dio_ctrl = NULL;
static DioCtrl2ExpCtrlMsg *msgs_dio_ctrl_2_exp_ctrl = NULL;

static DioCtrlDurHand2DioCtrlMsg *msgs_dio_ctrl_dur_hand_2_dio_ctrl = NULL;
static DioCtrl2DioCtrlDurHandMsg *msgs_dio_ctrl_2_dio_ctrl_dur_hand = NULL;   

static DioCtrlInputStatusHistory *static_dio_ctrl_input_status_history = NULL;
static DioCtrlOutputStatusHistory *static_dio_ctrl_output_status_history = NULL;

static DioCtrlParadigmRobotReach *static_dio_ctrl_paradigm = NULL;

static bool connect_to_exp_ctrl(void);

bool create_dio_control_rt_thread(RtTasksData *rt_tasks_data, DioCtrlData *dio_ctrl_data, Gui2DioCtrlMsg *msgs_gui_2_dio_ctrl, DioCtrl2GuiMsg *msgs_dio_ctrl_2_gui, DioCtrlInputStatusHistory *dio_ctrl_input_status_history, DioCtrlOutputStatusHistory *dio_ctrl_output_status_history, DioCtrlParadigmRobotReach *dio_ctrl_paradigm)
{
	static_rt_tasks_data = rt_tasks_data;

	static_dio_ctrl_data = dio_ctrl_data;

	static_msgs_gui_2_dio_ctrl = msgs_gui_2_dio_ctrl;
	static_msgs_dio_ctrl_2_gui = msgs_dio_ctrl_2_gui;

	static_dio_ctrl_input_status_history = dio_ctrl_input_status_history;
	static_dio_ctrl_output_status_history = dio_ctrl_output_status_history;

	static_dio_ctrl_paradigm = dio_ctrl_paradigm;

	msgs_exp_ctrl_2_dio_ctrl = allocate_shm_server_exp_ctrl_2_dio_ctrl_msg_buffer(msgs_exp_ctrl_2_dio_ctrl);

	if (! connect_to_exp_ctrl())
		return print_message(ERROR_MSG ,"DioControl", "DioControlRtTask", "create_dio_control_rt_thread", "connect_to_exp_ctrl().");	


	msgs_dio_ctrl_dur_hand_2_dio_ctrl = allocate_dio_ctrl_dur_hand_2_dio_ctrl_msg_buffer(msgs_dio_ctrl_dur_hand_2_dio_ctrl);
	msgs_dio_ctrl_2_dio_ctrl_dur_hand = allocate_dio_ctrl_2_dio_ctrl_dur_hand_msg_buffer(msgs_dio_ctrl_2_dio_ctrl_dur_hand);

	if(! create_dio_ctrl_duration_handler_rt_thread(rt_tasks_data, msgs_dio_ctrl_dur_hand_2_dio_ctrl, msgs_dio_ctrl_2_dio_ctrl_dur_hand, dio_ctrl_data->num_of_inp_comps, dio_ctrl_data->num_of_outp_comps))
		return print_message(ERROR_MSG ,"DioControl", "DioControlRtTask", "create_dio_control_rt_thread", "create_dio_ctrl_duration_handler_rt_thread().");	

	if (dio_control_rt_thread !=0)
		return print_message(BUG_MSG ,"DioControl", "DioControlRtTask", "create_dio_control_rt_thread", "CANNOT create rt_thread again.");	
	dio_control_rt_thread =  rt_thread_create(rt_dio_control, NULL, 10000);
	if (dio_control_rt_thread ==0)
		return print_message(BUG_MSG ,"DioControl", "DioControlRtTask", "create_dio_control_rt_thread", "Couldn' t create rt_thread.");	
	return TRUE;
}

bool kill_dio_control_rt_thread(void)
{
	return TRUE;
}

static void *rt_dio_control(void *args)
{
	RT_TASK *handler;
        RTIME period;
	RTIME prev_time, curr_time, execution_end;
	RTIME expected;
	RTIME dio_ctrl_time_ns;
	unsigned int timer_cpuid, task_cpuid;

	unsigned int run_time_cntr = 0;

	timer_cpuid = (SYSTIME_PERIODIC_CPU_ID*MAX_NUM_OF_CPU_THREADS_PER_CPU)+SYSTIME_PERIODIC_CPU_THREAD_ID;
	task_cpuid = (DIO_CONTROL_CPU_ID*MAX_NUM_OF_CPU_THREADS_PER_CPU)+DIO_CONTROL_CPU_THREAD_ID;

	SEM *dio_ctrl_rx_buff_sem = NULL;
	SEM *dio_ctrl_tx_buff_sem = NULL;
	DioCtrlRxShm *dio_ctrl_rx_buff_shm = NULL;
	DioCtrlTxShm *dio_ctrl_tx_buff_shm = NULL;

	if (! check_rt_task_specs_to_init(static_rt_tasks_data, DIO_CONTROL_CPU_ID, DIO_CONTROL_CPU_THREAD_ID, DIO_CONTROL_CPU_THREAD_TASK_ID, DIO_CONTROL_PERIOD, FALSE))  {
		print_message(ERROR_MSG ,"DioControl", "DioControlRtTask", "rt_dio_control", "! check_rt_task_specs_to_init()."); exit(1); }	
        if (! (handler = rt_task_init_schmod(DIO_CONTROL_TASK_NAME, DIO_CONTROL_TASK_PRIORITY, DIO_CONTROL_STACK_SIZE, DIO_CONTROL_MSG_SIZE,DIO_CONTROL_POLICY, 1 << task_cpuid))) {
		print_message(ERROR_MSG ,"DioControl", "DioControlRtTask", "rt_dio_control", "handler = rt_task_init_schmod()."); exit(1); }
	if (! write_rt_task_specs_to_rt_tasks_data(static_rt_tasks_data, DIO_CONTROL_CPU_ID, DIO_CONTROL_CPU_THREAD_ID, DIO_CONTROL_CPU_THREAD_TASK_ID, DIO_CONTROL_PERIOD, DIO_CONTROL_POSITIVE_JITTER_THRES, DIO_CONTROL_NEGATIVE_JITTER_THRES, DIO_CONTROL_RUN_TIME_THRES, "DioControl", FALSE))  {
		print_message(ERROR_MSG ,"DioControl", "DioControlRtTask", "rt_dio_control", "! write_rt_task_specs_to_rt_tasks_data()."); exit(1); }	

	// Initialization of semaphores should be done after initializing the rt task !!!!
	if (! init_rs232_buffers(&dio_ctrl_rx_buff_sem, &dio_ctrl_tx_buff_sem, &dio_ctrl_rx_buff_shm, &dio_ctrl_tx_buff_shm ))  {
		print_message(ERROR_MSG ,"DioControl", "DioControlRtTask", "rt_dio_control", "! init_rs232_buffers()."); exit(1); }	

	curr_time = rt_get_time_cpuid(task_cpuid);	
	dio_ctrl_time_ns = rt_get_time_ns_cpuid(timer_cpuid);	// use system time

        period = nano2count(DIO_CONTROL_PERIOD);
        rt_task_make_periodic(handler, curr_time + period, period);

	prev_time = curr_time ;
	expected = curr_time + period;

        mlockall(MCL_CURRENT | MCL_FUTURE);
	rt_make_hard_real_time();		// do not forget this // check the task by nano /proc/rtai/scheduler (HD/SF) 

	msgs_exp_ctrl_2_dio_ctrl->buff_read_idx = msgs_exp_ctrl_2_dio_ctrl->buff_write_idx; // to reset message buffer. previously written messages and reading of them now might lead to inconvenience.,

	msgs_dio_ctrl_dur_hand_2_dio_ctrl->buff_read_idx = msgs_dio_ctrl_dur_hand_2_dio_ctrl->buff_write_idx; // to reset message buffer. previously written messages and reading of them now might lead to inconvenience.,
	static_msgs_gui_2_dio_ctrl->buff_read_idx = static_msgs_gui_2_dio_ctrl->buff_write_idx;

        while (rt_dio_control_stay_alive) 
	{
        	rt_task_wait_period();

		curr_time = rt_get_time_cpuid(task_cpuid);	
		dio_ctrl_time_ns = rt_get_time_ns_cpuid(timer_cpuid);	// use system time

		expected += period;
		evaluate_and_save_jitter(static_rt_tasks_data, DIO_CONTROL_CPU_ID, DIO_CONTROL_CPU_THREAD_ID, DIO_CONTROL_CPU_THREAD_TASK_ID, curr_time, expected);
		prev_time = curr_time;

		// routines
		if (! handle_gui_to_dio_control_msg(static_dio_ctrl_data, dio_ctrl_time_ns, static_msgs_gui_2_dio_ctrl)) {
			print_message(ERROR_MSG ,"DioControl", "DioControlRtTask", "rt_dio_control", "! handle_gui_to_dio_control_msg()."); break; }
		if (! handle_exp_control_to_dio_control_msg(static_dio_ctrl_data, dio_ctrl_time_ns, msgs_exp_ctrl_2_dio_ctrl,  msgs_dio_ctrl_2_dio_ctrl_dur_hand, static_dio_ctrl_paradigm, static_msgs_dio_ctrl_2_gui))  {
			print_message(ERROR_MSG ,"DioControl", "DioControlRtTask", "rt_dio_control", "! handle_exp_control_to_dio_control_msg()."); break; }
		if (! handle_dio_ctrl_rx_shm(static_dio_ctrl_data, dio_ctrl_time_ns, msgs_dio_ctrl_2_dio_ctrl_dur_hand, msgs_dio_ctrl_2_exp_ctrl, static_dio_ctrl_input_status_history)) {
			print_message(ERROR_MSG ,"DioControl", "DioControlRtTask", "rt_dio_control", "! handle_dio_ctrl_rx_shm()."); break; }
		if (! handle_dio_ctrl_dur_handler_to_dio_control_msg(static_dio_ctrl_data, dio_ctrl_time_ns, msgs_dio_ctrl_dur_hand_2_dio_ctrl, msgs_dio_ctrl_2_exp_ctrl, static_dio_ctrl_paradigm))  {
			print_message(ERROR_MSG ,"DioControl", "DioControlRtTask", "rt_dio_control", "! handle_dio_ctrl_dur_handler_to_dio_control_msg()."); break; }
		if (! handle_dio_ctrl_tx_shm(static_dio_ctrl_data, dio_ctrl_time_ns, static_dio_ctrl_output_status_history)) {
			print_message(ERROR_MSG ,"DioControl", "DioControlRtTask", "rt_dio_control", "! handle_dio_ctrl_tx_shm()."); break; }
		// routines	
		execution_end = rt_get_time_cpuid(timer_cpuid);
		evaluate_and_save_period_run_time(static_rt_tasks_data, DIO_CONTROL_CPU_ID, DIO_CONTROL_CPU_THREAD_ID, DIO_CONTROL_CPU_THREAD_TASK_ID, curr_time, execution_end);		
		run_time_cntr++;
		if (run_time_cntr == NUM_OF_TASK_EXECUTIONS_4_PERFOMANCE_EVAL)
		{
			run_time_cntr = 0;
			write_run_time_to_averaging_buffer(static_rt_tasks_data, DIO_CONTROL_CPU_ID, DIO_CONTROL_CPU_THREAD_ID, DIO_CONTROL_CPU_THREAD_TASK_ID, curr_time, execution_end);	
		}
        }
	rt_make_soft_real_time();
        rt_task_delete(handler);
	print_message(INFO_MSG ,"DioControl", "DioControlRtTask", "rt_dio_control", "rt_task_delete().");	

        return 0; 
}

static bool connect_to_exp_ctrl(void )
{
	ExpCtrl2DioCtrlMsgItem msg_item;
	char str_exp_ctrl_2_dio_ctrl_msg[EXP_CTRL_2_DIO_CTRL_MSG_STRING_LENGTH];

	while (1) 
	{ 
		while (get_next_exp_ctrl_2_dio_ctrl_msg_buffer_item(msgs_exp_ctrl_2_dio_ctrl, &msg_item))
		{
			get_exp_ctrl_2_dio_ctrl_msg_type_string(msg_item.msg_type, str_exp_ctrl_2_dio_ctrl_msg);
			print_message(INFO_MSG ,"DioControl", "DioControlRtTask", "connect_to_exp_ctrl", str_exp_ctrl_2_dio_ctrl_msg);	
			switch (msg_item.msg_type)
			{
				case EXP_CTRL_2_DIO_CTRL_MSG_ARE_YOU_ALIVE:
					msgs_dio_ctrl_2_exp_ctrl = allocate_shm_client_dio_ctrl_2_exp_ctrl_msg_buffer(msgs_dio_ctrl_2_exp_ctrl);
					usleep(1000);
					if (msgs_dio_ctrl_2_exp_ctrl == NULL)
						return print_message(ERROR_MSG ,"DioControl", "DioControlRtTask", "connect_to_exp_ctrl", "msgs_dio_ctrl_2_exp_ctrl == NULL.");	
					if (!write_to_dio_ctrl_2_exp_ctrl_msg_buffer(msgs_dio_ctrl_2_exp_ctrl, static_rt_tasks_data->current_system_time, DIO_CTRL_2_EXP_CTRL_MSG_I_AM_ALIVE, 0))
						return print_message(ERROR_MSG ,"DioControl", "DioControlRtTask", "connect_to_exp_ctrl", "write_to_dio_ctrl_2_exp_ctrl_msg_buffer().");	
					print_message(INFO_MSG ,"DioControl", "DioControlRtTask", "connect_to_exp_ctrl", "Connection to EXP_CONTROL is successful!!!");	
					return TRUE;		
				default:
					print_message(BUG_MSG ,"DioControl", "DioControlRtTask", "connect_to_exp_ctrl", str_exp_ctrl_2_dio_ctrl_msg);	
					return print_message(BUG_MSG ,"DioControl", "DioControlRtTask", "connect_to_exp_ctrl", "default - switch.");
			}
		}
		print_message(INFO_MSG ,"DioControl", "DioControlRtTask", "connect_to_exp_ctrl", "Waiting for EXP_CONTROL to connect.");	
		sleep(1);
	}
	return print_message(BUG_MSG ,"DioControl", "DioControlRtTask", "connect_to_dio_ctrl_interf", "Wrong hit in the code.");
}
