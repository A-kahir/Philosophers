/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akahir <akahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 19:52:18 by akahir            #+#    #+#             */
/*   Updated: 2025/06/01 19:52:18 by akahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_msg(int flag)
{
	if (flag == 0)
	{
		write(2, "Error: invalid number of arguments\n\n", 37);
		write(2, "      ./philo (number of philosophers) (time to die) ", 54);
		write(2, "(time to eat) (time to sleep) ", 31);
		write(2, "(number_of_times_each_philosopher_must_eat)\n", 45);
	}
	else if (flag == 1)
	{
		write(2, "Error\n", 7);
	}
}

int	parse_args(int argc, char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (i <= (argc - 1))
	{
		j = 0;
		if (argv[i][0] == '\0')
			return (0);
		if (argv[i][0] == '+')
			j++;
		while (argv[i][j] != '\0')
		{
			if (!(argv[i][j] >= '0' && argv[i][j] <= '9'))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	ft_atoi(char *str)
{
	int					i;
	int					signe;
	int					result;

	signe = 1;
	i = 0;
	result = 0;
	while (((str[i] >= 9 && str[i] <= 13) || str[i] == 32))
		i++;
	if ((str[i] == '-') || (str[i] == '+'))
	{
		if (str[i] == '-')
			signe = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (result > (2147483647 - (str[i] - '0')) / 10)
			return (-1);
		result = ((result * 10) + (str[i] - '0'));
		i++;
	}
	return (result * signe);
}

int	ft_strcmp(char *s1, char *s2)
{
	size_t	i;

	if (!s1)
		return (1);
	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
