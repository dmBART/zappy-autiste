/*
** getion_timer.c for timer in /u/all/iniong_a/cu/rendu/c/zappy/src_server
** 
** Made by aime-bijou iniongo
** Login   <iniong_a@epitech.net>
** 
** Started on  Sat May 29 22:35:24 2010 aime-bijou iniongo
** Last update Mon Jun 14 17:25:55 2010 aime-bijou iniongo
*/

#include <sys/time.h>
#include <string.h>
#include <stdio.h>
#include "../includes/server.h"

void	get_small_time(t_timev *t, t_timev *id, int i)
{
  i = -1;
  t->t_old.tv_sec = 2000000000;
  t->t_old.tv_usec = 2000000000;
  while (i++ < MAX_IN)
    if (id[i].t_new.tv_sec != 2000000000)
      t->t_old.tv_sec = MIN_NB(id[i].t_old.tv_sec, t->t_old.tv_sec);
  i = -1;
  while (i++ < MAX_IN)
    if(t->t_old.tv_sec == id[i].t_old.tv_sec)
      t->t_old.tv_usec = MIN_NB(id[i].t_old.tv_usec, t->t_old.tv_usec);
  i = -1;
  while (i++ < MAX_IN)
    if(t->t_old.tv_sec == id[i].t_old.tv_sec &&
       t->t_old.tv_usec == id[i].t_old.tv_usec)
      {
	t->d = 1;
	t->cs = id[i].cs;
	t->t_new = id[i].t_new;
	t->t = id[i].t;
	t->action = xmalloc(sizeof(char *) * my_strlen(id[i].action));
	strcpy(t->action, id[i].action);
	break;
      }
}

t_timev		take_first_action(/* t_timev *time,  */t_timev *id)
{
  t_timev	t;
  int		i;

  i = 0;
  get_small_time(&t, id, i);
  return (t);
}

void	get_time_exec_2(t_timev *id, t_timev *time)
{
  int	x;

  while (time)
    {
      x = time->cs;
      if (id[x].d == time->d)
	{
	  id[x].t_new = time->t_new;
	  id[x].t_old = time->t_old;
	  id[x].t = time->t;
	  id[x].action = xmalloc(sizeof(char*) * my_strlen(time->action));
	  strcpy(id[x].action, time->action);
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
      id[x].t.tv_sec = 60000000;
      id[x].t.tv_usec = 60000000;
      id[x].t_new.tv_sec = 2000000000;
      id[x].t_new.tv_usec = 2000000000;
      id[x].d = 1000000000;
    }
  while (time)
    {
      x = time->cs;
      id[x].cs = x;
      id[x].d = MIN_NB(id[x].d, time->d);
      time = time->next;
    }
}

void		manage_time_in_select(t_timev t, struct timeval *tv)
{
  tv->tv_sec = t.t.tv_sec;
  tv->tv_usec = t.t.tv_usec;
}

void		update_time_struct(t_timev *time, t_env *e)
{
  while (time)
    {
      time->t.tv_sec = time->t_old.tv_sec - e->tv.tv_sec;
      time->t.tv_usec = time->t_old.tv_usec - e->tv.tv_usec;
      if (time->t.tv_sec < 0)
	time->t.tv_sec = 0;
      if (time->t.tv_usec < 0)
	time->t.tv_usec = 0;
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
      t.t.tv_sec = 0;
      t.t.tv_usec = 0;
    }
  else
    {
      get_time_exec(id, serv->tv);
      get_time_exec_2(id, serv->tv);
     t = take_first_action(/* serv->tv, */ id);
    }
  return (t);
}
