/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrouchon <lrouchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/10 15:55:17 by lrouchon          #+#    #+#             */
/*   Updated: 2026/08/30 17:13:08 by lrouchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdbool.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <limits.h>
# include <sys/time.h>

/* printf color macros */
# define COLOR_RED     "\x1b[31m"
# define COLOR_GREEN   "\x1b[32m"
# define COLOR_YELLOW  "\x1b[33m"
# define COLOR_BLUE    "\x1b[34m"
# define COLOR_RESET   "\x1b[0m"

typedef struct s_sync
{
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	dead_mutex;
	pthread_mutex_t	ready_mutex;
	pthread_mutex_t	finished_mutex;
	bool			dead_flag;
	int				ready_count;
	int				finished_count;
}	t_sync;

typedef struct s_times
{
	int				philosopher_amount;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				eat_count;
}	t_times;

typedef struct s_fork
{
	pthread_mutex_t			fork_mutex;
}	t_fork;

typedef struct s_philosopher
{
	pthread_t				thread;
	t_times					*times;
	t_sync					*sync;
	t_fork					*fork;
	char					*name;
	int						index;
	pthread_mutex_t			last_meal_mutex;
	long long				last_meal_time;
	pthread_mutex_t			started_mutex;
	bool					started;
	struct s_philosopher	*previous;
	struct s_philosopher	*next;
}	t_philosopher;

/* main.c */
int				monitor_loop(t_philosopher *philosopher);
void			*monitor(void *arg);
void			lone_philosopher(t_philosopher *philosopher);
void			thread_create_and_wait(
					t_philosopher *table,
					t_times *times,
					int i
					);

/* process.c */
void			update_last_meal_time(t_philosopher *philosopher);
int				eat(t_philosopher *philosopher);
int				nap(t_philosopher *philosopher);
int				think(t_philosopher *philosopher);
void			*lifecycle(void	*arg);

/* pre_process.c*/
void			ready_loop(t_philosopher *philosopher);
void			starting_block(t_philosopher *philosopher);

/* forks.c */
int				lock_fork(
					t_philosopher *philosopher,
					t_fork *fork
					);
int				take_forks(t_philosopher *philosopher);
int				release_forks(t_philosopher *philosopher);

/* init.c */
t_times			*init_times(
					int argc,
					const char **argv
					);
t_philosopher	*init_philosopher(
					t_times *times,
					t_sync *sync,
					int index
					);
t_sync			*init_sync(void);
t_philosopher	*init_table(
					const char **argv,
					t_times *times
					);

/* ft_utils_1.c */
int				ft_isdigit(int c);
int				ft_isspace(unsigned char c);
size_t			ft_strlen(const char *str);
int				ft_atoi(const char *str);

/* ft_utils_2.c */
size_t			ft_count(int n);
char			*ft_strdup(const char *s);
char			*ft_itoa(int n);
void			ft_usleep(
					long long duration,
					t_philosopher *philosopher
					);

/* philo_utils.c */
long long		timer(void);
void			print_lock(
					t_philosopher *philosopher,
					char *str,
					char *color
					);
void			print_death(t_philosopher *philosopher);
t_philosopher	*table_last(t_philosopher *philosopher);
void			table_add_back(
					t_philosopher **table,
					t_philosopher *new_philosopher
					);

/* checks.c */
bool			is_dead(t_philosopher *philosopher);
long long		get_last_meal_time(t_philosopher *philosopher);
bool			is_all_finished(t_philosopher *philosopher);
bool			is_all_ready(t_philosopher *philosopher);
bool			has_started(t_philosopher *philosopher);

/* exit.c */
void			clear_philosopher(
					int count,
					t_philosopher *philosopher
					);
void			clear_table(t_philosopher **table);

#endif /* PHILOSOPHERS_H */
