/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpuscedd <gpuscedd@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 14:05:06 by gpuscedd          #+#    #+#             */
/*   Updated: 2024/05/11 14:11:52 by gpuscedd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_valid(int c, int baselen)
{
	if (ft_isdigit(c))
		return (c - '0' < baselen);
	if (ft_islower(c))
		return (c - 'a' + 10 < baselen);
	if (ft_isupper(c))
		return (c - 'A' + 10 < baselen);
	return (0);
}

static int	get_value(char c)
{
	if (ft_isdigit(c))
		return (c - '0');
	if (ft_islower(c))
		return (c - 'a' + 10);
	return (c - 'A' + 10);
}

static int	ft_checkbase(char *base)
{
	int	i;

	if (base == NULL || *base == 0 || !base[1])
		return (0);
	i = 1;
	while ((base[i]))
	{
		if (base[i] == '+' || base[i] == '-')
			return (0);
		if (base[i] - base[i - 1] != 1)
			if (!(ft_isdigit(base[i - 1])
					&& (base[i] == 'a' || base[i] == 'A')))
				return (0);
		i++;
	}
	if (base[i])
		return (0);
	return (i);
}

int	ft_atoi_base(const char *str, char *base)
{
	int	sum;
	int	i;
	int	sign;
	int	baselen;

	baselen = ft_checkbase(base);
	if (str == NULL || !*str || baselen == 0)
		return (0);
	i = 0;
	sign = 1;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '+' || str[i] == '-')
		if (str[i++] == '-')
			sign = -1;
	sum = 0;
	while (is_valid(str[i], baselen))
	{
		sum *= baselen;
		sum += get_value(str[i]);
		i++;
	}
	return (sign * sum);
}
