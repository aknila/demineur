/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_mouse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aancel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/02 09:50:39 by aancel            #+#    #+#             */
/*   Updated: 2017/04/02 09:50:41 by aancel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/demineur.h"

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
		ft_putstr(C_ROUGE "Usage : ./demineur {" C_BLEU "size" C_ROUGE "} {" 
			C_VERT "pourcent of mine" C_ROUGE "}\n" 
			C_BLEU "Size : between 10 and 50\n" 
			C_VERT "Pourcent of mine between 5 and 50\n" FIN);
	if (i == 1)
		ft_putstr(C_ROUGE 
			"Failed to create a map, retry in a few second\n");
	system("killall afplay");
	return(-1);
}
