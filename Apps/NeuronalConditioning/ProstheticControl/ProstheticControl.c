#include "ProstheticControl.h"

static pthread_t logging_thread;
void *logging_thread_function( void *message_log );

#define BASE_SERVO_0_DEGREE_PULSE		2097
#define BASE_SERVO_90_DEGREE_PULSE		1532
#define BASE_SERVO_0_DEGREE_ADC_VAL		42
#define BASE_SERVO_90_DEGREE_ADC_VAL	311

#define SHOULDER_SERVO_0_DEGREE_PULSE		2160
#define SHOULDER_SERVO_90_DEGREE_PULSE		1585
#define SHOULDER_SERVO_0_DEGREE_ADC_VAL		546
#define SHOULDER_SERVO_90_DEGREE_ADC_VAL	287

#define ELBOW_SERVO_0_DEGREE_PULSE		1000
#define ELBOW_SERVO_90_DEGREE_PULSE		1484
#define ELBOW_SERVO_0_DEGREE_ADC_VAL	179
#define ELBOW_SERVO_90_DEGREE_ADC_VAL	267

#define BASE_SERVO_INIT_PULSE				BASE_SERVO_90_DEGREE_PULSE 
#define SHOULDER_SERVO_INIT_PULSE		1680
#define ELBOW_SERVO_INIT_PULSE			1494

int main( int argc, char *argv[])
{
	RtTasksData *rt_tasks_data = NULL;
	ThreeDofRobot 	*robot_arm = NULL;
	ProstheticCtrlParadigmRobotReach *prosthetic_ctrl_paradigm = NULL;
	MessageLogBuffer *message_log = NULL;
	Gui2ProstheticCtrlMsg *msgs_gui_2_prosthetic_ctrl = NULL; 
   	ProstheticCtrl2GuiMsg *msgs_prosthetic_ctrl_2_gui = NULL; 
	ProstheticCtrlStatusHistory* prosthetic_ctrl_status_history = NULL;
	ThreeDofRobotAngleHistory *robot_angle_history = NULL;
	ThreeDofRobotPulseHistory *robot_pulse_history = NULL;
	unsigned int i;
	ServoPulse diff_pulse;

    	setlocale(LC_ALL,  "en_US.UTF-8"); // ".OCP" if you want to use system settings

   	rt_tasks_data = rtai_malloc(SHM_NUM_RT_TASKS_DATA, 0);
	if (rt_tasks_data == NULL) 
		return print_message(ERROR_MSG ,"ProstheticControl", "ProstheticControl", "main", "rt_tasks_data == NULL.");

	robot_arm = g_new0(ThreeDofRobot, 1);
	prosthetic_ctrl_paradigm = g_new0(ProstheticCtrlParadigmRobotReach, 1);

	init_three_dof_robot_arm(robot_arm);
	submit_arm_length_vals(robot_arm, 14.60, 19.4, 2.1);
	submit_arm_security_limits(robot_arm, -19.0, 20.0, -20.0, 20.0, 3.0, 35.0, (M_PI*0.0)/12.0, (M_PI*12.0)/12.0, -(M_PI*0.5)/12.0, (M_PI*12.0)/12.0,  (M_PI*0.0)/12.0, (M_PI*12.0)/12.0);
	if (! submit_cartesian_robotic_space_borders(robot_arm, prosthetic_ctrl_paradigm, -18.0, 15.5, -19.0, 19.0, 4.0, 34.0))
		return print_message(ERROR_MSG ,"ProstheticControl", "ProstheticControl", "main", "! submit_cartesian_robotic_space_borders().");
	if (! submit_polar_robotic_space_borders(robot_arm, prosthetic_ctrl_paradigm, (M_PI*2.5)/12.0, (M_PI*9.5)/12.0, (M_PI*0.0)/12.0, (M_PI*10.0)/12.0, (M_PI*1.0)/12.0, (M_PI*11.0)/12.0))
		return print_message(ERROR_MSG ,"ProstheticControl", "ProstheticControl", "main", "! submit_polar_robotic_space_borders().");

	write_servo_pw_adc_ranges(&(robot_arm->servos[BASE_SERVO]), BASE_SERVO_0_DEGREE_PULSE, BASE_SERVO_90_DEGREE_PULSE, BASE_SERVO_0_DEGREE_ADC_VAL, BASE_SERVO_90_DEGREE_ADC_VAL);
	write_servo_pw_adc_ranges(&(robot_arm->servos[SHOULDER_SERVO]), SHOULDER_SERVO_0_DEGREE_PULSE, SHOULDER_SERVO_90_DEGREE_PULSE, SHOULDER_SERVO_0_DEGREE_ADC_VAL, SHOULDER_SERVO_90_DEGREE_ADC_VAL);
	write_servo_pw_adc_ranges(&(robot_arm->servos[ELBOW_SERVO]), ELBOW_SERVO_0_DEGREE_PULSE, ELBOW_SERVO_90_DEGREE_PULSE, ELBOW_SERVO_0_DEGREE_ADC_VAL, ELBOW_SERVO_90_DEGREE_ADC_VAL);

	init_servo_pulse(&(robot_arm->servos[BASE_SERVO]), BASE_SERVO_INIT_PULSE);
	init_servo_pulse(&(robot_arm->servos[SHOULDER_SERVO]), SHOULDER_SERVO_INIT_PULSE);
	init_servo_pulse(&(robot_arm->servos[ELBOW_SERVO]), ELBOW_SERVO_INIT_PULSE);

	init_servo_angles_for_sample_averaging(&(robot_arm->servos[BASE_SERVO]), ((BASE_SERVO_INIT_PULSE-BASE_SERVO_0_DEGREE_PULSE)/(BASE_SERVO_90_DEGREE_PULSE-BASE_SERVO_0_DEGREE_PULSE))*M_PI_2, 4);  // it is required for check_three_dof_robot_security_limits(). Too weird initialization cannot pass check security limits.
	init_servo_angles_for_sample_averaging(&(robot_arm->servos[SHOULDER_SERVO]), M_PI-((SHOULDER_SERVO_INIT_PULSE-SHOULDER_SERVO_0_DEGREE_PULSE)/(SHOULDER_SERVO_90_DEGREE_PULSE-SHOULDER_SERVO_0_DEGREE_PULSE))*M_PI_2, 4);
	// added 'M_PI -' into the second parameter of the above function since digital servo for shoulder has opposite potentiometer values compared to analog servo (Hitech HS-5805MG vs Hitech HS-805BB) 
	init_servo_angles_for_sample_averaging(&(robot_arm->servos[ELBOW_SERVO]), ((ELBOW_SERVO_INIT_PULSE-ELBOW_SERVO_0_DEGREE_PULSE)/(ELBOW_SERVO_90_DEGREE_PULSE-ELBOW_SERVO_0_DEGREE_PULSE))*M_PI_2, 4);  // it is required for check_three_dof_robot_security_limits(). Too weird initialization cannot pass check security limits.

/*	init_servo_spike_count_memo(&(robot_arm->servos[BASE_SERVO]), 4);
	init_servo_spike_count_memo(&(robot_arm->servos[SHOULDER_SERVO]), 4);
	init_servo_spike_count_memo(&(robot_arm->servos[ELBOW_SERVO]), 4);
*/
	init_servo_spike_count_memo(&(robot_arm->servos[BASE_SERVO]), 8);
	init_servo_spike_count_memo(&(robot_arm->servos[SHOULDER_SERVO]), 8);
	init_servo_spike_count_memo(&(robot_arm->servos[ELBOW_SERVO]), 8);

	prosthetic_ctrl_paradigm->stay_at_target_duration = 50000000;
	prosthetic_ctrl_paradigm->send_pw_command_wait_period = 25000000;
	prosthetic_ctrl_paradigm->receive_position_wait_period = 5000000;

	prosthetic_ctrl_paradigm->only_move_toward_selected_side = FALSE;


//	prosthetic_ctrl_paradigm->spike_2_servo_degree_multiplier = 0.5;
//	prosthetic_ctrl_paradigm->spike_2_servo_degree_handling_period_multiplier = 1;  /// to be 25 ms
	prosthetic_ctrl_paradigm->max_servo_angle_change = 1.0;
	prosthetic_ctrl_paradigm->spike_count_threshold_left = 0;
	prosthetic_ctrl_paradigm->spike_count_threshold_right = 0;
	prosthetic_ctrl_paradigm->left_bias_constant = 0.0; 
  	prosthetic_ctrl_paradigm->right_bias_constant = 0.0;
	prosthetic_ctrl_paradigm->left_spike_multiplier = 1.0;    
	prosthetic_ctrl_paradigm->right_spike_multiplier = 1.0;   

	prosthetic_ctrl_paradigm->target_info.cart_coordinates = g_new0(CartesianCoordinates, 2);
	prosthetic_ctrl_paradigm->target_info.robot_pulse_widths = g_new0(ThreeDofRobotServoPulse, 2);
	prosthetic_ctrl_paradigm->target_info.num_of_positions = 2;

//	POSITIONS ACCORDING TO TARGET LEDS
/*	prosthetic_ctrl_paradigm->target_info.cart_coordinates[0].height = 18.5 ;
	prosthetic_ctrl_paradigm->target_info.cart_coordinates[0].depth = 12.5;
	prosthetic_ctrl_paradigm->target_info.cart_coordinates[0].lateral = -8.0;
	prosthetic_ctrl_paradigm->target_info.robot_pulse_widths[0].pulse[BASE_SERVO] = 1624;
	prosthetic_ctrl_paradigm->target_info.robot_pulse_widths[0].pulse[SHOULDER_SERVO] = 1511;
	prosthetic_ctrl_paradigm->target_info.robot_pulse_widths[0].pulse[ELBOW_SERVO] = 1424;
	prosthetic_ctrl_paradigm->target_info.cart_coordinates[1].height = 18.5 ;
	prosthetic_ctrl_paradigm->target_info.cart_coordinates[1].depth = 12.5;
	prosthetic_ctrl_paradigm->target_info.cart_coordinates[1].lateral = 8.0;
	prosthetic_ctrl_paradigm->target_info.robot_pulse_widths[1].pulse[BASE_SERVO] = 1226;
	prosthetic_ctrl_paradigm->target_info.robot_pulse_widths[1].pulse[SHOULDER_SERVO] = 1511;
	prosthetic_ctrl_paradigm->target_info.robot_pulse_widths[1].pulse[ELBOW_SERVO] = 1424;
*/
	prosthetic_ctrl_paradigm->target_info.cart_coordinates[0].height = 17.7;
	prosthetic_ctrl_paradigm->target_info.cart_coordinates[0].depth = 11.85;
	prosthetic_ctrl_paradigm->target_info.cart_coordinates[0].lateral = 8.0;
	prosthetic_ctrl_paradigm->target_info.robot_pulse_widths[0].pulse[BASE_SERVO] = 1734;
	prosthetic_ctrl_paradigm->target_info.robot_pulse_widths[0].pulse[SHOULDER_SERVO] = SHOULDER_SERVO_INIT_PULSE;
	prosthetic_ctrl_paradigm->target_info.robot_pulse_widths[0].pulse[ELBOW_SERVO] = ELBOW_SERVO_INIT_PULSE;
	prosthetic_ctrl_paradigm->target_info.cart_coordinates[1].height = 17.7 ;
	prosthetic_ctrl_paradigm->target_info.cart_coordinates[1].depth = 11.85;
	prosthetic_ctrl_paradigm->target_info.cart_coordinates[1].lateral = -8.0;
	prosthetic_ctrl_paradigm->target_info.robot_pulse_widths[1].pulse[BASE_SERVO] = 1330;
	prosthetic_ctrl_paradigm->target_info.robot_pulse_widths[1].pulse[SHOULDER_SERVO] = SHOULDER_SERVO_INIT_PULSE;
	prosthetic_ctrl_paradigm->target_info.robot_pulse_widths[1].pulse[ELBOW_SERVO] = ELBOW_SERVO_INIT_PULSE;

	prosthetic_ctrl_paradigm->start_info.num_of_positions = 7;   ///   if change, change trialhandler.c as well. 	paradigm->num_of_robot_start_positions = 3;
	prosthetic_ctrl_paradigm->start_info.cart_coordinates = g_new0(CartesianCoordinates, prosthetic_ctrl_paradigm->start_info.num_of_positions);
	prosthetic_ctrl_paradigm->start_info.robot_pulse_widths = g_new0(ThreeDofRobotServoPulse, prosthetic_ctrl_paradigm->start_info.num_of_positions);

//	POSITIONS ACCORDING TO MIDLINE 
/*	prosthetic_ctrl_paradigm->start_info.cart_coordinates[0].height = 18.2 ;
	prosthetic_ctrl_paradigm->start_info.cart_coordinates[0].depth = 14.3;		
	prosthetic_ctrl_paradigm->start_info.cart_coordinates[0].lateral = 0.0;
	prosthetic_ctrl_paradigm->start_info.robot_pulse_widths[0].pulse[BASE_SERVO] = 1430;
	prosthetic_ctrl_paradigm->start_info.robot_pulse_widths[0].pulse[SHOULDER_SERVO] = 1531;
	prosthetic_ctrl_paradigm->start_info.robot_pulse_widths[0].pulse[ELBOW_SERVO] = 1444;
*/

	diff_pulse = prosthetic_ctrl_paradigm->target_info.robot_pulse_widths[0].pulse[BASE_SERVO] - prosthetic_ctrl_paradigm->target_info.robot_pulse_widths[1].pulse[BASE_SERVO];
	for (i = 0; i < prosthetic_ctrl_paradigm->start_info.num_of_positions; i++)
	{
		prosthetic_ctrl_paradigm->start_info.robot_pulse_widths[i].pulse[BASE_SERVO] = prosthetic_ctrl_paradigm->target_info.robot_pulse_widths[0].pulse[BASE_SERVO]  - ( ((double)(i +1 ) / (prosthetic_ctrl_paradigm->start_info.num_of_positions +1))* diff_pulse );
		prosthetic_ctrl_paradigm->start_info.robot_pulse_widths[i].pulse[SHOULDER_SERVO] = SHOULDER_SERVO_INIT_PULSE;
		prosthetic_ctrl_paradigm->start_info.robot_pulse_widths[i].pulse[ELBOW_SERVO] = ELBOW_SERVO_INIT_PULSE;		
	}

	prosthetic_ctrl_paradigm->threshold.outer_threshold.r_x = 16;  //height
	prosthetic_ctrl_paradigm->threshold.outer_threshold.r_y = 46; // depth    ->>>  to provide a circle with radius of ~12 cm at the frontal surface of the cage
	prosthetic_ctrl_paradigm->threshold.outer_threshold.r_z = 18; // lateral

	prosthetic_ctrl_paradigm->threshold.point_reach_threshold.r_x = 2.0;
	prosthetic_ctrl_paradigm->threshold.point_reach_threshold.r_y = 2.0;
	prosthetic_ctrl_paradigm->threshold.point_reach_threshold.r_z = 2.0;

	prosthetic_ctrl_paradigm->threshold.target_reach_threshold.r_x = 10.0; //height
	prosthetic_ctrl_paradigm->threshold.target_reach_threshold.r_y = 10.0; // depth
	prosthetic_ctrl_paradigm->threshold.target_reach_threshold.r_z = 1.0;// lateral

	msgs_gui_2_prosthetic_ctrl = allocate_gui_2_prosthetic_ctrl_msg_buffer(msgs_gui_2_prosthetic_ctrl);
	msgs_prosthetic_ctrl_2_gui = allocate_prosthetic_ctrl_2_gui_msg_buffer(msgs_prosthetic_ctrl_2_gui);

	prosthetic_ctrl_status_history = allocate_prosthetic_ctrl_status_history(prosthetic_ctrl_status_history, 50); 
	robot_angle_history = allocate_three_dof_robot_angle_history(robot_angle_history, 1000);
	robot_pulse_history = allocate_three_dof_robot_pulse_history(robot_pulse_history, 1000);

	initialize_data_read_write_handlers();

	message_log = allocate_message_log_buffer(message_log, 200);
    	pthread_create( &logging_thread, NULL, logging_thread_function, (void*)message_log);

	if(! create_prosthetic_control_rt_thread(rt_tasks_data, robot_arm, msgs_gui_2_prosthetic_ctrl,  msgs_prosthetic_ctrl_2_gui, prosthetic_ctrl_paradigm, message_log, prosthetic_ctrl_status_history, robot_angle_history, robot_pulse_history))
		return print_message(ERROR_MSG ,"ProstheticControl", "ProstheticControl", "main", "create_prosthetic_control_rt_thread().");
	gtk_init(&argc, &argv);
	create_gui_handler(rt_tasks_data, msgs_gui_2_prosthetic_ctrl, msgs_prosthetic_ctrl_2_gui, robot_arm, prosthetic_ctrl_paradigm, prosthetic_ctrl_status_history, robot_angle_history, robot_pulse_history);
	gtk_main();
	return 0;
}	

void *logging_thread_function( void *message_log )
{
	while (1)
	{
		if (!print_message_log_buffer(message_log, 50))
			return (void*)print_message(ERROR_MSG ,"ProstheticControl", "ProstheticControl", "logging_thread_function", "! print_message_log_buffer().");
		sleep(1);
	}
	return NULL;	
}
