/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_philos.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akahir <akahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 19:52:25 by akahir            #+#    #+#             */
/*   Updated: 2025/06/01 19:52:25 by akahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_print_actions(t_philo *philo, char *msg)
{
	struct timeval	tv;
	long			time;
	int				dead;

	if (!philo->g_data || !philo->g_data->mutexes)
	{
		printf("g_data || mutexes is NULL for philo %d\n", philo->philo_id);
		return ;
	}
	pthread_mutex_lock(&philo->g_data->mutexes->print_mutex);
	pthread_mutex_lock(&philo->g_data->mutexes->death_mutex);
	dead = philo->g_data->is_dead;
	if (ft_strcmp(msg, "died") != 0 && dead)
	{
		pthread_mutex_unlock(&philo->g_data->mutexes->death_mutex);
		pthread_mutex_unlock(&philo->g_data->mutexes->print_mutex);
		return ;
	}
	pthread_mutex_unlock(&philo->g_data->mutexes->death_mutex);
	gettimeofday(&tv, NULL);
	time = ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
	printf("%ld %d %s\n", time - philo->g_data->start_time,
		philo->philo_id, msg);
	pthread_mutex_unlock(&philo->g_data->mutexes->print_mutex);
}

void	ft_clean_destroy(t_philo *philo, t_data *g_data)
{
	t_philo	*temp;
	int		i;

	if (g_data)
	{
		i = 0;
		while (i < g_data->nb_philos)
		{
			pthread_mutex_destroy(&g_data->fork[i]);
			i++;
		}
		if (g_data->mutexes)
		{
			(pthread_mutex_destroy(&g_data->mutexes->print_mutex));
			(pthread_mutex_destroy(&g_data->mutexes->death_mutex));
			free(g_data->mutexes);
		}
		(free(g_data->fork), free(g_data));
	}
	while (philo)
	{
		temp = philo->next;
		free(philo);
		philo = temp;
	}
}

t_data	*ft_allocation(t_data *g_data, char **argv)
{
	struct timeval	tv;

	g_data = malloc(sizeof(t_data));
	if (!g_data)
		return (NULL);
	g_data->nb_philos = ft_atoi(argv[1]);
	g_data->fork = malloc(g_data->nb_philos * sizeof(pthread_mutex_t));
	if (g_data->fork == NULL)
		return (free(g_data), NULL);
	g_data->is_dead = 0;
	gettimeofday(&tv, NULL);
	g_data->start_time = ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
	return (g_data);
}

t_philo	*creat_node(t_philo *philo, char **argv, int *index)
{
	struct timeval	tv;

	philo = malloc(sizeof(t_philo));
	if (!philo)
		return (NULL);
	philo->philo_id = *index;
	philo->tt_die = ft_atoi(argv[2]);
	philo->tt_eat = ft_atoi(argv[3]);
	philo->tt_sleep = ft_atoi(argv[4]);
	philo->nb_tt_eat = 0;
	gettimeofday(&tv, NULL);
	philo->last_time_eat = ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
	philo->next = NULL;
	return (philo);
}
