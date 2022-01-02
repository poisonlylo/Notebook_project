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

void finish_with_error(MYSQL *con)
{
    fprintf(stderr, "%s\n", mysql_error(con));
    mysql_close(con);
    exit(1);
}


void login(GtkWidget *W,GtkEntry *data) {
    char requete[255];
    char password[255];
    char username[255];
    MYSQL mysql;
    MYSQL *con = mysql_init(NULL);
    if (con == NULL) {
        fprintf(stderr, "mysql_init() failed\n");
        exit(1);
    }

    if (mysql_real_connect(con, "localhost", "root", "mysql2016", "notebook", 3306, NULL, 0) == NULL) {
        finish_with_error(con);
    }

     if ( mysql_query(con, "SELECT password FROM account WHERE user_id = 1" )){
         finish_with_error(con);
     }

    MYSQL_RES *result = mysql_store_result(con);

    if (result == NULL)
    {
        finish_with_error(con);
    }

    int num_fields = mysql_num_fields(result);

    MYSQL_ROW row;
int i;
    while ((row = mysql_fetch_row(result)))
    {
        printf("%s",row[i] );
        printf("%s",gtk_entry_get_text(entry_password) );
            if ( gtk_entry_get_text(entry_password) == row[i]){
                printf("vous etes connecte!");
            }else{
                printf("erreur de username ou password");
            }
    }

    mysql_free_result(result);
    mysql_close(con);

    exit(0);
}

char username_con[255];



void login_console(char * password_con ) {
    char requette[50] ;
    MYSQL mysql;
    MYSQL *con = mysql_init(NULL);
    if (con == NULL) {
        fprintf(stderr, "mysql_init() failed\n");
        exit(1);
    }

    if (mysql_real_connect(con, "localhost", "root", "mysql2016", "notebook", 3306, NULL, 0) == NULL) {
        finish_with_error(con);
    }

   // sprintf(requette, "SELECT password FROM account WHERE username ='%s'", 'lyes' );

    if ( mysql_query(con, "SELECT password FROM account WHERE username ='lyes'" )){
        finish_with_error(con);
    }

    MYSQL_RES *result = mysql_store_result(con);

    if (result == NULL)
    {
        finish_with_error(con);
    }

    int num_fields = mysql_num_fields(result);

    MYSQL_ROW row;
    int i;
    while ((row = mysql_fetch_row(result)))
    {
        printf("%s",row[i] );
        printf("%s",password_con );
        if ( password_con == row[i]){
            printf("vous etes connecte!");
        }else{
            printf("erreur de username ou password");
        }
    }

    mysql_free_result(result);
    mysql_close(con);

    exit(0);
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
        char password_con[255];

        char requette[50] ;
        //demande a l'utilisateur
        printf("Tappez 1 pour interface graphique \n Tappez 2 pour lignes de commandes\n");
        scanf("%d", &reponse);


        //1 pour console
        if (reponse == 1 ){

            printf("entrez le password");
            fgets(password_con, 255, stdin);




            MYSQL *con = mysql_init(NULL);
            if (con == NULL) {
                fprintf(stderr, "mysql_init() failed\n");
                exit(1);
            }

            if (mysql_real_connect(con, "localhost", "root", "mysql2016", "notebook", 3306, NULL, 0) == NULL) {
                finish_with_error(con);
            }

            // sprintf(requette, "SELECT password FROM account WHERE username ='%s'", 'lyes' );

            if ( mysql_query(con, "SELECT password FROM account WHERE user_id = 1 " )){
                finish_with_error(con);
            }

            MYSQL_RES *result = mysql_store_result(con);

            if (result == NULL)
            {
                finish_with_error(con);
            }

            int num_fields = mysql_num_fields(result);

            MYSQL_ROW row;
            int i;
            while ((row = mysql_fetch_row(result)))
            {
                printf("%s",row[i] );


            }

            mysql_free_result(result);
            mysql_close(con);


            int ch;




            printf("\n\n\t***********************************\n");

            printf("\t*Block Notes Personnel*\n");

            printf("\t***********************************");

            while(1)

            {

                printf("\n\n\t\tMENU PRINCIPAL:");

                printf("\n\n\tAJOUTER UN DOSSIER\t[1]");

                printf("\n\tOUVRIR UN DOSSIER\t[2]");

                printf("\n\tMODIFIER UN DOSSIER\t[3]");

                printf("\n\tSUPPRIMER UN DOSSIER\t[4]");

                printf("\n\tMODIFIER LE MOT DE PASSE\t[5]");

                printf("\n\tSORTIE\t\t[6]");

                printf("\n\n\tSAISISSEZ VOTRE CHOIX :");

                scanf("%d",&ch);
/*
                switch(ch)

                {

                    case 1:

                        addrecord();

                        break;

                    case 2:

                        viewrecord();

                        break;

                    case 3:

                        editrecord();

                        break;

                    case 4:

                        deleterecord();

                        break;

                    case 5:

                        editpassword();

                        break;

                    case 6:

                        printf("\n\n\t\tTHANK YOU FOR USING THE SOFTWARE ");

                        getch();

                        exit(0);

                    default:

                        printf("\nYOU ENTERED WRONG CHOICE..");

                        printf("\nPRESS ANY KEY TO TRY AGAIN");

                        getch();

                        break;

                }

                system("cls");
*/
            }
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
            entry_username = gtk_builder_get_object(builder, "entry_username");
            entry_password = gtk_builder_get_object(builder, "entry_password");
        GtkWidget *btn_login = gtk_builder_get_object(builder, "btn_login");
        g_signal_connect(btn_login, "clicked", G_CALLBACK(login), entry_username);
        g_signal_connect(btn_login, "clicked", G_CALLBACK(login), entry_password);


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




