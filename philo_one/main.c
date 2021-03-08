/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddraco <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 20:06:28 by ddraco            #+#    #+#             */
/*   Updated: 2021/03/08 12:08:04 by aleksandrkomarov ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int			clear_mem(t_ph **ph, int status)
{
	int		i;

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
	if (status == EXIT_FAILURE)
		return (ft_putstr_fd("error: failure\n", 2));
	return (status);
}

int			main(int argc, char **argv)
{
	t_info	info;
	t_ph	*ph;
	int		i;

	i = 0;
	if (argc != 5 && argc != 6)
		return (ft_putstr_fd("error: bad arguments\n", 2));
	if (init_args(&info, argc, argv))
		return (ft_putstr_fd("error: bad arguments\n", 2));
	if (init_mtxs(&info) || ph_init(&info, &ph))
		return (clear_mem(&ph, EXIT_FAILURE));
	if (threads_start(&ph))
		return (clear_mem(&ph, EXIT_FAILURE));
	while (i < info.amount)
	{
		pthread_join((ph + i)->thread, NULL);
		i++;
	}
	return (clear_mem(&ph, EXIT_SUCCESS));
}
