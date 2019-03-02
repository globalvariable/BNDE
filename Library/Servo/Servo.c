#include "Servo.h"

void init_servo_data(ServoData *servo_data)
{
	pthread_mutex_init(&(servo_data->mutex), NULL);	
	pthread_mutex_lock(&(servo_data->mutex));
	servo_data->pulse_command.pulse_width = 0;
	servo_data->pulse_current = 0;
	servo_data->pulse_target= 0;
	servo_data->pulse_change = 0;
	servo_data->position.position = 0;
	pthread_mutex_unlock(&(servo_data->mutex));
}

void init_servo_pulse(ServoData *servo_data, ServoPulse pulse_width)
{
	pthread_mutex_lock(&(servo_data->mutex));	
	servo_data->pulse_current = pulse_width;
	servo_data->pulse_target = pulse_width;
	servo_data->pulse_command.pulse_width = (unsigned short int)65536 - (unsigned short int)((9216/10000.0)*10*servo_data->pulse_current);		
	pthread_mutex_unlock(&(servo_data->mutex));	
}

void submit_servo_target(ServoData *servo_data, ServoPulse target_pulse_width, double change_rate)
{
	pthread_mutex_lock(&(servo_data->mutex));
	servo_data->pulse_target = target_pulse_width;
	servo_data->pulse_change = (ServoPulseChange)((((double)servo_data->pulse_target) - ((double)servo_data->pulse_current))*change_rate);
	pthread_mutex_unlock(&(servo_data->mutex));
}
void submit_new_servo_target_with_no_change_rate_changing(ServoData *servo_data, ServoPulse target_pulse_width)
{
	pthread_mutex_lock(&(servo_data->mutex));
	servo_data->pulse_target = target_pulse_width;
	if (servo_data->pulse_target < servo_data->pulse_current)		/// change direction
	{
		if (servo_data->pulse_change > 0)
			servo_data->pulse_change = (- servo_data->pulse_change);
	}
	else
	{
		if (servo_data->pulse_change < 0)
			servo_data->pulse_change = (- servo_data->pulse_change);		
	}
	pthread_mutex_unlock(&(servo_data->mutex));
}

void submit_servo_direction_and_speed(ServoData *servo_data,  ServoPulseChange amount)
{
	pthread_mutex_lock(&(servo_data->mutex));
	servo_data->pulse_change = 0;
	servo_data->pulse_target = servo_data->pulse_target + amount;
	pthread_mutex_unlock(&(servo_data->mutex));
}

void submit_servo_direction_and_speed_via_spike_count(ServoData *servo_data,  unsigned int spike_cnt_2_decrease_pw, unsigned int spike_cnt_2_increase_pw)
{
	pthread_mutex_lock(&(servo_data->mutex));
	servo_data->pulse_change = 0;
	servo_data->spike_count_memo->spike_count_2_decrease_pw[0] += spike_cnt_2_decrease_pw;
	servo_data->spike_count_memo->spike_count_2_increase_pw[0] += spike_cnt_2_increase_pw;
	pthread_mutex_unlock(&(servo_data->mutex));
}

void evaluate_servo_pw_command(ServoData *servo_data)
{
	pthread_mutex_lock(&(servo_data->mutex));

	if (servo_data->pulse_change == 0)	// it is evaluating submit_servo_direction_and_speed
	{
		servo_data->pulse_current = servo_data->pulse_target;  // pulse_current is the pulse width which is sent to servo in previous period.
		servo_data->pulse_command.pulse_width = (unsigned short int)65536 - (unsigned short int)((9216/10000.0)*10*servo_data->pulse_current);
	}
	else if (servo_data->pulse_change > 0)  // target pulse width given and it reaches that pulse width with servo_data->pulse_change with the servo pulsing frequency period.
	{
		servo_data->pulse_current += servo_data->pulse_change;
		if (servo_data->pulse_current > servo_data->pulse_target)
		{
			servo_data->pulse_current = servo_data->pulse_target;
		}
		servo_data->pulse_command.pulse_width = (unsigned short int)65536 - (unsigned short int)((9216/10000.0)*10*servo_data->pulse_current);
	}
	else if (servo_data->pulse_change < 0) 
	{
		servo_data->pulse_current += servo_data->pulse_change;
		if (servo_data->pulse_current < servo_data->pulse_target)
		{
			servo_data->pulse_current = servo_data->pulse_target;
		}
		servo_data->pulse_command.pulse_width = (unsigned short int)65536 - (unsigned short int)((9216/10000.0)*10*servo_data->pulse_current);		
	}
	pthread_mutex_unlock(&(servo_data->mutex));	
}

void evaluate_servo_pw_command_with_limitation(ServoData *servo_data, double degree_limitation)
{
	double degree_change;
	pthread_mutex_lock(&(servo_data->mutex));

	if (servo_data->pulse_change == 0)	// it is evaluating submit_servo_direction_and_speed
	{
		if (servo_data->pulse_target > servo_data->pulse_current)
		{
			degree_change = ((double)(servo_data->pulse_target - servo_data->pulse_current)) / servo_data->range.pw_per_degree;
			if (degree_change > degree_limitation)
			{
				servo_data->pulse_target = servo_data->pulse_current + ((ServoPulse)(servo_data->range.pw_per_degree * degree_limitation));
			}
		}
		else
		{
			degree_change = ((double)(servo_data->pulse_current - servo_data->pulse_target)) / servo_data->range.pw_per_degree;
			if (degree_change > degree_limitation)
			{
				servo_data->pulse_target = servo_data->pulse_current - ((ServoPulse)(servo_data->range.pw_per_degree * degree_limitation));
			}
		}
		servo_data->pulse_current = servo_data->pulse_target;	// pulse_current is the pulse width which is sent to servo in previous period.
		servo_data->pulse_command.pulse_width = (unsigned short int)65536 - (unsigned short int)((9216/10000.0)*10*servo_data->pulse_current);
	}
	else if (servo_data->pulse_change > 0)  // target pulse width given and it reaches that pulse width with servo_data->pulse_change with the servo pulsing frequency period.
	{
		servo_data->pulse_current += servo_data->pulse_change;
		if (servo_data->pulse_current > servo_data->pulse_target)
		{
			servo_data->pulse_current = servo_data->pulse_target;
		}
		servo_data->pulse_command.pulse_width = (unsigned short int)65536 - (unsigned short int)((9216/10000.0)*10*servo_data->pulse_current);
	}
	else if (servo_data->pulse_change < 0) 
	{
		servo_data->pulse_current += servo_data->pulse_change;
		if (servo_data->pulse_current < servo_data->pulse_target)
		{
			servo_data->pulse_current = servo_data->pulse_target;
		}
		servo_data->pulse_command.pulse_width = (unsigned short int)65536 - (unsigned short int)((9216/10000.0)*10*servo_data->pulse_current);		
	}
	pthread_mutex_unlock(&(servo_data->mutex));	
}

void evaluate_servo_pw_command_with_limitation_and_threshold(ServoData *servo_data, double degree_limitation, double degree_threshold)
{
	double degree_change;
	pthread_mutex_lock(&(servo_data->mutex));

	if (servo_data->pulse_change == 0)	// it is evaluating submit_servo_direction_and_speed
	{
		if (servo_data->pulse_target > servo_data->pulse_current)
		{
			degree_change = ((double)(servo_data->pulse_target - servo_data->pulse_current)) / servo_data->range.pw_per_degree;
			if (degree_change < degree_threshold)
			{
				servo_data->pulse_target = servo_data->pulse_current; 		// no move
			}
			else if (degree_change > degree_limitation)
			{
				servo_data->pulse_target = servo_data->pulse_current + ((ServoPulse)(servo_data->range.pw_per_degree * degree_limitation));
			}
		}
		else
		{
			degree_change = ((double)(servo_data->pulse_current - servo_data->pulse_target)) / servo_data->range.pw_per_degree;
			if (degree_change < degree_threshold)
			{
				servo_data->pulse_target = servo_data->pulse_current; 		// no move
			}
			else if (degree_change > degree_limitation)
			{
				servo_data->pulse_target = servo_data->pulse_current - ((ServoPulse)(servo_data->range.pw_per_degree * degree_limitation));
			}
		}
		servo_data->pulse_current = servo_data->pulse_target;	// pulse_current is the pulse width which is sent to servo in previous period.
		servo_data->pulse_command.pulse_width = (unsigned short int)65536 - (unsigned short int)((9216/10000.0)*10*servo_data->pulse_current);
	}
	else if (servo_data->pulse_change > 0)  // target pulse width given and it reaches that pulse width with servo_data->pulse_change with the servo pulsing frequency period.
	{
		servo_data->pulse_current += servo_data->pulse_change;
		if (servo_data->pulse_current > servo_data->pulse_target)
		{
			servo_data->pulse_current = servo_data->pulse_target;
		}
		servo_data->pulse_command.pulse_width = (unsigned short int)65536 - (unsigned short int)((9216/10000.0)*10*servo_data->pulse_current);
	}
	else if (servo_data->pulse_change < 0) 
	{
		servo_data->pulse_current += servo_data->pulse_change;
		if (servo_data->pulse_current < servo_data->pulse_target)
		{
			servo_data->pulse_current = servo_data->pulse_target;
		}
		servo_data->pulse_command.pulse_width = (unsigned short int)65536 - (unsigned short int)((9216/10000.0)*10*servo_data->pulse_current);		
	}
	pthread_mutex_unlock(&(servo_data->mutex));	
}

bool evaluate_servo_pw_command_with_target_reach_feedback(ServoData *servo_data)
{
	bool reached;

	reached = FALSE;
	pthread_mutex_lock(&(servo_data->mutex));

	if (servo_data->pulse_change == 0)	// it is evaluating submit_servo_direction_and_speed
	{
		servo_data->pulse_current = servo_data->pulse_target;  // pulse_current is the pulse width which is sent to servo in previous period.
		servo_data->pulse_command.pulse_width = (unsigned short int)65536 - (unsigned short int)((9216/10000.0)*10*servo_data->pulse_current);
	}
	else if (servo_data->pulse_change > 0)  // target pulse width given and it reaches that pulse width with servo_data->pulse_change with the servo pulsing frequency period.
	{
		servo_data->pulse_current += servo_data->pulse_change;
		if (servo_data->pulse_current > servo_data->pulse_target)
		{
			servo_data->pulse_current = servo_data->pulse_target;
			reached = TRUE;
		}
		servo_data->pulse_command.pulse_width = (unsigned short int)65536 - (unsigned short int)((9216/10000.0)*10*servo_data->pulse_current);
	}
	else if (servo_data->pulse_change < 0) 
	{
		servo_data->pulse_current += servo_data->pulse_change;
		if (servo_data->pulse_current < servo_data->pulse_target)
		{
			servo_data->pulse_current = servo_data->pulse_target;
			reached = TRUE;
		}
		servo_data->pulse_command.pulse_width = (unsigned short int)65536 - (unsigned short int)((9216/10000.0)*10*servo_data->pulse_current);		
	}
	pthread_mutex_unlock(&(servo_data->mutex));	
	return reached;
}

void evaluate_servo_pw_command_via_spike_count_with_limitation_thresholding_biasing(ServoData *servo_data, double degree_limitation, double threshold, double bias_2_increase)
{
	double sum_2_decrease, sum_2_increase;
	unsigned int *cnt_2_dec_pw, *cnt_2_inc_pw;
	unsigned int memo_size, i;


	sum_2_decrease = 0;
	sum_2_increase = 0;

	cnt_2_dec_pw = servo_data->spike_count_memo->spike_count_2_decrease_pw;
	cnt_2_inc_pw = servo_data->spike_count_memo->spike_count_2_increase_pw;
	memo_size = servo_data->spike_count_memo->memo_size;

	pthread_mutex_lock(&(servo_data->mutex));

	if (servo_data->pulse_change == 0)	// it is evaluating submit_servo_direction_and_speed_via_spike_count
	{				
		for (i = 0; i < memo_size; i++)
		{
 			sum_2_decrease = sum_2_decrease + cnt_2_dec_pw[i];
 			sum_2_increase = sum_2_increase + cnt_2_inc_pw[i];
		}
		for (i = memo_size-1; i > 0; i--)
		{
			cnt_2_dec_pw[i] = cnt_2_dec_pw[i-1];
			cnt_2_inc_pw[i] = cnt_2_inc_pw[i-1];
		}
		cnt_2_dec_pw[0] = 0;		// submit_servo_direction_and_speed_via_spike_count will increase it. 
		cnt_2_inc_pw[0] = 0;		// submit_servo_direction_and_speed_via_spike_count will increase it. 

		sum_2_increase = sum_2_increase*bias_2_increase;

		if (sum_2_decrease > sum_2_increase)  // do not handle if (sum_2_decrease == sum_2_increase)
		{
			if (((sum_2_decrease -  sum_2_increase) / sum_2_decrease) > threshold)
				servo_data->pulse_target = servo_data->pulse_current - ((ServoPulse)(servo_data->range.pw_per_degree * degree_limitation));
		}
		if (sum_2_increase > sum_2_decrease)
		{
			if (((sum_2_increase -  sum_2_decrease) / sum_2_increase) > threshold)
				servo_data->pulse_target = servo_data->pulse_current + ((ServoPulse)(servo_data->range.pw_per_degree * degree_limitation));
		}
		servo_data->pulse_current = servo_data->pulse_target;	// pulse_current is the pulse width which is sent to servo in previous period.
		servo_data->pulse_command.pulse_width = (unsigned short int)65536 - (unsigned short int)((9216/10000.0)*10*servo_data->pulse_current);
	}
	else if (servo_data->pulse_change > 0)  // target pulse width given and it reaches that pulse width with servo_data->pulse_change with the servo pulsing frequency period.
	{
		servo_data->pulse_current += servo_data->pulse_change;
		if (servo_data->pulse_current > servo_data->pulse_target)
		{
			servo_data->pulse_current = servo_data->pulse_target;
		}
		servo_data->pulse_command.pulse_width = (unsigned short int)65536 - (unsigned short int)((9216/10000.0)*10*servo_data->pulse_current);
	}
	else if (servo_data->pulse_change < 0) 
	{
		servo_data->pulse_current += servo_data->pulse_change;
		if (servo_data->pulse_current < servo_data->pulse_target)
		{
			servo_data->pulse_current = servo_data->pulse_target;
		}
		servo_data->pulse_command.pulse_width = (unsigned short int)65536 - (unsigned short int)((9216/10000.0)*10*servo_data->pulse_current);		
	}
	pthread_mutex_unlock(&(servo_data->mutex));	
}



void evaluate_servo_pw_command_via_spike_count_with_limitation_thresholding_biasing_not_normalized(ServoData *servo_data, double degree_limitation, double threshold_2_decrease, double threshold_2_increase, double bias_2_decrease, double bias_2_increase, double bias_constant_2_decrease, double bias_constant_2_increase)
{
	double sum_2_decrease, sum_2_increase;
	unsigned int *cnt_2_dec_pw, *cnt_2_inc_pw;
	unsigned int memo_size, i;


	sum_2_decrease = 0;
	sum_2_increase = 0;

	cnt_2_dec_pw = servo_data->spike_count_memo->spike_count_2_decrease_pw;
	cnt_2_inc_pw = servo_data->spike_count_memo->spike_count_2_increase_pw;
	memo_size = servo_data->spike_count_memo->memo_size;

	pthread_mutex_lock(&(servo_data->mutex));

	if (servo_data->pulse_change == 0)	// it is evaluating submit_servo_direction_and_speed_via_spike_count
	{				
		for (i = 0; i < memo_size; i++)
		{
 			sum_2_decrease = sum_2_decrease + cnt_2_dec_pw[i];
 			sum_2_increase = sum_2_increase + cnt_2_inc_pw[i];
		}
		for (i = memo_size-1; i > 0; i--)
		{
			cnt_2_dec_pw[i] = cnt_2_dec_pw[i-1];
			cnt_2_inc_pw[i] = cnt_2_inc_pw[i-1];
		}
		cnt_2_dec_pw[0] = 0;		// submit_servo_direction_and_speed_via_spike_count will increase it. 
		cnt_2_inc_pw[0] = 0;		// submit_servo_direction_and_speed_via_spike_count will increase it. 

		sum_2_increase = sum_2_increase*bias_2_increase + bias_constant_2_increase;
		sum_2_decrease = sum_2_decrease*bias_2_decrease + bias_constant_2_decrease;

		if ((sum_2_decrease > sum_2_increase) && (sum_2_decrease > 0)) // do not handle if (sum_2_decrease == sum_2_increase)
		{
			if ((sum_2_decrease - sum_2_increase) >= threshold_2_decrease)
				servo_data->pulse_target = servo_data->pulse_current - ((ServoPulse)(servo_data->range.pw_per_degree * degree_limitation));
		}
		if ((sum_2_increase > sum_2_decrease) && (sum_2_increase > 0))
		{
			if ((sum_2_increase - sum_2_decrease) >= threshold_2_increase)
				servo_data->pulse_target = servo_data->pulse_current + ((ServoPulse)(servo_data->range.pw_per_degree * degree_limitation));
		}
		servo_data->pulse_current = servo_data->pulse_target;	// pulse_current is the pulse width which is sent to servo in previous period.
		servo_data->pulse_command.pulse_width = (unsigned short int)65536 - (unsigned short int)((9216/10000.0)*10*servo_data->pulse_current);
	}
	else if (servo_data->pulse_change > 0)  // target pulse width given and it reaches that pulse width with servo_data->pulse_change with the servo pulsing frequency period.
	{
		servo_data->pulse_current += servo_data->pulse_change;
		if (servo_data->pulse_current > servo_data->pulse_target)
		{
			servo_data->pulse_current = servo_data->pulse_target;
		}
		servo_data->pulse_command.pulse_width = (unsigned short int)65536 - (unsigned short int)((9216/10000.0)*10*servo_data->pulse_current);
	}
	else if (servo_data->pulse_change < 0) 
	{
		servo_data->pulse_current += servo_data->pulse_change;
		if (servo_data->pulse_current < servo_data->pulse_target)
		{
			servo_data->pulse_current = servo_data->pulse_target;
		}
		servo_data->pulse_command.pulse_width = (unsigned short int)65536 - (unsigned short int)((9216/10000.0)*10*servo_data->pulse_current);		
	}
	pthread_mutex_unlock(&(servo_data->mutex));	
}


void evaluate_servo_pw_command_via_spike_count_with_limitation_thresholding_biasing_not_normalized_one_side(ServoData *servo_data, double degree_limitation, double threshold_2_decrease, double threshold_2_increase, double bias_2_decrease, double bias_2_increase, double bias_constant_2_decrease, double bias_constant_2_increase, bool only_decrease, bool only_increase)
{
	double sum_2_decrease, sum_2_increase;
	unsigned int *cnt_2_dec_pw, *cnt_2_inc_pw;
	unsigned int memo_size, i;


	sum_2_decrease = 0;
	sum_2_increase = 0;

	cnt_2_dec_pw = servo_data->spike_count_memo->spike_count_2_decrease_pw;
	cnt_2_inc_pw = servo_data->spike_count_memo->spike_count_2_increase_pw;
	memo_size = servo_data->spike_count_memo->memo_size;

	pthread_mutex_lock(&(servo_data->mutex));

	if (servo_data->pulse_change == 0)	// it is evaluating submit_servo_direction_and_speed_via_spike_count
	{				
		for (i = 0; i < memo_size; i++)
		{
 			sum_2_decrease = sum_2_decrease + cnt_2_dec_pw[i];
 			sum_2_increase = sum_2_increase + cnt_2_inc_pw[i];
		}
		for (i = memo_size-1; i > 0; i--)
		{
			cnt_2_dec_pw[i] = cnt_2_dec_pw[i-1];
			cnt_2_inc_pw[i] = cnt_2_inc_pw[i-1];
		}
		cnt_2_dec_pw[0] = 0;		// submit_servo_direction_and_speed_via_spike_count will increase it. 
		cnt_2_inc_pw[0] = 0;		// submit_servo_direction_and_speed_via_spike_count will increase it. 

		sum_2_increase = sum_2_increase*bias_2_increase + bias_constant_2_increase;
		sum_2_decrease = sum_2_decrease*bias_2_decrease + bias_constant_2_decrease;

		if (only_decrease)  // move only toward one side
		{
			if ((sum_2_decrease > sum_2_increase) && (sum_2_decrease > 0)) // do not handle if (sum_2_decrease == sum_2_increase)
			{
				if ((sum_2_decrease - sum_2_increase) >= threshold_2_decrease)
					servo_data->pulse_target = servo_data->pulse_current - ((ServoPulse)(servo_data->range.pw_per_degree * degree_limitation));
			}			
		} 
		else if (only_increase) // move only toward one side
		{
			if ((sum_2_increase > sum_2_decrease) && (sum_2_increase > 0))
			{
				if ((sum_2_increase - sum_2_decrease) >= threshold_2_increase)
				servo_data->pulse_target = servo_data->pulse_current + ((ServoPulse)(servo_data->range.pw_per_degree * degree_limitation));
			}
		}
		else // move toward the side with higher spiking
		{
			if ((sum_2_decrease > sum_2_increase) && (sum_2_decrease > 0)) // do not handle if (sum_2_decrease == sum_2_increase)
			{
				if ((sum_2_decrease - sum_2_increase) >= threshold_2_decrease)
					servo_data->pulse_target = servo_data->pulse_current - ((ServoPulse)(servo_data->range.pw_per_degree * degree_limitation));
			}
			if ((sum_2_increase > sum_2_decrease) && (sum_2_increase > 0))
			{
				if ((sum_2_increase - sum_2_decrease) >= threshold_2_increase)
					servo_data->pulse_target = servo_data->pulse_current + ((ServoPulse)(servo_data->range.pw_per_degree * degree_limitation));
			}			
		}

		servo_data->pulse_current = servo_data->pulse_target;	// pulse_current is the pulse width which is sent to servo in previous period.
		servo_data->pulse_command.pulse_width = (unsigned short int)65536 - (unsigned short int)((9216/10000.0)*10*servo_data->pulse_current);
	}
	else if (servo_data->pulse_change > 0)  // target pulse width given and it reaches that pulse width with servo_data->pulse_change with the servo pulsing frequency period.
	{
		servo_data->pulse_current += servo_data->pulse_change;
		if (servo_data->pulse_current > servo_data->pulse_target)
		{
			servo_data->pulse_current = servo_data->pulse_target;
		}
		servo_data->pulse_command.pulse_width = (unsigned short int)65536 - (unsigned short int)((9216/10000.0)*10*servo_data->pulse_current);
	}
	else if (servo_data->pulse_change < 0) 
	{
		servo_data->pulse_current += servo_data->pulse_change;
		if (servo_data->pulse_current < servo_data->pulse_target)
		{
			servo_data->pulse_current = servo_data->pulse_target;
		}
		servo_data->pulse_command.pulse_width = (unsigned short int)65536 - (unsigned short int)((9216/10000.0)*10*servo_data->pulse_current);		
	}
	pthread_mutex_unlock(&(servo_data->mutex));	
}



void evaluate_servo_pw_command_via_spike_count_with_limitation_count_thresholding(ServoData *servo_data, double degree_limitation, double threshold)
{
	double sum_2_decrease, sum_2_increase;
	unsigned int *cnt_2_dec_pw, *cnt_2_inc_pw;
	unsigned int memo_size, i;


	sum_2_decrease = 0;
	sum_2_increase = 0;

	cnt_2_dec_pw = servo_data->spike_count_memo->spike_count_2_decrease_pw;
	cnt_2_inc_pw = servo_data->spike_count_memo->spike_count_2_increase_pw;
	memo_size = servo_data->spike_count_memo->memo_size;

	pthread_mutex_lock(&(servo_data->mutex));

	if (servo_data->pulse_change == 0)	// it is evaluating submit_servo_direction_and_speed_via_spike_count
	{				
		for (i = 0; i < memo_size; i++)
		{
 			sum_2_decrease = sum_2_decrease + cnt_2_dec_pw[i];
 			sum_2_increase = sum_2_increase + cnt_2_inc_pw[i];
		}
		for (i = memo_size-1; i > 0; i--)
		{
			cnt_2_dec_pw[i] = cnt_2_dec_pw[i-1];
			cnt_2_inc_pw[i] = cnt_2_inc_pw[i-1];
		}
		cnt_2_dec_pw[0] = 0;		// submit_servo_direction_and_speed_via_spike_count will increase it. 
		cnt_2_inc_pw[0] = 0;		// submit_servo_direction_and_speed_via_spike_count will increase it. 

		if (sum_2_decrease > sum_2_increase)  // do not handle if (sum_2_decrease == sum_2_increase)
		{
			if (sum_2_decrease >= threshold)
				servo_data->pulse_target = servo_data->pulse_current - ((ServoPulse)(servo_data->range.pw_per_degree * degree_limitation));
		}
		if (sum_2_increase > sum_2_decrease)
		{
			if (sum_2_increase  >= threshold)
				servo_data->pulse_target = servo_data->pulse_current + ((ServoPulse)(servo_data->range.pw_per_degree * degree_limitation));
		}
		servo_data->pulse_current = servo_data->pulse_target;	// pulse_current is the pulse width which is sent to servo in previous period.
		servo_data->pulse_command.pulse_width = (unsigned short int)65536 - (unsigned short int)((9216/10000.0)*10*servo_data->pulse_current);
	}
	else if (servo_data->pulse_change > 0)  // target pulse width given and it reaches that pulse width with servo_data->pulse_change with the servo pulsing frequency period.
	{
		servo_data->pulse_current += servo_data->pulse_change;
		if (servo_data->pulse_current > servo_data->pulse_target)
		{
			servo_data->pulse_current = servo_data->pulse_target;
		}
		servo_data->pulse_command.pulse_width = (unsigned short int)65536 - (unsigned short int)((9216/10000.0)*10*servo_data->pulse_current);
	}
	else if (servo_data->pulse_change < 0) 
	{
		servo_data->pulse_current += servo_data->pulse_change;
		if (servo_data->pulse_current < servo_data->pulse_target)
		{
			servo_data->pulse_current = servo_data->pulse_target;
		}
		servo_data->pulse_command.pulse_width = (unsigned short int)65536 - (unsigned short int)((9216/10000.0)*10*servo_data->pulse_current);		
	}
	pthread_mutex_unlock(&(servo_data->mutex));	
}

void get_servo_pw_val_bytes(ServoData *servo_data, unsigned char *low_byte, unsigned char *high_byte)
{
	pthread_mutex_lock(&(servo_data->mutex));
	*low_byte = servo_data->pulse_command.byte[0];
	*high_byte = servo_data->pulse_command.byte[1];
	pthread_mutex_unlock(&(servo_data->mutex));	
}

void write_servo_position_val(ServoData *servo_data, unsigned char low_byte, unsigned char high_byte)
{
	pthread_mutex_lock(&(servo_data->mutex));
	servo_data->position.byte[0] = low_byte;
	servo_data->position.byte[1] = high_byte;
	pthread_mutex_unlock(&(servo_data->mutex));	
}

void get_servo_position_val(ServoData *servo_data, ServoPosition *servo_position)
{
	pthread_mutex_lock(&(servo_data->mutex));
	*servo_position = servo_data->position.position;
	pthread_mutex_unlock(&(servo_data->mutex));	
}

void write_servo_pw_adc_ranges(ServoData *servo_data, ServoPulse zero_degree_pulse, ServoPulse ninety_degree_pulse, ServoPosition zero_degree_adc_val, ServoPosition ninety_degree_adc_val)
{
	pthread_mutex_lock(&(servo_data->mutex));
	servo_data->range.pulse_width_0_degree = zero_degree_pulse;
	servo_data->range.pulse_width_90_degree = ninety_degree_pulse;
	servo_data->range.position_0_degree = zero_degree_adc_val;
	servo_data->range.position_90_degree = ninety_degree_adc_val;
	servo_data->range.radian_per_pos_quanta = M_PI_2 / (servo_data->range.position_90_degree - servo_data->range.position_0_degree);
	servo_data->range.pw_per_degree = (servo_data->range.pulse_width_90_degree - servo_data->range.pulse_width_0_degree)/90.0;
	pthread_mutex_unlock(&(servo_data->mutex));	
}

void write_servo_0_degree_adc_val(ServoData *servo_data, ServoPosition zero_degree_adc_val)
{
	if (zero_degree_adc_val > servo_data->range.position_90_degree)
		servo_data->range.position_90_degree = zero_degree_adc_val;
	servo_data->range.position_0_degree = zero_degree_adc_val;
	servo_data->range.radian_per_pos_quanta = M_PI_2 / (servo_data->range.position_90_degree - servo_data->range.position_0_degree);
}

void write_servo_90_degree_adc_val(ServoData *servo_data, ServoPosition ninety_degree_adc_val)
{
	if (ninety_degree_adc_val < servo_data->range.position_0_degree)
		servo_data->range.position_0_degree = ninety_degree_adc_val;
	servo_data->range.position_90_degree = ninety_degree_adc_val;
	servo_data->range.radian_per_pos_quanta = M_PI_2 / (servo_data->range.position_90_degree - servo_data->range.position_0_degree);
}

void init_servo_angles_for_sample_averaging(ServoData *servo, ServoAngle initial_angle, unsigned int prev_angle_memo_size)
{
	unsigned int i;
	servo->angle_memo_4_averaging = g_new0(ServoAngleMemo, 1);
	servo->angle_memo_4_averaging->angles = g_new0(ServoAngle, prev_angle_memo_size);
	servo->angle_memo_4_averaging->memo_size = prev_angle_memo_size;	
	for (i = 0; i < prev_angle_memo_size; i++)
		servo->angle_memo_4_averaging->angles[i] = initial_angle;
}

void init_servo_spike_count_memo(ServoData *servo, unsigned int memo_size)
{
	servo->spike_count_memo = g_new0(ServoSpikeCountMemo, 1);
	servo->spike_count_memo->spike_count_2_decrease_pw = g_new0(unsigned int, memo_size);
	servo->spike_count_memo->spike_count_2_increase_pw = g_new0(unsigned int, memo_size);
	servo->spike_count_memo->memo_size = memo_size;	
}

void calculate_servo_angle_with_averaging(ServoData *servo)
{
	double last_angle, sum = 0.0;
	unsigned int i , memo_size;
	ServoAngle *prev_angles;

	memo_size = servo->angle_memo_4_averaging->memo_size;
	prev_angles = servo->angle_memo_4_averaging->angles;

	pthread_mutex_lock(&(servo->mutex));
	last_angle =  ((double)servo->position.position - (double)servo->range.position_0_degree) * servo->range.radian_per_pos_quanta;
	pthread_mutex_unlock(&(servo->mutex));
	prev_angles[0] = last_angle;
	for (i = 0; i < memo_size; i++)
 		sum =  sum + prev_angles[i];
	servo->current_angle = 	sum / ( (double) memo_size);

	for (i = memo_size-1; i > 0; i--)
	{
		prev_angles[i] = prev_angles[i-1];
	}
}

void clear_spike_count_memo_of_servo(ServoData *servo)
{
	unsigned int i , memo_size;
	unsigned int *spike_count_2_decrease_pw, *spike_count_2_increase_pw;

	memo_size = servo->spike_count_memo->memo_size;
	spike_count_2_decrease_pw = servo->spike_count_memo->spike_count_2_decrease_pw;
	spike_count_2_increase_pw = servo->spike_count_memo->spike_count_2_increase_pw;

	for (i = 0; i < memo_size; i++)
	{
		spike_count_2_decrease_pw[i] = 0;
		spike_count_2_increase_pw[i] = 0;
	}
}
