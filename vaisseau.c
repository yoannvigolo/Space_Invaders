/*
 * vaisseau.c
 *
 *  Created on: 21 févr. 2020
 *      Author: yoann
 */

#include <vaisseau.h>
#include "vt100.h"
#include "serial.h"
#include "time.h"
#include "unistd.h"

#define TOUCHE serial_get_last_char()

typedef struct identite		// Structure de la 1ère ligne d'ennemis
{
	int tab_x[5];		// tableau contenant position en X de chaque vaisseau
	int etat[5];// tableau contenant l'état de chaque vaisseau. 0 = Vivant | 1 = Mort
} ligne_ennemis;

static ligne_ennemis pos;
static ligne_ennemis etat;

typedef struct identite2	// Structure de la 2ème ligne d'ennemis
{
	int tab_x[5];
	int etat[5];
} ligne_ennemis2;

static ligne_ennemis2 pos2;
static ligne_ennemis2 etat2;

void Place_Caractere(uint8_t x, uint8_t y, const volatile char *s)
{
	vt100_move(x, y);
	serial_puts(s);
	return;
}

void Tire_vaisseau(int x, int y_ennemis, int y_ennemis2, int y_tir)
{
	Place_Caractere(x + 2, y_tir, "|");
	Delai(5);
	for (int i = 0; i < 5; i++)
	{
		if ((y_tir == y_ennemis + 1)
				&& (x + 2 == pos.tab_x[i] || x + 2 == pos.tab_x[i] + 1
						|| x + 2 == pos.tab_x[i] + 2
						|| x + 2 == pos.tab_x[i] + 3))
		{
			if (etat.etat[i] == 0)
			{

				Place_Caractere(pos.tab_x[i], y_ennemis, "    ");
				etat.etat[i] = 1;
				Place_Caractere(x + 2, y_tir, " ");
				return;
			}
			break;
		}

		else if ((y_tir == y_ennemis2 + 1)
				&& (x + 2 == pos2.tab_x[i] || x + 2 == pos2.tab_x[i] + 1
						|| x + 2 == pos2.tab_x[i] + 2
						|| x + 2 == pos2.tab_x[i] + 3))
		{
			if (etat2.etat[i] == 0)
			{

				Place_Caractere(pos2.tab_x[i], y_ennemis2, "    ");
				etat2.etat[i] = 1;
				Place_Caractere(x + 2, y_tir, " ");
				return;
			}
			break;
		}

	}

	Place_Caractere(x + 2, y_tir, " ");
	return;
}

int* Set_Pos_Ennemis(int x_start, int ecart, int numero_ligne_ennemis)
{
	int i = 0;
	for (; i < 5; i++)
	{
		if (numero_ligne_ennemis == 1)
		{
			if (etat.etat[i] == 1)
			{
				continue;
			}

			else
			{
				pos.tab_x[i] = x_start + (ecart * i);
			}
		}

		if (numero_ligne_ennemis == 2)
		{
			if (etat2.etat[i] == 1)
			{
				continue;
			}

			else
			{
				pos2.tab_x[i] = x_start + (ecart * i);
			}
		}
	}

	if (numero_ligne_ennemis == 1)
	{
		return pos.tab_x;
	}

	else
	{
		return pos2.tab_x;
	}

}

void Affichage_Ennemis(int x[], int y, const volatile char *s, int numero_ligne)
{
	int i = 0;
	for (; i < 5; i++)
	{
		if (numero_ligne == 1)
		{
			if (etat.etat[i] == 1)
			{
				continue;
			}
			Place_Caractere(x[i], y, s);
		}

		if (numero_ligne == 2)
		{
			if (etat2.etat[i] == 1)
			{
				continue;
			}
			Place_Caractere(x[i], y, s);
		}

	}
}

int borne_gauche(int x_start)
{
	if (pos.etat[0] == 1)
	{
		x_start = etat2.etat[0];

		if (etat2.etat[0] == 1)
		{
			x_start = pos.etat[1];

			if (pos.etat[1] == 1)
			{
				x_start = etat2.etat[1];

				if (etat2.etat[1] == 1)
				{
					x_start = pos.etat[2];
				}
			}
		}
	}

	return x_start;
}

void restart()
{
	for (int i = 0; i < 5; i++)
	{
		pos.tab_x[i] = 0;
		pos2.tab_x[i] = 0;
		etat2.etat[i] = 0;
		etat.etat[i] = 0;
	}
}

void Delai(unsigned long n)
{
	int i = 0;
	unsigned long int max = n * 100000;
	do
	{
		i++;
	} while (i <= max);
}
