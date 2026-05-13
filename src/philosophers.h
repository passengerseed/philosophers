/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrouchon <lrouchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/10 15:55:17 by lrouchon          #+#    #+#             */
/*   Updated: 2026/05/13 17:01:19 by lrouchon         ###   ########.fr       */
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
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
}	t_times;

typedef struct s_philosopher {
	pthread_t		thread;

	char			*name;
	t_times			*times;
	State			state;
	struct s_fork	*fork;
	struct s_philosopher	*previous;
	struct s_philosopher	*next;
}	t_philosopher;

typedef struct s_fork {
	struct s_philosopher	*philosopher;
}	t_fork;



/* main.c */
int				timer(void);
void			error(char *str);

/* init.c */
t_times			*init_times(const char **argv);
t_philosopher	*init_philosopher(char *name, t_times *times);
t_philosopher	*init_table(const char **argv, t_times *times);
// void			clear_table(t_philosopher **table);
// char			*generate_name(long unsigned *thread_id);

/* process.c */
int				switch_states(t_philosopher *philosopher, State new_state, int timestamp);
void			*live(void *arg);
int				eat(t_philosopher *philosopher);

/* utils.c */
int				ft_atoi(const char *str);

/* lst_utils.c */
void			table_add_back(t_philosopher **table, t_philosopher *new_philosopher);
void			table_add_front(t_philosopher **table, t_philosopher *new_philosopher);

/* debug.c */
void			print_table(t_philosopher *philosopher);

#endif /* PHILOSOPHERS_H */
