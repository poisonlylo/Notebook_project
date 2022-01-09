#include <stdio.h>
#include <mysql.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>
#include <sys/stat.h>


GtkBuilder *builder;
GtkBuilder *builder2;
GtkBuilder *builder3;
GtkWidget *app;
GtkWidget *app2;
GtkWidget *window2;
GtkEntry *tx_surname, *tx_email, *tx_password ;
GtkEntry *entry_username, *entry_password;
GtkWidget *notebook;
char pass[50];
char pass_entry[50];


void button_pressed(GtkWidget *W,GtkEntry *data) {
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
        mkdir(gtk_entry_get_text(tx_surname), S_IRWXU);
        exit(EXIT_SUCCESS);

    }
    else
    {
        printf("Une erreur s'est produite lors de la connexion à la BDD!");
    }
}

void close_window() {
    gtk_main_quit();
}


typedef struct{
    char *label;
    char sub_items;
    char sub_menu[6][15];
}MuButton;

MuButton menulist[] = {
          {"file", 6, {"new", "open","save", "save as", "close", "quit" }},
         {"edit", 4,{"copy", "paste","cut", "delete"} }
};

void close_tab(GtkWidget *button, gpointer data){
    int pg_num = gtk_notebook_page_num(GTK_NOTEBOOK(notebook), data);
    gtk_notebook_remove_page(notebook, pg_num); 
}

void add_tab(char *name){
    char texte[255];
    GtkWidget *textview = gtk_text_view_new();
GtkWidget *text = gtk_label_new(name);
GtkWidget *label = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
GtkWidget *icon = gtk_image_new_from_file("close.png");
GtkWidget *button = gtk_button_new();
gtk_button_set_image(GTK_BUTTON(button), icon);
gtk_box_pack_start(label,text, TRUE, TRUE, 0);
gtk_box_pack_start(label,button, FALSE, FALSE, 0);

GtkWidget *scroll_window = gtk_scrolled_window_new(NULL, NULL);
    gtk_container_add(scroll_window, textview);
    gtk_notebook_append_page(GTK_NOTEBOOK(notebook), scroll_window, label);
    g_signal_connect(button, "clicked", G_CALLBACK(close_tab), NULL);

    FILE *fp = fopen(name,"wb+");
    fputs(text, fp);
    fgets(texte, 155, fp);
    printf("%s", texte);
    fclose(fp);


    gtk_widget_show_all(label);
    gtk_widget_show_all(scroll_window);

}

void open_file(void *file_address){
    g_print("%s", file_address);
}
void open_file_dialog(){
    GtkWidget *open_dialog;
    int res;
    open_dialog = gtk_file_chooser_dialog_new("open_file", NULL, GTK_FILE_CHOOSER_ACTION_OPEN,  "Cancel", GTK_RESPONSE_CANCEL, "Open", GTK_RESPONSE_ACCEPT, NULL );
    res = gtk_dialog_run(GTK_DIALOG(open_dialog));
   if (res == GTK_RESPONSE_ACCEPT){
       char *file_address;
       GtkFileChooser *chooser = GTK_FILE_CHOOSER(open_dialog);
       file_address = gtk_file_chooser_get_filename(chooser);
       open_file(file_address);
       free(file_address);
   }
   gtk_widget_destroy(open_dialog);
}
void button_click(GtkWidget *button, gpointer data){
    char *btn = (char*)data ;
    if (strcmp(btn, "new") == 0) add_tab("new tab");
    if (strcmp(btn, "open") == 0) open_file_dialog();
}



void make_notebook(GtkWidget *vbox){
 notebook = gtk_notebook_new();
    gtk_box_pack_start(vbox,  notebook, TRUE, TRUE, 0);
    add_tab("untiteled");
}

void make_menu(GtkWidget *vbox){
    GtkWidget *menubar = gtk_menu_bar_new();
    for (int i = 0; i < 7; ++i) {
        GtkWidget *item = gtk_menu_item_new_with_label(menulist[i].label);
        GtkWidget *item_menu = gtk_menu_new();
        gtk_menu_shell_append(GTK_MENU_SHELL(menubar), item);
        gtk_menu_item_set_submenu(GTK_MENU_ITEM(item), item_menu);
        for (int j = 0; j < menulist->sub_items; ++j) {
            GtkWidget *subitem = gtk_menu_item_new_with_label(menulist[i].sub_menu[j]);
            g_signal_connect(GTK_WIDGET(subitem), "activate", G_CALLBACK(button_click),menulist[i].sub_menu[j] );
            gtk_menu_shell_append(GTK_MENU_SHELL(item_menu), subitem);

        }
    }
    gtk_container_add(GTK_CONTAINER(vbox), menubar);
}

void make_window(){
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_window_set_default_size(GTK_WINDOW(window), 800, 800);
    gtk_window_set_title(GTK_WINDOW(window), "NoteBook");
    g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(close_window), NULL);

    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_container_add(GTK_CONTAINER(window), vbox);
    make_menu(vbox);
    make_notebook(vbox);
    gtk_widget_show_all(window);

}

void finish_with_error(MYSQL *con)
{
    fprintf(stderr, "%s\n", mysql_error(con));
    mysql_close(con);
    exit(1);
}

void show_page(GtkWidget *window2) {
    gtk_widget_show(window2);
}


int login() {
    char requette[255];
    char password[255];
    char username[255];

    MYSQL *con = mysql_init(NULL);
    if (con == NULL) {
        fprintf(stderr, "mysql_init() failed\n");
        exit(1);
    }

    if (mysql_real_connect(con, "localhost", "root", "mysql2016", "notebook", 3306, NULL, 0) == NULL) {
        finish_with_error(con);
    }

     sprintf(requette, "SELECT * FROM account WHERE username = '%s'", gtk_entry_get_text(entry_username) );
     if ( mysql_query(con, requette)){
         finish_with_error(con);
     }

    MYSQL_RES *result = mysql_store_result(con);

    if (result == NULL)
    {
        finish_with_error(con);
    }

    MYSQL_ROW row;

    while ((row = mysql_fetch_row(result)))
    {
        sprintf(pass, "%s" , row[3]);
        sprintf(pass_entry, "%s",gtk_entry_get_text(entry_password)) ;

        if (strcmp(pass ,pass_entry ) == 0){
            return 1;
        }else{
            return 0;
        }
    }
    mysql_free_result(result);
    mysql_close(con);

    exit(0);
}

void main_window(* argc, *argv){
    g_log_set_handler ("Gtk", G_LOG_LEVEL_WARNING, (GLogFunc) gtk_false, NULL);
    gtk_init (&argc, &argv);
    g_log_set_handler ("Gtk", G_LOG_LEVEL_WARNING, g_log_default_handler, NULL);
    builder3 = gtk_builder_new ();
    gtk_builder_add_from_file (builder3, "../menu.glade", NULL);
    app2 = GTK_WIDGET (gtk_builder_get_object (builder3, "welcoming_window"));

    gtk_builder_connect_signals (builder3, NULL);

    g_object_unref (G_OBJECT (builder3));
    gtk_widget_show(app2);
    gtk_main ();
}

int login_console(char * password_con, char * username_con ) {
    char requette[50] ;

    MYSQL *con = mysql_init(NULL);
    if (con == NULL) {
        fprintf(stderr, "mysql_init() failed\n");
        exit(1);
    }

    if (mysql_real_connect(con, "localhost", "root", "mysql2016", "notebook", 3306, NULL, 0) == NULL) {
        finish_with_error(con);
    }

    sprintf(requette, "SELECT * FROM account WHERE username = '%s'", username_con );
    if ( mysql_query(con, requette)){
        finish_with_error(con);
    }

    MYSQL_RES *result = mysql_store_result(con);

    if (result == NULL)
    {
        finish_with_error(con);
    }

    MYSQL_ROW row;

    while ((row = mysql_fetch_row(result)))
    {
        sprintf(pass, "%s" , row[3]);
        sprintf(pass_entry, "%s",password_con) ;

        if (strcmp(pass ,pass_entry ) == 0){
            return 0 ;
        }else{
            return 1 ;
        }
    }
    mysql_free_result(result);
    mysql_close(con);

    exit(0);
}

void regestration_console(char *username, char *email, char *password){

    int id;
    char requete[255];

    MYSQL mysql;
    mysql_init(&mysql);
    mysql_options(&mysql,MYSQL_READ_DEFAULT_GROUP,"option");


    if(mysql_real_connect(&mysql,"localhost","root","mysql2016","notebook",3306,NULL,0))
    {

        sprintf(requete, "INSERT INTO account(user_id, username, email, password) VALUES('%d','%s', '%s', '%s')",
                id,username, email, password);

        mysql_query(&mysql, requete);
        mkdir(username, S_IRWXU);
        exit(EXIT_SUCCESS);

    }
    else
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
        int reponse_insc;
        char username_con[255] ;
        char password_con[255] ;
        char insc_email[255];
        char insc_password[255];
        char insc_username[255];

        //demande a l'utilisateur
        printf("Tappez 1 pour lignes de commandes  \n Tappez 2 pour interface graphique\n");
        scanf("%d", &reponse);


        //1 pour console
        if (reponse == 1 ){

            printf("Tappez 1 pour INSCRIPTION ou 2 pour CONNEXION \n");
            scanf("%d", &reponse_insc);

            if (reponse_insc == 1){
                printf("Entrez votre Username");
                scanf("%s", insc_username);

                printf("Entrez votre Email");
                scanf("%s", insc_email);

                printf("Entrez votre Mot de passe");
                scanf("%s", insc_password);

                regestration_console(insc_username, insc_email, insc_password);
            }
            else{
                printf("enter your username ");
                scanf("%s", &username_con);

                printf("enter your password ");
                scanf("%s", &password_con);

                if (login_console(password_con, username_con ) == 0 ){

                    opendir(username_con);

                int ch;

                printf("\n\n\t***********************************\n");

                printf("\t*Block Notes Personnel*\n");

                printf("\t***********************************");

                while(1)

                {

                    printf("\n\n\t\tMENU PRINCIPAL:");

                    printf("\n\n\tqjouter une note\t[1]");

                    printf("\n\tOuvrir une note\t[2]");

                    printf("\n\tModifier une note\t[3]");

                    printf("\n\tSupprimer une note\t[4]");

                    printf("\n\tSORTIE\t\t[5]");

                    printf("\n\n\tSAISISSEZ VOTRE CHOIX :");

                    scanf("%d",&ch);
    /*
                    switch(ch)

                    {

                        case 1:

                            add_note();

                            break;

                        case 2:

                            view_note();

                            break;

                        case 3:

                            edit_note();

                            break;

                        case 4:

                            delete_note();

                            break;

                        case 5:

                            printf("\n\n\t\tTHANK YOU FOR USING THE SOFTWARE ");

                            getch();

                            exit(0);

                        default:

                            printf("\nCe choix n'existe pas ..");

                            printf("\nRetappez un autre chiffre);

                            getch();

                            break;

                    }

                    system("cls");
    */
                }
                return 0;
            }
                else {
                printf("username or password incorrect !!");
            }
           }
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

        GtkWidget *button_next_page = gtk_builder_get_object(builder, "button_next_page");
        g_signal_connect(button_next_page, "clicked", G_CALLBACK(show_page), window2);

        g_object_unref (G_OBJECT (builder));
        g_object_unref (G_OBJECT (builder2));

        gtk_widget_show (app);
        gtk_main ();
/*
        if (login() == 1){
            printf("vous etes connecte");
        }else {
            printf("fausse manip");
        }
*/
            return 0;
        }

    }

