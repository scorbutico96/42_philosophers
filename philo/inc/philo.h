/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcrisari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 15:20:38 by mcrisari          #+#    #+#             */
/*   Updated: 2021/12/02 15:20:40 by mcrisari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

enum e_state {
	DEAD,
	FORK,
	EAT,
	SLEEP,
	THINK,
};

static const char *const	g_status_str[] = {
	"\e[31mis DEAD\e[0m",
	"has taken a fork",
	"\e[32mis eating\e[0m",
	"\e[35mis sleeping\e[0m",
	"\e[34mis thinking\e[0m",
};

typedef struct s_shared
{
	int				ttd;
	int				tts;
	int				tte;
	int				ntte;
	int				nof;
	int				simulation;
	struct timeval	time;
	pthread_mutex_t	mutex_stamp;
	pthread_mutex_t	*forks;
	pthread_mutex_t	dead;
}	t_shared;

typedef struct s_philo
{
	int				eaten;
	int				pid;
	int				need_eat;
	pthread_t		philo;
	pthread_t		death;
	t_shared		*shared;
	struct timeval	eat;
}	t_philo;

void		ft_gc(t_philo *thread);
int			ft_init(t_shared *shared, int argc, char **argv);
int			ft_init_thread(t_philo *thread, t_shared *shared);
void		ft_life(t_philo *thread, t_shared *shared);

void		ft_takefork(t_philo *thread);
void		ft_routine(t_philo *thread);
void		ft_controllo_morte(t_philo *thread);
void		ft_afterlife(t_philo *thread, t_shared *shared);

void		ft_timer_ms(t_philo *thread, long int delay);
int			ft_time_elapsed_ms(struct timeval t0, struct timeval t1);
void		ft_state(int state, t_philo *philo);

int			ft_isdigit(int c);
int			ft_atoi(const char *str);
int			ft_strncmp(char *s1, char *s2, int n);

#endif
