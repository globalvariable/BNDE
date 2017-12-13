#include "GuiDioControl.h"

static RtTasksData *static_rt_tasks_data = NULL;

static Gui2DioCtrlMsg *static_msgs_gui_2_dio_ctrl = NULL;    
static DioCtrl2GuiMsg *static_msgs_dio_ctrl_2_gui = NULL;  

static DioCtrlInputStatusHistory *static_dio_ctrl_input_status_history = NULL;
static DioCtrlOutputStatusHistory *static_dio_ctrl_output_status_history = NULL;

static DioCtrlParadigmRobotReach *static_dio_ctrl_paradigm = NULL;

static DioCtrlData *static_dio_ctrl_data = NULL;


static GtkWidget *entry_restrain_duration;
static GtkWidget *btn_submit_restrain_duration;

static GtkWidget *btn_restrain_on_off;

static GtkWidget *btn_select_directory_to_save;
static GtkWidget *btn_create_recording_folder;

static void create_recording_folder_button_func (void);

static void set_directory_btn_select_directory_to_save(void);

static void restrain_on_off_button_func (void);
static void submit_restrain_duration_button_func (void);

static gboolean timeout_callback(gpointer user_data) ;

bool create_dio_control_tab(GtkWidget *tabs, RtTasksData *rt_tasks_data, Gui2DioCtrlMsg *msgs_gui_2_dio_ctrl, DioCtrl2GuiMsg *msgs_dio_ctrl_2_gui, DioCtrlInputStatusHistory *dio_ctrl_input_status_history, DioCtrlOutputStatusHistory *dio_ctrl_output_status_history, DioCtrlData *dio_ctrl_data, DioCtrlParadigmRobotReach *dio_ctrl_paradigm)
{
	static_rt_tasks_data = rt_tasks_data;

	GtkWidget *frame, *frame_label, *hbox, *table, *vbox, *lbl;

	static_msgs_gui_2_dio_ctrl = msgs_gui_2_dio_ctrl;
	static_msgs_dio_ctrl_2_gui = msgs_dio_ctrl_2_gui;

	static_dio_ctrl_input_status_history = dio_ctrl_input_status_history;
	static_dio_ctrl_output_status_history = dio_ctrl_output_status_history;

	static_dio_ctrl_data = dio_ctrl_data;

	static_dio_ctrl_paradigm = dio_ctrl_paradigm;

        frame = gtk_frame_new ("");
        frame_label = gtk_label_new ("     Exp Envi Handler    ");      
   
        gtk_notebook_append_page (GTK_NOTEBOOK (tabs), frame, frame_label);  

 	hbox = gtk_hbox_new(TRUE, 0);
        gtk_container_add (GTK_CONTAINER (frame), hbox);

	table = gtk_table_new(2 ,3,TRUE);   // 2 rows 3 columns
	gtk_box_pack_start(GTK_BOX(hbox),table, TRUE,TRUE,0);

	vbox = gtk_vbox_new(FALSE, 0);
	gtk_table_attach_defaults(GTK_TABLE(table), vbox, 0,1, 0, 6);  // column 0-1, row 0-6

	hbox = gtk_hbox_new(FALSE, 0);
	gtk_box_pack_start(GTK_BOX(vbox),hbox, FALSE,FALSE,0);

	////////   LAST COLUMN
	vbox = gtk_vbox_new(FALSE, 0);
	gtk_table_attach_defaults(GTK_TABLE(table), vbox, 2,3, 0, 6);  // column 2-3, row 0-6

	hbox = gtk_hbox_new(FALSE, 0);
	gtk_box_pack_start(GTK_BOX(vbox),hbox, FALSE,FALSE,0);

	btn_submit_restrain_duration = gtk_button_new_with_label("Restrain Duration");
	gtk_box_pack_start (GTK_BOX (hbox), btn_submit_restrain_duration, FALSE, FALSE, 0);

	entry_restrain_duration = gtk_entry_new();
        gtk_box_pack_start(GTK_BOX(hbox), entry_restrain_duration, FALSE, FALSE, 0);
	gtk_widget_set_size_request(entry_restrain_duration, 50, 25);
	gtk_entry_set_text(GTK_ENTRY(entry_restrain_duration), "300");
	lbl = gtk_label_new("ms");	
     	gtk_box_pack_start(GTK_BOX(hbox),lbl, FALSE, FALSE, 0);

	hbox = gtk_hbox_new(FALSE, 0);
	gtk_box_pack_start(GTK_BOX(vbox),hbox, FALSE,FALSE,0);

	btn_restrain_on_off = gtk_button_new_with_label("Restrain: OFF");
	gtk_box_pack_start (GTK_BOX (hbox), btn_restrain_on_off, FALSE, FALSE, 0);

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

	g_signal_connect(G_OBJECT(btn_create_recording_folder), "clicked", G_CALLBACK(create_recording_folder_button_func), NULL);
	g_signal_connect(G_OBJECT(btn_restrain_on_off), "clicked", G_CALLBACK(restrain_on_off_button_func), NULL);
	g_signal_connect(G_OBJECT(btn_submit_restrain_duration), "clicked", G_CALLBACK(submit_restrain_duration_button_func), NULL);
	g_timeout_add(100, timeout_callback, NULL);		

	return TRUE;
}

static gboolean timeout_callback(gpointer user_data) 
{
	char *path_temp, *path;
	DioCtrl2GuiMsgItem msg_item;
	static bool recording = FALSE;
	unsigned int recording_number;

	while (get_next_dio_ctrl_2_gui_msg_buffer_item(static_msgs_dio_ctrl_2_gui, &msg_item))
	{
		switch (msg_item.msg_type)
		{
			case DIO_CTRL_2_GUI_MSG_START_RECORDING:
				path_temp = NULL; path = NULL;
				path_temp = gtk_file_chooser_get_uri (GTK_FILE_CHOOSER (btn_select_directory_to_save));
				path = &path_temp[7];   // since     uri returns file:///home/....	
				recording_number = msg_item.additional_data;
				if (!(*create_data_directory[MAX_NUMBER_OF_DATA_FORMAT_VER-1])(3, path, static_rt_tasks_data->current_system_time, recording_number))	
				{
					print_message(ERROR_MSG ,"DioControl", "GuiDioControl", "timeout_callback", " *create_data_directory().");		
					exit(1);
				}
				recording = TRUE;	
				if (!(*write_to_data_files[MAX_NUMBER_OF_DATA_FORMAT_VER-1])(2, static_dio_ctrl_input_status_history, static_dio_ctrl_output_status_history))	// this function handles history buffers
				{
					print_message(ERROR_MSG ,"DioControl", "GuiDioControl", "timeout_callback", " *write_to_data_files().");		
					exit(1);
				}				
				break;
			case DIO_CTRL_2_GUI_MSG_STOP_RECORDING:
				if (!(*write_to_data_files[MAX_NUMBER_OF_DATA_FORMAT_VER-1])(2, static_dio_ctrl_input_status_history, static_dio_ctrl_output_status_history))	// this function handles history buffers
				{
					print_message(ERROR_MSG ,"DioControl", "GuiDioControl", "timeout_callback", " *write_to_data_files().");		
					exit(1);
				}	
				recording_number = msg_item.additional_data;
				if (! (*fclose_all_data_files[MAX_NUMBER_OF_DATA_FORMAT_VER-1])(1, static_rt_tasks_data->current_system_time))	
				{
					print_message(ERROR_MSG ,"DioControl", "GuiDioControl", "timeout_callback", " *fclose_all_data_file().");		
					exit(1);
				}
				recording = FALSE;	
				break;
			case DIO_CTRL_2_GUI_MSG_CANCEL_RECORDING:
				path_temp = NULL; path = NULL;
				path_temp = gtk_file_chooser_get_uri (GTK_FILE_CHOOSER (btn_select_directory_to_save));
				path = &path_temp[7];   // since     uri returns file:///home/....		

				static_dio_ctrl_input_status_history->buff_read_idx = static_dio_ctrl_input_status_history->buff_write_idx;
				static_dio_ctrl_output_status_history->buff_read_idx = static_dio_ctrl_output_status_history->buff_write_idx;

				recording_number = msg_item.additional_data;
				if (! (*fclose_all_data_files[MAX_NUMBER_OF_DATA_FORMAT_VER-1])(1, static_rt_tasks_data->current_system_time))	
				{
					print_message(ERROR_MSG ,"DioControl", "GuiDioControl", "timeout_callback", "! *fclose_all_data_files().");
					exit(1);
				}
				if (! (*delete_data_directory[MAX_NUMBER_OF_DATA_FORMAT_VER-1])(2, path, recording_number))
				{
					print_message(ERROR_MSG ,"DioControl", "GuiDioControl", "timeout_callback", " *fdelete_all_data_files().");
					exit(1);
				}
				else
				recording = FALSE;	
				break;
			default:
				return print_message(ERROR_MSG ,"ExpControl", "GuiDioControl", "timeout_callback", "switch (msg_item.msg_type) - default");
		}
	}
	if (recording)
	{
		if (!(*write_to_data_files[MAX_NUMBER_OF_DATA_FORMAT_VER-1])(2, static_dio_ctrl_input_status_history, static_dio_ctrl_output_status_history))	// this function handles history buffers
		{
			print_message(ERROR_MSG ,"DioControl", "GuiDioControl", "timeout_callback", " *write_to_data_directory().");		
			exit(1);
		}			
	}
	else
	{
		static_dio_ctrl_input_status_history->buff_read_idx = static_dio_ctrl_input_status_history->buff_write_idx;
		static_dio_ctrl_output_status_history->buff_read_idx = static_dio_ctrl_output_status_history->buff_write_idx;		
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
		return (void)print_message(ERROR_MSG ,"DioControl", "GuiDioControl", "create_recording_folder_button_func", "Selected folder is /EXP_DATA main folder. Select a folder inside this folder.");				
	if ((*create_main_directory[MAX_NUMBER_OF_DATA_FORMAT_VER-1])(3, path,static_dio_ctrl_paradigm, static_dio_ctrl_data))		// record in last format version
	{
		
	}
	else
		print_message(ERROR_MSG ,"DioControl", "GuiDioControl", "create_recording_folder_button_func", " *create_main_directory().");			
}

static void set_directory_btn_select_directory_to_save(void)
{
	char line[600];
	FILE *fp = NULL;
       	if ((fp = fopen("./path_initial_directory", "r")) == NULL)  
       	{ 
		print_message(ERROR_MSG ,"DioControl", "GuiDioControl", "set_directory_btn_select_directory_to_save", "Couldn't find file: ./path_initial_directory.");
		print_message(ERROR_MSG ,"DioControl", "GuiDioControl", "set_directory_btn_select_directory_to_save", "/home is loaded as initial direcoty to create data folder.");
		gtk_file_chooser_set_current_folder (GTK_FILE_CHOOSER (btn_select_directory_to_save),"/home");
       	}
       	else
       	{
		if (fgets(line, sizeof line, fp ) == NULL) 
		{ 
			print_message(ERROR_MSG ,"DioControl", "GuiDioControl", "set_directory_btn_select_directory_to_save", "Couldn' t read ./path_initial_directory.");
			print_message(ERROR_MSG ,"DioControl", "GuiDioControl", "set_directory_btn_select_directory_to_save", "/home is loaded as initial direcoty to create data folder.");
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

static void restrain_on_off_button_func (void)
{
	if (static_dio_ctrl_paradigm->restrain_on)
	{
		static_dio_ctrl_paradigm->restrain_on = FALSE;
		gtk_button_set_label (GTK_BUTTON (btn_restrain_on_off),"Restrain: OFF");		
	}
	else
	{
		static_dio_ctrl_paradigm->restrain_on = TRUE;
		gtk_button_set_label (GTK_BUTTON (btn_restrain_on_off),"Restrain: ON");		
	}	
}


static void submit_restrain_duration_button_func (void)
{
	TimeStamp restrain_duration;
	unsigned int idx;

	restrain_duration = (TimeStamp)(1000000.0 * atof(gtk_entry_get_text(GTK_ENTRY(entry_restrain_duration))));

	if (! get_output_component_type_idx_in_dio_ctrl_data(static_dio_ctrl_data, DIO_CTRL_OUTPUT_COMPONENT_LEVER_SOLENOID, &idx))
		return (void)print_message(ERROR_MSG ,"DioControl", "GuiDioControl", "submit_restrain_duration_button_func", "! get_input_component_type_idx_in_dio_ctrl_data()");

	static_dio_ctrl_data->outp_comp_types[idx].high_status_duration = restrain_duration;

	return;
}
