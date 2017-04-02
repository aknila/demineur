/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rand.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aancel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/02 09:50:46 by aancel            #+#    #+#             */
/*   Updated: 2017/04/02 09:50:48 by aancel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/demineur.h"

int		ft_rand_ab(int a, int b)
{
	return (rand()%(b - a) + a);
}

int		ft_nbr_of_mine(char **tab, int i, int j, int size)
{
	int nbr;

	nbr = 0;
	if (tab[i][j] == '9')
		return (9);
	if (i - 1 >= 0 && j - 1 >= 0 && tab[i - 1][j - 1] == '9')
		nbr++;
	if (i - 1 >= 0 && tab[i - 1][j] == '9')
		nbr++;
	if (j + 1 < size && i - 1 >= 0 && tab[i - 1][j + 1] == '9')
		nbr++;
	if (j - 1 >= 0 && tab[i][j - 1] == '9')
		nbr++;
	if (j + 1 < size && tab[i][j + 1] == '9')
		nbr++;
	if (i + 1 < size && j - 1 >= 0 && tab[i + 1][j - 1] == '9')
		nbr++;
	if (i + 1 < size && tab[i + 1][j] == '9')
		nbr++;
	if (i + 1 < size && j + 1 < size && tab[i + 1][j + 1] == '9')
		nbr++;
	return (nbr);
}

char	**ft_set_demine(int size, int prc)
{
	int nb_case;
	int mine;
	char **tab;
	int *list;
	int i;
	int a;
	int stock;

	i = 0;
	tab = NULL;
	nb_case = size * size;
	mine = nb_case * prc / 100;
	if (!(list = (int *)malloc(sizeof(int) * mine)))
		return (NULL);
	srand(time(NULL));
	while (mine - i > 0)
	{
		stock = ft_rand_ab(0, nb_case);
		a = 0;
		while (a < i)
		{
			if (list[a] == stock)
			{
				stock = ft_rand_ab(0, nb_case);
				a = 0;
			}
			else
				a++;
		}
		list[i] = stock;
		i++;
	}
	if (!(tab = ft_putmine(ft_create_tab(size, size), size, list, mine)))
		return (NULL);
	return (tab);
}
