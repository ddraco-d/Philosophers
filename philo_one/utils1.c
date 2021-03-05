# include "philo.h"

size_t cur_time(void)
{
	size_t					rez;
	static struct timeval	time;
	if (gettimeofday(&time, NULL))
		return (TIME_ERROR);
	return ((time.tv_sec * (uint64_t)1000) + (time.tv_usec / 1000));
}

void better_usleep(uint64_t msec)
{
	uint64_t	start;
	start = cur_time();
	while (cur_time() - start < msec)
		usleep(500);	
}