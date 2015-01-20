/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmets <asmets@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/20 10:14:59 by asmets            #+#    #+#             */
/*   Updated: 2015/01/20 11:01:30 by asmets           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include <stdio.h>


char **init()
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
		ft_putendl(tab[j]);
		j++;
	}
}
