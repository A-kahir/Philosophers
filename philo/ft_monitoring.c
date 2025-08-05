/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_monitoring.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akahir <akahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 19:51:57 by akahir            #+#    #+#             */
/*   Updated: 2025/06/01 19:51:57 by akahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_check_die(t_philo *curr, int *full_eat)
{
	struct timeval	tv;
	long			nw;

	pthread_mutex_lock(&curr->g_data->mutexes->death_mutex);
	gettimeofday(&tv, NULL);
	nw = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	if (nw - curr->last_time_eat > curr->tt_die)
	{
		curr->g_data->is_dead = 1;
		pthread_mutex_unlock(&curr->g_data->mutexes->death_mutex);
		ft_print_actions(curr, "died");
		return (-1);
	}
	if (curr->g_data->must_eat_count == -1
		|| curr->nb_tt_eat < curr->g_data->must_eat_count)
		*full_eat = 0;
	pthread_mutex_unlock(&curr->g_data->mutexes->death_mutex);
	return (0);
}

void	*ft_monitor_philo(void *arg)
{
	t_philo	*curr;
	t_philo	*start;
	t_data	*g_data;
	int		full_eat;

	start = (t_philo *)arg;
	g_data = start->g_data;
	while (1)
	{
		full_eat = 1;
		curr = start;
		while (curr)
		{
			if (ft_check_die(curr, &full_eat) == -1)
				return (NULL);
			pthread_mutex_lock(&g_data->mutexes->death_mutex);
			if (g_data->is_dead)
			{
				pthread_mutex_unlock(&g_data->mutexes->death_mutex);
				return (NULL);
			}
			pthread_mutex_unlock(&g_data->mutexes->death_mutex);
			curr = curr->next;
		}
		if (full_eat)
		{
			pthread_mutex_lock(&g_data->mutexes->death_mutex);
			g_data->is_dead = 1;
			pthread_mutex_unlock(&g_data->mutexes->death_mutex);
			return (NULL);
		}
		usleep(100);
	}
}
