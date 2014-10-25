#ifndef RS232_DATA_H
#define RS232_DATA_H



typedef struct __RS232Data RS232Data;
typedef struct __RS232CompData RS232CompData;

#include <stdbool.h>
#include <gtk/gtk.h>
#include "../../../BlueSpike/TimeStamp.h"
#include "../../../BlueSpike/Library/Misc/Misc.h"

struct __RS232CompData
{
	TimeStamp		tx_period;
	TimeStamp		rx_period;
};

struct __RS232Data
{
	unsigned int		num_of_comps;
	RS232CompData	*comp_data;
};


RS232Data* allocate_rs232_data(RS232Data* data);
RS232Data* deallocate_rs232_data(RS232Data* data);
bool add_component_to_rs232_data(RS232Data *data, TimeStamp tx_period, TimeStamp rx_period);




#endif
