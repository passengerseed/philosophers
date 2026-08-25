/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrouchon <lrouchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/10 15:55:17 by lrouchon          #+#    #+#             */
/*   Updated: 2026/08/25 15:40:29 by lrouchon         ###   ########.fr       */
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

typedef struct s_sync {
	pthread_mutex_t	sync_mutex;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	state_mutex;
	bool			dead;
	int				ready_count;
}	t_sync;

typedef struct s_times {
	int				philosopher_amount;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				times_eating;
}	t_times;

typedef struct s_philosopher {
	pthread_t				thread;
	char					*name;
	int						index;
	t_times					*times;
	t_sync					*sync;
	long long				last_meal_time;
	pthread_mutex_t			last_meal_mutex;
	bool					ready_to_eat;
	bool					finished;
	struct s_fork			*fork;
	struct s_philosopher	*previous;
	struct s_philosopher	*next;
}	t_philosopher;

typedef struct s_fork {
	pthread_mutex_t			mutex;
}	t_fork;

/* main.c */
long long		timer(void);
void			*monitor(void *arg);
int				monitor_loop(t_philosopher *philosopher);

/* init.c */
t_sync			*init_sync(void);
t_times			*init_times(int argc, const char **argv);
t_philosopher	*init_philosopher(t_times *times, t_sync *sync, int index);
t_philosopher	*init_table(const char **argv, t_times *times);
void			table_add_back(t_philosopher **table,
					t_philosopher *new_philosopher);
t_philosopher	*table_last(t_philosopher *philosopher);
void			clear_table(t_philosopher **table, int i);

/* process.c */
void			*lifecycle(void	*arg);
int				take_forks_and_eat(t_philosopher *philosopher);
int				nap(t_philosopher *philosopher);
bool			is_dead(t_philosopher *philosopher);

/* utils.c */
size_t			ft_strlen(const char *str);
int				ft_atoi(const char *str);
size_t			ft_count(int n);
char			*ft_strdup(const char *s);
char			*ft_itoa(int n);
void			print_lock(t_philosopher *philosopher, char *str);
void			ft_usleep(long long duration);

/* debug.c */
void			print_table(t_philosopher *philosopher);

#endif /* PHILOSOPHERS_H */
