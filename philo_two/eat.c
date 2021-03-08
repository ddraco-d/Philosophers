/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddraco <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 12:58:40 by ddraco            #+#    #+#             */
/*   Updated: 2021/03/08 19:30:35 by ddraco           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat_and_sleep(t_ph *ph)
{
	if (ph->info->dead || (ph->info->nbr_each_eat &&\
		ph->meals == ph->info->nbr_each_eat))
		return ;
	sem_wait(ph->info->forks);
	messages(ph, FORK_TAKEN);
	sem_wait(ph->info->forks);
	messages(ph, FORK_TAKEN);
	sem_wait(ph->info->semaphor);
	ph->lst_meal = cur_time() + ph->info->time_to_die;
	messages(ph, EATING);
	sem_post(ph->info->semaphor);
	ph->meals += 1;
	better_usleep(ph->info->time_to_eat);
	sem_post(ph->info->forks);
	sem_post(ph->info->forks);
	messages(ph, SLEEPING);
	better_usleep(ph->info->time_to_sleep);
}
