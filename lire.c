#include <stdio.h>
#include <string.h>


int lire(char *chaine, int longueur) {
    char *positionEntree = NULL;
    // On lit le texte saisi au clavier
    if (fgets(chaine, longueur, stdin) != NULL) // Pas d'erreur desaisie ?
    {
        positionEntree = strchr(chaine, '\n'); // On recherche l'"Entrée"

        if (positionEntree != NULL) // Si on a trouvé le retour à la ligne
        {
            *positionEntree = '\0'; // On remplace ce caractère par\0
        }
        printf("\n");
        return 1; // On renvoie 1 si la fonction s'est déroulée sans erreur
    } else {
        return 0; // On renvoie 0 s'il y a eu une erreur
    }
}