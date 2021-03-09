/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_begin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddraco <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 13:48:20 by ddraco            #+#    #+#             */
/*   Updated: 2021/03/09 23:45:32 by ddraco           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*monitor(void *v_ph)
{
	t_ph	*ph;
	t_info	*info;

	ph = (t_ph *)v_ph;
	info = ph->info;
	pthread_detach(ph->status_thread);
	while (info->nbr_each_eat == 0 || info->nbr_each_eat != ph->meals)
	{
		sem_wait(info->semaphor);
		sem_wait(info->print_dead_sem);
		if (cur_time() > ph->lst_meal)
		{
			messages(ph, DEAD);
			info->dead = 1;
			sem_post(info->semaphor);
			exit(DEAD);
		}
		sem_post(info->print_dead_sem);
		sem_post(info->semaphor);
		usleep(1000);
	}
	return (NULL);
}

void	do_work(t_ph *ph)
{
	uint64_t	c_time;
	t_info		*info;

	info = ph->info;
	if ((c_time = cur_time()) == 1)
		exit(EXIT_FAILURE);
	ph->lst_meal = c_time + ph->info->time_to_die;
	if (pthread_create(&ph->status_thread, NULL, &monitor, (void *)ph))
		exit(EXIT_FAILURE);
	if (ph->place % 2 == 0)
		better_usleep(info->time_to_eat);
	while (ph->info->dead == 0)
	{
		if (ph->info->nbr_each_eat == 0 || ph->info->nbr_each_eat != ph->meals)
		{
			eat_and_sleep(ph);
			messages(ph, THINKING);
		}
		else
			break ;
	}
	exit(EXIT_SUCCESS);
}

int		threads_start(t_ph **ph)
{
	int	i;

	i = 0;
	if (((*ph)->info->start = cur_time()) == 1)
		return (EXIT_FAILURE);
	while (i < (*ph)->info->amount)
	{
		if (((*ph + i)->pid = fork()) < 0)
		{
			ph_kill(ph);
			return (EXIT_FAILURE);
		}
		else if ((*ph + i)->pid == 0)
			do_work(*ph + i);
		i++;
	}
	return (EXIT_SUCCESS);
}
