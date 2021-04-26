//
// Created by mesabo on 09/04/2021.
//
#include <stdio.h>
#include <mysql/mysql.h>
#include "../header/marquerplace.h"

void occuperplace(MYSQL *con, char code[50]) {
    char requete[200] = "";

    sprintf(requete, "UPDATE places SET etat = 1 WHERE code='%s' LIMIT 1;", code);
    mysql_query(con, requete);
}

void libererplace(MYSQL *con, char code[50]) {
    char requete[200] = "";

    sprintf(requete, "UPDATE places SET etat = 0 WHERE code='%s' LIMIT 1;", code);
    mysql_query(con, requete);
}
