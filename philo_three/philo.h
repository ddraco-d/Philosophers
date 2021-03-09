/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddraco <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 21:56:22 by ddraco            #+#    #+#             */
/*   Updated: 2021/03/09 23:16:46 by ddraco           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# define BAD_ARGS 2
# define MALLOC_ERROR 3
# define MUTEX_ERROR 4
# define TIME_ERROR 5
# define PTHREAD_ERROR 6

# define THINKING 7
# define SLEEPING 8
# define EATING 9
# define FORK_TAKEN 10
# define DEAD 11
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <semaphore.h>
# include <signal.h>

typedef struct		s_info
{
	int				amount;
	int				nbr_each_eat;
	int				dead;
	uint64_t		time_to_die;
	uint64_t		time_to_eat;
	uint64_t		time_to_sleep;
	uint64_t		start;
	sem_t			*forks;
	sem_t			*print_sem;
	sem_t			*print_dead_sem;
	sem_t			*semaphor;
}					t_info;

typedef struct		s_ph
{
	pid_t			pid;
	pthread_t		status_thread;

	int				place;
	int				meals;
	uint64_t		lst_meal;
	t_info			*info;
}					t_ph;

int					ft_atoi_s(char *str, uint64_t *res);
void				ft_putchar_fd(char c, int fd);
void				ft_putnbr_fd(int n, int fd);
int					ft_putstr_fd(char *s, int fd);
int					init_args(t_info *info, int argc, char **argv);
uint64_t			cur_time(void);
int					ph_init(t_info *info, t_ph **ph);
int					threads_start(t_ph **ph);
void				better_usleep(uint64_t msec);
void				messages(t_ph *ph, int msg_type);
void				eat_and_sleep(t_ph *ph);
int					init_sem(t_info *info);
void				ph_kill(t_ph **ph);
#endif
