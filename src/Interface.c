#include "Interface.h"
// ---- FONCTIONS ---- //

void sautLignes(int n) {
    int i=0;
    for(i; i < n ;i++) {
        printf("\n");
    }
}

void afficherMenuPrincipal() {
    printf("\n=======================================");
    printf("\n================= COF =================");
    printf("\n=======================================");
    printf("\n             COnnected Food            ");
    printf("\n\n");
    printf("Menu principal");
    printf("\n");
    printf("\n1. Enregistrer un nouvel aliment");
    printf("\n2. Consulter la listes des aliments en stock");
    printf("\n3. Menu 3");
    printf("\n");
}
