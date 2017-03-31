#ifndef DEMINE_H
# define DEMINE_H

# include "../minilibx_macos/mlx.h"
# include "color.h"
# include "../libft/includes/libft.h"
# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>
# include <string.h>
# include <fcntl.h>
# include <math.h>
# include <stdlib.h>
# include <time.h>

// # define malloc(x)	malloc(-1)     // pour tester la protection

typedef struct	s_img
{
	void		*ptr_img;
	char		*bts;
	int			size_line;
	int			bpp;
	int			end;
}				t_img;

typedef struct	s_env
{
	int			pxl;
	int			size_x;
	int			size_y;
	void		*mlx;
	void		*win;
	int			x1;
	int			x2;
	int			y1;
	int			y2;
	int			c1;
	int			c2;
	int			sum;
	int			nbr;
	int			prc;
	int			stop;
	t_img		*img;
	char		**tab;
	char		**ref;
	int			size;
}				t_env;

int		close_demine(t_env *ptr);
int		key_code(int kc, t_env *ptr);
int		ft_error(int i);
int		ft_rand_ab(int a, int b);
int		ft_nbr_of_mine(char **tab, int i, int j, int size);
char	**ft_putmine(char **tab, int size, int *list, int mine);
char	**ft_set_demine(int size, int prc);
void	pix_put_img(t_env *ptr, int x, int y, int color);
void	mlx_clr_img(t_env *ptr, int color);
void	set_case(t_env *ptr);
void	set_color(t_env *ptr, char c);
void	set_finish(t_env *ptr, int i);
void	aff_demine(t_env *ptr);
void	demine(t_env *ptr);
void	check_ref(t_env *ptr, int a, int b);
int		mouse_code(int button, int x, int y, t_env *ptr);
void	ft_start_demine(char **tab, int size, int prc);
int		main(int argc, char **argv);
int		do_demine(int size, int prc);
int		retry_demine(t_env *ptr);

#endif
