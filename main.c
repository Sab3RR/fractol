#include <stdio.h>
#include "fractol.h"
#include <pthread.h>



void	put_pixel(t_var *var, int y, int x, int color)
{
	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	*(int*)(var->img_addr + ((x + y * WIDTH) * var->bpp / 8)) = color;
}

void	DrawPoint(t_var *var, double y, double x, int color)
{
	int yCentr;
	int xCentr;
	int Inty;
	int Intx;

	yCentr = HEIGHT / 2;
	xCentr = WIDTH / 2;
	Inty = yCentr - (int)(y * var->scale / 4) + var->yShift;
	Intx = xCentr + (int)(x * var->scale / 4) + var->xShift;
	put_pixel(var, Inty, Intx, color);
}

int 	ft_isfull(t_var *var, int y, int x)
{
	if (var->map[x + y * WIDTH])
	{
		return (1);
	}
	var->map[x + y * WIDTH] = 1;
	return (0);
}

void	DrawMadelbrot(t_var var, t_var *var2)
{
//	double a;
//	double b;
//	double x;
//	double y;
//	double xtmp;
//	double ytmp;
//	int iterator;
//
////	ft_bzero(var.img_addr, (size_t)(WIDTH * HEIGHT * var.bpp / 8));
//	a = -2;
//	while (a <= 2)
//	{
//		b = -2;
//		while (b <= 2)
//		{
//			x = a;
//			y = b;
//			iterator = 0;
//			while (iterator < var.iterations && x * x + y * y < 4) {
//				xtmp = x * x - y * y + a;
//				ytmp = 2 * x * y + b;
//				x = xtmp;
//				y = ytmp;
//				iterator++;
//			}
//			if (iterator == var.iterations) {
//				DrawPoint(var2, b, a, 0x000000);
//			} else if (iterator > var.iterations * 0.8)
//			{
//				DrawPoint(var2, b, a, 0xFF0000);
//			}
//			else if (iterator > var.iterations / 2) {
//				DrawPoint(var2, b, a, 0xFFFF00);
//			} else
//			{
//				DrawPoint(var2, b, a, 0xFFFFFF);
//			}
//			b += (double)4 / var.scale;
////			b += 0.001;
//		}
//		a += (double)4 / var.scale;
////		a += 0.001;
//	}
//	var2->init -= 1;
//	mlx_put_image_to_window(var.mlx_ptr, var.win_ptr, var.img_ptr, 0, 0);
	int 	px;
	int 	py;
	double	a;
	double	b;
	double	x;
	double	y;
	double	xtmp;
	double	ytmp;
	int 	iterator;

	py = 0;
//	a = (var.yShift + (double)HEIGHT / 2 + py - HEIGHT) / var.scale;
//	b = (var.xShift + (double)WIDTH / 2 + px - WIDTH) / var.scale;

	while (py < HEIGHT)
	{
		a = (-var.yShift + ((double)HEIGHT / 2) + (py - HEIGHT)) / (var.scale / 2) * 2;
		px = 0;
		while (px < WIDTH)
		{
			if (ft_isfull(var2, py, px))
			{
				px++;
				continue;
			}
			put_pixel(var2, py, px, 0xFFFFFF);
			b = (-var.xShift + ((double)WIDTH / 2) + (px - WIDTH)) / (var.scale / 2) * 2;
			y = a;
			x = b;
			iterator = 0;
			while (iterator < var.iterations && x * x + y * y < 4) {
				xtmp = x * x - y * y + b;
				ytmp = 2 * x * y + a;
				x = xtmp;
				y = ytmp;
				iterator++;
			}
			if (iterator == var.iterations) {
				put_pixel(var2, py, px, 0x000000);
			}
//			else if (iterator > var.iterations * 0.8)
//			{
//				put_pixel(var2, py, px, 0xFF0000);
//			}
//			else if (iterator > var.iterations / 10)
//			{
//				put_pixel(var2, py, px, 0x00FF00);
//			}
//			else if (iterator > var.iterations / 50)
//			{
//				put_pixel(var2, py, px, 0xFFFF00);
//			}
//			else if (iterator > var.iterations / 100)
//			{
//				put_pixel(var2, py, px, 0x00FFFF);
//			}
			else
			{
				put_pixel(var2, py, px, (0x02596D * iterator * abs(var2->color)));
			}
//			else
//				put_pixel(var2, py, px, (0x403840 * iterator));
			px++;
		}
		py++;
	}

}

void	RevCenterShift(t_var *var, int x, int y)
{
	int yCentr;
	int xCentr;

	yCentr = HEIGHT / 2;
	xCentr = WIDTH / 2;
//	if (x < xCentr && y < yCentr)
//	{
//		var->xShift -= (xCentr - x) * x / xCentr;
//		var->yShift -= (yCentr - y) * y / yCentr;
//	}
//	else if (x > xCentr && y < yCentr)
//	{
//		var->xShift -= (x - xCentr) * xCentr / x;
//		var->yShift += (yCentr - y) * y / yCentr;
//	}
//	else if (x < xCentr && y > yCentr)
//	{
//		var->xShift -= (xCentr - x) * x / xCentr;
//		var->yShift += (y - yCentr) * yCentr / y;
//	}
//	else if (x > xCentr && y > yCentr)
//	{
//		var->xShift += (x - xCentr) * xCentr / x;
//		var->yShift += (y - yCentr) * yCentr / y;
//	}
	if (var->scale != 1000)
	{
		var->xShift -= var->xShift / ((var->scale - 1000) / 100);
		var->yShift -= var->yShift / ((var->scale - 1000) / 100);
	}
}

void	copy_var(t_var *var)
{
	ft_memcpy(var->var, var, sizeof(t_var));
}

void	CenterShift(t_var *var, int x, int y)
{
	int yCentr;
	int xCentr;

	yCentr = HEIGHT / 2;
	xCentr = WIDTH / 2;
	if (x < xCentr - 100 && y < yCentr - 100)
	{
		var->xShift += 50;
		var->yShift += 50;
	}
	else if (x > xCentr + 100 && y < yCentr - 100)
	{
		var->xShift -= 50;
		var->yShift += 50;
	}
	else if (x < xCentr - 100 && y > yCentr + 100)
	{
		var->xShift += 50;
		var->yShift -= 50;
	}
	else if (x > xCentr + 100 && y > yCentr - 100)
	{
		var->xShift -= 50;
		var->yShift -= 50;
	}
}

int 	key_hook(int button, t_var *var)
{
	if (button == 6)
	{

		if (var->init == 4)
		{
			ft_bzero(var->map, (size_t)(WIDTH * HEIGHT));
			var->color += 100;
		}
		var->init = 0;

//		ft_bzero(var->map, (size_t)(WIDTH * HEIGHT));
	}
	else if (button == 7)
	{

		if (var->init == 4)
		{
			ft_bzero(var->map, (size_t)(WIDTH * HEIGHT));
			var->color -= 100;
		}
		var->init = 0;

//		ft_bzero(var->map, (size_t)(WIDTH * HEIGHT));
	}
}

int		mouse_key(int button, int x, int y, t_var *var)
{
	if (button == 4)
	{
		var->scale += 50;
		CenterShift(var, x, y);
		if (var->init == 4)
		{
			copy_var(var);
			ft_bzero(var->map, (size_t)(WIDTH * HEIGHT));

		}

		var->init = 0;
	}
	if (button == 5)
	{
		if (var->scale > 1000)
			var->scale -= 50;
		RevCenterShift(var, x, y);
		if (var->init == 4)
		{
			copy_var(var);
			ft_bzero(var->map, (size_t)(WIDTH * HEIGHT));

		}
		var->init = 0;

	}
	if (button == 6)
	{
		var->iterations += 1;
		if (var->init == 4)
		{
			copy_var(var);
			ft_bzero(var->map, (size_t)(WIDTH * HEIGHT));

		}
		var->init = 0;

	}
	if (button == 7)
	{
		if (var->iterations > 0)
		{
			var->iterations -=1;
			if (var->init == 4)
			{
				copy_var(var);
				ft_bzero(var->map, (size_t)(WIDTH * HEIGHT));

			}
			var->init = 0;

		}
	}
//	DrawMadelbrot(var);
	return (0);
}

void	*mlx_loop_loop(void *param)
{
	t_var *var;

	var = (t_var*)param;
//	var->mlx_ptr = mlx_init();
//	var->win_ptr = mlx_new_window(var->mlx_ptr, WIDTH, HEIGHT, "fdf 42");
//	var->img_ptr = mlx_new_image(var->mlx_ptr, WIDTH, HEIGHT);
//	var->bpp = 32;
//	var->img_addr = mlx_get_data_addr(var->img_ptr,
//			&var->bpp, &var->size_line, &var->endian);
//	mlx_hook(var->win_ptr, 4, (1L << 17), mouse_key, (void*)var);
//	var->init = 1;
//	mlx_loop(var->mlx_ptr);
	while (1)
	{
	    if (var->init == 0)
        {
//            ft_bzero(var->img_addr, (size_t)(WIDTH * HEIGHT * var->bpp / 8));
            DrawMadelbrot(*var->var, var);
			var->init += 1;
	    	var->loopf = 0;
	    	if (var->br)
				break;
        }

	}
}

void    loop_hook(t_var *var)
{
	if (var->init == 4)
	{
		mlx_put_image_to_window(var->mlx_ptr, var->win_ptr, var->img_ptr, 0, 0);
	}

}

int main() {
	t_var	*var;


	var = (t_var *)ft_memalloc(sizeof(t_var));
	var->var = (t_var *)ft_memalloc(sizeof(t_var));
	pthread_attr_init(&var->attr[0]);
	pthread_attr_init(&var->attr[1]);
	pthread_attr_init(&var->attr[2]);
	pthread_attr_init(&var->attr[3]);
//	pthread_attr_init(&var->attr[4]);
//	pthread_attr_init(&var->attr[5]);
//	pthread_attr_init(&var->attr[6]);
//	pthread_attr_init(&var->attr[7]);
//	pthread_attr_init(&var->attr[8]);
//	pthread_attr_init(&var->attr[9]);

	var->mlx_ptr = mlx_init();
	var->win_ptr = mlx_new_window(var->mlx_ptr, WIDTH, HEIGHT, "fdf 42");
	var->img_ptr = mlx_new_image(var->mlx_ptr, WIDTH, HEIGHT);
	var->bpp = 32;
	var->img_addr = mlx_get_data_addr(var->img_ptr,
			&var->bpp, &var->size_line, &var->endian);
	var->iterations = 50;
//	var->scale = 1000;
	var->scale = 42500;
	var->yShift = -6021;
	var->xShift = -721;
	var->map = ft_memalloc((size_t)(HEIGHT * WIDTH));
	var->color = 1;
	copy_var(var);
	pthread_create(&var->tid[0], &var->attr[0], mlx_loop_loop, (void*)var);
	pthread_create(&var->tid[1], &var->attr[1], mlx_loop_loop, (void*)var);
	pthread_create(&var->tid[2], &var->attr[2], mlx_loop_loop, (void*)var);
	pthread_create(&var->tid[3], &var->attr[3], mlx_loop_loop, (void*)var);
//	pthread_create(&var->tid[4], &var->attr[4], mlx_loop_loop, (void*)var);
//	pthread_create(&var->tid[5], &var->attr[5], mlx_loop_loop, (void*)var);
//	pthread_create(&var->tid[6], &var->attr[6], mlx_loop_loop, (void*)var);
//	pthread_create(&var->tid[7], &var->attr[7], mlx_loop_loop, (void*)var);
//	pthread_create(&var->tid[8], &var->attr[8], mlx_loop_loop, (void*)var);
//	pthread_create(&var->tid[9], &var->attr[9], mlx_loop_loop, (void*)var);
//	while (!var->init)
//	{}
//	while (1)
//	{
//	DrawMadelbrot(var);
//	}

	mlx_hook(var->win_ptr, 4, (1L << 17), mouse_key, (void*)var);
	mlx_hook(var->win_ptr, 2, (1L << 17), key_hook, (void*)var);
	mlx_loop_hook(var->mlx_ptr, loop_hook, (void*)var);
	mlx_loop(var->mlx_ptr);
	printf("Hello, World!\n");
	return 0;
}