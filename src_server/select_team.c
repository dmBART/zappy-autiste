/*
** select_team.c for team in /u/all/iniong_a/cu/rendu/c/zappy/src_server
** 
** Made by aime-bijou iniongo
** Login   <iniong_a@epitech.net>
** 
** Started on  Sat May 29 21:29:53 2010 aime-bijou iniongo
** Last update Sun Jun 20 23:54:03 2010 aime-bijou iniongo
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

  ghost = MAX_FD + 1;
  while (ghost < MAX_GHOST)
    {
      if (players[ghost].type == FD_GHOST)
	if (my_strcmp(players[ghost].team, team_name) == 0)
	    return (ghost);
      ghost++;
    }
  return (-1);
}

void		re_init_player(t_play *ghost, t_play *player)
{
  int		x;

  x = 0;
  player->type = FD_CLIENT;
  ghost->type = FD_FREE;
  player->inv = xmalloc(sizeof(int *) * 7);
  player->dir = ghost->dir;
  player->lvl = ghost->lvl;
  player->x = ghost->x;
  player->y = ghost->y;
  while (x < 7)
    {
      player->inv[x] = ghost->inv[x];
      x++;
    }
  free(ghost->inv);
}

int	take_a_team(t_play *player, char *team, t_env *e, t_team *myteam)
{
  int	len;
  int	ghost;

  len = my_strlen(team);
  if ((ghost = ghost_player(player, team)) >= 0)
    re_init_player(&player[ghost], &player[e->i]);
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
	      return (0);
	    }
	}
      myteam = myteam->next;
    }
  return (-1);
}

int	chop_flags(t_desc *serv, t_play *players, t_env *e, int flags, int t)
{
  if (flags == 0)
    {
      close_client(serv->tv, &players[e->i], e);
      return (-1);
    }
  else
    {
      if (take_a_team(players, serv->team[t], e, e->team) == -1)
	{
	  close_client(serv->tv, &players[e->i], e);
	  return (-1);
	}
    }
  return (0);
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
  if (chop_flags(serv, players, e, flags, t) == -1)
    return (-1);
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
