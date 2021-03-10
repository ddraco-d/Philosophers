/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddraco <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 20:06:28 by ddraco            #+#    #+#             */
/*   Updated: 2021/03/10 11:00:41 by ddraco           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int			clear_mem(t_ph **ph, int status)
{
	sem_unlink("forks");
	sem_unlink("sem");
	sem_unlink("print");
	if (*ph)
		free(*ph);
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
	if (init_sem(&info) || ph_init(&info, &ph))
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
