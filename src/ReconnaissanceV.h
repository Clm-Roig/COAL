// EN-TETE ReconnaissanceV.h
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "Couleur.c"
#include "BDD.c"
// ---- CONSTANTES ---- //

// ---- FONCTIONS ---- //

Couleur* chargerImage(FILE* image);
# Renvoie un tableau de Couleur repr�sentant l'image charg�e

bool unifierFond(FILE* image);
#Renvoie True si la cam�ra a clairement pu identifier le fond, False #sinon
#image E images_aliments

Couleur couleurDominante(FILE* image);
#Renvoie True si la couleur dominante de la photo a clairement pu �tre #identifi�e, False sinon.
#couleurDominante(FILE * image1) => unifierFond(FILE * imageFond)

bool rechercheAliment(Couleur);
#Renvoie True si il y a au moins un aliment dans la base de donn�e qui est proche de la couleur dominante, False sinon
#rechercheAliment(Couleur) => Couleur==couleurDominante(FILE *)

int* IdAlimentsDeCouleur(Couleur);
# renvoie les ids des aliments qui ont une Couleur proche de celle rentr�e en param�tre

