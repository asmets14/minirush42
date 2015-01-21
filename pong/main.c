/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testgetarrow.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juschaef <juschaef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/08 14:00:56 by hhismans          #+#    #+#             */
/*   Updated: 2015/01/21 18:39:53 by asmets           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <termios.h>
#include <unistd.h>
#include <sys/termios.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include "Libft/libft.h"


typedef struct s_coord
{
	int x;
	int y;
	int value;
}				t_coord;

typedef struct s_tout
{
	t_coord *bal;
	t_coord *j1;
	t_coord *j2;
	t_coord	*vecteur;
	t_coord	*dir;
}				t_tout;

static int	kbhit(void)
{
	struct termios	oldt;
	struct termios	newt;
	int				ch;
	int				oldf;

	tcgetattr(STDIN_FILENO, &oldt);
	newt = oldt;
	newt.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &newt);
	oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
	fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);
	ch = getchar();
	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
	fcntl(STDIN_FILENO, F_SETFL, oldf);
	if (ch != EOF)
	{
		ungetc(ch, stdin);
		return (1);
	}
	return (0);
}

static int	getarrowkey(void)
{
	struct termios	line_police;
	char			c;
	int				d;

	if (ioctl(0, TIOCGETA, &line_police) < 0)
		1 ? (perror("getarrowkey error\n"), exit(1)) : 0;
	if (line_police.c_lflag &= ~(ICANON | ECHO))
		if ((ioctl(0, TIOCSETA, &line_police)) < 0)
			1 ? (perror("getarrowkey error\n"), exit(1)) : 0;
	if ((d = 0), kbhit())
		while ((c = fgetc(stdin)))
		{
			d = (c == 'w' ? 1 : d);
			d = (c == 65 ? 2 : d);
			d = (c == 66 ? 3 : d);
			d = (c == 's' ? 4 : d);
			if (d)
				return (d);
		}
	return (0);
}

void	remplace(int x, int y, char **tab, t_tout *tout)
{
	tout->bal->x = x;
	tout->bal->y = y;
}

int ft_abs(int c)
{
	if (c < 0)
		return (-c);
	return (c);
}

void        put_line_h(int x1, int y1, int x2, int y2, char **tab, t_tout *tout)
{
	int        x;

	x = x1;
	while (x <= x2)
	{
		remplace(x, y1 + ((y2 - y1) * (x - x1)) / (x2 - x1), tab, tout);
		x++;
	}
}

void        put_line_v(int x1, int y1, int x2, int y2, char **tab, t_tout *tout)
{
	int        y;

	y = y1;
	while (y <= y2)
	{
		remplace(x1 + ((x2 - x1) * (y - y1)) / (y2 - y1), y, tab, tout);
		y++;
	}
}

void        draw_line(int x1, int y1, int x2 , int y2 , char **tab, t_tout *tout)// depart - arriver
{

	//if ((x1 - x2) == 0 && (y1 - y2) == 0)
	//	mlx_pixel_put(e->mlx, e->win, x1, y1, 0x00FF00);
	if (x1 <= x2 && ((x2 - x1) >= ft_abs(y2 - y1)))
		put_line_h(x1, y1, x2, y2, tab, tout);
	else if (x2 <= x1 && ((x1 - x2) >= ft_abs(y1 - y2)))
		put_line_h(x2, y2, x1, y1, tab, tout);
	else if (y1 <= y2 && ((y2 - y1) >= ft_abs(x2 - x1)))
		put_line_v(x1, y1, x2, y2, tab, tout);
	else if (y2 <= y1 && ((y1 - y2) >= ft_abs(x1 - x2)))
		put_line_v(x2, y2, x1, y1, tab, tout);
}
void affect_bar1(t_tout *tout, char **tab)
{
	tab[tout->j1->y][tout->j1->x] = '|';
	tab[(tout->j1)->y + 1][tout->j1->x] = '|';
	tab[(tout->j1)->y + 2][tout->j1->x] = '|';

}

void affect_bar2(t_tout *tout, char **tab)
{
	tab[tout->j2->y][tout->j2->x] = '|';
	tab[(tout->j2)->y + 1][tout->j2->x] = '|';
	tab[(tout->j2)->y + 2][tout->j2->x] = '|';

}

void affectation_bal(t_tout *tout, char **tab)
{
	printf("x = %d, y = %d\n",tout->bal->x, tout->bal->y );
	tab[tout->bal->y][tout->bal->x] = 'o';
}

void start(t_tout *tout)
{
	tout->bal->x= 28;
	tout->bal->y= 2;
	tout->j1->x = 3;
	tout->j1->y = 8;
	tout->j2->x = 56;
	tout->j2->y = 8;
}

t_tout *init_bar_bal()
{
	t_tout *tout;

	tout = (t_tout *)malloc(sizeof(t_tout));
	tout->bal = (t_coord *)malloc(sizeof(t_coord));
	tout->j1 = (t_coord *)malloc(sizeof(t_coord));
	tout->j2 = (t_coord *)malloc(sizeof(t_coord));
	tout->vecteur = (t_coord *)malloc(sizeof(t_coord));
	tout->dir = (t_coord *)malloc(sizeof(t_coord));

	start(tout);
	tout->j1->value = 0;
	tout->j2->value = 0;
	return (tout);
}

char **init(t_tout *tout)
{
	char **tab;
	int i;
	int j;

	tab = (char **)malloc(sizeof(char *) * 20);
	j = 0; 
	i = 0;
	while (j < 20)
	{
		tab[j] = (char*)malloc(sizeof(char) * 61);
		while (i < 61)
		{
			if (i == 0 || i == 59 || j == 0 || j == 19)
				tab[j][i] = '#';
			else
				tab[j][i] = ' ';
			if (i == 60 )
				tab[j][i] = '\0';
			i++;
		}
		i = 0;
		j++;

	}

	affectation_bal(tout,tab);
	affect_bar2(tout, tab);
	affect_bar1(tout, tab);
	return (tab);
}

void print(char** tab)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (j < 20)
	{	
		ft_putstr("\033[34m");
		ft_putendl(tab[j]);
		ft_putstr("\033[0m");
		j++;
	}
}

void mouv_up(t_coord *bar, char **tab)
{
	if (bar->y > 1)
	{	
		tab[bar->y - 1][bar->x] = '|';
		tab[bar->y + 2][bar->x] = ' ';
		bar->y = bar->y - 1;
	}
}

void mouv_down(t_coord *bar, char **tab)
{
	if(bar->y < 16)
	{
		tab[bar->y + 3][bar->x] = '|';
		tab[bar->y][bar->x] = ' ';
		bar->y = bar->y + 1;
	}
}

void dir(t_tout *tout)
{
	int r;
	unsigned int seed;
	seed = time(NULL);
	r = rand_r(&seed) % 2;

	if(r == 0)
		tout->dir->x= -1;
	else
		tout->dir->x = 1;
	seed = time(NULL);
	r = rand_r(&seed) % 2;
	if(r == 0)
		tout->dir->y= -1;
	else
		tout->dir->y = 1;
}

int	verif_bal(t_tout *tout, char **tab)
{
	if(tab[(tout->bal->y) + (tout->dir->y)][(tout->bal->x) + (tout->dir->x)] == '|')
		tout->dir->x *= -1;
	if((tout->bal->y + tout->dir->y == 0) || ((tout->bal->y + tout->dir->y) == 19))
		tout->dir->y *= -1;
	if ((tout->bal->x + tout->dir->x == 0) )
	{
		tout->j2->value += 1;
		return (1);
	}
	if ((tout->bal->x + tout->dir->x) == 59)
	{
		tout->j1->value += 1;
		return (1);
	}
	return (0);
}

void mouv_bal(t_tout *tout, char **tab)
{
	tab[tout->bal->y][tout->bal->x] = ' ';
	draw_line(tout->bal->x, tout->bal->y, ((tout->bal)->x + 1), ((tout->bal)->y + 2), tab, tout);
	tout->bal->y += tout->dir->y;
	tout->bal->x += tout->dir->x;
	tab[tout->bal->y][tout->bal->x] = 'o';

}

int			main(void)
{
	int key;
	char **tab;
	t_tout *tout;
	tout = init_bar_bal();
	tab = init(tout);

	int time;
	dir(tout);
	while (1)
	{
		key = getarrowkey();
		if (key == 1) // j1
		{
			//write(1, "W\n", 2);
			mouv_up(tout->j1, tab);
		}
		else if (key == 2) // j2
			mouv_up(tout->j2, tab);
		//write(1, "fleche haut\n", 12);
		else if (key == 3) // j2
			mouv_down(tout->j2, tab);
		//	write(1, "fleche bas\n", 11);
		else if (key == 4) // j1
		{
			//write(1, "S\n", 2);
			mouv_down(tout->j1, tab);
		}
		if(verif_bal(tout, tab) == 1)
		{
			start(tout);
			tab = init(tout);

		}
		if (time % 5 == 0)
		{

			mouv_bal(tout, tab);
		}
			system("CLEAR");
		print(tab);
		printf("joueur 1 = %d \t joueur 2 = %d\n", tout->j1->value, tout->j2->value);
		usleep(100000);
		time++;
	}
	return (0);
}
