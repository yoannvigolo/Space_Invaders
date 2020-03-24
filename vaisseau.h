/*
 * vaisseau.h
 *
 *  Created on: 21 févr. 2020
 *      Author: yoann
 */

#ifndef VAISSEAU_H_
#include <unistd.h>
#define VAISSEAU_H_

int Mouvement_vaisseau(uint8_t t);
void Place_Caractere(uint8_t x, uint8_t y, const volatile char *s);
void Tire_vaisseau(int x, int y_ennemis, int y_ennemis2, int tir);
int* Set_Pos_Ennemis(int x_start, int ecart, int numero_ligne_ennemis);
void Affichage_Ennemis(int x[], int y, const volatile char *s, int numero_ligne);
void Delai(unsigned long n);
void restart();

#endif /* VAISSEAU_H_ */
