# ifndef HEADER_H
# define HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>

typedef struct s_data_philo
{
	int				philo_id;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				eat_x_times;
	int				ate_x_times;
	int				*already_ate_max;
	long int		last_meal_time;
	long int		*start_time;
	int				stop;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*main_lock;
	pthread_mutex_t	*priv_lock;
	pthread_mutex_t	*message_lock;
}				t_data_philo;

typedef struct s_table
{
	int				num_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				eat_x_times;
	int				already_ate_max; // philos who finished eating
	t_data_philo	*philos;
	long int		start_time;
	pthread_t		*threads;
	pthread_mutex_t	*forks;
	pthread_mutex_t message_lock;
	pthread_mutex_t	main_lock;
	pthread_mutex_t	*priv_lock;
}				t_data;

void ft_exit(char *str);
int	ft_atoi(const char *str);
int	ft_isalpha(int c);
int	ft_isdigit(char *c);
int	check_range(char *str);
int	get_time_now(void);
void	print_info(t_data_philo *philo, char *action);
int alive_check(t_data_philo *philo);


int	parse_args(t_data *data, int argc, char **argv);
int	init_data(t_data *data);
void	*routine(void *arg);
void	check_philos(t_data *data, t_data_philo *philo);
void	free_mutex(t_data *data);
void	free_all(t_data *data);


#endif
