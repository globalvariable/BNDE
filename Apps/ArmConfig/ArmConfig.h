#ifndef ARM_CONFIG_H
#define ARM_CONFIGL_H

#define DIO_CTRL_STATUS_MSG_LEN			1
#define DIO_CTRL_STATUS_MSG_START_IDX	1
#define DIO_CTRL_CMD_MSG_LEN				1
#define DIO_CTRL_CMD_MSG_START_IDX		1

#define ROBOT_POSITION_MSG_LEN		2*THREE_DOF_ROBOT_NUM_OF_SERVOS
#define ROBOT_POSITION_MSG_START_IDX	DIO_CTRL_STATUS_MSG_START_IDX+DIO_CTRL_STATUS_MSG_LEN

#define ROBOT_PW_CMD_MSG_LEN		2*THREE_DOF_ROBOT_NUM_OF_SERVOS
#define ROBOT_PW_CMD_MSG_START_IDX	DIO_CTRL_CMD_MSG_START_IDX+DIO_CTRL_CMD_MSG_LEN

#define RX_BUFF_SIZE				1 + DIO_CTRL_STATUS_MSG_LEN + (2*THREE_DOF_ROBOT_NUM_OF_SERVOS) + 2		// 0xFF + DIO_CTRL_STATUS (1 BYTE) + SERVO_0_POSITION_L_BYTE + SERVO_0_POSITION_H_BYTE + SERVO_1_POSITION_L_BYTE + SERVO_1_ POSITION_H_BYTE + SERVO_2_POSITION_L_BYTE + SERVO_2_ POSITION_H_BYTE + 0xFF + 0xFF

#define PW_TX_BUFF_SIZE			1 + DIO_CTRL_CMD_MSG_LEN + (2*THREE_DOF_ROBOT_NUM_OF_SERVOS) + 2		// 'P' + DIO_CTRL_COMND (1 BYTE) + SERVO_0_PW_L_BYTE + SERVO_0_PW_H_BYTE + SERVO_1_PW_L_BYTE + SERVO_1_ PW_H_BYTE + SERVO_2_PW_L_BYTE + SERVO_2_ PW_H_BYTE + 0xFF + 0xFF	

#define ADC_TX_BUFF_SIZE			1 + DIO_CTRL_CMD_MSG_LEN + 2		// 'A' + DIO_CTRL_COMND (1 BYTE) + 0xFF + 0xFF	





#define BASE_SERVO_0_DEGREE_PULSE		2104
#define BASE_SERVO_90_DEGREE_PULSE		1537
#define BASE_SERVO_0_DEGREE_ADC_VAL		35
#define BASE_SERVO_90_DEGREE_ADC_VAL	310

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




#include "Gui.h"
#include "ArmConfigRtTask.h"




#endif