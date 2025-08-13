/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_action2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akahir <akahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 17:07:20 by akahir            #+#    #+#             */
/*   Updated: 2025/08/13 01:41:35 by akahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ft_take_pair_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	pthread_mutex_lock(&philo->g_data->mutexes->death_mutex);
	if (philo->g_data->is_dead)
	{
		pthread_mutex_unlock(&philo->g_data->mutexes->death_mutex);
		pthread_mutex_unlock(philo->right_fork);
		return ;
	}
	pthread_mutex_unlock(&philo->g_data->mutexes->death_mutex);
	ft_print_actions(philo, "has taken a fork");
	pthread_mutex_lock(philo->left_fork);
	pthread_mutex_lock(&philo->g_data->mutexes->death_mutex);
	if (philo->g_data->is_dead)
	{
		pthread_mutex_unlock(&philo->g_data->mutexes->death_mutex);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		return ;
	}
	pthread_mutex_unlock(&philo->g_data->mutexes->death_mutex);
	ft_print_actions(philo, "has taken a fork");
}

static void	ft_take_impaire_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	pthread_mutex_lock(&philo->g_data->mutexes->death_mutex);
	if (philo->g_data->is_dead)
	{
		pthread_mutex_unlock(&philo->g_data->mutexes->death_mutex);
		pthread_mutex_unlock(philo->left_fork);
		return ;
	}
	pthread_mutex_unlock(&philo->g_data->mutexes->death_mutex);
	ft_print_actions(philo, "has taken a fork");
	pthread_mutex_lock(philo->right_fork);
	pthread_mutex_lock(&philo->g_data->mutexes->death_mutex);
	if (philo->g_data->is_dead)
	{
		pthread_mutex_unlock(&philo->g_data->mutexes->death_mutex);
		ft_unlock_forks_r_l(philo);
		return ;
	}
	pthread_mutex_unlock(&philo->g_data->mutexes->death_mutex);
	ft_print_actions(philo, "has taken a fork");
}

int	ft_sleep_action(long time_check, t_philo *philo)
{
	int		die;
	long	start;

	pthread_mutex_lock(&philo->g_data->mutexes->death_mutex);
	die = philo->g_data->is_dead;
	pthread_mutex_unlock(&philo->g_data->mutexes->death_mutex);
	start = ft_time();
	while (!die && ft_time() - start < time_check)
	{
		pthread_mutex_lock(&philo->g_data->mutexes->death_mutex);
		if (philo->g_data->is_dead)
		{
			pthread_mutex_unlock(&philo->g_data->mutexes->death_mutex);
			return (-1);
		}
		pthread_mutex_unlock(&philo->g_data->mutexes->death_mutex);
		usleep(100);
	}
	return (0);
}

int	ft_start_eating(t_philo *philo)
{
	if (philo->philo_id % 2 == 0)
		ft_take_pair_forks(philo);
	else
		ft_take_impaire_forks(philo);
	pthread_mutex_lock(&philo->g_data->mutexes->death_mutex);
	if (philo->g_data->is_dead)
	{
		pthread_mutex_unlock(&philo->g_data->mutexes->death_mutex);
		ft_unlock_forks_r_l(philo);
		return (-1);
	}
	pthread_mutex_unlock(&philo->g_data->mutexes->death_mutex);
	ft_print_actions(philo, "is eating");
	pthread_mutex_lock(&philo->g_data->mutexes->meals_mutex);
	philo->last_time_eat = ft_time();
	philo->nb_tt_eat++;
	pthread_mutex_unlock(&philo->g_data->mutexes->meals_mutex);
	if (ft_sleep_action(philo->tt_eat, philo) == -1)
	{
		ft_unlock_forks_r_l(philo);
		return (-1);
	}
	return (0);
}
