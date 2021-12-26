#include <stdio.h>
#include <mysql.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>

GtkBuilder *builder;
GtkWidget *app;
GtkEntry *tx_surname, *tx_email, *tx_password ;
void close_window(){
     gtk_main_quit();

}
/*
 void make_window(){
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 400);
    gtk_window_set_title(GTK_WINDOW(window), "Login");
    g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(close_window), NULL);

    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_container_add(GTK_CONTAINER(window), vbox);
    gtk_widget_show_all(window);
}
 */
void button_pressed(GtkWidget *W,gpointer *data) {
    char username[255];
    char password[255];
    char user[15];
    char pass[12];
    char email[255];
    int id;
    char requete[255];

    MYSQL mysql;
    mysql_init(&mysql);
    mysql_options(&mysql,MYSQL_READ_DEFAULT_GROUP,"option");


    if(mysql_real_connect(&mysql,"localhost","root","mysql2016","notebook",3306,NULL,0))
    {

        sprintf(requete, "INSERT INTO account(user_id, username, email, password) VALUES('%d','%s', '%s', '%s')",
                id,gtk_entry_get_text(tx_surname), gtk_entry_get_text(tx_email), gtk_entry_get_text(tx_password));

        mysql_query(&mysql, requete);

    }
    else
    {
        printf("Une erreur s'est produite lors de la connexion à la BDD!");
    }
}
/*
void login_window(GtkApplication *login_app, gpointer *user_data) {
    GtkWidget *window;
    window = gtk_application_window_new(login_app);
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 100);
    gtk_window_set_title(GTK_WINDOW(window), "Login");

    GtkWidget *vbox = gtk_vbox_new(FALSE, 0);
    gtk_container_add(GTK_CONTAINER(window), vbox);
    gtk_widget_show(vbox);


    tx_id = gtk_entry_new();
    gtk_box_pack_start(GTK_CONTAINER(vbox), tx_id, TRUE, TRUE, 10 );
    gtk_widget_show(tx_id);

    GtkWidget *hbox = gtk_hbox_new(TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), hbox, TRUE, TRUE, 10);

    tx_name = gtk_entry_new();
    gtk_box_pack_start(GTK_CONTAINER(hbox), tx_name, TRUE, TRUE, 10);
    gtk_widget_show(tx_name);

    GtkWidget *button_box = gtk_button_box_new(GTK_ORIENTATION_HORIZONTAL);
    gtk_box_pack_start(GTK_BOX(vbox), button_box, TRUE, TRUE, 10);

    GtkWidget *button = gtk_button_new_with_label("insert row");
    g_signal_connect(button, "clicked", G_CALLBACK(button_pressed), NULL);
    gtk_container_add(GTK_CONTAINER(button_box), button);
    gtk_widget_show(button);

    gtk_widget_show_all(window);
}
 */



G_MODULE_EXPORT
void on_app_destroy (void)
{
    gtk_main_quit ();
}

G_MODULE_EXPORT
void on_menu_quit_activate (void)
{
    gtk_main_quit ();
    exit(EXIT_SUCCESS);
}


    int main(int argc, char **argv){

        g_log_set_handler ("Gtk", G_LOG_LEVEL_WARNING, (GLogFunc) gtk_false, NULL);
        gtk_init (&argc, &argv);
        g_log_set_handler ("Gtk", G_LOG_LEVEL_WARNING, g_log_default_handler, NULL);

        builder = gtk_builder_new ();
        gtk_builder_add_from_file (builder, "app_design.glade", NULL);
        app = GTK_WIDGET (gtk_builder_get_object (builder, "window1"));
        gtk_builder_connect_signals (builder, NULL);



        g_object_unref (G_OBJECT (builder));

/* Enter the main loop */
        gtk_widget_show (app);
        gtk_main ();

/*
    GtkApplication *login = gtk_application_new("login.window", G_APPLICATION_FLAGS_NONE);
        g_signal_connect(login, "activate", G_CALLBACK(login_window), NULL);
         g_application_run(G_APPLICATION(login), argc, argv);
        g_object_unref(login);

        gtk_init(&argc, &argv);
        make_window();
        gtk_main();


        char username[255];
        char password[255];
        char user[15];
        char pass[12];
        char email[255];
        int id;
        char requete[255];





        printf("enter your email\n");
        fgets(email, 255, stdin);
        if(email[strlen(email)-1] == "\n") email[strlen(email)-1] = "\0";
        printf("enter your password\n");
        fgets(password, 255, stdin);
        printf("enter your username\n");
        fgets(username, 255, stdin);



        MYSQL mysql;
        mysql_init(&mysql);
        mysql_options(&mysql,MYSQL_READ_DEFAULT_GROUP,"option");


        if(mysql_real_connect(&mysql,"localhost","root","mysql2016","notebook",3306,NULL,0))
        {

            sprintf(requete, "INSERT INTO account(user_id , username, email, password) VALUES('%d', '%s', '%s', '%s')", id,username, email, password );

            mysql_query(&mysql, requete);

        }
        else
        {
            printf("Une erreur s'est produite lors de la connexion à la BDD!");
        }

*/
return 0;

    }

