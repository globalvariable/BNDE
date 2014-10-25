#ifndef SERVO_H
#define SERVO_H

#include <math.h>
#include <stdbool.h>
#include <pthread.h>
#include <stdio.h>
#include <gtk/gtk.h>

#define SERVO_CONTROLLER_CRYSTAL_FREQ	9216  // MHz

typedef union 
{
	unsigned char		byte[2];
	unsigned short int	pulse_width;
} ServoPulseCmd;	// X PointOneMicrosec

typedef unsigned short int ServoPulse;
typedef short int ServoPulseChange;   /// roration direction is provided signed int

typedef short int ServoPosition;   

typedef union 
{
	unsigned char		byte[2];
	ServoPosition			position;  // servo potentiometer output's adc quanta
} ServoPositionUnion;	// X PointOneMicrosec

typedef double ServoAngle;

typedef struct 
{ 
	ServoPulse			pulse_width_0_degree;	
	ServoPulse			pulse_width_90_degree;	
	ServoPosition			position_0_degree;
	ServoPosition			position_90_degree;
	double				radian_per_pos_quanta;
	double				pw_per_degree;
} ServoRange;

typedef struct 
{
	double min;
	double max;   // pi radians
} ServoAngularLimit;

typedef struct 
{
	ServoAngle			*angles;  
	unsigned int			memo_size;
} ServoAngleMemo;

typedef struct 
{
	unsigned int			*spike_count_2_decrease_pw;
	unsigned int			*spike_count_2_increase_pw;
	unsigned int			memo_size;
} ServoSpikeCountMemo;

typedef struct 
{ 
	pthread_mutex_t 		mutex; 
	ServoPulseCmd		pulse_command;	// pulse width to transmit (65536 - Timer value for MCU)
	ServoPulse			pulse_current;	// pulse width to transmit
	ServoPulse			pulse_target;		// pulse width for the target position.
	ServoPulseChange	pulse_change;	// inc/decrement pulse width to control speed to reach target.
	ServoPositionUnion	position;
	ServoRange			range;
	ServoAngle			current_angle;
	ServoAngularLimit		angular_security_limit;
	ServoAngleMemo		*angle_memo_4_averaging;  // for filtering via averaging
	ServoSpikeCountMemo	*spike_count_memo;
} ServoData;

void init_servo_data(ServoData *servo_data);
void init_servo_pulse(ServoData *servo_data, ServoPulse pulse_width);
void submit_servo_target(ServoData *servo_data, ServoPulse target_pulse_width, double change_rate);
void submit_new_servo_target_with_no_change_rate_changing(ServoData *servo_data, ServoPulse target_pulse_width);
void submit_servo_direction_and_speed(ServoData *servo_data,  ServoPulseChange amount);
void submit_servo_direction_and_speed_via_spike_count(ServoData *servo_data,  unsigned int spike_cnt_2_decrease_pw, unsigned int spike_cnt_2_increase_pw);
void evaluate_servo_pw_command(ServoData *servo_data);
void evaluate_servo_pw_command_with_limitation(ServoData *servo_data, double degree_limitation);
void evaluate_servo_pw_command_with_limitation_and_threshold(ServoData *servo_data, double degree_limitation, double degree_threshold);
bool evaluate_servo_pw_command_with_target_reach_feedback(ServoData *servo_data);
void evaluate_servo_pw_command_via_spike_count_with_limitation_thresholding_biasing(ServoData *servo_data, double degree_limitation, double threshold, double bias_2_increase);
void evaluate_servo_pw_command_via_spike_count_with_limitation_count_thresholding(ServoData *servo_data, double degree_limitation, double threshold);
void get_servo_pw_val_bytes(ServoData *servo_data, unsigned char *low_byte, unsigned char *high_byte);
void get_servo_position_val(ServoData *servo_data, ServoPosition *servo_position);
void write_servo_position_val(ServoData *servo_data, unsigned char low_byte, unsigned char high_byte);
void write_servo_pw_adc_ranges(ServoData *servo_data, ServoPulse zero_degree_pulse,ServoPulse ninety_degree_pulse, ServoPosition zero_degree_adc_val, ServoPosition ninety_degree_adc_val);
void write_servo_0_degree_adc_val(ServoData *servo_data, ServoPosition zero_degree_adc_val);
void write_servo_90_degree_adc_val(ServoData *servo_data, ServoPosition ninety_degree_adc_val);
void init_servo_angles_for_sample_averaging(ServoData *servo, ServoAngle initial_angle, unsigned int prev_angle_memo_size);
void init_servo_spike_count_memo(ServoData *servo, unsigned int memo_size);
void calculate_servo_angle_with_averaging(ServoData *servo);
void clear_spike_count_memo_of_servo(ServoData *servo);
#endif
