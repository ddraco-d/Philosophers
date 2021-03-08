/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddraco <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 21:56:13 by ddraco            #+#    #+#             */
/*   Updated: 2021/03/08 19:32:28 by ddraco           ###   ########.fr       */
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
		(*ph)[i].meals = 0;
		(*ph)[i].info = info;
		i++;
	}
	return (EXIT_SUCCESS);
}

int		init_sem(t_info *info)
{
	sem_unlink("forks");
	info->forks = sem_open("forks", O_CREAT | O_EXCL, 0644, info->amount);
	sem_unlink("sem");
	info->semaphor = sem_open("sem", O_CREAT | O_EXCL, 0644, 1);
	sem_unlink("print");
	info->print_sem = sem_open("print", O_CREAT | O_EXCL, 0644, 1);
	if (!(info->forks) || !(info->print_sem) || !(info->semaphor))
		return (EXIT_FAILURE);
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
