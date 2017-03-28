#include "../includes/demineur.h"

int		ft_error(int i)
{
	if (i == 0)
		ft_putstr(C_ROUGE "Usage : ./demineur {" C_BLEU "size" C_ROUGE "} {" C_VERT "pourcent of mine"
			C_ROUGE "}\n" C_BLEU "Size : between 10 and 40\n" C_VERT "Pourcent of mine between 20 and 75\n" FIN);
	if (i == 1)
		ft_putstr(C_ROUGE "Failed to create a map, retry in a few second\n");
	return(-1);
}

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

char	**ft_putmine(char **tab, int size, int *list, int mine)
{
	int i;
	int j;
	int z;

	i = 0;
	while (i < size)
	{
		tab[i][size] = '\0';
		i++;
	}
	tab[size][0] = '\0';
	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			z = 0;
			tab[i][j] = '0';
			while (z < mine)
			{
				if (list[z] == (i * size + j))
					tab[i][j] = '9';
				z++;
			}
			j++;
		}
		i++;
	}
	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			tab[i][j] = ft_nbr_of_mine(tab, i, j, size) + '0';
			j++;
		}
		i++;
	}
	return (tab);
}

char	**ft_demine(int size, int prc)
{
	int nb_case;
	int mine;
	char **tab;
	int *list;
	int i;
	int a;
	int b;

	i = 0;
	nb_case = size * size;
	mine = nb_case * prc / 100;
	if (!(list = (int *)malloc(sizeof(int) * mine)))
		return (NULL);
	srand(time(NULL));
	while (mine - i > 0)
	{
		list[i] = ft_rand_ab(0, nb_case);
		i++;
	}
	if (!(tab = ft_putmine(ft_create_tab(size, size), size, list, mine)))
		return (NULL);
	a = 0;
	while (a < size)
	{
		b = 0;
		while (b < size)
		{
			ft_putchar(tab[a][b]);
			ft_putchar(' ');
			b++;
		}
		ft_putchar('\n');
		a++;
	}
	return (tab);
}

int		main(int argc, char **argv)
{
	int size;
	int prc;
	char **tab;

	if (argc != 3)
		return (ft_error(0));
	size = ft_atoi(argv[1]);
	prc = ft_atoi(argv[2]);
	if ((size < 10 || size > 40) || (prc < 0 || prc > 75))
		return (ft_error(0));
	if ((tab = ft_demine(size, prc)) == NULL)
		return (ft_error(1));
	return (0);
}
