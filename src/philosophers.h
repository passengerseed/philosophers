/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrouchon <lrouchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/10 15:55:17 by lrouchon          #+#    #+#             */
/*   Updated: 2026/08/09 18:38:38 by lrouchon         ###   ########.fr       */
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

typedef enum state {
	INIT,		//0
	EATING,		//1
	SLEEPING,	//2
	THINKING,	//3
	DEAD		//4
}	State;

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
	t_times					*times;
	State					state;
	long long				last_meal_time;
	pthread_mutex_t			last_meal_mutex;
	bool					finished;
	struct s_fork			*fork;
	struct s_philosopher	*previous;
	struct s_philosopher	*next;
}	t_philosopher;

typedef struct s_fork {
	struct s_philosopher	*philosopher;
	pthread_mutex_t			mutex;
}	t_fork;



/* main.c */
long long		timer(void);
void			death_clock(t_philosopher *philosopher, int	delay);
void			error(char *str);
void			panopticon(t_philosopher *philosopher, const char **argv);

/* init.c */
t_times			*init_times(int argc, const char **argv);
t_philosopher	*init_philosopher(char *name, t_times *times);
t_philosopher	*init_table(const char **argv, t_times *times);
// void			clear_table(t_philosopher **table);
void			die(t_philosopher *philosopher, long long timestamp);
/* process.c */
int				switch_states(t_philosopher *philosopher, State new_state, long long timestamp);
int				eat(t_philosopher *philosopher, long long timestamp);
int				nap(t_philosopher *philosopher, long long timestamp);
void			die(t_philosopher *philosopher, long long timestamp);
void			*live(void *arg);

/* utils.c */
int				ft_atoi(const char *str);
char			*ft_strdup(const char *s);
char			*ft_strjoin(char const *s1, char const *s2);
// void			print_lock(t_philosopher *philosopher, char *str);

/* lst_utils.c */
void			table_add_back(t_philosopher **table, t_philosopher *new_philosopher);
void			table_add_front(t_philosopher **table, t_philosopher *new_philosopher);
t_philosopher	*table_last(t_philosopher *philosopher);

/* namegen.c */
int				rand(void);
char			*generate_name(int rand);

/* debug.c */
void			print_table(t_philosopher *philosopher);

#endif /* PHILOSOPHERS_H */
