#ifndef DATAFORMAT_V1_H
#define DATAFORMAT_V1_H

#include <stdarg.h>
#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <gtk/gtk.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <locale.h>

#include "../../../../../Library/Misc/Misc.h"
#include "../../ProstheticCtrlParadigm.h"
#include "../../../../../Library/Status/ProstheticCtrlStatusHistory.h"
#include "../../../../../Library/Robot/ThreeDofRobotHistory.h"

int create_main_directory_v1(int num, ...);
int create_data_directory_v1(int num, ...);
int fclose_all_data_files_v1(int num, ...);
int delete_data_directory_v1(int num, ...);
int write_to_data_files_v1(int num, ...);

int write_notes_to_files_v1(int num, ...);
int write_additional_notes_to_files_v1(int num, ...);







#endif
