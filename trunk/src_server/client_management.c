/*
** client_management.c for serveur in /u/all/iniong_a/cu/rendu/c/zappy/src_server
** 
** Made by aime-bijou iniongo
** Login   <iniong_a@epitech.net>
** 
** Started on  Fri May 28 00:49:11 2010 aime-bijou iniongo
** Last update Sat May 29 23:06:46 2010 aime-bijou iniongo
*/

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include "../includes/server.h"

void		close_client(t_play *player, int i)
{
  player[i].type = FD_FREE;
  write(player[i].cs, "ko\n", 3);
  close(player[i].cs);
  if (player[i].team != NULL)
    free(player[i].team);
  player[i].team = NULL;
}

void		manage_client(t_desc *serv, t_play *players, fd_set readfs)
{
  int		i;
  int		n;
  int		len;
  int		x;
  char		buff[4091];

  i = 0;
  while (i < MAX_FD)
    {
      if (players[i].type == FD_CLIENT && FD_ISSET(players[i].cs, &readfs))
	{
	  memset(buff, 0, 4090);
	  n = xread(players[i].cs, buff, 4090);
	  if (n == 0)
	    {
	      printf("client deconnected\n");
	      players[i].type = FD_FREE;
	    }
	  else
	    {
	      len = n - 2;
	      if (buff[len] == 13)
		buff[len] = '\0';
	      buff[n - 1] = '\0';
	      if (players->team == NULL)
		choose_a_team(serv, players, buff, i);
	      else
		add_elem(&players[i].t, buff);
	    }
	}
      i++;
    }
}

void			add_players(int s, t_env *e, t_play *players)
{
  int			x;
  unsigned int		len;
  struct sockaddr_in	client;

  x = 0;
  len = sizeof(client);
  if ((e->cs = accept(s, (struct sockaddr*)&client, &len)) != -1)
    while (x < MAX_FD)
      {
	if (players[x].type == FD_FREE)
	  {
	    players[x].cs = e->cs;
	    printf("new connection %d\n", players[x].cs);
	    players[x].ip = inet_ntoa(client.sin_addr);
	    players[x].life = 1260;
	    write(e->cs, "BIENVENUE\n", 10);
	    players[x].type = FD_CLIENT;
	    players[x].t = NULL;
	    break;
	  }
	x++;
      }
}
