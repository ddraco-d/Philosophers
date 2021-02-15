#include "philo.h"
#include <stdio.h>

int main(int argc, char **argv)
{
	t_info info;

	if (argc != 5 && argc != 6)
		return (ft_putstr_fd("error: bad arguments\n", 2));
	// int check = init_args(&info, argc, argv);
	// printf("-%d-\n", check);

	// if (init_args(&info, argc, argv))
		// return();
	
	printf("%d\n%zu\n%zu\n%zu\n", info.amount, info.time_to_die, info.time_to_eat, info.time_to_sleep);
	printf("%zu\n", info.nbr_each_eat);
}
