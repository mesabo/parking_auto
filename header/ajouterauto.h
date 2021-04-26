//
// Created by mesabo on 13/04/2021.
//
#ifndef PARKINGAUTOTO_AJOUTERAUTO_H
#define PARKINGAUTOTO_AJOUTERAUTO_H

void entreeauto(MYSQL *con, char immat[50]);

void sortieauto(MYSQL *con, char immat[50]);

char *tempspasse(MYSQL *con, char immat[50]);

#endif //PARKINGAUTOTO_AJOUTERAUTO_H
