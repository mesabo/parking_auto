#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>
#include "tests.c"
#include "lire.c"
#include "connexion.c"
#include "createdb.c"
#include "populate.c"
#include "ajouterauto.c"
#include "listerplaces.c"
#include "marquerplace.c"
#include "facture.c"

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


///P R E P R O C E S S E U R S
//void finish_with_error(MYSQL *con);


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
    int place;
    int autom;
    int TPS;
    int montant = 0;

    int theid = 0;
    char reponsedb[10];
    char choix[10];
    char option[10];
    int idx;
    ///



    MYSQL *con = mysql_init(NULL);


    printf("==========CONNEXION A LA BASE DE DONNEES ============\n");
    /* printf("========== SAISIR VOS INFORMATIONS DE BASE DE DONNEES POUR Y ACCEDER ============\n");
     printf("DB username: ");
     lire(username, 50);
     printf("DB password: ");
     lire(user_password, 50);*/

    connexion(con, "root", "hamilton", "parkingdb");
    /// CREATION DE LA DB SI NON EXISTANTE
    bool condition = false;
    if (condition) {
        initdb(con);
        MYSQL *con = mysql_init(NULL);
        // ON PROCEDE A LA CONNEXION
        if (con == NULL) {
            fprintf(stderr, "mysql_init() failed\n");
            exit(1);
        }
        connexion(con, "root", "hamilton", "parkingdb");
        add_data(con);
        printf("Vous etes connecté\n");
    }

    MSG_BIENVENU();
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
                            printf("********** FACTURE STATIONNEMENT VOITURE**********\ntemps stationnement:  %d\nvoiture %s a la place %s\nla facture s'eleve a %d \n\n",
                                   TPS, immat, code, montant);
                        } else {/// temps passe superieur ou egal a 24h, prix/j = VOITUREJOUR
                            montant = VOITUREJOUR * TPS;
                            facturesortie(con, code, immat, montant);/// ETABLIR UN FACTURE
                            printf("********** FACTURE STATIONNEMENT VOITURE**********\ntemps stationnement:  %d\nvoiture %s a la place %s\nla facture s'eleve a %d \n\n",
                                   TPS, immat, code, montant);
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
                            printf("********** FACTURE STATIONNEMENT CAMION**********\ntemps stationnement:  %d\nvoiture %s a la place %s\na facture s'eleve a %d \n\n",
                                   TPS, immat, code, montant);
                        } else {/// temps passe superieur ou egal a 24h, prix/j = CAMIONJOUR
                            montant = CAMIONJOUR * TPS;
                            facturesortie(con, code, immat, montant);/// ETABLIR UN FACTURE
                            printf("********** FACTURE STATIONNEMENT CAMION**********\ntemps stationnement:  %d\nvoiture %s a la place %s\na facture s'eleve a %d \n\n",
                                   TPS, immat, code, montant);
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
                            printf("********** FACTURE STATIONNEMENT VOITURE**********\nprix unitaire: %d \nvoiture %s a la place %s\na facture s'eleve a %d \n\n",
                                   TPS, immat, code, montant);
                        } else {/// temps passe superieur ou egal a 24h, prix/j = VOITUREJOUR
                            montant = DEUXROUESJOUR * TPS;
                            printf("********** FACTURE STATIONNEMENT VOITURE**********\nprix unitaire:  %d\nvoiture %s a la place %s\na facture s'eleve a %d \n\n",
                                   TPS, immat, code, montant);
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
// 6132JE01 PL21C
//////////////////////////////////////////////////////////////////////
/*
void finish_with_error(MYSQL *con) {
    fprintf(stderr, "%s\n", mysql_error(con));
    mysql_close(con);
    exit(1);
}
*/
/*printf("ENTRER CODE IMMATRICULATION DE L'ENGIN A L'ENTREE: ");
lire(immat, 50);
entreeauto(con, immat);
printf("ENTRER CODE IMMATRICULATION DE L'ENGIN A LA SORTIE: ");
lire(immat, 50);
sortieauto(con, immat);*/

/// liste des places dispo ou pas
/*  printf("<<<<<<<<<<VOICI LES PLACES ENREGISTREES DANS LE PARKING>>>>>>>>>>\n");
  listerplaces(con);*/

/* printf("<<<<<<<<<<VOICI LES PLACES OCCUPEES DANS LE PARKING>>>>>>>>>>\n");
 listerplacesoccupees(con);*/
/*
    printf("<<<<<<<<<<VOICI LES PLACES DISPONIBLES DANS LE PARKING>>>>>>>>>>\n");
    listerplacesdisponibles(con);

    printf("ENTRER CODE DE LA PLACE A OCCUPER: ");
    lire(code, 50);

    printf("ENTRER CODE IMMATRICULATION DE L'ENGIN A L'ENTREE: ");
    lire(immat, 50);
    entreeauto(con, immat);
    factureentree(con,code,immat);*/

/*
    printf("ENTRER CODE IMMATRICULATION DE L'ENGIN A LA SORTIE: ");
    lire(immat, 50);
    TPS = atoi(tempspasse(con, immat));

    printf("ENTRER CODE DE LA PLACE OCCUPEE: ");
    lire(code, 50);

    if (TPS < 2) {
        montant= VOITUREHEURE * TPS;
       // strcpy(montant, VOITUREHEURE * TPS);
        facturesortie(con, code, immat, montant);
    } else {
        montant= VOITUREJOUR * TPS;
        //strcpy(montant, VOITUREJOUR * TPS);
        facturesortie(con, code, immat, montant);
    }
*/
