/*
** select_team.c for team in /u/all/iniong_a/cu/rendu/c/zappy/src_server
** 
** Made by aime-bijou iniongo
** Login   <iniong_a@epitech.net>
** 
** Started on  Sat May 29 21:29:53 2010 aime-bijou iniongo
** Last update Sat May 29 22:15:53 2010 aime-bijou iniongo
*/

#include <stdio.h>
#include <string.h>
#include "../includes/server.h"

void		take_a_team(t_play *player, char *team, int i)
{
  int		len;

  len = my_strlen(team);
  player[i].team = xmalloc(sizeof(char*) * len);
  strcpy(player[i].team, team);
  write(player[i].cs, "ok\n", 3);
  printf("client %d choose ' %s ' as his team\n", player[i].cs, team);
}

void		choose_a_team(t_desc *serv, t_play *players, char *buff, int i)
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
    close_client(players, i);
  else
    take_a_team(players, serv->team[t], i);
}
