#include "ArmConfig.h"

int main( int argc, char *argv[])
{
	ThreeDofRobot *robot_arm = NULL;

	robot_arm = g_new0(ThreeDofRobot, 1);
	init_three_dof_robot_arm(robot_arm);
	submit_arm_length_vals(robot_arm, 14.60, 19.4, 2.1);
	submit_arm_security_limits(robot_arm, -19.0, 15.0, -20.0, 20.0, 3.0, 35.0, (M_PI*0.0)/12.0, (M_PI*12.0)/12.0, -(M_PI*0.5)/12.0, (M_PI*12.0)/12.0,  (M_PI*0.0)/12.0, (M_PI*12.0)/12.0);

	write_servo_pw_adc_ranges(&(robot_arm->servos[BASE_SERVO]), BASE_SERVO_0_DEGREE_PULSE, BASE_SERVO_90_DEGREE_PULSE, BASE_SERVO_0_DEGREE_ADC_VAL, BASE_SERVO_90_DEGREE_ADC_VAL);
	write_servo_pw_adc_ranges(&(robot_arm->servos[SHOULDER_SERVO]), SHOULDER_SERVO_0_DEGREE_PULSE, SHOULDER_SERVO_90_DEGREE_PULSE, SHOULDER_SERVO_0_DEGREE_ADC_VAL, SHOULDER_SERVO_90_DEGREE_ADC_VAL);
	write_servo_pw_adc_ranges(&(robot_arm->servos[ELBOW_SERVO]), ELBOW_SERVO_0_DEGREE_PULSE, ELBOW_SERVO_90_DEGREE_PULSE, ELBOW_SERVO_0_DEGREE_ADC_VAL, ELBOW_SERVO_90_DEGREE_ADC_VAL);

	init_servo_pulse(&(robot_arm->servos[BASE_SERVO]), BASE_SERVO_INIT_PULSE);
	init_servo_pulse(&(robot_arm->servos[SHOULDER_SERVO]), SHOULDER_SERVO_INIT_PULSE);
	init_servo_pulse(&(robot_arm->servos[ELBOW_SERVO]), ELBOW_SERVO_INIT_PULSE);

	init_servo_angles_for_sample_averaging(&(robot_arm->servos[BASE_SERVO]), ((BASE_SERVO_INIT_PULSE-BASE_SERVO_0_DEGREE_PULSE)/(BASE_SERVO_90_DEGREE_PULSE-BASE_SERVO_0_DEGREE_PULSE))*M_PI_2, 3);  // it is required for check_three_dof_robot_security_limits(). Too weird initialization cannot pass check security limits.
	init_servo_angles_for_sample_averaging(&(robot_arm->servos[SHOULDER_SERVO]), ((SHOULDER_SERVO_INIT_PULSE-SHOULDER_SERVO_0_DEGREE_PULSE)/(SHOULDER_SERVO_90_DEGREE_PULSE-SHOULDER_SERVO_0_DEGREE_PULSE))*M_PI_2, 3);
	init_servo_angles_for_sample_averaging(&(robot_arm->servos[ELBOW_SERVO]), ((ELBOW_SERVO_INIT_PULSE-ELBOW_SERVO_0_DEGREE_PULSE)/(ELBOW_SERVO_90_DEGREE_PULSE-ELBOW_SERVO_0_DEGREE_PULSE))*M_PI_2, 3);  // it is required for check_three_dof_robot_security_limits(). Too weird initialization cannot pass check security limits.

	if (! init_rs232_com1(115200))
 		return print_message(ERROR_MSG ,"ArmConfig", "ArmConfig", "main", "! init_rs232_com1().");	

	if(! create_servo_control_rt_thread(robot_arm))
		return print_message(ERROR_MSG ,"ArmConfig", "ArmConfig", "main", "create_servo_control_rt_thread().");

	gtk_init(&argc, &argv);
	create_gui(robot_arm);
	gtk_main();
	return 0;
}	
