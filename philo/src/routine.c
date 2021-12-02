/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcrisari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 15:20:02 by mcrisari          #+#    #+#             */
/*   Updated: 2021/12/02 15:20:04 by mcrisari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_controllo_morte(t_philo *thread)
{
	struct timeval	timenow;

	while (thread->shared->ttd && thread->shared->simulation
		&& thread->eaten != thread->shared->ntte && thread->shared->simulation)
	{
		gettimeofday(&timenow, NULL);
		usleep (50);
		pthread_mutex_lock(&thread->shared->dead);
		if (ft_time_elapsed_ms(thread->eat, timenow) > thread->shared->ttd
			&& thread->shared->simulation)
		{
			ft_state(DEAD, thread);
			thread->shared->simulation = 0;
		}
		pthread_mutex_unlock(&thread->shared->dead);
	}
}

void	ft_takefork(t_philo *thread)
{
	if (!thread->pid % 2)
	{
		if (thread->pid == thread->shared->nof - 1)
			pthread_mutex_lock(&thread->shared->forks[0]);
		else
			pthread_mutex_lock(&thread->shared->forks[thread->pid + 1]);
		pthread_mutex_lock(&thread->shared->forks[thread->pid]);
	}
	else
	{
		pthread_mutex_lock(&thread->shared->forks[thread->pid]);
		if (thread->pid == thread->shared->nof - 1)
			pthread_mutex_lock(&thread->shared->forks[0]);
		else
			pthread_mutex_lock(&thread->shared->forks[thread->pid +1]);
	}
}

void	ft_releasefork(t_philo *thread)
{
	if (thread->pid == thread->shared->nof - 1)
	{
		pthread_mutex_unlock(&thread->shared->forks[0]);
		pthread_mutex_unlock(&thread->shared->forks[thread->pid]);
	}
	else
	{
		pthread_mutex_unlock(&thread->shared->forks[thread->pid + 1]);
		pthread_mutex_unlock(&thread->shared->forks[thread->pid]);
	}
}

void	ft_routine(t_philo *thread)
{
	gettimeofday(&thread->eat, NULL);
	pthread_create(&thread->death, NULL, (void *)ft_controllo_morte, thread);
	while (thread->shared->simulation == 1
		&& thread->eaten != thread->shared->ntte && thread->shared->simulation)
	{
		ft_takefork(thread);
		ft_state(FORK, thread);
		ft_state(EAT, thread);
		thread->eaten++;
		gettimeofday(&thread->eat, NULL);
		ft_timer_ms(thread, thread->shared->tte);
		ft_releasefork(thread);
		if (thread->eaten == thread->shared->ntte)
			break ;
		ft_state(SLEEP, thread);
		ft_timer_ms(thread, thread->shared->tts);
		ft_state(THINK, thread);
	}
	pthread_join(thread->death, NULL);
}
