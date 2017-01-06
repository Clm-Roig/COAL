#include "Camera.h"

// ---- CONSTANTES ---- //
const char* CHEMIN_IMAGES_ALIMENTS = "data/images_aliments/";

// ---- FONCTIONS ---- //

int demarrerCam() {
    return 0;
}

int prendrePhoto(char* idPesee) {
    // Pour plus d'infos :
    // https://www.raspberrypi.org/wp-content/uploads/2013/07/RaspiCam-Documentation.pdf

    // raspistill permet de prendre une photo
    // -n annule la preview de la photo
    // -t delai avant prise de la photo
    // -w et -h hauteur et largeur de 1000pxls
    // -e spécifie l'encodage de la photo

    char* fonction = "raspistill -n -t 100 -w 1000 -h 1000 -e bmp -o ";

    char* chemin = malloc(50*sizeof(char));
    strcat(chemin,CHEMIN_IMAGES_ALIMENTS);
    strcat(chemin,idPesee);
    char* extension = ".bmp";

    char* exec = malloc(200*sizeof(char));
    strcat(exec,fonction);
    strcat(exec,"\"");
    strcat(exec,chemin);
    strcat(exec,extension);
    strcat(exec,"\"");

    system(exec);

    return 1;
}
