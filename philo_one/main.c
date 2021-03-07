#include "philo.h"

void clear_mem(t_ph **ph)
{
	int i;

	pthread_mutex_destroy(&(*ph)->info->mutex);
	pthread_mutex_destroy(&(*ph)->info->mutex_print);
	if (*ph)
	{
		if ((*ph)->info->forks)
		{
			i = 0;
			while (i < (*ph)->info->amount)
			{
				pthread_mutex_destroy(&(*ph)->info->forks[i]);
				i++;
			}
			free((*ph)->info->forks);
		}
		free(*ph);
	}
}


int main(int argc, char **argv)
{
	t_info	info;
	t_ph	*ph;

	if (argc != 5 && argc != 6)
		return (ft_putstr_fd("error: bad arguments\n", 2));
	init_args(&info, argc, argv);
	ph_init(&info, &ph);
	threads_start(&ph);
	rez(&ph, &info);
	clear_mem(&ph);
	// printf("-%d-\n", check);

	// if (init_args(&info, argc, argv))
		// return();
	
//	printf("%d\n%zu\n%zu\n%zu\n", info.amount, info.time_to_die, info.time_to_eat, info.time_to_sleep);
//	printf("%zu\n", info.nbr_each_eat);
}
