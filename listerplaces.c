//
// Created by mesabo on 08/04/2021.
//

#include <mysql/mysql.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void listerplaces(MYSQL *con) {

    if (mysql_query(con, "SELECT * FROM places")) {
        fprintf(stderr, "%s\n", mysql_error(con));
        mysql_close(con);
        exit(1);
    }

    MYSQL_RES *result = mysql_store_result(con);

    if (result == NULL) {
        fprintf(stderr, "%s\n", mysql_error(con));
        mysql_close(con);
        exit(1);
    }

    int num_fields = mysql_num_fields(result);

    MYSQL_ROW row;

    while ((row = mysql_fetch_row(result))) {
        for (int i = 0; i < num_fields; i++) {
            printf("[%s] ", row[i] ? row[i] : "NULL");
        }

        printf("\n");
    }

    mysql_free_result(result);
}

/// LISTE DES PLACES DISPONIBLES EN TOUT
void listerplacesdisponibles(MYSQL *con) {

    if (mysql_query(con, "SELECT * FROM places WHERE etat=0")) {
        fprintf(stderr, "%s\n", mysql_error(con));
        mysql_close(con);
        exit(1);
    }

    MYSQL_RES *result = mysql_store_result(con);

    if (result == NULL) {
        fprintf(stderr, "%s\n", mysql_error(con));
        mysql_close(con);
        exit(1);
    }

    int num_fields = mysql_num_fields(result);

    MYSQL_ROW row;

    while ((row = mysql_fetch_row(result))) {
        for (int i = 0; i < num_fields; i++) {
            printf("[%s] ", row[i] ? row[i] : "NULL");
        }

        printf("\n");
    }

    mysql_free_result(result);
}

/// LISTE DES PLACES DISPONIBLES POUR VOITURE
void listerplacesvoituresdisponibles(MYSQL *con) {

    if (mysql_query(con, "SELECT code,type FROM places WHERE type='VOITURES' AND etat=0")) {
        fprintf(stderr, "%s\n", mysql_error(con));
        mysql_close(con);
        exit(1);
    }

    MYSQL_RES *result = mysql_store_result(con);

    if (result == NULL) {
        fprintf(stderr, "%s\n", mysql_error(con));
        mysql_close(con);
        exit(1);
    }

    int num_fields = mysql_num_fields(result);

    MYSQL_ROW row;

    while ((row = mysql_fetch_row(result))) {
        for (int i = 0; i < num_fields; i++) {
            printf("[%s] ", row[i] ? row[i] : "NULL");
        }

        printf("\n");
    }

    mysql_free_result(result);
}

///LISTE DES PLACES DISPONIBLES POUR CAMION
void listerplacescamionsdisponibles(MYSQL *con) {

    if (mysql_query(con, "SELECT * FROM places WHERE type='CAMIONS' AND etat=0")) {
        fprintf(stderr, "%s\n", mysql_error(con));
        mysql_close(con);
        exit(1);
    }

    MYSQL_RES *result = mysql_store_result(con);

    if (result == NULL) {
        fprintf(stderr, "%s\n", mysql_error(con));
        mysql_close(con);
        exit(1);
    }

    int num_fields = mysql_num_fields(result);

    MYSQL_ROW row;

    while ((row = mysql_fetch_row(result))) {
        for (int i = 0; i < num_fields; i++) {
            printf("[%s] ", row[i] ? row[i] : "NULL");
        }

        printf("\n");
    }

    mysql_free_result(result);
}

///LISTE DES PLACES DISPONIBLES POUR ENGINS A DEUX ROUES
void listerplacesdeuxrouesdisponibles(MYSQL *con) {

if (mysql_query(con, "SELECT * FROM places WHERE type='DEUX_ROUES' AND etat=0")) {
fprintf(stderr, "%s\n", mysql_error(con));
mysql_close(con);
exit(1);
}

MYSQL_RES *result = mysql_store_result(con);

if (result == NULL) {
fprintf(stderr, "%s\n", mysql_error(con));
mysql_close(con);
exit(1);
}

int num_fields = mysql_num_fields(result);

MYSQL_ROW row;

while ((row = mysql_fetch_row(result))) {
for (int i = 0; i < num_fields; i++) {
printf("[%s] ", row[i] ? row[i] : "NULL");
}

printf("\n");
}

mysql_free_result(result);
}

///LISTE DES PLACES OCCUPEES EN GENERALE
void listerplacesoccupees(MYSQL *con) {

    if (mysql_query(con, "SELECT * FROM places WHERE etat=1")) {
        fprintf(stderr, "%s\n", mysql_error(con));
        mysql_close(con);
        exit(1);
    }

    MYSQL_RES *result = mysql_store_result(con);

    if (result == NULL) {
        fprintf(stderr, "%s\n", mysql_error(con));
        mysql_close(con);
        exit(1);
    }

    int num_fields = mysql_num_fields(result);

    MYSQL_ROW row;

    while ((row = mysql_fetch_row(result))) {
        for (int i = 0; i < num_fields; i++) {
            printf("[%s] ", row[i] ? row[i] : "NULL");
        }

        printf("\n");
    }

    mysql_free_result(result);
}