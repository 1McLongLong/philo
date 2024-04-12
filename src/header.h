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
	pthread_mutex_t	*write_message;
}				t_data_philo;

typedef struct s_table
{
	int				philos_num;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				eat_x_times;
	int				already_ate_max;
	t_data_philo	*philos;
	pthread_t		*threads;
	pthread_mutex_t	*forks;
	pthread_mutex_t	write_message;
	long int		start_time;
	pthread_mutex_t	main_lock;
	pthread_mutex_t	*priv_lock;
}				t_table;

void ft_exit(char *str);
int	ft_atoi(const char *str);
int	ft_isalpha(int c);
int	ft_isdigit(char *c);
int	check_range(char *str);
long int	get_time_now(void);
void	print_info(t_data_philo *philo, char *action);


int	parse_args(t_table *table, int argc, char **argv);
int	init_data(t_table *table);
void	control(t_table *table, t_data_philo *philo);
int	alive_check(t_data_philo *philo);
void	*philo_routine(void *arg);
void	destroy(t_table *table);
void	free_all(t_table *table);


#endif
