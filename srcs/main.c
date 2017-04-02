/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aancel <aancel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/02 09:29:33 by aancel            #+#    #+#             */
/*   Updated: 2017/04/02 12:03:56 by aancel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/demineur.h"

int		close_demine(t_env *ptr)
{
	mlx_destroy_image(ptr->mlx, ptr->img->ptr_img);
	mlx_destroy_window(ptr->mlx, ptr->win);
	free(ptr->ref);
	free(ptr->tab);
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
	while (a < ptr->size_x)
	{
		b = 0;
		while (b < ptr->size_y)
		{
			if ((a < ptr->x1 - (ptr->pxl * 3 / 2) || a > ptr->x2 + (ptr->pxl * 3 / 2) || b < ptr->y1 - (ptr->pxl * 3 / 2) || b > ptr->y2 + (ptr->pxl * 3 / 2)) && ABS(a - b) % 25 == 0)
			{
				pix_put_img(ptr, a + 1, b, 0x00ffffff);
				pix_put_img(ptr, a, b + 1, 0x00ffffff);
				pix_put_img(ptr, a - 1, b, 0x00ffffff);
				pix_put_img(ptr, a, b - 1, 0x00ffffff);
				pix_put_img(ptr, a, b, 0x00000000);
			}
			if ((a < ptr->x1 - (ptr->pxl * 3 / 2) || a > ptr->x2 + (ptr->pxl * 3 / 2) || b < ptr->y1 - (ptr->pxl * 3 / 2) || b > ptr->y2 + (ptr->pxl * 3 / 2)) && ABS(a + b) % 25 == 0)
			{
				pix_put_img(ptr, a + 1, b, 0x00ffffff);
				pix_put_img(ptr, a, b + 1, 0x00ffffff);
				pix_put_img(ptr, a - 1, b, 0x00ffffff);
				pix_put_img(ptr, a, b - 1, 0x00ffffff);
				pix_put_img(ptr, a, b, 0x00000000);
			}
			if ((a == ptr->x1 - (ptr->pxl * 3 / 2) || a == ptr->x2 + (ptr->pxl * 3 / 2) || b == ptr->y1 - (ptr->pxl * 3 / 2) || b == ptr->y2 + (ptr->pxl * 3 / 2)))
			{
				pix_put_img(ptr, a + 1, b, 0x00ffffff);
				pix_put_img(ptr, a, b + 1, 0x00ffffff);
				pix_put_img(ptr, a - 1, b, 0x00ffffff);
				pix_put_img(ptr, a, b - 1, 0x00ffffff);
				pix_put_img(ptr, a, b, 0x00000000);
			}
			if ((a == ptr->x1 - (ptr->pxl * 3 / 2) || a == ptr->x2 + (ptr->pxl * 3 / 2) || b == ptr->y1 - (ptr->pxl * 3 / 2) || b == ptr->y2 + (ptr->pxl * 3 / 2)))
			{
				pix_put_img(ptr, a + 1, b, 0x00ffffff);
				pix_put_img(ptr, a, b + 1, 0x00ffffff);
				pix_put_img(ptr, a - 1, b, 0x00ffffff);
				pix_put_img(ptr, a, b - 1, 0x00ffffff);
				pix_put_img(ptr, a, b, 0x00000000);
			}
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
	mlx_string_put(ptr->mlx, ptr->win, ptr->x1, ptr->y2, 0x00000000, "L = Discover   R = Protect");
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

int		main(int argc, char **argv)
{
	int sr;
	
	srand(time(NULL));
	if ((sr = ft_rand_ab(0, 3)) == 0)
		system("afplay EvenS_Tell.mp3 &");
	else if (sr == 1)
		system("afplay music.mp3 &");
	else
		system("afplay MuraMasa.mp3 &");
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
