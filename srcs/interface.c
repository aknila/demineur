/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aancel <aancel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/02 09:50:31 by aancel            #+#    #+#             */
/*   Updated: 2017/04/02 10:45:15 by aancel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/demineur.h"

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
	mlx_string_put(ptr->mlx, ptr->win, ptr->x1, ptr->y2, 0x00000000, "L = Discover   R = Protect");
	if (ptr->sum == ptr->nbr && ptr->stop == 0)
		set_finish(ptr, 1);
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
