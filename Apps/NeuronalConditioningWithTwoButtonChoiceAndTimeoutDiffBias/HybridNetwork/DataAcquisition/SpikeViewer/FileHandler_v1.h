#ifndef FILE_HANDLER_V1_H
#define FILE_HANDLER_V1_H

#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../../../../../Library/Misc/Misc.h"
#include "../SpikeThresholding.h"

int write_spike_thresholds_data_v1(int num, ...);
int read_spike_thresholds_data_v1(int num, ...);






#endif
