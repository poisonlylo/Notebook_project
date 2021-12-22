#include <stdio.h>
#include <mysql.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>

GtkWidget *notebook;

typedef struct{
    char *label;
    char sub_items;
    char sub_menu[6][15];
}MuButton;

MuButton menulist[] = {
          {"file", 6, {"new", "open","save", "save as", "close", "quit" }},
         {"edit", 4,{"copy", "paste","cut", "delete"} }
};

void close_tab(){
    g_print("close tab");
}

void add_tab(char *name){
GtkWidget *textview = gtk_text_view_new();
GtkWidget *text = gtk_label_new(name);
GtkWidget *label = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
GtkWidget *icon = gtk_image_new_from_file("close.png");
GtkWidget *button = gtk_button_new();
gtk_button_set_image(GTK_BUTTON(button), icon);
gtk_box_pack_start(label,text, TRUE, TRUE, 0);
gtk_box_pack_start(label,button, FALSE, FALSE, 0);
    g_signal_connect(button, "clicked", G_CALLBACK(close_tab), NULL);
GtkWidget *scroll_window = gtk_scrolled_window_new(NULL, NULL);
    gtk_container_add(scroll_window, textview);
    gtk_notebook_append_page(GTK_NOTEBOOK(notebook), scroll_window, label);
    gtk_widget_show_all(label);
    gtk_widget_show_all(scroll_window);

}

void button_click(GtkWidget *button, gpointer data){
    char *btn = (char*)data ;
    if (strcmp(btn, "new") == 0) add_tab("new tab");


}



void make_notebook(GtkWidget *vbox){
 notebook = gtk_notebook_new();
    gtk_box_pack_start(vbox,  notebook, TRUE, TRUE, 0);
    add_tab("untiteled");
}
void close_window(){
     gtk_main_quit();
}
void make_nemu(GtkWidget *vbox){
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
    make_nemu(vbox);
    make_notebook(vbox);
    gtk_widget_show_all(window);
}


    int main(int argc, char **argv){

        gtk_init(&argc, &argv);
        make_window();

        gtk_main();

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
return 0;

    }

