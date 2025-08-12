/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_action.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akahir <akahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 19:51:40 by akahir            #+#    #+#             */
/*   Updated: 2025/06/01 19:51:40 by akahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ft_time(void)
{
	struct timeval	tv;
	long			time;

	gettimeofday(&tv, NULL);
	time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (time);
}

static void	ft_unlock_forks_r_l(t_philo *philo)
{
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

static void	ft_eat(t_philo *philo)
{
	long			start;
	long			nw;

	ft_start_eating(philo);
	pthread_mutex_lock(&philo->g_data->mutexes->death_mutex);
	if (philo->g_data->is_dead)
		if (pthread_mutex_unlock(&philo->g_data->mutexes->death_mutex) == 0)
			return ;
	pthread_mutex_unlock(&philo->g_data->mutexes->death_mutex);
	if (philo->g_data->nb_philos == 1)
		return ;
	start = ft_time();
	while (1)
	{
		nw = ft_time();
		if (nw - start >= philo->tt_eat)
			break ;
		pthread_mutex_lock(&philo->g_data->mutexes->death_mutex);
		if (philo->g_data->is_dead)
			if (pthread_mutex_unlock(&philo->g_data->mutexes->death_mutex) == 0)
				break ;
		pthread_mutex_unlock(&philo->g_data->mutexes->death_mutex);
		usleep(100);
	}
	ft_unlock_forks_r_l(philo);
}

static	void	ft_think_sleep(t_philo *philo)
{
	while (1)
	{
		pthread_mutex_lock(&philo->g_data->mutexes->death_mutex);
		if (philo->g_data->is_dead)
			if (pthread_mutex_unlock(&philo->g_data->mutexes->death_mutex) == 0)
				break ;
		if (philo->g_data->must_eat_count != -1
			&& philo->nb_tt_eat >= philo->g_data->must_eat_count)
			if (pthread_mutex_unlock(&philo->g_data->mutexes->death_mutex) == 0)
				break ;
		pthread_mutex_unlock(&philo->g_data->mutexes->death_mutex);
		ft_print_actions(philo, "is thinking");
		if (philo->philo_id % 2 == 1)
			usleep(500);
		ft_eat(philo);
		pthread_mutex_lock(&philo->g_data->mutexes->death_mutex);
		if (philo->g_data->is_dead)
			if (pthread_mutex_unlock(&philo->g_data->mutexes->death_mutex) == 0)
				break ;
		philo->nb_tt_eat++;
		pthread_mutex_unlock(&philo->g_data->mutexes->death_mutex);
		ft_print_actions(philo, "is sleeping");
		usleep(philo->tt_sleep * 1000);
	}
}

void	*ft_action(void *arg)
{
	t_philo			*philo;
	long			start;
	long			nw;

	philo = (t_philo *)arg;
	if (philo->philo_id % 2 == 1)
	{
		start = ft_time();
		while (1)
		{
			nw = ft_time();
			if (nw - start >= 2)
				break ;
			pthread_mutex_lock(&philo->g_data->mutexes->death_mutex);
			if (philo->g_data->is_dead)
			{
				pthread_mutex_unlock(&philo->g_data->mutexes->death_mutex);
				return (NULL);
			}
			pthread_mutex_unlock(&philo->g_data->mutexes->death_mutex);
			usleep(100);
		}
	}
	return (ft_think_sleep(philo), NULL);
}
