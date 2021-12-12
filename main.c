#include <stdio.h>
#include <mysql.h>
#include <stdlib.h>
#include <string.h>

    int main(int argc, char **argv){

        char username[255];
        char password[255];
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
            mysql_close(&mysql);
        }
        else
        {
            printf("Une erreur s'est produite lors de la connexion à la BDD!");
        }

        return 0;
    }

