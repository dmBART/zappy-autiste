/*
** getion_timer.c for timer in /u/all/iniong_a/cu/rendu/c/zappy/src_server
** 
** Made by aime-bijou iniongo
** Login   <iniong_a@epitech.net>
** 
** Started on  Sat May 29 22:35:24 2010 aime-bijou iniongo
** Last update Sat Jun 12 22:27:29 2010 aime-bijou iniongo
*/

#include <sys/time.h>
#include <string.h>
#include <stdio.h>
#include "../includes/server.h"

typedef struct	s_str
{
  char		*str;
  int		time;
}		t_str;

t_str	str_tab[]= {
  {"inventaire", 1},
  {"avance", 7},
  {"droite", 7},
  {"gauche", 7},
  {"voir", 7},
  {"prend", 7},
  {"pose", 7},
  {NULL, 0}
};

void		add_elem(t_timev **player, char *action, int id, t_env *e)
{
  int		i;
  double	inc;
  t_timev	*new;

  i = 0;
  new = xmalloc(sizeof(*new));
  new->action = strdup(action);
  new->d = e->end;
  printf("%d\n", new->d);
  new->cs = id;
  gettimeofday(&new->t_new, NULL);
  while (str_tab[i].str != NULL)
    {
      if (e->state == 0 && strcmp(action, "life") == 0)
	{
	  inc = 1260 /e->t * 1000000;
	  new->t.tv_sec = (long)inc / 1000000;
	  new->t.tv_usec = (long)inc % 1000000;
	  break;
	}
      else if (my_strcmp(str_tab[i].str, action) == 0)
	{
	  inc = (double)((str_tab[i].time / e->t) * 1000000);
	  new->t.tv_sec = (long)inc / 1000000;
	  new->t.tv_usec = (long)inc % 1000000;
	  break;
	}
      i++;
    }
  if (i == 7)
    {
      new->t.tv_sec = 0;
      new->t.tv_usec = 0;
    }
  new->t_old.tv_sec = new->t.tv_sec + new->t_new.tv_sec;
  new->t_old.tv_usec = new->t.tv_usec + new->t_new.tv_usec;
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
  cpt = i;
  save = *time;
  while (*time)
    {
      if (my_strcmp((*time)->action, t.action) == 0 &&
	  (*time)->t_new.tv_sec == t.t_new.tv_sec &&
	  (*time)->t_new.tv_usec == t.t_new.tv_usec)
	{
	  printf("in del struct timer and action = %s \n", t.action);
	  cpt = i;
	  break;
	}
      *time = (*time)->next;
      i++;
    }
  tmp = *time;
  if (cpt == 0)
    {
      free((*time)->action);
      *time = (*time)->next;
      free(save);
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
      free(tmp);
      *time = save;
    }
/*   t.t = 0; */
}

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
