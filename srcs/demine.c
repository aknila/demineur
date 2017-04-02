/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   demine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aancel <aancel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/02 09:50:23 by aancel            #+#    #+#             */
/*   Updated: 2017/04/02 10:38:13 by aancel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/demineur.h"

int		do_demine(int size, int prc)
{
	char **tab;
	if ((tab = ft_set_demine(size, prc)) == NULL)
		return (-1);
	ft_start_demine(tab, size, prc);
	return (0);
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
