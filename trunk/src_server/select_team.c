/*
** select_team.c for team in /u/all/iniong_a/cu/rendu/c/zappy/src_server
** 
** Made by aime-bijou iniongo
** Login   <iniong_a@epitech.net>
** 
** Started on  Sat May 29 21:29:53 2010 aime-bijou iniongo
** Last update Mon Jun 14 17:42:51 2010 aime-bijou iniongo
*/

#include <stdio.h>
#include <string.h>
#include "../includes/server.h"

void		return_place_on_team(t_play *player, t_team *team)
{
  void		*save;

  save = team;
  while (team)
    {
      if (my_strcmp(team->name, player->team) == 0)
	team->place++;
      team = team->next;
    }
  team = save;
}

int	place_in_the_team(t_team *team, char *team_name)
{
  int	place;

  place = 0;
  while (team)
    {
      if (my_strcmp(team_name, team->name) == 0)
	place = team->place;
      team = team->next;
    }
  return (place);
}

void		take_a_team(t_play *player, char *team, t_env *e, t_team *myteam)
{
  int		len;

  len = my_strlen(team);
  while (myteam)
    {
      if (my_strcmp(myteam->name, team) == 0)
	{
	  if (myteam->place > 0)
	    {
	      player[e->i].team = xmalloc(sizeof(char*) * len);
	      strcpy(player[e->i].team, team);
	      myteam->place--;
	      write(player[e->i].cs, "ok\n", 3);
	      printf("client %d choose ' %s ' as his team\n", player[e->i].cs, team);
	      break;
	    }
	  else
	    {
	      close_client(player, e);
	      break;
	    }
	}
      myteam = myteam->next;
    }
}

void		choose_a_team(t_desc *serv, t_play *players, char *buff, t_env *e)
{
  int		flags;
  int		x;
  int		t;

  flags = 0;
  x = 0;
  t = 0;
  if (buff != NULL)
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
    take_a_team(players, serv->team[t], e, e->team);
}

void		add_elem_in_team(t_desc *serv, t_team **team, int i)
{
  t_team	*new;

  new = xmalloc(sizeof(new));
  new->name = strdup(serv->team[i]);
  new->place = serv->nb_sock;
  new->next = *team;
  *team = new;
}
