/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddraco <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 20:06:28 by ddraco            #+#    #+#             */
/*   Updated: 2021/03/10 10:59:10 by ddraco           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int			clear_mem(t_ph **ph, int status)
{
	sem_unlink("forks");
	sem_unlink("sem");
	sem_unlink("print");
	sem_unlink("print_dead");
	if (*ph)
		free(*ph);
	if (status == EXIT_FAILURE)
		return (ft_putstr_fd("error: failure\n", 2));
	exit(EXIT_SUCCESS);
}

int			res(t_ph **ph, t_info *info)
{
	int		i;
	int		status;

	i = 0;
	while (i < info->amount)
	{
		if (wait(&status) == -1)
			return (EXIT_FAILURE);
		if (WIFEXITED(status))
		{
			if (WEXITSTATUS(status) == DEAD)
				ph_kill(ph);
			else if (WEXITSTATUS(status) == EXIT_FAILURE)
			{
				ph_kill(ph);
				return (EXIT_FAILURE);
			}
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

int			main(int argc, char **argv)
{
	t_info	info;
	t_ph	*ph;

	if (argc != 5 && argc != 6)
		return (ft_putstr_fd("error: bad arguments\n", 2));
	if (init_args(&info, argc, argv))
		return (ft_putstr_fd("error: bad arguments\n", 2));
	if (init_sem(&info) || ph_init(&info, &ph))
		return (clear_mem(&ph, EXIT_FAILURE));
	if (threads_start(&ph))
		return (clear_mem(&ph, EXIT_FAILURE));
	if (res(&ph, &info) == EXIT_FAILURE)
		return (clear_mem(&ph, EXIT_FAILURE));
	return (clear_mem(&ph, EXIT_SUCCESS));
}
