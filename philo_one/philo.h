

#ifndef PHILO_H
# define PHILO_H
# define BAD_ARGS 2
# define MALLOC_ERROR 3
# define MUTEX_ERROR 4
# define TIME_ERROR 5
# define PTHREAD_ERROR 6
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct		s_info
{
	int				amount;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			nbr_each_eat;
	pthread_mutex_t	mutex_print;
	pthread_mutex_t	*forks;
	pthread_mutex_t	mutex;
	uint64_t		start;
	int				dead;
}					t_info;

typedef struct		s_ph
{
	pthread_t		thread;
	pthread_t		status_thread;

	pthread_mutex_t	l_fork;
	pthread_mutex_t	r_fork;
	int				place;
	int				amount_of_meals;
	size_t			lst_meal;
	t_info			*info;

//	int 			is_eating; ?

}					t_ph;


int		ft_atoi_s(char *str, size_t *res);
void	ft_putchar_fd(char c, int fd);
void	ft_putnbr_fd(int n, int fd);
size_t	ft_strlen(const char *s);
int		ft_putstr_fd(char *s, int fd);
int		init_args(t_info *info, int argc, char **argv);
size_t	cur_time(void);
int		ph_init(t_info *info, t_ph **ph);
int		threads_start(t_ph **ph);
void	better_usleep(uint64_t msec);
#endif
