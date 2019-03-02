#include "ArmConfigRtTask.h"

static ThreeDofRobot *static_robot_arm = NULL;

static RtTasksData *static_rt_tasks_data = NULL;

static SEM *static_dio_ctrl_rx_buff_sem = NULL;
static SEM *static_dio_ctrl_tx_buff_sem = NULL;
static DioCtrlRxShm *static_dio_ctrl_rx_buff_shm = NULL;
static DioCtrlTxShm *static_dio_ctrl_tx_buff_shm = NULL;




static int servo_control_rt_thread = 0;
static bool rt_servo_control_stay_alive = 1;

static void *rt_servo_control(void *args);


bool create_servo_control_rt_thread(ThreeDofRobot *robot_arm)
{
	static_robot_arm = robot_arm;


	if (servo_control_rt_thread != 0)
		return print_message(BUG_MSG ,"ServoControl", "ServoControlRtTask", "create_servo_control_rt_thread", "CANNOT create rt_thread again.");	
	servo_control_rt_thread =  rt_thread_create(rt_servo_control, NULL, 10000);
	if (servo_control_rt_thread == 0)
		return print_message(BUG_MSG ,"ServoControl", "ServoControlRtTask", "create_servo_control_rt_thread", "Couldn' t create rt_thread.");	

	return TRUE;
}

static void *rt_servo_control(void *args)
{
	RT_TASK *handler;
        RTIME period;
	unsigned int prev_time, curr_time, i;
	TimeStamp curr_system_time;

	unsigned char rx_buffer[RX_BUFF_SIZE];
	unsigned char adc_tx_buffer[ADC_TX_BUFF_SIZE];
	unsigned char pw_tx_buffer[PW_TX_BUFF_SIZE];
	DioCtrlTxShm dio_ctrl_tx_buffer;
	unsigned char cmd_low_byte, cmd_high_byte;

	adc_tx_buffer[0] = 'A';
	adc_tx_buffer[ADC_TX_BUFF_SIZE-2] = 0xFF;
	adc_tx_buffer[ADC_TX_BUFF_SIZE-1] = 0xFF;

	pw_tx_buffer[0] = 'P';
	pw_tx_buffer[PW_TX_BUFF_SIZE-2] = 0xFF;
	pw_tx_buffer[PW_TX_BUFF_SIZE-1] = 0xFF;	


	rt_set_oneshot_mode();

       if (! (handler = rt_task_init_schmod(nam2num("SERVOCON"), 10, 10000, 1000, SCHED_FIFO, 1 << ((3*MAX_NUM_OF_CPU_THREADS_PER_CPU)+0)))) {
		print_message(ERROR_MSG ,"ServoControl", "ServoControlRtTask", "rt_servo_control", "handler = rt_task_init_schmod()."); exit(1); }


	// SEMAPHORE should be init'd after rt_task_init_schmod
	if (! init_dio_ctrl_rx_buffer_semaphore(&static_dio_ctrl_rx_buff_sem))  {
		print_message(ERROR_MSG ,"ArmConfig", "ArmConfig", "main", "! init_dio_ctrl_rx_buffer_semaphore().");	exit(1); }	
	if (! init_dio_ctrl_tx_buffer_semaphore(&static_dio_ctrl_tx_buff_sem))  {
		print_message(ERROR_MSG ,"ArmConfig", "ArmConfig", "main", "! init_dio_ctrl_tx_buffer_semaphore().");	exit(1); }	
	if (! init_dio_ctrl_tx_buffer_shm(&static_dio_ctrl_tx_buff_shm, DIO_CTRL_CMD_MSG_LEN, rt_get_cpu_time_ns()) )  {
		print_message(ERROR_MSG ,"ArmConfig", "ArmConfig", "main", "! init_dio_ctrl_tx_buffer_shm().");	exit(1); }	
	if (! init_dio_ctrl_rx_buffer_shm(&static_dio_ctrl_rx_buff_shm, DIO_CTRL_STATUS_MSG_LEN) )  {
		print_message(ERROR_MSG ,"ArmConfig", "ArmConfig", "main", "! init_dio_ctrl_rx_buffer_shm().");	exit(1); }	


	start_rt_timer(0);

        period = nano2count(10000000);
        rt_task_make_periodic(handler, rt_get_time() + period, period);


        mlockall(MCL_CURRENT | MCL_FUTURE);
	rt_make_hard_real_time();		// do not forget this // check the task by nano /proc/rtai/scheduler (HD/SF) 

	curr_time = rt_get_cpu_time_ns();
	prev_time = curr_time;	

	if (! read_dio_ctrl_tx_buff_shm(&dio_ctrl_tx_buffer, static_dio_ctrl_tx_buff_shm, DIO_CTRL_CMD_MSG_LEN, static_dio_ctrl_tx_buff_sem)) {   //  Exp Envi Handler writes its command to static_dio_ctrl_tx_buff for delivery by this process
		print_message(ERROR_MSG ,"ServoControl", "ServoControlRtTask", "rt_servo_control", "! read_dio_ctrl_tx_buff_shm()."); exit(1); }	
	for (i = 0; i < DIO_CTRL_CMD_MSG_LEN; i++)
		adc_tx_buffer[DIO_CTRL_CMD_MSG_START_IDX+i] = dio_ctrl_tx_buffer.dio_ctrl_tx_buff[i];   // 'A' + DIO_CTRL_COMND (1 BYTE) + 0xFF + 0xFF	
	if (! write_to_rs232_com1(adc_tx_buffer, ADC_TX_BUFF_SIZE)) {
		print_message(ERROR_MSG ,"ServoControl", "ServoControlRtTask", "rt_servo_control", "! write_to_rs232_com1()."); exit(1); }	
        while (rt_servo_control_stay_alive) 
	{
		prev_time = rt_get_cpu_time_ns();

        	rt_task_wait_period();
		curr_time = rt_get_cpu_time_ns();

//		printf ("read\t%lld\t", rt_get_cpu_time_ns());	
		// routines
		clear_rx_buffer(rx_buffer, RX_BUFF_SIZE) ;
		if (! read_from_rs232_com1(rx_buffer, RX_BUFF_SIZE)) 
		{
			printf ("%lld\t", rt_get_cpu_time_ns());
			for (i = 0; i < RX_BUFF_SIZE; i++)
				printf ("%d\t", rx_buffer[i]);
			printf ("\n");
			print_message(ERROR_MSG ,"ServoControl", "ServoControlRtTask", "rt_servo_control", "! read_from_rs232_com1()."); exit(1); 
		}

//		printf ("%lld\n", rt_get_cpu_time_ns());	

		if ((rx_buffer[0] != 0xFF) || (rx_buffer[RX_BUFF_SIZE-2] != 0xFF) || (rx_buffer[RX_BUFF_SIZE-1] != 0xFF)) {
			print_message(ERROR_MSG ,"ServoControl", "ServoControlRtTask", "rt_servo_control", "Invalid rx message format."); exit(1); }
		if (! write_to_dio_ctrl_rx_buff_shm(&(rx_buffer[DIO_CTRL_STATUS_MSG_START_IDX]), static_dio_ctrl_rx_buff_shm, DIO_CTRL_STATUS_MSG_LEN, static_dio_ctrl_rx_buff_sem)) {
			print_message(ERROR_MSG ,"ServoControl", "ServoControlRtTask", "rt_servo_control", "! write_to_dio_ctrl_rx_buff_shm()."); exit(1); }
		for (i = 0; i <  ROBOT_POSITION_MSG_LEN; i+=2)
			write_servo_position_val(&(static_robot_arm->servos[(unsigned int) (i/2)]), rx_buffer[ROBOT_POSITION_MSG_START_IDX + i], rx_buffer[ROBOT_POSITION_MSG_START_IDX + i + 1]);

//		calculate_forward_kinematics(static_robot_arm);
		calculate_forward_kinematics_with_averaging(static_robot_arm);	


//		for (i = 0; i < THREE_DOF_ROBOT_NUM_OF_SERVOS; i++)
//			printf("%u\t", static_robot_arm->servos[i].position.position);
//		printf("\n");

//		printf("%u\t%u\t%u\n", static_robot_arm->servos[0].position.position, static_robot_arm->servos[1].position.position, static_robot_arm->servos[2].position.position);

		// routines	

	       	rt_task_wait_period();
		curr_time = rt_get_cpu_time_ns();

		prev_time = curr_time;

//		printf ("write\t%lld\t", rt_get_cpu_time_ns());		

		// routines

		if (! read_dio_ctrl_tx_buff_shm(&dio_ctrl_tx_buffer, static_dio_ctrl_tx_buff_shm, DIO_CTRL_CMD_MSG_LEN, static_dio_ctrl_tx_buff_sem)) {
			print_message(ERROR_MSG ,"ServoControl", "ServoControlRtTask", "rt_servo_control", "! read_dio_ctrl_tx_buff_shm()."); exit(1); }
		
//		printf("%u\n", dio_ctrl_tx_buffer[0]);

		for (i = 0; i < DIO_CTRL_CMD_MSG_LEN; i++)
			pw_tx_buffer[DIO_CTRL_CMD_MSG_START_IDX+i] = dio_ctrl_tx_buffer.dio_ctrl_tx_buff[i];

//		if ( check_three_dof_robot_security_limits(static_robot_arm))
//		{
			evaluate_three_dof_robot_arm_pw_command(static_robot_arm);
			for (i = 0; i < ROBOT_PW_CMD_MSG_LEN; i+=2)
			{
				get_servo_pw_val_bytes(&(static_robot_arm->servos[(unsigned int) (i/2)]), &cmd_low_byte, &cmd_high_byte);
				pw_tx_buffer[ROBOT_PW_CMD_MSG_START_IDX + i] = cmd_low_byte;
 				pw_tx_buffer[ROBOT_PW_CMD_MSG_START_IDX + i +1] = cmd_high_byte;
			}
			if (! write_to_rs232_com1(pw_tx_buffer, PW_TX_BUFF_SIZE)) {
				print_message(ERROR_MSG ,"ServoControl", "ServoControlRtTask", "rt_servo_control", "! write_to_rs232_com1()."); exit(1); }
//			printf ("%lld\n", rt_get_cpu_time_ns());		
/*		}
		else
		{
			print_message(ERROR_MSG ,"ServoControl", "ServoControlRtTask", "rt_servo_control", "! check_three_dof_robot_out_of_security_limits()."); exit(1);
		}
*/

		// routines	

        }
	rt_make_soft_real_time();
        rt_task_delete(handler);
	print_message(INFO_MSG ,"FirstBMICageInterfacer", "FirstBMICageInterfacerRtTask", "rt_cage_interfacer", "rt_task_delete().");	

        return 0; 
}
