/*
** getion_timer.c for timer in /u/all/iniong_a/cu/rendu/c/zappy/src_server
** 
** Made by aime-bijou iniongo
** Login   <iniong_a@epitech.net>
** 
** Started on  Sat May 29 22:35:24 2010 aime-bijou iniongo
** Last update Mon Jun  7 11:10:08 2010 aime-bijou iniongo
*/

#include <sys/time.h>
#include <string.h>
#include "../includes/server.h"

void			add_elem(t_timev **player, char *action, int id, int ti)
{
  t_timev		*new;
  struct timezone	t;
  struct timeval	tv;

  new = xmalloc(sizeof(new));
  new->action = xmalloc(sizeof(new->action) * my_strlen(action));
  strcpy(new->action, action);
  new->d = 1;
  if (my_strcmp(action, "incantation") == 0)
    new->time = 300 * 1000000 / ti;
  else if (my_strcmp(action, "inventaire") == 0)
    new->time = 1 * 1000000 / ti;
  else
    new->time = 7 * 1000000 / ti;
  gettimeofday(&tv, &t);
  new->t_new = tv.tv_sec + tv.tv_usec;
  new->t_old = 0;
  new->id = id;
  new->next = *player;
  *player = new;
}

void	get_small_time(t_timev *t, t_timev *id)
{
  int	i;
  int	x;

  i = -1;
  t->time = 100000000;
  while (i++ < MAX_FD)
    if (id[i].time != 10000000)
      {
	printf("i = %d", i);
/* 	printf("i = %d action = %s\n", i, id[i].action); */
	t->time = MIN_NB(id[i].time, t->time);
	t->id = id[i].id;
	t->t_new = id[i].t_new;
	t->d = 0;
      }
}

t_timev		take_first_action(t_timev **time, t_timev *id)
{
  int		x;
  t_timev	t;

  x = -1;
  while (x++ < MAX_FD)
    {
      id[x].t_new = 0;
      id[x].time = 10000000;
    }
  while (*time)
    {
      x = (*time)->id;
      if (id[x].action == NULL)
	id[x].action = xmalloc(sizeof(id[x].action) * my_strlen((*time)->action));
      else
	{
	  free(id[x].action);
	  id[x].action = xmalloc(sizeof(id[x].action) * my_strlen((*time)->action));
	}
      strcpy(id[x].action, (*time)->action);
      id[x].time = (*time)->time;
      id[x].id = x;
      id[x].t_new = MIN_NB(id[x].t_new, (*time)->t_new);
      *time = (*time)->next;
    }
  get_small_time(&t, id);
  return (t);
}

void		manage_time_in_select(t_timev t, struct timeval *tv)
{
  tv->tv_sec = t.time / 1000000;
  tv->tv_usec = t.time % 1000000;
}

void		update_time_struct(t_timev t, t_timev **time, int new_t)
{
  while (*time)
    {
      if (my_strcmp(t.action, (*time)->action) == 0
	  && t.t_new == (*time)->t_new)
	{
	  (*time)->d = 0;
	  (*time)->t_new = new_t;
	}
      *time = (*time)->next;
    }
}

t_timev		manage_time(t_timev *time)
{
  t_timev	t;
  t_timev	id[MAX_FD];
  int		i;

  if (time == NULL)
    {
      t.time = 0;
      t.t_new = 0;
    }
  else
    {
      i = -1;
      t = take_first_action(&time, id);
      printf("time 1 = %d\n", t.time);
    }
  return (t);
}
