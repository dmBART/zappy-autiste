/*
** elem_timer.c for elem timer in /u/all/iniong_a/cu/rendu/c/tmp
** 
** Made by aime-bijou iniongo
** Login   <iniong_a@epitech.net>
** 
** Started on  Mon Jun 14 17:19:31 2010 aime-bijou iniongo
** Last update Sun Jun 20 23:41:53 2010 aime-bijou iniongo
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
  {"connect_nbr", 1},
  {"inventaire", 1},
  {"avance", 7},
  {"droite", 7},
  {"gauche", 7},
  {"prend", 7},
  {"voir", 7},
  {"pose", 7},
  {"incantation", 300},
  {NULL, 0}
};

void		time_of_execution(t_timev *new, char *action, int t)
{
  int		i;
  int		len;
  double	inc;

  i = 0;
  while (str_tab[i].str != NULL)
    {
      len = my_strlen(str_tab[i].str) - 1;
       if (strncmp(str_tab[i].str, action, len) == 0)
	if (action[len + 1] == '\0' || action[len + 1] == ' ')
	  {
	    inc = (double)((str_tab[i].time / t) * 1000000);
	    new->t.tv_sec = (long)inc / 1000000;
	    new->t.tv_usec = (long)inc % 1000000;
	    break;
	  }
      i++;
    }
  if (str_tab[i].str == NULL)
    {
      new->t.tv_sec = 0;
      new->t.tv_usec = 0;
    }
}

void		add_elem(t_timev **player, char *action, int id, t_env *e)
{
  int		i;
  double	inc;
  t_timev	*new;

  i = 0;
  new = xmalloc(sizeof(*new));
  new->action = xmalloc(sizeof(char *) * my_strlen(action));
  new->action = strcpy(new->action, action);
  new->d = e->end;
  new->cs = id;
  gettimeofday(&new->t_new, NULL);
  if (e->state == 0 && strcmp(action, "vie") == 0)
    {
      inc = (double)(126 / e->t * 1000000);
      new->t.tv_sec = (long)inc / 1000000;
      new->t.tv_usec = (long)inc % 1000000;
      e->state = 1;
    }
  else
    time_of_execution(new, action, e->t);
  new->t_old.tv_sec = new->t.tv_sec + new->t_new.tv_sec;
  new->t_old.tv_usec = new->t.tv_usec + new->t_new.tv_usec;
  new->next = *player;
  *player = new;
}

void	del_elem_other(int cpt, void *save, void *tmp, t_timev **time)
{
  int	i;

  i = 0;
  tmp = *time;
  *time = save;
  if (cpt == 0)
    {
      free((*time)->action);
      *time = (*time)->next;
    }
  else
    {
      *time = save;
      while (i < (cpt - 1))
	{
	  *time = (*time)->next;
	  i++;
	}
      if (*time != NULL)
	{
	  free((*time)->action);
	  (*time)->next = (*time)->next->next;
	  *time = save;
	}
    }
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
  tmp = *time;
  while (*time)
    {
      if (my_strcmp((*time)->action, t.action) == 0 &&
	  (*time)->t_old.tv_sec == t.t_old.tv_sec &&
	  (*time)->t_old.tv_usec == t.t_old.tv_usec)
	{
	  cpt = i;
	  break;
	}
      *time = (*time)->next;
      i++;
    }
  del_elem_other(cpt, save, tmp, time);
}

void	del_elem_player(t_timev **eve, int fd, int size)
{
  int	i;
  int	x;
  int	*cpt;
  void	*save;
  void	*tmp;

  i = 0;
  x = 0;
  printf("size = %d\n", size);
  cpt = xmalloc(sizeof(*cpt) * size);
  save = *eve;
  tmp = *eve;
  while (*eve)
    {
      if (my_strcmp((*eve)->action, "vie") == 0 &&
	  (*eve)->cs == fd)
	{
	  cpt[x] = i;
	  x++;
	}
      *eve = (*eve)->next;
      i++;
    }
  x = -1;
  while (x++ < size)
    del_elem_other(cpt[x], save, tmp, eve);
}
