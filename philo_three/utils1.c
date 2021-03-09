/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddraco <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 21:56:30 by ddraco            #+#    #+#             */
/*   Updated: 2021/03/09 23:41:57 by ddraco           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

uint64_t					cur_time(void)
{
	uint64_t				to_return;
	static struct timeval	time;

	if (gettimeofday(&time, NULL))
		return (TIME_ERROR);
	to_return = time.tv_sec * 1000 + time.tv_usec / 1000;
	return (to_return);
}

void						better_usleep(uint64_t msec)
{
	uint64_t				start;

	start = cur_time();
	while (cur_time() - start < msec)
		usleep(500);
}

static char					*get_message(int msg_type)
{
	if (msg_type == EATING)
		return ("is eating\n");
	else if (msg_type == SLEEPING)
		return ("is sleeping\n");
	else if (msg_type == FORK_TAKEN)
		return ("has taken a fork\n");
	else if (msg_type == THINKING)
		return ("is thinking\n");
	return ("died\n");
}

void						messages(t_ph *ph, int msg_type)
{
	sem_wait(ph->info->print_sem);
	printf("%d %d %s", (int)(cur_time() - ph->info->start),\
		ph->place, get_message(msg_type));
	sem_post(ph->info->print_sem);
}

void						ph_kill(t_ph **ph)
{
	int	j;

	j = 0;
	while (j < (*ph)->info->amount)
	{
		kill((*ph + j)->pid, SIGKILL);
		j++;
	}
}
