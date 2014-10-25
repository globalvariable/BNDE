#ifndef INJECTION_CURRENT_DATA_H
#define INJECTION_CURRENT_DATA_H

typedef struct __InitializationCurrentParams InitializationCurrentParams;
typedef struct __CurrentNoiseParams CurrentNoiseParams;
typedef double InjectionCurrent;
typedef struct __NeuronCurrentTemplate NeuronCurrentTemplate;
typedef struct __CurrentPatternTemplate CurrentPatternTemplate;
typedef struct __CurrentTemplate CurrentTemplate;
typedef struct __CurrentPatternBuffer CurrentPatternBuffer;

#include <stdbool.h>
#include <gtk/gtk.h>
#include "../../../BlueSpike/Library/Misc/Misc.h"
#include "../Network/Network.h"
#include "../../../ExpControllers/Library/ExpStats/ExpStats.h"


struct __InitializationCurrentParams
{
	double		max_current;
	double		min_current;
	TimeStamp	duration;
	double		v_after_init;
	double		u_after_init;
};
struct __CurrentNoiseParams
{
	TimeStamp	noise_addition_interval;	
	double		noise_variance;	
};
struct __NeuronCurrentTemplate
{
	InitializationCurrentParams	init_params;
	CurrentNoiseParams 		noise_params;
	InjectionCurrent			*current;	
};

struct __CurrentPatternTemplate
{
	NeuronCurrentTemplate	***templates;
};

struct __CurrentTemplate
{
	ExpCurrentTemplate	*trial_current_template;
};

struct __CurrentPatternBuffer
{
	InjectionCurrent		***neuron_current_pattern;
	unsigned int			buff_write_idx;
};

struct __CurrentPatternBuffer
{
	InjectionCurrent		***neuron_current_pattern;
	unsigned int			buff_write_idx;
};

struct __InjectionCurrentData
{
	CurrentTemplate		*current_templates;
	CurrentPatternBuffer	*current_pattern_buffer;
};

InjectionCurrentData* allocate_injection_current_data(Network *network, ExpsData *trials_data, InjectionCurrentData* injection_current_data);
InjectionCurrentData* deallocate_injection_current_data(Network *network, ExpsData *trials_data, InjectionCurrentData* injection_current_data);
bool increment_current_template_types_in_current_pattern_templates(CurrentPatterns* current_patterns, TimeStamp sampling_interval);
bool submit_initialization_current(CurrentPatterns* current_patterns, unsigned int pattern_type_num, unsigned int layer, unsigned int neuron_group, unsigned int neuron_num, TimeStamp duration, double max_current);
bool submit_noise_params(CurrentPatterns* current_patterns, unsigned int pattern_type_num, unsigned int layer, unsigned int neuron_group, unsigned int neuron_num, TimeStamp	noise_addition_interval, double noise_variance);
bool submit_current_template_sample(CurrentPatterns* current_patterns, unsigned int pattern_type_num, unsigned int layer, unsigned int neuron_group, unsigned int neuron_num, TimeStamp sampling_time, double current);
bool interrogate_neuron_current_pattern_params(CurrentPatterns* current_patterns, unsigned int trial_num, unsigned int pattern_type_num, unsigned int layer, unsigned int neuron_group, unsigned int neuron_num);
bool get_current_pattern(CurrentPatterns* current_patterns, unsigned int trial_num, CurrentPattern **current_pattern);

#endif
