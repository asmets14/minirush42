

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

mouv_down1


mouv_up2

mouv_down2