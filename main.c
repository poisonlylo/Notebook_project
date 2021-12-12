#include <stdio.h>
#include <mysql.h>
#include <stdlib.h>

    int main(int argc, char **argv){

        MYSQL mysql;
        mysql_init(&mysql);
        mysql_options(&mysql,MYSQL_READ_DEFAULT_GROUP,"option");

        if(mysql_real_connect(&mysql,"localhost","root","mysql2016","notebook",3306,NULL,0))
        {
            mysql_query(&mysql, "SELECT * FROM account");
            MYSQL_RES *result = NULL;
            MYSQL_ROW row;
            int i = 1;

            //On met le jeu de résultat dans le pointeur result
            result = mysql_use_result(&mysql);
            //Tant qu'il y a encore un résultat ...
            while ((row = mysql_fetch_row(result)))
            {
                printf("Resultat %ld\n", i);
                i++;
            }
            //Libération du jeu de résultat
            mysql_free_result(result);
            mysql_close(&mysql);
        }
        else
        {
            printf("Une erreur s'est produite lors de la connexion à la BDD!");
        }

        return 0;
    }

