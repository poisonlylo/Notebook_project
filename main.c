#include <stdio.h>
#include <mysql.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>
#include <sys/stat.h>
#include<curses.h>
#define getch() wgetch(stdscr)

struct info{
    char name[30];
    char time[6];
    FILE *fp_info;
} ;

GtkBuilder *builder;
GtkBuilder *builder2;
GtkWidget *app;
GtkWidget *app2;
GtkWidget *window2;
GtkEntry *tx_surname, *tx_email, *tx_password ;
GtkEntry *entry_username, *entry_password;
char pass[50];
char pass_entry[50];

void add_note( ){

    FILE *fp ;
    struct info e ;

    char another = 'O' ,time[10];
    char filename[15];
    int choice;

    printf("\n\n\tEntrez la date:[jj-mm-aaaa]:");

    fflush(stdin);

    gets(filename);

    fp = fopen (filename, "ab+" ) ;

    if ( fp == NULL){

        fp=fopen(filename,"wb+");

     /*   if(fp==NULL){
            printf("\nSYSTEM ERROR...");
            printf("\nPRESS ANY KEY TO EXIT");
            return ;
        } */

    }

    while ( another == 'O'|| another=='o' )

    {

        choice=0;

        fflush(stdin);

        printf ( "\n\tEntrez le temps:[hh:mm]:");

        scanf("%s",time);

        rewind(fp);

        while(fread(&e,sizeof(e),1,fp)==1)

        {

            if(strcmp(e.time,time)==0)

            {

                printf("\n\tLa note existe deja.\n");

                choice=1;

            }

        }

        if(choice==0)

        {

            strcpy(e.time,time);

            printf("\tEntrez le nom:");

            fflush(stdin);

            gets(e.name);

            fflush(stdin);


            printf("\tNote:");
            fopen(e.name, "ab+");
            gets(e.fp_info);
            fclose(e.fp_info);

            fwrite( &e, sizeof (e), 1, fp ) ;

            printf("\nLa note est ajoutée...\n");

        }

        printf ( "\n\tAjouter une nouvelle note...(O/N) " ) ;

        fflush ( stdin ) ;

        another = getchar( ) ;

    }

    fclose ( fp ) ;


}

/*
void editrecord()

{

    system("cls");

    FILE *fpte ;

    struct info e ;

    char time[6],choice,filename[14];

    int num,count=0;

    printf("\n\n\t\t*******************************\n");

    printf("\t\t* WELCOME TO THE EDITING MENU *");

    printf("\n\t\t*******************************\n\n");

    choice=password();

    if(choice!=0)

    {

        return ;

    }

    do

    {

        printf("\n\tEntrez la date de la note que vous voulez modifier:[jj-mm-aaaa]:");

        fflush(stdin);

        gets(filename);

        printf("\n\tEntrez le moment:[hh:mm]:");

        gets(time);

        fpte = fopen ( filename, "rb+" ) ;

        if ( fpte == NULL )

        {

            printf( "\nLa note n'existe pas:" ) ;

            printf("\nPRESS ANY KEY TO GO BACK");

            getch();

            return;

        }

        while ( fread ( &e, sizeof ( e ), 1, fpte ) == 1 )

        {

            if(strcmp(e.time,time)==0)

            {


                printf("\n\n\t\tQue est ce que vous voulez modifier?");

                printf("\n1.Moment.");
                printf("\n2.Note.");
                printf("\n3.Date.");

                do{

                    printf("\n\tEntrez votre choix:");

                    fflush(stdin);

                    scanf("%d",&num);

                    fflush(stdin);

                    switch(num)

                    {

                        case 1:
                            printf("\nEntrez le moment:");
                            gets(e.time);

                            break;

                        case 2:
                            printf("\nEntrez votre note:");
                            gets(e.note);

                            break;

                        case 3:
                            printf("\nENTER THE NEW DATA:");

                            printf("\nNEW MEETING PLACE:");

                            gets(customer.place);

                            break;

                        case 4:
                            printf("\nENTER THE NEW DATA:");

                            printf("\nDURATION:");

                            gets(customer.duration);

                            break;

                        case 5:
                            printf("ENTER THE NEW DATA:");

                            printf("\nNOTE:");

                            gets(customer.note);

                            break;

                        case 6:
                            printf("\nENTER THE NEW DATA:");

                            printf("\nNEW TIME:[hh:mm]:");

                            gets(customer.time);

                            printf("\nNEW MEETING PERSON:");

                            gets(customer.name);

                            printf("\nNEW MEETING PLACE:");

                            gets(customer.place);

                            printf("\nDURATION:");

                            gets(customer.duration);

                            printf("\nNOTE:");

                            gets(customer.note);

                            break;

                        case 7:
                            printf("\nPRESS ANY KEY TO GO BACK...\n");

                            getch();

                            return ;

                            break;

                        default:
                            printf("\nYOU TYPED SOMETHING ELSE...TRY AGAIN\n");

                            break;

                    }

                }
                while(num<1||num>8);

                fseek(fpte,-sizeof(customer),SEEK_CUR);

                fwrite(&customer,sizeof(customer),1,fpte);

                fseek(fpte,-sizeof(customer),SEEK_CUR);

                fread(&customer,sizeof(customer),1,fpte);

                choice=5;

                break;

            }

        }

        if(choice==5)

        {

            system("cls");

            printf("\n\t\tEDITING COMPLETED...\n");

            printf("--------------------\n");

            printf("THE NEW RECORD IS:\n");

            printf("--------------------\n");

            printf("\nTIME: %s",customer.time);

            printf("\nMEETING WITH: %s",customer.name);

            printf("\nMEETING AT: %s",customer.place);

            printf("\nDURATION: %s",customer.duration);

            printf("\nNOTE: %s",customer.note);

            fclose(fpte);

            printf("\n\n\tWOULD YOU LIKE TO EDIT ANOTHER RECORD.(Y/N)");

            scanf("%c",&choice);

            count++;

        }

        else

        {

            printf("\nTHE RECORD DOES NOT EXIST::\n");

            printf("\nWOULD YOU LIKE TO TRY AGAIN...(Y/N)");

            scanf("%c",&choice);

        }

    }
    while(choice=='Y'||choice=='y');

    fclose ( fpte ) ;

    if(count==1)

        printf("\n%d FILE IS EDITED...\n",count);

    else if(count>1)

        printf("\n%d FILES ARE EDITED..\n",count);

    else

        printf("\nNO FILES EDITED...\n");

    printf("\tPRESS ENTER TO EXIT EDITING MENU.");

    getch();

}
*/
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

void close_window(){
    gtk_main_quit();
}

void finish_with_error(MYSQL *con)
{
    fprintf(stderr, "%s\n", mysql_error(con));
    mysql_close(con);
    exit(1);
}

void login(GtkWidget *W,GtkEntry *data) {
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
            printf("vous etes connecte!");
        }else{
            printf("erreur de username ou password");
        }
    }
    mysql_free_result(result);
    mysql_close(con);

    exit(0);
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

                if (login_console(password_con, username_con) == 0 ){

                    opendir(username_con);

                int ch;

                printf("\n\n\t***********************************\n");

                printf("\t*Block Notes Personnel*\n");

                printf("\t***********************************");

                while(1)

                {

                    printf("\n\n\t\tMENU PRINCIPAL:");

                    printf("\n\n\tAjouter une note\t[1]");

                    printf("\n\tOUVRIR UN DOSSIER\t[2]");

                    printf("\n\tMODIFIER UN DOSSIER\t[3]");

                    printf("\n\tSUPPRIMER UN DOSSIER\t[4]");

                    printf("\n\tMODIFIER LE MOT DE PASSE\t[5]");

                    printf("\n\tSORTIE\t\t[6]");

                    printf("\n\n\tSAISISSEZ VOTRE CHOIX :");

                    scanf("%d",&ch);

                    switch(ch)

                    {

                        case 1:

                            add_note();

                            break;

                  /*      case 2:

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
                            */

                        case 6:

                            printf("\n\n\t\tTHANK YOU FOR USING THE SOFTWARE ");



                            exit(0);

                        default:

                            printf("\nYOU ENTERED WRONG CHOICE..");

                            printf("\nPRESS ANY KEY TO TRY AGAIN");



                            break;

                    }

                    system("cls");

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


        g_object_unref (G_OBJECT (builder));
        g_object_unref (G_OBJECT (builder2));


        gtk_widget_show (app);


        gtk_main ();

            return 0;
        }

    }






