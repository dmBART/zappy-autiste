/*
** select_team.c for team in /u/all/iniong_a/cu/rendu/c/zappy/src_server
** 
** Made by aime-bijou iniongo
** Login   <iniong_a@epitech.net>
** 
** Started on  Sat May 29 21:29:53 2010 aime-bijou iniongo
** Last update Tue Jun  1 01:26:42 2010 aime-bijou iniongo
*/

#include <stdio.h>
#include <string.h>
#include "../includes/server.h"

void		take_a_team(t_play *player, char *team, t_env *e, t_team **myteam)
{
  int		len;

  len = my_strlen(team);
  while ((*myteam)->next != NULL)
    (*myteam) = (*myteam)->next;
  while ((*myteam))
    {
      if (my_strcmp(((*myteam))->name, team) == 0)
	{
	  if (((*myteam))->place > 0)
	    {
	      player[e->i].team = xmalloc(sizeof(char*) * len);
	      strcpy(player[e->i].team, team);
	      (*myteam)->place--;
	      write(player[e->i].cs, "ok\n", 3);
	      printf("client %d choose ' %s ' as his team\n", player[e->i].cs, team);
	      break;
	    }
	  else
	    {
	      write(player[e->i].cs, "ko\n", 3);
	      close_client(player, e);
	      break;
	    }
	}
      (*myteam) = (*myteam)->prev;
    }
}

void		choose_a_team(t_desc *serv, t_play *players, char *buff, t_env *e)
{
  int		flags;
  int		x;
  int		t;

  flags = 0;
  x = 0;
  while (serv->team[x] != NULL)
    {
      if (my_strcmp(serv->team[x], buff) == 0)
	{
	  flags = 1;
	  t = x;
	  break;
	}
      x++;
    }
  if (flags == 0)
    close_client(players, e);
  else
    take_a_team(players, serv->team[t], e, &e->team);
}

void		add_elem_in_team(t_desc *serv, t_team **team, int i)
{
  t_team	*new;

  new = xmalloc(sizeof(new));
  new->name = strdup(serv->team[i]);
  new->place = serv->nb_sock;
  new->next = *team;
  /*  new->prev = 0;*/
  if (*team)
    (*team)->prev = new;
  *team = new;
}
