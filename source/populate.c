#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>
#include "../header/populate.h"

// INSERTION DE DONNER DANS LA DB
void createdatabase(MYSQL *con) {
    ///CREATION DES TABLES A NOUVEAU
    if (mysql_query(con,
                    "CREATE TABLE IF NOT EXISTS places(id INT PRIMARY KEY, code VARCHAR(255),type VARCHAR(255),etat int )")) {
        fprintf(stderr, "%s\n", mysql_error(con));
        mysql_close(con);
        exit(1);
    }
    if (mysql_query(con,
                    "CREATE TABLE IF NOT EXISTS autos(id INT PRIMARY KEY AUTO_INCREMENT, immat VARCHAR(255), entree DATETIME, sortie DATETIME)")) {
        fprintf(stderr, "%s\n", mysql_error(con));
        mysql_close(con);
        exit(1);
    }
    if (mysql_query(con,
                    "CREATE TABLE IF NOT EXISTS factures(id INT PRIMARY KEY AUTO_INCREMENT, place INT,auto INT,montant VARCHAR(255),FOREIGN KEY (place) REFERENCES places(id),FOREIGN KEY (auto) REFERENCES autos(id))")) {
        fprintf(stderr, "%s\n", mysql_error(con));
        mysql_close(con);
        exit(1);
    }
}

void insert_vehicule(MYSQL *con) {
    /// REMPLISSAGE DE LA BIBLIOTHEQUE DE LIVRES
    printf("==========Remplissage de la bibliotheque...===================\n");
/// VOITURES
    printf("....\n");
    char requete[200] = "";
    int cpt = 1;
    while (cpt <= 5) {
        sprintf(requete, "INSERT INTO places(id,code,type,etat) VALUES('%d','PLV%d','VOITURE',0);", cpt, cpt);
        mysql_query(con, requete);
        cpt = cpt + 1;
    }
    printf("==========Remplissage des place pour voiture dans la bd termine....===================\n");
}


void insert_camions(MYSQL *con) {
    printf("....\n");
    char requete[200] = "";
    int cpt = 6;

    while (cpt <= 10) {
        sprintf(requete, "INSERT INTO places(id,code,type,etat) VALUES('%d','PLC%d','CAMIONS',0);", cpt, cpt);
        mysql_query(con, requete);
        cpt = cpt + 1;
    }
    printf("==========Remplissage des place pour camion dans la bd termine...===================\n");
}

void insert_2roues(MYSQL *con) {
    printf("....\n");
    char requete[200] = "";
    int cpt = 11;

    while (cpt <= 15) {
        sprintf(requete, "INSERT INTO places(id,code,type,etat) VALUES('%d','PLDR%d','DEUX_ROUES',0);", cpt, cpt);
        mysql_query(con, requete);
        cpt = cpt + 1;
    }
    printf("==========Remplissage des place pour 2 roues dans la bd termine...===================\n");
}
