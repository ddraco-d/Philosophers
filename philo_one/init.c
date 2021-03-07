/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddraco <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 21:56:13 by ddraco            #+#    #+#             */
/*   Updated: 2021/03/07 20:15:37 by ddraco           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int		ph_init(t_info *info, t_ph **ph)
{
	int	i;

	if (!(*ph = (t_ph*)malloc(sizeof(t_ph) * info->amount)))
		return (MALLOC_ERROR);
	i = 0;
	while (i < info->amount)
	{
		(*ph)[i].place = i + 1;
		(*ph)[i].amount_of_meals = 0;
		(*ph)[i].l_fork = &info->forks[i];
		(*ph)[i].r_fork = &info->forks[(i + 1) % info->amount];
		(*ph)[i].info = info;
		i++;
	}
	return (EXIT_SUCCESS);
}

int		init_mtxs(t_info *info)
{
	int	i;

	i = 0;
	if (pthread_mutex_init(&info->mutex_print, NULL) ||
		pthread_mutex_init(&info->mutex, NULL))
		return (MUTEX_ERROR);
	if (!(info->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)\
			* info->amount)))
		return (MALLOC_ERROR);
	while (i < info->amount)
	{
		if (pthread_mutex_init(&info->forks[i], NULL))
			return (MUTEX_ERROR);
		i++;
	}
	return (EXIT_SUCCESS);
}

int		init_args(t_info *info, int argc, char **argv)
{
	if (ft_atoi_s(argv[1], (uint64_t *)&info->amount) != 0 ||\
		ft_atoi_s(argv[2], &info->time_to_die) != 0 ||\
			ft_atoi_s(argv[3], &info->time_to_eat) != 0 ||\
				ft_atoi_s(argv[4], &info->time_to_sleep) != 0)
		return (BAD_ARGS);
	if (argc == 6 && ft_atoi_s(argv[5], (uint64_t *)&info->nbr_each_eat) != 0)
		return (BAD_ARGS);
	else if (argc == 5)
		info->nbr_each_eat = 0;
	if (info->amount < 2 || info->amount > 200 || info->nbr_each_eat < 0 ||\
			info->time_to_die < 60 || info->time_to_eat < 60 ||\
				info->time_to_sleep < 60)
		return (BAD_ARGS);
	info->dead = 0;
	return (EXIT_SUCCESS);
}
