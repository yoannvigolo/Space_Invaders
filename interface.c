/*
 * interface.c
 *
 *  Created on: 21 févr. 2020
 *      Author: yoann
 */

#include <interface.h>
#include "vt100.h"
#include "serial.h"
#include "time.h"
#include "unistd.h"
#include "vaisseau.h"

void Start_Menu()							// fonction qui affiche le menu
{
	int i = 10;
	for (i = 10; i <= 70; i++)
	{
		Place_Caractere(i, 3, "*");
		Place_Caractere(i, 7, "*");
	}

	for (int i = 3; i <= 7; i++)
	{
		Place_Caractere(10, i, "*");
		Place_Caractere(70, i, "*");
	}

	Place_Caractere(35, 5, "SPACE INVADERS");
	Place_Caractere(40, 12, "JOUER");
	Place_Caractere(25, 13, "____________________________________");
	Place_Caractere(32, 16, "Appuyer sur une touche ");
	Place_Caractere(52, 22, "Appuyez sur R pour RESTART");
}

void Bordure()								// fonction qui affiche les bordures
{
	int i = 1;
	for (i = 1; i <= 80; i++)
	{
		Place_Caractere(i, 1, "#");
		Place_Caractere(i, 24, "#");
	}
	i = 1;
	for (i = 1; i <= 24; i++)
	{
			Place_Caractere(1, i, "#");
			Place_Caractere(80, i, "#");
	}
}

