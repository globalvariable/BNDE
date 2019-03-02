#include "Gui.h"

static ThreeDofRobot *static_robot_arm = NULL;

static GtkWidget *entry_base_pulse_width;
static GtkWidget *entry_shoulder_pulse_width;
static GtkWidget *entry_elbow_pulse_width;
static GtkWidget *btn_submit_pulse_width;
static GtkWidget *entry_base_pulse_width_change;
static GtkWidget *entry_shoulder_pulse_width_change;
static GtkWidget *entry_elbow_pulse_width_change;
static GtkWidget *btn_increment_base_pulse_width;
static GtkWidget *btn_decrement_base_pulse_width;
static GtkWidget *lbl_base_0_degree_quanta;
static GtkWidget *btn_set_base_0_degree;
static GtkWidget *lbl_base_90_degree_quanta;
static GtkWidget *btn_set_base_90_degree;
static GtkWidget *lbl_base_degree_per_pos_quanta;
static GtkWidget *lbl_base_angle;
static GtkWidget *btn_increment_shoulder_pulse_width;
static GtkWidget *btn_decrement_shoulder_pulse_width;
static GtkWidget *lbl_shoulder_0_degree_quanta;
static GtkWidget *btn_set_shoulder_0_degree;
static GtkWidget *lbl_shoulder_90_degree_quanta;
static GtkWidget *btn_set_shoulder_90_degree;
static GtkWidget *lbl_shoulder_degree_per_pos_quanta;
static GtkWidget *lbl_shoulder_angle;
static GtkWidget *btn_increment_elbow_pulse_width;
static GtkWidget *btn_decrement_elbow_pulse_width;
static GtkWidget *lbl_elbow_0_degree_quanta;
static GtkWidget *btn_set_elbow_0_degree;
static GtkWidget *lbl_elbow_90_degree_quanta;
static GtkWidget *btn_set_elbow_90_degree;
static GtkWidget *lbl_elbow_degree_per_pos_quanta;
static GtkWidget *lbl_elbow_angle;

static GtkWidget *lbl_tip_height;
static GtkWidget *lbl_tip_lateral;
static GtkWidget *lbl_tip_depth;

static gboolean timeout_callback(gpointer none);

static void submit_pulse_width_button_func(void);
static void increment_base_pulse_width_button_func(void);
static void decrement_base_pulse_width_button_func(void);
static void set_base_0_degree_button_func(void);
static void set_base_90_degree_button_func(void);
static void increment_shoulder_pulse_width_button_func(void);
static void decrement_shoulder_pulse_width_button_func(void);
static void set_shoulder_0_degree_button_func(void);
static void set_shoulder_90_degree_button_func(void);
static void increment_elbow_pulse_width_button_func(void);
static void decrement_elbow_pulse_width_button_func(void);
static void set_elbow_0_degree_button_func(void);
static void set_elbow_90_degree_button_func(void);

void create_gui(ThreeDofRobot 	*robot_arm)
{
	GtkWidget *window, *vbox, *hbox, *lbl, *table;
	char temp [50];

	static_robot_arm = robot_arm;

 	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
  	gtk_window_set_default_size(GTK_WINDOW(window), 100, 100);
  	gtk_window_set_title(GTK_WINDOW(window), "ArmControl");
  	gtk_container_set_border_width(GTK_CONTAINER(window), 10);

  	vbox = gtk_vbox_new(TRUE, 0);
	gtk_container_add(GTK_CONTAINER(window), vbox);

  	hbox = gtk_hbox_new(FALSE, 0);
        gtk_box_pack_start(GTK_BOX(vbox),hbox, FALSE,FALSE,0);       

	table = gtk_table_new(2 ,2,TRUE);   // 2 rows 2 columns
	gtk_box_pack_start(GTK_BOX(hbox),table, TRUE,TRUE,0);

	vbox = gtk_vbox_new(FALSE, 0);
	gtk_table_attach_defaults(GTK_TABLE(table), vbox, 0,1, 0, 1);  // column 0-1, row 0-6

	hbox = gtk_hbox_new(FALSE, 0);
	gtk_box_pack_start(GTK_BOX(vbox),hbox, FALSE,FALSE,0);

	lbl = gtk_label_new("Base PW\t\t: ");
        gtk_box_pack_start(GTK_BOX(hbox),lbl, FALSE,FALSE,0);
        entry_base_pulse_width = gtk_entry_new();
        gtk_box_pack_start(GTK_BOX(hbox),entry_base_pulse_width, FALSE,FALSE,0);
	sprintf (temp, "%d", BASE_SERVO_INIT_PULSE);
	gtk_entry_set_text(GTK_ENTRY(entry_base_pulse_width), temp);
	gtk_widget_set_size_request(entry_base_pulse_width, 50, 30) ;	
	lbl = gtk_label_new("us");
        gtk_box_pack_start(GTK_BOX(hbox),lbl, FALSE,FALSE,0);

        entry_base_pulse_width_change = gtk_entry_new();
        gtk_box_pack_start(GTK_BOX(hbox),entry_base_pulse_width_change, FALSE,FALSE,0);
	gtk_entry_set_text(GTK_ENTRY(entry_base_pulse_width_change), "100");
	gtk_widget_set_size_request(entry_base_pulse_width_change, 50, 30) ;	

	btn_increment_base_pulse_width = gtk_button_new_with_label("+");
	gtk_box_pack_start (GTK_BOX (hbox), btn_increment_base_pulse_width, FALSE, FALSE, 0);
	gtk_widget_set_size_request(btn_increment_base_pulse_width, 30, 30) ;	
	btn_decrement_base_pulse_width = gtk_button_new_with_label("-");
	gtk_box_pack_start (GTK_BOX (hbox), btn_decrement_base_pulse_width, FALSE, FALSE, 0);
	gtk_widget_set_size_request(btn_decrement_base_pulse_width, 30, 30) ;	

	gtk_box_pack_start (GTK_BOX (hbox), gtk_vseparator_new(), FALSE, FALSE, 10);

	lbl_base_0_degree_quanta = gtk_label_new("0");
        gtk_box_pack_start(GTK_BOX(hbox),lbl_base_0_degree_quanta, FALSE,FALSE,0);
	gtk_widget_set_size_request(lbl_base_0_degree_quanta, 50, 30) ;	
	btn_set_base_0_degree = gtk_button_new_with_label("0°");
	gtk_box_pack_start (GTK_BOX (hbox), btn_set_base_0_degree, FALSE, FALSE, 0);
	gtk_widget_set_size_request(btn_set_base_0_degree, 40, 30) ;	
	lbl_base_90_degree_quanta = gtk_label_new("0");
        gtk_box_pack_start(GTK_BOX(hbox),lbl_base_90_degree_quanta, FALSE,FALSE,0);
	gtk_widget_set_size_request(lbl_base_90_degree_quanta, 50, 30) ;	
	btn_set_base_90_degree = gtk_button_new_with_label("90°");
	gtk_box_pack_start (GTK_BOX (hbox), btn_set_base_90_degree, FALSE, FALSE, 0);
	gtk_widget_set_size_request(btn_set_base_90_degree, 40, 30) ;	

	lbl_base_degree_per_pos_quanta = gtk_label_new("0°");
        gtk_box_pack_start(GTK_BOX(hbox),lbl_base_degree_per_pos_quanta, FALSE,FALSE,0);
	gtk_widget_set_size_request(lbl_base_degree_per_pos_quanta, 50, 30) ;	

	gtk_box_pack_start (GTK_BOX (hbox), gtk_vseparator_new(), FALSE, FALSE, 10);

	lbl_base_angle = gtk_label_new("0°");
        gtk_box_pack_start(GTK_BOX(hbox),lbl_base_angle, FALSE,FALSE,0);
	gtk_widget_set_size_request(lbl_base_angle, 60, 30) ;	

  	hbox = gtk_hbox_new(FALSE, 0);
        gtk_box_pack_start(GTK_BOX(vbox),hbox, FALSE,FALSE,0);       

	lbl = gtk_label_new("Shoulder PW\t: ");
        gtk_box_pack_start(GTK_BOX(hbox),lbl, FALSE,FALSE,0);
        entry_shoulder_pulse_width= gtk_entry_new();
        gtk_box_pack_start(GTK_BOX(hbox),entry_shoulder_pulse_width, FALSE,FALSE,0);
	sprintf (temp, "%d", SHOULDER_SERVO_INIT_PULSE);
	gtk_entry_set_text(GTK_ENTRY(entry_shoulder_pulse_width), temp);
	gtk_widget_set_size_request(entry_shoulder_pulse_width, 50, 30) ;	
	lbl = gtk_label_new("us");
        gtk_box_pack_start(GTK_BOX(hbox),lbl, FALSE,FALSE,0);

        entry_shoulder_pulse_width_change = gtk_entry_new();
        gtk_box_pack_start(GTK_BOX(hbox),entry_shoulder_pulse_width_change, FALSE,FALSE,0);
	gtk_entry_set_text(GTK_ENTRY(entry_shoulder_pulse_width_change), "100");
	gtk_widget_set_size_request(entry_shoulder_pulse_width_change, 50, 30) ;	

	btn_increment_shoulder_pulse_width = gtk_button_new_with_label("+");
	gtk_box_pack_start (GTK_BOX (hbox), btn_increment_shoulder_pulse_width, FALSE, FALSE, 0);
	gtk_widget_set_size_request(btn_increment_shoulder_pulse_width, 30, 30) ;	
	btn_decrement_shoulder_pulse_width = gtk_button_new_with_label("-");
	gtk_box_pack_start (GTK_BOX (hbox), btn_decrement_shoulder_pulse_width, FALSE, FALSE, 0);
	gtk_widget_set_size_request(btn_decrement_shoulder_pulse_width, 30, 30) ;	

	gtk_box_pack_start (GTK_BOX (hbox), gtk_vseparator_new(), FALSE, FALSE, 10);

	lbl_shoulder_0_degree_quanta = gtk_label_new("0");
        gtk_box_pack_start(GTK_BOX(hbox),lbl_shoulder_0_degree_quanta, FALSE,FALSE,0);
	gtk_widget_set_size_request(lbl_shoulder_0_degree_quanta, 50, 30) ;	
	btn_set_shoulder_0_degree = gtk_button_new_with_label("0°");
	gtk_box_pack_start (GTK_BOX (hbox), btn_set_shoulder_0_degree, FALSE, FALSE, 0);
	gtk_widget_set_size_request(btn_set_shoulder_0_degree, 40, 30) ;	
	lbl_shoulder_90_degree_quanta = gtk_label_new("0");
        gtk_box_pack_start(GTK_BOX(hbox),lbl_shoulder_90_degree_quanta, FALSE,FALSE,0);
	gtk_widget_set_size_request(lbl_shoulder_90_degree_quanta, 50, 30) ;	
	btn_set_shoulder_90_degree = gtk_button_new_with_label("90°");
	gtk_box_pack_start (GTK_BOX (hbox), btn_set_shoulder_90_degree, FALSE, FALSE, 0);
	gtk_widget_set_size_request(btn_set_shoulder_90_degree, 40, 30) ;	

	lbl_shoulder_degree_per_pos_quanta = gtk_label_new("0°");
        gtk_box_pack_start(GTK_BOX(hbox),lbl_shoulder_degree_per_pos_quanta, FALSE,FALSE,0);
	gtk_widget_set_size_request(lbl_shoulder_degree_per_pos_quanta, 50, 30) ;	

	gtk_box_pack_start (GTK_BOX (hbox), gtk_vseparator_new(), FALSE, FALSE, 10);

	lbl_shoulder_angle = gtk_label_new("0°");
        gtk_box_pack_start(GTK_BOX(hbox),lbl_shoulder_angle, FALSE,FALSE,0);
	gtk_widget_set_size_request(lbl_shoulder_angle, 60, 30) ;		

  	hbox = gtk_hbox_new(FALSE, 0);
        gtk_box_pack_start(GTK_BOX(vbox),hbox, FALSE,FALSE,0);       

	lbl = gtk_label_new("Elbow PW\t: ");
        gtk_box_pack_start(GTK_BOX(hbox),lbl, FALSE,FALSE,0);
        entry_elbow_pulse_width= gtk_entry_new();
        gtk_box_pack_start(GTK_BOX(hbox),entry_elbow_pulse_width, FALSE,FALSE,0);
	sprintf (temp, "%d", ELBOW_SERVO_INIT_PULSE);
	gtk_entry_set_text(GTK_ENTRY(entry_elbow_pulse_width), temp);
	gtk_widget_set_size_request(entry_elbow_pulse_width, 50, 30) ;	
	lbl = gtk_label_new("us");
        gtk_box_pack_start(GTK_BOX(hbox),lbl, FALSE,FALSE,0);

        entry_elbow_pulse_width_change = gtk_entry_new();
        gtk_box_pack_start(GTK_BOX(hbox),entry_elbow_pulse_width_change, FALSE,FALSE,0);
	gtk_entry_set_text(GTK_ENTRY(entry_elbow_pulse_width_change), "100");
	gtk_widget_set_size_request(entry_elbow_pulse_width_change, 50, 30) ;	

	btn_increment_elbow_pulse_width = gtk_button_new_with_label("+");
	gtk_box_pack_start (GTK_BOX (hbox), btn_increment_elbow_pulse_width, FALSE, FALSE, 0);
	gtk_widget_set_size_request(btn_increment_elbow_pulse_width, 30, 30) ;	
	btn_decrement_elbow_pulse_width = gtk_button_new_with_label("-");
	gtk_box_pack_start (GTK_BOX (hbox), btn_decrement_elbow_pulse_width, FALSE, FALSE, 0);
	gtk_widget_set_size_request(btn_decrement_elbow_pulse_width, 30, 30) ;	

	gtk_box_pack_start (GTK_BOX (hbox), gtk_vseparator_new(), FALSE, FALSE, 10);

	lbl_elbow_0_degree_quanta = gtk_label_new("0");
        gtk_box_pack_start(GTK_BOX(hbox),lbl_elbow_0_degree_quanta, FALSE,FALSE,0);
	gtk_widget_set_size_request(lbl_elbow_0_degree_quanta, 50, 30) ;	
	btn_set_elbow_0_degree = gtk_button_new_with_label("0°");
	gtk_box_pack_start (GTK_BOX (hbox), btn_set_elbow_0_degree, FALSE, FALSE, 0);
	gtk_widget_set_size_request(btn_set_elbow_0_degree, 40, 30) ;
	lbl_elbow_90_degree_quanta = gtk_label_new("0");
        gtk_box_pack_start(GTK_BOX(hbox),lbl_elbow_90_degree_quanta, FALSE,FALSE,0);
	gtk_widget_set_size_request(lbl_elbow_90_degree_quanta, 50, 30) ;		
	btn_set_elbow_90_degree = gtk_button_new_with_label("90°");
	gtk_box_pack_start (GTK_BOX (hbox), btn_set_elbow_90_degree, FALSE, FALSE, 0);
	gtk_widget_set_size_request(btn_set_elbow_90_degree, 40, 30) ;	

	lbl_elbow_degree_per_pos_quanta = gtk_label_new("0°");
        gtk_box_pack_start(GTK_BOX(hbox),lbl_elbow_degree_per_pos_quanta, FALSE,FALSE,0);
	gtk_widget_set_size_request(lbl_elbow_degree_per_pos_quanta, 50, 30) ;	

	gtk_box_pack_start (GTK_BOX (hbox), gtk_vseparator_new(), FALSE, FALSE, 10);

	lbl_elbow_angle = gtk_label_new("0°");
        gtk_box_pack_start(GTK_BOX(hbox),lbl_elbow_angle, FALSE,FALSE,0);
	gtk_widget_set_size_request(lbl_elbow_angle, 60, 30) ;		

  	hbox = gtk_hbox_new(FALSE, 0);
        gtk_box_pack_start(GTK_BOX(vbox),hbox, FALSE,FALSE,0);

	btn_submit_pulse_width = gtk_button_new_with_label("Submit Pulse Width");
	gtk_box_pack_start (GTK_BOX (hbox), btn_submit_pulse_width, TRUE, TRUE, 0);

	vbox = gtk_vbox_new(FALSE, 0);
	gtk_table_attach_defaults(GTK_TABLE(table), vbox, 0,1, 1, 2);  // column 0-1, row 1-2

	hbox = gtk_hbox_new(FALSE, 0);
	gtk_box_pack_start(GTK_BOX(vbox),hbox, FALSE,FALSE,0);

	lbl = gtk_label_new("Height\t\t: ");
        gtk_box_pack_start(GTK_BOX(hbox),lbl, FALSE,FALSE,0);
	lbl_tip_height = gtk_label_new("0");
        gtk_box_pack_start(GTK_BOX(hbox),lbl_tip_height, FALSE,FALSE,0);
	gtk_widget_set_size_request(lbl_tip_height, 60, 30) ;	

	hbox = gtk_hbox_new(FALSE, 0);
	gtk_box_pack_start(GTK_BOX(vbox),hbox, FALSE,FALSE,0);

	lbl = gtk_label_new("Lateral\t\t: ");
        gtk_box_pack_start(GTK_BOX(hbox),lbl, FALSE,FALSE,0);
	lbl_tip_lateral = gtk_label_new("0");
        gtk_box_pack_start(GTK_BOX(hbox),lbl_tip_lateral, FALSE,FALSE,0);
	gtk_widget_set_size_request(lbl_tip_lateral, 60, 30) ;	

	hbox = gtk_hbox_new(FALSE, 0);
	gtk_box_pack_start(GTK_BOX(vbox),hbox, FALSE,FALSE,0);

	lbl = gtk_label_new("Depth\t\t: ");
        gtk_box_pack_start(GTK_BOX(hbox),lbl, FALSE,FALSE,0);
	lbl_tip_depth = gtk_label_new("0");
        gtk_box_pack_start(GTK_BOX(hbox),lbl_tip_depth, FALSE,FALSE,0);
	gtk_widget_set_size_request(lbl_tip_depth, 60, 30) ;	


	gtk_widget_show_all(window);

  	g_signal_connect (G_OBJECT (window), "destroy", G_CALLBACK (gtk_main_quit), NULL);
      	g_signal_connect(G_OBJECT( btn_submit_pulse_width), "clicked", G_CALLBACK( submit_pulse_width_button_func), NULL);
      	g_signal_connect(G_OBJECT( btn_increment_base_pulse_width), "clicked", G_CALLBACK( increment_base_pulse_width_button_func), NULL);
      	g_signal_connect(G_OBJECT( btn_decrement_base_pulse_width), "clicked", G_CALLBACK( decrement_base_pulse_width_button_func), NULL);
      	g_signal_connect(G_OBJECT(btn_set_base_0_degree), "clicked", G_CALLBACK(set_base_0_degree_button_func), NULL);
      	g_signal_connect(G_OBJECT(btn_set_base_90_degree), "clicked", G_CALLBACK(set_base_90_degree_button_func), NULL);
      	g_signal_connect(G_OBJECT( btn_increment_shoulder_pulse_width), "clicked", G_CALLBACK( increment_shoulder_pulse_width_button_func), NULL);
      	g_signal_connect(G_OBJECT( btn_decrement_shoulder_pulse_width), "clicked", G_CALLBACK( decrement_shoulder_pulse_width_button_func), NULL);
      	g_signal_connect(G_OBJECT(btn_set_shoulder_0_degree), "clicked", G_CALLBACK(set_shoulder_0_degree_button_func), NULL);
      	g_signal_connect(G_OBJECT(btn_set_shoulder_90_degree), "clicked", G_CALLBACK(set_shoulder_90_degree_button_func), NULL);
      	g_signal_connect(G_OBJECT( btn_increment_elbow_pulse_width), "clicked", G_CALLBACK( increment_elbow_pulse_width_button_func), NULL);
      	g_signal_connect(G_OBJECT( btn_decrement_elbow_pulse_width), "clicked", G_CALLBACK( decrement_elbow_pulse_width_button_func), NULL);
      	g_signal_connect(G_OBJECT(btn_set_elbow_0_degree), "clicked", G_CALLBACK(set_elbow_0_degree_button_func), NULL);
      	g_signal_connect(G_OBJECT(btn_set_elbow_90_degree), "clicked", G_CALLBACK(set_elbow_90_degree_button_func), NULL);

	g_timeout_add(100, timeout_callback, NULL);
}

static gboolean timeout_callback(gpointer none)
{
	char temp[50];

	sprintf (temp, "%.2f°", static_robot_arm->servos[BASE_SERVO].current_angle * (180.0 / M_PI));
 	gtk_label_set_text(GTK_LABEL(lbl_base_angle), temp);
	sprintf (temp, "%.2f°", static_robot_arm->servos[SHOULDER_SERVO].current_angle * (180.0 / M_PI));
 	gtk_label_set_text(GTK_LABEL(lbl_shoulder_angle), temp);
	sprintf (temp, "%.2f°", static_robot_arm->servos[ELBOW_SERVO].current_angle * (180.0 / M_PI));
 	gtk_label_set_text(GTK_LABEL(lbl_elbow_angle), temp);

	sprintf (temp, "%.2f", static_robot_arm->tip_position.height);
 	gtk_label_set_text(GTK_LABEL(lbl_tip_height), temp);
	sprintf (temp, "%.2f", static_robot_arm->tip_position.lateral);
 	gtk_label_set_text(GTK_LABEL(lbl_tip_lateral), temp);
	sprintf (temp, "%.2f", static_robot_arm->tip_position.depth);
 	gtk_label_set_text(GTK_LABEL(lbl_tip_depth), temp);

	return TRUE;
} 

static void submit_pulse_width_button_func(void)
{
	ServoPulse base_pw, shoulder_pw, elbow_pw;
	
	base_pw = (unsigned short int)atof(gtk_entry_get_text(GTK_ENTRY(entry_base_pulse_width)));
	shoulder_pw = (unsigned short int)atof(gtk_entry_get_text(GTK_ENTRY(entry_shoulder_pulse_width)));
	elbow_pw = (unsigned short int)atof(gtk_entry_get_text(GTK_ENTRY(entry_elbow_pulse_width)));

	submit_servo_target(&(static_robot_arm->servos[BASE_SERVO]), base_pw, 0.01);
	submit_servo_target(&(static_robot_arm->servos[SHOULDER_SERVO]), shoulder_pw, 0.05);
	submit_servo_target(&(static_robot_arm->servos[ELBOW_SERVO]), elbow_pw, 0.05);

	return;
}

static void increment_base_pulse_width_button_func(void)
{	
	ServoPulse base_pw; 
	unsigned short int change;
	char temp [50];

	base_pw = (ServoPulse)atof(gtk_entry_get_text(GTK_ENTRY(entry_base_pulse_width)));
	change = (ServoPulse)atof(gtk_entry_get_text(GTK_ENTRY(entry_base_pulse_width_change)));

	base_pw = base_pw + change;
	submit_servo_target(&(static_robot_arm->servos[BASE_SERVO]), base_pw, 1.0);
	sprintf (temp, "%u", base_pw);
	gtk_entry_set_text(GTK_ENTRY(entry_base_pulse_width), temp);
}
static void decrement_base_pulse_width_button_func(void)
{
	ServoPulse base_pw; 
	unsigned short int change;
	char temp [50];

	base_pw = (unsigned short int)atof(gtk_entry_get_text(GTK_ENTRY(entry_base_pulse_width)));
	change = (unsigned short int)atof(gtk_entry_get_text(GTK_ENTRY(entry_base_pulse_width_change)));

	base_pw = base_pw - change;
	submit_servo_target(&(static_robot_arm->servos[BASE_SERVO]), base_pw, 1.0);
	sprintf (temp, "%u", base_pw);
	gtk_entry_set_text(GTK_ENTRY(entry_base_pulse_width), temp);
}
static void set_base_0_degree_button_func(void)
{
	char temp[50];
	ServoPosition servo_position;

	get_servo_position_val(&(static_robot_arm->servos[BASE_SERVO]), &servo_position);
	write_servo_0_degree_adc_val(&(static_robot_arm->servos[BASE_SERVO]), servo_position);

	sprintf (temp, "%u", static_robot_arm->servos[BASE_SERVO].range.position_0_degree); 
 	gtk_label_set_text(GTK_LABEL(lbl_base_0_degree_quanta), temp);
	sprintf (temp, "%.2f°", static_robot_arm->servos[BASE_SERVO].range.radian_per_pos_quanta * (180.0 / M_PI) ); 
 	gtk_label_set_text(GTK_LABEL(lbl_base_degree_per_pos_quanta), temp);
}
static void set_base_90_degree_button_func(void)
{
	char temp[50];
	ServoPosition servo_position;

	get_servo_position_val(&(static_robot_arm->servos[BASE_SERVO]), &(servo_position));
	write_servo_90_degree_adc_val(&(static_robot_arm->servos[BASE_SERVO]), servo_position);

	sprintf (temp, "%u", static_robot_arm->servos[BASE_SERVO].range.position_90_degree); 
 	gtk_label_set_text(GTK_LABEL(lbl_base_90_degree_quanta), temp);
	sprintf (temp, "%.2f°", static_robot_arm->servos[BASE_SERVO].range.radian_per_pos_quanta * (180.0 / M_PI) ); 
 	gtk_label_set_text(GTK_LABEL(lbl_base_degree_per_pos_quanta), temp);
}
static void increment_shoulder_pulse_width_button_func(void)
{
	ServoPulse shoulder_pw; 
	unsigned short int change;
	char temp [50];

	shoulder_pw = (unsigned short int)atof(gtk_entry_get_text(GTK_ENTRY(entry_shoulder_pulse_width)));
	change = (unsigned short int)atof(gtk_entry_get_text(GTK_ENTRY(entry_shoulder_pulse_width_change)));

	shoulder_pw = shoulder_pw + change;
	submit_servo_target(&(static_robot_arm->servos[SHOULDER_SERVO]), shoulder_pw, 1.0);
	sprintf (temp, "%u", shoulder_pw);
	gtk_entry_set_text(GTK_ENTRY(entry_shoulder_pulse_width), temp);
}
static void decrement_shoulder_pulse_width_button_func(void)
{
	ServoPulse shoulder_pw; 
	unsigned short int change;
	char temp [50];

	shoulder_pw = (unsigned short int)atof(gtk_entry_get_text(GTK_ENTRY(entry_shoulder_pulse_width)));
	change = (unsigned short int)atof(gtk_entry_get_text(GTK_ENTRY(entry_shoulder_pulse_width_change)));

	shoulder_pw = shoulder_pw - change;
	submit_servo_target(&(static_robot_arm->servos[SHOULDER_SERVO]), shoulder_pw, 1.0);
	sprintf (temp, "%u", shoulder_pw);
	gtk_entry_set_text(GTK_ENTRY(entry_shoulder_pulse_width), temp);
}
static void set_shoulder_0_degree_button_func(void)
{
	char temp[50];
	ServoPosition servo_position;

	get_servo_position_val(&(static_robot_arm->servos[SHOULDER_SERVO]), &servo_position);
	write_servo_0_degree_adc_val(&(static_robot_arm->servos[SHOULDER_SERVO]), servo_position);

	sprintf (temp, "%u", static_robot_arm->servos[SHOULDER_SERVO].range.position_0_degree); 
 	gtk_label_set_text(GTK_LABEL(lbl_shoulder_0_degree_quanta), temp);
	sprintf (temp, "%.2f°", static_robot_arm->servos[SHOULDER_SERVO].range.radian_per_pos_quanta * (180.0 / M_PI) ); 
 	gtk_label_set_text(GTK_LABEL(lbl_shoulder_degree_per_pos_quanta), temp);
}
static void set_shoulder_90_degree_button_func(void)
{
	char temp[50];
	ServoPosition servo_position;

	get_servo_position_val(&(static_robot_arm->servos[SHOULDER_SERVO]), &servo_position);
	write_servo_90_degree_adc_val(&(static_robot_arm->servos[SHOULDER_SERVO]), servo_position);

	sprintf (temp, "%u", static_robot_arm->servos[SHOULDER_SERVO].range.position_90_degree); 
 	gtk_label_set_text(GTK_LABEL(lbl_shoulder_90_degree_quanta), temp);
	sprintf (temp, "%.2f°", static_robot_arm->servos[SHOULDER_SERVO].range.radian_per_pos_quanta * (180.0 / M_PI) ); 
 	gtk_label_set_text(GTK_LABEL(lbl_shoulder_degree_per_pos_quanta), temp);
}
static void increment_elbow_pulse_width_button_func(void)
{
	ServoPulse elbow_pw; 
	unsigned short int change;
	char temp [50];

	elbow_pw = (unsigned short int)atof(gtk_entry_get_text(GTK_ENTRY(entry_elbow_pulse_width)));
	change = (unsigned short int)atof(gtk_entry_get_text(GTK_ENTRY(entry_elbow_pulse_width_change)));

	elbow_pw = elbow_pw + change;
	submit_servo_target(&(static_robot_arm->servos[ELBOW_SERVO]), elbow_pw, 1.0);
	sprintf (temp, "%u", elbow_pw);
	gtk_entry_set_text(GTK_ENTRY(entry_elbow_pulse_width), temp);
}
static void decrement_elbow_pulse_width_button_func(void)
{
	ServoPulse elbow_pw; 
	unsigned short int change;
	char temp [50];

	elbow_pw = (unsigned short int)atof(gtk_entry_get_text(GTK_ENTRY(entry_elbow_pulse_width)));
	change = (unsigned short int)atof(gtk_entry_get_text(GTK_ENTRY(entry_elbow_pulse_width_change)));

	elbow_pw = elbow_pw - change;
	submit_servo_target(&(static_robot_arm->servos[ELBOW_SERVO]), elbow_pw, 1.0);
	sprintf (temp, "%u", elbow_pw);
	gtk_entry_set_text(GTK_ENTRY(entry_elbow_pulse_width), temp);
}
static void set_elbow_0_degree_button_func(void)
{
	char temp[50];
	ServoPosition servo_position;

	get_servo_position_val(&(static_robot_arm->servos[ELBOW_SERVO]), &servo_position);
	write_servo_0_degree_adc_val(&(static_robot_arm->servos[ELBOW_SERVO]), servo_position);

	sprintf (temp, "%u", static_robot_arm->servos[ELBOW_SERVO].range.position_0_degree); 
 	gtk_label_set_text(GTK_LABEL(lbl_elbow_0_degree_quanta), temp);
	sprintf (temp, "%.2f°", static_robot_arm->servos[ELBOW_SERVO].range.radian_per_pos_quanta * (180.0 / M_PI) ); 
 	gtk_label_set_text(GTK_LABEL(lbl_elbow_degree_per_pos_quanta), temp);
}
static void set_elbow_90_degree_button_func(void)
{
	char temp[50];
	ServoPosition servo_position;

	get_servo_position_val(&(static_robot_arm->servos[ELBOW_SERVO]), &servo_position);
	write_servo_90_degree_adc_val(&(static_robot_arm->servos[ELBOW_SERVO]), servo_position);

	sprintf (temp, "%u", static_robot_arm->servos[ELBOW_SERVO].range.position_90_degree); 
 	gtk_label_set_text(GTK_LABEL(lbl_elbow_90_degree_quanta), temp);
	sprintf (temp, "%.2f°", static_robot_arm->servos[ELBOW_SERVO].range.radian_per_pos_quanta * (180.0 / M_PI) ); 
 	gtk_label_set_text(GTK_LABEL(lbl_elbow_degree_per_pos_quanta), temp);
}
