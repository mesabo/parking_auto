//
// Created by mesabo on 08/04/2021.
//
//
// Created by mesabo on 08/04/2021.
//
#include <stdio.h>
#include <mysql/mysql.h>

void factureentree(MYSQL *con, char code[50], char immat[50]) {
    char requete[200] = "";

    sprintf(requete,
            "INSERT INTO factures(place,auto) "
            "VALUES("
            "(SELECT id FROM places WHERE code='%s' LIMIT 1),"
            "(SELECT id FROM autos WHERE immat='%s' "
            "ORDER BY entree DESC LIMIT 1)"
            ");",
            code, immat);
    mysql_query(con, requete);
}

void facturesortie(MYSQL *con, char code[50], char immat[50], int montant) {
    char requete[255] = "";

    sprintf(requete,
            "UPDATE factures SET montant = '%d' WHERE auto = (SELECT id FROM autos WHERE immat='%s' ORDER BY entree DESC LIMIT 1) AND place = (SELECT id FROM places WHERE code='%s' ORDER BY id DESC LIMIT 1);",
            montant, immat, code);

    mysql_query(con, requete);
}

