/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddraco <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 12:58:40 by ddraco            #+#    #+#             */
/*   Updated: 2021/03/07 18:53:24 by aleksandrkomarov ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void		eat_and_sleep(t_ph *ph)
{
	uint64_t  c_time;
	if (ph->info->dead || (ph->info->nbr_each_eat &&\
		ph->amount_of_meals == ph->info->nbr_each_eat))
		return ;
	pthread_mutex_lock(ph->l_fork);
	messages(ph, FORK_TAKEN);
	pthread_mutex_lock(ph->r_fork);
	messages(ph, FORK_TAKEN);

	c_time = cur_time();
	pthread_mutex_lock(&ph->info->mutex);

	ph->lst_meal = c_time + ph->info->time_to_die;
	messages(ph, EATING);
	pthread_mutex_unlock(&ph->info->mutex);
	ph->amount_of_meals += 1;
	better_usleep(ph->info->time_to_eat);
//	ft_putstr_fd("printf is shit", STDOUT_FILENO);

	pthread_mutex_unlock(ph->l_fork);
	pthread_mutex_unlock(ph->r_fork);

	messages(ph, SLEEPING);
	better_usleep(ph->info->time_to_sleep);
}