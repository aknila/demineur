#include "../includes/demineur.h"

int		close_demine(t_env *ptr)
{
	mlx_destroy_image(ptr->mlx, ptr->img->ptr_img);
	mlx_destroy_window(ptr->mlx, ptr->win);
	system("killall afplay");
	exit(0);
	return (0);
}

int		retry_demine(t_env *ptr)
{
	mlx_destroy_image(ptr->mlx, ptr->img->ptr_img);
	mlx_destroy_window(ptr->mlx, ptr->win);
	do_demine(ptr->size, ptr->prc);
	return (0);
}

int		key_code(int kc, t_env *ptr)
{
	if (kc == 53)
		close_demine(ptr);
	if (kc == 48 && ptr->stop != 0)
		retry_demine(ptr);
	return (0);
}

int		ft_error(int i)
{
	if (i == 0)
		ft_putstr(C_ROUGE "Usage : ./demineur {" C_BLEU "size" C_ROUGE "} {" C_VERT "pourcent of mine"
			C_ROUGE "}\n" C_BLEU "Size : between 10 and 50\n" C_VERT "Pourcent of mine between 5 and 50\n" FIN);
	if (i == 1)
		ft_putstr(C_ROUGE "Failed to create a map, retry in a few second\n");
	system("killall afplay");
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

char	**ft_set_demine(int size, int prc)
{
	int nb_case;
	int mine;
	char **tab;
	int *list;
	int i;
	int a;
	int b;
	int stock;

	i = 0;
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
	a = 0;
	while (a < size)
	{
		b = 0;
		while (b < size)
		{
			if (tab[a][b] == '0')
				ft_putstr(C_ROUGE);
			if (tab[a][b] == '1')
				ft_putstr(C_BLEU);
			if (tab[a][b] == '2')
				ft_putstr(C_VERT);
			if (tab[a][b] == '3')
				ft_putstr(C_JAUNE);
			if (tab[a][b] == '4')
				ft_putstr(C_ROSE);
			if (tab[a][b] == '5')
				ft_putstr(C_TURQUOISE);
			if (tab[a][b] == '6')
				ft_putstr(F_VERT);
			if (tab[a][b] == '7')
				ft_putstr(F_ROUGE);
			if (tab[a][b] == '8')
				ft_putstr(F_BLEU);
			if (tab[a][b] == '9')
				ft_putstr(C_GREY);
			ft_putchar(tab[a][b]);
			ft_putstr(" " FIN);
			b++;
		}
		ft_putchar('\n');
		a++;
	}
	return (tab);
}

void	pix_put_img(t_env *ptr, int x, int y, int color)
{
	int		r;
	int		g;
	int		b;

	r = (color & 0xFF0000) >> 16;
	g = (color & 0xFF00) >> 8;
	b = (color & 0xFF);
	if (y >= 0 && x >= 0 && y < ptr->size_x && x < ptr->size_y)
	{
		ptr->img->bts[(y * ptr->img->size_line)
			+ ((ptr->img->bpp / 8) * x) + 2] = r;
		ptr->img->bts[(y * ptr->img->size_line)
			+ ((ptr->img->bpp / 8) * x) + 1] = g;
		ptr->img->bts[(y * ptr->img->size_line)
			+ ((ptr->img->bpp / 8) * x)] = b;
	}
}

void	mlx_clr_img(t_env *ptr, int color)
{
	int x;
	int y;

	x = 0;
	while (x < ptr->size_x)
	{
		y = 0;
		while (y < ptr->size_y)
		{
			pix_put_img(ptr, x, y, color);
			y++;
		}
		x++;
	}
}

void	set_case(t_env *ptr)
{
	int a;
	int b;
	int size;
	char **tab;

	size = ptr->size;
	tab = ptr->tab;
	ptr->x1 = 2 * ptr->pxl;
	ptr->x2 = ptr->size_x - ptr->x1;
	ptr->y1 = 2 * ptr->pxl;
	ptr->y2 = ptr->size_y - ptr->y1;
	// mlx_clr_img(ptr, ft_rand_ab(0x000000, 0xffffff));
	mlx_clr_img(ptr, 0x3b99ef);
	a = 0;
	while (ptr->x1 + a <= ptr->x2)
	{
		b = 0;
		while (ptr->y1 + b <= ptr->y2)
		{
			if ((a % ptr->pxl == 0) || (b % ptr->pxl == 0))
				pix_put_img(ptr, ptr->x1 + a, ptr->y1 + b, 0x00dddddd);
			else if ((a % ptr->pxl == ptr->pxl - 1) || (b % ptr->pxl == ptr->pxl - 1) || (a % ptr->pxl == ptr->pxl - 2) || (b % ptr->pxl == ptr->pxl - 2))
				pix_put_img(ptr, ptr->x1 + a, ptr->y1 + b, 0x00606060);
			else if ((a % ptr->pxl == 1) || (b % ptr->pxl == 1) || (a % ptr->pxl == 2) || (b % ptr->pxl == 2))
				pix_put_img(ptr, ptr->x1 + a, ptr->y1 + b, 0x00606060);
			else
				pix_put_img(ptr, ptr->x1 + a, ptr->y1 + b, 0x00909090);
			b++;
		}
		a++;
	}
	a = 0;
	while(a < size)
	{
		b = 0;
		while (b < size)
		{
			ptr->ref[a][b] = 'O';
			b++;
		}
		a++;
	}
	mlx_put_image_to_window(ptr->mlx, ptr->win, ptr->img->ptr_img, 0, 0);
}

void	set_color(t_env *ptr, char c)
{
	if (c == '0')
	{
		ptr->c1 = 0x00333333; // ok
		ptr->c2 = 0x00bbbbbb;
	}
	if (c == '1')
	{
		ptr->c1 = 0x00444499; // ok
		ptr->c2 = 0x009999ff;
	}
	if (c == '2')
	{
		ptr->c1 = 0x00336600; // ok
		ptr->c2 = 0x00339900;
	}
	if (c == '3')
	{
		ptr->c1 = 0x004b0000; // ok
		ptr->c2 = 0x00ce2020;
	}
	if (c == '4')
	{
		ptr->c1 = 0x00970000; // ok
		ptr->c2 = 0x00ff6633;
	}
	if (c == '5')
	{
		ptr->c1 = 0x006633cc; // ok
		ptr->c2 = 0x009e6bff;
	}
	if (c == '6')
	{
		ptr->c1 = 0x00663300; // ok
		ptr->c2 = 0x008e5b30;
	}
	if (c == '7')
	{
		ptr->c1 = 0x00cc3300; // ok
		ptr->c2 = 0x00cc9933;
	}
	if (c == '8')
	{
		ptr->c1 = 0x00000099; // ok
		ptr->c2 = 0x000099ff;
	}
	if (c == '9')
	{
		ptr->c1 = 0x00bbbbbb; // ok
		ptr->c2 = 0x00333333;
	}
	if (c == 'P')
	{
		ptr->c1 = 0x00444499; // ok
		ptr->c2 = 0x009999ff;
	}
}

void	set_finish(t_env *ptr, int i)
{
	if (i == 1)
	{
		mlx_clr_img(ptr, 0x3b99ef);
		mlx_put_image_to_window(ptr->mlx, ptr->win, ptr->img->ptr_img, 0, 0);
		mlx_string_put(ptr->mlx, ptr->win, ptr->x1, ptr->y1, 0x00000000, "YOU WIN !!!");
		ptr->stop = 1;
	}
	if (i == 0)
	{
		ptr->stop = -1;
		aff_demine(ptr);
		mlx_string_put(ptr->mlx, ptr->win, ptr->x1, ptr->y1 / 2, 0x00000000, "YOU LOSE !!!");
	}
}

void	aff_demine(t_env *ptr)
{
	int a;
	int b;
	char c[2];

	mlx_put_image_to_window(ptr->mlx, ptr->win, ptr->img->ptr_img, 0, 0);
	a = 0;
	while (a < ptr->size)
	{
		b = 0;
		while (b < ptr->size)
		{
			c[0] = ptr->tab[a][b];
			c[1] = '\0';
			if ((ptr->ref[a][b] == 'X' && c[0] != '0') || ptr->stop == -1)
			{
				set_color(ptr, c[0]);
				mlx_string_put(ptr->mlx, ptr->win, ptr->x1 + a * ptr->pxl + 8, ptr->y1 + b * ptr->pxl + 2, ptr->c1, c);
				mlx_string_put(ptr->mlx, ptr->win, ptr->x1 + a * ptr->pxl + 8, ptr->y1 + b * ptr->pxl + 0, ptr->c1, c);
				mlx_string_put(ptr->mlx, ptr->win, ptr->x1 + a * ptr->pxl + 9, ptr->y1 + b * ptr->pxl + 1, ptr->c1, c);
				mlx_string_put(ptr->mlx, ptr->win, ptr->x1 + a * ptr->pxl + 7, ptr->y1 + b * ptr->pxl + 1, ptr->c1, c);
				mlx_string_put(ptr->mlx, ptr->win, ptr->x1 + a * ptr->pxl + 8, ptr->y1 + b * ptr->pxl + 1, ptr->c2, c);
			}
			else if (ptr->ref[a][b] == 'P')
			{
				c[0] = ptr->ref[a][b];
				set_color(ptr, c[0]);
				mlx_string_put(ptr->mlx, ptr->win, ptr->x1 + a * ptr->pxl + 8, ptr->y1 + b * ptr->pxl + 2, ptr->c1, c);
				mlx_string_put(ptr->mlx, ptr->win, ptr->x1 + a * ptr->pxl + 8, ptr->y1 + b * ptr->pxl + 0, ptr->c1, c);
				mlx_string_put(ptr->mlx, ptr->win, ptr->x1 + a * ptr->pxl + 9, ptr->y1 + b * ptr->pxl + 1, ptr->c1, c);
				mlx_string_put(ptr->mlx, ptr->win, ptr->x1 + a * ptr->pxl + 7, ptr->y1 + b * ptr->pxl + 1, ptr->c1, c);
				mlx_string_put(ptr->mlx, ptr->win, ptr->x1 + a * ptr->pxl + 8, ptr->y1 + b * ptr->pxl + 1, ptr->c2, c);
			}
			b++;
		}
		a++;
	}
	if (ptr->sum == ptr->nbr && ptr->stop == 0)
	{
		set_finish(ptr, 1);
	}
}

void	demine(t_env *ptr)
{
	int a;
	int b;
	int a1;
	int b1;
	int size;
	char **tab;
	char **ref;

	size = ptr->size;
	tab = ptr->tab;
	ref = ptr->ref;
	a = 0;
	while (a < size)
	{
		b = 0;
		while (b < size)
		{
			if (ref[a][b] == 'X')
			{
				a1 = 0;
				while (ptr->x1 + a * ptr->pxl + a1 <= ptr->x1 + (a + 1) * ptr->pxl)
				{
					b1 = 0;
					while (ptr->y1 + b * ptr->pxl + b1 <= ptr->y1 + (b + 1) * ptr->pxl)
					{
						if ((a1 % ptr->pxl == 0) || (b1 % ptr->pxl == 0))
							pix_put_img(ptr, ptr->x1 + a * ptr->pxl + a1, ptr->y1 + b * ptr->pxl + b1, 0x00dddddd);
						else if ((a1 % ptr->pxl == ptr->pxl - 1) || (b1 % ptr->pxl == ptr->pxl - 1) || (a1 % ptr->pxl == ptr->pxl - 2) || (b1 % ptr->pxl == ptr->pxl - 2))
							pix_put_img(ptr, ptr->x1 + a * ptr->pxl + a1, ptr->y1 + b * ptr->pxl + b1, 0x00909090);
						else if ((a1 % ptr->pxl == 1) || (b1 % ptr->pxl == 1) || (a1 % ptr->pxl == 2) || (b1 % ptr->pxl == 2))
							pix_put_img(ptr, ptr->x1 + a * ptr->pxl + a1, ptr->y1 + b * ptr->pxl + b1, 0x00909090);
						else
							pix_put_img(ptr, ptr->x1 + a * ptr->pxl + a1, ptr->y1 + b * ptr->pxl + b1, 0x00505050);
						b1++;
					}
					a1++;
				}
			}
			b++;
		}
		a++;
	}
	aff_demine(ptr);
}

void	check_ref(t_env *ptr, int a, int b)
{
	if (a + 1 < ptr->size && ptr->ref[a + 1][b] == 'O')
	{
		ptr->ref[a + 1][b] = 'X';
		ptr->sum--;
		if (ptr->tab[a + 1][b] == '0')
			check_ref(ptr, a + 1, b);
	}
	if (a - 1 >= 0 && ptr->ref[a - 1][b] == 'O')
	{
		ptr->ref[a - 1][b] = 'X';
		ptr->sum--;
		if (ptr->tab[a - 1][b] == '0')
			check_ref(ptr, a - 1, b);
	}
	if (b + 1 < ptr->size && ptr->ref[a][b + 1] == 'O')
	{
		ptr->ref[a][b + 1] = 'X';
		ptr->sum--;
		if (ptr->tab[a][b + 1] == '0')
			check_ref(ptr, a, b + 1);
	}
	if (b - 1 >= 0 && ptr->ref[a][b - 1] == 'O')
	{
		ptr->ref[a][b - 1] = 'X';
		ptr->sum--;
		if (ptr->tab[a][b - 1] == '0')
			check_ref(ptr, a, b - 1);
	}
	if (a + 1 < ptr->size && b + 1 < ptr->size && ptr->ref[a + 1][b + 1] == 'O')
	{
		ptr->ref[a + 1][b + 1] = 'X';
		ptr->sum--;
		if (ptr->tab[a + 1][b + 1] == '0')
			check_ref(ptr, a + 1, b + 1);
	}
	if (a + 1 < ptr->size && b - 1 >= 0 && ptr->ref[a + 1][b - 1] == 'O')
	{
		ptr->ref[a + 1][b - 1] = 'X';
		ptr->sum--;
		if (ptr->tab[a + 1][b - 1] == '0')
			check_ref(ptr, a + 1, b - 1);
	}
	if (a - 1 >= 0 && b + 1 < ptr->size && ptr->ref[a - 1][b + 1] == 'O')
	{
		ptr->ref[a - 1][b + 1] = 'X';
		ptr->sum--;
		if (ptr->tab[a - 1][b + 1] == '0')
			check_ref(ptr, a - 1, b + 1);
	}
	if (a - 1 >= 0 && b - 1 >= 0 && ptr->ref[a - 1][b - 1] == 'O')
	{
		ptr->ref[a - 1][b - 1] = 'X';
		ptr->sum--;
		if (ptr->tab[a - 1][b - 1] == '0')
			check_ref(ptr, a - 1, b - 1);
	}

}

int		mouse_code(int button, int x, int y, t_env *ptr)
{
	int a;
	int b;

	if (x > ptr->x1 && x < ptr->x2 && y > ptr->y1 && y < ptr->y2 && ptr->stop == 0)
	{
		a = (x - ptr->x1) / ptr->pxl;
		b = (y - ptr->y1) / ptr->pxl;
		if (button == 1)
		{
			if (ptr->ref[a][b] != 'P' && ptr->tab[a][b] == '9')
			{
				set_finish(ptr, 0);
				return (0);
			}
			if (ptr->ref[a][b] == 'O')
			{
				ptr->ref[a][b] = 'X';
				ptr->sum--;
				if (ptr->tab[a][b] == '0')
					check_ref(ptr, a, b);
			}
		}
		if (button == 2)
		{
			if (ptr->ref[a][b] == 'O')
			{
				ptr->ref[a][b] = 'P';

			}
			else if (ptr->ref[a][b] == 'P')
			{
				ptr->ref[a][b] = 'O';
			}
		}
		demine(ptr);
	}
	return (0);
}

void	ft_start_demine(char **tab, int size, int prc)
{
	int nbr;
	int a;
	int b;
	char c;
	int sum;
	t_env ptr;
	t_img img;

	ptr.tab = tab;
	ptr.size = size;
	sum = 0;
	c = '0';
	while (c <= '9')
	{
		nbr = 0;
		a = 0;
		while (a < size)
		{
			b = 0;
			while (b < size)
			{
				if (tab[a][b] == c)
					nbr++;
				b++;
			}
			a++;
		}
		sum += nbr;
		c++;
	}
	ptr.sum = sum;
	ptr.nbr = nbr;
	ptr.pxl = 25;
	ptr.size_x = (size + 4) * ptr.pxl;
	ptr.size_y = ptr.size_x;
	ptr.mlx = mlx_init();
	ptr.win = mlx_new_window(ptr.mlx, ptr.size_x, ptr.size_y, "Demineur");
	img.ptr_img = mlx_new_image(ptr.mlx, ptr.size_x, ptr.size_y);
	img.bts = mlx_get_data_addr(img.ptr_img, &(img.bpp), &(img.size_line), &(img.end));
	ptr.img = &img;
	ptr.ref = ft_create_tab(size, size);
	ptr.stop = 0;
	ptr.prc = prc;
	set_case(&ptr);
	mlx_hook(ptr.win, 17, (1L << 17), close_demine, &ptr);
	mlx_hook(ptr.win, 2, 3, key_code, &ptr);
	mlx_mouse_hook(ptr.win, mouse_code, &ptr);
	mlx_loop(ptr.mlx);
}

int		main(int argc, char **argv)
{
	system("afplay -t 3600 music.mp3 &");
	int size;
	int prc;

	if (argc != 3)
		return (ft_error(0));
	size = ft_atoi(argv[1]);
	prc = ft_atoi(argv[2]);
	if ((size < 10 || size > 50 || size % 10 != 0) || (prc < 5 || prc > 50))
		return (ft_error(0));
	if (do_demine(size, prc) == -1)
		return (ft_error(1));
	return (0);
}

int		do_demine(int size, int prc)
{
	char **tab;
	if ((tab = ft_set_demine(size, prc)) == NULL)
		return (-1);
	ft_start_demine(tab, size, prc);
	return (0);
}
