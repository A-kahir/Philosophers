/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akahir <akahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 19:52:11 by akahir            #+#    #+#             */
/*   Updated: 2025/06/01 19:52:11 by akahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_mutexes
{
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	death_mutex;
}	t_mutexes;

typedef struct s_data
{
	int				nb_philos;
	long			start_time;
	pthread_mutex_t	*fork;
	int				is_dead;
	int				must_eat_count;
	t_mutexes		*mutexes;
}	t_data;

typedef struct s_philo
{
	int				philo_id;
	int				tt_die;
	int				tt_eat;
	int				tt_sleep;
	int				nb_tt_eat;
	long			last_time_eat;
	pthread_t		thread;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
	t_data			*g_data;
	struct s_philo	*next;
}	t_philo;

// initialisation :
t_philo	*init_philos(char **argv);
t_data	*ft_init_global_data(t_philo *philo, char **argv);
void	ft_init_mutexes(t_data *g_data, char **argv);

// action && monitoring :
void	ft_print_actions(t_philo *philo, char *msg);
void	*ft_action(void *var);
void	*ft_monitor_philo(void *var);

// utils philo :
t_philo	*creat_node(t_philo *philo, char **argv, int *index);
t_data	*ft_allocation(t_data *g_data, char **argv);
void	ft_clean_destroy(t_philo *philo, t_data *g_data);

// Libft functions:
void	print_msg(int flag);
int		parse_args(int argc, char **argv);
int		ft_atoi(char *str);
int		ft_strcmp(char *s1, char *s2);
long ft_static_var(long change_to, int flag);

#endif