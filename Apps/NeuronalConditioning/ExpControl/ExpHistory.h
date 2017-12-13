#ifndef TRIAL_HISTORY_H
#define TRIAL_HISTORY_H


typedef struct __ExpHistory ExpHistory;
typedef struct __ClassifiedExpHistory ClassifiedExpHistory;

#include <math.h>
#include "ExpData.h"

struct __ExpHistory    
{
	ExpData				*history;
	unsigned int 			buff_write_idx;    
	unsigned int 			buffer_size;	
};

struct __ClassifiedExpHistory
{
	ExpHistory			*all_trials;
	ExpHistory			**trial_types;	
	unsigned int num_of_target_positions;
};


ExpHistory* allocate_trial_history(ExpHistory* hist, unsigned int buffer_size); 
ExpHistory* deallocate_trial_history(ExpHistory* hist); 

ClassifiedExpHistory* allocate_classified_trial_history(ClassifiedExpHistory* classified_hist, unsigned int buffer_size, unsigned int num_of_target_positions);
ClassifiedExpHistory* deallocate_classified_trial_history(ClassifiedExpHistory* classified_hist);
bool write_trial_data_to_classified_trial_history(ClassifiedExpHistory* classified_history, ExpData *trial_data);

ExpData* get_previous_trial_history_data_ptr(ExpHistory* hist, unsigned int prev_idx);	// prev_idx zero brings the current trial data. 
#endif
