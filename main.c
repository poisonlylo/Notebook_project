#include <stdio.h>
#include <mysql.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>



GtkBuilder *builder;
GtkBuilder *builder2;
GtkWidget *app;
GtkWidget *app2;
GtkWidget *window2;
GtkEntry *tx_surname, *tx_email, *tx_password ;
GtkEntry *entry_username, *entry_password;

void button_pressed(GtkWidget *W,GtkEntry *data) {
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
void close_window(){
    gtk_main_quit();
}

void show_page(GtkWidget *W,GtkEntry *data){

    gtk_widget_show_all (data);

}


void login(GtkWidget *W,GtkEntry *data){
    char requete[255];
    char password[255];
    char username[255];
    MYSQL mysql;
    mysql_init(&mysql);
    mysql_options(&mysql,MYSQL_READ_DEFAULT_GROUP,"option");


    if(mysql_real_connect(&mysql,"localhost","root","mysql2016","notebook",3306,NULL,0))
    {

        sprintf(requete, "SELECT password FROM account WHERE user_id='%d'", 2);
        printf('%s', password);
        mysql_query(&mysql,requete );
        //if(gtk_entry_get_text(entry_username)== username && gtk_entry_get_text(entry_username)== password ){
        //    printf("reussi!!");
        //}
        mysql_close(&mysql);
    }else
    {
        printf("Une erreur s'est produite lors de la connexion à la BDD!");
    }
}


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





    int main(int argc, char **argv) {
        int reponse;

        //demande a l'utilisateur
        printf("Tappez 1 pour interface graphique \n Tappez 2 pour lignes de commandes\n");
        scanf("%d", &reponse);


        //1 pour console
        if (reponse == 1 ){
            printf("hello");
            return 0;
        }


        //2 pour GI
        else{
        g_log_set_handler ("Gtk", G_LOG_LEVEL_WARNING, (GLogFunc) gtk_false, NULL);
        gtk_init (&argc, &argv);
        g_log_set_handler ("Gtk", G_LOG_LEVEL_WARNING, g_log_default_handler, NULL);


        builder = gtk_builder_new ();
        gtk_builder_add_from_file (builder, "app_design.glade", NULL);
        app = GTK_WIDGET (gtk_builder_get_object (builder, "window1"));
        gtk_builder_connect_signals (builder, NULL);

        tx_surname = gtk_builder_get_object(builder, "tx_surname");
        tx_password = gtk_builder_get_object(builder, "tx_password");
        tx_email = gtk_builder_get_object(builder, "tx_email");
        GtkWidget *button_insc = gtk_builder_get_object(builder, "button_insc");

        g_signal_connect(button_insc, "clicked", G_CALLBACK(button_pressed), tx_surname);
        g_signal_connect(button_insc, "clicked", G_CALLBACK(button_pressed), tx_password);
        g_signal_connect(button_insc, "clicked", G_CALLBACK(button_pressed), tx_email);


        builder2 = gtk_builder_new ();
        gtk_builder_add_from_file (builder2, "app_design.glade", NULL);
        window2 = GTK_WIDGET (gtk_builder_get_object (builder2, "window2"));
        gtk_builder_connect_signals (builder2, NULL);
        GtkWidget *button_next_page = gtk_builder_get_object(builder, "button_next_page");
       // g_signal_connect(button_next_page, "clicked", G_CALLBACK(show_page), window2);
       // g_signal_connect(button_next_page, "clicked", G_CALLBACK(close_window), NULL);



        g_object_unref (G_OBJECT (builder));
        g_object_unref (G_OBJECT (builder2));


        gtk_widget_show (app);


        gtk_main ();

            return 0;
        }

    }









/*

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




