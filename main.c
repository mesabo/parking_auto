//
// Created by mesabo on 16/04/2021.
//

#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>
#include "lire.c"
#include "./header/connexion.h"
#include "./header/createdb.h"
#include "./header/populate.h"
#include "./header/ajouterauto.h"
#include "./header/listerplaces.h"
#include "./header/marquerplace.h"
#include "./header/facture.h"


/// MES MACROS ET DEFINES
//prix pour voitures
#define VOITUREHEURE 500    /// ATTENTION A NE PAS CHANGER CECI
#define VOITUREJOUR 20000

//prix pour camions
#define CAMIONHEURE 700
#define CAMIONJOUR 30000

//prix pour engins a deux roues
#define DEUXROUESHEURE 200
#define DEUXROUESJOUR 10000


#define ENTREE "OPERATION D'ENTREE"
#define SORTIE "OPERATION DE SORTIE"

#define MSG_BIENVENU() printf("<<<<<<<<<<BIEMVENUE CHEZ MESABO AUTO>>>>>>>>>>\n");
#define MSG_BYE() printf("\n---------<<<<<<<<<<A bientot :)>>>>>>>>>>-----------\n");

#define MSG_QUITTER() printf("<<<<<<<<<<VOUS POUVEZ QUITTER À TOUT MOMENT EN APPUYANT SUR LE TOUCHE `0` >>>>>>>>>>\n");
#define MSG_MENU(titre) printf("-----<<<<<<<<<<%s>>>>>>>>>>-----\n",titre);\
printf("1. VOITURE\n"); \
printf("2. CAMION\n"); \
printf("3. ENGIN A DEUX ROUES\n"); \
printf("Quel est votre choix (1-3)? :");

#define MSG_AUTRE_PLACE_CAMION() printf("VOULEZ-VOUS PRENDRE UNE PLACE POUR CAMION ?\n");\
printf("répondez par 1 (oui) ou 0 (non)? : ");

#define MSG_AUTRE_PLACE_VOITURE() printf("VOULEZ-VOUS PRENDRE UNE PLACE POUR VOITURE ?\n");\
printf("répondez par 1 (oui) ou 0 (non)? : ");

#define MSG_CODE() printf("code de la place: ");
#define MSG_IMMAT() printf("immatriculation du véhicule: ");

#define MSG_OPERATION() printf("QUELLE OPÉRATION VOULEZ-VOUS EFFECTUER?\n");\
printf("1. ENTREE\n"); \
printf("2. SORTIE\n");                                                      \
printf("Quel est votre choix (1 - 2)? :");

#define MSG_RESERVE(code, immat) printf("Vous avez réservé la place %s pour le véhicule immatriculé %s\n\n",code,immat);

#define MSG_PLACE_DISPO_VOITURE() printf("LISTE DES PLACES DISPONIBLES POUR VOITURE\n");
#define MSG_PLACE_DISPO_CAMION() printf("LISTE DES PLACES DISPONIBLES POUR CAMION\n");
#define MSG_PLACE_DISPO_ENGINS_DEUX_ROUES() printf("LISTE DES PLACES DISPONIBLES POUR ENGINS_DEUX_ROUES\n");

/// fin des macros et defines
/// PREPROCESSEURS

void main() {
    char username[50];
    char user_password[50];
    char db_name[50];
    char table_name[50];
    char login[50];
    /// en ce qui concerne les infos de l'engin
    char immat[50];
    char entree[50];
    char sortie[50];
    /// en ce qui concerne les infos de la place
    char code[50];
    char type[50];
    char etat[50];
    /// en ce qui concerne les infos de la facture

    int TPS;
    int montant = 0;


    char choix[10];
    char option[10];
    char question_initialisation[10];
    int idx;

    MYSQL *con = mysql_init(NULL);
    printf("==========CONNEXION A LA BASE DE DONNEES ============\n");
    printf("========== SAISIR VOS INFORMATIONS DE BASE DE DONNEES POUR Y ACCEDER ============\n");
    printf("DB username: ");
    lire(username, 50);
    printf("DB password: ");
    lire(user_password, 50);

    /// CONNEXION A LA BD AVEC UNAME ET PWD
    connexion(con, username, user_password, NULL);
    /// CREATION DE LA DB SI NON EXISTANTE
    initdb(con);
    con = mysql_init(NULL);
    // ON PROCEDE A LA CONNEXION
    if (con == NULL) {
        fprintf(stderr, "mysql_init() failed\n");
        exit(1);
    }
    connexion(con, username, user_password, "parkingdb");

    printf("Votre premier acces a la bd?\ntaper 1 pour oui\ntaper autre pour non\nreponse:>>> ");
    lire(question_initialisation, 50);

    int rep;
    if (rep = atoi(question_initialisation) == 1) {
        createdatabase(con);
        insert_vehicule(con);
        insert_camions(con);
        insert_2roues(con);
    }

    printf("Connexion a la BD avec succes.\n");

    ///MESSAGE ACCUEIL
    MSG_BIENVENU();

    /// EN PLEIN DE LE MILE
    do {
        MSG_OPERATION();
        lire(option, 50);
        int opt; ///option: entier
        int ch;/// choix: entier
        switch (opt = atoi(option)) {
            case 1:
            MSG_MENU(ENTREE);
                lire(choix, 50);
                /// DEBUT OPERATIONS D'ENTREE DE VEHICULES
                switch (ch = atoi(choix)) {
                    case 1:
                        /// RESERVATION POUR VOITURE
                        MSG_PLACE_DISPO_VOITURE();
                        listerplacesvoituresdisponibles(con);///LISTER PLACES
                        MSG_CODE();
                        lire(code, 50);
                        MSG_IMMAT();
                        lire(immat, 50);

                        entreeauto(con, immat);///ENREGISTRER LA VOITURE
                        occuperplace(con, code);/// MARQUER LA PLACE `OCCUPEE`
                        factureentree(con, code, immat);/// ETABLIR UN DEVIS (SEMI-FACTURE SANS MONTANT A PAYER)

                        MSG_RESERVE(code, immat);///MESSAGE DE NOTIFICATION DE L'OPERATION EFFECTUEE
                        break;
                    case 2:
                        /// RESERVATION POUR CAMION
                        MSG_PLACE_DISPO_CAMION();
                        listerplacescamionsdisponibles(con);///LISTER PLACES
                        MSG_CODE();
                        lire(code, 50);
                        MSG_IMMAT();
                        lire(immat, 50);

                        entreeauto(con, immat);///ENREGISTRER LA CAMION
                        occuperplace(con, code);/// MARQUER LA PLACE `OCCUPEE`
                        factureentree(con, code, immat);/// ETABLIR UN DEVIS (SEMI-FACTURE SANS MONTANT A PAYER)

                        MSG_RESERVE(code, immat);///MESSAGE DE NOTIFICATION DE L'OPERATION EFFECTUEE
                        break;
                    case 3:
                        /// RESERVATION POUR ENGINS_DEUX_ROUES
                        MSG_PLACE_DISPO_ENGINS_DEUX_ROUES();
                        listerplacesdeuxrouesdisponibles(con);///LISTER PLACES
                        MSG_CODE();
                        lire(code, 50);
                        MSG_IMMAT();
                        lire(immat, 50);

                        entreeauto(con, immat);///ENREGISTRER ENGIN_DEUX_ROUES
                        occuperplace(con, code);/// MARQUER LA PLACE `OCCUPEE`
                        factureentree(con, code, immat);/// ETABLIR UN DEVIS (SEMI-FACTURE SANS MONTANT A PAYER)

                        MSG_RESERVE(code, immat);///MESSAGE DE NOTIFICATION DE L'OPERATION EFFECTUEE
                        break;
                    default:
                        break;
                }
                break;/// FIN OPERATIONS D'ENTREE DE VEHICULES

            case 2:/// FIN OPERATIONS D'ENTREE DE VEHICULES
            MSG_MENU(SORTIE);
                lire(choix, 50);
                switch (ch = atoi(choix)) {
                    case 1:///VOITURE
                        MSG_CODE();
                        lire(code, 50);
                        MSG_IMMAT();
                        lire(immat, 50);

                        TPS = atoi(tempspasse(con, immat));/// CALCULER LE TEMPS PASSE DANS LE PARKING

                        sortieauto(con, immat);///ENREGISTRER LA DATE DE SORTIE LA VOITURE DU PARKING
                        if (TPS < 24) {/// temps passe inferieur a 24h, prix/h
                            montant = VOITUREHEURE * TPS;
                            facturesortie(con, code, immat, montant);/// ETABLIR UN FACTURE
                            printf("********** FACTURE STATIONNEMENT VOITURE**********\ntemps stationnement:  %d heures\nvoiture <<%s>> a la place <<%s>>\nla facture s'eleve a %d \n\n",
                                   TPS, immat, code, montant);
                        } else {/// temps passe superieur ou egal a 24h, prix/j = VOITUREJOUR
                            montant = VOITUREJOUR * (TPS%24);
                            facturesortie(con, code, immat, montant);/// ETABLIR UN FACTURE
                            printf("********** FACTURE STATIONNEMENT VOITURE**********\ntemps stationnement:  %d jours\nvoiture <<%s>> a la place <<%s>>\nla facture s'eleve a %d \n\n",
                                   TPS%24, immat, code, montant);
                        }
                        libererplace(con, code);/// MARQUER LA PLACE `LIBRE`

                        break;
                    case 2:///CAMION
                        MSG_CODE();
                        lire(code, 50);
                        MSG_IMMAT();
                        lire(immat, 50);

                        TPS = atoi(tempspasse(con, immat));/// CALCULER LE TEMPS PASSE DANS LE PARKING

                        sortieauto(con, immat);///ENREGISTRER LA DATE DE SORTIE LA CAMION DU PARKING
                        if (TPS < 24) {/// temps passe inferieur a 24h, prix/h
                            montant = CAMIONHEURE * TPS;
                            facturesortie(con, code, immat, montant);/// ETABLIR UN FACTURE
                            printf("********** FACTURE STATIONNEMENT CAMION**********\ntemps stationnement:  %d heures\nvoiture <<%s>> a la place <<%s>>\nla facture s'eleve a %d \n\n",
                                   TPS, immat, code, montant);
                        } else {/// temps passe superieur ou egal a 24h, prix/j = CAMIONJOUR
                            montant = CAMIONJOUR * (TPS%24);
                            facturesortie(con, code, immat, montant);/// ETABLIR UN FACTURE
                            printf("********** FACTURE STATIONNEMENT CAMION**********\ntemps stationnement:  %d jours\nvoiture <<%s>> a la place <<%s>>\nla facture s'eleve a %d \n\n",
                                   TPS%24, immat, code, montant);
                        }
                        libererplace(con, code);/// MARQUER LA PLACE `LIBRE`

                        break;
                    case 3:///ENGIN A DEUX ROUES
                        MSG_CODE();
                        lire(code, 50);
                        MSG_IMMAT();
                        lire(immat, 50);

                        TPS = atoi(tempspasse(con, immat));/// CALCULER LE TEMPS PASSE DANS LE PARKING
                        sortieauto(con, immat);///ENREGISTRER LA DATE DE SORTIE LA DEUX_ROUES DU PARKING
                        if (TPS < 24) {/// temps passe inferieur a 24h, prix/h
                            montant = DEUXROUESHEURE * TPS;
                            printf("********** FACTURE STATIONNEMENT VOITURE**********\nprix unitaire: %d heures\nvoiture <<%s>> a la place <<%s>>\nla facture s'eleve a %d \n\n",
                                   TPS, immat, code, montant);
                        } else {/// temps passe superieur ou egal a 24h, prix/j = VOITUREJOUR
                            montant = DEUXROUESJOUR * (TPS%24);
                            printf("********** FACTURE STATIONNEMENT VOITURE**********\nprix unitaire:  %d jours\nvoiture <<%s>> a la place <<%s>>\nla facture s'eleve a %d \n\n",
                                   TPS%24, immat, code, montant);
                        }
                        libererplace(con, code);/// MARQUER LA PLACE `LIBRE`


                        break;
                    default:
                        break;
                }
                break;
                /// FIN OPERATIONS SORTIE DE VEHICULES
            case 0:
                MSG_BYE();
                exit(0);
                break;
            default:
                printf("Saisir une valeur correct entre (0-1)!");
        }
    } while (option != 0);
}
