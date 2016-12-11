// EN-TETE Couleur.h
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#ifndef DEF_Couleur.h
#define DEF_Couleur.h

// ---- CONSTANTES ---- //


// ---- STRUCTURE ---- //
/** @struct Couleur
 *  @brief Structure definissant une couleur au format R-G-B
 *  @var Couleur::rCoul
 *  Valeur de Rouge (compris entre 0 et 255)
 *  @var Couleur::gCoul
 *  Valeur de Vert (compris entre 0 et 255)
 *  @var Couleur::bCoul
 *  Valeur de Bleu (compris entre 0 et 255)
 */
typedef struct Couleur {
    int rCoul;
    int gCoul;
    int bCoul;
} Couleur;

// ---- FONCTIONS ---- //

//Getters
/**
	@brief Recup�re rCoul d'une Couleur
	@param Couleur* couleur, la couleur � lire
	@return int rCoul, la valeur de rouge de la Couleur
*/
int getRCoul(Couleur* couleur);

/**
	@brief Recup�re gCoul d'une Couleur
	@param Couleur* couleur, la couleur � lire
	@return int gCoul, la valeur de rouge de la Couleur
*/
int getGCoul(Couleur* couleur);

/**
	@brief Recup�re bCoul d'une Couleur
	@param Couleur* couleur, la couleur � lire
	@return int bCoul, la valeur de rouge de la Couleur
*/
int getBCoul(Couleur* couleur);

// Setters
/**
	@brief Edition de rCoul dans la structure
	@param int r, la valeur de rouge � setter (compris entre 0 et 255)
	@param Couleur* couleur, la couleur � modifier
*/
void setRCoul(int r,Couleur* couleur);

/**
	@brief Edition de gCoul dans la structure
	@param int g, la valeur de vert � setter (compris entre 0 et 255)
	@param Couleur* couleur, la couleur � modifier
*/
void setGCoul(int g,Couleur* couleur);

/**
	@brief Edition de bCoul dans la structure
	@param int b, la valeur de bleu � setter (compris entre 0 et 255)
	@param Couleur* couleur la couleur � modifier
*/
void setBCoul(int b,Couleur* couleur);

#endif
