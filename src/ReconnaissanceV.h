// EN-TETE ReconnaissanceV.h
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "Couleur.h"
#include "BDD.h"

#ifndef DEF_ReconnaissanceV.h
#define DEF_ReconnaissanceV.h


// ---- CONSTANTES ---- //
const char* CHEMIN_IMAGES_ALIMENTS = "data/images_aliments/";

// ---- FONCTIONS ---- //

Couleur* chargerImage(FILE* image);
//Renvoie un tableau de Couleur repr�sentant l'image charg�e

int unifierFond(FILE* image);
//Renvoie True (1) si la cam�ra a clairement pu identifier le fond, sinon False (0)
//image E images_aliments

Couleur couleurDominante(FILE* image);
//Renvoie True si la couleur dominante de la photo a clairement pu �tre #identifi�e, False sinon.
//couleurDominante(FILE * image1) => unifierFond(FILE * imageFond)

int rechercheAliment(Couleur);
//Renvoie True(1) si il y a au moins un aliment dans la base de donn�e qui est proche de la couleur dominante, sinon False (0)
//rechercheAliment(Couleur) => Couleur==couleurDominante(FILE *)

int* IdAlimentsDeCouleur(Couleur);
//renvoie les ids des aliments qui ont une Couleur proche de celle rentr�e en param�tre


#endif
