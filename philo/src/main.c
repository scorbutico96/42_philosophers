/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcrisari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 15:19:54 by mcrisari          #+#    #+#             */
/*   Updated: 2021/12/02 15:19:55 by mcrisari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_life(t_philo *thread, t_shared *shared)
{
	int	i;

	i = 0;
	if (thread->shared->nof == 1)
	{
		gettimeofday(&thread->shared->time, NULL);
		ft_state(FORK, thread);
		ft_timer_ms(thread, thread->shared->ttd);
		ft_state(DEAD, thread);
	}
	else
	{
		gettimeofday(&thread->shared->time, NULL);
		while (i < shared->nof)
		{
			usleep(10);
			pthread_create(&thread[i].philo, NULL,
				(void *)ft_routine, &thread[i]);
			i++;
		}
	}
}

void	ft_afterlife(t_philo *thread, t_shared *shared)
{
	int	i;

	i = 0;
	while (i < shared->nof)
	{
		if (thread->shared->nof == 1)
		{
			pthread_join(thread[i].death, NULL);
			pthread_detach(thread[i].philo);
		}
		pthread_join(thread[i].philo, NULL);
		i++;
	}
	free(thread);
	free(thread->shared->forks);
}

int	main(int argc, char **argv)
{
	t_philo		*thread;
	t_shared	shared;

	thread = NULL;
	if (!ft_init(&shared, argc, argv))
		return (0);
	thread = malloc(sizeof(*thread) * shared.nof);
	if (!ft_init_thread(thread, &shared))
		return (0);
	ft_life(thread, &shared);
	ft_afterlife(thread, &shared);
}
