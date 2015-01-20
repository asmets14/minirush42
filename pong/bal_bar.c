
typedef struct s_tout
{
	t_coord *bal;
	t_coord *j1;
	t_coord *j2;
}				t_tout;

typedef struct s_coord
{
	int x;
	int y;
	int value;
}				t_coord;

void affect_bar1(t_tout, char **tab)
{
	tab[tout->j1->x][tout->j1->y] = '|';
	tab[tout->(j1->x + 1)][tout->j1->y] = '|';
	tab[tout->(j1->x + 2)][tout->j1->y] = '|';

}

void affect_bar2(t_tout, char **tab)
{
	tab[tout->j2->x][tout->j2->y] = '|';
	tab[tout->(j2->x + 1)][tout->j2->y] = '|';
	tab[tout->(j2->x + 2)][tout->j2->y] = '|';

}

void affectation_bal(t_tout *tout, char **tab)
{
	tab[tout->bal.x][tout->bal->y] = 'o';

}

void init_bar_bal()
{
	t_tout *tout;

	tout = (t_tout)malloc(sizeof(t_tout));
	tout->bal = (t_coord)malloc(sizeof(t_coord));
	tout->j1 = (t_coord)malloc(sizeof(t_coord));
	tout->j2 = (t_coord)malloc(sizeof(t_coord));

	tout->bal.x= 30;
	tout->bal.y= 7;
	tout->j1.x = 3;
	tout->j1.y = 10;
	tout->j2.x = 57;
	tout->j2.y = 10;
	// VALEUR A AJOUTER;

}