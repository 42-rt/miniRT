/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_try_atof.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 05:36:46 by jkong             #+#    #+#             */
/*   Updated: 2022/08/02 18:56:52 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>

static int	_isspace(int c)
{
	return ((011 <= c && c <= 015) || c == ' ');
}

static int	_isdigit(int c)
{
	return ('0' <= c && c <= '9');
}

static double	_atof(const char *str)
{
	int		sign;
	double	number;
	int		i;

	while (_isspace(*str))
		str++;
	sign = 0;
	if (*str == '+' || *str == '-')
		sign = *str++ == '-';
	number = 0;
	while (*str && _isdigit(*str))
		number = 10.0 * number + (1 - (sign << 1)) * (*str++ - '0');
	if (*str == '.')
	{
		str++;
		i = 0;
		while (str[i] && _isdigit(str[i]))
			number = 10.0 * number + (1 - (sign << 1)) * (str[i++] - '0');
		str += i;
		while (--i >= 0)
			number /= 10.0;
	}
	return (number);
}

double	try_atof(const char *str, double *out)
{
	int		i;
	int		j;

	if (!out)
		return (0);
	*out = 0;
	i = 0;
	while (_isspace(str[i]))
		i++;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i] == '0')
		i++;
	j = 0;
	while (_isdigit(str[i + j]))
		j++;
	if (str[i + j] == '.')
		j++;
	while (_isdigit(str[i + j]))
		j++;
	if (str[i + j])
		return (0);
	*out = _atof(str);
	return (1);
}
