/*
** getion_timer.c for timer in /u/all/iniong_a/cu/rendu/c/zappy/src_server
** 
** Made by aime-bijou iniongo
** Login   <iniong_a@epitech.net>
** 
** Started on  Sat May 29 22:35:24 2010 aime-bijou iniongo
** Last update Sat May 29 23:07:49 2010 aime-bijou iniongo
*/

#include <string.h>
#include "../includes/server.h"

void		add_elem(t_timev **player, char *action)
{
  t_timev	*new;

  new = xmalloc(sizeof(new));
  new->action = strdup(action);
  new->p = 1;
  if (my_strcmp(action, "incantation") == 0)
    new->time = 300;
  else if (my_strcmp(action, "inventaire") == 0)
    new->time = 1;
  else
    new->time = 7;
  new->prev = 0;
  *player = new;
  if (*player)
    (*player)->prev = new;
  new->next = *player;
}
