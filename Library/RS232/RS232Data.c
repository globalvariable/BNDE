#include "RS232Data.h"



RS232Data* allocate_rs232_data(RS232Data* data)
{
	if (data != NULL)
	{
		data = deallocate_rs232_data(data);
		data = allocate_rs232_data(data);
		return data;
	}  
	data = g_new0(RS232Data,1);
	print_message(INFO_MSG ,"ExperimentHandlers", "RS232Data", "allocate_rs232_data", "Created rs232_data.");
	return data;	
}
RS232Data* deallocate_rs232_data(RS232Data* data)
{
	if (data == NULL)
		return (RS232Data*)print_message(BUG_MSG ,"ExperimentHandlers", "RS232Data", "deallocate_rs232_data", "rs232_data == NULL.");    
	g_free(data->comp_data);
	g_free(data);
	print_message(INFO_MSG ,"ExperimentHandlers", "RS232Data", "deallocate_rs232_data", "Destroyed rs232_data.");
	return NULL;
}
bool add_component_to_rs232_data(RS232Data *data, TimeStamp tx_period, TimeStamp rx_period)
{
	RS232CompData	*lcl_comp_data;
	unsigned int i;

	lcl_comp_data = g_new0(RS232CompData, data->num_of_comps+1);
	for (i = 0; i < data->num_of_comps; i++)
	{
		lcl_comp_data[i] = data->comp_data[i];
	}
	lcl_comp_data[data->num_of_comps].tx_period = tx_period;
	lcl_comp_data[data->num_of_comps].rx_period = rx_period;
	g_free(data->comp_data);
	data->comp_data = lcl_comp_data;
	data->num_of_comps++;
	print_message(INFO_MSG ,"ExperimentHandlers", "RS232Data", "add_component_type_to_rs232_data", "Addition of RS232 component is successful.");	
	return TRUE;
}
