#include "GuiProstheticControl.h"

static RtTasksData *static_rt_tasks_data = NULL;

static Gui2ProstheticCtrlMsg *static_msgs_gui_2_prosthetic_ctrl;    
static ProstheticCtrl2GuiMsg *static_msgs_prosthetic_ctrl_2_gui;

static ThreeDofRobot *static_robot_arm = NULL;
static ProstheticCtrlParadigmRobotReach *static_prosthetic_ctrl_paradigm = NULL;

static ProstheticCtrlStatusHistory* static_prosthetic_ctrl_status_history = NULL;
static ThreeDofRobotAngleHistory *static_robot_angle_history = NULL;
static ThreeDofRobotPulseHistory *static_robot_pulse_history = NULL;

static GtkWidget *entry_left_target_left_bias_constant;
static GtkWidget *entry_left_target_right_bias_constant;

static GtkWidget *entry_right_target_left_bias_constant;
static GtkWidget *entry_right_target_right_bias_constant;

static GtkWidget *entry_left_spike_multiplier;
static GtkWidget *entry_right_spike_multiplier;
static GtkWidget *btn_submit_spike_multiplier;

static GtkWidget *entry_spike_threshold_left;
static GtkWidget *entry_spike_threshold_right;
static GtkWidget *btn_submit_spike_threshold;
static GtkWidget *btn_only_one_side;

static GtkWidget *btn_select_directory_to_save;
static GtkWidget *btn_create_recording_folder;

static void submit_spike_multiplier_button_func (void);

static void submit_spike_threshold_button_func (void);

static void only_one_side_button_func (void);

static void create_recording_folder_button_func (void);

static void set_directory_btn_select_directory_to_save(void);



static gboolean timeout_callback(gpointer graph);

bool create_prosthetic_control_tab(GtkWidget *tabs, RtTasksData *rt_tasks_data, Gui2ProstheticCtrlMsg *msgs_gui_2_prosthetic_ctrl, ProstheticCtrl2GuiMsg *msgs_prosthetic_ctrl_2_gui, ThreeDofRobot *robot_arm, ProstheticCtrlParadigmRobotReach *prosthetic_ctrl_paradigm, ProstheticCtrlStatusHistory* prosthetic_ctrl_status_history, ThreeDofRobotAngleHistory *robot_angle_history, ThreeDofRobotPulseHistory *robot_pulse_history)
{
	GtkWidget *frame, *frame_label, *hbox, *table, *vbox, *lbl;

	static_rt_tasks_data = rt_tasks_data;

	static_robot_arm = robot_arm;
	static_prosthetic_ctrl_paradigm = prosthetic_ctrl_paradigm;

	static_msgs_gui_2_prosthetic_ctrl = msgs_gui_2_prosthetic_ctrl;
	static_msgs_prosthetic_ctrl_2_gui = msgs_prosthetic_ctrl_2_gui;

	static_prosthetic_ctrl_status_history = prosthetic_ctrl_status_history;
	static_robot_angle_history = robot_angle_history;
	static_robot_pulse_history = robot_pulse_history;

        frame = gtk_frame_new ("");
        frame_label = gtk_label_new ("     Mov Obj Handler    ");      
   
        gtk_notebook_append_page (GTK_NOTEBOOK (tabs), frame, frame_label);  

 	hbox = gtk_hbox_new(TRUE, 0);
        gtk_container_add (GTK_CONTAINER (frame), hbox);

	table = gtk_table_new(2 ,3,TRUE);   // 2 rows 3 columns
	gtk_box_pack_start(GTK_BOX(hbox),table, TRUE,TRUE,0);

	vbox = gtk_vbox_new(FALSE, 0);
	gtk_table_attach_defaults(GTK_TABLE(table), vbox, 0,1, 0, 3);  // column 0-1, row 0-3

	hbox = gtk_hbox_new(FALSE, 0);
	gtk_box_pack_start(GTK_BOX(vbox),hbox, FALSE,FALSE,0);


        lbl = gtk_label_new("Left Target Left Bias Constant : ");
        gtk_box_pack_start(GTK_BOX(hbox),lbl, TRUE,TRUE, 0);

	entry_left_target_left_bias_constant = gtk_entry_new();
        gtk_box_pack_start(GTK_BOX(hbox), entry_left_target_left_bias_constant, FALSE, FALSE, 0);
	gtk_widget_set_size_request(entry_left_target_left_bias_constant, 50, 25);
	gtk_entry_set_text(GTK_ENTRY(entry_left_target_left_bias_constant), "0.0");

	hbox = gtk_hbox_new(FALSE, 0);
	gtk_box_pack_start(GTK_BOX(vbox),hbox, FALSE,FALSE,0);

        lbl = gtk_label_new("Left Target Right Bias Constant : ");
        gtk_box_pack_start(GTK_BOX(hbox),lbl, TRUE,TRUE, 0);

	entry_left_target_right_bias_constant = gtk_entry_new();
        gtk_box_pack_start(GTK_BOX(hbox), entry_left_target_right_bias_constant, FALSE, FALSE, 0);
	gtk_widget_set_size_request(entry_left_target_right_bias_constant, 50, 25);
	gtk_entry_set_text(GTK_ENTRY(entry_left_target_right_bias_constant), "0.0");


        gtk_box_pack_start(GTK_BOX(vbox),gtk_hseparator_new(), FALSE,FALSE, 5);


	hbox = gtk_hbox_new(FALSE, 0);
	gtk_box_pack_start(GTK_BOX(vbox),hbox, FALSE,FALSE,0);

        lbl = gtk_label_new("Right Target Left Bias Constant : ");
        gtk_box_pack_start(GTK_BOX(hbox),lbl, TRUE,TRUE, 0);

	entry_right_target_left_bias_constant = gtk_entry_new();
        gtk_box_pack_start(GTK_BOX(hbox), entry_right_target_left_bias_constant, FALSE, FALSE, 0);
	gtk_widget_set_size_request(entry_right_target_left_bias_constant, 50, 25);
	gtk_entry_set_text(GTK_ENTRY(entry_right_target_left_bias_constant), "0.0");

	hbox = gtk_hbox_new(FALSE, 0);
	gtk_box_pack_start(GTK_BOX(vbox),hbox, FALSE,FALSE,0);

        lbl = gtk_label_new("Right Target Right Bias Constant : ");
        gtk_box_pack_start(GTK_BOX(hbox),lbl, TRUE,TRUE, 0);

	entry_right_target_right_bias_constant = gtk_entry_new();
        gtk_box_pack_start(GTK_BOX(hbox), entry_right_target_right_bias_constant, FALSE, FALSE, 0);
	gtk_widget_set_size_request(entry_right_target_right_bias_constant, 50, 25);
	gtk_entry_set_text(GTK_ENTRY(entry_right_target_right_bias_constant), "0.0");

        gtk_box_pack_start(GTK_BOX(vbox),gtk_hseparator_new(), FALSE,FALSE, 5);

	hbox = gtk_hbox_new(FALSE, 0);
	gtk_box_pack_start(GTK_BOX(vbox),hbox, FALSE,FALSE,0);

        lbl = gtk_label_new("Left Multiplier : ");
        gtk_box_pack_start(GTK_BOX(hbox),lbl, TRUE,TRUE, 0);

	entry_left_spike_multiplier = gtk_entry_new();
        gtk_box_pack_start(GTK_BOX(hbox), entry_left_spike_multiplier, FALSE, FALSE, 0);
	gtk_widget_set_size_request(entry_left_spike_multiplier, 50, 25);
	gtk_entry_set_text(GTK_ENTRY(entry_left_spike_multiplier), "1.0");

	hbox = gtk_hbox_new(FALSE, 0);
	gtk_box_pack_start(GTK_BOX(vbox),hbox, FALSE,FALSE,0);

        lbl = gtk_label_new("Right Multiplier : ");
        gtk_box_pack_start(GTK_BOX(hbox),lbl, TRUE,TRUE, 0);

	entry_right_spike_multiplier = gtk_entry_new();
        gtk_box_pack_start(GTK_BOX(hbox), entry_right_spike_multiplier, FALSE, FALSE, 0);
	gtk_widget_set_size_request(entry_right_spike_multiplier, 50, 25);
	gtk_entry_set_text(GTK_ENTRY(entry_right_spike_multiplier), "1.0");

	hbox = gtk_hbox_new(FALSE, 0);
	gtk_box_pack_start(GTK_BOX(vbox),hbox, FALSE,FALSE,0);

	btn_submit_spike_multiplier = gtk_button_new_with_label("Submit Spike Multiplier");
	gtk_box_pack_start (GTK_BOX (hbox), btn_submit_spike_multiplier, FALSE, FALSE, 0);

	hbox = gtk_hbox_new(FALSE, 0);
	gtk_box_pack_start(GTK_BOX(vbox),hbox, FALSE,FALSE,0);

        lbl = gtk_label_new("");
        gtk_box_pack_start(GTK_BOX(hbox),lbl, TRUE,TRUE, 0);

	hbox = gtk_hbox_new(FALSE, 0);
	gtk_box_pack_start(GTK_BOX(vbox),hbox, FALSE,FALSE,0);

        lbl = gtk_label_new("Left Spike Count Threshold (100ms): ");
        gtk_box_pack_start(GTK_BOX(hbox),lbl, TRUE,TRUE, 0);

	entry_spike_threshold_left = gtk_entry_new();
        gtk_box_pack_start(GTK_BOX(hbox), entry_spike_threshold_left, FALSE, FALSE, 0);
	gtk_widget_set_size_request(entry_spike_threshold_left, 50, 25);
	gtk_entry_set_text(GTK_ENTRY(entry_spike_threshold_left), "1.0");

	hbox = gtk_hbox_new(FALSE, 0);
	gtk_box_pack_start(GTK_BOX(vbox),hbox, FALSE,FALSE,0);

        lbl = gtk_label_new("Right Spike Count Threshold (100ms): ");
        gtk_box_pack_start(GTK_BOX(hbox),lbl, TRUE,TRUE, 0);

	entry_spike_threshold_right = gtk_entry_new();
        gtk_box_pack_start(GTK_BOX(hbox), entry_spike_threshold_right, FALSE, FALSE, 0);
	gtk_widget_set_size_request(entry_spike_threshold_right, 50, 25);
	gtk_entry_set_text(GTK_ENTRY(entry_spike_threshold_right), "1.0");


	hbox = gtk_hbox_new(FALSE, 0);
	gtk_box_pack_start(GTK_BOX(vbox),hbox, FALSE,FALSE,0);

	btn_submit_spike_threshold = gtk_button_new_with_label("Submit Spike Threshold");
	gtk_box_pack_start (GTK_BOX (hbox), btn_submit_spike_threshold, FALSE, FALSE, 0);

	hbox = gtk_hbox_new(FALSE, 0);
	gtk_box_pack_start(GTK_BOX(vbox),hbox, FALSE,FALSE,0);

	btn_only_one_side = gtk_button_new_with_label("Only Move to Selected Side : OFF");
	gtk_box_pack_start (GTK_BOX (hbox), btn_only_one_side, FALSE, FALSE, 0);

	////////   LAST COLUMN
	vbox = gtk_vbox_new(FALSE, 0);
	gtk_table_attach_defaults(GTK_TABLE(table), vbox, 2,3, 0, 6);  // column 2-3, row 0-6

	hbox = gtk_hbox_new(FALSE, 0);
        gtk_box_pack_start(GTK_BOX(vbox),hbox, FALSE,FALSE,0);

   	hbox = gtk_hbox_new(FALSE, 0);
        gtk_box_pack_start(GTK_BOX(vbox),hbox, FALSE,FALSE, 0);  	      

  	btn_select_directory_to_save = gtk_file_chooser_button_new ("Select Directory", GTK_FILE_CHOOSER_ACTION_SELECT_FOLDER);
        gtk_box_pack_start(GTK_BOX(hbox), btn_select_directory_to_save, TRUE,TRUE,0);
	set_directory_btn_select_directory_to_save();

   	hbox = gtk_hbox_new(FALSE, 0);
        gtk_box_pack_start(GTK_BOX(vbox),hbox, FALSE,FALSE, 0);  	     

	btn_create_recording_folder = gtk_button_new_with_label("Create Recording Folder");
	gtk_box_pack_start (GTK_BOX (hbox), btn_create_recording_folder, TRUE, TRUE, 0);

        gtk_box_pack_start(GTK_BOX(vbox),gtk_hseparator_new(), FALSE,FALSE, 5);


	g_signal_connect(G_OBJECT(btn_submit_spike_multiplier), "clicked", G_CALLBACK(submit_spike_multiplier_button_func), NULL);

	g_signal_connect(G_OBJECT(btn_submit_spike_threshold), "clicked", G_CALLBACK(submit_spike_threshold_button_func), NULL);

	g_signal_connect(G_OBJECT(btn_only_one_side), "clicked", G_CALLBACK(only_one_side_button_func), NULL);

	g_signal_connect(G_OBJECT(btn_create_recording_folder), "clicked", G_CALLBACK(create_recording_folder_button_func), NULL);

	g_timeout_add(100, timeout_callback, NULL);		

	return TRUE;
}

static gboolean timeout_callback(gpointer graph)
{
	char *path_temp, *path;
	ProstheticCtrl2GuiMsgItem msg_item;
	static bool recording = FALSE;
	unsigned int recording_number;

	while (get_next_prosthetic_ctrl_2_gui_msg_buffer_item(static_msgs_prosthetic_ctrl_2_gui, &msg_item))
	{
		switch (msg_item.msg_type)
		{
			case PROSTHETIC_CTRL_2_GUI_MSG_START_RECORDING:
				path_temp = NULL; path = NULL;
				path_temp = gtk_file_chooser_get_uri (GTK_FILE_CHOOSER (btn_select_directory_to_save));
				path = &path_temp[7];   // since     uri returns file:///home/....	
				recording_number = msg_item.additional_data;
				if (!(*create_data_directory[DATA_FORMAT_VERSION])(3, path, static_rt_tasks_data->current_system_time, recording_number))	
				{
					print_message(ERROR_MSG ,"ProstheticControl", "GuiProstheticControl", "timeout_callback", " *create_data_directory().");		
					exit(1);
				}
				recording = TRUE;	
				if (!(*write_to_data_files[DATA_FORMAT_VERSION])(4, static_prosthetic_ctrl_status_history, static_robot_angle_history, static_robot_pulse_history, NULL))	// this function handles history buffers
				{
					print_message(ERROR_MSG ,"ProstheticControl", "GuiProstheticControl", "timeout_callback", " *write_to_data_files().");		
					exit(1);
				}				
				break;
			case PROSTHETIC_CTRL_2_GUI_MSG_STOP_RECORDING:
				if (!(*write_to_data_files[DATA_FORMAT_VERSION])(4, static_prosthetic_ctrl_status_history, static_robot_angle_history, static_robot_pulse_history, NULL))	// this function handles history buffers
				{
					print_message(ERROR_MSG ,"ProstheticControl", "GuiProstheticControl", "timeout_callback", " *write_to_data_files().");		
					exit(1);
				}	
				recording_number = msg_item.additional_data;
				if (! (*fclose_all_data_files[DATA_FORMAT_VERSION])(1, static_rt_tasks_data->current_system_time))	
				{
					print_message(ERROR_MSG ,"ProstheticControl", "GuiProstheticControl", "timeout_callback", " *fclose_all_data_file().");		
					exit(1);
				}
				recording = FALSE;	
				break;
			case PROSTHETIC_CTRL_2_GUI_MSG_CANCEL_RECORDING:
				path_temp = NULL; path = NULL;
				path_temp = gtk_file_chooser_get_uri (GTK_FILE_CHOOSER (btn_select_directory_to_save));
				path = &path_temp[7];   // since     uri returns file:///home/....		

				static_prosthetic_ctrl_status_history->buff_read_idx = static_prosthetic_ctrl_status_history->buff_write_idx;
				static_robot_angle_history->buff_read_idx = static_robot_angle_history->buff_write_idx;
				static_robot_pulse_history->buff_read_idx = static_robot_pulse_history->buff_write_idx;

				recording_number = msg_item.additional_data;
				if (! (*fclose_all_data_files[DATA_FORMAT_VERSION])(1, static_rt_tasks_data->current_system_time))	
				{
					print_message(ERROR_MSG ,"ProstheticControl", "GuiProstheticControl", "timeout_callback", "! *fclose_all_data_files().");
					exit(1);
				}
				if (! (*delete_data_directory[DATA_FORMAT_VERSION])(2, path, recording_number))
				{
					print_message(ERROR_MSG ,"ProstheticControl", "GuiProstheticControl", "timeout_callback", " *fdelete_all_data_files().");
					exit(1);
				}
				recording = FALSE;	
				break;
			case PROSTHETIC_CTRL_2_GUI_MSG_PROSTHETIC_CTRL_CONTROL_ENABLED:
				if (recording) // recording files are created when PROSTHETIC_CTRL_2_GUI_MSG_START_RECORDING comes. when recording is not iniatiated by START button in recording panel of ExpControl, PROSTHETIC_CTRL_2_GUI_MSG_START_RECORDING will not come. But PROSTHETIC_CTRL_2_GUI_MSG_PROSTHETIC_CTRL_CONTROL_ENABLED will come whenever a trial starts. if you try to write into paradigm data file using the below write_to_data_files function before creating a paradigm data file, there will appear a segmanetation fault. To prevent this problem, here is this if check.
				{
					if (!(*write_to_data_files[DATA_FORMAT_VERSION])(4, NULL, NULL, NULL, static_prosthetic_ctrl_paradigm))	// this function handles history buffers
					{
						print_message(ERROR_MSG ,"ProstheticControl", "GuiProstheticControl", "timeout_callback", " *write_to_data_files().");		
						exit(1);
					}
				}	
				break;
			default:
				return print_message(ERROR_MSG ,"ExpControl", "GuiProstheticControl", "timeout_callback", "switch (msg_item.msg_type) - default");
		}
	}
	if (recording)
	{
		if (!(*write_to_data_files[DATA_FORMAT_VERSION])(4, static_prosthetic_ctrl_status_history, static_robot_angle_history, static_robot_pulse_history, NULL))	// this function handles history buffers
		{
			print_message(ERROR_MSG ,"ProstheticControl", "GuiProstheticControl", "timeout_callback", " *write_to_data_files().");		
			exit(1);
		}			
	}
	else
	{
		static_prosthetic_ctrl_status_history->buff_read_idx = static_prosthetic_ctrl_status_history->buff_write_idx;
		static_robot_angle_history->buff_read_idx = static_robot_angle_history->buff_write_idx;
		static_robot_pulse_history->buff_read_idx = static_robot_pulse_history->buff_write_idx;	
	}
	return TRUE;
} 

static void create_recording_folder_button_func (void)
{
	unsigned int path_len;
	char *path_temp = NULL, *path = NULL;
	path_temp = gtk_file_chooser_get_uri (GTK_FILE_CHOOSER (btn_select_directory_to_save));
	path = &path_temp[7];   // since     uri returns file:///home/....	
	path_len = strlen(path_temp);
	if (strcmp(&(path_temp[path_len-8]),"EXP_DATA") == 0)
		return (void)print_message(ERROR_MSG ,"ProstheticControl", "GuiProstheticControl", "create_recording_folder_button_func", "Selected folder is /EXP_DATA main folder. Select a folder inside this folder.");				
	if ((*create_main_directory[DATA_FORMAT_VERSION])(3, path, static_prosthetic_ctrl_paradigm, static_robot_arm))		// record in last format version
	{
		
	}
	else
		print_message(ERROR_MSG ,"ProstheticControl", "GuiProstheticControl", "create_recording_folder_button_func", " *create_main_directory().");			
}

static void set_directory_btn_select_directory_to_save(void)
{
	char line[600];
	FILE *fp = NULL;
       	if ((fp = fopen("./path_initial_directory", "r")) == NULL)  
       	{ 
		print_message(ERROR_MSG ,"ProstheticControl", "GuiProstheticControl", "set_directory_btn_select_directory_to_save", "Couldn't find file: ./path_initial_directory.");
		print_message(ERROR_MSG ,"ProstheticControl", "GuiProstheticControl", "set_directory_btn_select_directory_to_save", "/home is loaded as initial direcoty to create data folder.");
		gtk_file_chooser_set_current_folder (GTK_FILE_CHOOSER (btn_select_directory_to_save),"/home");
       	}
       	else
       	{
		if (fgets(line, sizeof line, fp ) == NULL) 
		{ 
			print_message(ERROR_MSG ,"ProstheticControl", "GuiProstheticControl", "set_directory_btn_select_directory_to_save", "Couldn' t read ./path_initial_directory.");
			print_message(ERROR_MSG ,"ProstheticControl", "GuiProstheticControl", "set_directory_btn_select_directory_to_save", "/home is loaded as initial direcoty to create data folder.");
			gtk_file_chooser_set_current_folder (GTK_FILE_CHOOSER (btn_select_directory_to_save),"/home");
		}
		else
		{
			line[strlen(line)-16] = 0;   
			gtk_file_chooser_set_current_folder (GTK_FILE_CHOOSER (btn_select_directory_to_save),line);
		}
		fclose(fp); 		
	}  	 
}

static void submit_spike_multiplier_button_func (void)
{
	static_prosthetic_ctrl_paradigm->left_spike_multiplier = atof(gtk_entry_get_text(GTK_ENTRY(entry_left_spike_multiplier)));
	static_prosthetic_ctrl_paradigm->right_spike_multiplier = atof(gtk_entry_get_text(GTK_ENTRY(entry_right_spike_multiplier)));


	static_prosthetic_ctrl_paradigm->left_target_left_bias_constant_gui = atof(gtk_entry_get_text(GTK_ENTRY(entry_left_target_left_bias_constant)));
	static_prosthetic_ctrl_paradigm->left_target_right_bias_constant_gui = atof(gtk_entry_get_text(GTK_ENTRY(entry_left_target_right_bias_constant)));

	static_prosthetic_ctrl_paradigm->right_target_left_bias_constant_gui = atof(gtk_entry_get_text(GTK_ENTRY(entry_right_target_left_bias_constant)));
	static_prosthetic_ctrl_paradigm->right_target_right_bias_constant_gui = atof(gtk_entry_get_text(GTK_ENTRY(entry_right_target_right_bias_constant)));


}

static void submit_spike_threshold_button_func (void)
{
	static_prosthetic_ctrl_paradigm->spike_count_threshold_left = atof(gtk_entry_get_text(GTK_ENTRY(entry_spike_threshold_left)));
	static_prosthetic_ctrl_paradigm->spike_count_threshold_right = atof(gtk_entry_get_text(GTK_ENTRY(entry_spike_threshold_right)));
}

static void only_one_side_button_func (void)
{

	if (!static_prosthetic_ctrl_paradigm->only_move_toward_selected_side)
	{
		gtk_button_set_label (GTK_BUTTON(btn_only_one_side),"Only Move to Selected Side : ON");
		static_prosthetic_ctrl_paradigm->only_move_toward_selected_side = TRUE;
	}
	else
	{
		gtk_button_set_label (GTK_BUTTON(btn_only_one_side),"Only Move to Selected Side : OFF");
		static_prosthetic_ctrl_paradigm->only_move_toward_selected_side = FALSE;
	}	

}
