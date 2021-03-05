/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_begin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddraco <ddraco@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 13:48:20 by ddraco            #+#    #+#             */
/*   Updated: 2021/03/05 14:52:37 by ddraco           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"

void *monitor(void *v_ph)
{
	t_ph *ph;
	t_info *info;

	ph = (t_ph *)v_ph;
	info = ph->info;
	pthread_detach(ph->status_thread);
	if (info->nbr_each_eat == 0 || info->nbr_each_eat != ph->amount_of_meals)
		while (1)
		{
			pthread_mutex_lock(&info->mutex);
			if (cur_time() > ph->lst_meal)
			{
				// print_message()
				info->dead = 1;
				pthread_mutex_unlock(&info->mutex);
			}
			break ;
			pthread_mutex_unlock(&info->mutex);
			usleep(1000); //may be 777?
		}
	return ((void *)EXIT_SUCCESS);
}

void *do_work(void *v_ph)
{
	uint64_t	c_time;
	t_ph		*ph;
	t_info		*info;

	ph = (t_ph *)v_ph;
	info = ph->info;
	if ((c_time = cur_time()) == 1)
		return ((void *)EXIT_FAILURE);
	ph->lst_meal = c_time + ph->info->time_to_die;
	if (pthread_create(&ph->status_thread, NULL, &monitor, v_ph))
	{
		return ((void *)EXIT_FAILURE);
	}
	
	return ((void *)EXIT_SUCCESS);
}

int threads_start(t_ph **ph)
{
	int i;

	i = 0;
	if (((*ph)->info->start = cur_time()) == 1)
		return (EXIT_FAILURE);
	i = 0;
	while (i < (*ph)->info->amount)
	{
		if (pthread_create(&(*ph + i)->thread, NULL, &do_work, (void *)(*ph + i)))
			return (PTHREAD_ERROR);
	}
	return (EXIT_SUCCESS);
}

