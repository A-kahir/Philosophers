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
	long	current_time;
	long	start_time;
	int		dead;

	if (!philo->g_data || !philo->g_data->mutexes)
		return ;
	pthread_mutex_lock(&philo->g_data->mutexes->print_mutex);
	pthread_mutex_lock(&philo->g_data->mutexes->death_mutex);
	dead = philo->g_data->is_dead;
	start_time = philo->g_data->start_time;
	pthread_mutex_unlock(&philo->g_data->mutexes->death_mutex);
	if (ft_strcmp(msg, "died") != 0 && dead)
	{
		pthread_mutex_unlock(&philo->g_data->mutexes->print_mutex);
		return ;
	}
	current_time = ft_time();
	printf("%ld %d %s\n", current_time - start_time, philo->philo_id, msg);
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
			(pthread_mutex_destroy(&g_data->mutexes->meals_mutex));
			free(g_data->mutexes);
		}
		(free(g_data->fork), free(g_data));
	}
	while (philo)
	{
		temp = philo->next;
		1 && (free(philo), philo = temp);
	}
}

t_data	*ft_allocation(t_data *g_data, char **argv)
{
	g_data = malloc(sizeof(t_data));
	if (!g_data)
		return (NULL);
	g_data->nb_philos = ft_atoi(argv[1]);
	g_data->fork = malloc(g_data->nb_philos * sizeof(pthread_mutex_t));
	if (g_data->fork == NULL)
		return (free(g_data), NULL);
	g_data->is_dead = 0;
	g_data->start_time = ft_time();
	return (g_data);
}

t_philo	*creat_node(t_philo *philo, char **argv, int *index)
{
	philo = malloc(sizeof(t_philo));
	if (!philo)
		return (NULL);
	philo->philo_id = *index;
	philo->tt_die = ft_atoi(argv[2]);
	philo->tt_eat = ft_atoi(argv[3]);
	philo->tt_sleep = ft_atoi(argv[4]);
	philo->nb_tt_eat = 0;
	philo->last_time_eat = ft_time();
	philo->next = NULL;
	return (philo);
}

void	ft_have_one_philo(t_philo *philo)
{
	ft_print_actions(philo, "is thinking");
	ft_print_actions(philo, "has taken a fork");
	usleep(philo->tt_die);
	printf("%d %d %s\n", philo->tt_die,
		philo->philo_id, "is died");
}
