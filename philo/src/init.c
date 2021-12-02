/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcrisari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 15:19:44 by mcrisari          #+#    #+#             */
/*   Updated: 2021/12/02 15:19:47 by mcrisari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_check_args(int argc, char **argv)
{
	int	i;
	int	j;

	if (argc < 5 || argc > 6)
	{
		printf("Error : wrong amount of parameters\n");
		return (0);
	}
	i = 1;
	while (i < argc)
	{
		j = 0;
		while (argv[i][j])
		{
			if (!ft_isdigit(argv[i][j]))
			{
				printf("ERROR : invalid parameter\n");
				return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

int	ft_init(t_shared *shared, int argc, char **argv)
{
	if (!ft_check_args(argc, argv))
		return (0);
	shared->nof = atoi(argv[1]);
	if (shared->nof <= 0)
	{
		printf("Error : wrong amount of philosophers\n");
		return (0);
	}
	shared->ttd = atoi(argv[2]);
	shared->tte = atoi(argv[3]);
	shared->tts = atoi(argv[4]);
	shared->simulation = 1;
	if (argc == 6)
		shared->ntte = atoi(argv[5]);
	else
		shared->ntte = -1;
	shared->forks = malloc(sizeof(*shared->forks) * shared->nof);
	return (1);
}

int	ft_init_thread(t_philo *thread,	t_shared *shared)
{
	int	i;

	i = 0;
	while (i < shared->nof)
	{
		thread[i].pid = i;
		thread[i].eaten = 0;
		thread[i].need_eat = 0;
		thread[i].shared = shared;
		pthread_mutex_init(&shared->forks[i], NULL);
		i++;
	}
	pthread_mutex_init(&shared->mutex_stamp, NULL);
	pthread_mutex_init(&shared->dead, NULL);
	return (1);
}
