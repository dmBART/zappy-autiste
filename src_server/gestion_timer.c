/*
** getion_timer.c for timer in /u/all/iniong_a/cu/rendu/c/zappy/src_server
** 
** Made by aime-bijou iniongo
** Login   <iniong_a@epitech.net>
** 
** Started on  Sat May 29 22:35:24 2010 aime-bijou iniongo
** Last update Fri Jun 11 03:26:10 2010 aime-bijou iniongo
*/

#include <sys/time.h>
#include <string.h>
#include <stdio.h>
#include "../includes/server.h"

void			time_zero(t_timev *new)
{
  new->d = 0;
  new->t = 0;
  new->cs = 0;
  new->action = NULL;
}

void			add_elem(t_timev **player, char *action, int id, int ti)
{
  t_timev		*new;
  struct timeval	tv;
  struct timezone	ts;
  int			i;

  i = 0;
  new = xmalloc(sizeof(*new));
  new->action = strdup(action);
  new->d = 1;
  new->cs = id;
  gettimeofday(&new->t_new, &ts);
  if (my_strcmp(action, "incantation") == 0)
    new->t = 300 * 1000000 / ti;
  else if (my_strcmp(action, "inventaire") == 0)
    new->t = 1 * 1000000 / ti;
  else
    new->t = 7 * 1000000 / ti;
  new->t_old.tv_sec = (new->t / 1000000) + new->t_new.tv_sec;
  new->t_old.tv_usec = (new->t % 1000000) + new->t_new.tv_usec;
  new->next = *player;
  *player = new;
}

void	del_elem_to_queu(t_timev **time, t_timev t)
{
  void	*save;
  void	*tmp;
  int	cpt;
  int	i;

  i = 0;
  save = *time;
  while (*time)
    {
      if (my_strcmp((*time)->action, t.action) == 0 &&
	  (*time)->t_new.tv_sec == t.t_new.tv_sec &&
	  (*time)->t_new.tv_usec == t.t_new.tv_usec)
	{
	  printf("in del struct timer and action = %s \n", (*time)->action);
	  cpt = i;
	  break;
	}
      *time = (*time)->next;
      i++;
    }
  if (cpt == 0)
    {
      free((*time)->action);
      *time = (*time)->next;
    }
  else
    {
      *time = save;
      i = 0;
      while (i < (cpt - 1))
	{
	  *time = (*time)->next;
	  i++;
	}
      free((*time)->action);
      (*time)->next = (*time)->next->next;
      *time = save;
    }
  t.t = 0;
}

void	get_small_time(t_timev *t, t_timev *id)
{
  int	i;

  i = -1;
  t->t = 600000000;
  while (i++ < MAX_IN)
    if (id[i].t != 60000000)
      {
	t->t = MIN_NB(id[i].t, t->t);
	t->cs = id[i].cs;
	t->t_new = id[i].t_new;
	t->t_old = id[i].t_old;
	t->d = 1;
      }
  if (t->action == NULL)
    t->action = xmalloc(sizeof(t->action) * my_strlen(id[t->cs].action));
  else
    {
      free(t->action);
      t->action = xmalloc(sizeof(t->action) * my_strlen(id[t->cs].action));
    }
  strcpy(t->action, id[t->cs].action);
  t->d = 1;
}

t_timev		take_first_action(t_timev *time, t_timev *id)
{
   int		x;
  void		*save;
  t_timev	t;

  get_small_time(&t, id);
  return (t);
}

void	exec_action(t_timev *id, t_timev *time)
{
  int	x;

  while (time)
    {
      x = time->cs;
      if (id[x].t_new.tv_sec == time->t_new.tv_sec
	  && id[x].t_new.tv_usec == time->t_new.tv_usec)
	{
	  id[x].t = time->t;
	  id[x].t_old = time->t_old;
	  id[x].action = xmalloc(sizeof(char *) * my_strlen(time->action));
	  strcpy(id[x].action, time->action);
	}
      time = time->next;
    }
}

void	get_time_exec_2(t_timev *id, t_timev *time)
{
  int	x;

  while (time)
    {
      x = time->cs;
      if (id[x].t_new.tv_sec == time->t_new.tv_sec)
	{
	  id[x].t_new.tv_usec = MIN_NB(id[x].t_new.tv_usec, time->t_new.tv_usec);
	}
      time = time->next;
    }
}

void	get_time_exec(t_timev *id, t_timev *time)
{
  int	x;

  x = -1;
  while (x++ < MAX_IN)
    {
      id[x].t = 60000000;
      id[x].t_new.tv_sec = 2000000000;
      id[x].t_new.tv_usec = 2000000000;
    }
  while (time)
    {
      x = time->cs;
      id[x].cs = x;
      id[x].t_new.tv_sec = MIN_NB(id[x].t_new.tv_sec, time->t_new.tv_sec);
      time = time->next;
    }
}

void		manage_time_in_select(t_timev t, struct timeval *tv)
{
  tv->tv_sec = t.t / 1000000;
  tv->tv_usec = t.t % 1000000;
}

void		update_time_struct(t_timev *time, t_env *e)
{
  while (time)
    {
      time->t = (time->t_old.tv_sec - e->tv.tv_sec) * 1000000;
      time->t += time->t_old.tv_usec - e->tv.tv_usec;
      if (time->t < 0)
	time->t = 0;
      time = time->next;
    }
}

t_timev		manage_time(t_desc *serv)
{
  t_timev	t;
  t_timev	id[MAX_IN];

  if (serv->tv == NULL)
    {
      t.d = 0;
      t.t = 0;
    }
  else
    {
      get_time_exec(id, serv->tv);
      get_time_exec_2(id, serv->tv);
      exec_action(id, serv->tv);
     t = take_first_action(serv->tv, id);
    }
  return (t);
}
