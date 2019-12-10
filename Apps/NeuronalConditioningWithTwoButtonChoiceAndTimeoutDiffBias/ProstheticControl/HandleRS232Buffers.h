#ifndef HANDLE_RS232_BUFFERS_H
#define HANDLE_RS232_BUFFERS_H

#include <gtk/gtk.h>
#include <stdbool.h>
#include <rtai_shm.h>
#include <rtai_nam2num.h>
#include "../../../Library/RS232/RS232Handler.h"
#include "../../../Library/Robot/ThreeDofRobot.h"
#include "../../../Library/Status/ProstheticCtrlStatusHistory.h"
#include "../../../Library/Robot/ThreeDofRobotHistory.h"
#include "ProstheticCtrlParadigm.h"

bool init_rs232_buffers(ThreeDofRobot *robot_arm, SEM **dio_ctrl_rx_buff_sem, SEM **dio_ctrl_tx_buff_sem, DioCtrlRxShm **dio_ctrl_rx_buff_shm, DioCtrlTxShm **dio_ctrl_tx_buff_shm, TimeStamp current_time);
bool handle_dio_ctrl_tx_shm_and_send_rs232_adc_command(TimeStamp current_time);
bool handle_dio_ctrl_tx_shm_and_send_rs232_pulse_width_command(TimeStamp current_time, ThreeDofRobotPulseHistory *robot_pulse_history, double max_servo_angle_change, double spike_count_threshold_left, double spike_count_threshold_right, double left_spike_multiplier, double right_spike_multiplier, double left_bias_constant, double right_bias_constant, ProstheticCtrlParadigmRobotReach *prosthetic_ctrl_paradigm);
bool handle_rs232_rx_buffer_and_write_to_dio_ctrl_rx_shm(void);









#endif
