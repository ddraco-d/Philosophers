

#ifndef PHILO_H
# define PHILO_H
# define BAD_ARGS 1
# define WELL_DONE 0
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>

typedef struct s_info
{
	int			amount;
	size_t		time_to_die;
	size_t		time_to_eat;
	size_t		time_to_sleep;
	size_t		nbr_each_eat;
}				t_info;

int		ft_atoi_s(char *str, size_t *res);
void	ft_putchar_fd(char c, int fd);
void	ft_putnbr_fd(int n, int fd);
size_t	ft_strlen(const char *s);
int		ft_putstr_fd(char *s, int fd);
int		init_args(t_info *info, int argc, char **argv);

#endif
