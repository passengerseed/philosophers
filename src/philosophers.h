/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrouchon <lrouchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/10 15:55:17 by lrouchon          #+#    #+#             */
/*   Updated: 2026/08/17 16:46:22 by lrouchon         ###   ########.fr       */
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

typedef enum state {
	INIT,		//0
	EATING,		//1
	SLEEPING,	//2
	THINKING,	//3
	DEAD		//4
}	State;

typedef struct s_sync {
	pthread_mutex_t	sync_mutex;
	bool			even_phase_ready;
	bool			odd_phase_ready;
	int				even_ready_count;
	int				odd_ready_count;
	int				even_total;
	int				odd_total;
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
	State					state;
	pthread_mutex_t			state_mutex;
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
void			error(char *str);
void			panopticon(t_philosopher *philosopher, const char **argv);

/* init.c */
t_sync			*init_sync(t_times *times);
t_times			*init_times(int argc, const char **argv);
t_philosopher	*init_philosopher(t_times *times, t_sync *sync, int index);
t_philosopher	*init_table(const char **argv, t_times *times);
void			table_add_back(t_philosopher **table, t_philosopher *new_philosopher);
t_philosopher	*table_last(t_philosopher *philosopher);
// void			clear_table(t_philosopher **table);

/* process.c */
void			*lifecycle(void	*arg);

/* utils.c */
size_t			ft_strlen(const char *str);
int				ft_atoi(const char *str);
int				ft_rand(void);

/* namegen.c */
size_t			ft_count(int n);
char			*ft_itoa(int n);
char			*ft_strdup(const char *s);
char			*ft_strjoin(char const *s1, char const *s2);
char			*generate_name(int rand);

/* debug.c */
void			print_table(t_philosopher *philosopher);

#endif /* PHILOSOPHERS_H */
