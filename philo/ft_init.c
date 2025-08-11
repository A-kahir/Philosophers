/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akahir <akahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 19:51:49 by akahir            #+#    #+#             */
/*   Updated: 2025/06/01 19:51:49 by akahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	*init_philos(char **argv)
{
	t_philo	*head;
	t_philo	*curr;
	t_philo	*new_node;
	int		i;
	int		id_philo;

	head = NULL;
	curr = NULL;
	i = 1;
	id_philo = 1;
	new_node = creat_node(head, argv, &id_philo);
	head = new_node;
	curr = new_node;
	while (i < ft_atoi(argv[1]))
	{
		id_philo++;
		new_node = creat_node(curr, argv, &id_philo);
		curr->next = new_node;
		curr = new_node;
		i++;
	}
	return (head);
}

t_data	*ft_init_global_data(t_philo *philo, char **argv)
{
	t_data	*g_data;
	t_philo	*curr;
	int		i;

	g_data = NULL;
	g_data = ft_allocation(g_data, argv);
	i = 0;
	while (i < ft_atoi(argv[1]))
	{
		pthread_mutex_init(&g_data->fork[i], NULL);
		i++;
	}
	curr = philo;
	while (curr)
	{
		curr->left_fork = &g_data->fork[curr->philo_id - 1];
		curr->right_fork = &g_data->fork[curr->philo_id % g_data->nb_philos];
		curr->g_data = g_data;
		curr = curr->next;
	}
	return (g_data);
}

void	ft_init_mutexes(t_data *g_data, char **argv)
{
	g_data->mutexes = malloc(sizeof(t_mutexes));
	if (!g_data->mutexes)
		return ;
	pthread_mutex_init(&g_data->mutexes->print_mutex, NULL);
	pthread_mutex_init(&g_data->mutexes->death_mutex, NULL);
	if (argv[5])
		g_data->must_eat_count = ft_atoi(argv[5]);
	else
		g_data->must_eat_count = -1;
}
