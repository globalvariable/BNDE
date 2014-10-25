#ifndef DIO_CTRL_DATA_H
#define DIO_CTRL_DATA_H

typedef struct __DioCtrlInputCompTypeConstraints DioCtrlInputCompTypeConstraints;
typedef struct __DioCtrlInputCompTypeData DioCtrlInputCompTypeData;
typedef struct __DioCtrlOutputCompTypeData DioCtrlOutputCompTypeData;
typedef struct __DioCtrlData DioCtrlData;

#include <gtk/gtk.h>
#include <stdbool.h>
#include <string.h>
#include "../System/TimeStamp/TimeStamp.h"
#include "../Misc/Misc.h"
#include "DioCtrlComponentTypes.h"
#include "../Status/DioCtrlComponentStatus.h"

struct __DioCtrlInputCompTypeConstraints
{
	DioCtrlCompStatus	required_status_to_initiate_switching;		// high - low
	TimeStamp			max_high_status_duration;		
	TimeStamp			min_high_status_duration;	
	TimeStamp			max_low_status_duration;			
	TimeStamp			min_low_status_duration;		
	unsigned int			num_of_low_2_high_switch;
	unsigned int			num_of_high_2_low_switch;
};

struct __DioCtrlInputCompTypeData
{
	DioCtrlInputCompType					type;
	DioCtrlCompStatus					status;		// high - low
	unsigned int							low_2_high_switch_success;
	unsigned int							high_2_low_switch_success;
	DioCtrlInputCompTypeConstraints		constraints;
	bool 								enabled;
};

struct __DioCtrlOutputCompTypeData
{
	DioCtrlOutputCompType				type;
	DioCtrlCompStatus					status;		// high - low
	TimeStamp							high_status_duration;		
};

struct __DioCtrlData   // DO NOT BRING EXP ENVI STATUS HERE. IT IS KIND OF PRIVATE WHICH CAN BE CHANGED BY EXP ENVI HANDLER
{
	DioCtrlInputCompTypeData		*inp_comp_types;
	unsigned int					num_of_inp_comps;
	DioCtrlOutputCompTypeData	*outp_comp_types;
	unsigned int					num_of_outp_comps;
};

DioCtrlData* allocate_dio_ctrl_data(DioCtrlData* data);
DioCtrlData* deallocate_dio_ctrl_data(DioCtrlData* data);

bool get_input_component_type_idx_in_dio_ctrl_data(DioCtrlData *data, DioCtrlInputCompType comp_type, unsigned int *idx);
bool add_input_component_type_to_dio_ctrl_data(DioCtrlData *data, DioCtrlInputCompType comp_type, TimeStamp min_high_status_duration, TimeStamp max_high_status_duration, TimeStamp min_low_status_duration, TimeStamp max_low_status_duration, unsigned int num_of_low_2_high_switch, unsigned int num_of_high_2_low_switch, DioCtrlCompStatus required_status_to_initiate_switching, bool enabled);
bool is_input_component_type_used(DioCtrlData* data, DioCtrlInputCompType comp_type, bool *used);
bool submit_new_time_params_for_input_component_type(DioCtrlData *data, DioCtrlInputCompType comp_type, TimeStamp min_high_status_duration, TimeStamp max_high_status_duration, TimeStamp min_low_status_duration, TimeStamp max_low_status_duration);

bool submit_new_min_low_status_duration_for_input_component_type(DioCtrlData *data, DioCtrlInputCompType comp_type, TimeStamp min_low_status_duration);
bool submit_new_max_low_status_duration_for_input_component_type(DioCtrlData *data, DioCtrlInputCompType comp_type, TimeStamp max_low_status_duration);
bool submit_new_min_high_status_duration_for_input_component_type(DioCtrlData *data, DioCtrlInputCompType comp_type, TimeStamp min_high_status_duration);
bool submit_new_max_high_status_duration_for_input_component_type(DioCtrlData *data, DioCtrlInputCompType comp_type, TimeStamp max_high_status_duration);

bool get_output_component_type_idx_in_dio_ctrl_data(DioCtrlData *data, DioCtrlOutputCompType comp_type, unsigned int *idx);
bool add_output_component_type_to_dio_ctrl_data(DioCtrlData *data, DioCtrlOutputCompType comp_type, TimeStamp high_status_duration);
bool is_output_component_type_used(DioCtrlData* data, DioCtrlOutputCompType comp_type, bool *used);





#endif
