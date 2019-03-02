#include "Gui.h"



void create_gui_handler(RtTasksData *rt_tasks_data, Gui2ExpCtrlMsg *msgs_gui_2_exp_ctrl, ExpCtrlParadigmRobotReach *exp_ctrl_paradigm, ClassifiedExpHistory* classified_trial_history, ExpCtrl2GuiMsg *msgs_exp_ctrl_2_gui, ExpStatusHistory *trial_status_history)
{
	GtkWidget *window, *vbox, *tabs;

 	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
  	gtk_window_set_default_size(GTK_WINDOW(window), 500, 500);
  	gtk_window_set_title(GTK_WINDOW(window), "BMIExpController - ExpControl");
  	gtk_window_set_deletable(GTK_WINDOW(window), FALSE);
  	gtk_window_set_resizable(GTK_WINDOW(window), FALSE);
  	gtk_container_set_border_width(GTK_CONTAINER(window), 10);

  	vbox = gtk_vbox_new(TRUE, 0);
	gtk_container_add(GTK_CONTAINER(window), vbox);

	tabs = gtk_notebook_new ();
	gtk_notebook_set_tab_pos (GTK_NOTEBOOK (tabs), GTK_POS_TOP);
        gtk_box_pack_start(GTK_BOX(vbox),tabs, TRUE, TRUE, 0);

	if (!create_exp_control_tab(tabs, rt_tasks_data, msgs_gui_2_exp_ctrl, exp_ctrl_paradigm, classified_trial_history, msgs_exp_ctrl_2_gui, trial_status_history))
		print_message(ERROR_MSG ,"BMIExpController", "Gui", "create_gui", "create_exp_control_gui().");

	gtk_widget_show_all(window);
}

