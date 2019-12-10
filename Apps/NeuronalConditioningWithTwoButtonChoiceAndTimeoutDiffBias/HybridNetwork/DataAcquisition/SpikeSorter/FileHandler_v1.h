#ifndef FILE_HANDLER_V1_H
#define FILE_HANDLER_V1_H

#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../../../../../Library/Misc/Misc.h"
#include "../MwaConfig.h"
#include "../TemplateMatching.h"
#include "../../HybridNetworkData.h"
#include "../../../../../Library/Izlib/Network/Network.h"
#include <locale.h>


int write_template_matching_data_v1(int num, ...);
int read_template_matching_data_v1(int num, ...);






#endif
