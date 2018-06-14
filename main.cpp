// ConsoleApplication32.cpp: definisce il punto di ingresso dell'applicazione console.
//

#include "stdafx.h" // VS
#include <iostream>
#include <string.h>
#include <time.h>

#define NUMSURVIVOR 4 // Player
#define MAXKFR 3 //  Max kill for round
#define NOMELEN 12 // Nome è un array e serve una costante
#define VINCITORE 1 // Magari vincono in 2(?)
#define NOKILL 0 // Ovviamente
#define INITROUND 1 // Idem

typedef struct
{
	char nome[NOMELEN];
	int id;
	bool vivo=true;
}SURVIVOR;

void gioca();
void inizializza_tutti(SURVIVOR giocatori[]);
void inizializza_id(SURVIVOR *player, int index);
void nomina_tutti(SURVIVOR giocatori[]);
void nomina(SURVIVOR *player);
void muori(SURVIVOR *player);
void roba_random(SURVIVOR giocatori[], int alive, int *index);
void notifica_uccisione(SURVIVOR giocatori[], int index);
void reset_id(SURVIVOR giocatori[], int numalive);
void mortiid(SURVIVOR giocatori[]);
void havinto(SURVIVOR giocatore);
void vittoria(SURVIVOR giocatori[]);
int contavivi(SURVIVOR giocatori[]);
int contamorti(SURVIVOR giocatori[]);

int main()
{
	srand(time(NULL));
	gioca();
	std::cin.get();
	std::cin.get();
    return 0;
}

void gioca()
{
	int index;
	int alive;
	int round=INITROUND;
	int kts;
	SURVIVOR giocatori[NUMSURVIVOR];
	inizializza_tutti(giocatori);
	nomina_tutti(giocatori);
	do
	{
		alive = contavivi(giocatori);
		if (alive != VINCITORE)
		{
			printf("Round %d:\n", round);
			kts = rand() % MAXKFR; //Kill this round
			if(kts!=NOKILL)
			{
				for(int j=0;j<kts;j++)
				{
				roba_random(giocatori, alive, &index);
				notifica_uccisione(giocatori, index);
				}
			}
			else
			{
				printf("Nessuno è morto\n");
			}
		}
		else // Boh
		{
			vittoria(giocatori);
		}
		round++;
	} while (alive > VINCITORE);
	vittoria(giocatori); // Boh 2
}

void inizializza_tutti(SURVIVOR giocatori[])
{
	for (int j = 0; j < NUMSURVIVOR; j++)
	{
		inizializza_id(&giocatori[j], j);
	}
}

void inizializza_id(SURVIVOR *player, int index)
{
	player->id = index;
}

void nomina_tutti(SURVIVOR giocatori[])
{
	for (int j = 0; j < NUMSURVIVOR; j++)
	{
		nomina(&giocatori[j]);
	}
}

void nomina(SURVIVOR *player)
{
	printf("Inserisci nome player %d\n", player->id + 1);
	//scanf("%s", player->nome);
	scanf_s("%s", player->nome, NOMELEN+1);
}

void muori(SURVIVOR *player)
{
	player->vivo = false;
}

void roba_random(SURVIVOR giocatori[], int alive, int *index)
{
		reset_id(giocatori, alive);
		do
		{
			*index = rand() % alive;
		} while (giocatori[*index].vivo != true);
		muori(&giocatori[*index]);
		printf("Debug XD\n");
}

void notifica_uccisione(SURVIVOR giocatori[], int index)
{
	printf("%s è morto\n", giocatori[index].nome);
}

int contavivi(SURVIVOR giocatori[])
{
	int vivi=0;
	for (int j = 0; j < NUMSURVIVOR; j++)
	{
		if (giocatori[j].vivo != false)
		{
			vivi++;
		}
	}
	return vivi;
}

int contamorti(SURVIVOR giocatori[])
{
	int morti = 0;
	for (int j = 0; j < NUMSURVIVOR; j++)
	{
		if (giocatori[j].vivo != true)
		{
			morti++;
		}
	}
	return morti;
}

void reset_id(SURVIVOR giocatori[], int numalive) // Qua si sfancula tutto
{
	int morti=0;
	for (int j = 0; j < numalive; j++)
	{
		if (giocatori[j].vivo == true)
		{
			inizializza_id(&giocatori[j], (morti-j));
		}
		else
		{
			morti++;
		}
	}
}

void mortiid(SURVIVOR giocatori[]) // Idem sopra
{
	for (int j = 0; j < NUMSURVIVOR; j++)
	{
		if (giocatori[j].vivo != true)
		{
			giocatori[j].id = NUMSURVIVOR + giocatori[j].id;
		}
	}
}

void havinto(SURVIVOR giocatore)
{
	printf("Ha vinto %s!\n", giocatore.nome);
}

void vittoria(SURVIVOR giocatori[])
{
	for (int j = 0; j < VINCITORE; j++)
	{
		if (giocatori[j].vivo != false)
		{
			havinto(giocatori[j]);
		}
	}
}
