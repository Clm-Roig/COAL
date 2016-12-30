#include "BDD.h"

// ---- LECTURE ---- //
int nbLignesFichier(FILE* fichier) {
    int nbLignes = 0;
    char* a = NULL;
    a = malloc(TAILLE_MAX_LIGNE*sizeof(char));
    while(fgets(a, TAILLE_MAX_LIGNE, fichier) != NULL) {
        nbLignes++;
    }
    fseek(fichier,0,0);
    return nbLignes;
}

char* lireLigne(FILE* fichier, int n) {
    char* res = NULL;
    res = malloc(TAILLE_MAX_LIGNE*sizeof(char));
    int max = nbLignesFichier(fichier);
    // On cherche la ligne correspondante
    if (fichier && n <= max) {
        while(n>0) {
            fgets(res,TAILLE_MAX_LIGNE,fichier);
            n--;
        }
    }
    fseek(fichier,0,0);
    return res;
}

int getIdMax(char* type) {
    assert(type != NULL);
    const char* chemin = NULL;
    if (strcmp(type,"aliments") == 0) {
        chemin = CHEMIN_ALIMENTS;
    }
    else if (strcmp(type,"pesees") == 0) {
        chemin = CHEMIN_PESEES;
    }
    else {
        return -1;
    }
    FILE* fichier = fopen(chemin,"r+");
    assert(fichier != NULL);
    int nbLignes = nbLignesFichier(fichier);
    char* ligne = lireLigne(fichier,nbLignes);
    int idMax = atoi(strtok(ligne,";"));
    fseek(fichier,0,0);
    return idMax;
}

char* lireLigneParId(FILE* fichier, int id) {
    char* ligneLu = NULL;
    ligneLu = malloc(TAILLE_MAX_LIGNE*sizeof(char));
    int idLu;
    int max = nbLignesFichier(fichier);
    fseek(fichier,0,0);
    // On cherche la ligne correspondante
    if (fichier) {
        int n = 0;
        fseek(fichier,0,0);
        while(n <= max && idLu != id) {
            ligneLu = lireLigne(fichier,n);
            idLu = atoi(strtok(lireLigne(fichier,n),";"));
            n++;
        }
    }
    assert(idLu == id);

    fseek(fichier,0,0);
    return ligneLu;
}

// Lecture Aliments
char* getNomAliment(int id) {
    FILE* fichier = fopen(CHEMIN_ALIMENTS,"r");
    char* ligneLu = NULL;
    char* nomLu;

    ligneLu = malloc(TAILLE_MAX_LIGNE*sizeof(char));
    nomLu = malloc(30*sizeof(char));

    ligneLu = lireLigneParId(fichier,id);

    strtok(ligneLu,";");        // id
    nomLu = strtok(NULL,";");   // nom
    fclose(fichier);
    return nomLu;
}

Couleur* getCouleurAliment(int id) {
    FILE* fichier = fopen(CHEMIN_ALIMENTS,"r");
    char* ligneLu = NULL;
    char* couleurLu;

    ligneLu = malloc(TAILLE_MAX_LIGNE*sizeof(char));
    ligneLu = lireLigneParId(fichier,id);
    fclose(fichier);

    strtok(ligneLu,";");    // id
    strtok(NULL,";");       // nom
    couleurLu = strtok(NULL,";");

    // Splitage de la couleur
    char* r = NULL;
    r = malloc(3*sizeof(char));
    char* g = NULL;
    g = malloc(3*sizeof(char));
    char* b = NULL;
    b = malloc(3*sizeof(char));

    r = strtok(couleurLu,"-");
    g = strtok(NULL,"-");
    b = strtok(NULL,"-");

    // Conversion char* en Couleur*
    Couleur* coul = initCouleur();
    setRCoul(atoi(r),coul);
    setGCoul(atoi(g),coul);
    setBCoul(atoi(b),coul);

    return coul;
}

char* getIdAlimentParCouleur(Couleur* coul, int precision) {
    FILE* fichier = fopen(CHEMIN_ALIMENTS,"r");
    int res = 0;

    char* listeIds = NULL;
    // Au maximum, tous les aliments conviennent. On prend 4 car on n'aura pas plus de 999 aliments + le symbole ";" entre chaque aliment
    listeIds = malloc(nbLignesFichier(fichier)*4*sizeof(char));

    char* ligneLu = NULL;
    ligneLu = malloc(TAILLE_MAX_LIGNE*sizeof(char));
    int idLu;

    Couleur* couleurLu = initCouleur();

    int i=2;

    while (i <= nbLignesFichier(fichier)) {
        ligneLu = lireLigne(fichier,i);
        idLu = atoi(strtok(ligneLu,";"));

        setRCoul(getRCoul(getCouleurAliment(idLu)),couleurLu);
        setGCoul(getGCoul(getCouleurAliment(idLu)),couleurLu);
        setBCoul(getBCoul(getCouleurAliment(idLu)),couleurLu);

        // On regarde si la couleur est proche de celle demand�e
        if (abs(getRCoul(couleurLu) - getRCoul(coul)) <= precision) {
            if (abs(getGCoul(couleurLu) - getGCoul(coul)) <= precision) {
                if (abs(getBCoul(couleurLu) - getBCoul(coul)) <= precision) {
                    sprintf(listeIds,"%d",idLu);
                    strcat(listeIds,";");
                    res = 1;
                }
            }
        }
        i++;
    }
    // Fin de boucle : tout le fichier est parcouru
    fclose(fichier);

    // S'il n'y a pas d'aliments correspondants, on renvoie NULL
    if(!res) {
        listeIds = NULL;
    }
    return listeIds;
}

// Lecture Pesees
char* getQuantitePesee(int id) {
    FILE* fichier = fopen(CHEMIN_PESEES,"r");
    char* ligneLu = NULL;
    char* quantiteLu;

    ligneLu = malloc(TAILLE_MAX_LIGNE*sizeof(char));
    ligneLu = lireLigneParId(fichier,id);

    strtok(ligneLu,";");            // id
    quantiteLu = strtok(NULL,";");  // quantite
    fclose(fichier);
    return quantiteLu;
}

char* getDescriptionPesee(int id) {
    FILE* fichier = fopen(CHEMIN_PESEES,"r");
    char* ligneLu = NULL;
    char* descriptionLu;

    ligneLu = malloc(TAILLE_MAX_LIGNE*sizeof(char));
    ligneLu = lireLigneParId(fichier,id);

    strtok(ligneLu,";");    // id
    strtok(NULL,";");       // quantite
    descriptionLu = strtok(NULL,";");   // description
    fclose(fichier);
    return descriptionLu;
}

char* getDatePesee(int id) {
    FILE* fichier = fopen(CHEMIN_PESEES,"r");
    char* ligneLu = NULL;
    char* dateLu;

    ligneLu = malloc(TAILLE_MAX_LIGNE*sizeof(char));
    ligneLu = lireLigneParId(fichier,id);

    strtok(ligneLu,";");    // id
    strtok(NULL,";");       // quantite
    strtok(NULL,";");       // description
    dateLu = strtok(NULL,";");   // date
    fclose(fichier);
    return dateLu;
}

char* getIdAlimentPesee(int id) {
    FILE* fichier = fopen(CHEMIN_PESEES,"r");
    char* ligneLu = NULL;
    char* idAlimentLu;

    ligneLu = malloc(TAILLE_MAX_LIGNE*sizeof(char));
    ligneLu = lireLigneParId(fichier,id);

    strtok(ligneLu,";");    // id
    strtok(NULL,";");       // quantite
    strtok(NULL,";");       // description
    strtok(NULL,";");       // date
    idAlimentLu = strtok(NULL,";");   // id_aliment
    fclose(fichier);
    return idAlimentLu;
}

// ---- MODIFICATION ---- //
int setQuantitePesee(int id, int nouvQte) {
    // ouvrir fichier des pesees.
    FILE* fichier = fopen(CHEMIN_PESEES,"r");

    // modifie l'attribut quantite
    char* ligneModifiee = NULL;
    ligneModifiee = malloc(TAILLE_MAX_LIGNE*sizeof(char));

    char* idChar;
    idChar = malloc(sizeof(id));
    sprintf(idChar,"%d",id);

    ligneModifiee = idChar;
    strcat(ligneModifiee,";");

    char* nouvQteChar;
    nouvQteChar = malloc(sizeof(nouvQte));
    sprintf(nouvQteChar,"%d",nouvQte);

    strcat(ligneModifiee, nouvQteChar);
    strcat(ligneModifiee,";");

    strcat(ligneModifiee,getDescriptionPesee(id));
    strcat(ligneModifiee,";");

    strcat(ligneModifiee,getDatePesee(id));
    strcat(ligneModifiee,";");

    strcat(ligneModifiee,getIdAlimentPesee(id));

    // recopier le fichier dans le temp
    FILE* fichierTemp = fopen(CHEMIN_PESEES_TEMP,"a");

    char* ligneLue = NULL;
    ligneLue = malloc(TAILLE_MAX_LIGNE*sizeof(char));

    char* ligneRef = lireLigneParId(fichier,id);

    while(fgets(ligneLue,TAILLE_MAX_LIGNE, fichier) != NULL) {
        if(strcmp(ligneLue,ligneRef) != 0) {
            fprintf(fichierTemp,ligneLue);
        }
        else {
            fprintf(fichierTemp,ligneModifiee);
        }
    }

    fclose(fichier);
    fclose(fichierTemp);

    int res = 1;
    if(remove(CHEMIN_PESEES) != 0 || rename(CHEMIN_PESEES_TEMP,CHEMIN_PESEES) != 0) {
        res = 0;
    }
    return res;

}

int setDatePesee(int id, char* nouvDate) {
    FILE* fichier = fopen(CHEMIN_PESEES,"r");

    // modifie l'attribut quantite
    char* ligneModifiee = NULL;
    ligneModifiee = malloc(TAILLE_MAX_LIGNE*sizeof(char));

    char* idChar;
    idChar = malloc(sizeof(id));
    sprintf(idChar, "%d",id);

    ligneModifiee = idChar;
    strcat(ligneModifiee,";");

    strcat(ligneModifiee,getQuantitePesee(id));
    strcat(ligneModifiee,";");

    strcat(ligneModifiee,getDescriptionPesee(id));
    strcat(ligneModifiee,";");

    strcat(ligneModifiee,nouvDate);
    strcat(ligneModifiee,";");

    strcat(ligneModifiee,getIdAlimentPesee(id));

    // recopier le fichier dans le temp
    FILE* fichierTemp = fopen(CHEMIN_PESEES_TEMP,"a");

    char* ligneLue = NULL;
    ligneLue = malloc(TAILLE_MAX_LIGNE*sizeof(char));

    char* ligneRef = lireLigneParId(fichier,id);

    while(fgets(ligneLue,TAILLE_MAX_LIGNE, fichier) != NULL) {
        if(strcmp(ligneLue,ligneRef) != 0) {
            fprintf(fichierTemp,ligneLue);
        }
        else {
            fprintf(fichierTemp,ligneModifiee);
        }
    }

    fclose(fichier);
    fclose(fichierTemp);

    int res = 1;
    if(remove(CHEMIN_PESEES) != 0 || rename(CHEMIN_PESEES_TEMP,CHEMIN_PESEES) != 0) {
        res = 0;
    }
    return res;

}

// ---- ECRITURE ---- //
int ecrireDonneeAliment(char* nom, char* couleur) {
    FILE* fichier = fopen(CHEMIN_ALIMENTS,"r+");
    assert(fichier != NULL);
    fseek(fichier,0,SEEK_END);

    // Saut de ligne avant insertion et formatage des donn�es
    char buffer[TAILLE_MAX_LIGNE]="\n";

    // Obtention de l'id du nouvel aliment
    int id = getIdMax("aliments") + 1;
    char *idchar = NULL;
    idchar = malloc(10*sizeof(char));
    sprintf(idchar,"%d",id);

    strcat(buffer,idchar);
    strcat(buffer,";");
    strcat(buffer,nom);
    strcat(buffer,";");
    strcat(buffer,couleur);
    strcat(buffer,";");

    fprintf(fichier,buffer);
    fclose(fichier);
    return 1;
}

int ecrireDonneePesee(int quantite,char* description,char* date,int id_aliment) {
    FILE* fichier = fopen(CHEMIN_PESEES,"r+");

    // Contr�les
    assert(fichier != NULL);
    assert(date != NULL && date != "");

    // Saut de ligne avant insertion et formatage des donn�es
    char buffer[TAILLE_MAX_LIGNE]="\n";

    // Obtention de l'id de la nouvelle pes�e
    int id = getIdMax("pesees") + 1;
    fseek(fichier,0,SEEK_END);
    char *idchar = NULL;
    idchar = malloc(10*sizeof(char));
    sprintf(idchar,"%d",id);

    // Conversion des donn�es int en char
    char *quantite_char = NULL;
    quantite_char = malloc(100*sizeof(char));
    char *id_aliment_char = NULL;
    id_aliment_char = malloc(10*sizeof(char));
    sprintf(quantite_char,"%d",quantite);
    sprintf(id_aliment_char,"%d",id_aliment);

    // Ecriture dans le fichier (+ conversion des NULL en " ")
    strcat(buffer,idchar);
    strcat(buffer,";");

    if (quantite_char == "") {
         strcat(buffer," ");
    }
    else {
         strcat(buffer,quantite_char);
    }
    strcat(buffer,";");

    if (description == "") {
         strcat(buffer," ");
    }
    else {
         strcat(buffer,description);
    }

    strcat(buffer,";");
    strcat(buffer,date);
    strcat(buffer,";");
    strcat(buffer,id_aliment_char);

    fprintf(fichier,buffer);
    fclose(fichier);
    return 1;
}

// ---- SUPPRESSION ---- //
int supprimerDonneeAliment(int id){
    FILE* fichier = fopen(CHEMIN_ALIMENTS,"r+");

    // Obtention ligne � Supprimer
    char* ligneASupprimer = NULL;
    ligneASupprimer = malloc(TAILLE_MAX_LIGNE*sizeof(char));
    ligneASupprimer = lireLigneParId(fichier,id);

    FILE* fichierTemp = fopen(CHEMIN_ALIMENTS_TEMP,"a");

    // Recopie du fichier dans le fichier .tmp sauf la ligne � supprimer
    char* ligneLu = NULL;
    ligneLu = malloc(TAILLE_MAX_LIGNE*sizeof(char));
    while(fgets(ligneLu, TAILLE_MAX_LIGNE, fichier) != NULL) {
        if(strcmp(ligneLu,ligneASupprimer) != 0) {
            fprintf(fichierTemp,ligneLu);
        }
    }

    fclose(fichier);
    fclose(fichierTemp);

    int res = 1;
    if(remove(CHEMIN_ALIMENTS) != 0 || rename(CHEMIN_ALIMENTS_TEMP,CHEMIN_ALIMENTS) != 0) {
        res = 0;
    }
    return res;
}

int supprimerDonneePesee(int id){
    FILE* fichier = fopen(CHEMIN_PESEES,"r+");

    // Obtention ligne � Supprimer
    char* ligneASupprimer = NULL;
    ligneASupprimer = malloc(TAILLE_MAX_LIGNE*sizeof(char));
    ligneASupprimer = lireLigneParId(fichier,id);

    FILE* fichierTemp = fopen(CHEMIN_PESEES_TEMP,"a");


    // Recopie du fichier dans le fichier .tmp sauf la ligne � supprimer
    char* ligneLu = NULL;
    ligneLu = malloc(TAILLE_MAX_LIGNE*sizeof(char));
    while(fgets(ligneLu, TAILLE_MAX_LIGNE, fichier) != NULL) {
        if(strcmp(ligneLu,ligneASupprimer)) {
            fprintf(fichierTemp,ligneLu);
        }
    }

    fclose(fichier);
    fclose(fichierTemp);

    int res = 1;
    if(remove(CHEMIN_PESEES) != 0 || rename(CHEMIN_PESEES_TEMP,CHEMIN_PESEES) != 0) {
        res = 0;
    }
    return res;
}
