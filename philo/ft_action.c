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

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	ft_unlock_forks_r_l(t_philo *philo)
{
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

static void	ft_eat(t_philo *philo)
{
	long			start;

	if (ft_start_eating(philo) == -1)
		return ;
	pthread_mutex_lock(&philo->g_data->mutexes->death_mutex);
	if (philo->g_data->is_dead)
	{
		pthread_mutex_unlock(&philo->g_data->mutexes->death_mutex);
		ft_unlock_forks_r_l(philo);
		return ;
	}
	pthread_mutex_unlock(&philo->g_data->mutexes->death_mutex);
	start = ft_time();
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
		ft_eat(philo);
		pthread_mutex_lock(&philo->g_data->mutexes->death_mutex);
		if (philo->g_data->is_dead)
			if (pthread_mutex_unlock(&philo->g_data->mutexes->death_mutex) == 0)
				break ;
		pthread_mutex_unlock(&philo->g_data->mutexes->death_mutex);
		ft_print_actions(philo, "is sleeping");
		ft_sleep_action(philo->tt_sleep, philo);
	}
}

void	*ft_action(void *arg)
{
	t_philo			*philo;

	philo = (t_philo *)arg;
	if (philo->philo_id % 2 == 0)
		usleep(100);
	pthread_mutex_lock(&philo->g_data->mutexes->death_mutex);
	philo->g_data->start_time = ft_time();
	pthread_mutex_unlock(&philo->g_data->mutexes->death_mutex);
	return (ft_think_sleep(philo), NULL);
}
