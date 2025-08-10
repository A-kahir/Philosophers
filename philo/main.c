/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akahir <akahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 19:52:02 by akahir            #+#    #+#             */
/*   Updated: 2025/06/01 19:52:02 by akahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_action_monitoring(t_philo *philo, pthread_t *monitor)
{
	t_philo	*curr;

	curr = philo;
	while (curr != NULL)
	{
		if (pthread_create(&curr->thread, NULL, ft_action, curr) != 0)
			return (write(2, "creation thread failed\n", 24), 1);
		curr = curr->next;
	}
	if (pthread_create(monitor, NULL, ft_monitor_philo, philo) != 0)
		return (write(2, "monitor thread failed\n", 23), 1);
	pthread_join(*monitor, NULL);
	curr = philo;
	while (curr)
	{
		pthread_join(curr->thread, NULL);
		curr = curr->next;
	}
	return (0);
}

static int ft_parsing(int argc, char **argv)
{
	int			i;

	if ((argc != 5 && argc != 6) || ft_atoi(argv[1]) == 0)
		return (print_msg(0), 1);
	if (parse_args(argc, argv) == 0)
		return (print_msg(1), 1);
	i = 0;
	while (argv[i])
	{
		if (ft_atoi(argv[i]) < 0)
			return (print_msg(1), 1);
		i++;
	}
	return (0);
}

void f()
{
	system("leaks philo");
}

static void ft_have_one_philo(t_philo *philo)
{
	ft_print_actions(philo, "has taken a fork");
	usleep(philo->tt_die);
	printf("%d %d %s\n", philo->tt_die,
		philo->philo_id, "is died");
}

int	main(int argc, char **argv)
{
	// atexit(f);
	t_philo		*philo;
	t_data		*g_data;
	pthread_t	monitor;

	if (ft_parsing(argc, argv) == 1)
		return (1);
	philo = init_philos(argv);
	if (!philo)
		return (write(2, "Failed to init philo data\n", 27), 1);
	g_data = ft_init_global_data(philo, argv);
	if (!g_data)
		return (write(2, "Failed to init global data\n", 28), 1);
	ft_init_mutexes(g_data, argv);
	if (g_data->nb_philos != 1)
		if (ft_action_monitoring(philo, &monitor) == 1)
			return (write(2, "thread is failed\n", 18), 1);
	if (g_data->nb_philos == 1)
	{
		ft_have_one_philo(philo);
		return (0);
	}
	ft_clean_destroy(philo, g_data);
}
