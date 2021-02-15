# include "philo.h"

int init_args(t_info *info, int argc, char **argv)
{
	if (ft_atoi_s(argv[1], (size_t *) &info->amount) != 0 ||\
		ft_atoi_s(argv[2], &info->time_to_die) != 0 ||\
			ft_atoi_s(argv[3], &info->time_to_eat) != 0 ||\
				ft_atoi_s(argv[4], &info->time_to_sleep) != 0)
		return (BAD_ARGS);
	if (argc == 6 && ft_atoi_s(argv[5], &info->nbr_each_eat) != 0)
		return (BAD_ARGS);
	else if (argc == 5)
		info->nbr_each_eat = 0;
	if (info->amount < 2 || info->nbr_each_eat < 0 ||\
			info->time_to_die < 0 || info->time_to_eat < 0 ||\
				info->time_to_sleep < 0)
		return (BAD_ARGS);
	return (WELL_DONE);

}

