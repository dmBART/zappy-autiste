/*
** select_team.c for team in /u/all/iniong_a/cu/rendu/c/zappy/src_server
** 
** Made by aime-bijou iniongo
** Login   <iniong_a@epitech.net>
** 
** Started on  Sat May 29 21:29:53 2010 aime-bijou iniongo
** Last update Sat Jun 19 16:11:26 2010 aime-bijou iniongo
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

int		ghost_player(t_play *players, char *team_name)
{
  int		ghost;

  ghost = 0;
  while (ghost < MAX_FD)
    {
      if (players[ghost].type == FD_GHOST)
	if (my_strcmp(players[ghost].team, team_name) == 0)
	  return (ghost);
      ghost++;
    }
  return (-1);
}

void		take_a_team(t_play *player, char *team, t_env *e, t_team *myteam)
{
  int		len;
  int		ghost;

  len = my_strlen(team);
   if ((ghost = ghost_player(player, team)) == 0)
     {
       printf("in the ghost\n");
       player[e->i].type = FD_CLIENT;
       player[ghost].type = FD_FREE;
       player[e->i].inv = player[ghost].inv;
       player[e->i].dir = player[ghost].dir;
       player[e->i].lvl = player[ghost].lvl;
       player[e->i].x = player[ghost].x;
       player[e->i].y = player[ghost].y;
     }
    while (myteam)
      {
	if (my_strcmp(myteam->name, team) == 0)
	  {
	    if (myteam->place > 0)
	      {
		player[e->i].team = xmalloc(sizeof(char*) * len);
		strcpy(player[e->i].team, team);
		myteam->place--;
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

int		choose_a_team(t_desc *serv, t_play *players, char *buff, t_env *e)
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
    {
      close_client(players, e);
      return (-1);
    }
  else
    take_a_team(players, serv->team[t], e, e->team);
  return (0);
}

void		add_elem_in_team(t_desc *serv, t_team **team, int i)
{
  t_team	*new;

  new = xmalloc(sizeof(*new));
  new->name = strdup(serv->team[i]);
  new->place = serv->nb_sock;
  new->next = *team;
  *team = new;
}
