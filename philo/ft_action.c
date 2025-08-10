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

static	void	ft_taking_eating(t_philo *philo)
{
	struct timeval	tv;

	if (philo->g_data->nb_philos == 1)
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
		return ;
	}
	if (philo->philo_id % 2 == 0)
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
	else
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

static	void	ft_eat(t_philo *philo)
{
	struct timeval	tv;
	long			start;
	long			nw;

	ft_taking_eating(philo);
	pthread_mutex_lock(&philo->g_data->mutexes->death_mutex);
	if (philo->g_data->is_dead)
	{
		pthread_mutex_unlock(&philo->g_data->mutexes->death_mutex);
		return ;
	}
	pthread_mutex_unlock(&philo->g_data->mutexes->death_mutex);
	if (philo->g_data->nb_philos == 1)
		return ;
	gettimeofday(&tv, NULL);
	start = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	while (1)
	{
		gettimeofday(&tv, NULL);
		nw = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
		if (nw - start >= philo->tt_eat)
			break ;
		pthread_mutex_lock(&philo->g_data->mutexes->death_mutex);
		if (philo->g_data->is_dead)
		{
			pthread_mutex_unlock(&philo->g_data->mutexes->death_mutex);
			break ;
		}
		1 && (pthread_mutex_unlock(&philo->g_data->mutexes->death_mutex), usleep(100));
	}
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

static	void	ft_think_sleep(t_philo *philo)
{
	while (1)
	{
		pthread_mutex_lock(&philo->g_data->mutexes->death_mutex);
		if (philo->g_data->is_dead)
		{
			pthread_mutex_unlock(&philo->g_data->mutexes->death_mutex);
			break ;
		}
		if (philo->g_data->must_eat_count != -1
			&& philo->nb_tt_eat >= philo->g_data->must_eat_count)
		{
			pthread_mutex_unlock(&philo->g_data->mutexes->death_mutex);
			break ;
		}
		pthread_mutex_unlock(&philo->g_data->mutexes->death_mutex);
		ft_print_actions(philo, "is thinking");
		if (philo->philo_id % 2 == 1)
			usleep(500);
		ft_eat(philo);
		pthread_mutex_lock(&philo->g_data->mutexes->death_mutex);
		if (philo->g_data->is_dead)
		{
			pthread_mutex_unlock(&philo->g_data->mutexes->death_mutex);
			break ;
		}
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
	struct timeval	tv;

	philo = (t_philo *)arg;
	if (philo->philo_id % 2 == 1)
	{
		gettimeofday(&tv, NULL);
		start = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
		while (1)
		{
			gettimeofday(&tv, NULL);
			nw = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
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
