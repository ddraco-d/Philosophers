/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddraco <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 12:58:40 by ddraco            #+#    #+#             */
/*   Updated: 2021/03/08 12:08:04 by aleksandrkomarov ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat_and_sleep(t_ph *ph)
{
	if (ph->info->dead || (ph->info->nbr_each_eat &&\
		ph->meals == ph->info->nbr_each_eat))
		return ;
	pthread_mutex_lock(ph->l_fork);
	messages(ph, FORK_TAKEN);
	pthread_mutex_lock(ph->r_fork);
	messages(ph, FORK_TAKEN);
	pthread_mutex_lock(&ph->info->mutex);
	ph->lst_meal = cur_time() + ph->info->time_to_die;
	messages(ph, EATING);
	pthread_mutex_unlock(&ph->info->mutex);
	ph->meals += 1;
	better_usleep(ph->info->time_to_eat);
	pthread_mutex_unlock(ph->l_fork);
	pthread_mutex_unlock(ph->r_fork);
	messages(ph, SLEEPING);
	better_usleep(ph->info->time_to_sleep);
}
