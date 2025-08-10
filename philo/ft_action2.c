/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_action2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akahir <akahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 17:07:20 by akahir            #+#    #+#             */
/*   Updated: 2025/08/10 17:11:47 by akahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ft_take_one_philo(t_philo *philo)
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
	pthread_mutex_unlock(philo->left_fork);
}

static void	ft_take_even_philo(t_philo *philo)
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

static void	ft_take_odd_philo(t_philo *philo)
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
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		return ;
	}
	pthread_mutex_unlock(&philo->g_data->mutexes->death_mutex);
	ft_print_actions(philo, "has taken a fork");
}

void	ft_start_eating(t_philo *philo)
{
	struct timeval	tv;

	if (philo->g_data->nb_philos == 1)
		return (ft_take_one_philo(philo));
	if (philo->philo_id % 2 == 0)
		ft_take_even_philo(philo);
	else
		ft_take_odd_philo(philo);
	pthread_mutex_lock(&philo->g_data->mutexes->death_mutex);
	if (philo->g_data->is_dead)
	{
		pthread_mutex_unlock(&philo->g_data->mutexes->death_mutex);
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		return ;
	}
	gettimeofday(&tv, NULL);
	philo->last_time_eat = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	pthread_mutex_unlock(&philo->g_data->mutexes->death_mutex);
	ft_print_actions(philo, "is eating");
}
