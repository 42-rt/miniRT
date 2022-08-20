/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_pixel.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 14:16:07 by jkong             #+#    #+#             */
/*   Updated: 2022/08/20 10:16:42 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "libft.h"

#include "mlx.h"

static t_pixel	*_get_data_pos(char *ptr, int x, int y, int size_of_line)
{
	return (&((t_pixel *)ptr)[x + y * (size_of_line / sizeof(t_pixel))]);
}

/*
 * 0 : Little Endian
 * 1 : Bit Endian (Network Endian)
*/
static t_pixel	_make_pixel(int color, int endian)
{
	t_pixel			result;
	unsigned char	*buf;
	size_t			i;
	size_t			size;
	unsigned char	temp;

	result = (t_pixel)color;
	if (endian != 0)
	{
		buf = (unsigned char *)&result;
		size = sizeof(result);
		i = 0;
		while (i < size / 2)
		{
			temp = buf[size - 1 - i];
			buf[i] = buf[size - 1 - i];
			buf[size - 1 - i] = temp;
			i++;
		}
	}
	return (result);
}

void	fill_image(t_image *image, unsigned char byte)
{
	char	*ptr;
	int		size_of_line;
	int		ignore;

	ptr = mlx_get_data_addr(image->ptr, &ignore, &size_of_line, &ignore);
	ft_memset(ptr, byte, size_of_line * image->height);
}

int	get_pixel(t_image *image, int x, int y, int *pcolor)
{
	char	*ptr;
	int		bpp;
	int		size_of_line;
	int		endian;
	t_pixel	pixel;

	if (x < 0 || x >= image->width)
		return (0);
	if (y < 0 || y >= image->height)
		return (0);
	ptr = mlx_get_data_addr(image->ptr, &bpp, &size_of_line, &endian);
	if (bpp != sizeof(t_pixel) * BIT_COUNT)
		exit(EXIT_FAILURE);
	pixel = *_get_data_pos(ptr, x, y, size_of_line);
	*pcolor = _make_pixel(pixel, endian);
	return (1);
}

void	put_pixel(t_image *image, int x, int y, int color)
{
	char	*ptr;
	int		bpp;
	int		size_of_line;
	int		endian;
	t_pixel	pixel;

	if (x < 0 || x >= image->width)
		return ;
	if (y < 0 || y >= image->height)
		return ;
	ptr = mlx_get_data_addr(image->ptr, &bpp, &size_of_line, &endian);
	if (bpp != sizeof(t_pixel) * BIT_COUNT)
		exit(EXIT_FAILURE);
	pixel = _make_pixel(color, endian);
	*_get_data_pos(ptr, x, y, size_of_line) = pixel;
}
