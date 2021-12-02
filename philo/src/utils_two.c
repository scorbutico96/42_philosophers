/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_two.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcrisari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 15:20:19 by mcrisari          #+#    #+#             */
/*   Updated: 2021/12/02 15:20:21 by mcrisari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_strncmp(char *s1, char *s2, int n)
{
	char	*ptr1;
	char	*ptr2;

	ptr1 = s1;
	ptr2 = s2;
	if (n)
	{
		while (n-- && (*ptr1 || *ptr2))
		{
			if ((*ptr1) - (*ptr2))
				return ((*ptr1) - (*ptr2));
			ptr1++;
			ptr2++;
		}
	}
	return (0);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

static int	ft_isspace(int c)
{
	if ((c >= '\t' && c <= '\r') || c == ' ')
		return (1);
	else
		return (0);
}

int	ft_atoi(const char *str)
{
	int	it;
	int	sign;
	int	n;

	it = 0;
	sign = 1;
	n = 0;
	while (ft_isspace(str[it]))
		it++;
	if (str[it] == '-' && ft_isdigit(str[it + 1]))
	{
		sign = -1;
		it++;
	}
	if (str[it] == '+' && ft_isdigit(str[it + 1]))
		it++;
	while (ft_isdigit(str[it]))
	{
		n = (n * 10) + (str[it] - '0');
		it++;
	}
	return (n * sign);
}
