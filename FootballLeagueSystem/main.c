#include <stdio.h>
#include <stdlib.h>

typedef struct Info
{
	char *Name;
	int g_played;
	int g_won;
	int g_lost;
	int g_drawn;
	int points;
	struct Info* next;
}INFO, *PINFO, **PPINFO;

void InsertTeam(PPINFO Head,  int total, int won, int lost, int draw)
{
	PINFO newn = (PINFO)malloc(sizeof(INFO));
	Head = newn;
	PINFO temp = Head;
	temp -> g_played = total;
	temp -> g_won = won;
	temp -> g_lost = lost;
	temp -> g_drawn = draw;
	//temp -> points = points;
}

void display(PINFO Head)
{
	int i = 0;
	printf("Game Played = %d\n", Head ->g_played);
}
int main(void)
{
	PINFO First = NULL;
	//char name[255] = 'Aditya';
	int played = 5;
	int iWon = 4;
	int iLost = 1;
	int iDraw = 0;
	InsertTeam(&First, played,iWon, iLost, iDraw);
	display(&First);

	return 0;
}
