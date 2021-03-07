/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddraco <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 21:56:30 by ddraco            #+#    #+#             */
/*   Updated: 2021/03/07 18:17:43 by aleksandrkomarov ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"

uint64_t cur_time(void)
{
	uint64_t 				to_return;
	static struct timeval	time;
	if (gettimeofday(&time, NULL))
		return (TIME_ERROR);
	to_return = time.tv_sec * 1000 + time.tv_usec / 1000;
	return (to_return);
}

void better_usleep(uint64_t msec)
{
	uint64_t	start;
	start = cur_time();
	while (cur_time() - start < msec)
		usleep(500);	
}

static char *get_message(int msg_type)
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

int messages(t_ph *ph, int msg_type)
{
	if (ph->info->dead || (ph->info->nbr_each_eat &&\
		ph->amount_of_meals == ph->info->nbr_each_eat))
		return (EXIT_FAILURE);
	pthread_mutex_lock(&ph->info->mutex_print);
	// ft_putnbr_fd((int)(cur_time() - ph->info->start), 1);
	// ft_putchar_fd(' ', 1);
	// ft_putnbr_fd();
//	 ft_putstr_fd("printf is shit", STDOUT_FILENO);
	printf("%d %d %s", (int)(cur_time() - ph->info->start),\
		ph->place, get_message(msg_type));
	pthread_mutex_unlock(&ph->info->mutex_print);
	return (EXIT_SUCCESS);
}