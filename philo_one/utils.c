#include "philo.h"

size_t		ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
		i++;
	return (i);
}

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

int		ft_atoi_s(char *str, size_t *res)
{
	if (*str == '\0')
		return (-1);
	*res = 0;
	while (*str && *str <= '9' && *str >= '0')
	{
		*res = 10 * (*res) + (*str - '0');
		str++;
	}
	if (*str != '\0')
		return (-1);
	return (0);
}

void	ft_putnbr_fd(int n, int fd)
{
	if (n == -2147483648)
	{
		ft_putchar_fd('-', fd);
		ft_putchar_fd('2', fd);
		ft_putnbr_fd(147483648, fd);
	}
	else
	{
		if (n < 0)
		{
			ft_putchar_fd('-', fd);
			ft_putnbr_fd((-1) * n, fd);
		}
		else
		{
			if (n >= 10)
				ft_putnbr_fd(n / 10, fd);
			ft_putchar_fd('0' + n % 10, fd);
		}
	}
}

int		ft_putstr_fd(char *s, int fd)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		ft_putchar_fd(s[i++], fd);
	return (1);
}
