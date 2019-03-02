#include "Gui.h"

void create_gui_handler(RtTasksData *rt_tasks_data, Gui2ProstheticCtrlMsg *msgs_gui_2_prosthetic_ctrl, ProstheticCtrl2GuiMsg *msgs_prosthetic_ctrl_2_gui, ThreeDofRobot *robot_arm, ProstheticCtrlParadigmRobotReach *prosthetic_ctrl_paradigm, ProstheticCtrlStatusHistory* prosthetic_ctrl_status_history, ThreeDofRobotAngleHistory *robot_angle_history, ThreeDofRobotPulseHistory *robot_pulse_history)
{
	GtkWidget *window, *vbox, *tabs;

 	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
  	gtk_window_set_default_size(GTK_WINDOW(window), 1000, 1000);
  	gtk_window_set_title(GTK_WINDOW(window), "BMIExpController - ProstheticControl");
  	gtk_window_set_deletable(GTK_WINDOW(window), FALSE);
  	gtk_window_set_resizable(GTK_WINDOW(window), FALSE);
  	gtk_container_set_border_width(GTK_CONTAINER(window), 10);

  	vbox = gtk_vbox_new(TRUE, 0);
	gtk_container_add(GTK_CONTAINER(window), vbox);

	tabs = gtk_notebook_new ();
	gtk_notebook_set_tab_pos (GTK_NOTEBOOK (tabs), GTK_POS_TOP);
        gtk_box_pack_start(GTK_BOX(vbox),tabs, TRUE, TRUE, 0);

	if (!create_prosthetic_control_tab(tabs, rt_tasks_data, msgs_gui_2_prosthetic_ctrl, msgs_prosthetic_ctrl_2_gui, robot_arm, prosthetic_ctrl_paradigm, prosthetic_ctrl_status_history, robot_angle_history, robot_pulse_history))
		print_message(ERROR_MSG ,"BMIExpController", "Gui", "create_gui", "create_prosthetic_control_gui().");

	gtk_widget_show_all(window);
}
