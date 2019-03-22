#ifndef FRACTOL_H
# define FRACTOL_H
# include <mlx.h>
# include "libft/libft.h"
# include <fcntl.h>
# include <math.h>
# include <pthread.h>
# define WIDTH 1920
# define HEIGHT 1080

typedef struct		s_var
{
	void			*mlx_ptr;
	void			*win_ptr;
	void			*img_ptr;
	char			*img_addr;
	int				bpp;
	int				size_line;
	int				endian;
	int 			iterations;
	int 			scale;
	int 			xShift;
	int 			yShift;
	char 			*map;
	char 			init;
	pthread_t		tid[10];
	pthread_attr_t	attr[10];
	char 			td0;
	char 			td1;
	char			td2;
	char 			td3;
	struct s_var	*var;
	double			zoom;
	int 			color;
	char			loopf;
	char 			br;

}					t_var;
#endif
