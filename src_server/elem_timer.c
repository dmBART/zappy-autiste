/*
** elem_timer.c for elem timer in /u/all/iniong_a/cu/rendu/c/tmp
** 
** Made by aime-bijou iniongo
** Login   <iniong_a@epitech.net>
** 
** Started on  Mon Jun 14 17:19:31 2010 aime-bijou iniongo
** Last update Tue Jun 15 16:22:10 2010 aime-bijou iniongo
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
  {"prend", 7},
  {"voir", 7},
  {"pose", 7},
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
  new->action = strdup(action);
  new->d = e->end;
  new->cs = id;
  gettimeofday(&new->t_new, NULL);
  printf("nbr = %d\n", new->d);
  if (e->state == 0 && strcmp(action, "vie") == 0)
    {
      inc = (double)(126 / e->t * 1000000);
      printf("vie = %f\n", inc);
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

