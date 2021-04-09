#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>
#include <string.h>

// INSERTION DE DONNER DANS LA DB
void add_data(MYSQL *con) {
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
    /// REMPLISSAGE DE LA BIBLIOTHEQUE DE LIVRES
    printf("==========Remplissage de la bibliotheque...===================\n");
/// VOITURES
    printf("....\n");
    if (mysql_query(con, "INSERT INTO places(ID,code,type,etat) VALUES(1,'PL21A','VOITURE',0)")) {
        fprintf(stderr, "%s\n", mysql_error(con));
        mysql_close(con);
        exit(1);
    }
    printf("....\n");
    if (mysql_query(con, "INSERT INTO places(ID,code,type,etat) VALUES(2,'PL21B','VOITURE',0)")) {
        fprintf(stderr, "%s\n", mysql_error(con));
        mysql_close(con);
        exit(1);
    }
    printf("....\n");
    if (mysql_query(con, "INSERT INTO places(ID,code,type,etat) VALUES(3,'PL21C','VOITURE',0)")) {
        fprintf(stderr, "%s\n", mysql_error(con));
        mysql_close(con);
        exit(1);
    }
    printf("....\n");
    if (mysql_query(con, "INSERT INTO places(ID,code,type,etat) VALUES(4,'PL21D','VOITURE',0)")) {
        fprintf(stderr, "%s\n", mysql_error(con));
        mysql_close(con);
        exit(1);
    }
    printf("....\n");
    if (mysql_query(con, "INSERT INTO places(ID,code,type,etat) VALUES(5,'PL21E','VOITURE',0)")) {
        fprintf(stderr, "%s\n", mysql_error(con));
        mysql_close(con);
        exit(1);
    }
/// CAMIONS
    printf("....\n");
    if (mysql_query(con, "INSERT INTO places(ID,code,type,etat) VALUES(6,'PL21F','CAMIONS',0)")) {
        fprintf(stderr, "%s\n", mysql_error(con));
        mysql_close(con);
        exit(1);
    }
    printf("....\n");
    if (mysql_query(con, "INSERT INTO places(ID,code,type,etat) VALUES(7,'PL21G','CAMIONS',0)")) {
        fprintf(stderr, "%s\n", mysql_error(con));
        mysql_close(con);
        exit(1);
    }
    printf("....\n");
    if (mysql_query(con, "INSERT INTO places(ID,code,type,etat) VALUES(8,'PL21H','CAMIONS',0)")) {
        fprintf(stderr, "%s\n", mysql_error(con));
        mysql_close(con);
        exit(1);
    }
    printf("....\n");
    if (mysql_query(con, "INSERT INTO places(ID,code,type,etat) VALUES(9,'PL21I','CAMIONS',0)")) {
        fprintf(stderr, "%s\n", mysql_error(con));
        mysql_close(con);
        exit(1);
    }
    printf("....\n");
    if (mysql_query(con, "INSERT INTO places(ID,code,type,etat) VALUES(10,'PL21J','CAMIONS',0)")) {
        fprintf(stderr, "%s\n", mysql_error(con));
        mysql_close(con);
        exit(1);
    }
/// ENGINS A DEUX_ROUES
    printf("....\n");
    if (mysql_query(con, "INSERT INTO places(ID,code,type,etat) VALUES(11,'PL21K','DEUX_ROUES',0)")) {
        fprintf(stderr, "%s\n", mysql_error(con));
        mysql_close(con);
        exit(1);
    }
    printf("....\n");
    if (mysql_query(con, "INSERT INTO places(ID,code,type,etat) VALUES(12,'PL21L','DEUX_ROUES',0)")) {
        fprintf(stderr, "%s\n", mysql_error(con));
        mysql_close(con);
        exit(1);
    }
    printf("....\n");
    if (mysql_query(con, "INSERT INTO places(ID,code,type,etat) VALUES(13,'PL21M','DEUX_ROUES',0)")) {
        fprintf(stderr, "%s\n", mysql_error(con));
        mysql_close(con);
        exit(1);
    }
    printf("....\n");
    if (mysql_query(con, "INSERT INTO places(ID,code,type,etat) VALUES(14,'PL21N','DEUX_ROUES',0)")) {
        fprintf(stderr, "%s\n", mysql_error(con));
        mysql_close(con);
        exit(1);
    }
    printf("....\n");
    if (mysql_query(con, "INSERT INTO places(ID,code,type,etat) VALUES(15,'PL21O','DEUX_ROUES',0)")) {
        fprintf(stderr, "%s\n", mysql_error(con));
        mysql_close(con);
        exit(1);
    }

    printf("===========Remplissage de la bibliotheque termine=================\n");
}