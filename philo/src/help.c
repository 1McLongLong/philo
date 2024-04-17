#include "header.h"

void	print_info(t_data_philo *philo, char *str)
{
	long int	time;

	pthread_mutex_lock(philo->message_lock);
	time = get_time_now() - *philo->start_time;
	if (time >= 0 && time <= 2147483647 && alive_check(philo))
		printf("%d %d %s\n", (int)time, philo->philo_id, str);
	pthread_mutex_unlock(philo -> message_lock);
}

int	get_time_now(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

int	ft_isdigit(char *c)
{
	while (c && *c)
	{
		if (*c < '0' || *c > '9')
			return (1);
		c++;
	}
	return (0);
}

int	check_range(char *str)
{
	int		i;
	int		result;

	i = 0;
	result = 0;
	while (str[i] != '\0')
	{
		if (result > 2147483647)
			return (1);
		result = result * 10 + str[i] - '0';
		i++;
	}
	return (0);
}

static int	ft_handle(char *s, int sign)
{
	long int	nbr;
	long int	nb;

	nb = 0;
	nbr = 0;
	while (*s >= '0' && *s <= '9')
	{
		nb = nbr * 10 + (*s - '0');
		if (nb < nbr && sign == 1)
			return (-1);
		else if (nb < nbr && sign == -1)
			return (0);
		nbr = nb;
		s++;
	}
	return ((int) nbr * sign);
}

int	ft_atoi(const char *str)
{
	char	*s;
	int		sign;

	sign = 1;
	s = (char *) str;
	while (*s == ' ' || *s == '\n' || *s == '\v' || *s == '\f'
		|| *s == '\t' || *s == '\r')
		s++;
	if (*s == '+')
		s++;
	else if (*s == '-')
	{
		sign = -1;
		s++;
	}
	return (ft_handle(s, sign));
}
