

mouv_up(t_coord *bar, t_tab *tab)
{
	tab[bar->y - 1][bar->x] = '|';
	tab[bar->y + 2][bar->x] = ' ';
	bar->y = bar->y - 1;
}

mouv_down(t_coord *bar, t_tab *tab)
{
	tab[bar->y + 3][bar->x] = '|';
	tab[bar->y][bar->x] = ' ';
	bar->y = bar->y + 1;
}

__________________________________________________


void verif_bal(t_tout *tout, char **tab)
{

	if(tab[(tout->bal->y) + (tout->dir->y)][(tout->bal->x) + (tout->dir->x)] == '|';
		tout->dir->x *= -1;
	if((tout->bal->x + tout->dir->x == 0) || ((tout->bal->x + tout->dir->x) == 19))
		tout->dir->y *= -1;
}

void mouv_bal(t_tout *tout, char **tab)
{
	tab[(tout->bal->y) + (tout->dir->y)][(tout->bal->x) + (tout->dir->x)] = 'o';
	tab[tout->bal->y][tout->bal->x] = ' ';

}

void dir(t_tout *tout)
{
    unsigned int seed;
    seed = time(NULL);
    r = rand_r(&seed) % 2;

    if(r = 0)
    	tout->dir->x= -1;
    else
    	tout->dir->x] = 1;
	seed = time(NULL);
    r = rand_r(&seed) % 2;
	if(r = 0)
    	tout->dir->y= -1;
    else
    	tout->dir->y] = 1;
}