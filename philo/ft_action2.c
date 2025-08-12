/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_action2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akahir <akahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 17:07:20 by akahir            #+#    #+#             */
/*   Updated: 2025/08/12 16:50:02 by akahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ft_take_pair_philo(t_philo *philo)
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

static void	ft_take_impaire_philo(t_philo *philo)
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
	if (philo->philo_id % 2 == 0)
		ft_take_pair_philo(philo);
	else
		ft_take_impaire_philo(philo);
	pthread_mutex_lock(&philo->g_data->mutexes->death_mutex);
	if (philo->g_data->is_dead)
	{
		pthread_mutex_unlock(&philo->g_data->mutexes->death_mutex);
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		return ;
	}
	philo->last_time_eat = ft_time();
	pthread_mutex_unlock(&philo->g_data->mutexes->death_mutex);
	ft_print_actions(philo, "is eating");
}
