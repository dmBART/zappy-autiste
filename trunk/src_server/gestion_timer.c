/*
** getion_timer.c for timer in /u/all/iniong_a/cu/rendu/c/zappy/src_server
** 
** Made by aime-bijou iniongo
** Login   <iniong_a@epitech.net>
** 
** Started on  Sat May 29 22:35:24 2010 aime-bijou iniongo
** Last update Thu Jun 17 23:48:25 2010 aime-bijou iniongo
*/

#include <sys/time.h>
#include <string.h>
#include <stdio.h>
#include "../includes/server.h"

void	get_small_time(t_timev *t, t_timev *id, int i, t_timev t_life)
{
  int	flags;

  flags = 0;
  i = -1;
  t->t_old.tv_sec = 2000000000;
  t->t_old.tv_usec = 2000000000;
  while (i++ < MAX_IN)
    if (id[i].t_new.tv_sec != 2000000000 && id[i].d != 1000000000)
      t->t_old.tv_sec = MIN_NB(id[i].t_old.tv_sec, t->t_old.tv_sec);
  i = -1;
  while (i++ < MAX_IN)
    if(t->t_old.tv_sec == id[i].t_old.tv_sec && id[i].d != 1000000000)
      t->t_old.tv_usec = MIN_NB(id[i].t_old.tv_usec, t->t_old.tv_usec);
  i = -1;
  if (t->t_old.tv_sec  >= t_life.t_old.tv_sec)
    {
       t->d = 1;
       t->cs = t_life.cs;
       t->t_new = t_life.t_new;
       t->t_old = t_life.t_old;
       t->t = t_life.t;
       t->action = xmalloc(sizeof(char *) * my_strlen("vie"));
       strcpy(t->action, "vie");
    }
  else
    {
    while (i++ < MAX_IN)
      if(t->t_old.tv_sec == id[i].t_old.tv_sec &&
	 t->t_old.tv_usec == id[i].t_old.tv_usec
	 && id[i].d > 0)
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
}

void		get_small_life(t_timev *life, t_timev *t_life)
{
  int		i;

  i = -1;
  t_life->t_old.tv_sec = 2000000000;
  t_life->t_old.tv_usec = 2000000000;
  while (i++ < MAX_IN)
    if (life[i].t_old.tv_sec != 2000000000)
      t_life->t_old.tv_sec = MIN_NB(t_life->t_old.tv_sec, life[i].t_old.tv_sec);
  i = -1;
  while (i++ < MAX_IN)
    if(t_life->t_old.tv_sec == life[i].t_old.tv_sec && life[i].d != 60000000)
      t_life->t_old.tv_usec = MIN_NB(life[i].t_old.tv_usec, t_life->t_old.tv_usec);
  i = -1;
  if (t_life->t_old.tv_sec  != 2000000000)
    while (i++ < MAX_IN)
      if(t_life->t_old.tv_sec == life[i].t_old.tv_sec &&
	 t_life->t_old.tv_usec == life[i].t_old.tv_usec
	 && life[i].d > 0)
	{
	  t_life->d = 1;
	  t_life->cs = life[i].cs;
	  t_life->t_new = life[i].t_new;
	  t_life->t = life[i].t;
	  t_life->action = xmalloc(sizeof(char *) * my_strlen(life[i].action));
	  strcpy(t_life->action, life[i].action);
	  break;
	}
}

t_timev		take_first_action(t_timev *id, t_timev *life)
{
  t_timev	t;
  t_timev	t_life;
  int		i;

  i = 0;
  get_small_life(life, &t_life);
  get_small_time(&t, id, i, t_life);
  return (t);
}

void	get_time_exec_2(t_timev *id, t_timev *time)
{
  int	x;

  while (time)
    {
      x = time->cs;
      if (id[x].d > 0)
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
      if (time->d != 1)
	{
	  id[x].cs = x;
	  id[x].d = MIN_NB(id[x].d, time->d);
	}
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

void		get_life(t_timev *life, t_timev *time)
{
  int		x;

  x = 0;
  while (time)
    {
      x = time->cs;
      if (time->action != NULL && time->d == 1/* my_strcmp(time->action, "vie") == 0 */)
	{
	  life[x].d = time->d;
	  life[x].cs = x;
	  life[x].action = xmalloc(sizeof(char *) * my_strlen(time->action));
	  strcpy(life[x].action, "vie");
	  life[x].t = time->t;
	  life[x].t_new = time->t_new;
	  life[x].t_old = time->t_old;
	}
      time = time->next;
    }
}

void		free_time(t_timev *life, t_timev *id)
{
  int		x;

  x = -1;
  while (x++ < MAX_IN)
    {
      if(id[x].action != NULL)
	{
	  free(id[x].action);
	  id[x].action = NULL;
	}
      if(life[x].action != NULL)
	{
	  free(life[x].action);
	  life[x].action = NULL;
	}
    }
}

void		init_struct(t_timev *life, t_timev *id)
{
  int		x;

  x = -1;
  while (x++ < MAX_IN)
    {
      life[x].t.tv_sec = 2000000000;
      life[x].t.tv_usec = 60000000;
      life[x].t_new.tv_sec = 2000000000;
      life[x].t_new.tv_usec = 2000000000;
      life[x].t_old.tv_sec = 2000000000;
      life[x].t_old.tv_usec = 2000000000;
      life[x].d = 1000000000;
    }
  x = -1;
  while (x++ < MAX_IN)
    {
      id[x].d = 1000000000;
      life[x].d = 0;
      id[x].action = NULL;
      life[x].action = NULL;
    }
}

t_timev		manage_time(t_desc *serv)
{
  t_timev	t;
  t_timev	life[MAX_IN];
  t_timev	id[MAX_IN];

  t.t_old.tv_sec = 0;
  if (serv->tv == NULL)
    {
      t.d = 0;
      t.t.tv_sec = 0;
      t.t.tv_usec = 0;
    }
  else
    {
      init_struct(life, id);
      get_life(life, serv->tv);
      get_time_exec(id, serv->tv);
      get_time_exec_2(id, serv->tv);
      t = take_first_action(id, life);
      free_time(life, id);
      if (t.t_old.tv_sec == 2000000000)
	{
	  t.d = 0;
	  t.t.tv_sec = 0;
	  t.t.tv_usec = 0;
	}
    }
  return (t);
}
