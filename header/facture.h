//
// Created by mesabo on 13/04/2021.
//

#ifndef PARKINGAUTOTO_FACTURE_H
#define PARKINGAUTOTO_FACTURE_H
extern void factureentree(MYSQL *con, char code[50], char immat[50]);
extern void facturesortie(MYSQL *con, char code[50], char immat[50], int montant);
#endif //PARKINGAUTOTO_FACTURE_H
