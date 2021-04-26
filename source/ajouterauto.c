//
// Created by mesabo on 08/04/2021.
//
#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>
#include "../header/ajouterauto.h"

void entreeauto(MYSQL *con, char immat[50]) {
    char requete[200] = "";
    sprintf(requete, "INSERT INTO autos(immat,entree) VALUES('%s',NOW());", immat);
    mysql_query(con, requete);
}

void sortieauto(MYSQL *con, char immat[50]) {
    char requete[200] = "";

    sprintf(requete, "UPDATE autos SET sortie = NOW() WHERE immat='%s' ORDER BY entree DESC LIMIT 1;", immat);
    mysql_query(con, requete);
}

char *tempspasse(MYSQL *con, char immat[50]) {
    char requete[200] = "";

    sprintf(requete,
            "SELECT TIMESTAMPDIFF(HOUR,entree,sortie) FROM autos WHERE immat='%s' ORDER BY sortie DESC LIMIT 1;",
            immat);
    mysql_query(con, requete);

    MYSQL_RES *result = mysql_store_result(con);
    if (result == NULL) {
        fprintf(stderr, "%s\n", mysql_error(con));
        mysql_close(con);
        exit(1);
    }

    int num_fields = mysql_num_fields(result);
    MYSQL_ROW row;
    char *tps;

    while ((row = mysql_fetch_row(result)) != 0) {
        for (int i = 0; i < num_fields; i++) {
            tps = row[0] ? row[0] : "NULL";
            // printf("LE TEMPS PASSE EN STATIONNEMENT EST DE %s SECONDES\n",row[0] ? row[0] : "NULL");

        }
    }
    mysql_free_result(result);
    printf("LE TEMPS PASSE EN STATIONNEMENT EST DE %s HEURES\n", tps);
    return tps;
}
